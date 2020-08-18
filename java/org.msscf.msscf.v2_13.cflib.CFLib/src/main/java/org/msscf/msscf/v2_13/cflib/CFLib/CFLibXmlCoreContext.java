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

package org.msscf.msscf.v2_13.cflib.CFLib;

import java.util.HashMap;
import java.util.Map;

/**
 *	An XML Core Context is a processing stack entry pushed
 *	at the start of each element or document and popped
 *	at the end of their processing.
 */
public class CFLibXmlCoreContext {

	/**
	 *	Context stack chain.
	 *	<p>
	 *	This had been handled via Java collections, but that
	 *	made the access of stack top - 1 inefficient.
	 */
	private CFLibXmlCoreContext prevContext = null;

	/**
	 *	The StringBuffer to receive character event data.
	 */
	private StringBuffer elementText = new StringBuffer();

	/**
	 *	The XmlCoreElementHandler selected to handle the
	 *	beginElement and endElement events.
	 */
	private CFLibXmlCoreElementHandler elementHandler = null;

	/**
	 *	The Log4J log to receive parser processing messages.
	 *	<p>
	 *	Programmer debug and trace messages should go to <tt>debuglog</tt>.
	 */
	private ICFLibMessageLog log = null;

	/**
	 *	The XML Core Parser which owns this processing Context.
	 */
	private CFLibXmlCoreParser parser = null;

	/**
	 *	The QName of the element being processed.
	 */
	private String elementQName = null;

	/**
	 *	Named attribute map.  Used to retain startElement data for use in endElement.
	 */
	private Map<String,Object> valueMap = new HashMap<String,Object>();

//	Constructors

	/**
	 *	Copy and link an XML Core Context.
	 *	<p>
	 *	The specified source element becomes the PrevContext.
	 *
	 *	@param	src	The context to copy.
	 *	@param	qName	The QName of the element about to be processed.
	 *	@param	handler	The XmlCoreElementHandler which will be used for processing.
	 */
	public CFLibXmlCoreContext(
		CFLibXmlCoreContext src,
		String qName,
		CFLibXmlCoreElementHandler handler )
	{
		assert src != null : "src (arg 1) is null";

		prevContext = src;
		setElementHandler( src.getElementHandler() );
		setLog( src.getLog() );
		setParser( src.getParser() );
		setQNameElementHandler( qName, handler );

//		debuglog.setLevel( Level.INFO );
	}

	/**
	 *	Construct a "root" XML Core Context instance.
	 *
	 *	@param	coreParser	The parser which owns this instance.
	 *	@param	jlog	Log4J log to use, if null, use parser's log.
	 *	@param	handler	The XmlCoreElementHandler which will be processing the doc root.
	 */
	public CFLibXmlCoreContext(
		CFLibXmlCoreParser coreParser,
		ICFLibMessageLog jlog,
		CFLibXmlCoreElementHandler elementHandler )
	{
		assert coreParser != null : "coreParser (arg 1) is null";
		assert elementHandler != null : "elementHandler (arg 3) is null";
		
		prevContext = null;
		
		setParser( coreParser );
		
		if( jlog != null ) {
			setLog( jlog );
		}
		else {
			setLog( coreParser.getLog() );
		}

		setQNameElementHandler( ".", elementHandler );
	}

//	Accessors: PrevContext

	/**
	 *	Get the previous context in the stack.
	 *
	 *	@return	The previous context or null if this is
	 *			the bottom of the stack.
	 */
	public CFLibXmlCoreContext getPrevContext() {
		return( prevContext );
	}

//	Accessors: ValueMap

	/**
	 *	Is there a mapping for the named value slot?
	 *
	 *	@param	name	The name of the object
	 *
	 *	@return	True if there is a mapping for the name.
	 */
	public boolean hasNamedValue( String key ) {
		boolean retval = valueMap.containsKey( key );
		return( retval );
	}
	
	/**
	 *	Get the object for the named value slot.
	 *
	 *	@param	name	The name of the object
	 *	@return	The object associated with the name or null.
	 */
	public Object getNamedValue( String key ) {
		Object retval = valueMap.get( key );
		return( retval );
	}
	
	/**
	 *	Put a named value.
	 *
	 *	@param	name	The name of the object
	 *	@param	value	The object to store for the name
	 *
	 *	@return	The object previously associated with the name or null
	 */
	public Object putNamedValue( String key, Object value ) {
		Object retval = valueMap.put( key, value );
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

//	Accessors: log

	/**
	 *	Get the runtime processing log.
	 *
	 *	@return	Log4J log
	 */
	public ICFLibMessageLog getLog() {
		if( log != null ) {
			return( log );
		}
		if( parser != null ) {
			return( parser.getLog() );
		}
		return( null );
	}

	/**
	 *	Set the runtime processing log.
	 *
	 *	@param	jlog	The log to use for runtime processing messages
	 */
	public void setLog( ICFLibMessageLog jlog ) {
		log = jlog;
	}

//	Accessors: ElementText
	
	/**
	 *	Get the ElementText for the current context.
	 *
	 * 	@return	The element text collected so far.
	 */
	public String getElementText() {
		return( elementText.toString() );
	}

	/**
	 *	Append a character segment to the element text.
	 */
	public void appendElementText( char ch[], int start, int length ) {
		elementText.append( ch, start, length );
	}

//	Accessors: ElementHandler

	/**
	 *	Retrieve the element handler for this processing context.
	 *
	 *	@return	The element handler selected for processing the current element.
	 */
	public CFLibXmlCoreElementHandler getElementHandler() {
		return( elementHandler );
	}

	/**
	 *	Set the element handler for this processing context.
	 *
	 *	@param	handler	The XmlCoreElementHandler selected to process the element.
	 */
	protected void setElementHandler( CFLibXmlCoreElementHandler handler ) {
		assert handler != null : "handler (arg 1) is null";
		elementHandler = handler;
	}

	/**
	 *	Set the element handler and QName for this processing context.
	 *
	 *	@param	qName	The QName of the element or document being processed.
	 *	@param	handler	The XmlCoreElementHandler selected to process the element.
	 */
	public void setQNameElementHandler( String qName, CFLibXmlCoreElementHandler handler ) {
		assert elementQName == null : "Element context QName has already been set";
		assert qName != null && qName.length() > 0 : "qName (arg 1) is null or empty";
		assert handler != null : "handler (arg 2) is null";
		elementHandler = handler;
		elementQName = new String( qName );
	}
}
