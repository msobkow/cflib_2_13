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

#include <cflib/CFLib.hpp>
#include <cflib/TCFLibBigDecimal.hpp>
#include <cflib/CFLibRuntimeException.hpp>
#include <cflib/CFLibArgumentException.hpp>
#include <cflib/CFLibUsageException.hpp>
#include <cflib/CFLibXmlCoreIso8859Encoder.hpp>

namespace cflib {

	class CFLibXmlUtil {

	public:

		static const std::string CLASS_NAME;
		static const std::string S_EMPTY_STRING;
		static const std::string S_IS_INVALID;
		static const std::string S_VALUE;
		static const std::string S_EXPECTED_SIGNED_DIGITS;
		static const std::string S_EXPECTED_DIGITS;
		static const std::string S_EXPECTED_DECIMAL_NUMBER;

		static const char S_UTC[4];

		/**
		 *	Formatting for XML attribute content strings.
		**/

		static bool isDigits( const std::string& value, bool allowSign, bool allowDecimal );

		static std::vector<BYTE>* parseBlob( const std::string& value );
		static std::int16_t* parseInt16( const std::string& value );
		static std::int16_t* parseInt16( const std::string& fieldName, const std::string& value );
		static std::int32_t* parseInt32( const std::string& value );
		static std::int32_t* parseInt32( const std::string& fieldName, const std::string& value );
		static std::int64_t* parseInt64( const std::string& value );
		static std::int64_t* parseInt64( const std::string& fieldName, const std::string& value );
		static std::uint16_t* parseUInt16( const std::string& value );
		static std::uint16_t* parseUInt16( const std::string& fieldName, const std::string& value );
		static std::uint32_t* parseUInt32( const std::string& value );
		static std::uint32_t* parseUInt32( const std::string& fieldName, const std::string& value );
		static std::uint64_t* parseUInt64( const std::string& value );
		static std::uint64_t* parseUInt64( const std::string& fieldName, const std::string& value );
		static float* parseFloat( const std::string& value );
		static float* parseFloat( const std::string& fieldName, const std::string& value );
		static double* parseDouble( const std::string& value );
		static double* parseDouble( const std::string& fieldName, const std::string& value );
		static std::string* parseXmlString( const std::string& value );
		static std::string* parseXmlString( const std::string& fieldName, const std::string& value );
		static std::string* parseXmlStringWhitespacePreserve( const std::string& value );
		static std::string* parseXmlStringWhitespacePreserve( const std::string& fieldName, const std::string& value );
		static std::chrono::system_clock::time_point* parseDate( const std::string& value );
		static std::chrono::system_clock::time_point* parseDate( const std::string& fieldName, const std::string& value );
		static std::chrono::system_clock::time_point* parseTime( const std::string& value );
		static std::chrono::system_clock::time_point* parseTime( const std::string& fieldName, const std::string& value );
		static std::chrono::system_clock::time_point* parseTimestamp( const std::string& value );
		static std::chrono::system_clock::time_point* parseTimestamp( const std::string& fieldName, const std::string& value );
		static std::chrono::system_clock::time_point* parseTZDate( const std::string& value );
		static std::chrono::system_clock::time_point* parseTZDate( const std::string& fieldName, const std::string& value );
		static std::chrono::system_clock::time_point* parseTZTime( const std::string& value );
		static std::chrono::system_clock::time_point* parseTZTime( const std::string& fieldName, const std::string& value );
		static std::chrono::system_clock::time_point* parseTZTimestamp( const std::string& value );
		static std::chrono::system_clock::time_point* parseTZTimestamp( const std::string& fieldName, const std::string& value );
		static void parseUuid( uuid_ptr_t target, const std::string& value );
		static void parseUuid( uuid_ptr_t target, const std::string& fieldName, const std::string& value );

		// eval methods are like parse methods, except they throw exceptions if there is no content in value instead of returning NULL
		static std::vector<BYTE> evalBlob( const std::string& value );
		static std::int16_t evalInt16( const std::string& value );
		static std::int16_t evalInt16( const std::string& fieldName, const std::string& value );
		static std::int32_t evalInt32( const std::string& value );
		static std::int32_t evalInt32( const std::string& fieldName, const std::string& value );
		static std::int64_t evalInt64( const std::string& value );
		static std::int64_t evalInt64( const std::string& fieldName, const std::string& value );
		static std::uint16_t evalUInt16( const std::string& value );
		static std::uint16_t evalUInt16( const std::string& fieldName, const std::string& value );
		static std::uint32_t evalUInt32( const std::string& value );
		static std::uint32_t evalUInt32( const std::string& fieldName, const std::string& value );
		static std::uint64_t evalUInt64( const std::string& value );
		static std::uint64_t evalUInt64( const std::string& fieldName, const std::string& value );
		static float evalFloat( const std::string& value );
		static float evalFloat( const std::string& fieldName, const std::string& value );
		static double evalDouble( const std::string& value );
		static double evalDouble( const std::string& fieldName, const std::string& value );
		static std::string evalXmlString( const std::string& value );
		static std::string evalXmlString( const std::string& fieldName, const std::string& value );
		static std::string evalXmlStringWhitespacePreserve( const std::string& value );
		static std::string evalXmlStringWhitespacePreserve( const std::string& fieldName, const std::string& value );
		static std::chrono::system_clock::time_point evalDate( const std::string& value );
		static std::chrono::system_clock::time_point evalDate( const std::string& fieldName, const std::string& value );
		static std::chrono::system_clock::time_point evalTime( const std::string& value );
		static std::chrono::system_clock::time_point evalTime( const std::string& fieldName, const std::string& value );
		static std::chrono::system_clock::time_point evalTimestamp( const std::string& value );
		static std::chrono::system_clock::time_point evalTimestamp( const std::string& fieldName, const std::string& value );
		static std::chrono::system_clock::time_point evalTZDate( const std::string& value );
		static std::chrono::system_clock::time_point evalTZDate( const std::string& fieldName, const std::string& value );
		static std::chrono::system_clock::time_point evalTZTime( const std::string& value );
		static std::chrono::system_clock::time_point evalTZTime( const std::string& fieldName, const std::string& value );
		static std::chrono::system_clock::time_point evalTZTimestamp( const std::string& value );
		static std::chrono::system_clock::time_point evalTZTimestamp( const std::string& fieldName, const std::string& value );

		static std::string formatBoolean( const bool val );
		static std::string formatBlob( const std::vector<BYTE>& val );
		static std::string formatInt16( const std::int16_t val );
		static std::string formatInt32( const std::int32_t val );
		static std::string formatInt64( const std::int64_t val );
		static std::string formatUInt16( const std::uint16_t val );
		static std::string formatUInt32( const std::uint32_t val );
		static std::string formatUInt64( const std::uint64_t val );
		static std::string formatFloat( const float val );
		static std::string formatDouble( const double val );
		static std::string formatMPFR( const mpfr_t& val );
		static std::string formatMPFR( mpfr_srcptr val );
		static std::string formatXmlString( const std::string& str );
		static std::string formatXmlStringWhitespacePreserve( const std::string& str );
		static std::string formatDate( const std::chrono::system_clock::time_point& cal );
		static std::string formatTime( const std::chrono::system_clock::time_point& cal );
		static std::string formatTimestamp( const std::chrono::system_clock::time_point& cal );
		static std::string formatTZDate( const std::chrono::system_clock::time_point& cal );
		static std::string formatTZTime( const std::chrono::system_clock::time_point& cal );
		static std::string formatTZTimestamp( const std::chrono::system_clock::time_point& cal );
		static std::string formatUuid( const uuid_ptr_t val );

		/**
		 *	Formatting for Required XML attributes.
		**/

		static std::string formatRequiredBoolean( const std::string* separator, const std::string& attrName, const bool val );

		static std::string formatRequiredBlob( const std::string* separator, const std::string& attrName, const std::vector<BYTE>& val );

		static std::string formatRequiredInt16( const std::string* separator, const std::string& attrName, const std::int16_t val );

		static std::string formatRequiredInt32( const std::string* separator, const std::string& attrName, const std::int32_t val );

		static std::string formatRequiredInt64( const std::string* separator, const std::string& attrName, const std::int64_t val );

		static std::string formatRequiredUInt16( const std::string* separator, const std::string& attrName, const std::uint16_t val );

		static std::string formatRequiredUInt32( const std::string* separator, const std::string& attrName, const std::uint32_t val );

		static std::string formatRequiredUInt64( const std::string* separator, const std::string& attrName, const std::uint64_t val );

		static std::string formatRequiredFloat( const std::string* separator, const std::string& attrName, const float val );

		static std::string formatRequiredDouble( const std::string* separator, const std::string& attrName, const double val );

		static std::string formatRequiredNumber(const std::string* separator, const std::string& attrName, const CFLibGenericBigDecimal& val);

		static std::string formatRequiredXmlString( const std::string* separator, const std::string& attrName, const std::string& str );

		static std::string formatRequiredDate( const std::string* separator, const std::string& attrName, const std::chrono::system_clock::time_point& cal );

		static std::string formatRequiredTime( const std::string* separator, const std::string& attrName, const std::chrono::system_clock::time_point& cal );

		static std::string formatRequiredTimestamp( const std::string* separator, const std::string& attrName, const std::chrono::system_clock::time_point& cal );

		static std::string formatRequiredTZDate( const std::string* separator, const std::string& attrName, const std::chrono::system_clock::time_point& cal );

		static std::string formatRequiredTZTime( const std::string* separator, const std::string& attrName, const std::chrono::system_clock::time_point& cal );

		static std::string formatRequiredTZTimestamp( const std::string* separator, const std::string& attrName, const std::chrono::system_clock::time_point& cal );

		static std::string formatRequiredUuid( const std::string* separator, const std::string& attrName, const uuid_ptr_t val );

		/**
		 *	Formatting for Optional XML attributes.
		**/

		static std::string formatOptionalBoolean( const std::string* separator, const std::string& attrName, const CFLibNullableBool& val );

		static std::string formatOptionalBlob( const std::string* separator, const std::string& attrName, const std::vector<BYTE>* val );

		static std::string formatOptionalInt16( const std::string* separator, const std::string& attrName, const CFLibNullableInt16& val );

		static std::string formatOptionalInt32( const std::string* separator, const std::string& attrName, const CFLibNullableInt32& val );

		static std::string formatOptionalInt64( const std::string* separator, const std::string& attrName, const CFLibNullableInt64& val );

		static std::string formatOptionalUInt16( const std::string* separator, const std::string& attrName, const CFLibNullableUInt16& val );

		static std::string formatOptionalUInt32( const std::string* separator, const std::string& attrName, const CFLibNullableUInt32& val );

		static std::string formatOptionalUInt64( const std::string* separator, const std::string& attrName, const CFLibNullableUInt64& val );

		static std::string formatOptionalFloat( const std::string* separator, const std::string& attrName, const CFLibNullableFloat& val );

		static std::string formatOptionalDouble( const std::string* separator, const std::string& attrName, const CFLibNullableDouble& val );

		static std::string formatOptionalNumber(const std::string* separator, const std::string& attrName, const CFLibGenericBigDecimal* val);

		static std::string formatOptionalXmlString( const std::string* separator, const std::string& attrName, const std::string* str );

		static std::string formatOptionalDate( const std::string* separator, const std::string& attrName, const std::chrono::system_clock::time_point* cal );

		static std::string formatOptionalTime( const std::string* separator, const std::string& attrName, const std::chrono::system_clock::time_point* cal );

		static std::string formatOptionalTimestamp( const std::string* separator, const std::string& attrName, const std::chrono::system_clock::time_point* cal );

		static std::string formatOptionalTZDate( const std::string* separator, const std::string& attrName, const std::chrono::system_clock::time_point* cal );

		static std::string formatOptionalTZTime( const std::string* separator, const std::string& attrName, const std::chrono::system_clock::time_point* cal );

		static std::string formatOptionalTZTimestamp( const std::string* separator, const std::string& attrName, const std::chrono::system_clock::time_point* cal );
	
		static std::string formatOptionalUuid( const std::string* separator, const std::string& attrName, const uuid_ptr_t val );
	};
}
