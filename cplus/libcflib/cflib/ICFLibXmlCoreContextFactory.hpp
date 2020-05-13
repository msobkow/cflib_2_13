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
#include <uuid/uuid.h>
#include <mpfr.h>
#include <time.h>

#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <chrono>
#include <ctime>
#include <list>
#include <string>
#include <tuple>
#include <vector>

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>

#include <cflib/CFLib.hpp>
#include <cflib/ICFLibAnyObj.hpp>
#include <cflib/ICFLibMessageLog.hpp>

namespace cflib {

	class CFLibXmlCoreContext;
	class CFLibXmlCoreElementHandler;
	class CFLibXmlCoreParser;

	class ICFLibXmlCoreContextFactory {

	public:
		ICFLibXmlCoreContextFactory() {
		}

		virtual ~ICFLibXmlCoreContextFactory() {
		}

		virtual ICFLibMessageLog* getLog() const = 0;

		virtual CFLibXmlCoreContext* newXmlCoreContext(
			CFLibXmlCoreContext* parent,
			const XMLCh* qName,
			CFLibXmlCoreElementHandler* handler ) const = 0;

		virtual CFLibXmlCoreContext* newXmlCoreContext(
			CFLibXmlCoreParser* coreParser,
			ICFLibMessageLog* jLogger,
			CFLibXmlCoreElementHandler* handler ) const = 0;
	};
}
