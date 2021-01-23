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
#include <cflib/CFLibUnsupportedClassException.hpp>

namespace cflib {

	const std::string CFLibUnsupportedClassException::CLASS_NAME( "CFLibUnsupportedClassException" );
	const std::string CFLibUnsupportedClassException::CAUSE_NAME( "UnsupportedClass" );
	const std::string CFLibUnsupportedClassException::S_UNSUPPORTED_CLASS( " is unnsupported class " );
	const std::string CFLibUnsupportedClassException::S_EXPECTED( ", expected " );

	CFLibUnsupportedClassException::~CFLibUnsupportedClassException()
	{
	}

	CFLibUnsupportedClassException::CFLibUnsupportedClassException(
		const CFLibUnsupportedClassException& src )
	: cflib::CFLibIntegrityException( src )
	{
	}

	CFLibUnsupportedClassException::CFLibUnsupportedClassException()
	: cflib::CFLibIntegrityException(
			CAUSE_NAME,				// Cause
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

	CFLibUnsupportedClassException::CFLibUnsupportedClassException(
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
	: cflib::CFLibIntegrityException(
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

	CFLibUnsupportedClassException::CFLibUnsupportedClassException(
		const std::string& argCause,
		const std::string& argExceptionName,
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		const std::string& argArgValueString,
		const std::string& argMessageText )
	: cflib::CFLibIntegrityException(
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

	CFLibUnsupportedClassException::CFLibUnsupportedClassException(
		const std::string& argCause,
		const std::string& argExceptionName,
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		const std::string& argMessageText )
	: cflib::CFLibIntegrityException(
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

	CFLibUnsupportedClassException::CFLibUnsupportedClassException(
		const std::string& argCause,
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		const std::string& argMessageText )
	: cflib::CFLibIntegrityException(
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

	CFLibUnsupportedClassException::CFLibUnsupportedClassException(
		const std::string& throwingClassName,
		const std::string& methName,
		size_t argOffset,
		const std::string& argName,
		const std::string& msg )
	: cflib::CFLibIntegrityException(
			CAUSE_NAME,					// Cause
			CLASS_NAME,					// ExceptionName
			throwingClassName,			// argClassFieldName
			methName,					// argMethodName
			argOffset,					// argArgOffset
			argName,					// argArgName
			S_Empty,					// argArgValueString,
			S_Empty,					// argArgMinValueString
			S_Empty,					// argArgMaxValueString
			msg )						// argMessageText
	{
	}

	CFLibUnsupportedClassException::CFLibUnsupportedClassException(
		const std::string& throwingClassName,
		const std::string& methName,
		const std::string& msg )
	: cflib::CFLibIntegrityException(
			CAUSE_NAME,					// Cause
			CLASS_NAME,					// ExceptionName
			throwingClassName,			// argClassFieldName
			methName,					// argMethodName
			0LL,						// argArgOffset
			S_Empty,					// argArgName
			S_Empty,					// argArgValueString,
			S_Empty,					// argArgMinValueString
			S_Empty,					// argArgMaxValueString
			msg )						// argMessageText
	{
	}

	CFLibUnsupportedClassException::CFLibUnsupportedClassException(
		const std::string& msg )
	: cflib::CFLibIntegrityException(
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

	CFLibUnsupportedClassException::CFLibUnsupportedClassException(
		const std::string& throwingClassName,
		const std::string& methName,
		const std::string& argObjName,
		ICFLibAnyObj* argObj,
		const std::string& argExpectedClasses )
	: cflib::CFLibIntegrityException(
			CAUSE_NAME,					// Cause
			CLASS_NAME,					// ExceptionName
			S_Empty,					// argClassFieldName
			S_Empty,					// argMethodName
			0LL,						// argArgOffset
			S_Empty,					// argArgName
			S_Empty,					// argArgValueString,
			S_Empty,					// argArgMinValueString
			S_Empty,					// argArgMaxValueString
			std::string( argObjName + S_UNSUPPORTED_CLASS + (( argObj != NULL ) ? argObj->getClassName() : CFLib::S_EMPTY ) + S_EXPECTED + argExpectedClasses ) )
	{
	}
}

