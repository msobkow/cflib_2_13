/*
 *  MSS Code Factory CFLib 2.13
 *
 *	Copyright 2020-2021 Mark Stephen Sobkow
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
 *	Please contact Mark Stephen Sobkow at mark.sobkow@gmail.com for commercial licensing.
 */

#include <iostream>
#include <cflib/CFLibXmlCore.hpp>
#include <cflib/CFLibXmlCoreParser.hpp>
#include <cflib/CFLibXmlCoreElementHandler.hpp>

namespace cflib {

	const std::string CFLibXmlCoreParser::CLASS_NAME( "CFLibXmlCoreParser" );

	xercesc::XMLGrammarPoolImpl* CFLibXmlCoreParser::grammarPool = NULL;

	bool CFLibXmlCoreParser::isInitialized() {
		if( grammarPool != NULL ) {
			return( true );
		}
		else {
			return( false );
		}
	}

	void CFLibXmlCoreParser::init() {
		static const std::string S_ProcName( "init" );
		if( grammarPool != NULL ) {
			return;
		}
		if( ! CFLib::isInitialized() ) {
			throw CFLibUsageException( CLASS_NAME,
				S_ProcName,
				CFLib::S_MsgInitMustBeCalledFirst );
		}
		grammarPool = new xercesc::XMLGrammarPoolImpl();
	}

	void CFLibXmlCoreParser::release() {
		try {
			if( grammarPool != NULL ) {
				delete grammarPool;
				grammarPool = NULL;
			}
		}
		catch( ... ) {
			grammarPool = NULL;
		}
	}

	CFLibXmlCoreParser::CFLibXmlCoreParser()
	: xercesc::DefaultHandler(),
	  ICFLibXmlCoreContextFactory()
	{
		static const std::string S_ProcName( "construct-default" );
		if( ! CFLib::isInitialized() ) {
			throw CFLibUsageException( CLASS_NAME,
				S_ProcName,
				CFLib::S_MsgInitMustBeCalledFirst );
		}
		log = NULL;
		rootElementHandler = NULL;
		contextStack = new std::vector<CFLibXmlCoreContext*>();
		xmlCoreContextFactory = NULL;
		docLocator = NULL;
	}

	CFLibXmlCoreParser::CFLibXmlCoreParser( ICFLibMessageLog* jlog )
	: xercesc::DefaultHandler(),
	  ICFLibXmlCoreContextFactory()
	{
		static const std::string S_ProcName( "construct-log" );
		if( ! CFLib::isInitialized() ) {
			throw CFLibUsageException( CLASS_NAME,
				S_ProcName,
				CFLib::S_MsgInitMustBeCalledFirst );
		}
		log = jlog;
		rootElementHandler = NULL;
		contextStack = new std::vector<CFLibXmlCoreContext*>();
		xmlCoreContextFactory = NULL;
		docLocator = NULL;
	}

	CFLibXmlCoreParser::~CFLibXmlCoreParser() {
		docLocator = NULL;
		if( contextStack != NULL ) {
			CFLibXmlCoreContext* old;
			while( ! contextStack->empty() ) {
				old = contextStack->back();
				contextStack->pop_back();
				if( old != NULL ) {
					delete old;
					old = NULL;
				}
			}
			delete contextStack;
			contextStack = NULL;
		}
	}

	xercesc::XMLGrammarPool* CFLibXmlCoreParser::getGrammarPool() {
		static const std::string S_ProcName( "getGrammarPool" );
		if( ! CFLib::isInitialized() ) {
			throw CFLibUsageException( CLASS_NAME,
				S_ProcName,
				CFLib::S_MsgInitMustBeCalledFirst );
		}
		return( grammarPool );
	}

	xercesc::Grammar* CFLibXmlCoreParser::addToGrammarPool( const std::string& name, xercesc::Grammar* grammar ) {
		static const std::string S_ProcName( "addToGrammarPool" );
		if( ! CFLib::isInitialized() ) {
			throw CFLibUsageException( CLASS_NAME,
				S_ProcName,
				CFLib::S_MsgInitMustBeCalledFirst );
		}
		xercesc::Grammar* useGrammar = NULL;
		if( grammar != NULL ) {
			xercesc::Grammar* existingGrammar = grammarPool->retrieveGrammar( grammar->getGrammarDescription() );
			if( existingGrammar != NULL ) {
				useGrammar = existingGrammar;
			}
			else {
				grammarPool->cacheGrammar( grammar );
				useGrammar = grammar;
			}
		}
		return( useGrammar );
	}

	const xercesc::Locator* CFLibXmlCoreParser::getDocumentLocator() const {
		return( docLocator );
	}

	void CFLibXmlCoreParser::setDocumentLocator( xercesc::Locator* newLocator ) {
		docLocator = newLocator;
		xercesc::DefaultHandler::setDocumentLocator( newLocator );
	}

	ICFLibMessageLog* CFLibXmlCoreParser::getLog() const {
		return( log );
	}

	void CFLibXmlCoreParser::setLog( ICFLibMessageLog* jlog ) {
		log = jlog;
	}

	CFLibXmlCoreElementHandler* CFLibXmlCoreParser::getRootElementHandler() {
		return( rootElementHandler );
	}

	void CFLibXmlCoreParser::setRootElementHandler( CFLibXmlCoreElementHandler* handler ) {
		rootElementHandler = handler;
	}

	std::string CFLibXmlCoreParser::getLocationInfo() {
		const xercesc::Locator* locator = getDocumentLocator();
		std::string buff;
		if( locator != NULL ) {

			std::string* pathName = NULL;

			const XMLCh* docName = locator->getSystemId();
			if( docName != NULL ) {
				char* cDocName = xercesc::XMLString::transcode( docName );
				pathName = new std::string( cDocName );
				xercesc::XMLString::release( &cDocName );
			}

			if( pathName == NULL ) {
				docName = locator->getPublicId();
				if( docName != NULL ) {
					char* cDocName = xercesc::XMLString::transcode( docName );
					pathName = new std::string( cDocName );
					xercesc::XMLString::release( &cDocName );
				}
			}

			if( pathName != NULL ) {
				buff.append( *pathName );
				delete pathName;
				pathName = NULL;
			}

			XMLFileLoc line = locator->getLineNumber();
			if( line >= 0 ) {
				buff.append( "[" + std::to_string( line ) );
				XMLFileLoc col = locator->getColumnNumber();
				if( col >= 0 ) {
					buff.append( "," + std::to_string( col ) );
				}
				buff.append( "]" );
			}
			buff.append( " " );
		}
		return( buff );
	}

	CFLibXmlCoreContext* CFLibXmlCoreParser::getCurContext() {
		if( contextStack->empty() ) {
			return( NULL );
		}
		CFLibXmlCoreContext* curContext = contextStack->back();
		return( curContext );
	}

	ICFLibXmlCoreContextFactory* CFLibXmlCoreParser::getXmlCoreContextFactory() {
		return( xmlCoreContextFactory );
	}

	void CFLibXmlCoreParser::setXmlCoreContextFactory( ICFLibXmlCoreContextFactory* factory ) {
		xmlCoreContextFactory = factory;
	}

	CFLibXmlCoreContext* CFLibXmlCoreParser::newXmlCoreContext(
		CFLibXmlCoreContext* parent,
		const XMLCh* const qName,
		CFLibXmlCoreElementHandler* handler ) const
	{
		CFLibXmlCoreContext* retval;
		if( ( xmlCoreContextFactory != NULL ) && ( xmlCoreContextFactory != this ) ) {
			retval = xmlCoreContextFactory->newXmlCoreContext( parent, qName, handler );
		}
		else {
			retval = new CFLibXmlCoreContext( parent, qName, handler );
		}

		return( retval );
	}

	CFLibXmlCoreContext* CFLibXmlCoreParser::newXmlCoreContext(
		CFLibXmlCoreParser* coreParser,
		ICFLibMessageLog* jlog,
		CFLibXmlCoreElementHandler* handler ) const
	{
		CFLibXmlCoreContext* retval;
		if( ( xmlCoreContextFactory != NULL ) && ( xmlCoreContextFactory != this ) ) {
			retval = xmlCoreContextFactory->newXmlCoreContext( coreParser, jlog, handler );
		}
		else {
			retval = new CFLibXmlCoreContext( coreParser, jlog, handler );
		}
		return( retval );
	}

	std::string CFLibXmlCoreParser::formatMessage( const xercesc::SAXParseException& ex ) {
		std::string buff;

		const XMLCh* systemId = ex.getSystemId();
		if( systemId != NULL ) {
			char* cSystemId = xercesc::XMLString::transcode( systemId );
			std::string cppSystemId( cSystemId );
			std::string::size_type lastSlash = cppSystemId.find_last_of( "/" );
			if( ( lastSlash >= 0 ) && ( lastSlash != cppSystemId.length() ) ) {
				std::string shortName = cppSystemId.substr( lastSlash + 1 );
				buff.append( shortName );
			}
			xercesc::XMLString::release( &cSystemId );
		}

		buff.append( "[" );
		buff.append( CFLibXmlUtil::formatInt64( ex.getLineNumber() ) );
		buff.append( "," );
		buff.append( CFLibXmlUtil::formatInt64( ex.getColumnNumber() ) );
		buff.append( "]: " );
		const XMLCh* message = ex.getMessage();
		if( message != NULL ) {
			char* cMessage = xercesc::XMLString::transcode( message );
			buff.append( cMessage );
			xercesc::XMLString::release( &cMessage );
		}
		buff.append( "\n" );

		return( buff );
	}

	void CFLibXmlCoreParser::warning( const xercesc::SAXParseException& ex )
	{
		std::string fmt = formatMessage( ex );
		if( log != NULL ) {
			log->message( "WARN:  " + fmt );
		}
		else {
			std::cerr << "WARN:  " + fmt + "\n";
		}
	}

	void CFLibXmlCoreParser::error( const xercesc::SAXParseException& ex )
	{
		std::string fmt = formatMessage( ex );
		if( log != NULL ) {
			log->message( "ERROR: " + fmt );
		}
		else {
			std::cerr << "ERROR: " + fmt + "\n";
		}
	}

	void CFLibXmlCoreParser::fatalError( const xercesc::SAXParseException& ex )
	{
		std::string fmt = formatMessage( ex );
		if( log != NULL ) {
			log->message( "FATAL: " + fmt );
		}
		else {
			std::cerr << "FATAL: " + fmt + "\n";
		}
	}

	std::string CFLibXmlCoreParser::getFormattedNearLocation() {
		std::string retval;
		const xercesc::Locator* loc = getDocumentLocator();
		if( loc != NULL ) {
			retval.append( " near " );
			const XMLCh* systemId = loc->getSystemId();
			if( systemId != NULL ) {
				char* cSystemId = xercesc::XMLString::transcode( systemId );
				std::string cppSystemId( cSystemId );
				retval.append( cppSystemId );
				xercesc::XMLString::release( &cSystemId );
			}
			XMLFileLoc lineno = loc->getLineNumber();
			if( lineno > 0 ) {
				retval.append( "[" );
				retval.append( CFLibXmlUtil::formatInt64( lineno ) );
				XMLFileLoc colno = loc->getColumnNumber();
				if( colno > 0 ) {
					retval.append( "," );
					retval.append( std::to_string( colno ) );
				}
				retval.append( "]" );
			}
		}
		return( retval );
	}

	void CFLibXmlCoreParser::clearElementText() {
		contextStack->back()->clearElementText();
	}

	std::string CFLibXmlCoreParser::getElementText() {
		return( contextStack->back()->getElementText() );
	}

	void CFLibXmlCoreParser::startElement(
		const XMLCh* const uri,
		const XMLCh* const localname,
		const XMLCh* const qname,
		const xercesc::Attributes& attrs )
	{
		const static std::string S_ProcName( "startElement" );
		CFLibXmlCoreContext* curContext;
		if( contextStack->empty() ) {
			CFLibXmlCoreElementHandler* rootHandler = getRootElementHandler();
			CFLibXmlCoreContext* rootContext = new CFLibXmlCoreContext( this, getLog(), rootHandler );
			contextStack->push_back( rootContext );
		}

		CFLibXmlCoreContext* prev = contextStack->back();
		CFLibXmlCoreElementHandler* prevHandler = prev->getElementHandler();

		CFLibXmlCoreElementHandler* curHandler = prevHandler->getElementHandler( qname );
		if( curHandler == NULL ) {
			char* cQName = xercesc::XMLString::transcode( qname );
			std::string cppQName( cQName );
			xercesc::XMLString::release( &cQName );
			std::string Msg( "ContextStack.top.ElementHandler<*>.getElementHandler( \""	+ cppQName + "\" ) has no such mapping" );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				Msg );
		}

		curContext = new CFLibXmlCoreContext( prev, qname, curHandler );
		curContext->clearElementText();

		contextStack->push_back( curContext );

		curHandler->startElement( uri, localname, qname, attrs );
	}

	void CFLibXmlCoreParser::endElement (
		const XMLCh* const uri,
		const XMLCh* const localname,
		const XMLCh* const qname )
	{
		CFLibXmlCoreContext* curContext = contextStack->back();
		CFLibXmlCoreElementHandler* curHandler = curContext->getElementHandler();
		if( curHandler != NULL ) {
			try {
				curHandler->endElement( uri, localname, qname );
			}
			catch( ... ) {
			}
		}
		contextStack->pop_back();
		delete curContext;
		curContext = NULL;
	}

    void CFLibXmlCoreParser::characters(
		const XMLCh* const chars,
		const XMLSize_t length )
	{
		if( ( chars == NULL ) || ( length <= 0 ) ) {
			return;
		}
		if( getCurContext() != NULL ) {
			getCurContext()->appendElementText( chars, length );
		}
	}

	std::string* CFLibXmlCoreParser::appendLocatorInformation( std::string* buff ) {

		const xercesc::Locator* locator = getDocumentLocator();
		if( locator != NULL ) {

			std::string* pathName = NULL;

			const XMLCh* systemId = locator->getSystemId();
			if( systemId != NULL ) {
				char* cSystemId = xercesc::XMLString::transcode( systemId );
				pathName = new std::string( cSystemId );
				xercesc::XMLString::release( &cSystemId );
			}

			if( pathName == NULL ) {
				const XMLCh* publicId = locator->getPublicId();
				char* cPublicId = xercesc::XMLString::transcode( publicId );
				pathName = new std::string( cPublicId );
				xercesc::XMLString::release( &cPublicId );
			}

			if( pathName != NULL ) {
				buff->append( *pathName );
				delete pathName;
				pathName = NULL;
			}

			XMLFileLoc line = locator->getLineNumber();
			if( line >= 0 ) {
				buff->append( "[" + std::to_string( line ) + "]" );
			}
		}

		return( buff );
	}

	void CFLibXmlCoreParser::initParser() {
	}
}
