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
 *	Contact Mark Stephen Sobkow at mark.sobkow@gmail.com for commercial licensing.
 */

package org.msscf.msscf.v2_13.cflib.CFLib;

import java.util.*;

import org.apache.logging.log4j.Level;
import org.apache.logging.log4j.Logger;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;

/**
 *	An XML Core Element Handler is a named evaluator for the JAXP
 *	callback events <tt>beginElement()</tt> and <tt>endElement()</tt>.
 *	<p>
 *	Each element parse context has a map by QName, resolving to
 *	XmlCoreElementParser instances.
 */
public abstract class CFLibXmlCoreElementHandler {

	/**
	 *	The XML Core Parser which owns this Element Handler.
	 */
	private CFLibXmlCoreParser parser = null;

	/**
	 *	The Map by QName for resolving sub-element handlers.
	 */
	private Map<String,CFLibXmlCoreElementHandler> elementHandler = new HashMap<String,CFLibXmlCoreElementHandler>();

//	Constructors

	/**
	 *	Construct an XML Core Element Handler owned by the
	 *	specified parser.
	 *	<p>
	 *	The logger associated with the parser is used for
	 *	processing messages.
	 *
	 *	@param	coreParser	The parser which owns this instance.
	 */
	public CFLibXmlCoreElementHandler( CFLibXmlCoreParser coreParser ) {
		assert coreParser != null : "coreParser (arg 1) is null";
		// Deprecated by Log4J 2 debugLogger.setLevel( Level.INFO );
		setParser( coreParser );
	}

//	Accessors: Logger
	
	/**
	 *	Get the Log4J Logger for processing messages.
	 *
	 *	@return	Logger
	 */
	public ICFLibMessageLog getLog() {
		CFLibXmlCoreContext context = ( parser != null ) ? parser.getCurContext() : null;
		ICFLibMessageLog retval = ( context != null ) ? context.getLog() : null;
		if( retval == null ) {
			if( parser != null ) {
				retval = parser.getLog();
			}
		}
		return( retval );
	}

//	Accessors: Parser

	/**
	 *	Get the XML Core Parser which owns this element handler.
	 *
	 *	@return	The XML Core Parser which owns this element handler.
	 */
	public CFLibXmlCoreParser getParser() {
		return( parser );
	}

	/**
	 *	Set the XML Core Parser which owns this element handler.
	 *
	 *	@param	coreParser	The parser which owns this instance.
	 */
	protected void setParser( CFLibXmlCoreParser coreParser ) {
		assert coreParser != null : "coreParser (arg 1) is null";
		parser = coreParser;
	}

//	Accessors: ElementHandler

	/**
	 *	Add an element handler to be invoked when the named sub-element QName
	 *	is encountered.
	 *
	 *	@param	qName	The QName to map to the handler
	 *	@param	handler	The XmlCoreElementHandler to process the element events.
	 */
	public void addElementHandler( String qName, CFLibXmlCoreElementHandler handler ) {
		assert qName != null && qName.length() > 0 : "qName (arg 1) is null or empty";
		assert handler != null : "handler (arg 2) is null";
		assert ! elementHandler.containsKey( qName ) : "Duplicate qName=\"" + qName + "\" in elementHandler map";
		elementHandler.put( new String( qName ), handler );
	}

	/**
	 *	Locate the named element handler.
	 *
	 *	@param	qName	The QName used to locate the handler.
	 *	@return	The XmlCoreElementHandler mapped to the specified name or null.
	 */
	public CFLibXmlCoreElementHandler getElementHandler( String qName ) {
		CFLibXmlCoreElementHandler retval = (CFLibXmlCoreElementHandler)elementHandler.get( qName );
		return( retval );
	}

//	Element Event Handlers

	/**
	 *	Receive notification of the beginning of an element.
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
	 *					empty string if qualified names are not available
	 *	@param	attrs	the attributes attached to the element.  If
	 *					there are no attributes, it shall be an empty
	 *					Attributes object.  The value of this object after
	 *					startElement returns is undefined.
	 *
	 *	@throws	org.xml.sax.SAXException any SAX exception, possibly
	 *			wrapping another exception
	 */
	public abstract void startElement(
		String		uri,
		String		localName,
		String		qName,
		Attributes	attrs )
	throws SAXException;


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
	 *					empty string if qualified names are not available
	 *
	 *	@throws	org.xml.sax.SAXException any SAX exception, possibly
	 *			wrapping another exception
	 */
	public abstract void endElement(
		String	uri,
		String	localName,
		String	qName)
	throws SAXException;

}
