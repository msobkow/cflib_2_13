/*
 *  MSS Code Factory CFLib 2.13
 *
 *	Copyright 2020 Mark Stephen Sobkow
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
 *	Please contact Mark Stephen Sobkow at msobkow@sasktel.net for commercial licensing.
 */

#include <cflib/CFLibXmlCoreContext.hpp>
#include <cflib/CFLibXmlCoreParser.hpp>

namespace cflib {

	const std::string CFLibXmlCoreContext::CLASS_NAME( "CFLibXmlCoreContext" );

	CFLibXmlCoreContext::CFLibXmlCoreContext(
		CFLibXmlCoreContext* src,
		const XMLCh* const qName,
		CFLibXmlCoreElementHandler* handler )
	{
		const static std::string S_ProcName( "construct-child" );
		const static std::string S_ArgSrc( "src" );
		const static std::string S_ArgQName( "qName" );
		const static std::string S_ArgHandler( "handler" );
		if( ! CFLib::isInitialized() ) {
			throw CFLibUsageException( CLASS_NAME,
				S_ProcName,
				CFLib::S_MsgInitMustBeCalledFirst );
		}
		prevContext = NULL;
		elementHandler = NULL;
		log = NULL;
		parser = NULL;
		elementQName = NULL;
		obj = NULL;
		if( src == NULL ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_ArgSrc );
		}
		if( qName == NULL ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				2,
				S_ArgQName );
		}
		if( handler == NULL ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				3,
				S_ArgHandler );
		}
		prevContext = src;
		setElementHandler( src->getElementHandler() );
		setLog( src->getLog() );
		setParser( src->getParser() );
		setQNameElementHandler( qName, handler );
	}

	CFLibXmlCoreContext::CFLibXmlCoreContext(
		CFLibXmlCoreParser* coreParser,
		ICFLibMessageLog* jlog,
		CFLibXmlCoreElementHandler* handler )
	{
		const static std::string S_ProcName( "construct-root" );
		const static std::string S_ArgCoreParser( "coreParser" );
		const static std::string S_ArgHandler( "handler" );
		const static XMLCh X_QNameRoot[2] = { (XMLCh)'.', (XMLCh)0 };
		if( ! CFLib::isInitialized() ) {
			throw CFLibUsageException( CLASS_NAME,
				S_ProcName,
				CFLib::S_MsgInitMustBeCalledFirst );
		}
		if( coreParser == NULL ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_ArgCoreParser );
		}
		if( handler == NULL ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				3,
				S_ArgHandler );
		}
		elementQName = NULL;
		prevContext = NULL;
		setParser( coreParser );
		if( jlog != NULL ) {
			setLog( jlog );
		}
		else {
			setLog( coreParser->getLog() );
		}
		setQNameElementHandler( X_QNameRoot, handler );
	}

	CFLibXmlCoreContext::~CFLibXmlCoreContext() {
		if( elementQName != NULL ) {
			delete elementQName;
			elementQName = NULL;
		}
	}

	CFLibXmlCoreContext* CFLibXmlCoreContext::getPrevContext() const {
		return( prevContext );
	}

	bool CFLibXmlCoreContext::hasNamedTag( const std::string& key ) const {
		auto match = tagMap.find( key );
		if( match == tagMap.end() ) {
			return( false );
		}
		else {
			return( true );
		}
	}

	const std::string& CFLibXmlCoreContext::getNamedTag( const std::string& key ) const {
		const static std::string S_ProcName( "getNamedTag" );
		const static std::string S_MsgKeyNotFound( "Key not found: " );
		auto match = tagMap.find( key );
		if( match != tagMap.end() ) {
			return( match->second );
		}
		else {
			std::string S_Msg( S_MsgKeyNotFound + key );
			throw CFLibUnresolvedRelationException(
				CLASS_NAME,
				S_ProcName,
				S_Msg );
		}
	}

	void CFLibXmlCoreContext::putNamedTag( const std::string& key, const std::string& tag ) {
		tagMap[key] = tag;
	}

	ICFLibAnyObj* CFLibXmlCoreContext::getObj() const {
		return( obj );
	}

	void CFLibXmlCoreContext::setObj( ICFLibAnyObj* value ) {
		obj = value;
	}

	CFLibXmlCoreParser* CFLibXmlCoreContext::getParser() {
		return( parser );
	}

	void CFLibXmlCoreContext::setParser( CFLibXmlCoreParser* coreParser ) {
		const static std::string S_ProcName( "construct-root" );
		const static std::string S_ArgCoreParser( "coreParser" );
		if( coreParser == NULL ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_ArgCoreParser );
		}
		parser = coreParser;
	}

	ICFLibMessageLog* CFLibXmlCoreContext::getLog() const {
		if( log != NULL ) {
			return( log );
		}
		if( parser != NULL ) {
			return( parser->getLog() );
		}
		return( NULL );
	}

	void CFLibXmlCoreContext::setLog( ICFLibMessageLog* jlog ) {
		log = jlog;
	}

	void CFLibXmlCoreContext::clearElementText() {
		elementText = CFLib::S_EMPTY; 
	}

	std::string CFLibXmlCoreContext::getElementText() const {
		return( elementText );
	}

	void CFLibXmlCoreContext::appendElementText( const XMLCh* chars, std::string::size_type length ) {
		if( ( chars == NULL ) || ( length <= 0 ) ) {
			return;
		}
		char* transcoded = xercesc::XMLString::transcode( chars );
		std::string cplusstr( transcoded );
		xercesc::XMLString::release( &transcoded );
		elementText.append( cplusstr );
	}

	CFLibXmlCoreElementHandler* CFLibXmlCoreContext::getElementHandler() const {
		return( elementHandler );
	}

	void CFLibXmlCoreContext::setElementHandler( CFLibXmlCoreElementHandler* handler ) {
		const static std::string S_ProcName( "setElementHandler" );
		const static std::string S_ArgHandler( "handler" );
		if( handler == NULL ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_ArgHandler );
		}
		elementHandler = handler;
	}

	void CFLibXmlCoreContext::setQNameElementHandler( const XMLCh* const qName, CFLibXmlCoreElementHandler* handler ) {
		const static std::string S_ProcName( "setElementHandler" );
		const static std::string S_ArgQName( "qName" );
		const static std::string S_ArgHandler( "handler" );
		const static std::string S_MsgQNameAlreadySet( "QName has already been set" );
		if( qName == NULL ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_ArgQName );
		}
		if( handler == NULL ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				2,
				S_ArgHandler );
		}
		if( elementQName != NULL ) {
			throw CFLibUsageException( CLASS_NAME,
				S_ProcName,
				S_MsgQNameAlreadySet );
		}
		elementHandler = handler;
		char* cQName = xercesc::XMLString::transcode( qName );
		elementQName = new std::string( cQName );
		xercesc::XMLString::release( &cQName );
	}
}
