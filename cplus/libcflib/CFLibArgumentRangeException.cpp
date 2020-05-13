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
#include <cflib/CFLibXmlUtil.hpp>
#include <cflib/CFLibArgumentRangeException.hpp>

namespace cflib {

	const std::string CFLibArgumentRangeException::CLASS_NAME( "CFLibArgumentRangeException" );
	const std::string CFLibArgumentRangeException::CAUSE_NAME( "Range" );
	const std::string CFLibArgumentRangeException::S_IS_OUT_OF_THE_RANGE( " is out of the range " );
	const std::string CFLibArgumentRangeException::S_VALUE_OUT_OF_RANGE( "value is out of range" );

	CFLibArgumentRangeException::~CFLibArgumentRangeException() {
	}

	CFLibArgumentRangeException::CFLibArgumentRangeException(
		const CFLibArgumentRangeException& src )
	: cflib::CFLibArgumentException( src )
	{
	}

	CFLibArgumentRangeException::CFLibArgumentRangeException()
	: cflib::CFLibArgumentException(
			CAUSE_NAME,					// Cause
			CLASS_NAME,	// ExceptionName
			S_Empty,					// argClassFieldName
			S_Empty,					// argMethodName
			0LL,						// argArgOffset
			S_Empty,					// argArgName
			S_Empty,					// argArgValueString,
			S_Empty,					// argArgMinValueString
			S_Empty,					// argArgMaxValueString
			S_Empty )					// argMessageText
	{
	}

	CFLibArgumentRangeException::CFLibArgumentRangeException(
		const std::string& argCause,
		const std::string& argExceptionName,
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		const std::string& argArgValueString,
		const std::string& argArgMinValueString,
		const std::string& argArgMaxValueString,
		const std::string& argMessageText )
	: cflib::CFLibArgumentException(
			argCause,					// Cause
			argExceptionName,			// ExceptionName
			argClassFieldName,			// argClassFieldName
			argMethodName,				// argMethodName
			argArgOffset,				// argArgOffset
			argArgName,					// argArgName
			argArgValueString,			// argArgValueString,
			argArgMinValueString,		// argArgMinValueString
			argArgMaxValueString,		// argArgMaxValueString
			argMessageText )			// argMessageText
	{
	}

	CFLibArgumentRangeException::CFLibArgumentRangeException(
		const std::string& argCause,
		const std::string& argExceptionName,
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		const std::string& argArgValueString,
		const std::string& argMessageText )
	: cflib::CFLibArgumentException(
			argCause,					// Cause
			argExceptionName,			// ExceptionName
			argClassFieldName,			// argClassFieldName
			argMethodName,				// argMethodName
			argArgOffset,				// argArgOffset
			argArgName,					// argArgName
			argArgValueString,			// argArgValueString,
			S_Empty,					// argArgMinValueString
			S_Empty,					// argArgMaxValueString
			argMessageText )			// argMessageText
	{
	}

	CFLibArgumentRangeException::CFLibArgumentRangeException(
		const std::string& argCause,
		const std::string& argExceptionName,
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		const std::string& argMessageText )
	: cflib::CFLibArgumentException(
			argCause,					// Cause
			argExceptionName,			// ExceptionName
			argClassFieldName,			// argClassFieldName
			argMethodName,				// argMethodName
			0LL,						// argArgOffset
			S_Empty,					// argArgName
			S_Empty,					// argArgValueString,
			S_Empty,					// argArgMinValueString
			S_Empty,					// argArgMaxValueString
			argMessageText )			// argMessageText
	{
	}

	CFLibArgumentRangeException::CFLibArgumentRangeException(
		const std::string& argCause,
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		const std::string& argMessageText )
	: cflib::CFLibArgumentException(
			argCause,					// Cause
			CLASS_NAME,					// ExceptionName
			argClassFieldName,			// argClassFieldName
			argMethodName,				// argMethodName
			0LL,						// argArgOffset
			S_Empty,					// argArgName
			S_Empty,					// argArgValueString,
			S_Empty,					// argArgMinValueString
			S_Empty,					// argArgMaxValueString
			argMessageText )			// argMessageText
	{
	}

	CFLibArgumentRangeException::CFLibArgumentRangeException(
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		const std::string& msg )
	: cflib::CFLibArgumentException(
			CAUSE_NAME,					// Cause
			CLASS_NAME,					// ExceptionName
			argClassFieldName,			// argClassFieldName
			argMethodName,					// argMethodName
			argArgOffset,				// argArgOffset
			argArgName,					// argArgName
			S_Empty,					// argArgValueString,
			S_Empty,					// argArgMinValueString
			S_Empty,					// argArgMaxValueString
			msg )						// argMessageText
	{
	}

	CFLibArgumentRangeException::CFLibArgumentRangeException(
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		const std::string& msg )
	: cflib::CFLibArgumentException(
			CAUSE_NAME,					// Cause
			CLASS_NAME,					// ExceptionName
			argClassFieldName,			// argClassFieldName
			argMethodName,					// argMethodName
			0LL,						// argArgOffset
			S_Empty,					// argArgName
			S_Empty,					// argArgValueString,
			S_Empty,					// argArgMinValueString
			S_Empty,					// argArgMaxValueString
			msg )						// argMessageText
	{
	}

	CFLibArgumentRangeException::CFLibArgumentRangeException(
		const std::string& fieldName,
		const std::string& msg )
	: cflib::CFLibArgumentException(
			CAUSE_NAME,					// Cause
			CLASS_NAME,					// ExceptionName
			fieldName,					// argClassFieldName
			S_Empty,					// argMethodName
			0LL,						// argArgOffset
			S_Empty,					// argArgName
			S_Empty,					// argArgValueString,
			S_Empty,					// argArgMinValueString
			S_Empty,					// argArgMaxValueString
			msg )						// argMessageText
	{
	}

	CFLibArgumentRangeException::CFLibArgumentRangeException(
		const std::string& msg )
	: cflib::CFLibArgumentException(
			CAUSE_NAME,					// Cause
			CLASS_NAME,					// ExceptionName
			S_Empty,					// argClassFieldName
			S_Empty,					// argMethodName
			0LL,						// argArgOffset
			S_Empty,					// argArgName
			S_Empty,					// argArgValueString,
			S_Empty,					// argArgMinValueString
			S_Empty,					// argArgMaxValueString
			msg )						// argMessageText
	{
	}

	CFLibArgumentRangeException::CFLibArgumentRangeException(
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		int16_t argValue,
		int16_t minValue,
		int16_t maxValue )
	: cflib::CFLibArgumentException(
			CAUSE_NAME,							// Cause
			CLASS_NAME,							// ExceptionName
			argClassFieldName,					// argClassFieldName
			argMethodName,						// argMethodName
			argArgOffset,						// argArgOffset
			argArgName,							// argArgName
			std::to_string( argValue ),			// argArgValueString,
			std::to_string( minValue ),			// argArgMinValueString
			std::to_string( maxValue ),			// argArgMaxValueString
			std::string( argArgName + CFLib::S_SPACE + CFLib::S_VALUE_SPACE + std::to_string( argValue ) + S_IS_OUT_OF_THE_RANGE + std::to_string( minValue ) + CFLib::S_DOT_DOT + std::to_string( maxValue ) ) )
	{
	}

	CFLibArgumentRangeException::CFLibArgumentRangeException(
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		int32_t argValue,
		int32_t minValue,
		int32_t maxValue )
	: cflib::CFLibArgumentException(
			CAUSE_NAME,							// Cause
			CLASS_NAME,							// ExceptionName
			argClassFieldName,					// argClassFieldName
			argMethodName,						// argMethodName
			argArgOffset,						// argArgOffset
			argArgName,							// argArgName
			std::to_string( argValue ),			// argArgValueString,
			std::to_string( minValue ),			// argArgMinValueString
			std::to_string( maxValue ),			// argArgMaxValueString
			std::string( argArgName + CFLib::S_SPACE + CFLib::S_VALUE_SPACE + std::to_string( argValue ) + S_IS_OUT_OF_THE_RANGE + std::to_string( minValue ) + CFLib::S_DOT_DOT + std::to_string( maxValue ) ) )
	{
	}

	CFLibArgumentRangeException::CFLibArgumentRangeException(
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		int64_t argValue,
		int64_t minValue,
		int64_t maxValue )
	: cflib::CFLibArgumentException(
			CAUSE_NAME,							// Cause
			CLASS_NAME,							// ExceptionName
			argClassFieldName,					// argClassFieldName
			argMethodName,						// argMethodName
			argArgOffset,						// argArgOffset
			argArgName,							// argArgName
			std::to_string( argValue ),			// argArgValueString,
			std::to_string( minValue ),			// argArgMinValueString
			std::to_string( maxValue ),			// argArgMaxValueString
			std::string( argArgName + CFLib::S_SPACE + CFLib::S_VALUE_SPACE + std::to_string( argValue ) + S_IS_OUT_OF_THE_RANGE + std::to_string( minValue ) + CFLib::S_DOT_DOT + std::to_string( maxValue ) ) )
	{
	}

	CFLibArgumentRangeException::CFLibArgumentRangeException(
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		uint16_t argValue,
		uint16_t minValue,
		uint16_t maxValue )
	: cflib::CFLibArgumentException(
			CAUSE_NAME,							// Cause
			CLASS_NAME,							// ExceptionName
			argClassFieldName,					// argClassFieldName
			argMethodName,						// argMethodName
			argArgOffset,						// argArgOffset
			argArgName,							// argArgName
			std::to_string( argValue ),			// argArgValueString,
			std::to_string( minValue ),			// argArgMinValueString
			std::to_string( maxValue ),			// argArgMaxValueString
			std::string( argArgName + CFLib::S_SPACE + CFLib::S_VALUE_SPACE + std::to_string( argValue ) + S_IS_OUT_OF_THE_RANGE + std::to_string( minValue ) + CFLib::S_DOT_DOT + std::to_string( maxValue ) ) )
	{
	}

	CFLibArgumentRangeException::CFLibArgumentRangeException(
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		uint32_t argValue,
		uint32_t minValue,
		uint32_t maxValue )
	: cflib::CFLibArgumentException(
			CAUSE_NAME,							// Cause
			CLASS_NAME,							// ExceptionName
			argClassFieldName,					// argClassFieldName
			argMethodName,						// argMethodName
			argArgOffset,						// argArgOffset
			argArgName,							// argArgName
			std::to_string( argValue ),			// argArgValueString,
			std::to_string( minValue ),			// argArgMinValueString
			std::to_string( maxValue ),			// argArgMaxValueString
			std::string( argArgName + CFLib::S_SPACE + CFLib::S_VALUE_SPACE + std::to_string( argValue ) + S_IS_OUT_OF_THE_RANGE + std::to_string( minValue ) + CFLib::S_DOT_DOT + std::to_string( maxValue ) ) )
	{
	}

	CFLibArgumentRangeException::CFLibArgumentRangeException(
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		uint64_t argValue,
		uint64_t minValue,
		uint64_t maxValue )
	: cflib::CFLibArgumentException(
			CAUSE_NAME,							// Cause
			CLASS_NAME,							// ExceptionName
			argClassFieldName,					// argClassFieldName
			argMethodName,						// argMethodName
			argArgOffset,						// argArgOffset
			argArgName,							// argArgName
			std::to_string( argValue ),			// argArgValueString,
			std::to_string( minValue ),			// argArgMinValueString
			std::to_string( maxValue ),			// argArgMaxValueString
			std::string( argArgName + CFLib::S_SPACE + CFLib::S_VALUE_SPACE + std::to_string( argValue ) + S_IS_OUT_OF_THE_RANGE + std::to_string( minValue ) + CFLib::S_DOT_DOT + std::to_string( maxValue ) ) )
	{
	}

	CFLibArgumentRangeException::CFLibArgumentRangeException(
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		float argValue,
		float minValue,
		float maxValue )
	: cflib::CFLibArgumentException(
			CAUSE_NAME,							// Cause
			CLASS_NAME,							// ExceptionName
			argClassFieldName,					// argClassFieldName
			argMethodName,						// argMethodName
			argArgOffset,						// argArgOffset
			argArgName,							// argArgName
			std::to_string( argValue ),			// argArgValueString,
			std::to_string( minValue ),			// argArgMinValueString
			std::to_string( maxValue ),			// argArgMaxValueString
			std::string( argArgName + CFLib::S_SPACE + CFLib::S_VALUE_SPACE + std::to_string( argValue ) + S_IS_OUT_OF_THE_RANGE + std::to_string( minValue ) + CFLib::S_DOT_DOT + std::to_string( maxValue ) ) )
	{
	}

	CFLibArgumentRangeException::CFLibArgumentRangeException(
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		double argValue,
		double minValue,
		double maxValue )
	: cflib::CFLibArgumentException(
			CAUSE_NAME,							// Cause
			CLASS_NAME,							// ExceptionName
			argClassFieldName,					// argClassFieldName
			argMethodName,						// argMethodName
			argArgOffset,						// argArgOffset
			argArgName,							// argArgName
			std::to_string( argValue ),			// argArgValueString,
			std::to_string( minValue ),			// argArgMinValueString
			std::to_string( maxValue ),			// argArgMaxValueString
			std::string( argArgName + CFLib::S_SPACE + CFLib::S_VALUE_SPACE + std::to_string( argValue ) + S_IS_OUT_OF_THE_RANGE + std::to_string( minValue ) + CFLib::S_DOT_DOT + std::to_string( maxValue ) ) )
	{
	}

	CFLibArgumentRangeException::CFLibArgumentRangeException(
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		const std::chrono::system_clock::time_point& argValue,
		const std::chrono::system_clock::time_point& minValue,
		const std::chrono::system_clock::time_point& maxValue )
	: cflib::CFLibArgumentException(
			CAUSE_NAME,									// Cause
			CLASS_NAME,									// ExceptionName
			argClassFieldName,							// argClassFieldName
			argMethodName,								// argMethodName
			argArgOffset,								// argArgOffset
			argArgName,									// argArgName
			CFLibXmlUtil::formatTimestamp( argValue ),	// argArgValueString,
			CFLibXmlUtil::formatTimestamp( minValue ),	// argArgMinValueString
			CFLibXmlUtil::formatTimestamp( maxValue ),	// argArgMaxValueString
			std::string( argArgName + CFLib::S_SPACE + CFLib::S_VALUE_SPACE + CFLibXmlUtil::formatTimestamp( argValue ) + S_IS_OUT_OF_THE_RANGE + CFLibXmlUtil::formatTimestamp( minValue ) + CFLib::S_DOT_DOT + CFLibXmlUtil::formatTimestamp( maxValue ) ) )
	{
	}

	CFLibArgumentRangeException::CFLibArgumentRangeException(
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		const std::string& argValue,
		const std::string& minValue,
		const std::string& maxValue )
	: cflib::CFLibArgumentException(
			CAUSE_NAME,					// Cause
			CLASS_NAME,					// ExceptionName
			argClassFieldName,			// argClassFieldName
			argMethodName,				// argMethodName
			argArgOffset,				// argArgOffset
			argArgName,					// argArgName
			argValue,					// argArgValueString,
			minValue,					// argArgMinValueString
			maxValue,					// argArgMaxValueString
			std::string( argArgName + CFLib::S_SPACE + CFLib::S_VALUE_SPACE + argValue + S_IS_OUT_OF_THE_RANGE + minValue + CFLib::S_DOT_DOT + maxValue ) )
	{
	}

	CFLibArgumentRangeException::CFLibArgumentRangeException(
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		mpfr_srcptr argValue,
		mpfr_srcptr minValue,
		mpfr_srcptr maxValue )
	: cflib::CFLibArgumentException(
			CAUSE_NAME,								// Cause
			CLASS_NAME,								// ExceptionName
			argClassFieldName,						// argClassFieldName
			argMethodName,							// argMethodName
			argArgOffset,							// argArgOffset
			argArgName,								// argArgName
			CFLibXmlUtil::formatMPFR( argValue ),	// argArgValueString,
			CFLibXmlUtil::formatMPFR( minValue ),	// argArgMinValueString
			CFLibXmlUtil::formatMPFR( maxValue ),	// argArgMaxValueString
			std::string( argArgName + CFLib::S_SPACE + CFLib::S_VALUE_SPACE + CFLibXmlUtil::formatMPFR( argValue ) + S_IS_OUT_OF_THE_RANGE + CFLibXmlUtil::formatMPFR( minValue ) + CFLib::S_DOT_DOT + CFLibXmlUtil::formatMPFR( maxValue ) ) )
	{
	}

	CFLibArgumentRangeException::CFLibArgumentRangeException(
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		const CFLibGenericBigDecimal& argValue,
		const CFLibGenericBigDecimal& minValue,
		const CFLibGenericBigDecimal& maxValue )
	: cflib::CFLibArgumentException(
			CAUSE_NAME,							// Cause
			CLASS_NAME,							// ExceptionName
			argClassFieldName,					// argClassFieldName
			argMethodName,						// argMethodName
			argArgOffset,						// argArgOffset
			argArgName,							// argArgName
			argValue.toString(),				// argArgValueString,
			minValue.toString(),				// argArgMinValueString
			maxValue.toString(),				// argArgMaxValueString
			std::string( argArgName + CFLib::S_SPACE + CFLib::S_VALUE_SPACE + argValue.toString() + S_IS_OUT_OF_THE_RANGE + minValue.toString() + CFLib::S_DOT_DOT + maxValue.toString() ) )
	{
	}
}
