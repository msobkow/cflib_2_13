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

#include <array>
#include <cassert>
#include <cstddef>
#include <chrono>
#include <ctime>
#include <list>
#include <string>

#include <cflib/CFLibExceptionInfo.hpp>

namespace cflib {

	class CFLibRuntimeException;

		class CFLibArgumentException;
			class CFLibArgumentOverflowException;
			class CFLibArgumentRangeException;
			class CFLibArgumentUnderflowException;
			class CFLibEmptyArgumentException;
			class CFLibInvalidArgumentException;
			class CFLibNullArgumentException;

		class CFLibCodeStateException;
			class CFLibMustOverrideException;
			class CFLibNotImplementedYetException;
			class CFLibNotSupportedException;
			class CFLibUsageException;

		class CFLibIntegrityException;
			class CFLibDependentsDetectedException;
			class CFLibPrimaryKeyNotNewException;
			class CFLibUniqueIndexViolationException;
			class CFLibUnrecognizedAttributeException;
			class CFLibUnresolvedRelationException;
			class CFLibUnsupportedClassException;

		class CFLibCollisionDetectedException;
		class CFLibDbException;
		class CFLibMathException;
		class CFLibStaleCacheDetectedException;
		class CFLibSubroutineException;

		class CFLibWrapXercesException;
		class CFLibWrapSystemException;

	class CFLibRuntimeException : public std::runtime_error, public cflib::CFLibExceptionInfo {

	public:
		static const std::string CLASS_NAME;
		static const std::string CAUSE_NAME;

		virtual ~CFLibRuntimeException();

		CFLibRuntimeException(
			const CFLibRuntimeException& src );

		CFLibRuntimeException(
			CFLibExceptionInfo& src );

		CFLibRuntimeException();

		CFLibRuntimeException( 
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

		CFLibRuntimeException( 
			const std::string& argCause,
			const std::string& argExceptionName,
			const std::string& argClassFieldName,
			const std::string& argMethodName,
			size_t argArgOffset,
			const std::string& argArgName,
			const std::string& argArgValueString,
			const std::string& argMessageText );

		CFLibRuntimeException( 
			const std::string& argCause,
			const std::string& argExceptionName,
			const std::string& argClassFieldName,
			const std::string& argMethodName,
			const std::string& argMessageText );

		CFLibRuntimeException( 
			const std::string& argCause,
			const std::string& argClassFieldName,
			const std::string& argMethodName,
			const std::string& argMessageText );

		CFLibRuntimeException(
			const std::string& throwingClassName,
			const std::string& methName,
			size_t argOffset,
			const std::string& argName,
			const std::string& msg );

		CFLibRuntimeException(
			const std::string& throwingClassName,
			const std::string& methName,
			const std::string& msg );

		CFLibRuntimeException(
			const std::string& fieldName,
			const std::string& msg );

		CFLibRuntimeException(
			const std::string& msg );
	};
}
