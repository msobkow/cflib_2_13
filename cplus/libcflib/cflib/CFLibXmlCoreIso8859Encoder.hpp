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
#include <cflib/CFLibXmlUtil.hpp>
#include <cflib/CFLibRuntimeException.hpp>
#include <cflib/CFLibArgumentRangeException.hpp>

namespace cflib {

	/**
	 *	The XmlCoreIso8859Encoder converts native strings and characters
	 *	to HTML/XML escaped text.
	 */
	class CFLibXmlCoreIso8859Encoder {

	protected:
		char ch;
		std::string::size_type len;
		std::string* map;
		static CFLibXmlCoreIso8859Encoder** ToXml;

	public:

		static const std::string CLASS_NAME;

		CFLibXmlCoreIso8859Encoder();
		~CFLibXmlCoreIso8859Encoder();

		static void release();
		static void init();

		/**
		 *	Encode a character code as an HTML/XML escape sequence.
		 *
		 *	@param		ic	The integer character code to encode.
		 *	@returns	The "&amp;#9999;" escape sequence for the character code.
		 */
		static std::string xmlEscape( int ic );

		/**
		 *	Encode acharacter as an HTML/XML escape sequence.
		 *
		 *	@param		c	The character to encode.
		 *	@returns	The "&amp;#9999;" escape sequence for the character code.
		 */
		static std::string xmlEscape( char c );

		/**
		 *	Convert a character code for XML/HTML.
		 *	<P>
		 *	Readable encodings such as "&quot;quot;" are used where portable,
		 *	otherwise unicode escapes are used.
		 *
		 *	@param		ic	The integer character code to encode.
		 *	@returns	The most readable XML encoding of the character available.
		 */
		static std::string xmlString( int ic );

		/**
		 *	Convert a character for XML/HTML.
		 *	<P>
		 *	Readable encodings such as "&quot;quot;" are used where portable,
		 *	otherwise unicode escapes are used.
		 *
		 *	@param		c	The character to encode.
		 *	@returns	The most readable XML encoding of the character available.
		 */
		static std::string xmlString( char c );

		/**
		 *	Encode a string for HTML/XML body.
		 *	<P>
		 *	This method returns a string with special characters encoded
		 *	for HTML/XML, such as <tt>&amp;</tt> mapping to <tt>&amp;amp;</tt>.
		 *	<p>
		 *	Unlike the full encoding of xmlString, single and double quotes
		 *	that would interfere with HTML/XML attribute bodies are not
		 *	encoded.
		 *
		 *	@param	str		The string to be encoded.
		 *	@returns	The XML/HTML encoded version of the string.
		 */
		static std::string* xmlBodyString( const std::string* str );
		static std::string xmlBodyString( const std::string& str );

		/**
		 *	Encode a string for HTML/XML.
		 *	<P>
		 *	This method returns a string with special characters encoded
		 *	for HTML/XML, such as <tt>&amp;</tt> mapping to <tt>&amp;amp;</tt>.
		 *
		 *	@param	str		The string to be encoded.
		 *	@returns	The XML/HTML encoded version of the string.
		 */
		static std::string* xmlAttrString( const std::string* str );
		static std::string xmlAttrString( const std::string& str );

		/**
		 *	Encode an escape string for HTML/XML.
		 *	<P>
		 *	This method returns a string with special characters encoded
		 *	for HTML/XML, such as <tt>&amp;</tt> mapping to <tt>&amp;amp;</tt>.
		 *
		 *	@param	str		The string to be encoded.
		 *	@returns	The XML/HTML encoded version of the string.
		 */
		static std::string* xmlEscapeString( const std::string* str );
		static std::string xmlEscapeString( const std::string& str );
	};
}
