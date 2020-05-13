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

#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/framework/XMLGrammarPool.hpp>
#include <xercesc/framework/XMLGrammarPoolImpl.hpp>
#include <xercesc/framework/XMLGrammarDescription.hpp>
#include <xercesc/parsers/SAXParser.hpp>
#include <xercesc/sax/Locator.hpp>
#include <xercesc/sax/SAXException.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/Xerces_autoconf_config.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/validators/common/Grammar.hpp>
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

#include <cflib/CFLib.hpp>
#include <cflib/ICFLibMessageLog.hpp>
#include <cflib/CFLibXmlUtil.hpp>
#include <cflib/CFLibXmlCoreContext.hpp>
#include <cflib/ICFLibXmlCoreContextFactory.hpp>
#include <cflib/CFLibXmlCoreParser.hpp>
#include <cflib/CFLibXmlCoreLineCountMemBufInputSource.hpp>

namespace cflib {

	class CFLibXmlCoreSaxParser	: public CFLibXmlCoreParser	{

	protected:
		xercesc::SAX2XMLReader* saxXmlReader;
		cflib::CFLibXmlCoreLineCountMemBufInputSource* memBufInputSource;

	public:
		static const std::string CLASS_NAME;
		static const std::string S_SaxXmlReaderMustBeInitialized;

		CFLibXmlCoreSaxParser();
		CFLibXmlCoreSaxParser( ICFLibMessageLog* jLogger );
		virtual ~CFLibXmlCoreSaxParser();

	protected:
		virtual void initParser();

	public:

		/**
		 *	Load the specified XSD file.
		 *
		 *	@param	xsdFileName - The file system name of the XSD file to be loaded
		 *
		 *	@returns The cached grammar instance resolved by loading the XSD file.
		 */
		xercesc::Grammar* loadGrammar( const std::string& xsdFileName );

		/**
		 *	Parse the specified URI
		 *
		 *	@param	uri - The URI for the document to parse.
		 */
		virtual void parse( const char* systemid );

		/**
		 *	Parse the specified string contents.
		 *	<p>
		 *	The string passed to this method is typically
		 *	a request or response XML document to be processed
		 *	by an appropriate parser and applied to a storage
		 *	server layer.
		 *
		 *	@param The name of the buffer to use in location information.
		 *	@param	str The string contents to be parsed.
		 */
		virtual void parseStringContents( const std::string& buffname, const std::string& str );

		/**
		 *	Parse the specified InputSource.
		 *	<p>
		 *	The InputSource passed to this method is typically
		 *	a piece of glue tying together some other objects output
		 *	as the input for a parse.
		 *
		 *	@param	src The InputSource contents to be parsed.
		 */
		virtual void parse( const xercesc::InputSource& src );
	};
}
