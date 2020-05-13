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

#include <cflib/CFLib.hpp>
#include <cflib/CFLibInvalidArgumentException.hpp>
#include <cflib/CFLibNullArgumentException.hpp>
#include <cflib/CFLibXmlUtil.hpp>
#include <cflib/CFLibGenericBigDecimal.hpp>
#include <xercesc/util/XMLString.hpp>

namespace cflib {

	const std::string CFLibXmlUtil::CLASS_NAME( "CFLibXmlUtil" );
	const std::string CFLibXmlUtil::S_EMPTY_STRING( "" );
	const std::string CFLibXmlUtil::S_IS_INVALID( "\" is invalid" );
	const std::string CFLibXmlUtil::S_VALUE( "value" );
	const std::string CFLibXmlUtil::S_EXPECTED_SIGNED_DIGITS( "Expected signed digits" );
	const std::string CFLibXmlUtil::S_EXPECTED_DIGITS( "Expected unsigned digits" );
	const std::string CFLibXmlUtil::S_EXPECTED_DECIMAL_NUMBER( "Expected decimal number" );

	const char CFLibXmlUtil::S_UTC[4] = "UTC";

	/**
	 *	Parsing for XML attribute content strings.
	**/

	bool CFLibXmlUtil::isDigits( const std::string& value, bool allowSign, bool allowDecimal ) {
		std::string::size_type idx = 0;
		std::string::size_type len = value.length();
		if( allowSign ) {
			switch( value.at( idx ) ) {
				case '+':
				case '-':
					idx++;
					break;
				default:
					break;
			}
		}
		while( ( idx < len ) && ( ( allowDecimal && ( value.at( idx ) == '.' ) ) || isdigit( value.at( idx ) ) ) ) {
			idx ++;
		}
		if( idx < len ) {
			return( false );
		}
		return( true );
	}

	std::vector<BYTE>* CFLibXmlUtil::parseBlob( const std::string& value ) {
		static const std::string S_ProcName( "parseBlob" );
		static const std::string S_Base64Decode( "base64_decode()" );
		if( value.length() <= 0 ) {
			return( NULL );
		}
		std::vector<BYTE>* vec = CFLib::base64_decode( value );
		if( vec == NULL ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				0,
				S_Base64Decode );
		}
		return( vec );
	}

	std::int16_t* CFLibXmlUtil::parseInt16( const std::string& value ) {
		static const std::string S_ProcName( "parseInt16" );
		if( value.length() <= 0 ) {
			return( NULL );
		}
		if( ! isDigits( value, true, false ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				S_EXPECTED_SIGNED_DIGITS );
		}
		int iValue;
		std::sscanf( value.data(), "%d", &iValue );
		int16_t tValue = (int16_t)iValue;
		int16_t* retval = new int16_t();
		*retval = tValue;
		return( retval );
	}

	std::int16_t* CFLibXmlUtil::parseInt16( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "parseInt16" );
		if( value.length() <= 0 ) {
			return( NULL );
		}
		if( ! isDigits( value, true, false ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				S_EXPECTED_SIGNED_DIGITS );
		}
		int iValue;
		std::sscanf( value.data(), "%d", &iValue );
		int16_t tValue = (int16_t)iValue;
		int16_t* retval = new int16_t();
		*retval = tValue;
		return( retval );
	}

	std::int32_t* CFLibXmlUtil::parseInt32( const std::string& value ) {
		static const std::string S_ProcName( "parseInt32" );
		if( value.length() <= 0 ) {
			return( NULL );
		}
		if( ! isDigits( value, true, false ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				S_EXPECTED_SIGNED_DIGITS );
		}
		int iValue;
		std::sscanf( value.data(), "%d", &iValue );
		int32_t tValue = (int32_t)iValue;
		int32_t* retval = new int32_t();
		*retval = tValue;
		return( retval );
	}

	std::int32_t* CFLibXmlUtil::parseInt32( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "parseInt32" );
		if( value.length() <= 0 ) {
			return( NULL );
		}
		if( ! isDigits( value, true, false ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				S_EXPECTED_SIGNED_DIGITS );
		}
		int iValue;
		std::sscanf( value.data(), "%d", &iValue );
		int32_t tValue = (int32_t)iValue;
		int32_t* retval = new int32_t();
		*retval = tValue;
		return( retval );
	}

	std::int64_t* CFLibXmlUtil::parseInt64( const std::string& value ) {
		static const std::string S_ProcName( "parseInt64" );
		if( value.length() <= 0 ) {
			return( NULL );
		}
		if( ! isDigits( value, true, false ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				S_EXPECTED_SIGNED_DIGITS );
		}
		long lValue;
		std::sscanf( value.data(), "%ld", &lValue );
		int64_t tValue = (int64_t)lValue;
		int64_t* retval = new int64_t();
		*retval = tValue;
		return( retval );
	}

	std::int64_t* CFLibXmlUtil::parseInt64( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "parseInt64" );
		if( value.length() <= 0 ) {
			return( NULL );
		}
		if( ! isDigits( value, true, false ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				S_EXPECTED_SIGNED_DIGITS );
		}
		long lValue;
		std::sscanf( value.data(), "%ld", &lValue );
		int64_t tValue = (int64_t)lValue;
		int64_t* retval = new int64_t();
		*retval = tValue;
		return( retval );
	}

	std::uint16_t* CFLibXmlUtil::parseUInt16( const std::string& value ) {
		static const std::string S_ProcName( "parseUInt16" );
		if( value.length() <= 0 ) {
			return( NULL );
		}
		if( ! isDigits( value, false, false ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				S_EXPECTED_DIGITS );
		}
		unsigned uValue;
		std::sscanf( value.data(), "%u", &uValue );
		uint16_t tValue = (uint16_t)uValue;
		uint16_t* retval = new uint16_t();
		*retval = tValue;
		return( retval );
	}

	std::uint16_t* CFLibXmlUtil::parseUInt16( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "parseUInt16" );
		if( value.length() <= 0 ) {
			return( NULL );
		}
		if( ! isDigits( value, false, false ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				S_EXPECTED_DIGITS );
		}
		unsigned uValue;
		std::sscanf( value.data(), "%u", &uValue );
		uint16_t tValue = (uint16_t)uValue;
		uint16_t* retval = new uint16_t();
		*retval = tValue;
		return( retval );
	}

	std::uint32_t* CFLibXmlUtil::parseUInt32( const std::string& value ) {
		static const std::string S_ProcName( "parseUInt32" );
		if( value.length() <= 0 ) {
			return( NULL );
		}
		if( ! isDigits( value, false, false ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				S_EXPECTED_DIGITS );
		}
		unsigned uValue;
		std::sscanf( value.data(), "%u", &uValue );
		uint32_t tValue = (uint32_t)uValue;
		uint32_t* retval = new uint32_t();
		*retval = tValue;
		return( retval );
	}

	std::uint32_t* CFLibXmlUtil::parseUInt32( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "parseUInt32" );
		if( value.length() <= 0 ) {
			return( NULL );
		}
		if( ! isDigits( value, false, false ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				S_EXPECTED_DIGITS );
		}
		unsigned uValue;
		std::sscanf( value.data(), "%u", &uValue );
		uint32_t tValue = (uint32_t)uValue;
		uint32_t* retval = new uint32_t();
		*retval = tValue;
		return( retval );
	}

	std::uint64_t* CFLibXmlUtil::parseUInt64( const std::string& value ) {
		static const std::string S_ProcName( "parseUInt64" );
		if( value.length() <= 0 ) {
			return( NULL );
		}
		if( ! isDigits( value, false, false ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				S_EXPECTED_DIGITS );
		}
		unsigned long uValue;
		std::sscanf( value.data(), "%lu", &uValue );
		uint64_t tValue = (uint64_t)uValue;
		uint64_t* retval = new uint64_t();
		*retval = tValue;
		return( retval );
	}

	std::uint64_t* CFLibXmlUtil::parseUInt64( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "parseUInt64" );
		if( value.length() <= 0 ) {
			return( NULL );
		}
		if( ! isDigits( value, false, false ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				S_EXPECTED_DIGITS );
		}
		unsigned long uValue;
		std::sscanf( value.data(), "%lu", &uValue );
		uint64_t tValue = (uint64_t)uValue;
		uint64_t* retval = new uint64_t();
		*retval = tValue;
		return( retval );
	}

	float* CFLibXmlUtil::parseFloat( const std::string& value ) {
		static const std::string S_ProcName( "parseFloat" );
		if( value.length() <= 0 ) {
			return( NULL );
		}
		if( ! isDigits( value, true, true ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				S_EXPECTED_DECIMAL_NUMBER );
		}
		float fValue;
		std::sscanf( value.data(), "%f", &fValue );
		float* retval = new float();
		*retval = fValue;
		return( retval );
	}

	float* CFLibXmlUtil::parseFloat( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "parseFloat" );
		if( value.length() <= 0 ) {
			return( NULL );
		}
		if( ! isDigits( value, true, true ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				S_EXPECTED_DECIMAL_NUMBER );
		}
		float fValue;
		std::sscanf( value.data(), "%f", &fValue );
		float* retval = new float();
		*retval = fValue;
		return( retval );
	}

	double* CFLibXmlUtil::parseDouble( const std::string& value ) {
		static const std::string S_ProcName( "parseDouble" );
		if( value.length() <= 0 ) {
			return( NULL );
		}
		if( ! isDigits( value, true, true ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				S_EXPECTED_DECIMAL_NUMBER );
		}
		double dValue;
		std::sscanf( value.data(), "%lf", &dValue );
		double* retval = new double();
		*retval = dValue;
		return( retval );
	}

	double* CFLibXmlUtil::parseDouble( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "parseDouble" );
		if( value.length() <= 0 ) {
			return( NULL );
		}
		if( ! isDigits( value, true, true ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				S_EXPECTED_DECIMAL_NUMBER );
		}
		double dValue;
		std::sscanf( value.data(), "%lf", &dValue );
		double* retval = new double();
		*retval = dValue;
		return( retval );
	}

	std::string* CFLibXmlUtil::parseXmlString( const std::string& value ) {
		static const std::string S_ProcName( "parseXmlString" );
		static const std::string S_Amp( "&" );
		static const std::string S_Lt( "<" );
		static const std::string S_Gt( ">" );
		static const std::string S_Quot( "\"" );
		static const std::string S_SQuot( "'" );
		static const std::string S_Semi( ";" );

		std::string* retval = new std::string();
		std::string::size_type len = value.length();
		std::string::size_type idx = 0;
		char ch;
		char chStr[2];
		chStr[1] = '\000';
		std::string::size_type semipos;
		std::string tag;
		std::string::size_type taglen;
		std::string::size_type tagidx;
		bool handleEscape = false;
		while( idx < len ) {
			ch = value.at( idx );
			if( ch == '&' ) {
				semipos = value.find( ';', idx + 1);
				if( semipos > 0 ) {
					tag = value.substr( idx + 1, semipos - 1 );
					if( 0 == xercesc::XMLString::compareIString( tag.data(), "amp" ) ) {
						retval->append( S_Amp );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "lt" ) ) {
						retval->append( S_Lt );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "gt" ) ) {
						retval->append( S_Gt );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "quot" ) ) {
						retval->append( S_Quot );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "squot" ) ) {
						retval->append( S_SQuot );
					}
					else {
						taglen = tag.length();
						tagidx = 0;
						while( ( tagidx < taglen ) && isxdigit( tag.at( tagidx ) ) ) {
							tagidx ++;
						}
						if( tagidx < taglen ) {
							retval->append( S_Amp );
							retval->append( tag );
							retval->append( S_Semi );
						}
						else {
							int ival;
							sscanf( tag.data(), "%x", &ival );
							chStr[0] = ival;
							retval->append( chStr );
						}
					}
					idx = idx + 1 + tag.length() + 1;
				}
				else {
					tag = value.substr( idx );
					retval->append( tag );
				}
			}
			else if( ch == '\\' ) {
				tag = value.substr( idx, 1 );
				if( tag == "n" ) {
					handleEscape = false;
					retval->append( "\n" );
				}
				else if( tag == "r" ) {
					handleEscape = false;
					retval->append( "\r" );
				}
				else if( tag == "f" ) {
					handleEscape = false;
					retval->append( "\f" );
				}
				else if( tag == "t" ) {
					handleEscape = false;
					retval->append( "\t" );
				}
				else {
					std::string Msg( "Unrecognized escape tag '" + tag + "'" );
					throw CFLibUsageException( CLASS_NAME,
						S_ProcName,
						Msg );
				}
			}
			else {
				chStr[0] = ch;
				retval->append( chStr );
			}
		}
		return( retval );
	}

	std::string* CFLibXmlUtil::parseXmlString( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "parseXmlString" );
		static const std::string S_Amp( "&" );
		static const std::string S_Lt( "<" );
		static const std::string S_Gt( ">" );
		static const std::string S_Quot( "\"" );
		static const std::string S_SQuot( "'" );
		static const std::string S_Semi( ";" );

		std::string* retval = new std::string();
		std::string::size_type len = value.length();
		std::string::size_type idx = 0;
		char ch;
		char chStr[2];
		chStr[1] = '\000';
		std::string::size_type semipos;
		std::string tag;
		std::string::size_type taglen;
		std::string::size_type tagidx;
		while( idx < len ) {
			ch = value.at( idx );
			if( ch == '&' ) {
				semipos = value.find( ';', idx + 1);
				if( semipos > 0 ) {
					tag = value.substr( idx + 1, semipos - 1 );
					if( 0 == xercesc::XMLString::compareIString( tag.data(), "amp" ) ) {
						retval->append( S_Amp );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "lt" ) ) {
						retval->append( S_Lt );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "gt" ) ) {
						retval->append( S_Gt );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "quot" ) ) {
						retval->append( S_Quot );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "squot" ) ) {
						retval->append( S_SQuot );
					}
					else {
						taglen = tag.length();
						tagidx = 0;
						while( ( tagidx < taglen ) && isxdigit( tag.at( tagidx ) ) ) {
							tagidx ++;
						}
						if( tagidx < taglen ) {
							retval->append( S_Amp );
							retval->append( tag );
							retval->append( S_Semi );
						}
						else {
							int ival;
							sscanf( tag.data(), "%x", &ival );
							chStr[0] = ival;
							retval->append( chStr );
						}
					}
					idx = idx + 1 + tag.length() + 1;
				}
				else {
					tag = value.substr( idx );
					retval->append( tag );
				}
			}
			else {
				chStr[0] = ch;
				retval->append( chStr );
			}
		}
		return( retval );
	}

	std::string* CFLibXmlUtil::parseXmlStringWhitespacePreserve( const std::string& value ) {
		static const std::string S_ProcName( "parseXmlStringWhitespacePreserve" );
		static const std::string S_Amp( "&" );
		static const std::string S_Lt( "<" );
		static const std::string S_Gt( ">" );
		static const std::string S_Quot( "\"" );
		static const std::string S_SQuot( "'" );
		static const std::string S_Semi( ";" );

		std::string* retval = new std::string();
		std::string::size_type len = value.length();
		std::string::size_type idx = 0;
		char ch;
		char chStr[2];
		chStr[1] = '\000';
		std::string::size_type semipos;
		std::string tag;
		std::string::size_type taglen;
		std::string::size_type tagidx;
		while( idx < len ) {
			ch = value.at( idx );
			if( ch == '&' ) {
				semipos = value.find( ';', idx + 1);
				if( semipos > 0 ) {
					tag = value.substr( idx + 1, semipos - 1 );
					if( 0 == xercesc::XMLString::compareIString( tag.data(), "amp" ) ) {
						retval->append( S_Amp );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "lt" ) ) {
						retval->append( S_Lt );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "gt" ) ) {
						retval->append( S_Gt );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "quot" ) ) {
						retval->append( S_Quot );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "squot" ) ) {
						retval->append( S_SQuot );
					}
					else {
						taglen = tag.length();
						tagidx = 0;
						while( ( tagidx < taglen ) && isxdigit( tag.at( tagidx ) ) ) {
							tagidx ++;
						}
						if( tagidx < taglen ) {
							retval->append( S_Amp );
							retval->append( tag );
							retval->append( S_Semi );
						}
						else {
							int ival;
							sscanf( tag.data(), "%x", &ival );
							chStr[0] = ival;
							retval->append( chStr );
						}
					}
					idx = idx + 1 + tag.length() + 1;
				}
				else {
					tag = value.substr( idx );
					retval->append( tag );
				}
			}
			else {
				chStr[0] = ch;
				retval->append( chStr );
			}
		}
		return( retval );
	}

	std::string* CFLibXmlUtil::parseXmlStringWhitespacePreserve( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "parseXmlStringWhitespacePreserve" );
		static const std::string S_Amp( "&" );
		static const std::string S_Lt( "<" );
		static const std::string S_Gt( ">" );
		static const std::string S_Quot( "\"" );
		static const std::string S_SQuot( "'" );
		static const std::string S_Semi( ";" );

		std::string* retval = new std::string();
		std::string::size_type len = value.length();
		std::string::size_type idx = 0;
		char ch;
		char chStr[2];
		chStr[1] = '\000';
		std::string::size_type semipos;
		std::string tag;
		std::string::size_type taglen;
		std::string::size_type tagidx;
		while( idx < len ) {
			ch = value.at( idx );
			if( ch == '&' ) {
				semipos = value.find( ';', idx + 1);
				if( semipos > 0 ) {
					tag = value.substr( idx + 1, semipos - 1 );
					if( 0 == xercesc::XMLString::compareIString( tag.data(), "amp" ) ) {
						retval->append( S_Amp );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "lt" ) ) {
						retval->append( S_Lt );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "gt" ) ) {
						retval->append( S_Gt );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "quot" ) ) {
						retval->append( S_Quot );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "squot" ) ) {
						retval->append( S_SQuot );
					}
					else {
						taglen = tag.length();
						tagidx = 0;
						while( ( tagidx < taglen ) && isxdigit( tag.at( tagidx ) ) ) {
							tagidx ++;
						}
						if( tagidx < taglen ) {
							retval->append( S_Amp );
							retval->append( tag );
							retval->append( S_Semi );
						}
						else {
							int ival;
							sscanf( tag.data(), "%x", &ival );
							chStr[0] = ival;
							retval->append( chStr );
						}
					}
					idx = idx + 1 + tag.length() + 1;
				}
				else {
					tag = value.substr( idx );
					retval->append( tag );
				}
			}
			else {
				chStr[0] = ch;
				retval->append( chStr );
			}
		}
		return( retval );
	}

	std::chrono::system_clock::time_point* CFLibXmlUtil::parseDate( const std::string& value ) {
		static const std::string S_ProcName( "parseDate" );
		static const std::string S_InvalidFormat( "Invalid value format, must be YYYY-MM-DD, \"" );
		static const char S_PERCENT_D[3] = "%d";

		if( value.length() == 0 ) {
			return( NULL );
		}

		if( value.length() != 10 ) {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				buff );
		}

		if( ! ( isdigit( value.at(0) )
				&& isdigit( value.at(1) )
				&& isdigit( value.at(2) )
				&& isdigit( value.at(3) )
				&& ( value.at(4) == '-' )
				&& isdigit( value.at(5) )
				&& isdigit( value.at(6) )
				&& ( value.at(7) == '-' )
				&& isdigit( value.at(8) )
				&& isdigit( value.at(9) ) ) )
		{
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				buff );
		}

		std::chrono::system_clock::time_point* retval = NULL;

		std::string strYear = value.substr( 0, 4 );
		std::string strMonth = value.substr( 5, 7 );
		std::string strDay = value.substr( 8, 10 );

		int iYear;
		int iMonth;
		int iDay;

		std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
		std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
		std::sscanf( strDay.data(), S_PERCENT_D, &iDay );

		iYear -= 1900;
		iMonth -= 1;

		struct tm tmRead = { 0 };
		tmRead.tm_year = iYear;
		tmRead.tm_mon = iMonth;
		tmRead.tm_mday = iDay;

#if !defined(_WINDOWS)
		tmRead.tm_gmtoff = 0L;
		tmRead.tm_zone = S_UTC;
#endif

		time_t timeRead = mktime( &tmRead );

		std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

		retval = new std::chrono::system_clock::time_point( converted );

		return( retval );
	}

	std::chrono::system_clock::time_point* CFLibXmlUtil::parseDate( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "parseDate" );
		static const std::string S_InvalidFormat( "Invalid value format, must be YYYY-MM-DD, \"" );
		static const char S_PERCENT_D[3] = "%d";

		if( value.length() == 0 ) {
			return( NULL );
		}

		if( value.length() != 10 ) {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				buff );
		}

		if( ! ( isdigit( value.at(0) )
				&& isdigit( value.at(1) )
				&& isdigit( value.at(2) )
				&& isdigit( value.at(3) )
				&& ( value.at(4) == '-' )
				&& isdigit( value.at(5) )
				&& isdigit( value.at(6) )
				&& ( value.at(7) == '-' )
				&& isdigit( value.at(8) )
				&& isdigit( value.at(9) ) ) )
		{
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				buff );
		}

		std::chrono::system_clock::time_point* retval = NULL;

		std::string strYear = value.substr( 0, 4 );
		std::string strMonth = value.substr( 5, 7 );
		std::string strDay = value.substr( 8, 10 );

		int iYear;
		int iMonth;
		int iDay;

		std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
		std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
		std::sscanf( strDay.data(), S_PERCENT_D, &iDay );

		iYear -= 1900;
		iMonth -= 1;

		struct tm tmRead = { 0 };
		tmRead.tm_year = iYear;
		tmRead.tm_mon = iMonth;
		tmRead.tm_mday = iDay;

#if !defined(_WINDOWS)
		tmRead.tm_gmtoff = 0L;
		tmRead.tm_zone = S_UTC;
#endif

		time_t timeRead = mktime( &tmRead );

		std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

		retval = new std::chrono::system_clock::time_point( converted );

		return( retval );
	}

	std::chrono::system_clock::time_point* CFLibXmlUtil::parseTime( const std::string& value ) {
		static const std::string S_ProcName( "parseTime" );
		static const std::string S_InvalidFormat( "Invalid value format, must be HH:MI:SS, \"" );
		static const char S_PERCENT_D[3] = "%d";

		if( value.length() == 0 ) {
			return( NULL );
		}

		if( value.length() != 8 ) {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				buff );
		}

		if( ! ( isdigit( value.at(0) )
				&& isdigit( value.at(1) )
				&& ( value.at(2) == ':' )
				&& isdigit( value.at(3) )
				&& isdigit( value.at(4) )
				&& ( value.at(5) == ':' )
				&& isdigit( value.at(6) )
				&& isdigit( value.at(7) ) ) )
		{
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				buff );
		}

		std::chrono::system_clock::time_point* retval = NULL;

		std::string strHour = value.substr( 0, 1 );
		std::string strMin = value.substr( 3, 4 );
		std::string strSec = value.substr( 6, 7 );

		int iHour;
		int iMin;
		int iSec;

		std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
		std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
		std::sscanf( strSec.data(), S_PERCENT_D, &iSec );

		struct tm tmRead = { 0 };
		tmRead.tm_year = 70;
		tmRead.tm_mon = 0;
		tmRead.tm_mday = 1;
		tmRead.tm_hour = iHour;
		tmRead.tm_min = iMin;
		tmRead.tm_sec = iSec;

#if !defined(_WINDOWS)
		tmRead.tm_gmtoff = 0L;
		tmRead.tm_zone = S_UTC;
#endif

		time_t timeRead = mktime( &tmRead );

		std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

		retval = new std::chrono::system_clock::time_point( converted );

		return( retval );
	}

	std::chrono::system_clock::time_point* CFLibXmlUtil::parseTime( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "parseTime" );
		static const std::string S_InvalidFormat( "Invalid value format, must be HH:MI:SS, \"" );
		static const char S_PERCENT_D[3] = "%d";

		if( value.length() == 0 ) {
			return( NULL );
		}

		if( value.length() != 8 ) {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				buff );
		}

		if( ! ( isdigit( value.at(0) )
				&& isdigit( value.at(1) )
				&& ( value.at(2) == ':' )
				&& isdigit( value.at(3) )
				&& isdigit( value.at(4) )
				&& ( value.at(5) == ':' )
				&& isdigit( value.at(6) )
				&& isdigit( value.at(7) ) ) )
		{
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				buff );
		}

		std::chrono::system_clock::time_point* retval = NULL;

		std::string strHour = value.substr( 0, 1 );
		std::string strMin = value.substr( 3, 4 );
		std::string strSec = value.substr( 6, 7 );

		int iHour;
		int iMin;
		int iSec;

		std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
		std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
		std::sscanf( strSec.data(), S_PERCENT_D, &iSec );

		struct tm tmRead = { 0 };
		tmRead.tm_year = 70;
		tmRead.tm_mon = 0;
		tmRead.tm_mday = 1;
		tmRead.tm_hour = iHour;
		tmRead.tm_min = iMin;
		tmRead.tm_sec = iSec;

#if !defined(_WINDOWS)
		tmRead.tm_gmtoff = 0L;
		tmRead.tm_zone = S_UTC;
#endif

		time_t timeRead = mktime( &tmRead );

		std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

		retval = new std::chrono::system_clock::time_point( converted );

		return( retval );
	}

	std::chrono::system_clock::time_point* CFLibXmlUtil::parseTimestamp( const std::string& value ) {
		static const std::string S_ProcName( "parseTimestamp" );
		static const std::string S_InvalidFormat( "Invalid value format, must be YYYY-MM-DDTHH:MI:SS, \"" );
		static const char S_PERCENT_D[3] = "%d";

		if( value.length() == 0 ) {
			return( NULL );
		}

		if( value.length() != 19 ) {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				buff );
		}

		if( ! ( isdigit( value.at(0) )
				&& isdigit( value.at(1) )
				&& isdigit( value.at(2) )
				&& isdigit( value.at(3) )
				&& ( value.at(4) == '-' )
				&& isdigit( value.at(5) )
				&& isdigit( value.at(6) )
				&& ( value.at(7) == '-' )
				&& isdigit( value.at(8) )
				&& isdigit( value.at(9) )
				&& ( value.at(10) == 'T' )
				&& isdigit( value.at(11) )
				&& isdigit( value.at(12) )
				&& ( value.at(13) == ':' )
				&& isdigit( value.at(14) )
				&& isdigit( value.at(15) )
				&& ( value.at(16) == ':' )
				&& isdigit( value.at(17) )
				&& isdigit( value.at(18) ) ) )
		{
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				buff );
		}

		std::chrono::system_clock::time_point* retval = NULL;

		std::string strYear = value.substr( 0, 4 );
		std::string strMonth = value.substr( 5, 7 );
		std::string strDay = value.substr( 8, 10 );
		std::string strHour = value.substr( 11, 13 );
		std::string strMin = value.substr( 14, 16 );
		std::string strSec = value.substr( 17, 19 );

		int iYear;
		int iMonth;
		int iDay;
		int iHour;
		int iMin;
		int iSec;

		std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
		std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
		std::sscanf( strDay.data(), S_PERCENT_D, &iDay );
		std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
		std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
		std::sscanf( strSec.data(), S_PERCENT_D, &iSec );

		iYear -= 1900;
		iMonth -= 1;
		if( iMonth == 12 ) {
			iYear++;
			iMonth = 0;
		}

		struct tm tmRead = { 0 };

		tmRead.tm_year = iYear;
		tmRead.tm_mon = iMonth;
		tmRead.tm_mday = iDay;
		tmRead.tm_hour = iHour;
		tmRead.tm_min = iMin;
		tmRead.tm_sec = iSec;

#if !defined(_WINDOWS)
		tmRead.tm_gmtoff = 0L;
		tmRead.tm_zone = S_UTC;
#endif

		time_t timeRead = mktime( &tmRead );

		std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

		retval = new std::chrono::system_clock::time_point( converted );

		return( retval );
	}

	std::chrono::system_clock::time_point* CFLibXmlUtil::parseTimestamp( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "parseTimestamp" );
		static const std::string S_InvalidFormat( "Invalid value format, must be YYYY-MM-DDTHH:MI:SS, \"" );
		static const char S_PERCENT_D[3] = "%d";

		if( value.length() == 0 ) {
			return( NULL );
		}

		if( value.length() != 19 ) {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				buff );
		}

		if( ! ( isdigit( value.at(0) )
				&& isdigit( value.at(1) )
				&& isdigit( value.at(2) )
				&& isdigit( value.at(3) )
				&& ( value.at(4) == '-' )
				&& isdigit( value.at(5) )
				&& isdigit( value.at(6) )
				&& ( value.at(7) == '-' )
				&& isdigit( value.at(8) )
				&& isdigit( value.at(9) )
				&& ( value.at(10) == 'T' )
				&& isdigit( value.at(11) )
				&& isdigit( value.at(12) )
				&& ( value.at(13) == ':' )
				&& isdigit( value.at(14) )
				&& isdigit( value.at(15) )
				&& ( value.at(16) == ':' )
				&& isdigit( value.at(17) )
				&& isdigit( value.at(18) ) ) )
		{
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				buff );
		}

		std::chrono::system_clock::time_point* retval = NULL;

		std::string strYear = value.substr( 0, 4 );
		std::string strMonth = value.substr( 5, 7 );
		std::string strDay = value.substr( 8, 10 );
		std::string strHour = value.substr( 11, 13 );
		std::string strMin = value.substr( 14, 16 );
		std::string strSec = value.substr( 17, 19 );

		int iYear;
		int iMonth;
		int iDay;
		int iHour;
		int iMin;
		int iSec;

		std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
		std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
		std::sscanf( strDay.data(), S_PERCENT_D, &iDay );
		std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
		std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
		std::sscanf( strSec.data(), S_PERCENT_D, &iSec );

		iYear -= 1900;
		iMonth -= 1;
		if( iMonth == 12 ) {
			iYear++;
			iMonth = 0;
		}

		struct tm tmRead = { 0 };

		tmRead.tm_year = iYear;
		tmRead.tm_mon = iMonth;
		tmRead.tm_mday = iDay;
		tmRead.tm_hour = iHour;
		tmRead.tm_min = iMin;
		tmRead.tm_sec = iSec;

#if !defined(_WINDOWS)
		tmRead.tm_gmtoff = 0L;
		tmRead.tm_zone = S_UTC;
#endif

		time_t timeRead = mktime( &tmRead );

		std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

		retval = new std::chrono::system_clock::time_point( converted );

		return( retval );
	}

	std::chrono::system_clock::time_point* CFLibXmlUtil::parseTZDate( const std::string& value ) {
		static const std::string S_ProcName( "parseTZDate" );
		static const std::string S_InvalidFormat( "Invalid value format, must be YYYY-MM-DDZ or YYYY-MM-DD+HO:MO, \"" );
		static const char S_PERCENT_D[3] = "%d";

		if( value.length() == 0 ) {
			return( NULL );
		}

		if( ( value.length() != 11 ) && ( value.length() != 16 ) ) {
			if( value.length() != 19 ) {
				std::string buff = * new std::string( S_InvalidFormat );
				buff.append( value );
				buff.append( S_IS_INVALID );
				throw CFLibInvalidArgumentException( CLASS_NAME,
					S_ProcName,
					1,
					S_VALUE,
					buff );
			}
		}

		if( ! ( isdigit( value.at(0) )
				&& isdigit( value.at(1) )
				&& isdigit( value.at(2) )
				&& isdigit( value.at(3) )
				&& ( value.at(4) == '-' )
				&& isdigit( value.at(5) )
				&& isdigit( value.at(6) )
				&& ( value.at(7) == '-' )
				&& isdigit( value.at(8) )
				&& isdigit( value.at(9) ) ) )
		{
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				buff );
		}

		std::chrono::system_clock::time_point* retval = NULL;

		if( value.at( 10 ) == 'Z' ) {
			std::string strYear = value.substr( 0, 4 );
			std::string strMonth = value.substr( 5, 7 );
			std::string strDay = value.substr( 8, 10 );

			int iYear;
			int iMonth;
			int iDay;

			std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
			std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
			std::sscanf( strDay.data(), S_PERCENT_D, &iDay );

			iYear -= 1900;
			iMonth -= 1;

			struct tm tmRead = { 0 };
			tmRead.tm_year = iYear;
			tmRead.tm_mon = iMonth;
			tmRead.tm_mday = iDay;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = 0L;
			tmRead.tm_zone = S_UTC;
#endif

			time_t timeRead = mktime( &tmRead );

			std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

			retval = new std::chrono::system_clock::time_point( converted );
		}
		else if( ( value.at( 10 ) == '-' )
			&& ( isdigit( value.at( 11 ) ) )
			&& ( isdigit( value.at( 12 ) ) )
			&& ( value.at( 13 ) == ':' )
			&& ( isdigit( value.at( 14 ) ) )
			&& ( isdigit( value.at( 15 ) ) ) )
		{
			std::string strYear = value.substr( 0, 4 );
			std::string strMonth = value.substr( 5, 7 );
			std::string strDay = value.substr( 8, 10 );
			std::string strTZHour = value.substr( 11, 12 );
			std::string strTZMin = value.substr( 14,15 );

			int iYear;
			int iMonth;
			int iDay;
			int iTZHour;
			int iTZMin;

			std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
			std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
			std::sscanf( strDay.data(), S_PERCENT_D, &iDay );
			std::sscanf( strTZHour.data(), S_PERCENT_D, &iTZHour );
			std::sscanf( strTZMin.data(), S_PERCENT_D, &iTZMin );

			iYear -= 1900;
			iMonth -= 1;

			struct tm tmRead = { 0 };
			tmRead.tm_year = iYear;
			tmRead.tm_mon = iMonth;
			tmRead.tm_mday = iDay;

			int iOffset = iTZHour * 60 * 60;
			iOffset += iTZMin * 60;

			iOffset = 0 - iOffset;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = iOffset;
			tmRead.tm_zone = NULL;
#endif

			time_t timeRead = mktime( &tmRead );

			std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

			retval = new std::chrono::system_clock::time_point( converted );
		}
		else if( ( value.at( 10 ) == '+' )
			&& ( isdigit( value.at( 11 ) ) )
			&& ( isdigit( value.at( 12 ) ) )
			&& ( value.at( 13 ) == ':' )
			&& ( isdigit( value.at( 14 ) ) )
			&& ( isdigit( value.at( 15 ) ) ) )
		{
			std::string strYear = value.substr( 0, 4 );
			std::string strMonth = value.substr( 5, 7 );
			std::string strDay = value.substr( 8, 10 );
			std::string strTZHour = value.substr( 11, 12 );
			std::string strTZMin = value.substr( 14,15 );

			int iYear;
			int iMonth;
			int iDay;
			int iTZHour;
			int iTZMin;

			std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
			std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
			std::sscanf( strDay.data(), S_PERCENT_D, &iDay );
			std::sscanf( strTZHour.data(), S_PERCENT_D, &iTZHour );
			std::sscanf( strTZMin.data(), S_PERCENT_D, &iTZMin );

			iYear -= 1900;
			iMonth -= 1;

			struct tm tmRead = { 0 };
			tmRead.tm_year = iYear;
			tmRead.tm_mon = iMonth;
			tmRead.tm_mday = iDay;

			int iOffset = iTZHour * 60 * 60;
			iOffset += iTZMin * 60;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = iOffset;
			tmRead.tm_zone = NULL;
#endif

			time_t timeRead = mktime( &tmRead );

			std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

			retval = new std::chrono::system_clock::time_point( converted );
		}
		else {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				buff );
		}

		return( retval );
	}

	std::chrono::system_clock::time_point* CFLibXmlUtil::parseTZDate( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "parseTZDate" );
		static const std::string S_InvalidFormat( "Invalid value format, must be YYYY-MM-DDZ or YYYY-MM-DD+HO:MO, \"" );
		static const char S_PERCENT_D[3] = "%d";

		if( value.length() == 0 ) {
			return( NULL );
		}

		if( ( value.length() != 11 ) && ( value.length() != 16 ) ) {
			if( value.length() != 19 ) {
				std::string buff = * new std::string( S_InvalidFormat );
				buff.append( value );
				buff.append( S_IS_INVALID );
				throw CFLibInvalidArgumentException( CLASS_NAME,
					S_ProcName,
					1,
					S_VALUE,
					buff );
			}
		}

		if( ( value.length() != 11 ) && ( value.length() != 16 ) ) {
			if( value.length() != 19 ) {
				std::string buff = * new std::string( S_InvalidFormat );
				buff.append( value );
				buff.append( S_IS_INVALID );
				throw CFLibInvalidArgumentException( CLASS_NAME,
					S_ProcName,
					1,
					fieldName,
					buff );
			}
		}

		if( ! ( isdigit( value.at(0) )
				&& isdigit( value.at(1) )
				&& isdigit( value.at(2) )
				&& isdigit( value.at(3) )
				&& ( value.at(4) == '-' )
				&& isdigit( value.at(5) )
				&& isdigit( value.at(6) )
				&& ( value.at(7) == '-' )
				&& isdigit( value.at(8) )
				&& isdigit( value.at(9) ) ) )
		{
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				buff );
		}

		std::chrono::system_clock::time_point* retval = NULL;

		if( value.at( 10 ) == 'Z' ) {
			std::string strYear = value.substr( 0, 4 );
			std::string strMonth = value.substr( 5, 7 );
			std::string strDay = value.substr( 8, 10 );

			int iYear;
			int iMonth;
			int iDay;

			std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
			std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
			std::sscanf( strDay.data(), S_PERCENT_D, &iDay );

			iYear -= 1900;
			iMonth -= 1;

			struct tm tmRead = { 0 };
			tmRead.tm_year = iYear;
			tmRead.tm_mon = iMonth;
			tmRead.tm_mday = iDay;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = 0L;
			tmRead.tm_zone = S_UTC;
#endif

			time_t timeRead = mktime( &tmRead );

			std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

			retval = new std::chrono::system_clock::time_point( converted );
		}
		else if( ( value.at( 10 ) == '-' )
			&& ( isdigit( value.at( 11 ) ) )
			&& ( isdigit( value.at( 12 ) ) )
			&& ( value.at( 13 ) == ':' )
			&& ( isdigit( value.at( 14 ) ) )
			&& ( isdigit( value.at( 15 ) ) ) )
		{
			std::string strYear = value.substr( 0, 4 );
			std::string strMonth = value.substr( 5, 7 );
			std::string strDay = value.substr( 8, 10 );
			std::string strTZHour = value.substr( 11, 12 );
			std::string strTZMin = value.substr( 14,15 );

			int iYear;
			int iMonth;
			int iDay;
			int iTZHour;
			int iTZMin;

			std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
			std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
			std::sscanf( strDay.data(), S_PERCENT_D, &iDay );
			std::sscanf( strTZHour.data(), S_PERCENT_D, &iTZHour );
			std::sscanf( strTZMin.data(), S_PERCENT_D, &iTZMin );

			iYear -= 1900;
			iMonth -= 1;

			struct tm tmRead = { 0 };
			tmRead.tm_year = iYear;
			tmRead.tm_mon = iMonth;
			tmRead.tm_mday = iDay;

			int iOffset = iTZHour * 60 * 60;
			iOffset += iTZMin * 60;

			iOffset = 0 - iOffset;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = iOffset;
			tmRead.tm_zone = NULL;
#endif

			time_t timeRead = mktime( &tmRead );

			std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

			retval = new std::chrono::system_clock::time_point( converted );
		}
		else if( ( value.at( 10 ) == '+' )
			&& ( isdigit( value.at( 11 ) ) )
			&& ( isdigit( value.at( 12 ) ) )
			&& ( value.at( 13 ) == ':' )
			&& ( isdigit( value.at( 14 ) ) )
			&& ( isdigit( value.at( 15 ) ) ) )
		{
			std::string strYear = value.substr( 0, 4 );
			std::string strMonth = value.substr( 5, 7 );
			std::string strDay = value.substr( 8, 10 );
			std::string strTZHour = value.substr( 11, 12 );
			std::string strTZMin = value.substr( 14,15 );

			int iYear;
			int iMonth;
			int iDay;
			int iTZHour;
			int iTZMin;

			std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
			std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
			std::sscanf( strDay.data(), S_PERCENT_D, &iDay );
			std::sscanf( strTZHour.data(), S_PERCENT_D, &iTZHour );
			std::sscanf( strTZMin.data(), S_PERCENT_D, &iTZMin );

			iYear -= 1900;
			iMonth -= 1;

			struct tm tmRead = { 0 };
			tmRead.tm_year = iYear;
			tmRead.tm_mon = iMonth;
			tmRead.tm_mday = iDay;

			int iOffset = iTZHour * 60 * 60;
			iOffset += iTZMin * 60;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = iOffset;
			tmRead.tm_zone = NULL;
#endif

			time_t timeRead = mktime( &tmRead );

			std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

			retval = new std::chrono::system_clock::time_point( converted );
		}
		else {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				buff );
		}

		return( retval );
	}

	std::chrono::system_clock::time_point* CFLibXmlUtil::parseTZTime( const std::string& value ) {
		static const std::string S_ProcName( "parseTZTime" );
		static const std::string S_InvalidFormat( "Invalid value format, must be HH:MI:SSZ or HH:MI:SS+HO:MO, \"" );
		static const char S_PERCENT_D[3] = "%d";

		if( value.length() == 0 ) {
			return( NULL );
		}

		if( ( value.length() != 9 ) && ( value.length() != 14 ) ) {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				buff );
		}

		if( ! ( isdigit( value.at(0) )
				&& isdigit( value.at(1) )
				&& ( value.at(2) == ':' )
				&& isdigit( value.at(3) )
				&& isdigit( value.at(4) )
				&& ( value.at(5) == ':' )
				&& isdigit( value.at(6) )
				&& isdigit( value.at(7) ) ) )
		{
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				buff );
		}

		std::chrono::system_clock::time_point* retval = NULL;

		if( value.at( 8 ) == 'Z' ) {
			std::string strHour = value.substr( 0, 1 );
			std::string strMin = value.substr( 3, 4 );
			std::string strSec = value.substr( 6, 7 );

			int iHour;
			int iMin;
			int iSec;

			std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
			std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
			std::sscanf( strSec.data(), S_PERCENT_D, &iSec );

			struct tm tmRead = { 0 };
			tmRead.tm_hour = iHour;
			tmRead.tm_min = iMin;
			tmRead.tm_sec = iSec;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = 0L;
			tmRead.tm_zone = S_UTC;
#endif

			time_t timeRead = mktime( &tmRead );

			std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

			retval = new std::chrono::system_clock::time_point( converted );
		}
		else if( ( value.at( 8 ) == '-' )
			&& ( isdigit( value.at( 9 ) ) )
			&& ( isdigit( value.at( 10 ) ) )
			&& ( value.at( 11 ) == ':' )
			&& ( isdigit( value.at( 12 ) ) )
			&& ( isdigit( value.at( 13 ) ) ) )
		{
			std::string strHour = value.substr( 0, 1 );
			std::string strMin = value.substr( 3, 4 );
			std::string strSec = value.substr( 6, 7 );
			std::string strTZHour = value.substr( 9, 10 );
			std::string strTZMin = value.substr( 12, 13 );

			int iHour;
			int iMin;
			int iSec;
			int iTZHour;
			int iTZMin;

			std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
			std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
			std::sscanf( strSec.data(), S_PERCENT_D, &iSec );
			std::sscanf( strTZHour.data(), S_PERCENT_D, &iTZHour );
			std::sscanf( strTZMin.data(), S_PERCENT_D, &iTZMin );

			struct tm tmRead = { 0 };
			tmRead.tm_hour = iHour;
			tmRead.tm_min = iMin;
			tmRead.tm_sec = iSec;

			int iOffset = iTZHour * 60 * 60;
			iOffset += iTZMin * 60;

			iOffset = 0 - iOffset;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = iOffset;
			tmRead.tm_zone = NULL;
#endif

			time_t timeRead = mktime( &tmRead );

			std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

			retval = new std::chrono::system_clock::time_point( converted );
		}
		else if( ( value.at( 8 ) == '+' )
				&& ( isdigit( value.at( 9 ) ) )
				&& ( isdigit( value.at( 10 ) ) )
				&& ( value.at( 11 ) == ':' )
				&& ( isdigit( value.at( 12 ) ) )
				&& ( isdigit( value.at( 13 ) ) ) )
		{
			std::string strHour = value.substr( 0, 1 );
			std::string strMin = value.substr( 3, 4 );
			std::string strSec = value.substr( 6, 7 );
			std::string strTZHour = value.substr( 9, 10 );
			std::string strTZMin = value.substr( 12, 13 );

			int iHour;
			int iMin;
			int iSec;
			int iTZHour;
			int iTZMin;

			std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
			std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
			std::sscanf( strSec.data(), S_PERCENT_D, &iSec );
			std::sscanf( strTZHour.data(), S_PERCENT_D, &iTZHour );
			std::sscanf( strTZMin.data(), S_PERCENT_D, &iTZMin );

			struct tm tmRead = { 0 };
			tmRead.tm_hour = iHour;
			tmRead.tm_min = iMin;
			tmRead.tm_sec = iSec;

			int iOffset = iTZHour * 60 * 60;
			iOffset += iTZMin * 60;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = iOffset;
			tmRead.tm_zone = NULL;
#endif

			time_t timeRead = mktime( &tmRead );

			std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

			retval = new std::chrono::system_clock::time_point( converted );
		}
		else {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				buff );
		}

		return( retval );
	}

	std::chrono::system_clock::time_point* CFLibXmlUtil::parseTZTime( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "parseTZTime" );
		static const std::string S_InvalidFormat( "Invalid value format, must be HH:MI:SSZ or HH:MI:SS+HO:MO, \"" );
		static const char S_PERCENT_D[3] = "%d";

		if( value.length() == 0 ) {
			return( NULL );
		}

		if( ( value.length() != 9 ) && ( value.length() != 14 ) ) {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				buff );
		}

		if( ! ( isdigit( value.at(0) )
				&& isdigit( value.at(1) )
				&& ( value.at(2) == ':' )
				&& isdigit( value.at(3) )
				&& isdigit( value.at(4) )
				&& ( value.at(5) == ':' )
				&& isdigit( value.at(6) )
				&& isdigit( value.at(7) ) ) )
		{
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				buff );
		}

		std::chrono::system_clock::time_point* retval = NULL;

		if( value.at( 8 ) == 'Z' ) {
			std::string strHour = value.substr( 0, 1 );
			std::string strMin = value.substr( 3, 4 );
			std::string strSec = value.substr( 6, 7 );

			int iHour;
			int iMin;
			int iSec;

			std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
			std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
			std::sscanf( strSec.data(), S_PERCENT_D, &iSec );

			struct tm tmRead = { 0 };
			tmRead.tm_hour = iHour;
			tmRead.tm_min = iMin;
			tmRead.tm_sec = iSec;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = 0L;
			tmRead.tm_zone = S_UTC;
#endif

			time_t timeRead = mktime( &tmRead );

			std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

			retval = new std::chrono::system_clock::time_point( converted );
		}
		else if( ( value.at( 8 ) == '-' )
			&& ( isdigit( value.at( 9 ) ) )
			&& ( isdigit( value.at( 10 ) ) )
			&& ( value.at( 11 ) == ':' )
			&& ( isdigit( value.at( 12 ) ) )
			&& ( isdigit( value.at( 13 ) ) ) )
		{
			std::string strHour = value.substr( 0, 1 );
			std::string strMin = value.substr( 3, 4 );
			std::string strSec = value.substr( 6, 7 );
			std::string strTZHour = value.substr( 9, 10 );
			std::string strTZMin = value.substr( 12, 13 );

			int iHour;
			int iMin;
			int iSec;
			int iTZHour;
			int iTZMin;

			std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
			std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
			std::sscanf( strSec.data(), S_PERCENT_D, &iSec );
			std::sscanf( strTZHour.data(), S_PERCENT_D, &iTZHour );
			std::sscanf( strTZMin.data(), S_PERCENT_D, &iTZMin );

			struct tm tmRead = { 0 };
			tmRead.tm_hour = iHour;
			tmRead.tm_min = iMin;
			tmRead.tm_sec = iSec;

			int iOffset = iTZHour * 60 * 60;
			iOffset += iTZMin * 60;

			iOffset = 0 - iOffset;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = iOffset;
			tmRead.tm_zone = NULL;
#endif

			time_t timeRead = mktime( &tmRead );

			std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

			retval = new std::chrono::system_clock::time_point( converted );
		}
		else if( ( value.at( 8 ) == '+' )
				&& ( isdigit( value.at( 9 ) ) )
				&& ( isdigit( value.at( 10 ) ) )
				&& ( value.at( 11 ) == ':' )
				&& ( isdigit( value.at( 12 ) ) )
				&& ( isdigit( value.at( 13 ) ) ) )
		{
			std::string strHour = value.substr( 0, 1 );
			std::string strMin = value.substr( 3, 4 );
			std::string strSec = value.substr( 6, 7 );
			std::string strTZHour = value.substr( 9, 10 );
			std::string strTZMin = value.substr( 12, 13 );

			int iHour;
			int iMin;
			int iSec;
			int iTZHour;
			int iTZMin;

			std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
			std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
			std::sscanf( strSec.data(), S_PERCENT_D, &iSec );
			std::sscanf( strTZHour.data(), S_PERCENT_D, &iTZHour );
			std::sscanf( strTZMin.data(), S_PERCENT_D, &iTZMin );

			struct tm tmRead = { 0 };
			tmRead.tm_hour = iHour;
			tmRead.tm_min = iMin;
			tmRead.tm_sec = iSec;

			int iOffset = iTZHour * 60 * 60;
			iOffset += iTZMin * 60;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = iOffset;
			tmRead.tm_zone = NULL;
#endif

			time_t timeRead = mktime( &tmRead );

			std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

			retval = new std::chrono::system_clock::time_point( converted );
		}
		else {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				buff );
		}

		return( retval );
	}

	std::chrono::system_clock::time_point* CFLibXmlUtil::parseTZTimestamp( const std::string& value ) {
		static const std::string S_ProcName( "parseTZTimestamp" );
		static const std::string S_InvalidFormat( "Invalid value format, must be YYYY-MM-DDTHH:MI:SSZ or YYYY-MM-DDTHH:MI:SS+HO:MO, \"" );
		static const char S_PERCENT_D[3] = "%d";

		if( value.length() == 0 ) {
			return( NULL );
		}

		if( ( value.length() != 20 ) && ( value.length() != 25 ) ) {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				buff );
		}

		if( ! ( isdigit( value.at(0) )
				&& isdigit( value.at(1) )
				&& isdigit( value.at(2) )
				&& isdigit( value.at(3) )
				&& ( value.at(4) == '-' )
				&& isdigit( value.at(5) )
				&& isdigit( value.at(6) )
				&& ( value.at(7) == '-' )
				&& isdigit( value.at(8) )
				&& isdigit( value.at(9) )
				&& ( value.at(10) == 'T' )
				&& isdigit( value.at(11) )
				&& isdigit( value.at(12) )
				&& ( value.at(13) == ':' )
				&& isdigit( value.at(14) )
				&& isdigit( value.at(15) )
				&& ( value.at(16) == ':' )
				&& isdigit( value.at(17) )
				&& isdigit( value.at(18) ) ) )
		{
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				buff );
		}

		std::chrono::system_clock::time_point* retval = NULL;

		if( value.at( 19 ) == 'Z' ) {
			std::string strYear = value.substr( 0, 4 );
			std::string strMonth = value.substr( 5, 7 );
			std::string strDay = value.substr( 8, 10 );
			std::string strHour = value.substr( 11, 13 );
			std::string strMin = value.substr( 14, 16 );
			std::string strSec = value.substr( 17, 19 );

			int iYear;
			int iMonth;
			int iDay;
			int iHour;
			int iMin;
			int iSec;

			std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
			std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
			std::sscanf( strDay.data(), S_PERCENT_D, &iDay );
			std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
			std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
			std::sscanf( strSec.data(), S_PERCENT_D, &iSec );

			iYear -= 1900;
			iMonth -= 1;
			if( iMonth == 12 ) {
				iYear++;
				iMonth = 0;
			}

			struct tm tmRead = { 0 };

			tmRead.tm_year = iYear;
			tmRead.tm_mon = iMonth;
			tmRead.tm_mday = iDay;
			tmRead.tm_hour = iHour;
			tmRead.tm_min = iMin;
			tmRead.tm_sec = iSec;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = 0L;
			tmRead.tm_zone = S_UTC;
#endif

			time_t timeRead = mktime( &tmRead );

			std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

			retval = new std::chrono::system_clock::time_point( converted );
		}
		else if( ( value.at( 19 ) == '-' )
			&& ( isdigit( value.at( 20 ) ) )
			&& ( isdigit( value.at( 21 ) ) )
			&& ( value.at( 22 ) == ':' )
			&& ( isdigit( value.at( 23 ) ) )
			&& ( isdigit( value.at( 24 ) ) ) )
		{
			std::string strYear = value.substr( 0, 4 );
			std::string strMonth = value.substr( 5, 7 );
			std::string strDay = value.substr( 8, 10 );
			std::string strHour = value.substr( 11, 13 );
			std::string strMin = value.substr( 14, 16 );
			std::string strSec = value.substr( 17, 19 );
			std::string strTZHour = value.substr( 20, 21 );
			std::string strTZMin = value.substr( 23, 24 );

			int iYear;
			int iMonth;
			int iDay;
			int iHour;
			int iMin;
			int iSec;
			int iTZHour;
			int iTZMin;

			std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
			std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
			std::sscanf( strDay.data(), S_PERCENT_D, &iDay );
			std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
			std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
			std::sscanf( strSec.data(), S_PERCENT_D, &iSec );
			std::sscanf( strTZHour.data(), S_PERCENT_D, &iTZHour );
			std::sscanf( strTZMin.data(), S_PERCENT_D, &iTZMin );

			iYear -= 1900;
			iMonth -= 1;
			if( iMonth == 12 ) {
				iYear++;
				iMonth = 0;
			}

			struct tm tmRead = { 0 };

			tmRead.tm_year = iYear;
			tmRead.tm_mon = iMonth;
			tmRead.tm_mday = iDay;
			tmRead.tm_hour = iHour;
			tmRead.tm_min = iMin;
			tmRead.tm_sec = iSec;

			int iOffset = iTZHour * 60 * 60;
			iOffset += iTZMin * 60;

			iOffset = 0 - iOffset;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = iOffset;
			tmRead.tm_zone = NULL;
#endif

			time_t timeRead = mktime( &tmRead );

			std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

			retval = new std::chrono::system_clock::time_point( converted );
		}
		else if( ( value.at( 19 ) == '+' )
				&& ( isdigit( value.at( 20 ) ) )
				&& ( isdigit( value.at( 21 ) ) )
				&& ( value.at( 22 ) == ':' )
				&& ( isdigit( value.at( 23 ) ) )
				&& ( isdigit( value.at( 24 ) ) ) )
		{
			std::string strYear = value.substr( 0, 4 );
			std::string strMonth = value.substr( 5, 7 );
			std::string strDay = value.substr( 8, 10 );
			std::string strHour = value.substr( 11, 13 );
			std::string strMin = value.substr( 14, 16 );
			std::string strSec = value.substr( 17, 19 );
			std::string strTZHour = value.substr( 20, 21 );
			std::string strTZMin = value.substr( 23, 24 );

			int iYear;
			int iMonth;
			int iDay;
			int iHour;
			int iMin;
			int iSec;
			int iTZHour;
			int iTZMin;

			std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
			std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
			std::sscanf( strDay.data(), S_PERCENT_D, &iDay );
			std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
			std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
			std::sscanf( strSec.data(), S_PERCENT_D, &iSec );
			std::sscanf( strTZHour.data(), S_PERCENT_D, &iTZHour );
			std::sscanf( strTZMin.data(), S_PERCENT_D, &iTZMin );

			iYear -= 1900;
			iMonth -= 1;
			if( iMonth == 12 ) {
				iYear++;
				iMonth = 0;
			}

			struct tm tmRead = { 0 };

			tmRead.tm_year = iYear;
			tmRead.tm_mon = iMonth;
			tmRead.tm_mday = iDay;
			tmRead.tm_hour = iHour;
			tmRead.tm_min = iMin;
			tmRead.tm_sec = iSec;

			int iOffset = iTZHour * 60 * 60;
			iOffset += iTZMin * 60;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = iOffset;
			tmRead.tm_zone = NULL;
#endif

			time_t timeRead = mktime( &tmRead );

			std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

			retval = new std::chrono::system_clock::time_point( converted );
		}
		else {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				buff );
		}

		return( retval );
	}

	std::chrono::system_clock::time_point* CFLibXmlUtil::parseTZTimestamp( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "parseTZTimestamp" );
		static const std::string S_InvalidFormat( "Invalid value format, must be YYYY-MM-DDTHH:MI:SSZ or YYYY-MM-DDTHH:MI:SS+HO:MO, \"" );
		static const char S_PERCENT_D[3] = "%d";

		if( value.length() == 0 ) {
			return( NULL );
		}

		if( ( value.length() != 20 ) && ( value.length() != 25 ) ) {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				buff );
		}

		if( ! ( isdigit( value.at(0) )
				&& isdigit( value.at(1) )
				&& isdigit( value.at(2) )
				&& isdigit( value.at(3) )
				&& ( value.at(4) == '-' )
				&& isdigit( value.at(5) )
				&& isdigit( value.at(6) )
				&& ( value.at(7) == '-' )
				&& isdigit( value.at(8) )
				&& isdigit( value.at(9) )
				&& ( value.at(10) == 'T' )
				&& isdigit( value.at(11) )
				&& isdigit( value.at(12) )
				&& ( value.at(13) == ':' )
				&& isdigit( value.at(14) )
				&& isdigit( value.at(15) )
				&& ( value.at(16) == ':' )
				&& isdigit( value.at(17) )
				&& isdigit( value.at(18) ) ) )
		{
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				buff );
		}

		std::chrono::system_clock::time_point* retval = NULL;

		if( value.at( 19 ) == 'Z' ) {
			std::string strYear = value.substr( 0, 4 );
			std::string strMonth = value.substr( 5, 7 );
			std::string strDay = value.substr( 8, 10 );
			std::string strHour = value.substr( 11, 13 );
			std::string strMin = value.substr( 14, 16 );
			std::string strSec = value.substr( 17, 19 );

			int iYear;
			int iMonth;
			int iDay;
			int iHour;
			int iMin;
			int iSec;

			std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
			std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
			std::sscanf( strDay.data(), S_PERCENT_D, &iDay );
			std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
			std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
			std::sscanf( strSec.data(), S_PERCENT_D, &iSec );

			iYear -= 1900;
			iMonth -= 1;
			if( iMonth == 12 ) {
				iYear++;
				iMonth = 0;
			}

			struct tm tmRead = { 0 };

			tmRead.tm_year = iYear;
			tmRead.tm_mon = iMonth;
			tmRead.tm_mday = iDay;
			tmRead.tm_hour = iHour;
			tmRead.tm_min = iMin;
			tmRead.tm_sec = iSec;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = 0L;
			tmRead.tm_zone = S_UTC;
#endif

			time_t timeRead = mktime( &tmRead );

			std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

			retval = new std::chrono::system_clock::time_point( converted );
		}
		else if( ( value.at( 19 ) == '-' )
			&& ( isdigit( value.at( 20 ) ) )
			&& ( isdigit( value.at( 21 ) ) )
			&& ( value.at( 22 ) == ':' )
			&& ( isdigit( value.at( 23 ) ) )
			&& ( isdigit( value.at( 24 ) ) ) )
		{
			std::string strYear = value.substr( 0, 4 );
			std::string strMonth = value.substr( 5, 7 );
			std::string strDay = value.substr( 8, 10 );
			std::string strHour = value.substr( 11, 13 );
			std::string strMin = value.substr( 14, 16 );
			std::string strSec = value.substr( 17, 19 );
			std::string strTZHour = value.substr( 20, 21 );
			std::string strTZMin = value.substr( 23, 24 );

			int iYear;
			int iMonth;
			int iDay;
			int iHour;
			int iMin;
			int iSec;
			int iTZHour;
			int iTZMin;

			std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
			std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
			std::sscanf( strDay.data(), S_PERCENT_D, &iDay );
			std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
			std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
			std::sscanf( strSec.data(), S_PERCENT_D, &iSec );
			std::sscanf( strTZHour.data(), S_PERCENT_D, &iTZHour );
			std::sscanf( strTZMin.data(), S_PERCENT_D, &iTZMin );

			iYear -= 1900;
			iMonth -= 1;
			if( iMonth == 12 ) {
				iYear++;
				iMonth = 0;
			}

			struct tm tmRead = { 0 };

			tmRead.tm_year = iYear;
			tmRead.tm_mon = iMonth;
			tmRead.tm_mday = iDay;
			tmRead.tm_hour = iHour;
			tmRead.tm_min = iMin;
			tmRead.tm_sec = iSec;

			int iOffset = iTZHour * 60 * 60;
			iOffset += iTZMin * 60;

			iOffset = 0 - iOffset;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = iOffset;
			tmRead.tm_zone = NULL;
#endif

			time_t timeRead = mktime( &tmRead );

			std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

			retval = new std::chrono::system_clock::time_point( converted );
		}
		else if( ( value.at( 19 ) == '+' )
				&& ( isdigit( value.at( 20 ) ) )
				&& ( isdigit( value.at( 21 ) ) )
				&& ( value.at( 22 ) == ':' )
				&& ( isdigit( value.at( 23 ) ) )
				&& ( isdigit( value.at( 24 ) ) ) )
		{
			std::string strYear = value.substr( 0, 4 );
			std::string strMonth = value.substr( 5, 7 );
			std::string strDay = value.substr( 8, 10 );
			std::string strHour = value.substr( 11, 13 );
			std::string strMin = value.substr( 14, 16 );
			std::string strSec = value.substr( 17, 19 );
			std::string strTZHour = value.substr( 20, 21 );
			std::string strTZMin = value.substr( 23, 24 );

			int iYear;
			int iMonth;
			int iDay;
			int iHour;
			int iMin;
			int iSec;
			int iTZHour;
			int iTZMin;

			std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
			std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
			std::sscanf( strDay.data(), S_PERCENT_D, &iDay );
			std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
			std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
			std::sscanf( strSec.data(), S_PERCENT_D, &iSec );
			std::sscanf( strTZHour.data(), S_PERCENT_D, &iTZHour );
			std::sscanf( strTZMin.data(), S_PERCENT_D, &iTZMin );

			iYear -= 1900;
			iMonth -= 1;
			if( iMonth == 12 ) {
				iYear++;
				iMonth = 0;
			}

			struct tm tmRead = { 0 };

			tmRead.tm_year = iYear;
			tmRead.tm_mon = iMonth;
			tmRead.tm_mday = iDay;
			tmRead.tm_hour = iHour;
			tmRead.tm_min = iMin;
			tmRead.tm_sec = iSec;

			int iOffset = iTZHour * 60 * 60;
			iOffset += iTZMin * 60;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = iOffset;
			tmRead.tm_zone = NULL;
#endif

			time_t timeRead = mktime( &tmRead );

			std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

			retval = new std::chrono::system_clock::time_point( converted );
		}
		else {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				buff );
		}

		return( retval );
	}

	void CFLibXmlUtil::parseUuid( uuid_ptr_t target, const std::string& value ) {
		static const std::string S_ProcName( "parseUuid" );
		static const std::string S_InvalidFormat( "Invalid value format, must be xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx, \"" );

		if( value.length() == 0 ) {
			for( int i = 0; i < 16; i++ ) {
				target[ i ] = 0;
			}
			return;
		}

		if( value.length() != 36 ) {
			for( int i = 0; i < 16; i++ ) {
				target[ i ] = 0;
			}
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				buff );
		}

		uuid_parse( value.data(), target );
	}

	void CFLibXmlUtil::parseUuid( uuid_ptr_t target, const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "parseUuid" );
		static const std::string S_InvalidFormat( "Invalid value format, must be xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx, \"" );

		if( value.length() == 0 ) {
			for( int i = 0; i < 16; i++ ) {
				target[ i ] = 0;
			}
			return;
		}

		if( value.length() != 36 ) {
			for( int i = 0; i < 16; i++ ) {
				target[ i ] = 0;
			}
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				buff );
		}

		if( ! ( isxdigit( value.at(0) )
				&& isxdigit( value.at(1) )
				&& isxdigit( value.at(2) )
				&& isxdigit( value.at(3) )
				&& isxdigit( value.at(4) )
				&& isxdigit( value.at(5) )
				&& isxdigit( value.at(6) )
				&& isxdigit( value.at(7) )
				&& ( value.at(8) == '-' )
				&& isxdigit( value.at(9) )
				&& isxdigit( value.at(10) )
				&& isxdigit( value.at(11) )
				&& isxdigit( value.at(12) )
				&& ( value.at(13) == '-' )
				&& isxdigit( value.at(14) )
				&& isxdigit( value.at(15) )
				&& isxdigit( value.at(16) )
				&& isxdigit( value.at(17) )
				&& ( value.at(18) == '-' )
				&& isxdigit( value.at(19) )
				&& isxdigit( value.at(20) )
				&& isxdigit( value.at(21) )
				&& isxdigit( value.at(22) )
				&& ( value.at(23) == '-' )
				&& isxdigit( value.at(24) )
				&& isxdigit( value.at(25) )
				&& isxdigit( value.at(26) )
				&& isxdigit( value.at(27) )
				&& isxdigit( value.at(28) )
				&& isxdigit( value.at(29) )
				&& isxdigit( value.at(30) )
				&& isxdigit( value.at(31) )
				&& isxdigit( value.at(32) )
				&& isxdigit( value.at(33) )
				&& isxdigit( value.at(34) )
				&& isxdigit( value.at(35) ) ) )
		{
			for( int i = 0; i < 16; i ++ ) {
				target[i] = 0;
			}
			std::string buff( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				buff );
		}

		uuid_parse( value.data(), target );
	}

	std::vector<BYTE> CFLibXmlUtil::evalBlob( const std::string& value ) {
		static const std::string S_ProcName( "evalBlob" );
		static const std::string S_Base64Decode( "base64_decode()" );
		if( value.length() <= 0 ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				"value" );
		}
		std::vector<BYTE>* vec = CFLib::base64_decode( value );
		if( vec == NULL ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				0,
				S_Base64Decode );
		}
		std::vector<BYTE> retval = *vec;
		delete vec;
		vec = NULL;
		return( retval );
	}

	std::int16_t CFLibXmlUtil::evalInt16( const std::string& value ) {
		static const std::string S_ProcName( "evalInt16" );
		if( value.length() <= 0 ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE );
		}
		if( ! isDigits( value, true, false ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				S_EXPECTED_SIGNED_DIGITS );
		}
		int iValue;
		std::sscanf( value.data(), "%d", &iValue );
		int16_t tValue = (int16_t)iValue;
		return( tValue );
	}

	std::int16_t CFLibXmlUtil::evalInt16( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "evalInt16" );
		if( value.length() <= 0 ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE );
		}
		if( ! isDigits( value, true, false ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				S_EXPECTED_SIGNED_DIGITS );
		}
		int iValue;
		std::sscanf( value.data(), "%d", &iValue );
		int16_t tValue = (int16_t)iValue;
		return( tValue );
	}

	std::int32_t CFLibXmlUtil::evalInt32( const std::string& value ) {
		static const std::string S_ProcName( "evalInt32" );
		if( value.length() <= 0 ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE );
		}
		if( ! isDigits( value, true, false ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				S_EXPECTED_SIGNED_DIGITS );
		}
		int iValue;
		std::sscanf( value.data(), "%d", &iValue );
		int32_t tValue = (int32_t)iValue;
		return( tValue );
	}

	std::int32_t CFLibXmlUtil::evalInt32( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "evalInt32" );
		if( value.length() <= 0 ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE );
		}
		if( ! isDigits( value, true, false ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				S_EXPECTED_SIGNED_DIGITS );
		}
		int iValue;
		std::sscanf( value.data(), "%d", &iValue );
		int32_t tValue = (int32_t)iValue;
		return( tValue );
	}

	std::int64_t CFLibXmlUtil::evalInt64( const std::string& value ) {
		static const std::string S_ProcName( "evalInt64" );
		if( value.length() <= 0 ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE );
		}
		if( ! isDigits( value, true, false ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				S_EXPECTED_SIGNED_DIGITS );
		}
		long lValue;
		std::sscanf( value.data(), "%ld", &lValue );
		int64_t tValue = (int64_t)lValue;
		return( tValue );
	}

	std::int64_t CFLibXmlUtil::evalInt64( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "evalInt64" );
		if( value.length() <= 0 ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE );
		}
		if( ! isDigits( value, true, false ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				S_EXPECTED_SIGNED_DIGITS );
		}
		long lValue;
		std::sscanf( value.data(), "%ld", &lValue );
		int64_t tValue = (int64_t)lValue;
		return( tValue );
	}

	std::uint16_t CFLibXmlUtil::evalUInt16( const std::string& value ) {
		static const std::string S_ProcName( "evalUInt16" );
		if( value.length() <= 0 ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE );
		}
		if( ! isDigits( value, false, false ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				S_EXPECTED_DIGITS );
		}
		unsigned uValue;
		std::sscanf( value.data(), "%u", &uValue );
		uint16_t tValue = (uint16_t)uValue;
		return( tValue );
	}

	std::uint16_t CFLibXmlUtil::evalUInt16( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "evalUInt16" );
		if( value.length() <= 0 ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE );
		}
		if( ! isDigits( value, false, false ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				S_EXPECTED_DIGITS );
		}
		unsigned uValue;
		std::sscanf( value.data(), "%u", &uValue );
		uint16_t tValue = (uint16_t)uValue;
		return( tValue );
	}

	std::uint32_t CFLibXmlUtil::evalUInt32( const std::string& value ) {
		static const std::string S_ProcName( "evalUInt32" );
		if( value.length() <= 0 ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE );
		}
		if( ! isDigits( value, false, false ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				S_EXPECTED_DIGITS );
		}
		unsigned uValue;
		std::sscanf( value.data(), "%u", &uValue );
		uint32_t tValue = (uint32_t)uValue;
		return( tValue );
	}

	std::uint32_t CFLibXmlUtil::evalUInt32( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "evalUInt32" );
		if( value.length() <= 0 ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE );
		}
		if( ! isDigits( value, false, false ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				S_EXPECTED_DIGITS );
		}
		unsigned uValue;
		std::sscanf( value.data(), "%u", &uValue );
		uint32_t tValue = (uint32_t)uValue;
		return( tValue );
	}

	std::uint64_t CFLibXmlUtil::evalUInt64( const std::string& value ) {
		static const std::string S_ProcName( "evalUInt64" );
		if( value.length() <= 0 ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE );
		}
		if( ! isDigits( value, false, false ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				S_EXPECTED_DIGITS );
		}
		unsigned long uValue;
		std::sscanf( value.data(), "%lu", &uValue );
		uint64_t tValue = (uint64_t)uValue;
		return( tValue );
	}

	std::uint64_t CFLibXmlUtil::evalUInt64( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "evalUInt64" );
		if( value.length() <= 0 ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE );
		}
		if( ! isDigits( value, false, false ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				S_EXPECTED_DIGITS );
		}
		unsigned long uValue;
		std::sscanf( value.data(), "%lu", &uValue );
		uint64_t tValue = (uint64_t)uValue;
		return( tValue );
	}

	float CFLibXmlUtil::evalFloat( const std::string& value ) {
		static const std::string S_ProcName( "evalFloat" );
		if( value.length() <= 0 ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE );
		}
		if( ! isDigits( value, true, true ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				S_EXPECTED_DECIMAL_NUMBER );
		}
		float fValue;
		std::sscanf( value.data(), "%f", &fValue );
		return( fValue );
	}

	float CFLibXmlUtil::evalFloat( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "evalFloat" );
		if( value.length() <= 0 ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE );
		}
		if( ! isDigits( value, true, true ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				S_EXPECTED_DECIMAL_NUMBER );
		}
		float fValue;
		std::sscanf( value.data(), "%f", &fValue );
		return( fValue );
	}

	double CFLibXmlUtil::evalDouble( const std::string& value ) {
		static const std::string S_ProcName( "evalDouble" );
		if( value.length() <= 0 ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE );
		}
		if( ! isDigits( value, true, true ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				S_EXPECTED_DECIMAL_NUMBER );
		}
		double dValue;
		std::sscanf( value.data(), "%lf", &dValue );
		return( dValue );
	}

	double CFLibXmlUtil::evalDouble( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "evalDouble" );
		if( value.length() <= 0 ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE );
		}
		if( ! isDigits( value, true, true ) ) {
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				S_EXPECTED_DECIMAL_NUMBER );
		}
		double dValue;
		std::sscanf( value.data(), "%lf", &dValue );
		return( dValue );
	}

	std::string CFLibXmlUtil::evalXmlString( const std::string& value ) {
		static const std::string S_ProcName( "evalXmlString" );
		static const std::string S_Amp( "&" );
		static const std::string S_Lt( "<" );
		static const std::string S_Gt( ">" );
		static const std::string S_Quot( "\"" );
		static const std::string S_SQuot( "'" );
		static const std::string S_Semi( ";" );

		std::string retval;
		std::string::size_type len = value.length();
		std::string::size_type idx = 0;
		char ch;
		char chStr[2];
		chStr[1] = '\000';
		std::string::size_type semipos;
		std::string tag;
		std::string::size_type taglen;
		std::string::size_type tagidx;
		bool handleEscape = false;
		while( idx < len ) {
			ch = value.at( idx );
			if( ch == '&' ) {
				semipos = value.find( ';', idx + 1);
				if( semipos > 0 ) {
					tag = value.substr( idx + 1, semipos - 1 );
					if( 0 == xercesc::XMLString::compareIString( tag.data(), "amp" ) ) {
						retval.append( S_Amp );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "lt" ) ) {
						retval.append( S_Lt );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "gt" ) ) {
						retval.append( S_Gt );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "quot" ) ) {
						retval.append( S_Quot );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "squot" ) ) {
						retval.append( S_SQuot );
					}
					else {
						taglen = tag.length();
						tagidx = 0;
						while( ( tagidx < taglen ) && isxdigit( tag.at( tagidx ) ) ) {
							tagidx ++;
						}
						if( tagidx < taglen ) {
							retval.append( S_Amp );
							retval.append( tag );
							retval.append( S_Semi );
						}
						else {
							int ival;
							sscanf( tag.data(), "%x", &ival );
							chStr[0] = ival;
							retval.append( chStr );
						}
					}
					idx = idx + 1 + tag.length() + 1;
				}
				else {
					tag = value.substr( idx );
					retval.append( tag );
				}
			}
			else if( ch == '\\' ) {
				tag = value.substr( idx, 1 );
				if( tag == "n" ) {
					handleEscape = false;
					retval.append( "\n" );
				}
				else if( tag == "r" ) {
					handleEscape = false;
					retval.append( "\r" );
				}
				else if( tag == "f" ) {
					handleEscape = false;
					retval.append( "\f" );
				}
				else if( tag == "t" ) {
					handleEscape = false;
					retval.append( "\t" );
				}
				else {
					std::string Msg( "Unrecognized escape tag '" + tag + "'" );
					throw CFLibUsageException( CLASS_NAME,
						S_ProcName,
						Msg );
				}
			}
			else {
				chStr[0] = ch;
				retval.append( chStr );
			}
		}
		return( retval );
	}

	std::string CFLibXmlUtil::evalXmlString( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "evalXmlString" );
		static const std::string S_Amp( "&" );
		static const std::string S_Lt( "<" );
		static const std::string S_Gt( ">" );
		static const std::string S_Quot( "\"" );
		static const std::string S_SQuot( "'" );
		static const std::string S_Semi( ";" );

		std::string retval;
		std::string::size_type len = value.length();
		std::string::size_type idx = 0;
		char ch;
		char chStr[2];
		chStr[1] = '\000';
		std::string::size_type semipos;
		std::string tag;
		std::string::size_type taglen;
		std::string::size_type tagidx;
		while( idx < len ) {
			ch = value.at( idx );
			if( ch == '&' ) {
				semipos = value.find( ';', idx + 1);
				if( semipos > 0 ) {
					tag = value.substr( idx + 1, semipos - 1 );
					if( 0 == xercesc::XMLString::compareIString( tag.data(), "amp" ) ) {
						retval.append( S_Amp );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "lt" ) ) {
						retval.append( S_Lt );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "gt" ) ) {
						retval.append( S_Gt );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "quot" ) ) {
						retval.append( S_Quot );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "squot" ) ) {
						retval.append( S_SQuot );
					}
					else {
						taglen = tag.length();
						tagidx = 0;
						while( ( tagidx < taglen ) && isxdigit( tag.at( tagidx ) ) ) {
							tagidx ++;
						}
						if( tagidx < taglen ) {
							retval.append( S_Amp );
							retval.append( tag );
							retval.append( S_Semi );
						}
						else {
							int ival;
							sscanf( tag.data(), "%x", &ival );
							chStr[0] = ival;
							retval.append( chStr );
						}
					}
					idx = idx + 1 + tag.length() + 1;
				}
				else {
					tag = value.substr( idx );
					retval.append( tag );
				}
			}
			else {
				chStr[0] = ch;
				retval.append( chStr );
			}
		}
		return( retval );
	}

	std::string CFLibXmlUtil::evalXmlStringWhitespacePreserve( const std::string& value ) {
		static const std::string S_ProcName( "evalXmlStringWhitespacePreserve" );
		static const std::string S_Amp( "&" );
		static const std::string S_Lt( "<" );
		static const std::string S_Gt( ">" );
		static const std::string S_Quot( "\"" );
		static const std::string S_SQuot( "'" );
		static const std::string S_Semi( ";" );

		std::string retval;
		std::string::size_type len = value.length();
		std::string::size_type idx = 0;
		char ch;
		char chStr[2];
		chStr[1] = '\000';
		std::string::size_type semipos;
		std::string tag;
		std::string::size_type taglen;
		std::string::size_type tagidx;
		while( idx < len ) {
			ch = value.at( idx );
			if( ch == '&' ) {
				semipos = value.find( ';', idx + 1);
				if( semipos > 0 ) {
					tag = value.substr( idx + 1, semipos - 1 );
					if( 0 == xercesc::XMLString::compareIString( tag.data(), "amp" ) ) {
						retval.append( S_Amp );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "lt" ) ) {
						retval.append( S_Lt );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "gt" ) ) {
						retval.append( S_Gt );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "quot" ) ) {
						retval.append( S_Quot );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "squot" ) ) {
						retval.append( S_SQuot );
					}
					else {
						taglen = tag.length();
						tagidx = 0;
						while( ( tagidx < taglen ) && isxdigit( tag.at( tagidx ) ) ) {
							tagidx ++;
						}
						if( tagidx < taglen ) {
							retval.append( S_Amp );
							retval.append( tag );
							retval.append( S_Semi );
						}
						else {
							int ival;
							sscanf( tag.data(), "%x", &ival );
							chStr[0] = ival;
							retval.append( chStr );
						}
					}
					idx = idx + 1 + tag.length() + 1;
				}
				else {
					tag = value.substr( idx );
					retval.append( tag );
				}
			}
			else {
				chStr[0] = ch;
				retval.append( chStr );
			}
		}
		return( retval );
	}

	std::string CFLibXmlUtil::evalXmlStringWhitespacePreserve( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "evalXmlStringWhitespacePreserve" );
		static const std::string S_Amp( "&" );
		static const std::string S_Lt( "<" );
		static const std::string S_Gt( ">" );
		static const std::string S_Quot( "\"" );
		static const std::string S_SQuot( "'" );
		static const std::string S_Semi( ";" );

		std::string retval;
		std::string::size_type len = value.length();
		std::string::size_type idx = 0;
		char ch;
		char chStr[2];
		chStr[1] = '\000';
		std::string::size_type semipos;
		std::string tag;
		std::string::size_type taglen;
		std::string::size_type tagidx;
		while( idx < len ) {
			ch = value.at( idx );
			if( ch == '&' ) {
				semipos = value.find( ';', idx + 1);
				if( semipos > 0 ) {
					tag = value.substr( idx + 1, semipos - 1 );
					if( 0 == xercesc::XMLString::compareIString( tag.data(), "amp" ) ) {
						retval.append( S_Amp );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "lt" ) ) {
						retval.append( S_Lt );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "gt" ) ) {
						retval.append( S_Gt );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "quot" ) ) {
						retval.append( S_Quot );
					}
					else if( 0 == xercesc::XMLString::compareIString( tag.data(), "squot" ) ) {
						retval.append( S_SQuot );
					}
					else {
						taglen = tag.length();
						tagidx = 0;
						while( ( tagidx < taglen ) && isxdigit( tag.at( tagidx ) ) ) {
							tagidx ++;
						}
						if( tagidx < taglen ) {
							retval.append( S_Amp );
							retval.append( tag );
							retval.append( S_Semi );
						}
						else {
							int ival;
							sscanf( tag.data(), "%x", &ival );
							chStr[0] = ival;
							retval.append( chStr );
						}
					}
					idx = idx + 1 + tag.length() + 1;
				}
				else {
					tag = value.substr( idx );
					retval.append( tag );
				}
			}
			else {
				chStr[0] = ch;
				retval.append( chStr );
			}
		}
		return( retval );
	}

	std::chrono::system_clock::time_point CFLibXmlUtil::evalDate( const std::string& value ) {
		static const std::string S_ProcName( "evalDate" );
		static const std::string S_InvalidFormat( "Invalid value format, must be YYYY-MM-DD, \"" );
		static const char S_PERCENT_D[3] = "%d";

		if( value.length() == 0 ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE );
		}

		if( value.length() != 10 ) {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				buff );
		}

		if( ! ( isdigit( value.at(0) )
				&& isdigit( value.at(1) )
				&& isdigit( value.at(2) )
				&& isdigit( value.at(3) )
				&& ( value.at(4) == '-' )
				&& isdigit( value.at(5) )
				&& isdigit( value.at(6) )
				&& ( value.at(7) == '-' )
				&& isdigit( value.at(8) )
				&& isdigit( value.at(9) ) ) )
		{
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				buff );
		}

		std::string strYear = value.substr( 0, 4 );
		std::string strMonth = value.substr( 5, 7 );
		std::string strDay = value.substr( 8, 10 );

		int iYear;
		int iMonth;
		int iDay;

		std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
		std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
		std::sscanf( strDay.data(), S_PERCENT_D, &iDay );

		iYear -= 1900;
		iMonth -= 1;

		struct tm tmRead = { 0 };
		tmRead.tm_year = iYear;
		tmRead.tm_mon = iMonth;
		tmRead.tm_mday = iDay;

#if !defined(_WINDOWS)
		tmRead.tm_gmtoff = 0L;
		tmRead.tm_zone = S_UTC;
#endif

		time_t timeRead = mktime( &tmRead );

		std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

		return( converted );
	}

	std::chrono::system_clock::time_point CFLibXmlUtil::evalDate( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "evalDate" );
		static const std::string S_InvalidFormat( "Invalid value format, must be YYYY-MM-DD, \"" );
		static const char S_PERCENT_D[3] = "%d";

		if( value.length() == 0 ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE );
		}

		if( value.length() != 10 ) {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				buff );
		}

		if( ! ( isdigit( value.at(0) )
				&& isdigit( value.at(1) )
				&& isdigit( value.at(2) )
				&& isdigit( value.at(3) )
				&& ( value.at(4) == '-' )
				&& isdigit( value.at(5) )
				&& isdigit( value.at(6) )
				&& ( value.at(7) == '-' )
				&& isdigit( value.at(8) )
				&& isdigit( value.at(9) ) ) )
		{
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				buff );
		}

		std::string strYear = value.substr( 0, 4 );
		std::string strMonth = value.substr( 5, 7 );
		std::string strDay = value.substr( 8, 10 );

		int iYear;
		int iMonth;
		int iDay;

		std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
		std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
		std::sscanf( strDay.data(), S_PERCENT_D, &iDay );

		iYear -= 1900;
		iMonth -= 1;

		struct tm tmRead = { 0 };
		tmRead.tm_year = iYear;
		tmRead.tm_mon = iMonth;
		tmRead.tm_mday = iDay;

#if !defined(_WINDOWS)
		tmRead.tm_gmtoff = 0L;
		tmRead.tm_zone = S_UTC;
#endif

		time_t timeRead = mktime( &tmRead );

		std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

		return( converted );
	}

	std::chrono::system_clock::time_point CFLibXmlUtil::evalTime( const std::string& value ) {
		static const std::string S_ProcName( "evalTime" );
		static const std::string S_InvalidFormat( "Invalid value format, must be HH:MI:SS, \"" );
		static const char S_PERCENT_D[3] = "%d";

		if( value.length() == 0 ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE );
		}

		if( value.length() != 8 ) {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				buff );
		}

		if( ! ( isdigit( value.at(0) )
				&& isdigit( value.at(1) )
				&& ( value.at(2) == ':' )
				&& isdigit( value.at(3) )
				&& isdigit( value.at(4) )
				&& ( value.at(5) == ':' )
				&& isdigit( value.at(6) )
				&& isdigit( value.at(7) ) ) )
		{
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				buff );
		}

		std::string strHour = value.substr( 0, 1 );
		std::string strMin = value.substr( 3, 4 );
		std::string strSec = value.substr( 6, 7 );

		int iHour;
		int iMin;
		int iSec;

		std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
		std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
		std::sscanf( strSec.data(), S_PERCENT_D, &iSec );

		struct tm tmRead = { 0 };
		tmRead.tm_year = 70;
		tmRead.tm_mon = 0;
		tmRead.tm_mday = 1;
		tmRead.tm_hour = iHour;
		tmRead.tm_min = iMin;
		tmRead.tm_sec = iSec;

#if !defined(_WINDOWS)
		tmRead.tm_gmtoff = 0L;
		tmRead.tm_zone = S_UTC;
#endif

		time_t timeRead = mktime( &tmRead );

		std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

		return( converted );
	}

	std::chrono::system_clock::time_point CFLibXmlUtil::evalTime( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "evalTime" );
		static const std::string S_InvalidFormat( "Invalid value format, must be HH:MI:SS, \"" );
		static const char S_PERCENT_D[3] = "%d";

		if( value.length() == 0 ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE );
		}

		if( value.length() != 8 ) {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				buff );
		}

		if( ! ( isdigit( value.at(0) )
				&& isdigit( value.at(1) )
				&& ( value.at(2) == ':' )
				&& isdigit( value.at(3) )
				&& isdigit( value.at(4) )
				&& ( value.at(5) == ':' )
				&& isdigit( value.at(6) )
				&& isdigit( value.at(7) ) ) )
		{
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				buff );
		}

		std::string strHour = value.substr( 0, 1 );
		std::string strMin = value.substr( 3, 4 );
		std::string strSec = value.substr( 6, 7 );

		int iHour;
		int iMin;
		int iSec;

		std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
		std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
		std::sscanf( strSec.data(), S_PERCENT_D, &iSec );

		struct tm tmRead = { 0 };
		tmRead.tm_year = 70;
		tmRead.tm_mon = 0;
		tmRead.tm_mday = 1;
		tmRead.tm_hour = iHour;
		tmRead.tm_min = iMin;
		tmRead.tm_sec = iSec;

#if !defined(_WINDOWS)
		tmRead.tm_gmtoff = 0L;
		tmRead.tm_zone = S_UTC;
#endif

		time_t timeRead = mktime( &tmRead );

		std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

		return( converted );
	}

	std::chrono::system_clock::time_point CFLibXmlUtil::evalTimestamp( const std::string& value ) {
		static const std::string S_ProcName( "evalTimestamp" );
		static const std::string S_InvalidFormat( "Invalid value format, must be YYYY-MM-DDTHH:MI:SS, \"" );
		static const char S_PERCENT_D[3] = "%d";

		if( value.length() == 0 ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE );
		}

		if( value.length() != 19 ) {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				buff );
		}

		if( ! ( isdigit( value.at(0) )
				&& isdigit( value.at(1) )
				&& isdigit( value.at(2) )
				&& isdigit( value.at(3) )
				&& ( value.at(4) == '-' )
				&& isdigit( value.at(5) )
				&& isdigit( value.at(6) )
				&& ( value.at(7) == '-' )
				&& isdigit( value.at(8) )
				&& isdigit( value.at(9) )
				&& ( value.at(10) == 'T' )
				&& isdigit( value.at(11) )
				&& isdigit( value.at(12) )
				&& ( value.at(13) == ':' )
				&& isdigit( value.at(14) )
				&& isdigit( value.at(15) )
				&& ( value.at(16) == ':' )
				&& isdigit( value.at(17) )
				&& isdigit( value.at(18) ) ) )
		{
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				buff );
		}

		std::string strYear = value.substr( 0, 4 );
		std::string strMonth = value.substr( 5, 7 );
		std::string strDay = value.substr( 8, 10 );
		std::string strHour = value.substr( 11, 13 );
		std::string strMin = value.substr( 14, 16 );
		std::string strSec = value.substr( 17, 19 );

		int iYear;
		int iMonth;
		int iDay;
		int iHour;
		int iMin;
		int iSec;

		std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
		std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
		std::sscanf( strDay.data(), S_PERCENT_D, &iDay );
		std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
		std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
		std::sscanf( strSec.data(), S_PERCENT_D, &iSec );

		iYear -= 1900;
		iMonth -= 1;
		if( iMonth == 12 ) {
			iYear++;
			iMonth = 0;
		}

		struct tm tmRead = { 0 };

		tmRead.tm_year = iYear;
		tmRead.tm_mon = iMonth;
		tmRead.tm_mday = iDay;
		tmRead.tm_hour = iHour;
		tmRead.tm_min = iMin;
		tmRead.tm_sec = iSec;

#if !defined(_WINDOWS)
		tmRead.tm_gmtoff = 0L;
		tmRead.tm_zone = S_UTC;
#endif

		time_t timeRead = mktime( &tmRead );

		std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

		return( converted );
	}

	std::chrono::system_clock::time_point CFLibXmlUtil::evalTimestamp( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "evalTimestamp" );
		static const std::string S_InvalidFormat( "Invalid value format, must be YYYY-MM-DDTHH:MI:SS, \"" );
		static const char S_PERCENT_D[3] = "%d";

		if( value.length() == 0 ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE );
		}

		if( value.length() != 19 ) {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				buff );
		}

		if( ! ( isdigit( value.at(0) )
				&& isdigit( value.at(1) )
				&& isdigit( value.at(2) )
				&& isdigit( value.at(3) )
				&& ( value.at(4) == '-' )
				&& isdigit( value.at(5) )
				&& isdigit( value.at(6) )
				&& ( value.at(7) == '-' )
				&& isdigit( value.at(8) )
				&& isdigit( value.at(9) )
				&& ( value.at(10) == 'T' )
				&& isdigit( value.at(11) )
				&& isdigit( value.at(12) )
				&& ( value.at(13) == ':' )
				&& isdigit( value.at(14) )
				&& isdigit( value.at(15) )
				&& ( value.at(16) == ':' )
				&& isdigit( value.at(17) )
				&& isdigit( value.at(18) ) ) )
		{
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				buff );
		}

		std::string strYear = value.substr( 0, 4 );
		std::string strMonth = value.substr( 5, 7 );
		std::string strDay = value.substr( 8, 10 );
		std::string strHour = value.substr( 11, 13 );
		std::string strMin = value.substr( 14, 16 );
		std::string strSec = value.substr( 17, 19 );

		int iYear;
		int iMonth;
		int iDay;
		int iHour;
		int iMin;
		int iSec;

		std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
		std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
		std::sscanf( strDay.data(), S_PERCENT_D, &iDay );
		std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
		std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
		std::sscanf( strSec.data(), S_PERCENT_D, &iSec );

		iYear -= 1900;
		iMonth -= 1;
		if( iMonth == 12 ) {
			iYear++;
			iMonth = 0;
		}

		struct tm tmRead = { 0 };

		tmRead.tm_year = iYear;
		tmRead.tm_mon = iMonth;
		tmRead.tm_mday = iDay;
		tmRead.tm_hour = iHour;
		tmRead.tm_min = iMin;
		tmRead.tm_sec = iSec;

#if !defined(_WINDOWS)
		tmRead.tm_gmtoff = 0L;
		tmRead.tm_zone = S_UTC;
#endif

		time_t timeRead = mktime( &tmRead );

		std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

		return( converted );
	}

	std::chrono::system_clock::time_point CFLibXmlUtil::evalTZDate( const std::string& value ) {
		static const std::string S_ProcName( "evalTZDate" );
		static const std::string S_InvalidFormat( "Invalid value format, must be YYYY-MM-DDZ or YYYY-MM-DD+HO:MO, \"" );
		static const char S_PERCENT_D[3] = "%d";

		if( value.length() == 0 ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE );
		}

		if( ( value.length() != 11 ) && ( value.length() != 16 ) ) {
			if( value.length() != 19 ) {
				std::string buff = * new std::string( S_InvalidFormat );
				buff.append( value );
				buff.append( S_IS_INVALID );
				throw CFLibInvalidArgumentException( CLASS_NAME,
					S_ProcName,
					1,
					S_VALUE,
					buff );
			}
		}

		if( ! ( isdigit( value.at(0) )
				&& isdigit( value.at(1) )
				&& isdigit( value.at(2) )
				&& isdigit( value.at(3) )
				&& ( value.at(4) == '-' )
				&& isdigit( value.at(5) )
				&& isdigit( value.at(6) )
				&& ( value.at(7) == '-' )
				&& isdigit( value.at(8) )
				&& isdigit( value.at(9) ) ) )
		{
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				buff );
		}

		std::chrono::system_clock::time_point converted;

		if( value.at( 10 ) == 'Z' ) {
			std::string strYear = value.substr( 0, 4 );
			std::string strMonth = value.substr( 5, 7 );
			std::string strDay = value.substr( 8, 10 );

			int iYear;
			int iMonth;
			int iDay;

			std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
			std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
			std::sscanf( strDay.data(), S_PERCENT_D, &iDay );

			iYear -= 1900;
			iMonth -= 1;

			struct tm tmRead = { 0 };
			tmRead.tm_year = iYear;
			tmRead.tm_mon = iMonth;
			tmRead.tm_mday = iDay;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = 0L;
			tmRead.tm_zone = S_UTC;
#endif

			time_t timeRead = mktime( &tmRead );

			converted = std::chrono::system_clock::from_time_t( timeRead );
		}
		else if( ( value.at( 10 ) == '-' )
			&& ( isdigit( value.at( 11 ) ) )
			&& ( isdigit( value.at( 12 ) ) )
			&& ( value.at( 13 ) == ':' )
			&& ( isdigit( value.at( 14 ) ) )
			&& ( isdigit( value.at( 15 ) ) ) )
		{
			std::string strYear = value.substr( 0, 4 );
			std::string strMonth = value.substr( 5, 7 );
			std::string strDay = value.substr( 8, 10 );
			std::string strTZHour = value.substr( 11, 12 );
			std::string strTZMin = value.substr( 14,15 );

			int iYear;
			int iMonth;
			int iDay;
			int iTZHour;
			int iTZMin;

			std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
			std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
			std::sscanf( strDay.data(), S_PERCENT_D, &iDay );
			std::sscanf( strTZHour.data(), S_PERCENT_D, &iTZHour );
			std::sscanf( strTZMin.data(), S_PERCENT_D, &iTZMin );

			iYear -= 1900;
			iMonth -= 1;

			struct tm tmRead = { 0 };
			tmRead.tm_year = iYear;
			tmRead.tm_mon = iMonth;
			tmRead.tm_mday = iDay;

			int iOffset = iTZHour * 60 * 60;
			iOffset += iTZMin * 60;

			iOffset = 0 - iOffset;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = iOffset;
			tmRead.tm_zone = NULL;
#endif

			time_t timeRead = mktime( &tmRead );

			converted = std::chrono::system_clock::from_time_t( timeRead );
		}
		else if( ( value.at( 10 ) == '+' )
			&& ( isdigit( value.at( 11 ) ) )
			&& ( isdigit( value.at( 12 ) ) )
			&& ( value.at( 13 ) == ':' )
			&& ( isdigit( value.at( 14 ) ) )
			&& ( isdigit( value.at( 15 ) ) ) )
		{
			std::string strYear = value.substr( 0, 4 );
			std::string strMonth = value.substr( 5, 7 );
			std::string strDay = value.substr( 8, 10 );
			std::string strTZHour = value.substr( 11, 12 );
			std::string strTZMin = value.substr( 14,15 );

			int iYear;
			int iMonth;
			int iDay;
			int iTZHour;
			int iTZMin;

			std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
			std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
			std::sscanf( strDay.data(), S_PERCENT_D, &iDay );
			std::sscanf( strTZHour.data(), S_PERCENT_D, &iTZHour );
			std::sscanf( strTZMin.data(), S_PERCENT_D, &iTZMin );

			iYear -= 1900;
			iMonth -= 1;

			struct tm tmRead = { 0 };
			tmRead.tm_year = iYear;
			tmRead.tm_mon = iMonth;
			tmRead.tm_mday = iDay;

			int iOffset = iTZHour * 60 * 60;
			iOffset += iTZMin * 60;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = iOffset;
			tmRead.tm_zone = NULL;
#endif

			time_t timeRead = mktime( &tmRead );

			converted = std::chrono::system_clock::from_time_t( timeRead );
		}
		else {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				buff );
		}

		return( converted );
	}

	std::chrono::system_clock::time_point CFLibXmlUtil::evalTZDate( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "evalTZDate" );
		static const std::string S_InvalidFormat( "Invalid value format, must be YYYY-MM-DDZ or YYYY-MM-DD+HO:MO, \"" );
		static const char S_PERCENT_D[3] = "%d";

		if( value.length() == 0 ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE );
		}

		if( ( value.length() != 11 ) && ( value.length() != 16 ) ) {
			if( value.length() != 19 ) {
				std::string buff = * new std::string( S_InvalidFormat );
				buff.append( value );
				buff.append( S_IS_INVALID );
				throw CFLibInvalidArgumentException( CLASS_NAME,
					S_ProcName,
					1,
					S_VALUE,
					buff );
			}
		}

		if( ( value.length() != 11 ) && ( value.length() != 16 ) ) {
			if( value.length() != 19 ) {
				std::string buff = * new std::string( S_InvalidFormat );
				buff.append( value );
				buff.append( S_IS_INVALID );
				throw CFLibInvalidArgumentException( CLASS_NAME,
					S_ProcName,
					1,
					fieldName,
					buff );
			}
		}

		if( ! ( isdigit( value.at(0) )
				&& isdigit( value.at(1) )
				&& isdigit( value.at(2) )
				&& isdigit( value.at(3) )
				&& ( value.at(4) == '-' )
				&& isdigit( value.at(5) )
				&& isdigit( value.at(6) )
				&& ( value.at(7) == '-' )
				&& isdigit( value.at(8) )
				&& isdigit( value.at(9) ) ) )
		{
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				buff );
		}

		std::chrono::system_clock::time_point converted;

		if( value.at( 10 ) == 'Z' ) {
			std::string strYear = value.substr( 0, 4 );
			std::string strMonth = value.substr( 5, 7 );
			std::string strDay = value.substr( 8, 10 );

			int iYear;
			int iMonth;
			int iDay;

			std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
			std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
			std::sscanf( strDay.data(), S_PERCENT_D, &iDay );

			iYear -= 1900;
			iMonth -= 1;

			struct tm tmRead = { 0 };
			tmRead.tm_year = iYear;
			tmRead.tm_mon = iMonth;
			tmRead.tm_mday = iDay;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = 0L;
			tmRead.tm_zone = S_UTC;
#endif

			time_t timeRead = mktime( &tmRead );

			converted = std::chrono::system_clock::from_time_t( timeRead );
		}
		else if( ( value.at( 10 ) == '-' )
			&& ( isdigit( value.at( 11 ) ) )
			&& ( isdigit( value.at( 12 ) ) )
			&& ( value.at( 13 ) == ':' )
			&& ( isdigit( value.at( 14 ) ) )
			&& ( isdigit( value.at( 15 ) ) ) )
		{
			std::string strYear = value.substr( 0, 4 );
			std::string strMonth = value.substr( 5, 7 );
			std::string strDay = value.substr( 8, 10 );
			std::string strTZHour = value.substr( 11, 12 );
			std::string strTZMin = value.substr( 14,15 );

			int iYear;
			int iMonth;
			int iDay;
			int iTZHour;
			int iTZMin;

			std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
			std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
			std::sscanf( strDay.data(), S_PERCENT_D, &iDay );
			std::sscanf( strTZHour.data(), S_PERCENT_D, &iTZHour );
			std::sscanf( strTZMin.data(), S_PERCENT_D, &iTZMin );

			iYear -= 1900;
			iMonth -= 1;

			struct tm tmRead = { 0 };
			tmRead.tm_year = iYear;
			tmRead.tm_mon = iMonth;
			tmRead.tm_mday = iDay;

			int iOffset = iTZHour * 60 * 60;
			iOffset += iTZMin * 60;

			iOffset = 0 - iOffset;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = iOffset;
			tmRead.tm_zone = NULL;
#endif

			time_t timeRead = mktime( &tmRead );

			converted = std::chrono::system_clock::from_time_t( timeRead );
		}
		else if( ( value.at( 10 ) == '+' )
			&& ( isdigit( value.at( 11 ) ) )
			&& ( isdigit( value.at( 12 ) ) )
			&& ( value.at( 13 ) == ':' )
			&& ( isdigit( value.at( 14 ) ) )
			&& ( isdigit( value.at( 15 ) ) ) )
		{
			std::string strYear = value.substr( 0, 4 );
			std::string strMonth = value.substr( 5, 7 );
			std::string strDay = value.substr( 8, 10 );
			std::string strTZHour = value.substr( 11, 12 );
			std::string strTZMin = value.substr( 14,15 );

			int iYear;
			int iMonth;
			int iDay;
			int iTZHour;
			int iTZMin;

			std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
			std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
			std::sscanf( strDay.data(), S_PERCENT_D, &iDay );
			std::sscanf( strTZHour.data(), S_PERCENT_D, &iTZHour );
			std::sscanf( strTZMin.data(), S_PERCENT_D, &iTZMin );

			iYear -= 1900;
			iMonth -= 1;

			struct tm tmRead = { 0 };
			tmRead.tm_year = iYear;
			tmRead.tm_mon = iMonth;
			tmRead.tm_mday = iDay;

			int iOffset = iTZHour * 60 * 60;
			iOffset += iTZMin * 60;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = iOffset;
			tmRead.tm_zone = NULL;
#endif

			time_t timeRead = mktime( &tmRead );

			converted = std::chrono::system_clock::from_time_t( timeRead );
		}
		else {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				buff );
		}

		return( converted );
	}

	std::chrono::system_clock::time_point CFLibXmlUtil::evalTZTime( const std::string& value ) {
		static const std::string S_ProcName( "evalTZTime" );
		static const std::string S_InvalidFormat( "Invalid value format, must be HH:MI:SSZ or HH:MI:SS+HO:MO, \"" );
		static const char S_PERCENT_D[3] = "%d";

		if( value.length() == 0 ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE );
		}

		if( ( value.length() != 9 ) && ( value.length() != 14 ) ) {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				buff );
		}

		if( ! ( isdigit( value.at(0) )
				&& isdigit( value.at(1) )
				&& ( value.at(2) == ':' )
				&& isdigit( value.at(3) )
				&& isdigit( value.at(4) )
				&& ( value.at(5) == ':' )
				&& isdigit( value.at(6) )
				&& isdigit( value.at(7) ) ) )
		{
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				buff );
		}

		std::chrono::system_clock::time_point converted;

		if( value.at( 8 ) == 'Z' ) {
			std::string strHour = value.substr( 0, 1 );
			std::string strMin = value.substr( 3, 4 );
			std::string strSec = value.substr( 6, 7 );

			int iHour;
			int iMin;
			int iSec;

			std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
			std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
			std::sscanf( strSec.data(), S_PERCENT_D, &iSec );

			struct tm tmRead = { 0 };
			tmRead.tm_hour = iHour;
			tmRead.tm_min = iMin;
			tmRead.tm_sec = iSec;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = 0L;
			tmRead.tm_zone = S_UTC;
#endif

			time_t timeRead = mktime( &tmRead );

			converted = std::chrono::system_clock::from_time_t( timeRead );
		}
		else if( ( value.at( 8 ) == '-' )
			&& ( isdigit( value.at( 9 ) ) )
			&& ( isdigit( value.at( 10 ) ) )
			&& ( value.at( 11 ) == ':' )
			&& ( isdigit( value.at( 12 ) ) )
			&& ( isdigit( value.at( 13 ) ) ) )
		{
			std::string strHour = value.substr( 0, 1 );
			std::string strMin = value.substr( 3, 4 );
			std::string strSec = value.substr( 6, 7 );
			std::string strTZHour = value.substr( 9, 10 );
			std::string strTZMin = value.substr( 12, 13 );

			int iHour;
			int iMin;
			int iSec;
			int iTZHour;
			int iTZMin;

			std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
			std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
			std::sscanf( strSec.data(), S_PERCENT_D, &iSec );
			std::sscanf( strTZHour.data(), S_PERCENT_D, &iTZHour );
			std::sscanf( strTZMin.data(), S_PERCENT_D, &iTZMin );

			struct tm tmRead = { 0 };
			tmRead.tm_hour = iHour;
			tmRead.tm_min = iMin;
			tmRead.tm_sec = iSec;

			int iOffset = iTZHour * 60 * 60;
			iOffset += iTZMin * 60;

			iOffset = 0 - iOffset;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = iOffset;
			tmRead.tm_zone = NULL;
#endif

			time_t timeRead = mktime( &tmRead );

			converted = std::chrono::system_clock::from_time_t( timeRead );
		}
		else if( ( value.at( 8 ) == '+' )
				&& ( isdigit( value.at( 9 ) ) )
				&& ( isdigit( value.at( 10 ) ) )
				&& ( value.at( 11 ) == ':' )
				&& ( isdigit( value.at( 12 ) ) )
				&& ( isdigit( value.at( 13 ) ) ) )
		{
			std::string strHour = value.substr( 0, 1 );
			std::string strMin = value.substr( 3, 4 );
			std::string strSec = value.substr( 6, 7 );
			std::string strTZHour = value.substr( 9, 10 );
			std::string strTZMin = value.substr( 12, 13 );

			int iHour;
			int iMin;
			int iSec;
			int iTZHour;
			int iTZMin;

			std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
			std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
			std::sscanf( strSec.data(), S_PERCENT_D, &iSec );
			std::sscanf( strTZHour.data(), S_PERCENT_D, &iTZHour );
			std::sscanf( strTZMin.data(), S_PERCENT_D, &iTZMin );

			struct tm tmRead = { 0 };
			tmRead.tm_hour = iHour;
			tmRead.tm_min = iMin;
			tmRead.tm_sec = iSec;

			int iOffset = iTZHour * 60 * 60;
			iOffset += iTZMin * 60;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = iOffset;
			tmRead.tm_zone = NULL;
#endif

			time_t timeRead = mktime( &tmRead );

			converted = std::chrono::system_clock::from_time_t( timeRead );
		}
		else {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				buff );
		}

		return( converted );
	}

	std::chrono::system_clock::time_point CFLibXmlUtil::evalTZTime( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "evalTZTime" );
		static const std::string S_InvalidFormat( "Invalid value format, must be HH:MI:SSZ or HH:MI:SS+HO:MO, \"" );
		static const char S_PERCENT_D[3] = "%d";

		if( value.length() == 0 ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE );
		}

		if( ( value.length() != 9 ) && ( value.length() != 14 ) ) {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				buff );
		}

		if( ! ( isdigit( value.at(0) )
				&& isdigit( value.at(1) )
				&& ( value.at(2) == ':' )
				&& isdigit( value.at(3) )
				&& isdigit( value.at(4) )
				&& ( value.at(5) == ':' )
				&& isdigit( value.at(6) )
				&& isdigit( value.at(7) ) ) )
		{
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				buff );
		}

		std::chrono::system_clock::time_point converted;

		if( value.at( 8 ) == 'Z' ) {
			std::string strHour = value.substr( 0, 1 );
			std::string strMin = value.substr( 3, 4 );
			std::string strSec = value.substr( 6, 7 );

			int iHour;
			int iMin;
			int iSec;

			std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
			std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
			std::sscanf( strSec.data(), S_PERCENT_D, &iSec );

			struct tm tmRead = { 0 };
			tmRead.tm_hour = iHour;
			tmRead.tm_min = iMin;
			tmRead.tm_sec = iSec;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = 0L;
			tmRead.tm_zone = S_UTC;
#endif

			time_t timeRead = mktime( &tmRead );

			converted = std::chrono::system_clock::from_time_t( timeRead );
		}
		else if( ( value.at( 8 ) == '-' )
			&& ( isdigit( value.at( 9 ) ) )
			&& ( isdigit( value.at( 10 ) ) )
			&& ( value.at( 11 ) == ':' )
			&& ( isdigit( value.at( 12 ) ) )
			&& ( isdigit( value.at( 13 ) ) ) )
		{
			std::string strHour = value.substr( 0, 1 );
			std::string strMin = value.substr( 3, 4 );
			std::string strSec = value.substr( 6, 7 );
			std::string strTZHour = value.substr( 9, 10 );
			std::string strTZMin = value.substr( 12, 13 );

			int iHour;
			int iMin;
			int iSec;
			int iTZHour;
			int iTZMin;

			std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
			std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
			std::sscanf( strSec.data(), S_PERCENT_D, &iSec );
			std::sscanf( strTZHour.data(), S_PERCENT_D, &iTZHour );
			std::sscanf( strTZMin.data(), S_PERCENT_D, &iTZMin );

			struct tm tmRead = { 0 };
			tmRead.tm_hour = iHour;
			tmRead.tm_min = iMin;
			tmRead.tm_sec = iSec;

			int iOffset = iTZHour * 60 * 60;
			iOffset += iTZMin * 60;

			iOffset = 0 - iOffset;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = iOffset;
			tmRead.tm_zone = NULL;
#endif

			time_t timeRead = mktime( &tmRead );

			converted = std::chrono::system_clock::from_time_t( timeRead );
		}
		else if( ( value.at( 8 ) == '+' )
				&& ( isdigit( value.at( 9 ) ) )
				&& ( isdigit( value.at( 10 ) ) )
				&& ( value.at( 11 ) == ':' )
				&& ( isdigit( value.at( 12 ) ) )
				&& ( isdigit( value.at( 13 ) ) ) )
		{
			std::string strHour = value.substr( 0, 1 );
			std::string strMin = value.substr( 3, 4 );
			std::string strSec = value.substr( 6, 7 );
			std::string strTZHour = value.substr( 9, 10 );
			std::string strTZMin = value.substr( 12, 13 );

			int iHour;
			int iMin;
			int iSec;
			int iTZHour;
			int iTZMin;

			std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
			std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
			std::sscanf( strSec.data(), S_PERCENT_D, &iSec );
			std::sscanf( strTZHour.data(), S_PERCENT_D, &iTZHour );
			std::sscanf( strTZMin.data(), S_PERCENT_D, &iTZMin );

			struct tm tmRead = { 0 };
			tmRead.tm_hour = iHour;
			tmRead.tm_min = iMin;
			tmRead.tm_sec = iSec;

			int iOffset = iTZHour * 60 * 60;
			iOffset += iTZMin * 60;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = iOffset;
			tmRead.tm_zone = NULL;
#endif

			time_t timeRead = mktime( &tmRead );

			converted = std::chrono::system_clock::from_time_t( timeRead );
		}
		else {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				buff );
		}

		return( converted );
	}

	std::chrono::system_clock::time_point CFLibXmlUtil::evalTZTimestamp( const std::string& value ) {
		static const std::string S_ProcName( "evalTZTimestamp" );
		static const std::string S_InvalidFormat( "Invalid value format, must be YYYY-MM-DDTHH:MI:SSZ or YYYY-MM-DDTHH:MI:SS+HO:MO, \"" );
		static const char S_PERCENT_D[3] = "%d";

		if( value.length() == 0 ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE );
		}

		if( ( value.length() != 20 ) && ( value.length() != 25 ) ) {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				buff );
		}

		if( ! ( isdigit( value.at(0) )
				&& isdigit( value.at(1) )
				&& isdigit( value.at(2) )
				&& isdigit( value.at(3) )
				&& ( value.at(4) == '-' )
				&& isdigit( value.at(5) )
				&& isdigit( value.at(6) )
				&& ( value.at(7) == '-' )
				&& isdigit( value.at(8) )
				&& isdigit( value.at(9) )
				&& ( value.at(10) == 'T' )
				&& isdigit( value.at(11) )
				&& isdigit( value.at(12) )
				&& ( value.at(13) == ':' )
				&& isdigit( value.at(14) )
				&& isdigit( value.at(15) )
				&& ( value.at(16) == ':' )
				&& isdigit( value.at(17) )
				&& isdigit( value.at(18) ) ) )
		{
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				buff );
		}

		std::chrono::system_clock::time_point converted;

		if( value.at( 19 ) == 'Z' ) {
			std::string strYear = value.substr( 0, 4 );
			std::string strMonth = value.substr( 5, 7 );
			std::string strDay = value.substr( 8, 10 );
			std::string strHour = value.substr( 11, 13 );
			std::string strMin = value.substr( 14, 16 );
			std::string strSec = value.substr( 17, 19 );

			int iYear;
			int iMonth;
			int iDay;
			int iHour;
			int iMin;
			int iSec;

			std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
			std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
			std::sscanf( strDay.data(), S_PERCENT_D, &iDay );
			std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
			std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
			std::sscanf( strSec.data(), S_PERCENT_D, &iSec );

			iYear -= 1900;
			iMonth -= 1;
			if( iMonth == 12 ) {
				iYear++;
				iMonth = 0;
			}

			struct tm tmRead = { 0 };

			tmRead.tm_year = iYear;
			tmRead.tm_mon = iMonth;
			tmRead.tm_mday = iDay;
			tmRead.tm_hour = iHour;
			tmRead.tm_min = iMin;
			tmRead.tm_sec = iSec;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = 0L;
			tmRead.tm_zone = S_UTC;
#endif

			time_t timeRead = mktime( &tmRead );

			converted = std::chrono::system_clock::from_time_t( timeRead );
		}
		else if( ( value.at( 19 ) == '-' )
			&& ( isdigit( value.at( 20 ) ) )
			&& ( isdigit( value.at( 21 ) ) )
			&& ( value.at( 22 ) == ':' )
			&& ( isdigit( value.at( 23 ) ) )
			&& ( isdigit( value.at( 24 ) ) ) )
		{
			std::string strYear = value.substr( 0, 4 );
			std::string strMonth = value.substr( 5, 7 );
			std::string strDay = value.substr( 8, 10 );
			std::string strHour = value.substr( 11, 13 );
			std::string strMin = value.substr( 14, 16 );
			std::string strSec = value.substr( 17, 19 );
			std::string strTZHour = value.substr( 20, 21 );
			std::string strTZMin = value.substr( 23, 24 );

			int iYear;
			int iMonth;
			int iDay;
			int iHour;
			int iMin;
			int iSec;
			int iTZHour;
			int iTZMin;

			std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
			std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
			std::sscanf( strDay.data(), S_PERCENT_D, &iDay );
			std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
			std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
			std::sscanf( strSec.data(), S_PERCENT_D, &iSec );
			std::sscanf( strTZHour.data(), S_PERCENT_D, &iTZHour );
			std::sscanf( strTZMin.data(), S_PERCENT_D, &iTZMin );

			iYear -= 1900;
			iMonth -= 1;
			if( iMonth == 12 ) {
				iYear++;
				iMonth = 0;
			}

			struct tm tmRead = { 0 };

			tmRead.tm_year = iYear;
			tmRead.tm_mon = iMonth;
			tmRead.tm_mday = iDay;
			tmRead.tm_hour = iHour;
			tmRead.tm_min = iMin;
			tmRead.tm_sec = iSec;

			int iOffset = iTZHour * 60 * 60;
			iOffset += iTZMin * 60;

			iOffset = 0 - iOffset;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = iOffset;
			tmRead.tm_zone = NULL;
#endif

			time_t timeRead = mktime( &tmRead );

			converted = std::chrono::system_clock::from_time_t( timeRead );
		}
		else if( ( value.at( 19 ) == '+' )
				&& ( isdigit( value.at( 20 ) ) )
				&& ( isdigit( value.at( 21 ) ) )
				&& ( value.at( 22 ) == ':' )
				&& ( isdigit( value.at( 23 ) ) )
				&& ( isdigit( value.at( 24 ) ) ) )
		{
			std::string strYear = value.substr( 0, 4 );
			std::string strMonth = value.substr( 5, 7 );
			std::string strDay = value.substr( 8, 10 );
			std::string strHour = value.substr( 11, 13 );
			std::string strMin = value.substr( 14, 16 );
			std::string strSec = value.substr( 17, 19 );
			std::string strTZHour = value.substr( 20, 21 );
			std::string strTZMin = value.substr( 23, 24 );

			int iYear;
			int iMonth;
			int iDay;
			int iHour;
			int iMin;
			int iSec;
			int iTZHour;
			int iTZMin;

			std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
			std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
			std::sscanf( strDay.data(), S_PERCENT_D, &iDay );
			std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
			std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
			std::sscanf( strSec.data(), S_PERCENT_D, &iSec );
			std::sscanf( strTZHour.data(), S_PERCENT_D, &iTZHour );
			std::sscanf( strTZMin.data(), S_PERCENT_D, &iTZMin );

			iYear -= 1900;
			iMonth -= 1;
			if( iMonth == 12 ) {
				iYear++;
				iMonth = 0;
			}

			struct tm tmRead = { 0 };

			tmRead.tm_year = iYear;
			tmRead.tm_mon = iMonth;
			tmRead.tm_mday = iDay;
			tmRead.tm_hour = iHour;
			tmRead.tm_min = iMin;
			tmRead.tm_sec = iSec;

			int iOffset = iTZHour * 60 * 60;
			iOffset += iTZMin * 60;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = iOffset;
			tmRead.tm_zone = NULL;
#endif

			time_t timeRead = mktime( &tmRead );

			converted = std::chrono::system_clock::from_time_t( timeRead );
		}
		else {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE,
				buff );
		}

		return( converted );
	}

	std::chrono::system_clock::time_point CFLibXmlUtil::evalTZTimestamp( const std::string& fieldName, const std::string& value ) {
		static const std::string S_ProcName( "evalTZTimestamp" );
		static const std::string S_InvalidFormat( "Invalid value format, must be YYYY-MM-DDTHH:MI:SSZ or YYYY-MM-DDTHH:MI:SS+HO:MO, \"" );
		static const char S_PERCENT_D[3] = "%d";

		if( value.length() == 0 ) {
			throw CFLibNullArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_VALUE );
		}

		if( ( value.length() != 20 ) && ( value.length() != 25 ) ) {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				buff );
		}

		if( ! ( isdigit( value.at(0) )
				&& isdigit( value.at(1) )
				&& isdigit( value.at(2) )
				&& isdigit( value.at(3) )
				&& ( value.at(4) == '-' )
				&& isdigit( value.at(5) )
				&& isdigit( value.at(6) )
				&& ( value.at(7) == '-' )
				&& isdigit( value.at(8) )
				&& isdigit( value.at(9) )
				&& ( value.at(10) == 'T' )
				&& isdigit( value.at(11) )
				&& isdigit( value.at(12) )
				&& ( value.at(13) == ':' )
				&& isdigit( value.at(14) )
				&& isdigit( value.at(15) )
				&& ( value.at(16) == ':' )
				&& isdigit( value.at(17) )
				&& isdigit( value.at(18) ) ) )
		{
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				buff );
		}

		std::chrono::system_clock::time_point converted;

		if( value.at( 19 ) == 'Z' ) {
			std::string strYear = value.substr( 0, 4 );
			std::string strMonth = value.substr( 5, 7 );
			std::string strDay = value.substr( 8, 10 );
			std::string strHour = value.substr( 11, 13 );
			std::string strMin = value.substr( 14, 16 );
			std::string strSec = value.substr( 17, 19 );

			int iYear;
			int iMonth;
			int iDay;
			int iHour;
			int iMin;
			int iSec;

			std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
			std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
			std::sscanf( strDay.data(), S_PERCENT_D, &iDay );
			std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
			std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
			std::sscanf( strSec.data(), S_PERCENT_D, &iSec );

			iYear -= 1900;
			iMonth -= 1;
			if( iMonth == 12 ) {
				iYear++;
				iMonth = 0;
			}

			struct tm tmRead = { 0 };

			tmRead.tm_year = iYear;
			tmRead.tm_mon = iMonth;
			tmRead.tm_mday = iDay;
			tmRead.tm_hour = iHour;
			tmRead.tm_min = iMin;
			tmRead.tm_sec = iSec;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = 0L;
			tmRead.tm_zone = S_UTC;
#endif

			time_t timeRead = mktime( &tmRead );

			converted = std::chrono::system_clock::from_time_t( timeRead );
		}
		else if( ( value.at( 19 ) == '-' )
			&& ( isdigit( value.at( 20 ) ) )
			&& ( isdigit( value.at( 21 ) ) )
			&& ( value.at( 22 ) == ':' )
			&& ( isdigit( value.at( 23 ) ) )
			&& ( isdigit( value.at( 24 ) ) ) )
		{
			std::string strYear = value.substr( 0, 4 );
			std::string strMonth = value.substr( 5, 7 );
			std::string strDay = value.substr( 8, 10 );
			std::string strHour = value.substr( 11, 13 );
			std::string strMin = value.substr( 14, 16 );
			std::string strSec = value.substr( 17, 19 );
			std::string strTZHour = value.substr( 20, 21 );
			std::string strTZMin = value.substr( 23, 24 );

			int iYear;
			int iMonth;
			int iDay;
			int iHour;
			int iMin;
			int iSec;
			int iTZHour;
			int iTZMin;

			std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
			std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
			std::sscanf( strDay.data(), S_PERCENT_D, &iDay );
			std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
			std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
			std::sscanf( strSec.data(), S_PERCENT_D, &iSec );
			std::sscanf( strTZHour.data(), S_PERCENT_D, &iTZHour );
			std::sscanf( strTZMin.data(), S_PERCENT_D, &iTZMin );

			iYear -= 1900;
			iMonth -= 1;
			if( iMonth == 12 ) {
				iYear++;
				iMonth = 0;
			}

			struct tm tmRead = { 0 };

			tmRead.tm_year = iYear;
			tmRead.tm_mon = iMonth;
			tmRead.tm_mday = iDay;
			tmRead.tm_hour = iHour;
			tmRead.tm_min = iMin;
			tmRead.tm_sec = iSec;

			int iOffset = iTZHour * 60 * 60;
			iOffset += iTZMin * 60;

			iOffset = 0 - iOffset;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = iOffset;
			tmRead.tm_zone = NULL;
#endif

			time_t timeRead = mktime( &tmRead );

			converted = std::chrono::system_clock::from_time_t( timeRead );
		}
		else if( ( value.at( 19 ) == '+' )
				&& ( isdigit( value.at( 20 ) ) )
				&& ( isdigit( value.at( 21 ) ) )
				&& ( value.at( 22 ) == ':' )
				&& ( isdigit( value.at( 23 ) ) )
				&& ( isdigit( value.at( 24 ) ) ) )
		{
			std::string strYear = value.substr( 0, 4 );
			std::string strMonth = value.substr( 5, 7 );
			std::string strDay = value.substr( 8, 10 );
			std::string strHour = value.substr( 11, 13 );
			std::string strMin = value.substr( 14, 16 );
			std::string strSec = value.substr( 17, 19 );
			std::string strTZHour = value.substr( 20, 21 );
			std::string strTZMin = value.substr( 23, 24 );

			int iYear;
			int iMonth;
			int iDay;
			int iHour;
			int iMin;
			int iSec;
			int iTZHour;
			int iTZMin;

			std::sscanf( strYear.data(), S_PERCENT_D, &iYear );
			std::sscanf( strMonth.data(), S_PERCENT_D, &iMonth );
			std::sscanf( strDay.data(), S_PERCENT_D, &iDay );
			std::sscanf( strHour.data(), S_PERCENT_D, &iHour );
			std::sscanf( strMin.data(), S_PERCENT_D, &iMin );
			std::sscanf( strSec.data(), S_PERCENT_D, &iSec );
			std::sscanf( strTZHour.data(), S_PERCENT_D, &iTZHour );
			std::sscanf( strTZMin.data(), S_PERCENT_D, &iTZMin );

			iYear -= 1900;
			iMonth -= 1;
			if( iMonth == 12 ) {
				iYear++;
				iMonth = 0;
			}

			struct tm tmRead = { 0 };

			tmRead.tm_year = iYear;
			tmRead.tm_mon = iMonth;
			tmRead.tm_mday = iDay;
			tmRead.tm_hour = iHour;
			tmRead.tm_min = iMin;
			tmRead.tm_sec = iSec;

			int iOffset = iTZHour * 60 * 60;
			iOffset += iTZMin * 60;

#if !defined(_WINDOWS)
			tmRead.tm_gmtoff = iOffset;
			tmRead.tm_zone = NULL;
#endif

			time_t timeRead = mktime( &tmRead );

			converted = std::chrono::system_clock::from_time_t( timeRead );
		}
		else {
			std::string buff = * new std::string( S_InvalidFormat );
			buff.append( value );
			buff.append( S_IS_INVALID );
			throw CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				fieldName,
				buff );
		}

		return( converted );
	}

	std::string CFLibXmlUtil::formatBoolean( const bool val ) {
		static const std::string S_False( "false" );
		static const std::string S_True( "true" );

		std::string retval;
		if( val ) {
			retval = std::string( S_True );
		}
		else {
			retval = std::string( S_False );
		}
		return( retval );
	}

	std::string CFLibXmlUtil::formatBlob( const std::vector<BYTE>& val ) {
		std::string strEncoded = CFLib::base64_encode( val.data(), (unsigned int)( val.size() ) );
		return( strEncoded );
	}

	std::string CFLibXmlUtil::formatInt16( const std::int16_t val ) {
		std::string str = std::to_string( val );
		std::string retval( str.c_str() );
		return( retval );
	}

	std::string CFLibXmlUtil::formatInt32( const std::int32_t val ) {
		std::string str = std::to_string( val );
		std::string retval( str.c_str() );
		return( retval );
	}

	std::string CFLibXmlUtil::formatInt64( const std::int64_t val ) {
		std::string str = std::to_string( val );
		std::string retval( str.c_str() );
		return( retval );
	}

	std::string CFLibXmlUtil::formatUInt16( const std::uint16_t val ) {
		std::string str = std::to_string( val );
		std::string retval( str.c_str() );
		return( retval );
	}

	std::string CFLibXmlUtil::formatUInt32( const std::uint32_t val ) {
		std::string str = std::to_string( val );
		std::string retval( str.c_str() );
		return( retval );
	}

	std::string CFLibXmlUtil::formatUInt64( const std::uint64_t val ) {
		std::string str = std::to_string( val );
		std::string retval( str.c_str() );
		return( retval );
	}

	std::string CFLibXmlUtil::formatFloat( const float val ) {
		char buff[256] = {0};
		snprintf( &buff[0], 256, "%1.99f", val );
		std::string::size_type len = strlen( &buff[0] );
		while( ( len > 0 ) && ( buff[len-1] == '0' ) ) {
			buff[len-1] = '\000';
			len --;
		}
		std::string retval( buff  );
		return( retval );
	}

	std::string CFLibXmlUtil::formatDouble( const double val ) {
		char buff[256] = {0};
		snprintf( &buff[0], 256, "%1.99f", val );
		std::string::size_type len = strlen( &buff[0] );
		while( ( len > 0 ) && ( buff[len-1] == '0' ) ) {
			buff[len-1] = '\000';
			len --;
		}
		std::string retval( buff  );
		return( retval );
	}

	std::string CFLibXmlUtil::formatMPFR( const mpfr_t& val ) {
		static const std::string S_BuffFormat( "%RNf" );
		char buffValue[CFLibGenericBigDecimal::MAX_DIGITS+CFLibGenericBigDecimal::MAX_DIGITS+4];
		mpfr_snprintf( buffValue, CFLibGenericBigDecimal::MAX_DIGITS+CFLibGenericBigDecimal::MAX_DIGITS, S_BuffFormat.c_str(), val );
		std::string mpfrValue( buffValue );
		return( mpfrValue );
	}

	std::string CFLibXmlUtil::formatMPFR( mpfr_srcptr val ) {
		static const std::string S_BuffFormat( "%RNf" );
		char buffValue[CFLibGenericBigDecimal::MAX_DIGITS+CFLibGenericBigDecimal::MAX_DIGITS+4];
		mpfr_snprintf( buffValue, CFLibGenericBigDecimal::MAX_DIGITS+CFLibGenericBigDecimal::MAX_DIGITS, S_BuffFormat.c_str(), val );
		std::string mpfrValue( buffValue );
		return( mpfrValue );
	}

	std::string CFLibXmlUtil::formatXmlString( const std::string& str ) {
		static const std::string S_ProcName( "formatXmlString" );
		static const std::string S_Unicode10( "&#10;" );
		static const std::string S_Unicode13( "&#13;" );
		static const std::string S_APos( "&apos;" );
		static const std::string S_Quot( "&quot;" );
		static const std::string S_Amp( "&" );
		static const std::string S_Lt( "&lt;" );
		static const std::string S_Gt( "&gt;" );

		std::string buff;
		char ch;
		std::string::size_type idx;
		std::string::size_type len = str.length();
		for( idx = 0; idx < len; idx ++ ) {
			ch = str.at( idx );
			switch( ch ) {
				case '\n':
					buff.append( S_Unicode10 );
					break;
				case '\r':
					buff.append( S_Unicode13 );
					break;
				case ' ':
				case '\t':
				case '@':
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
				case 'a':
				case 'b':
				case 'c':
				case 'd':
				case 'e':
				case 'f':
				case 'g':
				case 'h':
				case 'i':
				case 'j':
				case 'k':
				case 'l':
				case 'm':
				case 'n':
				case 'o':
				case 'p':
				case 'q':
				case 'r':
				case 's':
				case 't':
				case 'u':
				case 'v':
				case 'w':
				case 'x':
				case 'y':
				case 'z':
				case 'A':
				case 'B':
				case 'C':
				case 'D':
				case 'E':
				case 'F':
				case 'G':
				case 'H':
				case 'I':
				case 'J':
				case 'K':
				case 'L':
				case 'M':
				case 'N':
				case 'O':
				case 'P':
				case 'Q':
				case 'R':
				case 'S':
				case 'T':
				case 'U':
				case 'V':
				case 'W':
				case 'X':
				case 'Y':
				case 'Z':
				case '~':
				case '!':
				case '#':
				case '$':
				case '%':
				case '^':
				case '*':
				case '(':
				case ')':
				case '-':
				case '_':
				case '+':
				case '=':
				case '{':
				case '}':
				case '[':
				case ']':
				case ':':
				case ';':
				case ',':
				case '.':
				case '?':
				case '/':
				case '\\':
				case '|':
					char cstr[2];
					cstr[0] = ch;
					cstr[1] = '\000';
					buff.append( &cstr[0] );
					break;
				case '\'':
					buff.append( S_APos );
					break;
				case '"':
					buff.append( S_Quot );
					break;
				case '&':
					buff.append( S_Amp );
					break;
				case '<':
					buff.append( S_Lt );
					break;
				case '>':
					buff.append( S_Gt );
					break;
				default:
					int charCode = (int)ch;
					std::string* seq = new std::string();
					seq->append( "&#" );
					std::string strCharCode = std::to_string( charCode );
					seq->append( strCharCode );
					seq->append( ";" );
					std::string strSeq( *seq );
					buff.append( strSeq );
					delete seq;
					seq = NULL;
					break;
			}
		}

		return( buff );
	}

	std::string CFLibXmlUtil::formatXmlStringWhitespacePreserve( const std::string& str ) {
		static const std::string S_ProcName( "formatXmlStringWhitespacePreserve" );
		static const std::string S_APos( "&apos;" );
		static const std::string S_Quot( "&quot;" );
		static const std::string S_Amp( "&" );
		static const std::string S_Lt( "&lt;" );
		static const std::string S_Gt( "&gt;" );

		std::string buff;
		char ch;
		std::string::size_type idx;
		std::string::size_type len = str.length();
		char cstr[2];

		for( idx = 0; idx < len; idx ++ ) {
			ch = str.at( idx );
			switch( ch ) {
				case '\n':
				case '\r':
				case ' ':
				case '\t':
				case '@':
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
				case 'a':
				case 'b':
				case 'c':
				case 'd':
				case 'e':
				case 'f':
				case 'g':
				case 'h':
				case 'i':
				case 'j':
				case 'k':
				case 'l':
				case 'm':
				case 'n':
				case 'o':
				case 'p':
				case 'q':
				case 'r':
				case 's':
				case 't':
				case 'u':
				case 'v':
				case 'w':
				case 'x':
				case 'y':
				case 'z':
				case 'A':
				case 'B':
				case 'C':
				case 'D':
				case 'E':
				case 'F':
				case 'G':
				case 'H':
				case 'I':
				case 'J':
				case 'K':
				case 'L':
				case 'M':
				case 'N':
				case 'O':
				case 'P':
				case 'Q':
				case 'R':
				case 'S':
				case 'T':
				case 'U':
				case 'V':
				case 'W':
				case 'X':
				case 'Y':
				case 'Z':
				case '~':
				case '!':
				case '#':
				case '$':
				case '%':
				case '^':
				case '*':
				case '(':
				case ')':
				case '-':
				case '_':
				case '+':
				case '=':
				case '{':
				case '}':
				case '[':
				case ']':
				case ':':
				case ';':
				case ',':
				case '.':
				case '?':
				case '/':
				case '\\':
				case '|':
					cstr[0] = ch;
					cstr[1] = '\000';
					buff.append( &cstr[0] );
					break;
				case '\'':
					buff.append( S_APos );
					break;
				case '"':
					buff.append( S_Quot );
					break;
				case '&':
					buff.append( S_Amp );
					break;
				case '<':
					buff.append( S_Lt );
					break;
				case '>':
					buff.append( S_Gt );
					break;
				default:
					int charCode = (int)ch;
					std::string* seq = new std::string();
					seq->append( "&#" );
					std::string strCharCode = std::to_string( charCode );
					seq->append( strCharCode );
					seq->append( ";" );
					std::string strSeq( *seq );
					buff.append( strSeq );
					delete seq;
					seq = NULL;
					break;
			}
		}

		return( buff );
	}

	std::string CFLibXmlUtil::formatDate( const std::chrono::system_clock::time_point& cal ) {
		std::time_t time = std::chrono::system_clock::to_time_t( cal );
		std::tm utc = *std::localtime( &time );
		char strbuff[12] = {0};
		strftime( &strbuff[0], sizeof(strbuff), "%Y-%m-%d", &utc );
		std::string retval( strbuff );
		return( retval );
	}

	std::string CFLibXmlUtil::formatTime( const std::chrono::system_clock::time_point& cal ) {
		std::time_t time = std::chrono::system_clock::to_time_t( cal );
		std::tm utc = *std::localtime( &time );
		char strbuff[10] = {0};
		strftime( &strbuff[0], sizeof(strbuff), "%H:%M:%S", &utc );
		std::string retval( strbuff );
		return( retval );
	}

	std::string CFLibXmlUtil::formatTimestamp( const std::chrono::system_clock::time_point& cal ) {
		std::time_t time = std::chrono::system_clock::to_time_t( cal );
		std::tm utc = *std::localtime( &time );
		char strbuff[20] = {0};
		strftime( &strbuff[0], sizeof(strbuff), "%Y-%m-%dT%H:%M:%S", &utc );
		std::string retval( strbuff );
		return( retval );
	}

	std::string CFLibXmlUtil::formatTZDate( const std::chrono::system_clock::time_point& cal ) {
		std::time_t time = std::chrono::system_clock::to_time_t( cal );
		std::tm utc = *std::localtime( &time );
		char strbuff[12] = {0};
		strftime( &strbuff[0], sizeof(strbuff), "%Y-%m-%dZ", &utc );
		std::string retval( strbuff );
		return( retval );
	}

	std::string CFLibXmlUtil::formatTZTime( const std::chrono::system_clock::time_point& cal ) {
		std::time_t time = std::chrono::system_clock::to_time_t( cal );
		std::tm utc = *std::localtime( &time );
		char strbuff[10] = {0};
		strftime( &strbuff[0], sizeof(strbuff), "%H:%M:%SZ", &utc );
		std::string retval( strbuff );
		return( retval );
	}

	std::string CFLibXmlUtil::formatTZTimestamp( const std::chrono::system_clock::time_point& cal ) {
		std::time_t time = std::chrono::system_clock::to_time_t( cal );
		std::tm utc = *std::localtime( &time );
		char strbuff[24] = {0};
		strftime( &strbuff[0], sizeof(strbuff), "%Y-%m-%dT%H:%M:%SZ", &utc );
		std::string retval( strbuff );
		return( retval );
	}

	std::string CFLibXmlUtil::formatUuid( const uuid_ptr_t val ) {
		char unparse[40] = {0};
		uuid_unparse( val, &unparse[0] );
		std::string retval( unparse );
		return( retval );
	}

	/**
	 *	Formatting for Required XML attributes.
	**/

	std::string CFLibXmlUtil::formatRequiredBoolean( const std::string* separator, const std::string& attrName, const bool val ) {
		static const std::string S_EqualQuote( "=\"" );
		static const std::string S_Quote( "\"" );
		std::string retval;
		if( separator != NULL ) {
			retval.append( *separator );
		}
		retval.append( attrName );
		retval.append( S_EqualQuote );
		std::string formattedValue = formatBoolean( val );
		retval.append( formattedValue );
		retval.append( S_Quote );
		return( retval );
	}

	std::string CFLibXmlUtil::formatRequiredBlob( const std::string* separator, const std::string& attrName, const std::vector<BYTE>& val ) {
		static const std::string S_EqualQuote( "=\"" );
		static const std::string S_Quote( "\"" );
		std::string retval;
		if( separator != NULL ) {
			retval.append( *separator );
		}
		retval.append( attrName );
		retval.append( S_EqualQuote );
		std::string formattedValue = formatBlob( val );
		retval.append( formattedValue );
		retval.append( S_Quote );
		return( retval );
	}

	std::string CFLibXmlUtil::formatRequiredInt16( const std::string* separator, const std::string& attrName, const std::int16_t val ) {
		static const std::string S_EqualQuote( "=\"" );
		static const std::string S_Quote( "\"" );
		std::string retval;
		if( separator != NULL ) {
			retval.append( *separator );
		}
		retval.append( attrName );
		retval.append( S_EqualQuote );
		std::string formattedValue = formatInt16( val );
		retval.append( formattedValue );
		retval.append( S_Quote );
		return( retval );
	}

	std::string CFLibXmlUtil::formatRequiredInt32( const std::string* separator, const std::string& attrName, const std::int32_t val ) {
		static const std::string S_EqualQuote( "=\"" );
		static const std::string S_Quote( "\"" );
		std::string retval;
		if( separator != NULL ) {
			retval.append( *separator );
		}
		retval.append( attrName );
		retval.append( S_EqualQuote );
		std::string formattedValue = formatInt32( val );
		retval.append( formattedValue );
		retval.append( S_Quote );
		return( retval );
	}

	std::string CFLibXmlUtil::formatRequiredInt64( const std::string* separator, const std::string& attrName, const std::int64_t val ) {
		static const std::string S_EqualQuote( "=\"" );
		static const std::string S_Quote( "\"" );
		std::string retval;
		if( separator != NULL ) {
			retval.append( *separator );
		}
		retval.append( attrName );
		retval.append( S_EqualQuote );
		std::string formattedValue = formatInt64( val );
		retval.append( formattedValue );
		retval.append( S_Quote );
		return( retval );
	}

	std::string CFLibXmlUtil::formatRequiredUInt16( const std::string* separator, const std::string& attrName, const std::uint16_t val ) {
		static const std::string S_EqualQuote( "=\"" );
		static const std::string S_Quote( "\"" );
		std::string retval;
		if( separator != NULL ) {
			retval.append( *separator );
		}
		retval.append( attrName );
		retval.append( S_EqualQuote );
		std::string formattedValue = formatUInt16( val );
		retval.append( formattedValue );
		retval.append( S_Quote );
		return( retval );
	}

	std::string CFLibXmlUtil::formatRequiredUInt32( const std::string* separator, const std::string& attrName, const std::uint32_t val ) {
		static const std::string S_EqualQuote( "=\"" );
		static const std::string S_Quote( "\"" );
		std::string retval;
		if( separator != NULL ) {
			retval.append( *separator );
		}
		retval.append( attrName );
		retval.append( S_EqualQuote );
		std::string formattedValue = formatUInt32( val );
		retval.append( formattedValue );
		retval.append( S_Quote );
		return( retval );
	}

	std::string CFLibXmlUtil::formatRequiredUInt64( const std::string* separator, const std::string& attrName, const std::uint64_t val ) {
		static const std::string S_EqualQuote( "=\"" );
		static const std::string S_Quote( "\"" );
		std::string retval;
		if( separator != NULL ) {
			retval.append( *separator );
		}
		retval.append( attrName );
		retval.append( S_EqualQuote );
		std::string formattedValue = formatUInt64( val );
		retval.append( formattedValue );
		retval.append( S_Quote );
		return( retval );
	}

	std::string CFLibXmlUtil::formatRequiredFloat( const std::string* separator, const std::string& attrName, const float val ) {
		static const std::string S_EqualQuote( "=\"" );
		static const std::string S_Quote( "\"" );
		std::string retval;
		if( separator != NULL ) {
			retval.append( *separator );
		}
		retval.append( attrName );
		retval.append( S_EqualQuote );
		std::string formattedValue = formatFloat( val );
		retval.append( formattedValue );
		retval.append( S_Quote );
		return( retval );
	}

	std::string CFLibXmlUtil::formatRequiredDouble( const std::string* separator, const std::string& attrName, const double val ) {
		static const std::string S_EqualQuote( "=\"" );
		static const std::string S_Quote( "\"" );
		std::string retval;
		if( separator != NULL ) {
			retval.append( *separator );
		}
		retval.append( attrName );
		retval.append( S_EqualQuote );
		std::string formattedValue = formatDouble( val );
		retval.append( formattedValue );
		retval.append( S_Quote );
		return( retval );
	}

	std::string CFLibXmlUtil::formatRequiredNumber(const std::string* separator, const std::string& attrName, const CFLibGenericBigDecimal& val) {
		static const std::string S_EqualQuote("=\"");
		static const std::string S_Quote("\"");
		std::string retval;
		if (separator != NULL) {
			retval.append(*separator);
		}
		retval.append(attrName);
		retval.append(S_EqualQuote);
		std::string formattedValue = val.toString();
		retval.append(formattedValue);
		retval.append(S_Quote);
		return(retval);
	}

	std::string CFLibXmlUtil::formatRequiredXmlString( const std::string* separator, const std::string& attrName, const std::string& str ) {
		static const std::string S_EqualQuote( "=\"" );
		static const std::string S_Quote( "\"" );
		std::string retval;
		if( separator != NULL ) {
			retval.append( *separator );
		}
		retval.append( attrName );
		retval.append( S_EqualQuote );
		std::string formattedStr = formatXmlString( str );
		retval.append( formattedStr );
		retval.append( S_Quote );
		return( retval );
	}

	std::string CFLibXmlUtil::formatRequiredDate( const std::string* separator, const std::string& attrName, const std::chrono::system_clock::time_point& cal ) {
		static const std::string S_EqualQuote( "=\"" );
		static const std::string S_Quote( "\"" );
		std::string retval;
		if( separator != NULL ) {
			retval.append( *separator );
		}
		retval.append( attrName );
		retval.append( S_EqualQuote );
		std::string formattedCal = formatDate( cal );
		retval.append( formattedCal );
		retval.append( S_Quote );
		return( retval );
	}

	std::string CFLibXmlUtil::formatRequiredTime( const std::string* separator, const std::string& attrName, const std::chrono::system_clock::time_point& cal ) {
		static const std::string S_EqualQuote( "=\"" );
		static const std::string S_Quote( "\"" );
		std::string retval;
		if( separator != NULL ) {
			retval.append( *separator );
		}
		retval.append( attrName );
		retval.append( S_EqualQuote );
		std::string formattedCal = formatTime( cal );
		retval.append( formattedCal );
		retval.append( S_Quote );
		return( retval );
	}

	std::string CFLibXmlUtil::formatRequiredTimestamp( const std::string* separator, const std::string& attrName, const std::chrono::system_clock::time_point& cal ) {
		static const std::string S_EqualQuote( "=\"" );
		static const std::string S_Quote( "\"" );
		std::string retval;
		if( separator != NULL ) {
			retval.append( *separator );
		}
		retval.append( attrName );
		retval.append( S_EqualQuote );
		std::string formattedCal = formatTimestamp( cal );
		retval.append( formattedCal );
		retval.append( S_Quote );
		return( retval );
	}

	std::string CFLibXmlUtil::formatRequiredTZDate( const std::string* separator, const std::string& attrName, const std::chrono::system_clock::time_point& cal ) {
		static const std::string S_EqualQuote( "=\"" );
		static const std::string S_Quote( "\"" );
		std::string retval;
		if( separator != NULL ) {
			retval.append( *separator );
		}
		retval.append( attrName );
		retval.append( S_EqualQuote );
		std::string formattedCal = formatTZDate( cal );
		retval.append( formattedCal );
		retval.append( S_Quote );
		return( retval );
	}

	std::string CFLibXmlUtil::formatRequiredTZTime( const std::string* separator, const std::string& attrName, const std::chrono::system_clock::time_point& cal ) {
		static const std::string S_EqualQuote( "=\"" );
		static const std::string S_Quote( "\"" );
		std::string retval;
		if( separator != NULL ) {
			retval.append( *separator );
		}
		retval.append( attrName );
		retval.append( S_EqualQuote );
		std::string formattedCal = formatTZTime( cal );
		retval.append( formattedCal );
		retval.append( S_Quote );
		return( retval );
	}

	std::string CFLibXmlUtil::formatRequiredTZTimestamp( const std::string* separator, const std::string& attrName, const std::chrono::system_clock::time_point& cal ) {
		static const std::string S_EqualQuote( "=\"" );
		static const std::string S_Quote( "\"" );
		std::string retval;
		if( separator != NULL ) {
			retval.append( *separator );
		}
		retval.append( attrName );
		retval.append( S_EqualQuote );
		std::string formattedCal = formatTZTimestamp( cal );
		retval.append( formattedCal );
		retval.append( S_Quote );
		return( retval );
	}

	std::string CFLibXmlUtil::formatRequiredUuid( const std::string* separator, const std::string& attrName, const uuid_ptr_t val ) {
		static const std::string S_EqualQuote( "=\"" );
		static const std::string S_Quote( "\"" );
		std::string retval;
		if( separator != NULL ) {
			retval.append( *separator );
		}
		retval.append( attrName );
		retval.append( S_EqualQuote );
		std::string formattedVal = formatUuid( val );
		retval.append( formattedVal );
		retval.append( S_Quote );
		return( retval );
	}

	/**
	 *	Formatting for Optional XML attributes.
	**/

	std::string CFLibXmlUtil::formatOptionalBoolean( const std::string* separator, const std::string& attrName, const CFLibNullableBool& val ) {
		if( ! val.isNull() ) {
			return( formatRequiredBoolean( separator, attrName, val.getValue() ) );
		}
		else {
			std::string retval;
			return( retval );
		}
	}

	std::string CFLibXmlUtil::formatOptionalBlob( const std::string* separator, const std::string& attrName, const std::vector<BYTE>* val ) {
		if( val != NULL ) {
			return( formatRequiredBlob( separator, attrName, *val ) );
		}
		else {
			std::string retval;
			return( retval );
		}
	}

	std::string CFLibXmlUtil::formatOptionalInt16( const std::string* separator, const std::string& attrName, const CFLibNullableInt16& val ) {
		if( ! val.isNull() ) {
			return( formatRequiredInt16( separator, attrName, val.getValue() ) );
		}
		else {
			std::string retval;
			return( retval );
		}
	}

	std::string CFLibXmlUtil::formatOptionalInt32( const std::string* separator, const std::string& attrName, const CFLibNullableInt32& val ) {
		if( ! val.isNull() ) {
			return( formatRequiredInt32( separator, attrName, val.getValue() ) );
		}
		else {
			std::string retval;
			return( retval );
		}
	}

	std::string CFLibXmlUtil::formatOptionalInt64( const std::string* separator, const std::string& attrName, const CFLibNullableInt64& val ) {
		if( ! val.isNull() ) {
			return( formatRequiredInt64( separator, attrName, val.getValue() ) );
		}
		else {
			std::string retval;
			return( retval );
		}
	}

	std::string CFLibXmlUtil::formatOptionalUInt16( const std::string* separator, const std::string& attrName, const CFLibNullableUInt16& val ) {
		if( ! val.isNull() ) {
			return( formatRequiredUInt16( separator, attrName, val.getValue() ) );
		}
		else {
			std::string retval;
			return( retval );
		}
	}

	std::string CFLibXmlUtil::formatOptionalUInt32( const std::string* separator, const std::string& attrName, const CFLibNullableUInt32& val ) {
		if( ! val.isNull() ) {
			return( formatRequiredUInt32( separator, attrName, val.getValue() ) );
		}
		else {
			std::string retval;
			return( retval );
		}
	}

	std::string CFLibXmlUtil::formatOptionalUInt64( const std::string* separator, const std::string& attrName, const CFLibNullableUInt64& val ) {
		if( ! val.isNull() ) {
			return( formatRequiredUInt64( separator, attrName, val.getValue() ) );
		}
		else {
			std::string retval;
			return( retval );
		}
	}

	std::string CFLibXmlUtil::formatOptionalFloat( const std::string* separator, const std::string& attrName, const CFLibNullableFloat& val ) {
		if( ! val.isNull() ) {
			return( formatRequiredFloat( separator, attrName, val.getValue() ) );
		}
		else {
			std::string retval;
			return( retval );
		}
	}

	std::string CFLibXmlUtil::formatOptionalDouble( const std::string* separator, const std::string& attrName, const CFLibNullableDouble& val ) {
		if( ! val.isNull() ) {
			return( formatRequiredDouble( separator, attrName, val.getValue() ) );
		}
		else {
			std::string retval;
			return( retval );
		}
	}

	std::string CFLibXmlUtil::formatOptionalNumber(const std::string* separator, const std::string& attrName, const CFLibGenericBigDecimal* val) {
		if (val != NULL) {
			return(formatRequiredNumber(separator, attrName, *val));
		}
		else {
			std::string retval;
			return(retval);
		}
	}

	std::string CFLibXmlUtil::formatOptionalXmlString( const std::string* separator, const std::string& attrName, const std::string* str ) {
		if( str != NULL ) {
			return( formatRequiredXmlString( separator, attrName, *str ) );
		}
		else {
			std::string retval;
			return( retval );
		}
	}

	std::string CFLibXmlUtil::formatOptionalDate( const std::string* separator, const std::string& attrName, const std::chrono::system_clock::time_point* cal ) {
		if( cal != NULL ) {
			return( formatRequiredDate( separator, attrName, *cal ) );
		}
		else {
			std::string retval;
			return( retval );
		}
	}

	std::string CFLibXmlUtil::formatOptionalTime( const std::string* separator, const std::string& attrName, const std::chrono::system_clock::time_point* cal ) {
		if( cal != NULL ) {
			return( formatRequiredTime( separator, attrName, *cal ) );
		}
		else {
			std::string retval;
			return( retval );
		}
	}

	std::string CFLibXmlUtil::formatOptionalTimestamp( const std::string* separator, const std::string& attrName, const std::chrono::system_clock::time_point* cal ) {
		if( cal != NULL ) {
			return( formatRequiredTimestamp( separator, attrName, *cal ) );
		}
		else {
			std::string retval;
			return( retval );
		}
	}

	std::string CFLibXmlUtil::formatOptionalTZDate( const std::string* separator, const std::string& attrName, const std::chrono::system_clock::time_point* cal ) {
		if( cal != NULL ) {
			return( formatRequiredTZDate( separator, attrName, *cal ) );
		}
		else {
			std::string retval;
			return( retval );
		}
	}

	std::string CFLibXmlUtil::formatOptionalTZTime( const std::string* separator, const std::string& attrName, const std::chrono::system_clock::time_point* cal ) {
		if( cal != NULL ) {
			return( formatRequiredTZTime( separator, attrName, *cal ) );
		}
		else {
			std::string retval;
			return( retval );
		}
	}

	std::string CFLibXmlUtil::formatOptionalTZTimestamp( const std::string* separator, const std::string& attrName, const std::chrono::system_clock::time_point* cal ) {
		if( cal != NULL ) {
			return( formatRequiredTZTimestamp( separator, attrName, *cal ) );
		}
		else {
			std::string retval;
			return( retval );
		}
	}

	std::string CFLibXmlUtil::formatOptionalUuid( const std::string* separator, const std::string& attrName, const uuid_ptr_t val ) {
		if( val != NULL ) {
			return( formatRequiredUuid( separator, attrName, val ) );
		}
		else {
			std::string retval;
			return( retval );
		}
	}
}
