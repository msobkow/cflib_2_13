#pragma once

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
#include <xercesc/framework/MemBufInputSource.hpp>

#include <cflib/CFLibXmlCoreLineCountBinInputStream.hpp>

namespace cflib {
	class CFLibXmlCoreLineCountMemBufInputSource : public xercesc::MemBufInputSource {
		protected:
			CFLibXmlCoreParser* coreParser;

		public:
			CFLibXmlCoreLineCountMemBufInputSource( CFLibXmlCoreParser* parser,
				const XMLByte* const srcDocBytes,
				const XMLSize_t byteCount,
				const XMLCh * const bufId,
				const bool adoptBuffer = false,
				xercesc::MemoryManager * const manager = xercesc::XMLPlatformUtils::fgMemoryManager );
			CFLibXmlCoreLineCountMemBufInputSource( CFLibXmlCoreParser* parser,
				const XMLByte* const srcDocBytes,
				const XMLSize_t byteCount,
				const char * const bufId,
				const bool adoptBuffer = false,
				xercesc::MemoryManager * const manager = xercesc::XMLPlatformUtils::fgMemoryManager );
			virtual ~CFLibXmlCoreLineCountMemBufInputSource();
			virtual xercesc::BinInputStream * makeStream() const;
	};
}
