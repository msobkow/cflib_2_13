#pragma once

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

#include <ctype.h>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <string>

#include <xercesc/sax/SAXException.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLException.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/BinInputStream.hpp>
#include <xercesc/sax/DocumentHandler.hpp>
#include <xercesc/sax/Locator.hpp>
#include <xercesc/framework/MemoryManager.hpp>

namespace cflib {

	class CFLibXmlCoreParser;

	class CFLibXmlCoreLineCountBinInputStream : public virtual xercesc::BinInputStream, public virtual xercesc::Locator {
		protected:
			CFLibXmlCoreParser* coreParser;
			xercesc::BinInputStream* chainedInput;
			XMLFilePos myLineNumber;
			XMLFilePos myColNumber;
			XMLCh * publicId;
			XMLCh * systemId;

		public:
			CFLibXmlCoreLineCountBinInputStream( CFLibXmlCoreParser* parser, xercesc::BinInputStream* chain );
			virtual ~CFLibXmlCoreLineCountBinInputStream();
			virtual CFLibXmlCoreParser* getParser();
			virtual const XMLCh * getPublicId() const;
			virtual void setPublicId( const XMLCh* value );
			virtual void setPublicId( const std::string& value );
			virtual const XMLCh * getSystemId() const;
			virtual void setSystemId( const XMLCh* value );
			virtual void setSystemId( const std::string& value );
			virtual XMLFileLoc getLineNumber() const;
			virtual XMLFileLoc getColumnNumber() const;
			virtual XMLFilePos curPos() const;
			virtual const XMLCh* getContentType() const;
			virtual const XMLCh* getEncoding() const;
			virtual XMLSize_t readBytes( XMLByte *const toFill, const XMLSize_t maxToRead );
	};
}
