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

package org.msscf.msscf.v2_13.cflib.CFLib.Tip;

import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.PrintStream;
import java.net.URISyntaxException;
import java.net.URL;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.KeyFactory;
import java.security.KeyPair;
import java.security.KeyPairGenerator;
import java.security.NoSuchAlgorithmException;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.SecureRandom;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.X509EncodedKeySpec;

import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.SecretKey;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;

import org.msscf.msscf.v2_13.cflib.CFLib.*;

import org.xml.sax.*;
import org.apache.commons.codec.binary.Base64;
import org.apache.xerces.xni.grammars.Grammar;

public class CFTipEnvelopeHandler
	extends CFLibXmlCoreSaxParser
	implements ContentHandler
{
	// The namespace URI of the supported schema
	public final static String	SCHEMA_XMLNS = "uri://org.msscf/msscf/2.0.13/cftipenvelope";

	// The source for loading the supported schema
	public final static String	SCHEMA_URI = "/opt/msscf/2.0.13/xsd/cftip-2.13-envelope.xsd";
	public final static String	SCHEMA_ROOT_URI = "/xsd/cftip-2.13-envelope.xsd";

	protected static Grammar myGrammar = null;

	// Constructors

	public CFTipEnvelopeHandler() {
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

	public CFTipEnvelopeHandler( ICFLibMessageLog logger ) {
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

	// The Request Handler for the incoming AppRequest and LoginRequest messages

	private ICFTipRequestHandler requestHandler = null;

	public ICFTipRequestHandler getRequestHandler() {
		return( requestHandler );
	}

	public void setRequestHandler( ICFTipRequestHandler value ) {
		final String S_ProcName = "setRequestHandler";
		if( value == null ) {
			throw new CFLibNullArgumentException( getClass(),
				S_ProcName,
				1,
				"value" );
		}
		requestHandler = value;
	}

	// The formatter for processing exceptions
	
	private ICFTipThrowableFormatter throwableFormatter = null;
	
	public ICFTipThrowableFormatter getThrowableFormatter() {
		return( throwableFormatter );
	}
	
	public void setThrowableFormatter( ICFTipThrowableFormatter value ) {
		final String S_ProcName = "setThrowableFormatter";
		if( value == null ) {
			throw new CFLibNullArgumentException( getClass(),
				S_ProcName,
				1,
				"value" );
		}
		throwableFormatter = value;
	}
	
	// Accessors for invoker

	private String response = "";

	public String getResponse() {
		return( response );
	}

	void setResponse( String str ) {
		if( str == null ) {
			response = "";
		}
		else {
			response = str;
		}
	}

	// Server Information

	private CFTipServerInfo serverInfo = null;

	public CFTipServerInfo getServerInfo() {
		return( serverInfo );
	}

	public void setServerInfo( CFTipServerInfo value ) {
		final String S_ProcName = "setServerInfo";
		
		if( value == null ) {
			throw new CFLibNullArgumentException( getClass(),
				S_ProcName,
				1,
				"value" );
		}
		
		serverInfo = value;
	}

	// Encryption Support

	// Session key and accessors
	
	private SecretKey sessionKey = null;

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
				"Session key must be initialized by setEncodedSessionKey()" );
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
				"Session key must be initialized by setEncodedSessionKey()" );
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

	// Client device public key for decrypting password hash
	
	private PublicKey clientPublicKey = null;
	
	public void setEncodedClientPublicKey( byte encoded[] )
	throws NoSuchAlgorithmException,
		NoSuchPaddingException,
		InvalidKeyException,
		InvalidKeySpecException
	{
		X509EncodedKeySpec x509KeySpec = new X509EncodedKeySpec( encoded );
		KeyFactory kf = KeyFactory.getInstance( "RSA" );
		clientPublicKey = kf.generatePublic( x509KeySpec );
	}

	public byte[] decryptWithClientPublicKey( byte value[] )
	throws NoSuchAlgorithmException,
		NoSuchPaddingException,
		InvalidKeyException,
		IllegalBlockSizeException,
		BadPaddingException
	{
		final String S_ProcName = "decryptWithClientPublicKey";

		if( clientPublicKey == null ) {
			throw new CFLibUsageException( getClass(),
				S_ProcName,
				"Client public key must be set by calling setEncodedClientPublicKey() first" );
		}

		Cipher cipher = Cipher.getInstance( "RSA/ECB/PKCS1Padding" );
		if( cipher == null ) {
			throw new CFLibNullArgumentException( getClass(),
				S_ProcName,
				0,
				"cipher" );
		}

		cipher.init( Cipher.DECRYPT_MODE, clientPublicKey );
		
		byte decrypted[] = cipher.doFinal( value );

		return( decrypted );
	}
	
	// Element Handler instances

	private CFTipQueryServerInfoHandler queryServerInfoHandler = null;
	private CFTipAppRequestHandler appRequestHandler = null;
	private CFTipLoginRequestHandler loginRequestHandler = null;
	private CFTipSaxEnvelopeDocHandler saxEnvelopeDocHandler = null;
	private CFTipSaxEnvelopeRootHandler saxEnvelopeRootHandler = null;
	
	// Element Handler Resolver Factories

	protected CFTipQueryServerInfoHandler getQueryServerInfoHandler() {
		if( queryServerInfoHandler == null ) {
			queryServerInfoHandler = new CFTipQueryServerInfoHandler( this );
		}
		return( queryServerInfoHandler );
	}

	protected CFTipAppRequestHandler getAppRequestHandler() {
		if( appRequestHandler == null ) {
			appRequestHandler = new CFTipAppRequestHandler( this );
		}
		return( appRequestHandler );
	}

	protected CFTipLoginRequestHandler getLoginRequestHandler() {
		if( loginRequestHandler == null ) {
			loginRequestHandler = new CFTipLoginRequestHandler( this );
		}
		return( loginRequestHandler );
	}

	protected CFTipSaxEnvelopeDocHandler getSaxEnvelopeDocHandler() {
		if( saxEnvelopeDocHandler == null ) {
			saxEnvelopeDocHandler = new CFTipSaxEnvelopeDocHandler( this );
			saxEnvelopeDocHandler.addElementHandler( "AppRequest", getAppRequestHandler() );
			saxEnvelopeDocHandler.addElementHandler( "LoginRequest", getLoginRequestHandler() );
			saxEnvelopeDocHandler.addElementHandler( "QueryServerInfo", getQueryServerInfoHandler() );
		}
		return( saxEnvelopeDocHandler );
	}

	// Root Element Handler Resolver Factory

	protected CFTipSaxEnvelopeRootHandler getSaxRqstRootHandler() {
		if( saxEnvelopeRootHandler == null ) {
			saxEnvelopeRootHandler = new CFTipSaxEnvelopeRootHandler( this );
			saxEnvelopeRootHandler.addElementHandler( "CFTIPEnvelope", getSaxEnvelopeDocHandler() );
		}
		return( saxEnvelopeRootHandler );
	}

	// Root Element Handler

	/*
	 *	CFTipSaxEnvelopeRootHandler XML SAX Root Element Handler implementation
	 */
	public class CFTipSaxEnvelopeRootHandler
		extends CFLibXmlCoreElementHandler
	{
		public CFTipSaxEnvelopeRootHandler( CFTipEnvelopeHandler xmsgRqstHandler ) {
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
	 *	CFTipSaxEnvelopeDocHandler XML SAX Doc Element Handler implementation
	 */
	public class CFTipSaxEnvelopeDocHandler
		extends CFLibXmlCoreElementHandler
	{
		public CFTipSaxEnvelopeDocHandler( CFTipEnvelopeHandler xmsgRqstHandler ) {
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

	// Parse XML string contents

	public void parseStringContents( String str ) {
		setResponse( "" );
		try {
			super.parseStringContents( str );
		}
		catch( RuntimeException e ) {
			ICFLibMessageLog log = getLog();
			if( log != null ) {
				PrintStream printStream = log.getPrintStream();
				log.message( "Caught " + e.getClass().getName() + " -- " + e.getMessage() );
				e.printStackTrace( printStream );
			}
			else {
				e.printStackTrace();
			}
			setResponse( "" );
		}
		catch( Error e ) {
			ICFLibMessageLog log = getLog();
			if( log != null ) {
				PrintStream printStream = log.getPrintStream();
				log.message( "Caught " + e.getClass().getName() + " -- " + e.getMessage() );
				e.printStackTrace( printStream );
			}
			else {
				e.printStackTrace();
			}
			setResponse( "" );
		}
	}

	// Parse a URL

	public void parse( String url ) {
		setResponse( "" );
		try {
			super.parse( url );
		}
		catch( RuntimeException e ) {
			ICFLibMessageLog log = getLog();
			if( log != null ) {
				PrintStream printStream = log.getPrintStream();
				log.message( "Caught " + e.getClass().getName() + " -- " + e.getMessage() );
				e.printStackTrace( printStream );
			}
			else {
				e.printStackTrace();
			}
			setResponse( "" );
		}
		catch( Error e ) {
			ICFLibMessageLog log = getLog();
			if( log != null ) {
				PrintStream printStream = log.getPrintStream();
				log.message( "Caught " + e.getClass().getName() + " -- " + e.getMessage() );
				e.printStackTrace( printStream );
			}
			else {
				e.printStackTrace();
			}
			setResponse( "" );
		}
	}

	// Parse a file

	public void parseFile( String url ) {
		setResponse( "" );
		try {
			super.parse( url );
		}
		catch( RuntimeException e ) {
			ICFLibMessageLog log = getLog();
			if( log != null ) {
				PrintStream printStream = log.getPrintStream();
				log.message( "Caught " + e.getClass().getName() + " -- " + e.getMessage() );
				e.printStackTrace( printStream );
			}
			else {
				e.printStackTrace();
			}
			setResponse( "" );
		}
		catch( Error e ) {
			ICFLibMessageLog log = getLog();
			if( log != null ) {
				PrintStream printStream = log.getPrintStream();
				log.message( "Caught " + e.getClass().getName() + " -- " + e.getMessage() );
				e.printStackTrace( printStream );
			}
			else {
				e.printStackTrace();
			}
			setResponse( "" );
		}
	}

	/*
	 *	CFTipQueryServerInfoHandler XML SAX Element Handler implementation
	 */
	public class CFTipQueryServerInfoHandler
		extends CFLibXmlCoreElementHandler
	{
		public CFTipQueryServerInfoHandler( CFTipEnvelopeHandler envelopeHandler ) {
			super( envelopeHandler );
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
	
			CFTipEnvelopeHandler envelopeHandler = (CFTipEnvelopeHandler)getParser();
			if( envelopeHandler == null ) {
				throw new CFLibNullArgumentException( getClass(),
					S_ProcName,
					0,
					"getParser()" );
			}
	
			try {
				// Common XML Attributes
				String	attrId = null;
				// Request Attributes
				// Attribute Extraction
				String	attrLocalName;
				int		numAttrs;
				int		idxAttr;
	
				assert qName.equals( "QueryServerInfo" );
	
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
	
				// Prepare the server information response message
	
				CFTipServerInfo serverInfo = envelopeHandler.getServerInfo();
				String clusterURL = serverInfo.getClusterURL();
				String clusterDescr = serverInfo.getClusterDescr();
				String schemaName = serverInfo.getSchemaName();
				String schemaDescr = serverInfo.getSchemaDescr();
				CFTipServerInfo.AltSchema altSchemas[] = serverInfo.getAltSchemas();
				String serverLoginKey = serverInfo.getServerLoginKey();
				int numSchemas = altSchemas.length;
				CFTipServerInfo.AltSchema altSchema;
				String altSchemaName;
				String altSchemaDescr;
	
				StringBuffer buff = new StringBuffer();
				buff.append(
						"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
					+	"<CFTipServerInfo\n"
					+	"\t\txmlns=\"uri://org.msscf.msscf/CFTipServerInfo\"\n"
					+	"\t\txmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n"
					+	"\t\txmlns:xs=\"http://www.w3.org/2001/XMLSchema\"\n"
					+	"\t\txsi:schemaLocation=\"uri://org.msscf.msscf/CFTipServerInfo file:../bin/xsd/cftip-serverinfo.xsd\""
					+	"\t\tClusterURL=\"" + CFLibXmlUtil.formatXmlString( clusterURL ) + "\"\n"
					+	"\t\tClusterDescr=\"" + CFLibXmlUtil.formatXmlString( clusterDescr ) + "\"\n"
					+	"\t\tSchemaName=\"" + CFLibXmlUtil.formatXmlString( schemaName ) + "\"\n"
					+	"\t\tSchemaDescr=\"" + CFLibXmlUtil.formatXmlString( schemaDescr ) + "\"\n"
					+	"\t\tServerLoginKey=\"" + CFLibXmlUtil.formatXmlString( serverLoginKey ) + "\" >\n" );
	
				for( int idx = 0; idx < numSchemas; idx ++ ) {
					altSchema = altSchemas[idx];
					if( altSchema != null ) {
						altSchemaName = altSchema.getSchemaName();
						altSchemaDescr = altSchema.getSchemaDescr();
						buff.append(
								"\t<AltSchema SchemaName=\""
							+		CFLibXmlUtil.formatXmlString( altSchemaName )
							+		"\" SchemaDescr=\""
							+		CFLibXmlUtil.formatXmlString( altSchemaDescr )
							+		"\" />\n" );
					}
				}
	
				buff.append(
						"</CFTipServerInfo>\n" );
	
				envelopeHandler.setResponse( buff.toString() );
			}
			catch( RuntimeException e ) {
				ICFLibMessageLog log = getLog();
				if( log != null ) {
					PrintStream printStream = log.getPrintStream();
					log.message( "Caught " + e.getClass().getName() + " -- " + e.getMessage() );
					e.printStackTrace( printStream );
				}
				else {
					e.printStackTrace();
				}
				envelopeHandler.setResponse( "" );
			}
			catch( Error e ) {
				ICFLibMessageLog log = getLog();
				if( log != null ) {
					PrintStream printStream = log.getPrintStream();
					log.message( "Caught " + e.getClass().getName() + " -- " + e.getMessage() );
					e.printStackTrace( printStream );
				}
				else {
					e.printStackTrace();
				}
				envelopeHandler.setResponse( "" );
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

	/*
	 *	CFTipQueryServerInfoHandler XML SAX Element Handler implementation
	 */
	public class CFTipLoginRequestHandler
		extends CFLibXmlCoreElementHandler
	{
		public CFTipLoginRequestHandler( CFTipEnvelopeHandler envelopeHandler ) {
			super( envelopeHandler );
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
	
			CFTipEnvelopeHandler envelopeHandler = (CFTipEnvelopeHandler)getParser();
			if( envelopeHandler == null ) {
				throw new CFLibNullArgumentException( getClass(),
					S_ProcName,
					0,
					"getParser()" );
			}
	
			ICFTipRequestHandler rqstHandler = envelopeHandler.getRequestHandler();
			if( rqstHandler == null ) {
				throw new CFLibNullArgumentException( getClass(),
					S_ProcName,
					0,
					"getParser().getRequestHandler()" );
			}

			IvParameterSpec ivspec = null;

			try {
				// Common XML Attributes
				String	attrId = null;
				// Request Attributes
				String	attrMessageIV = null;
				String	attrAES256Key = null;
				String	attrPayload = null;
				// Attribute Extraction
				String	attrLocalName;
				int		numAttrs;
				int		idxAttr;
	
				assert qName.equals( "LoginRequest" );
	
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
					else if( attrLocalName.equals( "MessageIV" ) ) {
						if( attrMessageIV != null ) {
							throw new CFLibUniqueIndexViolationException( getClass(),
								S_ProcName,
								S_LocalName,
								attrLocalName );
						}
						attrMessageIV = attrs.getValue( idxAttr );
					}
					else if( attrLocalName.equals( "AES256Key" ) ) {
						if( attrAES256Key != null ) {
							throw new CFLibUniqueIndexViolationException( getClass(),
								S_ProcName,
								S_LocalName,
								attrLocalName );
						}
						attrAES256Key = attrs.getValue( idxAttr );
					}
					else if( attrLocalName.equals( "Payload" ) ) {
						if( attrPayload != null ) {
							throw new CFLibUniqueIndexViolationException( getClass(),
								S_ProcName,
								S_LocalName,
								attrLocalName );
						}
						attrPayload = attrs.getValue( idxAttr );
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
	
				// Verify that the key and payload was provided

				if( ( attrMessageIV == null ) || ( attrMessageIV.length() <= 0 ) ) {
					throw new CFLibNullArgumentException( getClass(),
						S_ProcName,
						0,
						"MessageIV" );
				}

				if( ( attrAES256Key == null ) || ( attrAES256Key.length() <= 0 ) ) {
					throw new CFLibNullArgumentException( getClass(),
						S_ProcName,
						0,
						"AES256Key" );
				}

				if( ( attrPayload == null ) || ( attrPayload.length() <= 0 ) ) {
					throw new CFLibNullArgumentException( getClass(),
						S_ProcName,
						0,
						"Payload" );
				}

				// Unmarshall the IV
				
				byte[] iv = Base64.decodeBase64( attrMessageIV );
				ivspec = new IvParameterSpec( iv );

				// Convert the AES256Key string from Base64 to a byte array
				
				byte[] base64AES256Key = Base64.decodeBase64( attrAES256Key );
				byte[] decryptedAES256Key = serverInfo.decryptWithServerPrivateKey( base64AES256Key );
				envelopeHandler.setEncodedSessionKey( decryptedAES256Key );

				// Convert the payload from Base64 to a byte array
				
				byte payload[] = Base64.decodeBase64( attrPayload );
				
				// Decrypt the payload using the application session private key
				
				byte decrypted[] = envelopeHandler.decryptWithSessionKey( ivspec, payload );

				// The payload's password and client public key are further encrypted by the device key,
				// but that processing is handled by the request parser

				// Process the decrypted payload using the envelope's request handler

				String rqst;
				String rspn;
				try {
					rqst = new String( decrypted );
					rqstHandler.parseStringContents( rqst );
					rspn = rqstHandler.getResponse();
					if( rspn == null ) {
						rspn = "";
					}
				}
				catch( Throwable t ) {
					if( throwableFormatter != null ) {
						rspn = throwableFormatter.formatResponseThrowable( t );
					}
					else {
						rspn = "";
					}
				}

				// Encrypt the response using the session private key to prevent MITM attacks
				
				byte bytes[] = rspn.getBytes();

				byte encrypted[] = envelopeHandler.encryptWithSessionKey( ivspec, bytes );
				
				// Encode the encrypted response as Base64
				
				String rspnString = new String( Base64.encodeBase64( encrypted ) );

				envelopeHandler.setResponse( rspnString );
			}
			catch( RuntimeException e ) {
				ICFLibMessageLog log = getLog();
				if( log != null ) {
					PrintStream printStream = log.getPrintStream();
					log.message( "Caught " + e.getClass().getName() + " -- " + e.getMessage() );
					e.printStackTrace( printStream );
				}
				else {
					e.printStackTrace();
				}

				String rspn;
				if( throwableFormatter != null ) {
					rspn = throwableFormatter.formatResponseThrowable( e );
				}
				else {
					rspn = "";
				}

				// Encrypt the response using the session private key to prevent MITM attacks
			
				byte bytes[] = rspn.getBytes();

				byte encrypted[];
				try {
					encrypted = envelopeHandler.encryptWithSessionKey( ivspec, bytes );
				}
				catch ( InvalidKeyException
					| NoSuchAlgorithmException
					| NoSuchPaddingException
					| IllegalBlockSizeException
					| BadPaddingException
					| InvalidAlgorithmParameterException x )
				{
					encrypted = new byte[0];
				}
			
				// Encode the encrypted response as Base64
			
				String rspnString = new String( Base64.encodeBase64( encrypted ) );

				envelopeHandler.setResponse( rspnString );
			}
			catch( Error e ) {
				ICFLibMessageLog log = getLog();
				if( log != null ) {
					PrintStream printStream = log.getPrintStream();
					log.message( "Caught " + e.getClass().getName() + " -- " + e.getMessage() );
					e.printStackTrace( printStream );
				}
				else {
					e.printStackTrace();
				}

				String rspn;
				if( throwableFormatter != null ) {
					rspn = throwableFormatter.formatResponseThrowable( e );
				}
				else {
					rspn = "";
				}

				// Encrypt the response using the session private key to prevent MITM attacks
			
				byte bytes[] = rspn.getBytes();

				byte encrypted[];
				try {
					encrypted = envelopeHandler.encryptWithSessionKey( ivspec, bytes );
				}
				catch ( InvalidKeyException
					| NoSuchAlgorithmException
					| NoSuchPaddingException
					| IllegalBlockSizeException
					| BadPaddingException
					| InvalidAlgorithmParameterException x )
				{
					encrypted = new byte[0];
				}
			
				// Encode the encrypted response as Base64
			
				String rspnString = new String( Base64.encodeBase64( encrypted ) );

				envelopeHandler.setResponse( rspnString );
			}
			catch( InvalidKeyException e ) {
				ICFLibMessageLog log = getLog();
				if( log != null ) {
					PrintStream printStream = log.getPrintStream();
					log.message( "Caught InvalidKeyException -- " + e.getMessage() );
					e.printStackTrace( printStream );
				}
				else {
					e.printStackTrace();
				}

				String rspn;
				if( throwableFormatter != null ) {
					rspn = throwableFormatter.formatResponseThrowable( e );
				}
				else {
					rspn = "";
				}

				// Encrypt the response using the session private key to prevent MITM attacks
			
				byte bytes[] = rspn.getBytes();

				byte encrypted[];
				try {
					encrypted = envelopeHandler.encryptWithSessionKey( ivspec, bytes );
				}
				catch ( InvalidKeyException
					| NoSuchAlgorithmException
					| NoSuchPaddingException
					| IllegalBlockSizeException
					| BadPaddingException
					| InvalidAlgorithmParameterException x )
				{
					encrypted = new byte[0];
				}
			
				// Encode the encrypted response as Base64
			
				String rspnString = new String( Base64.encodeBase64( encrypted ) );

				envelopeHandler.setResponse( rspnString );
			}
			catch( NoSuchAlgorithmException e ) {
				ICFLibMessageLog log = getLog();
				if( log != null ) {
					PrintStream printStream = log.getPrintStream();
					log.message( "Caught NoSuchAlgorithmException -- " + e.getMessage() );
					e.printStackTrace( printStream );
				}
				else {
					e.printStackTrace();
				}

				String rspn;
				if( throwableFormatter != null ) {
					rspn = throwableFormatter.formatResponseThrowable( e );
				}
				else {
					rspn = "";
				}

				// Encrypt the response using the session private key to prevent MITM attacks
			
				byte bytes[] = rspn.getBytes();

				byte encrypted[];
				try {
					encrypted = envelopeHandler.encryptWithSessionKey( ivspec, bytes );
				}
				catch ( InvalidKeyException
					| NoSuchAlgorithmException
					| NoSuchPaddingException
					| IllegalBlockSizeException
					| BadPaddingException
					| InvalidAlgorithmParameterException x )
				{
					encrypted = new byte[0];
				}
			
				// Encode the encrypted response as Base64
			
				String rspnString = new String( Base64.encodeBase64( encrypted ) );

				envelopeHandler.setResponse( rspnString );
			}
			catch( NoSuchPaddingException e ) {
				ICFLibMessageLog log = getLog();
				if( log != null ) {
					PrintStream printStream = log.getPrintStream();
					log.message( "Caught NoSuchPaddingException -- " + e.getMessage() );
					e.printStackTrace( printStream );
				}
				else {
					e.printStackTrace();
				}
				envelopeHandler.setResponse( "" );
			}
			catch( IllegalBlockSizeException e ) {
				ICFLibMessageLog log = getLog();
				if( log != null ) {
					PrintStream printStream = log.getPrintStream();
					log.message( "Caught IllegalBlockSizeException -- " + e.getMessage() );
					e.printStackTrace( printStream );
				}
				else {
					e.printStackTrace();
				}

				String rspn;
				if( throwableFormatter != null ) {
					rspn = throwableFormatter.formatResponseThrowable( e );
				}
				else {
					rspn = "";
				}

				// Encrypt the response using the session private key to prevent MITM attacks
			
				byte bytes[] = rspn.getBytes();

				byte encrypted[];
				try {
					encrypted = envelopeHandler.encryptWithSessionKey( ivspec, bytes );
				}
				catch ( InvalidKeyException
					| NoSuchAlgorithmException
					| NoSuchPaddingException
					| IllegalBlockSizeException
					| BadPaddingException
					| InvalidAlgorithmParameterException x )
				{
					encrypted = new byte[0];
				}
			
				// Encode the encrypted response as Base64
			
				String rspnString = new String( Base64.encodeBase64( encrypted ) );

				envelopeHandler.setResponse( rspnString );
			}
			catch( BadPaddingException e ) {
				ICFLibMessageLog log = getLog();
				if( log != null ) {
					PrintStream printStream = log.getPrintStream();
					log.message( "Caught BadPaddingException -- " + e.getMessage() );
					e.printStackTrace( printStream );
				}
				else {
					e.printStackTrace();
				}

				String rspn;
				if( throwableFormatter != null ) {
					rspn = throwableFormatter.formatResponseThrowable( e );
				}
				else {
					rspn = "";
				}

				// Encrypt the response using the session private key to prevent MITM attacks
			
				byte bytes[] = rspn.getBytes();

				byte encrypted[];
				try {
					encrypted = envelopeHandler.encryptWithSessionKey( ivspec, bytes );
				}
				catch ( InvalidKeyException
					| NoSuchAlgorithmException
					| NoSuchPaddingException
					| IllegalBlockSizeException
					| BadPaddingException
					| InvalidAlgorithmParameterException x )
				{
					encrypted = new byte[0];
				}
			
				// Encode the encrypted response as Base64
			
				String rspnString = new String( Base64.encodeBase64( encrypted ) );

				envelopeHandler.setResponse( rspnString );
			}
			catch (InvalidAlgorithmParameterException e) {
				ICFLibMessageLog log = getLog();
				if( log != null ) {
					PrintStream printStream = log.getPrintStream();
					log.message( "Caught InvalidAlgorithmParameterException -- " + e.getMessage() );
					e.printStackTrace( printStream );
				}
				else {
					e.printStackTrace();
				}

				String rspn;
				if( throwableFormatter != null ) {
					rspn = throwableFormatter.formatResponseThrowable( e );
				}
				else {
					rspn = "";
				}

				// Encrypt the response using the session private key to prevent MITM attacks
			
				byte bytes[] = rspn.getBytes();

				byte encrypted[];
				try {
					encrypted = envelopeHandler.encryptWithSessionKey( ivspec, bytes );
				}
				catch ( InvalidKeyException
					| NoSuchAlgorithmException
					| NoSuchPaddingException
					| IllegalBlockSizeException
					| BadPaddingException
					| InvalidAlgorithmParameterException x )
				{
					encrypted = new byte[0];
				}
			
				// Encode the encrypted response as Base64
			
				String rspnString = new String( Base64.encodeBase64( encrypted ) );

				envelopeHandler.setResponse( rspnString );
			}
			catch( InvalidKeySpecException e ) {
				ICFLibMessageLog log = getLog();
				if( log != null ) {
					PrintStream printStream = log.getPrintStream();
					log.message( "Caught InvalidKeySpecException -- " + e.getMessage() );
					e.printStackTrace( printStream );
				}
				else {
					e.printStackTrace();
				}

				String rspn;
				if( throwableFormatter != null ) {
					rspn = throwableFormatter.formatResponseThrowable( e );
				}
				else {
					rspn = "";
				}

				// Encrypt the response using the session private key to prevent MITM attacks
			
				byte bytes[] = rspn.getBytes();

				byte encrypted[];
				try {
					encrypted = envelopeHandler.encryptWithSessionKey( ivspec, bytes );
				}
				catch ( InvalidKeyException
					| NoSuchAlgorithmException
					| NoSuchPaddingException
					| IllegalBlockSizeException
					| BadPaddingException
					| InvalidAlgorithmParameterException x )
				{
					encrypted = new byte[0];
				}
			
				// Encode the encrypted response as Base64
			
				String rspnString = new String( Base64.encodeBase64( encrypted ) );

				envelopeHandler.setResponse( rspnString );
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

	/*
	 *	CFTipQueryServerInfoHandler XML SAX Element Handler implementation
	 */
	public class CFTipAppRequestHandler
		extends CFLibXmlCoreElementHandler
	{
		public CFTipAppRequestHandler( CFTipEnvelopeHandler envelopeHandler ) {
			super( envelopeHandler );
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

			CFTipEnvelopeHandler envelopeHandler = (CFTipEnvelopeHandler)getParser();
			if( envelopeHandler == null ) {
				throw new CFLibNullArgumentException( getClass(),
					S_ProcName,
					0,
					"getParser()" );
			}

			ICFTipRequestHandler rqstHandler = envelopeHandler.getRequestHandler();
			if( rqstHandler == null ) {
				throw new CFLibNullArgumentException( getClass(),
					S_ProcName,
					0,
					"getParser().getRequestHandler()" );
			}

			IvParameterSpec ivspec = null;
			
			try {
				// Common XML Attributes
				String	attrId = null;
				// Request Attributes
				String	attrMessageIV = null;
				String	attrPayload = null;
				// Attribute Extraction
				String	attrLocalName;
				int		numAttrs;
				int		idxAttr;

				assert qName.equals( "AppRequest" );

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
					else if( attrLocalName.equals( "MessageIV" ) ) {
						if( attrMessageIV != null ) {
							throw new CFLibUniqueIndexViolationException( getClass(),
								S_ProcName,
								S_LocalName,
								attrLocalName );
						}
						attrMessageIV = attrs.getValue( idxAttr );
					}
					else if( attrLocalName.equals( "Payload" ) ) {
						if( attrPayload != null ) {
							throw new CFLibUniqueIndexViolationException( getClass(),
								S_ProcName,
								S_LocalName,
								attrLocalName );
						}
						attrPayload = attrs.getValue( idxAttr );
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

				// Verify that a payload was provided

				if( ( attrMessageIV == null ) || ( attrMessageIV.length() <= 0 ) ) {
					throw new CFLibNullArgumentException( getClass(),
						S_ProcName,
						0,
						"MessageIV" );
				}
				
				if( ( attrPayload == null ) || ( attrPayload.length() <= 0 ) ) {
					throw new CFLibNullArgumentException( getClass(),
						S_ProcName,
						0,
						"Payload" );
				}

				// Unmarshall the IV
				
				byte[] iv = Base64.decodeBase64( attrMessageIV );
				ivspec = new IvParameterSpec( iv );

				// Convert the payload from Base64 to a byte array
				
				byte payload[] = Base64.decodeBase64( attrPayload );

				// Decrypt the payload using the application session private key
				
				byte decrypted[] = envelopeHandler.decryptWithSessionKey( ivspec, payload );
				
				// Process the decrypted payload using the envelope's request handler

				String rqst;
				String rspn;
				try {
					rqst = new String( decrypted );
					rqstHandler.parseStringContents( rqst );
					rspn = rqstHandler.getResponse();
					if( rspn == null ) {
						rspn = "";
					}
				}
				catch( Throwable t ) {
					if( throwableFormatter != null ) {
						rspn = throwableFormatter.formatResponseThrowable( t );
					}
					else {
						rspn = "";
					}
				}

				// Encrypt the response using the session private key to prevent MITM attacks
				
				byte bytes[] = rspn.getBytes();

				byte encrypted[] = envelopeHandler.encryptWithSessionKey( ivspec, bytes );
				
				// Encode the encrypted response as Base64
				
				String rspnString = new String( Base64.encodeBase64( encrypted ) );

				envelopeHandler.setResponse( rspnString );
			}
			catch( RuntimeException e ) {
				ICFLibMessageLog log = getLog();
				if( log != null ) {
					PrintStream printStream = log.getPrintStream();
					log.message( "Caught " + e.getClass().getName() + " -- " + e.getMessage() );
					e.printStackTrace( printStream );
				}
				else {
					e.printStackTrace();
				}

				String rspn;
				if( throwableFormatter != null ) {
					rspn = throwableFormatter.formatResponseThrowable( e );
				}
				else {
					rspn = "";
				}

				// Encrypt the response using the session private key to prevent MITM attacks
			
				byte bytes[] = rspn.getBytes();

				byte encrypted[];
				try {
					if( ivspec != null ) {
						encrypted = envelopeHandler.encryptWithSessionKey( ivspec, bytes );
					}
					else {
						encrypted = new byte[0];
					}
				}
				catch ( InvalidKeyException
					| NoSuchAlgorithmException
					| NoSuchPaddingException
					| IllegalBlockSizeException
					| BadPaddingException
					| InvalidAlgorithmParameterException x )
				{
					encrypted = new byte[0];
				}
			
				// Encode the encrypted response as Base64
			
				String rspnString = new String( Base64.encodeBase64( encrypted ) );

				envelopeHandler.setResponse( rspnString );
			}
			catch( Error e ) {
				ICFLibMessageLog log = getLog();
				if( log != null ) {
					PrintStream printStream = log.getPrintStream();
					log.message( "Caught " + e.getClass().getName() + " -- " + e.getMessage() );
					e.printStackTrace( printStream );
				}
				else {
					e.printStackTrace();
				}

				String rspn;
				if( throwableFormatter != null ) {
					rspn = throwableFormatter.formatResponseThrowable( e );
				}
				else {
					rspn = "";
				}

				// Encrypt the response using the session private key to prevent MITM attacks
			
				byte bytes[] = rspn.getBytes();

				byte encrypted[];
				try {
					encrypted = envelopeHandler.encryptWithSessionKey( ivspec, bytes );
				}
				catch ( InvalidKeyException
					| NoSuchAlgorithmException
					| NoSuchPaddingException
					| IllegalBlockSizeException
					| BadPaddingException
					| InvalidAlgorithmParameterException x )
				{
					encrypted = new byte[0];
				}
			
				// Encode the encrypted response as Base64
			
				String rspnString = new String( Base64.encodeBase64( encrypted ) );

				envelopeHandler.setResponse( rspnString );
			}
			catch( InvalidKeyException e ) {
				ICFLibMessageLog log = getLog();
				if( log != null ) {
					PrintStream printStream = log.getPrintStream();
					log.message( "Caught InvalidKeyException -- " + e.getMessage() );
					e.printStackTrace( printStream );
				}
				else {
					e.printStackTrace();
				}

				String rspn;
				if( throwableFormatter != null ) {
					rspn = throwableFormatter.formatResponseThrowable( e );
				}
				else {
					rspn = "";
				}

				// Encrypt the response using the session private key to prevent MITM attacks
			
				byte bytes[] = rspn.getBytes();

				byte encrypted[];
				try {
					encrypted = envelopeHandler.encryptWithSessionKey( ivspec, bytes );
				}
				catch ( InvalidKeyException
					| NoSuchAlgorithmException
					| NoSuchPaddingException
					| IllegalBlockSizeException
					| BadPaddingException
					| InvalidAlgorithmParameterException x )
				{
					encrypted = new byte[0];
				}
			
				// Encode the encrypted response as Base64
			
				String rspnString = new String( Base64.encodeBase64( encrypted ) );

				envelopeHandler.setResponse( rspnString );
			}
			catch( NoSuchAlgorithmException e ) {
				ICFLibMessageLog log = getLog();
				if( log != null ) {
					PrintStream printStream = log.getPrintStream();
					log.message( "Caught NoSuchAlgorithmException -- " + e.getMessage() );
					e.printStackTrace( printStream );
				}
				else {
					e.printStackTrace();
				}

				String rspn;
				if( throwableFormatter != null ) {
					rspn = throwableFormatter.formatResponseThrowable( e );
				}
				else {
					rspn = "";
				}

				// Encrypt the response using the session private key to prevent MITM attacks
			
				byte bytes[] = rspn.getBytes();

				byte encrypted[];
				try {
					encrypted = envelopeHandler.encryptWithSessionKey( ivspec, bytes );
				}
				catch ( InvalidKeyException
					| NoSuchAlgorithmException
					| NoSuchPaddingException
					| IllegalBlockSizeException
					| BadPaddingException
					| InvalidAlgorithmParameterException x )
				{
					encrypted = new byte[0];
				}
			
				// Encode the encrypted response as Base64
			
				String rspnString = new String( Base64.encodeBase64( encrypted ) );

				envelopeHandler.setResponse( rspnString );
			}
			catch( NoSuchPaddingException e ) {
				ICFLibMessageLog log = getLog();
				if( log != null ) {
					PrintStream printStream = log.getPrintStream();
					log.message( "Caught NoSuchPaddingException -- " + e.getMessage() );
					e.printStackTrace( printStream );
				}
				else {
					e.printStackTrace();
				}
				envelopeHandler.setResponse( "" );
			}
			catch( IllegalBlockSizeException e ) {
				ICFLibMessageLog log = getLog();
				if( log != null ) {
					PrintStream printStream = log.getPrintStream();
					log.message( "Caught IllegalBlockSizeException -- " + e.getMessage() );
					e.printStackTrace( printStream );
				}
				else {
					e.printStackTrace();
				}

				String rspn;
				if( throwableFormatter != null ) {
					rspn = throwableFormatter.formatResponseThrowable( e );
				}
				else {
					rspn = "";
				}

				// Encrypt the response using the session private key to prevent MITM attacks
			
				byte bytes[] = rspn.getBytes();

				byte encrypted[];
				try {
					encrypted = envelopeHandler.encryptWithSessionKey( ivspec, bytes );
				}
				catch ( InvalidKeyException
					| NoSuchAlgorithmException
					| NoSuchPaddingException
					| IllegalBlockSizeException
					| BadPaddingException
					| InvalidAlgorithmParameterException x )
				{
					encrypted = new byte[0];
				}
			
				// Encode the encrypted response as Base64
			
				String rspnString = new String( Base64.encodeBase64( encrypted ) );

				envelopeHandler.setResponse( rspnString );
			}
			catch( BadPaddingException e ) {
				ICFLibMessageLog log = getLog();
				if( log != null ) {
					PrintStream printStream = log.getPrintStream();
					log.message( "Caught BadPaddingException -- " + e.getMessage() );
					e.printStackTrace( printStream );
				}
				else {
					e.printStackTrace();
				}

				String rspn;
				if( throwableFormatter != null ) {
					rspn = throwableFormatter.formatResponseThrowable( e );
				}
				else {
					rspn = "";
				}

				// Encrypt the response using the session private key to prevent MITM attacks
			
				byte bytes[] = rspn.getBytes();

				byte encrypted[];
				try {
					encrypted = envelopeHandler.encryptWithSessionKey( ivspec, bytes );
				}
				catch ( InvalidKeyException
					| NoSuchAlgorithmException
					| NoSuchPaddingException
					| IllegalBlockSizeException
					| BadPaddingException
					| InvalidAlgorithmParameterException x )
				{
					encrypted = new byte[0];
				}
			
				// Encode the encrypted response as Base64
			
				String rspnString = new String( Base64.encodeBase64( encrypted ) );

				envelopeHandler.setResponse( rspnString );
			}
			catch (InvalidAlgorithmParameterException e) {
				ICFLibMessageLog log = getLog();
				if( log != null ) {
					PrintStream printStream = log.getPrintStream();
					log.message( "Caught InvalidAlgorithmParameterException -- " + e.getMessage() );
					e.printStackTrace( printStream );
				}
				else {
					e.printStackTrace();
				}

				String rspn;
				if( throwableFormatter != null ) {
					rspn = throwableFormatter.formatResponseThrowable( e );
				}
				else {
					rspn = "";
				}

				// Encrypt the response using the session private key to prevent MITM attacks
			
				byte bytes[] = rspn.getBytes();

				byte encrypted[];
				try {
					encrypted = envelopeHandler.encryptWithSessionKey( ivspec, bytes );
				}
				catch ( InvalidKeyException
					| NoSuchAlgorithmException
					| NoSuchPaddingException
					| IllegalBlockSizeException
					| BadPaddingException
					| InvalidAlgorithmParameterException x )
				{
					encrypted = new byte[0];
				}
			
				// Encode the encrypted response as Base64
			
				String rspnString = new String( Base64.encodeBase64( encrypted ) );

				envelopeHandler.setResponse( rspnString );
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
}
