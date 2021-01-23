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
#include <uuid/uuid.h>
#include <mpfr.h>
#include <time.h>

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <string>

#include <xercesc/sax/SAXException.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLException.hpp>
#include <xercesc/util/ArrayIndexOutOfBoundsException.hpp>
#include <xercesc/util/EmptyStackException.hpp>
#include <xercesc/util/IOException.hpp>
#include <xercesc/util/IllegalArgumentException.hpp>
#include <xercesc/util/InvalidCastException.hpp>
#include <xercesc/util/NoSuchElementException.hpp>
#include <xercesc/util/NullPointerException.hpp>
#include <xercesc/util/NumberFormatException.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/util/ParseException.hpp>
#include <xercesc/util/RuntimeException.hpp>
#include <xercesc/util/SchemaDateTimeException.hpp>
#include <xercesc/util/TranscodingException.hpp>
#include <xercesc/util/UTFDataFormatException.hpp>
#include <xercesc/util/UnexpectedEOFException.hpp>
#include <xercesc/util/UnsupportedEncodingException.hpp>
#include <xercesc/util/XMLString.hpp>

#include <cflib/CFLib.hpp>
#include <cflib/CFLibInvalidArgumentException.hpp>

namespace cflib {

	class CFLibXmlCore {

	private:
		volatile static bool initialized;

	public:
		static const std::string CLASS_NAME;

		CFLibXmlCore();
		virtual ~CFLibXmlCore();

		static bool isInitialized();
		static void init();
		static void release();
	};
}
