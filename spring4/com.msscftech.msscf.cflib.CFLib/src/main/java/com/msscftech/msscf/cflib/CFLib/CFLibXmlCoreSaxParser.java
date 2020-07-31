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

package com.msscftech.msscf.cflib.CFLib;

import java.io.FileNotFoundException;
import java.io.InputStream;
import java.io.ByteArrayInputStream;

import javax.xml.XMLConstants;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.SAXNotSupportedException;

import org.apache.xerces.parsers.XIncludeAwareParserConfiguration;
import org.apache.xerces.parsers.XMLGrammarPreparser;
import org.apache.xerces.xni.parser.XMLParserConfiguration;
import org.xml.sax.SAXException;
import org.xml.sax.SAXNotRecognizedException;
import org.xml.sax.SAXParseException;
import org.xml.sax.XMLReader;

/**
 *	An XmlCoreSaxParser is an abstract Xerces-J DefaultHandler
 *	specialized for SAX2 parsing. 
 *
 *	Based on Xerces-J 2.8.0 "ParserAPIUsage.java" sample
 *	code published under Apache License 2.0.
 *
 *	@see	http://xerces.apache.org/
 */
public abstract class CFLibXmlCoreSaxParser extends CFLibXmlCoreParser {

//	Instance Attributes

	/**
	 *	The SAX Parser for a SAX2 parser.
	 */
	protected SAXParser saxParser = null;

//	Constructors

	/**
	 *	Construct a default parser.
	 */
	public CFLibXmlCoreSaxParser() {
		super();
	}

	/**
	 *	Construct a default XmlCoreParser logging to the
	 *	specified Log4J Logger.
	 *
	 *	@param	jLogger - Log4J Logger
	 */
	public CFLibXmlCoreSaxParser( ICFLibMessageLog jLogger ) {
		super( jLogger );
	}

//	Accessors: API

	/**
	 *	Get the API implemented.
	 */
	public String getAPI() {
		return( API_SAX );
	}
	
	/**
	 *	Initialize the parser.
	 *	<p>
	 *	Initialization pre-loads the XSD for documents accepted
	 *	by the parser.
	 */
	protected void initParser() {
		super.initParser();
		final String S_ProcName = "initParser";

        try {
        	assert saxParser == null : "saxParser already exists";

        	SAXParserFactory spf = SAXParserFactory.newInstance();
			spf.setNamespaceAware( true );
			spf.setXIncludeAware( false );
			//spf.setSchema( schema );
			spf.setValidating( true );
			spf.setFeature( XMLConstants.FEATURE_SECURE_PROCESSING, false );
    		spf.setFeature( "http://xml.org/sax/features/validation", true );
    		spf.setFeature( "http://apache.org/xml/features/validation/schema", true );
    		spf.setFeature( "http://apache.org/xml/features/validation/schema/normalized-value", true );
			
			// Create a SAXParser
			SAXParser sp = spf.newSAXParser();
	    	sp.setProperty( "http://java.sun.com/xml/jaxp/properties/schemaLanguage",
	    		"http://www.w3.org/2001/XMLSchema" );
	    	sp.setProperty( "http://apache.org/xml/properties/internal/grammar-pool", getGrammarPool() );
			
	    	XMLReader reader = sp.getXMLReader();
    		reader.setFeature( "http://xml.org/sax/features/validation", true );
    		reader.setFeature( "http://apache.org/xml/features/validation/schema", true );
    		reader.setFeature( "http://apache.org/xml/features/validation/schema/normalized-value", true );
	    	reader.setProperty( "http://apache.org/xml/properties/internal/grammar-pool", getGrammarPool() );

	    	saxParser = sp;
        }
        catch (SAXParseException e) {
            // ignore
        }
        catch (SAXException e) {
        	Exception nested;
    		nested = e.getException();
    		if( nested == null ) {
    			nested = e;
    		}
    		if( getLog() != null ) {
    			getLog().message( "CFLibXmlCoreSaxParser.initParser() Ignored exception " + getFormattedNearLocation() + nested.getClass().getName() + " " + nested.getMessage() + "\n" );
    		}
    		else {
    			System.err.append( "CFLibXmlCoreSaxParser.initParser() Ignored exception " + getFormattedNearLocation() + nested.getClass().getName() + " " + nested.getMessage() + "\n" );
    		}
        }
        catch (Exception e) {
        	if( getLog() != null ) {
        		getLog().message( "CFLibXmlCoreSaxParser.initParser() Ignored exception " + getFormattedNearLocation() + e.getClass().getName() + " " + e.getMessage() + "\n" );
        	}
        	else {
	    		System.err.append( "CFLibXmlCoreSaxParser.initParser() Ignored exception " + getFormattedNearLocation() + e.getClass().getName() + " " + e.getMessage() + "\n" );
	    	}
        }
    }

	/**
	 *	Parse the specified URI
	 *
	 *	@param	uri - The URI for the document to parse.
	 */
	protected void parse( String uri ) {
		assert ( uri != null ) && ( uri.length() > 0 ) : "uri (parm 1) is null or empty";
		assert saxParser != null : "Parser must be initialized first";

        try {
    		saxParser.reset();
    		saxParser.parse( uri, this );
        }
        catch (SAXParseException e) {
            // ignore
        }
        catch (SAXException e) {
        	Exception nested;
    		nested = e.getException();
    		if( nested == null ) {
    			nested = e;
    		}
    		if( getLog() != null ) {
    			getLog().message( "CFLibXmlCoreSaxParser.parse() Ignored exception " + getFormattedNearLocation() + nested.getClass().getName() + " " + nested.getMessage() + "\n" );
    		}
    		else {
    			System.err.append( "ERROR: CFLibXmlCoreSaxParser.parse() Ignored exception " + getFormattedNearLocation() + nested.getClass().getName() + " " + nested.getMessage() + "\n" );
    		}
        }
		catch( FileNotFoundException e ) {
			if( getLog() != null ) {
				getLog().message( "CFLibXmlCoreSaxParser.parse() Could not find file \"" + uri + "\"\n" );
			}
			else {
				System.err.append( "ERROR: CFLibXmlCoreSaxParser.parse() Could not find file \"" + uri + "\"\n" );
			}
		}
		catch (Exception e) {
			if( getLog() != null ) {
				getLog().message( "CFLibXmlCoreSaxParser.parser() Ignored exception " + getFormattedNearLocation() + e.getClass().getName() + " " + e.getMessage() + "\n" );
			}
			else {
				System.err.append( "ERROR: CFLibXmlCoreSaxParser.parser() Ignored exception " + getFormattedNearLocation() + e.getClass().getName() + " " + e.getMessage() + "\n" );
			}
		}
	}

	/**
	 *	Parse the specified string contents.
	 *	<p>
	 *	The string passed to this method is typically
	 *	a request or response XML document to be processed
	 *	by an appropriate parser and applied to a storage
	 *	server layer.
	 *
	 *	@param	str The string contents to be parsed.
	 */
	public void parseStringContents( String str ) {
		final String S_ProcName = "parseStringContents";
		if( str == null ) {
			throw new CFLibNullArgumentException( getClass(),
				S_ProcName,
				1,
				"str" );
		}
		byte bytes[] = str.getBytes();
		InputStream instream = new ByteArrayInputStream( bytes );
		parse( instream );
	}
	
	/**
	 *	Parse the specified Stream
	 *
	 *	@param	input - The InputStream for the document to parse.
	 */
	protected void parse( InputStream inputStream ) {
		assert inputStream != null : "inputStream (arg 1) is null";
		assert saxParser != null : "Parser must be initialized first";

        try {
    		saxParser.reset();
    		saxParser.parse( inputStream, this );
        }
        catch (SAXParseException e) {
        	Exception nested;
    		nested = e.getException();
    		if( nested == null ) {
    			nested = e;
    		}
    		if( getLog() != null ) {
    			getLog().message( "CFLibXmlCoreSaxParser.parse() Ignored SAXParseException exception " + nested.getClass().getName() + " " + nested.getMessage() + "\n" );
    		}
    		else {
    			System.err.append( "ERROR: CFLibXmlCoreSaxParser.parse() Ignored SAXParseException exception " + nested.getClass().getName() + " " + nested.getMessage() + "\n" );
    		}
        }
        catch (SAXException e) {
        	Exception nested;
    		nested = e.getException();
    		if( nested == null ) {
    			nested = e;
    		}
    		if( getLog() != null ) {
    			getLog().message( "CFLibXmlCoreSaxParser.parse() Ignored exception " + getFormattedNearLocation() + nested.getClass().getName() + " " + nested.getMessage() + "\n" );
    		}
    		else {
    			System.err.append( "ERROR: CFLibXmlCoreSaxParser.parse() Ignored exception " + getFormattedNearLocation() + nested.getClass().getName() + " " + nested.getMessage() + "\n" );
    		}
        }
		catch (Exception e) {
			if( getLog() != null ) {
				getLog().message( "CFLibXmlCoreSaxParser.parser() Ignored exception " + getFormattedNearLocation() + e.getClass().getName() + " " + e.getMessage() + "\n" );
			}
			else {
				System.err.append( "ERROR: CFLibXmlCoreSaxParser.parser() Ignored exception " + getFormattedNearLocation() + e.getClass().getName() + " " + e.getMessage() + "\n" );
			}
		}
	}
}
