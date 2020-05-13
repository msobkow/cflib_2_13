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

#include <cflib/CFLibXmlCoreIso8859Encoder.hpp>

namespace cflib {

	const std::string CFLibXmlCoreIso8859Encoder::CLASS_NAME( "CFLibXmlCoreIso8859Encoder" );
	CFLibXmlCoreIso8859Encoder** CFLibXmlCoreIso8859Encoder::ToXml = NULL;

	CFLibXmlCoreIso8859Encoder::CFLibXmlCoreIso8859Encoder() {
		ch = '\000';
		len = 0;
		map = NULL;
	}

	CFLibXmlCoreIso8859Encoder::~CFLibXmlCoreIso8859Encoder() {
		if( map != NULL ) {
			delete map;
			map = NULL;
		}
	}

	/**
	 *	Encode a character code as an HTML/XML escape sequence.
	 *
	 *	@param		ic	The integer character code to encode.
	 *	@returns	The "&amp;#9999;" escape sequence for the character code.
	 */
	std::string CFLibXmlCoreIso8859Encoder::xmlEscape( int ic ) {
		static const std::string S_ProcName( "xmlEscape" );
		static const std::string S_ArgIC( "ic" );
		if( ( ic < 0 ) || ( ic > 65536 ) ) {
			std::string Msg( "Character code " + CFLibXmlUtil::formatInt32( ic ) + " not in range 0..65536" );
			throw CFLibArgumentRangeException( CLASS_NAME,
				S_ProcName,
				1,
				S_ArgIC,
				ic,
				(int)0,
				(int)65536 );
		}
		std::string retval( "&#" + CFLibXmlUtil::formatInt32( ic ) + ";" );
		return( retval );
	}

	/**
	 *	Encode acharacter as an HTML/XML escape sequence.
	 *
	 *	@param		c	The character to encode.
	 *	@returns	The "&amp;#9999;" escape sequence for the character code.
	 */
	std::string CFLibXmlCoreIso8859Encoder::xmlEscape( char c ) {
		int ic = (int)c;
		std::string retval = xmlEscape( ic );
		return( retval );
	}

	/**
	 *	Convert a character code for XML/HTML.
	 *	<P>
	 *	Readable encodings such as "&quot;quot;" are used where portable,
	 *	otherwise unicode escapes are used.
	 *
	 *	@param		ic	The integer character code to encode.
	 *	@returns	The most readable XML encoding of the character available.
	 */
	std::string CFLibXmlCoreIso8859Encoder::xmlString( int ic ) {
		if( ToXml == NULL ) {
			init();
		}
		std::string* retval = NULL;
		if( ( ic >= 0 ) && ( ic <= 255 ) ) {
			retval = new std::string( *(ToXml[ic]->map) );
		}
		else {
			retval = new std::string( xmlEscape( ic ) );
		}
		return( *retval );
	}


	/**
	 *	Convert a character for XML/HTML.
	 *	<P>
	 *	Readable encodings such as "&quot;quot;" are used where portable,
	 *	otherwise unicode escapes are used.
	 *
	 *	@param		c	The character to encode.
	 *	@returns	The most readable XML encoding of the character available.
	 */
	std::string CFLibXmlCoreIso8859Encoder::xmlString( char c ) {
		int ic = (int)c;
		std::string retval = xmlString( ic );
		return( retval );
	}


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
	std::string* CFLibXmlCoreIso8859Encoder::xmlBodyString( const std::string* str ) {
		static const std::string S_DQuote( "\"" );
		static const std::string S_SQuote( "\'" );
		if( str == NULL ) {
			return( NULL );
		}
		std::string* retval = new std::string( xmlBodyString( *str ) );
		return( retval );
	}

	std::string CFLibXmlCoreIso8859Encoder::xmlBodyString( const std::string& str ) {
		static const std::string S_DQuote( "\"" );
		static const std::string S_SQuote( "\'" );
		std::string retval;
		std::string::size_type len = str.length();
		if( len > 0 ) {
			char cur = '\0';
			std::string::size_type idx = 0;
			cur = str.at( 0 );
			while( idx < len ) {
				if( idx > 0 ) {
					cur = str.at( idx );
				}
				idx ++;
				switch( cur ) {
					case '\"': retval.append( S_DQuote ); break;
					case '\'': retval.append( S_SQuote ); break;
					default: retval.append( xmlString( cur ) ); break;
				}
			}
		}
		return( retval );
	}

	/**
	 *	Encode a string for HTML/XML.
	 *	<P>
	 *	This method returns a string with special characters encoded
	 *	for HTML/XML, such as <tt>&amp;</tt> mapping to <tt>&amp;amp;</tt>.
	 *
	 *	@param	str		The string to be encoded.
	 *	@returns	The XML/HTML encoded version of the string.
	 */
	std::string* CFLibXmlCoreIso8859Encoder::xmlAttrString( const std::string* str ) {
		if( str == NULL ) {
			return( NULL );
		}
		std::string* retval = new std::string( xmlAttrString( *str ) );
		return( retval );
	}

	std::string CFLibXmlCoreIso8859Encoder::xmlAttrString( const std::string& str ) {
		std::string retval;
		std::string::size_type len = str.length();
		if( len > 0 ) {
			char cur = '\0';
			std::string::size_type idx = 0;
			cur = str.at( 0 );
			while( idx < len ) {
				if( idx > 0 ) {
					cur = str.at( idx );
				}
				idx ++;
				retval.append( xmlString( cur ) );
			}
		}
		return( retval );
	}

	/**
	 *	Encode an escape string for HTML/XML.
	 *	<P>
	 *	This method returns a string with special characters encoded
	 *	for HTML/XML, such as <tt>&amp;</tt> mapping to <tt>&amp;amp;</tt>.
	 *
	 *	@param	str		The string to be encoded.
	 *	@returns	The XML/HTML encoded version of the string.
	 */
	std::string* CFLibXmlCoreIso8859Encoder::xmlEscapeString( const std::string* str ) {
		if( str == NULL ) {
			return( NULL );
		}
		std::string* retval = new std::string( xmlEscapeString( *str ) );
		return( retval );
	}

	std::string CFLibXmlCoreIso8859Encoder::xmlEscapeString( const std::string& str ) {
		std::string retval;
		std::string::size_type len = str.length();
		if( len > 0 ) {
			char cur = '\0';
			bool handleEscape = false;
			std::string::size_type idx = 0;
			cur = str.at( 0 );
			while( idx < len ) {
				if( idx > 0 ) {
					cur = str.at( idx );
				}
				idx ++;
				if( handleEscape ) {
					switch( cur ) {
						case '\\':
							handleEscape = false;
							retval.append( "\\" );
							continue;
						case '\"':
							handleEscape = false;
							retval.append( "&quot;" );
							continue;
						case '\'':
							handleEscape = false;
							retval.append( "&squot;" );
							continue;
						case 'b':
							handleEscape = false;
							retval.append( "\b" );
							continue;
						case 'f':
							handleEscape = false;
							retval.append( "\f" );
							continue;
						case 'n':
							handleEscape = false;
							retval.append( "\n" );
							continue;
						case 'r':
							handleEscape = false;
							retval.append( "\r" );
							continue;
						case 't':
							handleEscape = false;
							retval.append( "\t" );
							continue;
						default:
							handleEscape = false;
							retval.append( xmlString( '\\' ) );
							// Not special, so we want normal XML encoding of the character
							break;
					}
				}
				if( cur == '\\' ) {
					handleEscape = true;
					continue;
				}
				retval.append( xmlString( cur ) );
			}
			if( handleEscape ) {
				// Dangling backslash
				handleEscape = false;
				retval.append( xmlString( '\\' ) );
			}
		}
		return( retval );
	}

	void CFLibXmlCoreIso8859Encoder::release() {
		if( ToXml != NULL ) {
			for( size_t i = 0; i < 255; i++ ) {
				if( ToXml[i] != NULL ) {
					delete ToXml[i];
					ToXml[i] = NULL;
				}
			}
			delete ToXml;
			ToXml = NULL;
		}
	}

	void CFLibXmlCoreIso8859Encoder::init() {
		static const std::string S_ProcName( "init" );
		if( ToXml != NULL ) {
			return;
		}
		int idx;
		char ca[2] = { '\000', '\000' };
		ToXml = new CFLibXmlCoreIso8859Encoder*[256];
		for( idx = 0x00; idx <= 0xFF; idx++ ) {
			ToXml[idx] = new CFLibXmlCoreIso8859Encoder();
			ToXml[idx]->ch = (char)idx;
			ToXml[idx]->len = 0;
			ToXml[idx]->map = NULL;
		}
		/* XML does not allow NUL chars, so we use spaces */
		/* ISO 8859-1 Character Codes 0..15 */
		ToXml[0x00]->map = new std::string( " " );
		ToXml[0x01]->map = new std::string( xmlEscape( 0x01 ) );
		ToXml[0x02]->map = new std::string( xmlEscape( 0x02 ) );
		ToXml[0x03]->map = new std::string( xmlEscape( 0x03 ) );
		ToXml[0x04]->map = new std::string( xmlEscape( 0x04 ) );
		ToXml[0x05]->map = new std::string( xmlEscape( 0x05 ) );
		ToXml[0x06]->map = new std::string( xmlEscape( 0x06 ) );
		ToXml[0x07]->map = new std::string( xmlEscape( 0x07 ) );
		ToXml[0x08]->map = new std::string( xmlEscape( 0x08 ) );
		// { 0x09, 1, { 0x09, 0x00 } },
		// { 0x0A, 1, { 0x0A, 0x00 } },
		ToXml[0x0B]->map = new std::string( xmlEscape( 0x0B ) );
		ToXml[0x0C]->map = new std::string( xmlEscape( 0x0C ) );
		// { 0x0D, 1, { 0x0D, 0x00 } },
		ToXml[0x0E]->map = new std::string( xmlEscape( 0x0E ) );
		ToXml[0x0F]->map = new std::string( xmlEscape( 0x0F ) );

		/* ISO 8859-1 Character Codes 16..31 */
		ToXml[0x10]->map = new std::string( xmlEscape( 0x10 ) );
		ToXml[0x11]->map = new std::string( xmlEscape( 0x11 ) );
		ToXml[0x12]->map = new std::string( xmlEscape( 0x12 ) );
		ToXml[0x13]->map = new std::string( xmlEscape( 0x13 ) );
		ToXml[0x14]->map = new std::string( xmlEscape( 0x14 ) );
		ToXml[0x15]->map = new std::string( xmlEscape( 0x15 ) );
		ToXml[0x16]->map = new std::string( xmlEscape( 0x16 ) );
		ToXml[0x17]->map = new std::string( xmlEscape( 0x17 ) );
		ToXml[0x18]->map = new std::string( xmlEscape( 0x18 ) );
		ToXml[0x19]->map = new std::string( xmlEscape( 0x19 ) );
		ToXml[0x1A]->map = new std::string( xmlEscape( 0x1A ) );
		ToXml[0x1B]->map = new std::string( xmlEscape( 0x1B ) );
		ToXml[0x1C]->map = new std::string( xmlEscape( 0x1C ) );
		ToXml[0x1D]->map = new std::string( xmlEscape( 0x1D ) );
		ToXml[0x1E]->map = new std::string( xmlEscape( 0x1E ) );
		ToXml[0x1F]->map = new std::string( xmlEscape( 0x1F ) );

		/* ISO 8859-1 Character Codes 32..47 */
		// { 0x20, 1, { 0x20, 0x00 } },
		// { 0x21, 1, { 0x21, 0x00 } },
		ToXml[0x22]->map = new std::string( "&quot;" );
		// { 0x23, 1, { 0x23, 0x00 } },
		// { 0x24, 1, { 0x24, 0x00 } },
		// { 0x25, 1, { 0x25, 0x00 } },
		ToXml[0x26]->map = new std::string( "&amp;" );
		// { 0x27, 1, { 0x27, 0x00 } },
		// { 0x28, 1, { 0x28, 0x00 } },
		//	{ 0x29, 1, { 0x29, 0x00 } },
		//	{ 0x2A, 1, { 0x2A, 0x00 } },
		//	{ 0x2B, 1, { 0x2B, 0x00 } },
		//	{ 0x2C, 1, { 0x2C, 0x00 } },
		//	{ 0x2D, 1, { 0x2D, 0x00 } },
		//	{ 0x2E, 1, { 0x2E, 0x00 } },
		//	{ 0x2F, 1, { 0x2F, 0x00 } },

		/* ISO 8859-1 Character Codes 48..63 */
		//	{ 0x30, 1, { 0x30, 0x00 } },
		//	{ 0x31, 1, { 0x31, 0x00 } },
		//	{ 0x32, 1, { 0x32, 0x00 } },
		//	{ 0x33, 1, { 0x33, 0x00 } },
		//	{ 0x34, 1, { 0x34, 0x00 } },
		//	{ 0x35, 1, { 0x35, 0x00 } },
		//	{ 0x36, 1, { 0x36, 0x00 } },
		//	{ 0x37, 1, { 0x37, 0x00 } },
		//	{ 0x38, 1, { 0x38, 0x00 } },
		//	{ 0x39, 1, { 0x39, 0x00 } },
		//	{ 0x3A, 1, { 0x3A, 0x00 } },
		//	{ 0x3B, 1, { 0x3B, 0x00 } },
		ToXml[0x3C]->map = new std::string( "&lt;" );
		//	{ 0x3D, 1, { 0x3D, 0x00 } },
		ToXml[0x3E]->map = new std::string( "&gt;" );
		//	{ 0x3F, 1, { 0x3F, 0x00 } },

		/* ISO 8859-1 Character Codes 64..79 */
		//	{ 0x40, 1, { 0x40, 0x00 } },
		//	{ 0x41, 1, { 0x41, 0x00 } },
		//	{ 0x42, 1, { 0x42, 0x00 } },
		//	{ 0x43, 1, { 0x43, 0x00 } },
		//	{ 0x44, 1, { 0x44, 0x00 } },
		//	{ 0x45, 1, { 0x45, 0x00 } },
		//	{ 0x46, 1, { 0x46, 0x00 } },
		//	{ 0x47, 1, { 0x47, 0x00 } },
		//	{ 0x48, 1, { 0x48, 0x00 } },
		//	{ 0x49, 1, { 0x49, 0x00 } },
		//	{ 0x4A, 1, { 0x4A, 0x00 } },
		//	{ 0x4B, 1, { 0x4B, 0x00 } },
		//	{ 0x4C, 1, { 0x4C, 0x00 } },
		//	{ 0x4D, 1, { 0x4D, 0x00 } },
		//	{ 0x4E, 1, { 0x4E, 0x00 } },
		//	{ 0x4F, 1, { 0x4F, 0x00 } },

		/* ISO 8859-1 Character Codes 80..95 */
		//	{ 0x50, 1, { 0x50, 0x00 } },
		//	{ 0x51, 1, { 0x51, 0x00 } },
		//	{ 0x52, 1, { 0x52, 0x00 } },
		//	{ 0x53, 1, { 0x53, 0x00 } },
		//	{ 0x54, 1, { 0x54, 0x00 } },
		//	{ 0x55, 1, { 0x55, 0x00 } },
		//	{ 0x56, 1, { 0x56, 0x00 } },
		//	{ 0x57, 1, { 0x57, 0x00 } },
		//	{ 0x58, 1, { 0x58, 0x00 } },
		//	{ 0x59, 1, { 0x59, 0x00 } },
		//	{ 0x5A, 1, { 0x5A, 0x00 } },
		//	{ 0x5B, 1, { 0x5B, 0x00 } },
		//	{ 0x5C, 1, { 0x5C, 0x00 } },
		//	{ 0x5D, 1, { 0x5D, 0x00 } },
		//	{ 0x5E, 1, { 0x5E, 0x00 } },
		//	{ 0x5F, 1, { 0x5F, 0x00 } },

		/* ISO 8859-1 Character Codes 96..111 */
		//	{ 0x60, 1, { 0x60, 0x00 } },
		//	{ 0x61, 1, { 0x61, 0x00 } },
		//	{ 0x62, 1, { 0x62, 0x00 } },
		//	{ 0x63, 1, { 0x63, 0x00 } },
		//	{ 0x64, 1, { 0x64, 0x00 } },
		//	{ 0x65, 1, { 0x65, 0x00 } },
		//	{ 0x66, 1, { 0x66, 0x00 } },
		//	{ 0x67, 1, { 0x67, 0x00 } },
		//	{ 0x68, 1, { 0x68, 0x00 } },
		//	{ 0x69, 1, { 0x69, 0x00 } },
		//	{ 0x6A, 1, { 0x6A, 0x00 } },
		//	{ 0x6B, 1, { 0x6B, 0x00 } },
		//	{ 0x6C, 1, { 0x6C, 0x00 } },
		//	{ 0x6D, 1, { 0x6D, 0x00 } },
		//	{ 0x6E, 1, { 0x6E, 0x00 } },
		//	{ 0x6F, 1, { 0x6F, 0x00 } },

		/* ISO 8859-1 Character Codes 112..127 */
		//	{ 0x70, 1, { 0x70, 0x00 } },
		//	{ 0x71, 1, { 0x71, 0x00 } },
		//	{ 0x72, 1, { 0x72, 0x00 } },
		//	{ 0x73, 1, { 0x73, 0x00 } },
		//	{ 0x74, 1, { 0x74, 0x00 } },
		//	{ 0x75, 1, { 0x75, 0x00 } },
		//	{ 0x76, 1, { 0x76, 0x00 } },
		//	{ 0x77, 1, { 0x77, 0x00 } },
		//	{ 0x78, 1, { 0x78, 0x00 } },
		//	{ 0x79, 1, { 0x79, 0x00 } },
		//	{ 0x7A, 1, { 0x7A, 0x00 } },
		//	{ 0x7B, 1, { 0x7B, 0x00 } },
		//	{ 0x7C, 1, { 0x7C, 0x00 } },
		//	{ 0x7D, 1, { 0x7D, 0x00 } },
		//	{ 0x7E, 1, { 0x7E, 0x00 } },
		ToXml[0x7F]->map = new std::string( xmlEscape( 0x7F ) );

//		Initialize remaining ASCII7 string maps

		for( idx = 0; idx <= 0x7F; idx ++ ) {
			if( ToXml[idx]->map == NULL ) {
				ca[0] = (char)idx;
				ToXml[idx]->map = new std::string( ca );
			}
		}

//		Initialize remaining 8859-1 string maps

		/*
		 *	ISO 8859-1 Character Codes 128..255
		 *
		 *	It turns out Xerces 2.2.0 doesn't recognize a lot
		 *	of extended characters.  Rather than try to isolate
		 *	which, we'll just use numeric character codes instead.
		 */
		for( idx = 0x80; idx <= 0xFF; idx ++ ) {
			ToXml[idx]->map = new std::string( xmlEscape( idx ) );
		}

//		Initialize the mapping lengths

		for( idx = 0; idx <= 0xFF; idx ++ ) {
			if( ToXml[idx]->map == NULL ) {
				std::string Msg( "ToXml map entry " + CFLibXmlUtil::formatInt32( idx ) + " corrupt!" );
				throw CFLibRuntimeException( CLASS_NAME,
					S_ProcName,
					Msg );
			}
			ToXml[idx]->len = ToXml[idx]->map->length();
			if( ToXml[idx]->len <= 0 ) {
				std::string Msg( "ToXml map entry " + CFLibXmlUtil::formatInt32( idx ) + " is empty!" );
				throw CFLibRuntimeException( CLASS_NAME,
					S_ProcName,
					Msg );
			}
		}
	};
}
