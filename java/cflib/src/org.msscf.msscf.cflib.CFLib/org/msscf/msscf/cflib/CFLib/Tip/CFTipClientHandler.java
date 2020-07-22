/*
 *	MSS Code Factory CFLib 2.13
 *
 *	Copyright (c) 2020 Mark Stephen Sobkow
 *
 *	This file is part of MSS Code Factory.
 *
 *	MSS Code Factory is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU Lesser General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	MSS Code Factory is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU Lesser General Public License for more details.
 *
 *	You should have received a copy of the GNU Lesser General Public License
 *	along with MSS Code Factory.  If not, see https://www.gnu.org/licenses/.
 *
 *	Donations to support MSS Code Factory can be made at
 *	https://www.paypal.com/paypalme2/MarkSobkow
 *
 *	Contact Mark Stephen Sobkow at msobkow@sasktel.net for commercial licensing.
 */

package org.msscf.msscf.cflib.CFLib.Tip;

import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.net.URISyntaxException;
import java.net.URL;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.KeyFactory;
import java.security.NoSuchAlgorithmException;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.SecureRandom;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.X509EncodedKeySpec;

import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.KeyGenerator;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.SecretKey;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;

import org.msscf.msscf.cflib.CFLib.*;

import org.apache.commons.codec.binary.Base64;
import org.apache.xerces.xni.grammars.Grammar;
import org.xml.sax.*;

public class CFTipClientHandler
	extends CFLibXmlCoreSaxParser
	implements ContentHandler
{

	// The namespace URI of the supported schema
	public final static String	SCHEMA_XMLNS = "uri://org.msscf/msscf/2.0.13/CFTipServerInfo";

	// The source for loading the supported schema
	public final static String	SCHEMA_URI = "/opt/msscf/2.0.13/xsd/cftip-2.13-serverinfo.xsd";
	public final static String	SCHEMA_ROOT_URI = "/xsd/cftip-2.13-serverinfo.xsd";

	protected static Grammar myGrammar = null;
	
	// Constructors

	public CFTipClientHandler() {
		super();
		setRootElementHandler( getSaxRqstRootHandler() );
		if( myGrammar == null ) {
			InputStream input;
			File file = new File( SCHEMA_URI );
			if( file.exists() ) {
				try {
					input = new FileInputStream( file );
				}
				catch( Exception e ) {
					input = null;
				}
				if( input != null ) {
					myGrammar = addToGrammarPool( SCHEMA_URI, input );
				}
			}
			else {
				input = getClass().getResourceAsStream( SCHEMA_ROOT_URI );
				if( input != null ) {
					myGrammar = addToGrammarPool( SCHEMA_ROOT_URI, input );
				}
			}
		}
		initParser();
	}

	public CFTipClientHandler( ICFLibMessageLog logger ) {
		super( logger );
		setRootElementHandler( getSaxRqstRootHandler() );
		if( myGrammar == null ) {
			InputStream input;
			File file = new File( SCHEMA_URI );
			if( file.exists() ) {
				try {
					input = new FileInputStream( file );
				}
				catch( Exception e ) {
					input = null;
				}
				if( input != null ) {
					myGrammar = addToGrammarPool( SCHEMA_URI, input );
				}
			}
			else {
				input = getClass().getResourceAsStream( SCHEMA_ROOT_URI );
				if( input != null ) {
					myGrammar = addToGrammarPool( SCHEMA_ROOT_URI, input );
				}
			}
		}
		initParser();
	}

	// The Response Handler for the incoming response messages

	private ICFTipResponseHandler responseHandler = null;

	public ICFTipResponseHandler getResponseHandler() {
		return( responseHandler );
	}

	public void setResponseHandler( ICFTipResponseHandler value ) {
		final String S_ProcName = "setResponseHandler";
		if( value == null ) {
			throw new CFLibNullArgumentException( getClass(),
				S_ProcName,
				1,
				"value" );
		}
		responseHandler = value;
	}

	// Server Information

	private CFTipServerInfo serverInfo = null;

	public CFTipServerInfo getServerInfo() {
		return( serverInfo );
	}

	void setServerInfo( CFTipServerInfo value ) {
		serverInfo = value;
	}

	// Session key and accessors
	
	private SecretKey sessionKey = null;
	
	public void initSessionKey() throws NoSuchAlgorithmException {
		KeyGenerator kg = KeyGenerator.getInstance( "AES" );
		kg.init( 256, new SecureRandom() );
		sessionKey = kg.generateKey();
	}

	public byte[] getEncodedSessionKey()
	throws NoSuchAlgorithmException,
		NoSuchPaddingException,
		InvalidKeyException,
		IllegalBlockSizeException
	{
		final String S_ProcName = "getEncodedSessionKey";
		
		if( sessionKey == null ) {
			throw new CFLibUsageException( getClass(),
				S_ProcName,
				"Session key must be initialized by initSessionKey()" );
		}
		
		byte encoded[] = sessionKey.getEncoded();
		
		return( encoded );
	}

	public void setEncodedSessionKey( byte encoded[] )
	throws NoSuchAlgorithmException,
		NoSuchPaddingException,
		InvalidKeyException,
		InvalidKeySpecException
	{
		sessionKey = new SecretKeySpec( encoded, "AES" );
	}

	public byte[] encryptWithSessionKey( IvParameterSpec ivspec, byte value[] )
	throws InvalidKeyException,
		NoSuchAlgorithmException,
		NoSuchPaddingException,
		IllegalBlockSizeException,
		BadPaddingException,
		InvalidAlgorithmParameterException
	{
		final String S_ProcName = "encryptWithClientPrivateKey";

		if( sessionKey == null ) {
			throw new CFLibUsageException( getClass(),
				S_ProcName,
				"Session key must be initialized by initSessionKey()" );
		}

		Cipher cipher = Cipher.getInstance( "AES/CBC/PKCS5Padding" );
		if( cipher == null ) {
			throw new CFLibNullArgumentException( getClass(),
				S_ProcName,
				0,
				"cipher" );
		}

		cipher.init( Cipher.ENCRYPT_MODE, sessionKey, ivspec );

		byte encrypted[] = cipher.doFinal( value );

		return( encrypted );
	}

	public byte[] decryptWithSessionKey( IvParameterSpec ivspec, byte value[] )
	throws NoSuchAlgorithmException,
		NoSuchPaddingException,
		InvalidKeyException,
		IllegalBlockSizeException,
		BadPaddingException,
		InvalidAlgorithmParameterException
	{
		final String S_ProcName = "decryptWithClientPrivateKey";

		if( sessionKey == null ) {
			throw new CFLibUsageException( getClass(),
				S_ProcName,
				"Session key must be initialized by initSessionKey()" );
		}

		Cipher cipher = Cipher.getInstance( "AES/CBC/PKCS5Padding" );
		if( cipher == null ) {
			throw new CFLibNullArgumentException( getClass(),
				S_ProcName,
				0,
				"cipher" );
		}

		cipher.init( Cipher.DECRYPT_MODE, sessionKey, ivspec );
		
		byte decrypted[] = cipher.doFinal( value );

		return( decrypted );
	}

	// Session keys and accessors

	// Encryption Support

	// Device name and key
	private String deviceName = null;
	private PublicKey devicePublicKey = null;
	private PrivateKey devicePrivateKey = null;

	public String getDeviceName() {
		return( deviceName );
	}
	
	public void setDeviceName( String value ) {
		deviceName = value;
	}
	
	public PrivateKey getDevicePrivateKey() {
		return( devicePrivateKey );
	}
	
	public void setDevicePrivateKey( PrivateKey value ) {
		devicePrivateKey = value;
	}
	
	public PublicKey getDevicePublicKey() {
		return( devicePublicKey );
	}
	
	public void setDevicePublicKey( PublicKey value ) {
		devicePublicKey = value;
	}

	public byte[] getEncodedDevicePublicKey()
	throws NoSuchAlgorithmException,
		NoSuchPaddingException,
		InvalidKeyException,
		IllegalBlockSizeException
	{
		final String S_ProcName = "getEncodedDevicePublicKey";

		if( devicePublicKey == null ) {
			throw new CFLibUsageException( getClass(),
				S_ProcName,
				"Device keys must be initialized by createDeviceKeys() or loadDeviceKeys()" );
		}

		byte encoded[] = devicePublicKey.getEncoded();
		
		return( encoded );
	}

	public byte[] encryptWithDevicePrivateKey( byte value[] )
	throws InvalidKeyException,
		NoSuchAlgorithmException,
		NoSuchPaddingException,
		IllegalBlockSizeException,
		BadPaddingException
	{
		final String S_ProcName = "encryptWithDevicePrivateKey";

		if( devicePrivateKey == null ) {
			throw new CFLibUsageException( getClass(),
				S_ProcName,
				"Device keys must be initialized by createDeviceKeys() or loadDeviceKeys()" );
		}

		Cipher cipher = Cipher.getInstance( "RSA/ECB/PKCS1Padding" );
		if( cipher == null ) {
			throw new CFLibNullArgumentException( getClass(),
				S_ProcName,
				0,
				"cipher" );
		}

		cipher.init( Cipher.ENCRYPT_MODE, devicePrivateKey );

		byte encrypted[] = cipher.doFinal( value );

		return( encrypted );
	}

	// Request transmitter API; you need to overload this in a subclass
	
	public String sendReceive( String value ) {
		final String S_ProcName = "sendReceive";
		throw new CFLibMustOverrideException( getClass(),
			S_ProcName );
	}

	// Issue a server information query and process the response

	public CFTipServerInfo requestServerInfo()
	throws InvalidKeyException,
		NoSuchAlgorithmException,
		NoSuchPaddingException,
		InvalidKeySpecException
	{
		final String S_ProcName = "requestServerInfo";
		final String msg =
				"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
			+	"<CFTIPEnvelope\n"
			+	"\t\txmlns=\"uri://org.msscf.msscf/cftipenvelope\"\n"
			+	"\t\txmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n"
			+	"\t\txmlns:xs=\"http://www.w3.org/2001/XMLSchema\"\n"
			+	"\t\txsi:schemaLocation=\"uri://org.msscf.msscf/cftipenvelope file:../bin/xsd/cftip-envelope.xsd\" >\n"
			+	"\t<QueryServerInfo />\n"
			+	"</CFTIPEnvelope>\n";
		String response = sendReceive( msg );
		if( ( response == null ) || ( response.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( getClass(),
				S_ProcName,
				0,
				"response" );
		}
		parseStringContents( response );
		if( serverInfo == null ) {
			throw new CFLibNullArgumentException( getClass(),
				S_ProcName,
				0,
				"serverInfo" );
		}
		String encodedServerKey = serverInfo.getServerLoginKey();
		byte decodedServerKey[] = Base64.decodeBase64( encodedServerKey );
		serverInfo.setEncodedServerPublicKey( decodedServerKey );
		return( serverInfo );
	}

	// Issue a login request and process the response
	
	public void issueLoginRequest( String body )
	throws InvalidKeyException,
		NoSuchAlgorithmException,
		NoSuchPaddingException,
		IllegalBlockSizeException,
		BadPaddingException,
		InvalidAlgorithmParameterException
	{
		final String S_ProcName = "issueLoginRequest";

		if( responseHandler == null ) {
			throw new CFLibUsageException( getClass(),
				S_ProcName,
				"Response handler must be set first by setResponseHandler()" );
		}

		if( serverInfo == null ) {
			throw new CFLibUsageException( getClass(),
				S_ProcName,
				"Server info must be queried first by requestServerInfo()" );
		}

		if( ( body == null ) || ( body.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( getClass(),
				S_ProcName,
				1,
				"body" );
		}

		SecureRandom random = new SecureRandom();
		byte iv[] = new byte[16];
		random.nextBytes( iv );
		byte[] base64IV = Base64.encodeBase64( iv );
		String stringIV = new String( base64IV );
		IvParameterSpec ivspec = new IvParameterSpec( iv );
		
		byte[] encodedSessionKey = getEncodedSessionKey();
		byte[] encryptedSessionKey = serverInfo.encryptWithServerPublicKey( encodedSessionKey );
		byte[] base64SessionKey = Base64.encodeBase64( encryptedSessionKey );
		String stringSessionKey = new String( base64SessionKey );

		byte bodyBytes[] = body.getBytes();
		byte serverEncrypted[] = encryptWithSessionKey( ivspec, bodyBytes );
		byte base64Encrypted[] = Base64.encodeBase64( serverEncrypted );
		String encoded = new String( base64Encrypted );

		final String msg =
				"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
			+	"<CFTIPEnvelope\n"
			+	"\t\txmlns=\"uri://org.msscf.msscf/cftipenvelope\"\n"
			+	"\t\txmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n"
			+	"\t\txmlns:xs=\"http://www.w3.org/2001/XMLSchema\"\n"
			+	"\t\txsi:schemaLocation=\"uri://org.msscf.msscf/cftipenvelope file:../bin/xsd/cftip-envelope.xsd\" >\n"
			+	"\t<LoginRequest MessageIV=\"" + stringIV + "\" AES256Key=\"" + stringSessionKey + "\" Payload=\"" + encoded + "\" />\n"
			+	"</CFTIPEnvelope>\n";
		String response = sendReceive( msg );
		if( ( response == null ) || ( response.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( getClass(),
				S_ProcName,
				0,
				"response" );
		}
		byte responseBytes[] = Base64.decodeBase64( response );
		byte decrypted[] = decryptWithSessionKey( ivspec, responseBytes );
		String decryptedResponse = new String( decrypted );
		responseHandler.parseStringContents( decryptedResponse );
	}

	// Issue an application request and process the response
	
	public void issueAppRequest( String body )
	throws InvalidKeyException,
		NoSuchAlgorithmException,
		NoSuchPaddingException,
		IllegalBlockSizeException,
		BadPaddingException,
		InvalidAlgorithmParameterException
	{
		final String S_ProcName = "issueAppRequest";

		if( responseHandler == null ) {
			throw new CFLibUsageException( getClass(),
				S_ProcName,
				"Response handler must be set first by setResponseHandler()" );
		}

		if( serverInfo == null ) {
			throw new CFLibUsageException( getClass(),
				S_ProcName,
				"Server info must be queried first by requestServerInfo()" );
		}

		if( sessionKey == null ) {
			throw new CFLibUsageException( getClass(),
				S_ProcName,
				"Session key must be set first by logging in" );
		}

		if( ( body == null ) || ( body.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( getClass(),
				S_ProcName,
				1,
				"body" );
		}

		SecureRandom random = new SecureRandom();
		byte iv[] = new byte[16];
		random.nextBytes( iv );
		byte[] base64IV = Base64.encodeBase64( iv );
		String stringIV = new String( base64IV );
		IvParameterSpec ivspec = new IvParameterSpec( iv );

		byte bodyBytes[] = body.getBytes();
		byte serverEncrypted[] = encryptWithSessionKey( ivspec, bodyBytes );
		byte base64Encrypted[] = Base64.encodeBase64( serverEncrypted );
		String encoded = new String( base64Encrypted );

		final String msg =
				"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
			+	"<CFTIPEnvelope\n"
			+	"\t\txmlns=\"uri://org.msscf.msscf/cftipenvelope\"\n"
			+	"\t\txmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n"
			+	"\t\txmlns:xs=\"http://www.w3.org/2001/XMLSchema\"\n"
			+	"\t\txsi:schemaLocation=\"uri://org.msscf.msscf/cftipenvelope file:../bin/xsd/cftip-envelope.xsd\" >\n"
			+	"\t<AppRequest MessageIV=\"" + stringIV + "\" Payload=\"" + encoded + "\" />\n"
			+	"</CFTIPEnvelope>\n";
		String response = sendReceive( msg );
		if( ( response == null ) || ( response.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( getClass(),
				S_ProcName,
				0,
				"response" );
		}
		byte responseBytes[] = Base64.decodeBase64( response );
		byte decrypted[] = decryptWithSessionKey( ivspec, responseBytes );
		String decryptedResponse = new String( decrypted );
		responseHandler.parseStringContents( decryptedResponse );
	}
	
	// Element Handler instances

	private CFTipSaxServerInfoRootHandler saxServerInfoRootHandler = null;
	private CFTipSaxServerInfoDocHandler saxServerInfoDocHandler = null;
	private CFTipAltSchemaEltHandler altSchemaEltHandler = null;
	
	// Element Handler Resolver Factories

	protected CFTipAltSchemaEltHandler getAltSchemaEltHandler() {
		if( altSchemaEltHandler == null ) {
			altSchemaEltHandler = new CFTipAltSchemaEltHandler( this );
		}
		return( altSchemaEltHandler );
	}

	protected CFTipSaxServerInfoDocHandler getSaxServerInfoDocHandler() {
		if( saxServerInfoDocHandler == null ) {
			saxServerInfoDocHandler = new CFTipSaxServerInfoDocHandler( this );
			saxServerInfoDocHandler.addElementHandler( "AltSchema", getAltSchemaEltHandler() );
		}
		return( saxServerInfoDocHandler );
	}

	// Root Element Handler Resolver Factory

	protected CFTipSaxServerInfoRootHandler getSaxRqstRootHandler() {
		if( saxServerInfoRootHandler == null ) {
			saxServerInfoRootHandler = new CFTipSaxServerInfoRootHandler( this );
			saxServerInfoRootHandler.addElementHandler( "CFTipServerInfo", getSaxServerInfoDocHandler() );
		}
		return( saxServerInfoRootHandler );
	}

	// Root Element Handler

	/*
	 *	CFTipSaxServerInfoRootHandler XML SAX Root Element Handler implementation
	 */
	public class CFTipSaxServerInfoRootHandler
		extends CFLibXmlCoreElementHandler
	{
		public CFTipSaxServerInfoRootHandler( CFTipClientHandler xmsgRqstHandler ) {
			super( xmsgRqstHandler );
		}

		public void startElement(
			String		uri,
			String		localName,
			String		qName,
			Attributes	attrs )
		throws SAXException
		{
		}

		public void endElement(
			String		uri,
			String		localName,
			String		qName )
		throws SAXException
		{
		}
	}

	// Document Element Handler

	/*
	 *	CFTipSaxServerInfoDocHandler XML SAX Doc Element Handler implementation
	 */
	public class CFTipSaxServerInfoDocHandler
		extends CFLibXmlCoreElementHandler
	{
		public CFTipSaxServerInfoDocHandler( CFTipClientHandler clientHandler ) {
			super( clientHandler );
		}

		public void startElement(
			String		uri,
			String		localName,
			String		qName,
			Attributes	attrs )
		throws SAXException
		{
			final String S_ProcName = "startElement";
			final String S_LocalName = "LocalName";

			CFTipClientHandler clientHandler = (CFTipClientHandler)getParser();
			if( clientHandler == null ) {
				throw new CFLibNullArgumentException( getClass(),
					S_ProcName,
					0,
					"getParser()" );
			}

			try {
				// Common XML Attributes
				String	attrId = null;
				// Request Attributes
				String	attrClusterURL = null;
				String	attrClusterDescr = null;
				String	attrSchemaName = null;
				String	attrSchemaDescr = null;
				String	attrServerLoginKey = null;
				// Attribute Extraction
				String	attrLocalName;
				int		numAttrs;
				int		idxAttr;

				assert qName.equals( "CFTipServerInfo" );

				// Extract Attributes
				numAttrs = attrs.getLength();
				for( idxAttr = 0; idxAttr < numAttrs; idxAttr++ ) {
					attrLocalName = attrs.getLocalName( idxAttr );
					if( attrLocalName.equals( "Id" ) ) {
						if( attrId != null ) {
							throw new CFLibUniqueIndexViolationException( getClass(),
								S_ProcName,
								S_LocalName,
								attrLocalName );
						}
						attrId = attrs.getValue( idxAttr );
					}
					else if( attrLocalName.equals( "ClusterURL" ) ) {
						if( attrClusterURL != null ) {
							throw new CFLibUniqueIndexViolationException( getClass(),
								S_ProcName,
								S_LocalName,
								attrLocalName );
						}
						attrClusterURL = attrs.getValue( idxAttr );
					}
					else if( attrLocalName.equals( "ClusterDescr" ) ) {
						if( attrClusterDescr != null ) {
							throw new CFLibUniqueIndexViolationException( getClass(),
								S_ProcName,
								S_LocalName,
								attrLocalName );
						}
						attrClusterDescr = attrs.getValue( idxAttr );
					}
					else if( attrLocalName.equals( "SchemaName" ) ) {
						if( attrSchemaName != null ) {
							throw new CFLibUniqueIndexViolationException( getClass(),
								S_ProcName,
								S_LocalName,
								attrLocalName );
						}
						attrSchemaName = attrs.getValue( idxAttr );
					}
					else if( attrLocalName.equals( "SchemaDescr" ) ) {
						if( attrSchemaDescr != null ) {
							throw new CFLibUniqueIndexViolationException( getClass(),
								S_ProcName,
								S_LocalName,
								attrLocalName );
						}
						attrSchemaDescr = attrs.getValue( idxAttr );
					}
					else if( attrLocalName.equals( "ServerLoginKey" ) ) {
						if( attrServerLoginKey != null ) {
							throw new CFLibUniqueIndexViolationException( getClass(),
								S_ProcName,
								S_LocalName,
								attrLocalName );
						}
						attrServerLoginKey = attrs.getValue( idxAttr );
					}
					else if( attrLocalName.equals( "schemaLocation" ) ) {
						// ignored
					}
					else {
						throw new CFLibUnrecognizedAttributeException( getClass(),
							S_ProcName,
							getParser().getLocationInfo(),
							attrLocalName );
					}
				}

				// Verify that required attributes were provided

				if( ( attrClusterURL == null ) || ( attrClusterURL.length() <= 0 ) ) {
					throw new CFLibNullArgumentException( getClass(),
						S_ProcName,
						0,
						"ClusterURL" );
				}

				if( ( attrClusterDescr == null ) || ( attrClusterDescr.length() <= 0 ) ) {
					throw new CFLibNullArgumentException( getClass(),
						S_ProcName,
						0,
						"ClusterDescr" );
				}

				if( ( attrSchemaName == null ) || ( attrSchemaName.length() <= 0 ) ) {
					throw new CFLibNullArgumentException( getClass(),
						S_ProcName,
						0,
						"SchemaName" );
				}

				if( ( attrSchemaDescr == null ) || ( attrSchemaDescr.length() <= 0 ) ) {
					throw new CFLibNullArgumentException( getClass(),
						S_ProcName,
						0,
						"SchemaDescr" );
				}

				if( ( attrServerLoginKey == null ) || ( attrServerLoginKey.length() <= 0 ) ) {
					throw new CFLibNullArgumentException( getClass(),
						S_ProcName,
						0,
						"ServerLoginKey" );
				}

				// Initialize a ServerInfo object with the attributes
				
				CFTipServerInfo info = new CFTipServerInfo();
				info.setClusterURL( attrClusterURL );
				info.setClusterDescr( attrClusterDescr );
				info.setSchemaName( attrSchemaName );
				info.setSchemaDescr( attrSchemaDescr );
				info.setServerLoginKey( attrServerLoginKey );

				clientHandler.setServerInfo( info );
			}
			catch( RuntimeException e ) {
				clientHandler.setServerInfo( null );
				throw( e );
			}
			catch( Error e ) {
				clientHandler.setServerInfo( null );
				throw( e );
			}
		}

		public void endElement(
			String		uri,
			String		localName,
			String		qName )
		throws SAXException
		{
		}
	}

	// AltSchemaElt Handler

	public class CFTipAltSchemaEltHandler
		extends CFLibXmlCoreElementHandler
	{
		public CFTipAltSchemaEltHandler( CFTipClientHandler clientHandler ) {
			super( clientHandler );
		}

		public void startElement(
			String		uri,
			String		localName,
			String		qName,
			Attributes	attrs )
		throws SAXException
		{
			final String S_ProcName = "startElement";
			final String S_LocalName = "LocalName";

			CFTipClientHandler clientHandler = (CFTipClientHandler)getParser();
			if( clientHandler == null ) {
				throw new CFLibNullArgumentException( getClass(),
					S_ProcName,
					0,
					"getParser()" );
			}

			// Common XML Attributes
			String	attrId = null;
			// Request Attributes
			String	attrSchemaName = null;
			String	attrSchemaDescr = null;
			// Attribute Extraction
			String	attrLocalName;
			int		numAttrs;
			int		idxAttr;

			assert qName.equals( "AltSchema" );

			// Extract Attributes
			numAttrs = attrs.getLength();
			for( idxAttr = 0; idxAttr < numAttrs; idxAttr++ ) {
				attrLocalName = attrs.getLocalName( idxAttr );
				if( attrLocalName.equals( "Id" ) ) {
					if( attrId != null ) {
						throw new CFLibUniqueIndexViolationException( getClass(),
							S_ProcName,
							S_LocalName,
							attrLocalName );
					}
					attrId = attrs.getValue( idxAttr );
				}
				else if( attrLocalName.equals( "SchemaName" ) ) {
					if( attrSchemaName != null ) {
						throw new CFLibUniqueIndexViolationException( getClass(),
							S_ProcName,
							S_LocalName,
							attrLocalName );
					}
					attrSchemaName = attrs.getValue( idxAttr );
				}
				else if( attrLocalName.equals( "SchemaDescr" ) ) {
					if( attrSchemaDescr != null ) {
						throw new CFLibUniqueIndexViolationException( getClass(),
							S_ProcName,
							S_LocalName,
							attrLocalName );
					}
					attrSchemaDescr = attrs.getValue( idxAttr );
				}
				else if( attrLocalName.equals( "schemaLocation" ) ) {
					// ignored
				}
				else {
					throw new CFLibUnrecognizedAttributeException( getClass(),
						S_ProcName,
						getParser().getLocationInfo(),
						attrLocalName );
				}
			}

			// Verify that required attributes were provided

			if( ( attrSchemaName == null ) || ( attrSchemaName.length() <= 0 ) ) {
				throw new CFLibNullArgumentException( getClass(),
					S_ProcName,
					0,
					"SchemaName" );
			}

			if( ( attrSchemaDescr == null ) || ( attrSchemaDescr.length() <= 0 ) ) {
				throw new CFLibNullArgumentException( getClass(),
					S_ProcName,
					0,
					"SchemaDescr" );
			}

			// Add the alternate schema to the server information
			
			clientHandler.getServerInfo().addAltSchema( attrSchemaName, attrSchemaDescr );
		}

		public void endElement(
			String		uri,
			String		localName,
			String		qName )
		throws SAXException
		{
		}
	}

	// Parse XML string contents

	public void parseStringContents( String str ) {
		setServerInfo( null );
		try {
			super.parseStringContents( str );
		}
		catch( CFLibRuntimeException e ) {
			setServerInfo( null );
			throw( e );
		}
		catch( RuntimeException e ) {
			setServerInfo( null );
			throw( e );
		}
		catch( Exception e ) {
			setServerInfo( null );
			throw( e );
		}
	}

	// Parse a URL

	public void parse( String url ) {
		setServerInfo( null );
		try {
			super.parse( url );
		}
		catch( CFLibRuntimeException e ) {
			setServerInfo( null );
			throw( e );
		}
		catch( RuntimeException e ) {
			setServerInfo( null );
			throw( e );
		}
		catch( Exception e ) {
			setServerInfo( null );
			throw( e );
		}
	}

	// Parse a file

	public void parseFile( String url ) {
		setServerInfo( null );
		try {
			super.parse( url );
		}
		catch( CFLibRuntimeException e ) {
			setServerInfo( null );
			throw( e );
		}
		catch( RuntimeException e ) {
			setServerInfo( null );
			throw( e );
		}
		catch( Exception e ) {
			setServerInfo( null );
			throw( e );
		}
	}
}
