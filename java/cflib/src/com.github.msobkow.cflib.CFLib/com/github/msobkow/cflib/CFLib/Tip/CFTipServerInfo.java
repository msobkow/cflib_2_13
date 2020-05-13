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

package com.github.msobkow.cflib.CFLib.Tip;

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

import org.apache.commons.codec.binary.Base64;

import com.github.msobkow.cflib.CFLib.*;

public class CFTipServerInfo {

	// Constructors

	public CFTipServerInfo() {
	}

	// Server Information

	public final static int CLUSTER_L_URL = 192;
	public final static int CLUSTER_L_DESCR = 128;
	public final static int SCHEMA_L_NAME = 32;
	public final static int SCHEMA_L_DESCR = 1023;
	public final static int PUBLIC_L_KEY = 8000;

	public class AltSchema {
		private String schemaName = "callSetSchemaName()";
		private String schemaDescr = "callSetSchemaDescr()";

		public AltSchema() {
		}

		public AltSchema( String parmName, String parmDescr ) {
			schemaName = parmName;
			schemaDescr = parmDescr;
		}

		public String getSchemaName() {
			return( schemaName );
		}

		void setSchemaName( String value ) {
			final String S_ProcName = "setSchemaName";
			if( ( value == null ) || ( value.length() <= 0 ) ) {
				throw new CFLibNullArgumentException( getClass(),
					S_ProcName,
					1,
					"value" );
			}
			if( value.length() > SCHEMA_L_NAME ) {
				throw new CFLibArgumentOverflowException( getClass(),
					S_ProcName,
					1,
					"value.length()",
					value.length(),
					SCHEMA_L_NAME );
			}
			schemaName = value;
		}

		public String getSchemaDescr() {
			return( schemaDescr );
		}

		void setSchemaDescr( String value ) {
			final String S_ProcName = "setSchemaDescr";
			if( ( value == null ) || ( value.length() <= 0 ) ) {
				throw new CFLibNullArgumentException( getClass(),
					S_ProcName,
					1,
					"value" );
			}
			if( value.length() > SCHEMA_L_DESCR ) {
				throw new CFLibArgumentOverflowException( getClass(),
					S_ProcName,
					1,
					"value.length()",
					value.length(),
					SCHEMA_L_DESCR );
			}
			schemaDescr = value;
		}
	}

	private String clusterURL = null;
	private String clusterDescr = null;
	private String schemaName = null;
	private String schemaDescr = null;
	private AltSchema altSchemas[] = new AltSchema[0];
	private String serverLoginKey = null;

	public String getClusterURL() {
		return( clusterURL );
	}

	public void setClusterURL( String value ) {
		final String S_ProcName = "setClusterURL";
		if( ( value == null ) || ( value.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( getClass(),
				S_ProcName,
				1,
				"value" );
		}
		if( value.length() > CLUSTER_L_URL ) {
			throw new CFLibArgumentOverflowException( getClass(),
				S_ProcName,
				1,
				"value.length()",
				value.length(),
				CLUSTER_L_URL );
		}
		clusterURL = value;
	}

	public String getClusterDescr() {
		return( clusterDescr );
	}

	public void setClusterDescr( String value ) {
		final String S_ProcName = "setClusterDescr";
		if( ( value == null ) || ( value.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( getClass(),
				S_ProcName,
				1,
				"value" );
		}
		if( value.length() > CLUSTER_L_DESCR ) {
			throw new CFLibArgumentOverflowException( getClass(),
				S_ProcName,
				1,
				"value.length()",
				value.length(),
				CLUSTER_L_DESCR );
		}
		clusterDescr = value;
	}

	public String getSchemaName() {
		return( schemaName );
	}

	public void setSchemaName( String value ) {
		final String S_ProcName = "setSchemaName";
		if( ( value == null ) || ( value.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( getClass(),
				S_ProcName,
				1,
				"value" );
		}
		if( value.length() > SCHEMA_L_NAME ) {
			throw new CFLibArgumentOverflowException( getClass(),
				S_ProcName,
				1,
				"value.length()",
				value.length(),
				SCHEMA_L_NAME );
		}
		schemaName = value;
	}

	public String getSchemaDescr() {
		return( schemaDescr );
	}

	public void setSchemaDescr( String value ) {
		final String S_ProcName = "setSchemaDescr";
		if( ( value == null ) || ( value.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( getClass(),
				S_ProcName,
				1,
				"value" );
		}
		if( value.length() > SCHEMA_L_DESCR ) {
			throw new CFLibArgumentOverflowException( getClass(),
				S_ProcName,
				1,
				"value.length()",
				value.length(),
				SCHEMA_L_DESCR );
		}
		schemaDescr = value;
	}

	public AltSchema[] getAltSchemas() {
		return( altSchemas );
	}

	public void addAltSchema( String schemaName, String schemaDescr ) {	
		AltSchema altSchema = new AltSchema();
		altSchema.setSchemaName( schemaName );
		altSchema.setSchemaDescr( schemaDescr );
		
		AltSchema oldAltSchemas[] = altSchemas;
		AltSchema newAltSchemas[] = new AltSchema[ oldAltSchemas.length + 1 ];
		for( int idx = 0; idx < oldAltSchemas.length; idx ++ ) {
			newAltSchemas[idx] = oldAltSchemas[idx];
		}
		newAltSchemas[ oldAltSchemas.length ] = altSchema;
		
		altSchemas = newAltSchemas;
	}

	public String getServerLoginKey() {
		return( serverLoginKey );
	}

	public void setServerLoginKey( String serverEncodedKey ) {
		final String S_ProcName = "setServerLoginKey";
		try {
			byte[] decoded = Base64.decodeBase64( serverEncodedKey.getBytes() );
			setEncodedServerPublicKey( decoded );
		}
		catch( InvalidKeyException
			| NoSuchAlgorithmException
			| NoSuchPaddingException
			| InvalidKeySpecException e )
		{
			throw new CFLibRuntimeException( getClass(),
				S_ProcName,
				"Caught " + e.getClass().getName() + " -- " + e.getMessage(),
				e );
		}
		serverLoginKey = serverEncodedKey;
	}

	private PublicKey serverPublicKey = null;
	private PrivateKey serverPrivateKey = null;
	
	public PublicKey getServerPublicKey() {
		return( serverPublicKey );
	}
	
	public void setEncodedServerPublicKey( byte encoded[] )
	throws NoSuchAlgorithmException,
		NoSuchPaddingException,
		InvalidKeyException,
		InvalidKeySpecException
	{
		X509EncodedKeySpec x509KeySpec = new X509EncodedKeySpec( encoded );
		KeyFactory kf = KeyFactory.getInstance( "RSA" );
		serverPublicKey = kf.generatePublic( x509KeySpec );
	}

	public byte[] encryptWithServerPublicKey( byte value[] )
	throws InvalidKeyException,
		NoSuchAlgorithmException,
		NoSuchPaddingException,
		IllegalBlockSizeException,
		BadPaddingException
	{
		final String S_ProcName = "encryptWithServerPublicKey";
		
		if( serverPublicKey == null ) {
			throw new CFLibUsageException( getClass(),
				S_ProcName,
				"Server public key must be set first" );
		}

		Cipher cipher = Cipher.getInstance( "RSA/ECB/PKCS1Padding" );
		if( cipher == null ) {
			throw new CFLibNullArgumentException( getClass(),
				S_ProcName,
				0,
				"cipher" );
		}

		cipher.init( Cipher.ENCRYPT_MODE, serverPublicKey );

		byte encrypted[] = cipher.doFinal( value );

		return( encrypted );
	}

	public byte[] decryptWithServerPublicKey( byte value[] )
	throws NoSuchAlgorithmException,
		NoSuchPaddingException,
		InvalidKeyException,
		IllegalBlockSizeException,
		BadPaddingException
	{
		final String S_ProcName = "decryptWithServerPublicKey";

		if( serverPublicKey == null ) {
			throw new CFLibUsageException( getClass(),
				S_ProcName,
				"Server key must be initialized by setEncodedServerPublicKey()" );
		}

		Cipher cipher = Cipher.getInstance( "RSA/ECB/PKCS1Padding" );
		if( cipher == null ) {
			throw new CFLibNullArgumentException( getClass(),
				S_ProcName,
				0,
				"cipher" );
		}

		cipher.init( Cipher.DECRYPT_MODE, serverPublicKey );
		
		byte decrypted[] = cipher.doFinal( value );

		return( decrypted );
	}

	public void setServerKeys( PublicKey publicKey, PrivateKey privateKey )
	throws InvalidKeyException,
		NoSuchAlgorithmException,
		NoSuchPaddingException,
		IllegalBlockSizeException
	{
		final String S_ProcName = "setServerKeys";
		if( publicKey == null ) {
			throw new CFLibNullArgumentException( getClass(),
				S_ProcName,
				1,
				"publicKey" );
		}
		if( privateKey == null ) {
			throw new CFLibNullArgumentException( getClass(),
				S_ProcName,
				1,
				"privateKey" );
		}

		serverPrivateKey = privateKey;
		serverPublicKey = publicKey;
		
		byte encodedPKey[] = getEncodedServerPublicKey();
		String encoded = new String( Base64.encodeBase64( encodedPKey ) );
		serverLoginKey = encoded;
	}
	
	public void initServerKeys()
	throws NoSuchAlgorithmException,
		InvalidKeyException,
		NoSuchPaddingException,
		IllegalBlockSizeException
	{
		if( serverPrivateKey == null ) {
			KeyPairGenerator kpg = KeyPairGenerator.getInstance( "RSA" );
			kpg.initialize( 2048, new SecureRandom() );
			KeyPair serverKeyPair = kpg.generateKeyPair();
			serverPrivateKey = serverKeyPair.getPrivate();
			serverPublicKey = serverKeyPair.getPublic();
		}
		
		byte encodedPKey[] = getEncodedServerPublicKey();
		String encoded = new String( Base64.encodeBase64( encodedPKey ) );
		serverLoginKey = encoded;
	}
	
	public byte[] getEncodedServerPublicKey()
	throws NoSuchAlgorithmException,
		NoSuchPaddingException,
		InvalidKeyException,
		IllegalBlockSizeException
	{
		final String S_ProcName = "getEncodedServerPublicKey";

		if( serverPublicKey == null ) {
			throw new CFLibNullArgumentException( getClass(),
				S_ProcName,
				0,
				"serverPublicKey" );
		}

		byte encoded[] = serverPublicKey.getEncoded();
		
		return( encoded );
	}

	public byte[] decryptWithServerPrivateKey( byte value[] )
	throws NoSuchAlgorithmException,
		NoSuchPaddingException,
		InvalidKeyException,
		IllegalBlockSizeException,
		BadPaddingException
	{
		final String S_ProcName = "decryptWithServerPrivateKey";
		
		if( serverPrivateKey == null ) {
			throw new CFLibUsageException( getClass(),
				S_ProcName,
				"Server keys must be initialized by initServerKeys() or setServerKeys()" );
		}

		Cipher cipher = Cipher.getInstance( "RSA/ECB/PKCS1Padding" );
		if( cipher == null ) {
			throw new CFLibNullArgumentException( getClass(),
				S_ProcName,
				0,
				"cipher" );
		}

		cipher.init( Cipher.DECRYPT_MODE, serverPrivateKey );
		
		byte decrypted[] = cipher.doFinal( value );

		return( decrypted );
	}
}
