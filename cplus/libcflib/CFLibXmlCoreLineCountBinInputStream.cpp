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

#include <cflib/CFLibXmlCoreLineCountBinInputStream.hpp>
#include <cflib/CFLibXmlCoreParser.hpp>

namespace cflib {

	CFLibXmlCoreLineCountBinInputStream::CFLibXmlCoreLineCountBinInputStream( CFLibXmlCoreParser* parser, xercesc::BinInputStream* chain ) {
		coreParser = parser;
		chainedInput = chain;
		publicId = NULL;
		systemId = NULL;
		myLineNumber = 0;
		myColNumber = 0;
		if( coreParser != NULL ) {
			coreParser->setDocumentLocator( this );
		}
	}

	CFLibXmlCoreLineCountBinInputStream::~CFLibXmlCoreLineCountBinInputStream() {
		if( coreParser != NULL ) {
			coreParser->setDocumentLocator( NULL );
			coreParser = NULL;
		}
		if( chainedInput != NULL ) {
			delete chainedInput;
			chainedInput = NULL;
		}
		if( publicId != NULL ) {
			xercesc::XMLString::release( &publicId );
			publicId = NULL;
		}
		if( systemId != NULL ) {
			xercesc::XMLString::release( &systemId );
			systemId = NULL;
		}
		myLineNumber = 0;
		myColNumber = 0;
	}

	CFLibXmlCoreParser* CFLibXmlCoreLineCountBinInputStream::getParser() {
		return( coreParser );
	}

	const XMLCh * CFLibXmlCoreLineCountBinInputStream::getPublicId() const {
		return( publicId );
	}

	const XMLCh * CFLibXmlCoreLineCountBinInputStream::getSystemId() const {
		return( systemId );
	}

	void CFLibXmlCoreLineCountBinInputStream::setPublicId( const XMLCh* value ) {
		if( value != publicId ) {
			if( publicId != NULL ) {
				xercesc::XMLString::release( &publicId );
				publicId = NULL;
			}
			if( value != NULL ) {
				publicId = xercesc::XMLString::replicate( value );
			}
		}
	}

	void CFLibXmlCoreLineCountBinInputStream::setPublicId( const std::string& value ) {
		XMLCh* transcoded = xercesc::XMLString::transcode( value.c_str() );
		setPublicId( transcoded );
		xercesc::XMLString::release( &transcoded );
	}

	void CFLibXmlCoreLineCountBinInputStream::setSystemId( const XMLCh* value ) {
		if( value != systemId ) {
			if( systemId != NULL ) {
				xercesc::XMLString::release( &systemId );
				systemId = NULL;
			}
			if( value != NULL ) {
				systemId = xercesc::XMLString::replicate( value );
			}
		}
	}

	void CFLibXmlCoreLineCountBinInputStream::setSystemId( const std::string& value ) {
		XMLCh* transcoded = xercesc::XMLString::transcode( value.c_str() );
		setSystemId( transcoded );
		xercesc::XMLString::release( &transcoded );
	}

	XMLFileLoc CFLibXmlCoreLineCountBinInputStream::getLineNumber() const {
		return( myLineNumber );
	}

	XMLFileLoc CFLibXmlCoreLineCountBinInputStream::getColumnNumber() const {
		return( myColNumber );
	}

	XMLFilePos CFLibXmlCoreLineCountBinInputStream::curPos() const {
		return( chainedInput->curPos() );
	}

	const XMLCh* CFLibXmlCoreLineCountBinInputStream::getContentType() const {
		return( chainedInput->getContentType() );
	}

	const XMLCh* CFLibXmlCoreLineCountBinInputStream::getEncoding() const {
		return( chainedInput->getEncoding() );
	}

	XMLSize_t CFLibXmlCoreLineCountBinInputStream::readBytes( XMLByte *const toFill, const XMLSize_t maxToRead ) {
		XMLSize_t actuallyRead = chainedInput->readBytes( toFill, maxToRead );
		if( actuallyRead > 0 ) {
			for( XMLSize_t i = 0; i < actuallyRead; i++ ) {
				if( toFill[i] == '\n' ) {
					myLineNumber ++;
					myColNumber = 0;
				}
				else {
					myColNumber ++;
				}
			}
		}
		return( actuallyRead );
	}
}
