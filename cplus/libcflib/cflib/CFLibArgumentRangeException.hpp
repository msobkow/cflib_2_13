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

	class CFLibArgumentRangeException : public CFLibArgumentException {

	public:
		static const std::string CLASS_NAME;
		static const std::string CAUSE_NAME;
		static const std::string S_IS_OUT_OF_THE_RANGE;
		static const std::string S_VALUE_OUT_OF_RANGE;

		virtual ~CFLibArgumentRangeException();

		CFLibArgumentRangeException(
			const CFLibArgumentRangeException& src );

		CFLibArgumentRangeException();

		CFLibArgumentRangeException( 
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

		CFLibArgumentRangeException( 
			const std::string& argCause,
			const std::string& argExceptionName,
			const std::string& argClassFieldName,
			const std::string& argMethodName,
			size_t argArgOffset,
			const std::string& argArgName,
			const std::string& argArgValueString,
			const std::string& argMessageText );

		CFLibArgumentRangeException( 
			const std::string& argCause,
			const std::string& argExceptionName,
			const std::string& argClassFieldName,
			const std::string& argMethodName,
			const std::string& argMessageText );

		CFLibArgumentRangeException( 
			const std::string& argCause,
			const std::string& argClassFieldName,
			const std::string& argMethodName,
			const std::string& argMessageText );

		CFLibArgumentRangeException(
			const std::string& throwingClassName,
			const std::string& methName,
			size_t argArgOffset,
			const std::string& argArgName,
			const std::string& msg );

		CFLibArgumentRangeException(
			const std::string& throwingClassName,
			const std::string& methName,
			const std::string& msg );

		CFLibArgumentRangeException(
			const std::string& fieldName,
			const std::string& msg );

		CFLibArgumentRangeException(
			const std::string& msg );

// MSS WORKING TODO NEED TO MIGRATE THE FOLLOWING SPECIALIZATIONS

		CFLibArgumentRangeException(
			const std::string& throwingClassName,
			const std::string& methName,
			size_t argArgOffset,
			const std::string& argArgName,
			int16_t argValue,
			int16_t minValue,
			int16_t maxValue );

		CFLibArgumentRangeException(
			const std::string& throwingClassName,
			const std::string& methName,
			size_t argArgOffset,
			const std::string& argArgName,
			int32_t argValue,
			int32_t minValue,
			int32_t maxValue );

		CFLibArgumentRangeException(
			const std::string& throwingClassName,
			const std::string& methName,
			size_t argArgOffset,
			const std::string& argArgName,
			int64_t argValue,
			int64_t minValue,
			int64_t maxValue );

		CFLibArgumentRangeException(
			const std::string& throwingClassName,
			const std::string& methName,
			size_t argArgOffset,
			const std::string& argArgName,
			uint16_t argValue,
			uint16_t minValue,
			uint16_t maxValue );

		CFLibArgumentRangeException(
			const std::string& throwingClassName,
			const std::string& methName,
			size_t argArgOffset,
			const std::string& argArgName,
			uint32_t argValue,
			uint32_t minValue,
			uint32_t maxValue );

		CFLibArgumentRangeException(
			const std::string& throwingClassName,
			const std::string& methName,
			size_t argArgOffset,
			const std::string& argArgName,
			uint64_t argValue,
			uint64_t minValue,
			uint64_t maxValue );

		CFLibArgumentRangeException(
			const std::string& throwingClassName,
			const std::string& methName,
			size_t argArgOffset,
			const std::string& argArgName,
			float argValue,
			float minValue,
			float maxValue );

		CFLibArgumentRangeException(
			const std::string& throwingClassName,
			const std::string& methName,
			size_t argArgOffset,
			const std::string& argArgName,
			double argValue,
			double minValue,
			double maxValue );

		CFLibArgumentRangeException(
			const std::string& throwingClassName,
			const std::string& methName,
			size_t argArgOffset,
			const std::string& argArgName,
			const std::chrono::system_clock::time_point& argValue,
			const std::chrono::system_clock::time_point& minValue,
			const std::chrono::system_clock::time_point& maxValue );

		CFLibArgumentRangeException(
			const std::string& throwingClassName,
			const std::string& methName,
			size_t argArgOffset,
			const std::string& argArgName,
			const std::string& argValue,
			const std::string& minValue,
			const std::string& maxValue );

		CFLibArgumentRangeException(
			const std::string& throwingClassName,
			const std::string& methName,
			size_t argArgOffset,
			const std::string& argArgName,
			mpfr_srcptr argValue,
			mpfr_srcptr minValue,
			mpfr_srcptr maxValue );

		CFLibArgumentRangeException(
			const std::string& throwingClassName,
			const std::string& methName,
			size_t argArgOffset,
			const std::string& argArgName,
			const CFLibGenericBigDecimal& argValue,
			const CFLibGenericBigDecimal& minValue,
			const CFLibGenericBigDecimal& maxValue );
	};
}
