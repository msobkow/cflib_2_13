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

package org.msscf.msscf.cflib.v2_13.CFLib;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.net.URI;
import java.nio.file.FileSystemNotFoundException;
import java.nio.file.Paths;
import java.util.*;

import javax.xml.XMLConstants;
import javax.xml.transform.stream.StreamSource;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;

import org.apache.xerces.parsers.XMLGrammarPreparser;
import org.apache.xerces.util.XMLGrammarPoolImpl;
import org.apache.xerces.xni.grammars.Grammar;
import org.apache.xerces.xni.grammars.XMLGrammarDescription;
import org.apache.xerces.xni.grammars.XMLGrammarPool;
import org.apache.xerces.xni.parser.XMLInputSource;
import org.xml.sax.Attributes;
import org.xml.sax.Locator;
import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException;
import org.xml.sax.helpers.DefaultHandler;

/**
 *	An OmxParser is an abstract Xerces-J DefaultHandler.
 *
 *	This class defines constants which are used by most SAX2 parser
 *	implementations.
 *
 *	Based on Xerces-J 2.8.0 "ParserAPIUsage.java" sample
 *	code published under Apache License 2.0.
 *
 *	@see	http://xerces.apache.org/
 */
public abstract class CFLibXmlCoreParser
extends DefaultHandler
implements CFLibXmlCoreContextFactory
{

//	Constants

	/**
	 *	Constant for requesting the SAX2 parser API.
	 */
	public final static String	API_SAX = "sax";

	/**
	 *	Constant for requesting the DOM parser API.
	 */
	public final static String	API_DOM = "dom";

	/**
	 *	The default is to disable XInclude processing.
	 */
	public final static boolean	DEFAULT_XINCLUDE = false;

	/**
	 *	The default is to disable secure processing.
	 *	<p>
	 *	MSS WORKING -- This is likely to change.
	 */
	public final static boolean	DEFAULT_SECURE_PROCESSING = false;

//	Instance Attributes

	/**
	 *	Is XInclude processing enabled?
	 */
	private boolean	xIncludeAware = DEFAULT_XINCLUDE;

	/**
	 *	Is secure processing enabled?
	 */
	private boolean secureProcessingEnabled = DEFAULT_SECURE_PROCESSING;

	private ICFLibMessageLog log = null;

	/**
	 *	The current document locator of the parse.
	 */
	private Locator documentLocator = null;

	/**
	 *	The root element handler for processing schema documents.
	 */
	private CFLibXmlCoreElementHandler rootElementHandler = null;

	/**
	 *	The processing of startDocument, endDocument,
	 *	startElement, and stopElement events maintains
	 *	the processing context stack of the parser.
	 */
	private volatile LinkedList<CFLibXmlCoreContext> contextStack = new LinkedList<CFLibXmlCoreContext>();

	/**
	 *	The Context factory to use.
	 *	<p>
	 *	If no context factory is ever specified, the default "this"
	 *	factory is used.
	 */
	private CFLibXmlCoreContextFactory xmlCoreContextFactory = null;

	private static XMLGrammarPoolImpl grammarPool = new XMLGrammarPoolImpl();
	
	public static XMLGrammarPool getGrammarPool() {
		return( grammarPool );
	}

	public static Grammar addToGrammarPool( String name, InputStream input ) {
		assert grammarPool != null;
		
		XMLGrammarPreparser preparser = new XMLGrammarPreparser();
		preparser.setGrammarPool( grammarPool );
		preparser.registerPreparser( XMLGrammarDescription.XML_SCHEMA, null );
		Grammar grammar;
        XMLInputSource inputSource = new XMLInputSource( "parseGrammar", name, name, input, "UTF-8" );
        try {
        	grammar = preparser.preparseGrammar( XMLGrammarDescription.XML_SCHEMA, inputSource );
        }
        catch( IOException e ) {
        	grammar = null;
        }
        try {
        	input.close();
        }
        catch( IOException e ) {
        }
        if( grammar != null ) {
        	Grammar existingGrammar = grammarPool.retrieveGrammar( grammar.getGrammarDescription() );
        	if( existingGrammar != null ) {
        		grammar = existingGrammar;
        	}
        	else {
        		grammarPool.putGrammar( grammar );
        	}
        }
		
		return( grammar );
	}

//	Constructors

	/**
	 *	Construct a default parser.
	 */
	public CFLibXmlCoreParser() {
		this.
		log = null;
	}

	/**
	 *	Construct a default XmlCoreParser logging to the
	 *	specified Log4J log.
	 *
	 *	@param	jlog - Log4J log
	 */
	public CFLibXmlCoreParser( ICFLibMessageLog jlog ) {
		assert jlog != null
			: "jlog (arg 1) is null";
		log = jlog;
	}

//	Accessors: API

	/**
	 *	Get the API implemented.
	 */
	public abstract String getAPI();

//	Accessors: XIncludeAware

	/**
	 *	Is XInclude processing enabled?
	 *
	 *	@return	True if XInclude processing is enabled. 
	 */
	public boolean isXIncludeAware() {
		return( xIncludeAware );
	}
	
	/**
	 *	Specify whether to enable or disable XInclude processing.
	 *
	 *	@param	flag - True to enable, false to disable
	 */
	public void setXIncludeAware( boolean flag ) {
		xIncludeAware = flag;
	}

//	Accessors: SecureProcessingEnabled

	/**
	 *	Is secure processing enabled?
	 *
	 *	@return	True if secure processing is enabled. 
	 */
	public boolean isSecureProcessingEnabled() {
		return( secureProcessingEnabled );
	}
	
	/**
	 *	Specify whether to enable or disable secure processing.
	 *
	 *	@param	flag - True to enable, false to disable
	 */
	public void setSecureProcessingEnabled( boolean flag ) {
		secureProcessingEnabled = flag;
	}

//	Accessors: log

	/**
	 *	Get the Log4J log to receive this parser's messages.
	 *
	 *	@return	The Log4J log 
	 */
	public ICFLibMessageLog getLog() {
		return( log );
	}
	
	/**
	 *	Set the Log4J log to receive this parser's messages.
	 *
	 *	@param	jlog - The log to use
	 */
	public void setLog( ICFLibMessageLog jlog ) {
		assert jlog != null
			: "jlog (arg 1) is null";
		log = jlog;
	}

//	Accessors: RootElementHandler
	
	/**
	 *	Get the element handler for processing the document root.
	 *
	 *	@return	The root element handler
	 */
	public CFLibXmlCoreElementHandler getRootElementHandler() {
		return( rootElementHandler );
	}
	
	/**
	 *	Set the element handler for processing the document root.
	 *
	 *	@param	handler	The root element handler to use.
	 */
	protected void setRootElementHandler( CFLibXmlCoreElementHandler handler ) {
		assert handler != null : "handler (arg 1) is null";
		rootElementHandler = handler;
	}

//	Accessors: DocLocator

	/**
	 *	Get the current document locator.
	 *	<p>
	 *	Note that the document locator is only valid during SAX event
	 *	processing.
	 *
	 *	@return	The current document locator if any.
	 */
	public Locator getDocumentLocator() {
		return( documentLocator );
	}

	public String getLocationInfo() {
		Locator locator = getDocumentLocator();
		StringBuffer buff = new StringBuffer();
		if( locator != null ) {
	
			String shortName = null;
			String docName = locator.getSystemId();
			if( docName != null ) {
				int lastSlash = docName.lastIndexOf( '/' );
				if( ( lastSlash >= 0 ) && ( lastSlash != docName.length() ) ) {
					shortName = new String( docName.substring( lastSlash + 1 ) );
				}
			}
			
			if( shortName == null ) {
				docName = locator.getPublicId();
				if( docName != null ) {
					int lastSlash = docName.lastIndexOf( '/' );
					if( ( lastSlash >= 0 ) && ( lastSlash != docName.length() ) ) {
						shortName = new String( docName.substring( lastSlash + 1 ) );
					}
				}
			}
			
			if( shortName != null ) {
				buff.append( shortName );
			}
			
			int line = locator.getLineNumber();
			if( line >= 0 ) {
				buff.append( "[" + line );
				int col = locator.getColumnNumber();
				if( col >= 0 ) {
					buff.append( "," + col );
				}
				buff.append( "]" );
			}
			buff.append( " " );
		}
		return( buff.toString() );
	}

//	Accessors: CurContext

	/**
	 *	Get the top element handler on the stack, used to locate the
	 *	handler for a sub-element.
	 *
	 *	@return	The top element handler on the stack.
	 */
	public CFLibXmlCoreContext getCurContext() {
		if( contextStack.isEmpty() ) {
			return( null );
		}
		
		CFLibXmlCoreContext curContext = (CFLibXmlCoreContext)( contextStack.getLast() );
		return( curContext );
	}

//	Accessors: XmlCoreContextFactory
	
	/**
	 *	Get the context factory to use.
	 *
	 *	@return	The context factory to use.
	 */
	public CFLibXmlCoreContextFactory getXmlCoreContextFactory() {
		return( xmlCoreContextFactory );
	}

	/**
	 *	Set the context factory to use.
	 *
	 *	@param	factory	The context factory to use.	
	 */
	public void setXmlCoreContextFactory( CFLibXmlCoreContextFactory factory ) {
		assert factory != null : "factory (arg 1) is null";
		xmlCoreContextFactory = factory;
	}

//	XmlCoreContextFactory Interface

	/**
	 *	Copy an XML Core Context.
	 *
	 *	@param	src	The context to copy.
	 *	@param	qName	The QName of the element about to be processed.
	 *	@param	handler	The XmlCoreElementHandler which will be used for processing.
	 */
	public CFLibXmlCoreContext newXmlCoreContext(
		CFLibXmlCoreContext src,
		String qName,
		CFLibXmlCoreElementHandler handler )
	{
		CFLibXmlCoreContext retval;
		if( ( xmlCoreContextFactory != null ) && ( xmlCoreContextFactory != this ) ) {
			retval = xmlCoreContextFactory.newXmlCoreContext( src, qName, handler );
		}
		else {
			retval = new CFLibXmlCoreContext( src, qName, handler );
		}
		
		return( retval );
	}

	/**
	 *	Construct a "root" XML Core Context instance.
	 *
	 *	@param	coreParser	The parser which owns this instance.
	 *	@param	jlog	Log4J log to use, if null, use parser's log.
	 *	@param	handler	The XmlCoreElementHandler which will be processing the doc root.
	 */
	public CFLibXmlCoreContext newXmlCoreContext(
		CFLibXmlCoreParser coreParser,
		ICFLibMessageLog jlog,
		CFLibXmlCoreElementHandler elementHandler )
	{
		CFLibXmlCoreContext retval;
		if( ( xmlCoreContextFactory != null ) && ( xmlCoreContextFactory != this ) ) {
			retval = xmlCoreContextFactory.newXmlCoreContext( coreParser, jlog, elementHandler );
		}
		else {
			retval = new CFLibXmlCoreContext( coreParser, jlog, elementHandler );
		}
		return( retval );
	}

//	ErrorHandler Interface

	/**
	 *	Handle a warning.
	 */
	public void warning( SAXParseException ex )
		throws SAXException
	{
		String fmt = formatMessage( ex );
		if( log != null ) {
			log.message( "WARN:  " + fmt );
		}
		else {
			System.err.append( "WARN:  " + fmt + "\n" );
		}
	}

	/**
	 *	Handle an error.
	 */
	public void error( SAXParseException ex )
		throws SAXException
	{
		String fmt = formatMessage( ex );
		if( log != null ) {
			log.message( "ERROR: " + fmt );
		}
		else {
			System.err.append( "ERROR: " + fmt + "\n" );
		}
	}

	/**
	 *	Handle a fatal error.
	 */
	public void fatalError( SAXParseException ex )
		throws SAXException
	{
		String fmt = formatMessage( ex );
		if( log != null ) {
			log.message( "FATAL: " + fmt );
		}
		else {
			System.err.append( "FATAL: " + fmt + "\n" );
		}
	}

	/**
	 *	Format the error stack for the specified exception.
	 *
	 *	@param	ex - SAXParseException to report.
	 *
	 *	@return	The formatted error stack.
	 */
	protected String formatMessage( SAXParseException ex ) {
		StringBuffer buff = new StringBuffer();

		String systemId = ex.getSystemId();
        if (systemId != null) {
            int index = systemId.lastIndexOf('/');
            if (index != -1) {
                systemId = systemId.substring(index + 1);
            }
            buff.append( systemId );
        }

        buff.append( '[' );
        buff.append( ex.getLineNumber() );
        buff.append( ',');
        buff.append( ex.getColumnNumber() );
        buff.append( "]: " );
        buff.append( ex.getMessage() );
        buff.append( '\n' );

        return( buff.toString() );
    }

//	ContentHandler Interface

    /**
     *	Receive an object for locating the origin of SAX document events.
     *	<p>
     *	@see org.xml.sax.ContentHandler
     *
     *	@param	locator an object that can return the location of
     *			any SAX document event
     */
    public void setDocumentLocator( Locator locator ) {
    	super.setDocumentLocator( locator );
    	assert locator != null : "locator (arg 1) is null";
    	documentLocator = locator;
    }

    /**
     *	If there is a document locator, use it's information to
     *	prepare a string of the form "near $SystemId$[<$ineNo$.$ColNo$]",
     *	or at least as much of it as possible.
     *
     *	@return	Formatted string or empty string if there is no locator set.
     */
	public String getFormattedNearLocation() {
		String retval;
		Locator loc = getDocumentLocator();
		if( loc != null ) {
			String sysid = loc.getSystemId();
			if( sysid == null ) {
				sysid = "";
			}
			int lineno = loc.getLineNumber();
			int colno = loc.getColumnNumber();
			retval = "near "
				+ sysid
				+ ( ( lineno > 0 )
					? "[" + Integer.toString( lineno )
							+ ( ( colno > 0 )
									? "." + Integer.toString( colno )
									: "" )
							+ "]"
					: "" )
				+ " ";
		}
		else {
			retval = "";
		}
		return( retval );
	}


    /**
     *	Receive notification of the beginning of an element.
     *	<p>
     *	@see org.xml.sax.ContentHandler
     *	<p>
     *	The base implementation maintains the stack of StringBuffers
     *	used to collect the fragments of elementText.
     *
     *	@param	uri	the Namespace URI, or the empty string if the
     *				element has no Namespace URI or if Namespace
     *				processing is not being performed
     *	@param	localName	the local name (without prefix), or the
     *						empty string if Namespace processing
     *						is not being performed
     *	@param	qName	the qualified name (with prefix), or the
     *        			empty string if qualified names are not available
     *	@param	attrs	the attributes attached to the element.  If
     *					there are no attributes, it shall be an empty
     *					Attributes object.  The value of this object after
     *					startElement returns is undefined.
     *
     *	@throws	org.xml.sax.SAXException any SAX exception, possibly
     *			wrapping another exception
     */
    public final void startElement(
    	String		uri,
    	String		localName,
		String		qName,
		Attributes	attrs )
	throws SAXException
	{
    	CFLibXmlCoreContext curContext;
    	if( contextStack.isEmpty() ) {
    		CFLibXmlCoreElementHandler rootHandler = getRootElementHandler();
    		assert rootHandler != null;
    		CFLibXmlCoreContext rootContext = new CFLibXmlCoreContext( this, getLog(), rootHandler );
    		contextStack.addLast( rootContext );
    	}

		CFLibXmlCoreContext prev = (CFLibXmlCoreContext)contextStack.getLast();
		if( prev == null ) {
			throw new RuntimeException( "ContextStack.top is a null value" );
		}

		CFLibXmlCoreElementHandler prevHandler = prev.getElementHandler();
		if( prevHandler == null ) {
			throw new RuntimeException( "ContextStack.top.ElementHandler is null" );
		}

		CFLibXmlCoreElementHandler curHandler = prevHandler.getElementHandler( qName );
		if( curHandler == null ) {
			throw new RuntimeException( "ContextStack.top.ElementHandler<"
				+ prevHandler.getClass().getSimpleName() + ">.getElementHandler( \""
				+ qName + "\" ) has no such mapping" );
		}

    	curContext = new CFLibXmlCoreContext( prev, qName, curHandler );

    	contextStack.addLast( curContext );

    	curHandler.startElement( uri, localName, qName, attrs );
	}


    /**
     *	Receive notification of the end of an element.
     *	<p>
     *	@see org.xml.sax.ContentHandler
     *
     *	@param	uri	the Namespace URI, or the empty string if the
     *				element has no Namespace URI or if Namespace
     *				processing is not being performed
     *	@param	localName	the local name (without prefix), or the
     *						empty string if Namespace processing
     *						is not being performed
     *	@param	qName	the qualified name (with prefix), or the
     *        			empty string if qualified names are not available
     *
     *	@throws	org.xml.sax.SAXException any SAX exception, possibly
     *			wrapping another exception
     */
    public final void endElement(
    	String	uri,
    	String	localName,
    	String	qName)
	throws SAXException
	{
    	assert ! contextStack.isEmpty() : "ContextStack underflow";

    	CFLibXmlCoreContext curContext = (CFLibXmlCoreContext)contextStack.getLast();
    	CFLibXmlCoreElementHandler curHandler = curContext.getElementHandler();

    	try {
    		curHandler.endElement( uri, localName, qName );
    	}
    	finally {
    		contextStack.removeLast();
    	}
	}

    
    /**
     *	Receive notification of character data.
     *	<p>
     *	@see org.xml.sax.ContentHandler
     *	<p>
     *	Appends the additional characters to the current ElementText
     *	StringBuffer.
     *
     *	@param	ch	the characters from the XML document
     *	@param	start	the start position in the array
     *	@param	length	the number of characters to read from the array
     *
     *	@throws	org.xml.sax.SAXException any SAX exception, possibly
     *			wrapping another exception
     */
    public final void characters( char ch[], int start, int length )
	throws SAXException
	{
    	if( ( ch == null ) || ( length <= 0 ) ) {
    		return;
    	}

    	getCurContext().appendElementText( ch, start, length );
	}

//	Protected Methods

    /**
     *	Append the document locator information to the specified StringBuffer.
     *
     *	@param	buff - The StringBuffer to receive document locator information.
     *
     *	@return	The specified buffer to enable functional chaining.
     */
    public StringBuffer appendLocatorInformation( StringBuffer buff ) {

    	assert buff != null: "buff (arg 1) is null";
    	
    	Locator locator = getDocumentLocator();
    	if( locator != null ) {

    		String shortName = null;
    		String docName = locator.getSystemId();
    		if( docName != null ) {
    			int lastSlash = docName.lastIndexOf( '/' );
    			if( ( lastSlash >= 0 ) && ( lastSlash != docName.length() ) ) {
    				shortName = new String( docName.substring( lastSlash + 1 ) );
    			}
    		}
    		
    		if( shortName == null ) {
    			docName = locator.getPublicId();
    			if( docName != null ) {
	    			int lastSlash = docName.lastIndexOf( '/' );
	    			if( ( lastSlash >= 0 ) && ( lastSlash != docName.length() ) ) {
	    				shortName = new String( docName.substring( lastSlash + 1 ) );
	    			}
    			}
    		}
    		
    		if( shortName != null ) {
				buff.append( shortName );
    		}
    		
    		int line = locator.getLineNumber();
    		if( line >= 0 ) {
    			buff.append( "[" + line );
//    			int col = locator.getColumnNumber();
//    			if( col >= 0 ) {
//    				buff.append( "," + col );
//    			}
    			buff.append( "]" );
    		}
    	}
    	
    	return( buff );
	}

	/**
	 *	Initialize the parser schema.
	 *	<p>
	 *	Load the XSDs for documents accepted by the parser.
	 */
	protected void initParser() {

		assert log != null : "log must be set before initializaton";
		assert rootElementHandler != null : "RootElementHandler must be set before initialization";

    }

//
//	/**
//	 *	Parse the specified URI
//	 *
//	 *	@param	uri - The URI for the document to parse.
//	 */
//	public abstract void parse( String uri );
//
//	/**
//	 *	Parse the specified Stream
//	 *
//	 *	@param	input - The InputStream for the document to parse.
//	 */
//	public abstract void parse( InputStream inputStream );

}
