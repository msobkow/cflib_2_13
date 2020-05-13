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

#include <iostream>
#include <cflib/CFLibXmlCoreElementHandler.hpp>

namespace cflib {

	const std::string CFLibXmlCoreElementHandler::CLASS_NAME( "CFLibXmlCoreElementHandler" );

	CFLibXmlCoreElementHandler::CFLibXmlCoreElementHandler( CFLibXmlCoreParser* coreParser ) {
		static const std::string S_ProcName( "construct" );
		static const std::string S_ArgCoreParser( "coreParser" );
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
		parser = coreParser;
	}

	CFLibXmlCoreElementHandler::~CFLibXmlCoreElementHandler() {
	}

	ICFLibMessageLog* CFLibXmlCoreElementHandler::getLog() const {
		CFLibXmlCoreContext* context = ( parser != NULL ) ? parser->getCurContext() : NULL;
		ICFLibMessageLog* retval = ( context != NULL ) ? context->getLog() : NULL;
		if( retval == NULL ) {
			if( parser != NULL ) {
				retval = parser->getLog();
			}
		}
		return( retval );
	}

	CFLibXmlCoreParser* CFLibXmlCoreElementHandler::getParser() const {
		return( parser );
	}

	void CFLibXmlCoreElementHandler::setParser( CFLibXmlCoreParser* coreParser ) {
		static const std::string S_ProcName( "setParser" );
		static const std::string S_ArgCoreParser( "coreParser" );
		if( coreParser == NULL ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_ArgCoreParser );
		}
		parser = coreParser;
	}

	void CFLibXmlCoreElementHandler::addElementHandler( const std::string& qName, CFLibXmlCoreElementHandler* handler ) {
		static const std::string S_ProcName( "addElementHandler" );
		static const std::string S_ArgQName( "qName" );
		static const std::string S_ArgHandler( "handler" );
		static const std::string S_MsgCollisionDetected( "Collision detected for key " );
		if( qName.length() <= 0 ) {
			throw CFLibEmptyArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_ArgQName );
		}
		if( handler == NULL ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_ArgHandler );
		}
		auto curElt = elementHandler.find( qName );
		if( curElt != elementHandler.end() ) {
			std::string S_Msg( S_MsgCollisionDetected + qName );
			throw CFLibCollisionDetectedException( CLASS_NAME,
				S_ProcName,
				S_Msg );
		}
		elementHandler[qName] = handler;
	}

	CFLibXmlCoreElementHandler* CFLibXmlCoreElementHandler::getElementHandler( const std::string& qName ) const {
		static const std::string S_ProcName( "getElementHandler" );
		static const std::string S_ArgQName( "qName" );
		if( qName.length() <= 0 ) {
			throw CFLibEmptyArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_ArgQName );
		}
		auto curElt = elementHandler.find( qName );
		if( curElt == elementHandler.end() ) {
			return( NULL );
		}
		else {
			return( curElt->second );
		}
	}

	CFLibXmlCoreElementHandler* CFLibXmlCoreElementHandler::getElementHandler( const XMLCh* qName ) const {
		if( qName == NULL ) {
			return( NULL );
		}
		char* cQName = xercesc::XMLString::transcode( qName );
		std::string cppQName( cQName );
		xercesc::XMLString::release( &cQName );
		CFLibXmlCoreElementHandler* retval = getElementHandler( cppQName );
		return( retval );
	}

	void CFLibXmlCoreElementHandler::fatalError( const xercesc::SAXParseException& exception ) {
		char* cMessage = xercesc::XMLString::transcode( exception.getMessage () );
		std::string cppMessage( cMessage );
		std::string Msg( "Fatal error: " + cppMessage + " near " + parser->getLocationInfo() + "\n" );
		xercesc::XMLString::release( &cMessage );
		if( getLog() != NULL ) {
			getLog()->message( Msg );
		}
		else {
			std::cerr << Msg;
		}
	}
}
