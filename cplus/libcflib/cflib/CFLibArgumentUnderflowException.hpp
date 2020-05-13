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

#include <uuid/uuid.h>
#include <mpfr.h>

#include <array>
#include <cassert>
#include <cstddef>
#include <chrono>
#include <ctime>
#include <list>
#include <string>

#include <cflib/CFLib.hpp>
#include <cflib/CFLibGenericBigDecimal.hpp>
#include <cflib/CFLibExceptionInfo.hpp>
#include <cflib/CFLibRuntimeException.hpp>
#include <cflib/CFLibArgumentException.hpp>

namespace cflib {

	class CFLibArgumentUnderflowException : public CFLibArgumentException {

	public:
		static const std::string CLASS_NAME;
		static const std::string CAUSE_NAME;
		static const std::string S_MUST_BE_AT_LEAST;

		virtual ~CFLibArgumentUnderflowException();

		CFLibArgumentUnderflowException(
			const CFLibArgumentUnderflowException& src );

		CFLibArgumentUnderflowException();

		CFLibArgumentUnderflowException( 
			const std::string& argCause,
			const std::string& argExceptionName,
			const std::string& argClassFieldName,
			const std::string& argMethodName,
			size_t argArgOffset,
			const std::string& argArgName,
			const std::string& argArgValueString,
			const std::string& argArgMinValueString,
			const std::string& argArgMaxValueString,
			const std::string& argMessageText );

		CFLibArgumentUnderflowException( 
			const std::string& argCause,
			const std::string& argExceptionName,
			const std::string& argClassFieldName,
			const std::string& argMethodName,
			size_t argArgOffset,
			const std::string& argArgName,
			const std::string& argArgValueString,
			const std::string& argMessageText );

		CFLibArgumentUnderflowException( 
			const std::string& argCause,
			const std::string& argExceptionName,
			const std::string& argClassFieldName,
			const std::string& argMethodName,
			const std::string& argMessageText );

		CFLibArgumentUnderflowException( 
			const std::string& argCause,
			const std::string& argClassFieldName,
			const std::string& argMethodName,
			const std::string& argMessageText );

		CFLibArgumentUnderflowException(
			const std::string& throwingClassName,
			const std::string& methName,
			size_t argArgOffset,
			const std::string& argArgName,
			const std::string& msg );

		CFLibArgumentUnderflowException(
			const std::string& throwingClassName,
			const std::string& methName,
			const std::string& msg );

		CFLibArgumentUnderflowException(
			const std::string& fieldName,
			const std::string& msg );

		CFLibArgumentUnderflowException(
			const std::string& msg );

		CFLibArgumentUnderflowException(
			const std::string& throwingClassName,
			const std::string& methName,
			size_t argArgOffset,
			const std::string& argArgName,
			int16_t argValue,
			int16_t minValue );

		CFLibArgumentUnderflowException(
			const std::string& throwingClassName,
			const std::string& methName,
			size_t argArgOffset,
			const std::string& argArgName,
			int32_t argValue,
			int32_t minValue );

		CFLibArgumentUnderflowException(
			const std::string& throwingClassName,
			const std::string& methName,
			size_t argArgOffset,
			const std::string& argArgName,
			int64_t argValue,
			int64_t minValue );

		CFLibArgumentUnderflowException(
			const std::string& throwingClassName,
			const std::string& methName,
			size_t argArgOffset,
			const std::string& argArgName,
			uint16_t argValue,
			uint16_t minValue );

		CFLibArgumentUnderflowException(
			const std::string& throwingClassName,
			const std::string& methName,
			size_t argArgOffset,
			const std::string& argArgName,
			uint32_t argValue,
			uint32_t minValue );

		CFLibArgumentUnderflowException(
			const std::string& throwingClassName,
			const std::string& methName,
			size_t argArgOffset,
			const std::string& argArgName,
			uint64_t argValue,
			uint64_t minValue );

		CFLibArgumentUnderflowException(
			const std::string& throwingClassName,
			const std::string& methName,
			size_t argArgOffset,
			const std::string& argArgName,
			float argValue,
			float minValue );

		CFLibArgumentUnderflowException(
			const std::string& throwingClassName,
			const std::string& methName,
			size_t argArgOffset,
			const std::string& argArgName,
			double argValue,
			double minValue );

		CFLibArgumentUnderflowException(
			const std::string& throwingClassName,
			const std::string& methName,
			size_t argArgOffset,
			const std::string& argArgName,
			const std::chrono::system_clock::time_point& argValue,
			const std::chrono::system_clock::time_point& minValue );

		CFLibArgumentUnderflowException(
			const std::string& throwingClassName,
			const std::string& methName,
			size_t argArgOffset,
			const std::string& argArgName,
			const std::string& argValue,
			const std::string& minValue );

		CFLibArgumentUnderflowException(
			const std::string& throwingClassName,
			const std::string& methName,
			size_t argArgOffset,
			const std::string& argArgName,
			mpfr_srcptr argValue,
			mpfr_srcptr minValue );

		CFLibArgumentUnderflowException(
			const std::string& throwingClassName,
			const std::string& methName,
			size_t argArgOffset,
			const std::string& argArgName,
			const CFLibGenericBigDecimal& argValue,
			const CFLibGenericBigDecimal& minValue );
	};
}
