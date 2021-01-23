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
#include <cflib/CFLibXmlUtil.hpp>
#include <cflib/CFLibArgumentUnderflowException.hpp>

namespace cflib {

	const std::string CFLibArgumentUnderflowException::CLASS_NAME( "CFLibArgumentUnderflowException" );
	const std::string CFLibArgumentUnderflowException::CAUSE_NAME( "Underflow" );
	const std::string CFLibArgumentUnderflowException::S_MUST_BE_AT_LEAST( " must be at least " );

	CFLibArgumentUnderflowException::~CFLibArgumentUnderflowException() {
	}

	CFLibArgumentUnderflowException::CFLibArgumentUnderflowException(
		const CFLibArgumentUnderflowException& src )
	: cflib::CFLibArgumentException( src )
	{
	}

	CFLibArgumentUnderflowException::CFLibArgumentUnderflowException()
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

	CFLibArgumentUnderflowException::CFLibArgumentUnderflowException(
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

	CFLibArgumentUnderflowException::CFLibArgumentUnderflowException(
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

	CFLibArgumentUnderflowException::CFLibArgumentUnderflowException(
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

	CFLibArgumentUnderflowException::CFLibArgumentUnderflowException(
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

	CFLibArgumentUnderflowException::CFLibArgumentUnderflowException(
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argName,
		const std::string& msg )
	: cflib::CFLibArgumentException(
			CAUSE_NAME,					// Cause
			CLASS_NAME,					// ExceptionName
			argClassFieldName,			// argClassFieldName
			argMethodName,				// argMethodName
			argArgOffset,				// argArgOffset
			argName,					// argArgName
			S_Empty,					// argArgValueString,
			S_Empty,					// argArgMinValueString
			S_Empty,					// argArgMaxValueString
			msg )						// argMessageText
	{
	}

	CFLibArgumentUnderflowException::CFLibArgumentUnderflowException(
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		const std::string& msg )
	: cflib::CFLibArgumentException(
			CAUSE_NAME,					// Cause
			CLASS_NAME,					// ExceptionName
			argClassFieldName,			// argClassFieldName
			argMethodName,				// argMethodName
			0LL,						// argArgOffset
			S_Empty,					// argArgName
			S_Empty,					// argArgValueString,
			S_Empty,					// argArgMinValueString
			S_Empty,					// argArgMaxValueString
			msg )						// argMessageText
	{
	}

	CFLibArgumentUnderflowException::CFLibArgumentUnderflowException(
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

	CFLibArgumentUnderflowException::CFLibArgumentUnderflowException(
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

	CFLibArgumentUnderflowException::CFLibArgumentUnderflowException(
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		int16_t argValue,
		int16_t minValue )
	: cflib::CFLibArgumentException(
			CAUSE_NAME,							// Cause
			CLASS_NAME,							// ExceptionName
			argClassFieldName,					// argClassFieldName
			argMethodName,						// argMethodName
			argArgOffset,						// argArgOffset
			argArgName,							// argArgName
			std::to_string( argValue ),			// argArgValueString,
			std::to_string( minValue ),			// argArgMinValueString
			S_Empty,							// argArgMaxValueString
	 		std::string( argArgName + CFLib::S_SPACE + CFLib::S_VALUE_SPACE + std::to_string( argValue ) + S_MUST_BE_AT_LEAST + std::to_string( minValue ) ) )
	{
	}

	CFLibArgumentUnderflowException::CFLibArgumentUnderflowException(
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		int32_t argValue,
		int32_t minValue )
	: cflib::CFLibArgumentException(
			CAUSE_NAME,							// Cause
			CLASS_NAME,							// ExceptionName
			argClassFieldName,					// argClassFieldName
			argMethodName,						// argMethodName
			argArgOffset,						// argArgOffset
			argArgName,							// argArgName
			std::to_string( argValue ),			// argArgValueString,
			std::to_string( minValue ),			// argArgMinValueString
			S_Empty,							// argArgMaxValueString
	 		std::string( argArgName + CFLib::S_SPACE + CFLib::S_VALUE_SPACE + std::to_string( argValue ) + S_MUST_BE_AT_LEAST + std::to_string( minValue ) ) )
	{
	}

	CFLibArgumentUnderflowException::CFLibArgumentUnderflowException(
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		int64_t argValue,
		int64_t minValue )
	: cflib::CFLibArgumentException(
			CAUSE_NAME,							// Cause
			CLASS_NAME,							// ExceptionName
			argClassFieldName,					// argClassFieldName
			argMethodName,						// argMethodName
			argArgOffset,						// argArgOffset
			argArgName,							// argArgName
			std::to_string( argValue ),			// argArgValueString,
			std::to_string( minValue ),			// argArgMinValueString
			S_Empty,							// argArgMaxValueString
	 		std::string( argArgName + CFLib::S_SPACE + CFLib::S_VALUE_SPACE + std::to_string( argValue ) + S_MUST_BE_AT_LEAST + std::to_string( minValue ) ) )
	{
	}

	CFLibArgumentUnderflowException::CFLibArgumentUnderflowException(
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		uint16_t argValue,
		uint16_t minValue )
	: cflib::CFLibArgumentException(
			CAUSE_NAME,							// Cause
			CLASS_NAME,							// ExceptionName
			argClassFieldName,					// argClassFieldName
			argMethodName,						// argMethodName
			argArgOffset,						// argArgOffset
			argArgName,							// argArgName
			std::to_string( argValue ),			// argArgValueString,
			std::to_string( minValue ),			// argArgMinValueString
			S_Empty,							// argArgMaxValueString
	 		std::string( argArgName + CFLib::S_SPACE + CFLib::S_VALUE_SPACE + std::to_string( argValue ) + S_MUST_BE_AT_LEAST + std::to_string( minValue ) ) )
	{
	}

	CFLibArgumentUnderflowException::CFLibArgumentUnderflowException(
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		uint32_t argValue,
		uint32_t minValue )
	: cflib::CFLibArgumentException(
			CAUSE_NAME,							// Cause
			CLASS_NAME,							// ExceptionName
			argClassFieldName,					// argClassFieldName
			argMethodName,						// argMethodName
			argArgOffset,						// argArgOffset
			argArgName,							// argArgName
			std::to_string( argValue ),			// argArgValueString,
			std::to_string( minValue ),			// argArgMinValueString
			S_Empty,							// argArgMaxValueString
	 		std::string( argArgName + CFLib::S_SPACE + CFLib::S_VALUE_SPACE + std::to_string( argValue ) + S_MUST_BE_AT_LEAST + std::to_string( minValue ) ) )
	{
	}

	CFLibArgumentUnderflowException::CFLibArgumentUnderflowException(
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		uint64_t argValue,
		uint64_t minValue )
	: cflib::CFLibArgumentException(
			CAUSE_NAME,							// Cause
			CLASS_NAME,							// ExceptionName
			argClassFieldName,					// argClassFieldName
			argMethodName,						// argMethodName
			argArgOffset,						// argArgOffset
			argArgName,							// argArgName
			std::to_string( argValue ),			// argArgValueString,
			std::to_string( minValue ),			// argArgMinValueString
			S_Empty,							// argArgMaxValueString
	 		std::string( argArgName + CFLib::S_SPACE + CFLib::S_VALUE_SPACE + std::to_string( argValue ) + S_MUST_BE_AT_LEAST + std::to_string( minValue ) ) )
	{
	}

	CFLibArgumentUnderflowException::CFLibArgumentUnderflowException(
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		float argValue,
		float minValue )
	: cflib::CFLibArgumentException(
			CAUSE_NAME,							// Cause
			CLASS_NAME,							// ExceptionName
			argClassFieldName,					// argClassFieldName
			argMethodName,						// argMethodName
			argArgOffset,						// argArgOffset
			argArgName,							// argArgName
			std::to_string( argValue ),			// argArgValueString,
			std::to_string( minValue ),			// argArgMinValueString
			S_Empty,							// argArgMaxValueString
	 		std::string( argArgName + CFLib::S_SPACE + CFLib::S_VALUE_SPACE + std::to_string( argValue ) + S_MUST_BE_AT_LEAST + std::to_string( minValue ) ) )
	{
	}

	CFLibArgumentUnderflowException::CFLibArgumentUnderflowException(
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		double argValue,
		double minValue )
	: cflib::CFLibArgumentException(
			CAUSE_NAME,							// Cause
			CLASS_NAME,							// ExceptionName
			argClassFieldName,					// argClassFieldName
			argMethodName,						// argMethodName
			argArgOffset,						// argArgOffset
			argArgName,							// argArgName
			std::to_string( argValue ),			// argArgValueString,
			std::to_string( minValue ),			// argArgMinValueString
			S_Empty,							// argArgMaxValueString
	 		std::string( argArgName + CFLib::S_SPACE + CFLib::S_VALUE_SPACE + std::to_string( argValue ) + S_MUST_BE_AT_LEAST + std::to_string( minValue ) ) )
	{
	}

	CFLibArgumentUnderflowException::CFLibArgumentUnderflowException(
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		const std::chrono::system_clock::time_point& argValue,
		const std::chrono::system_clock::time_point& minValue )
	: cflib::CFLibArgumentException(
			CAUSE_NAME,									// Cause
			CLASS_NAME,									// ExceptionName
			argClassFieldName,							// argClassFieldName
			argMethodName,								// argMethodName
			argArgOffset,								// argArgOffset
			argArgName,									// argArgName
			CFLibXmlUtil::formatTimestamp( argValue ),	// argArgValueString,
			CFLibXmlUtil::formatTimestamp( minValue ),	// argArgMinValueString
			S_Empty,									// argArgMaxValueString
			std::string( argArgName + CFLib::S_SPACE + CFLib::S_VALUE_SPACE + CFLibXmlUtil::formatTimestamp( argValue ) + S_MUST_BE_AT_LEAST + CFLibXmlUtil::formatTimestamp( minValue ) ) )
	{
	}

	CFLibArgumentUnderflowException::CFLibArgumentUnderflowException(
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		const std::string& argValue,
		const std::string& minValue )
	: cflib::CFLibArgumentException(
			CAUSE_NAME,							// Cause
			CLASS_NAME,							// ExceptionName
			argClassFieldName,					// argClassFieldName
			argMethodName,						// argMethodName
			argArgOffset,						// argArgOffset
			argArgName,							// argArgName
			argValue,							// argArgValueString,
			minValue,							// argArgMinValueString
			S_Empty,							// argArgMaxValueString
	 		std::string( argArgName + CFLib::S_SPACE + CFLib::S_VALUE_SPACE + argValue + S_MUST_BE_AT_LEAST + minValue ) )
	{
	}

	CFLibArgumentUnderflowException::CFLibArgumentUnderflowException(
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		mpfr_srcptr argValue,
		mpfr_srcptr minValue )
	: cflib::CFLibArgumentException(
			CAUSE_NAME,								// Cause
			CLASS_NAME,								// ExceptionName
			argClassFieldName,						// argClassFieldName
			argMethodName,							// argMethodName
			argArgOffset,							// argArgOffset
			argArgName,								// argArgName
			CFLibXmlUtil::formatMPFR( argValue ),	// argArgValueString,
			CFLibXmlUtil::formatMPFR( minValue ),	// argArgMinValueString
			S_Empty,								// argArgMaxValueString
	 		std::string( argArgName + CFLib::S_SPACE + CFLib::S_VALUE_SPACE + CFLibXmlUtil::formatMPFR( argValue ) + S_MUST_BE_AT_LEAST + CFLibXmlUtil::formatMPFR( minValue ) ) )
	{
	}

	CFLibArgumentUnderflowException::CFLibArgumentUnderflowException(
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		const CFLibGenericBigDecimal& argValue,
		const CFLibGenericBigDecimal& minValue )
	: cflib::CFLibArgumentException(
			CAUSE_NAME,							// Cause
			CLASS_NAME,							// ExceptionName
			argClassFieldName,					// argClassFieldName
			argMethodName,						// argMethodName
			argArgOffset,						// argArgOffset
			argArgName,							// argArgName
			argValue.toString(),				// argArgValueString,
			minValue.toString(),				// argArgMinValueString
			S_Empty,							// argArgMaxValueString
	 		std::string( argArgName + CFLib::S_SPACE + CFLib::S_VALUE_SPACE + argValue.toString() + S_MUST_BE_AT_LEAST + minValue.toString() ) )
	{
	}
}
