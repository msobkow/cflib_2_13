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
#include <cflib/CFLibExceptionInfo.hpp>
#include <cflib/CFLibRuntimeException.hpp>
#include <cflib/CFLibIntegrityException.hpp>

namespace cflib {

class CFLibPrimaryKeyNotNewException : public CFLibIntegrityException {

	public:
		static const std::string CLASS_NAME;
		static const std::string CAUSE_NAME;
		static const std::string S_PKEY_IS_NOT_NEW;

		virtual ~CFLibPrimaryKeyNotNewException();

		CFLibPrimaryKeyNotNewException(
			const CFLibPrimaryKeyNotNewException& src );

		CFLibPrimaryKeyNotNewException();

		CFLibPrimaryKeyNotNewException( 
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

		CFLibPrimaryKeyNotNewException( 
			const std::string& argCause,
			const std::string& argExceptionName,
			const std::string& argClassFieldName,
			const std::string& argMethodName,
			size_t argArgOffset,
			const std::string& argArgName,
			const std::string& argArgValueString,
			const std::string& argMessageText );

		CFLibPrimaryKeyNotNewException( 
			const std::string& argCause,
			const std::string& argExceptionName,
			const std::string& argClassFieldName,
			const std::string& argMethodName,
			const std::string& argMessageText );

		CFLibPrimaryKeyNotNewException( 
			const std::string& argCause,
			const std::string& argClassFieldName,
			const std::string& argMethodName,
			const std::string& argMessageText );

		CFLibPrimaryKeyNotNewException(
			const std::string& throwingClassName,
			const std::string& methName,
			size_t argArgOffset,
			const std::string& argArgName,
			const std::string& msg );

		CFLibPrimaryKeyNotNewException(
			const std::string& throwingClassName,
			const std::string& methName,
			const std::string& msg );

		CFLibPrimaryKeyNotNewException(
			const std::string& msg );

		CFLibPrimaryKeyNotNewException(
			const std::string& throwingClassName,
			const std::string& methName,
			ICFLibAnyObj* argKey );
	};
}
