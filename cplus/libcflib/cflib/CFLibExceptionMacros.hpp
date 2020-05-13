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

#include <array>
#include <cassert>
#include <cstddef>
#include <chrono>
#include <ctime>
#include <list>
#include <string>
#include <future>
#include <regex>
#include <filesystem>
#include <chrono>
#include <any>
#include <variant>

#include <cflib/CFLibExceptionInfo.hpp>

#define CFLIB_EXCEPTION_DECLINFO \
	cflib::CFLibExceptionInfo exceptionInfo;

#define CFLIB_EXCEPTION_EMPTY \
	exceptionInfo.empty()

#define CFLIB_EXCEPTION_CATCH_FALLTHROUGH \
	catch( xercesc::SAXNotRecognizedException e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsXercesException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtXercesException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_SAXNotRecognizedException ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		const XMLCh* message = e.getMessage(); \
		if( message != NULL ) { \
			char* cUseMessage = xercesc::XMLString::transcode( message ); \
			if( cUseMessage != NULL ) { \
				std::string cppMessage( cUseMessage ); \
				exceptionInfo.setMessageText( cppMessage ); \
				xercesc::XMLString::release( &cUseMessage ); \
				cUseMessage = NULL; \
			} \
		} \
	} \
	catch( xercesc::SAXNotSupportedException e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsXercesException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtXercesException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_SAXNotSupportedException ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		const XMLCh* message = e.getMessage(); \
		if( message != NULL ) { \
			char* cUseMessage = xercesc::XMLString::transcode( message ); \
			if( cUseMessage != NULL ) { \
				std::string cppMessage( cUseMessage ); \
				exceptionInfo.setMessageText( cppMessage ); \
				xercesc::XMLString::release( &cUseMessage ); \
				cUseMessage = NULL; \
			} \
		} \
	} \
	catch( xercesc::SAXParseException e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsXercesException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtXercesException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_SAXParseException ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		const XMLCh* message = e.getMessage(); \
		if( message != NULL ) { \
			char* cUseMessage = xercesc::XMLString::transcode( message ); \
			if( cUseMessage != NULL ) { \
				std::string cppMessage( cUseMessage ); \
				exceptionInfo.setMessageText( cppMessage ); \
				xercesc::XMLString::release( &cUseMessage ); \
				cUseMessage = NULL; \
			} \
		} \
	} \
	catch( xercesc::SAXException e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsXercesException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtXercesException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_SAXException ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		const XMLCh* message = e.getMessage(); \
		if( message != NULL ) { \
			char* cUseMessage = xercesc::XMLString::transcode( message ); \
			if( cUseMessage != NULL ) { \
				std::string cppMessage( cUseMessage ); \
				exceptionInfo.setMessageText( cppMessage ); \
				xercesc::XMLString::release( &cUseMessage ); \
				cUseMessage = NULL; \
			} \
		} \
	} \
	catch( cflib::CFLibArgumentOverflowException e ) { \
		exceptionInfo = e; \
	} \
	catch( cflib::CFLibArgumentRangeException e ) { \
		exceptionInfo = e; \
	} \
	catch( cflib::CFLibArgumentUnderflowException e ) { \
		exceptionInfo = e; \
	} \
	catch( cflib::CFLibEmptyArgumentException e ) { \
		exceptionInfo = e; \
	} \
	catch( cflib::CFLibInvalidArgumentException e ) { \
		exceptionInfo = e; \
	} \
	catch( cflib::CFLibNullArgumentException e ) { \
		exceptionInfo = e; \
	} \
	catch( cflib::CFLibArgumentException e ) { \
		exceptionInfo = e; \
	} \
	catch( cflib::CFLibMustOverrideException e ) { \
		exceptionInfo = e; \
	} \
	catch( cflib::CFLibNotImplementedYetException e ) { \
		exceptionInfo = e; \
	} \
	catch( cflib::CFLibNotSupportedException e ) { \
		exceptionInfo = e; \
	} \
	catch( cflib::CFLibUsageException e ) { \
		exceptionInfo = e; \
	} \
	catch( cflib::CFLibCodeStateException e ) { \
		exceptionInfo = e; \
	} \
	catch( cflib::CFLibDependentsDetectedException e ) { \
		exceptionInfo = e; \
	} \
	catch( cflib::CFLibPrimaryKeyNotNewException e ) { \
		exceptionInfo = e; \
	} \
	catch( cflib::CFLibUniqueIndexViolationException e ) { \
		exceptionInfo = e; \
	} \
	catch( cflib::CFLibUnrecognizedAttributeException e ) { \
		exceptionInfo = e; \
	} \
	catch( cflib::CFLibUnresolvedRelationException e ) { \
		exceptionInfo = e; \
	} \
	catch( cflib::CFLibUnsupportedClassException e ) { \
		exceptionInfo = e; \
	} \
	catch( cflib::CFLibIntegrityException e ) { \
		exceptionInfo = e; \
	} \
	catch( cflib::CFLibCollisionDetectedException e ) { \
		exceptionInfo = e; \
	} \
	catch( cflib::CFLibDbException e ) { \
		exceptionInfo = e; \
	} \
	catch( cflib::CFLibMathException e ) { \
		exceptionInfo = e; \
	} \
	catch( cflib::CFLibStaleCacheDetectedException e ) { \
		exceptionInfo = e; \
	} \
	catch( cflib::CFLibSubroutineException e ) { \
		exceptionInfo = e; \
	} \
	catch( cflib::CFLibWrapSystemException e ) { \
		exceptionInfo = e; \
	} \
	catch( cflib::CFLibWrapXercesException e ) { \
		exceptionInfo = e; \
	} \
	catch( cflib::CFLibRuntimeException e ) { \
		exceptionInfo = e; \
	} \
	catch( std::invalid_argument e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_invalid_argument ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
	} \
	catch( std::domain_error e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_domain_error ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
	} \
	catch( std::length_error e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_length_error ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
	} \
	catch( std::out_of_range e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_out_of_range ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
	} \
	catch( std::future_error e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_future_error ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
	} \
	catch( std::logic_error e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_logic_error ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
	} \
	catch( std::bad_optional_access e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_bad_optional_access ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
	} \
	catch( std::range_error e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_range_error ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
	} \
	catch( std::overflow_error e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_overflow_error ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
	} \
	catch( std::regex_error e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_regex_error ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
	} \
	catch( std::ios_base::failure e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_ios_base_failure ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
	} \
	catch( std::filesystem::filesystem_error e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_filesystem_error ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
	} \
	catch( std::system_error e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_system_error ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
	} \
	catch( std::bad_typeid e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_bad_typeid ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
	} \
	catch( std::bad_any_cast e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_bad_any_cast ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
	} \
	catch( std::bad_cast e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_bad_cast ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
	} \
	catch( std::bad_weak_ptr e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_bad_weak_ptr ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
	} \
	catch( std::bad_function_call e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_bad_function_call ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
	} \
	catch( std::bad_array_new_length e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_bad_array_new_length ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
	} \
	catch( std::bad_alloc e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_bad_alloc ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
	} \
	catch( std::bad_exception e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_bad_exception ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
	} \
	catch( std::bad_variant_access e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_bad_variant_access ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
	} \
	catch( std::exception e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_std_exception ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
	}

#define CFLIB_EXCEPTION_CATCH_GOTO(cleanup) \
	catch( xercesc::SAXNotRecognizedException e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsXercesException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtXercesException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_SAXNotRecognizedException ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		const XMLCh* message = e.getMessage(); \
		if( message != NULL ) { \
			char* cUseMessage = xercesc::XMLString::transcode( message ); \
			if( cUseMessage != NULL ) { \
				std::string cppMessage( cUseMessage ); \
				exceptionInfo.setMessageText( cppMessage ); \
				xercesc::XMLString::release( &cUseMessage ); \
				cUseMessage = NULL; \
			} \
		} \
		goto cleanup; \
	} \
	catch( xercesc::SAXNotSupportedException e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsXercesException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtXercesException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_SAXNotSupportedException ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		const XMLCh* message = e.getMessage(); \
		if( message != NULL ) { \
			char* cUseMessage = xercesc::XMLString::transcode( message ); \
			if( cUseMessage != NULL ) { \
				std::string cppMessage( cUseMessage ); \
				exceptionInfo.setMessageText( cppMessage ); \
				xercesc::XMLString::release( &cUseMessage ); \
				cUseMessage = NULL; \
			} \
		} \
		goto cleanup; \
	} \
	catch( xercesc::SAXParseException e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsXercesException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtXercesException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_SAXParseException ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		const XMLCh* message = e.getMessage(); \
		if( message != NULL ) { \
			char* cUseMessage = xercesc::XMLString::transcode( message ); \
			if( cUseMessage != NULL ) { \
				std::string cppMessage( cUseMessage ); \
				exceptionInfo.setMessageText( cppMessage ); \
				xercesc::XMLString::release( &cUseMessage ); \
				cUseMessage = NULL; \
			} \
		} \
		goto cleanup; \
	} \
	catch( xercesc::SAXException e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsXercesException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtXercesException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_SAXException ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		const XMLCh* message = e.getMessage(); \
		if( message != NULL ) { \
			char* cUseMessage = xercesc::XMLString::transcode( message ); \
			if( cUseMessage != NULL ) { \
				std::string cppMessage( cUseMessage ); \
				exceptionInfo.setMessageText( cppMessage ); \
				xercesc::XMLString::release( &cUseMessage ); \
				cUseMessage = NULL; \
			} \
		} \
		goto cleanup; \
	} \
	catch( cflib::CFLibArgumentOverflowException e ) { \
		exceptionInfo = e; \
		goto cleanup; \
	} \
	catch( cflib::CFLibArgumentRangeException e ) { \
		exceptionInfo = e; \
		goto cleanup; \
	} \
	catch( cflib::CFLibArgumentUnderflowException e ) { \
		exceptionInfo = e; \
		goto cleanup; \
	} \
	catch( cflib::CFLibEmptyArgumentException e ) { \
		exceptionInfo = e; \
		goto cleanup; \
	} \
	catch( cflib::CFLibInvalidArgumentException e ) { \
		exceptionInfo = e; \
		goto cleanup; \
	} \
	catch( cflib::CFLibNullArgumentException e ) { \
		exceptionInfo = e; \
		goto cleanup; \
	} \
	catch( cflib::CFLibArgumentException e ) { \
		exceptionInfo = e; \
		goto cleanup; \
	} \
	catch( cflib::CFLibMustOverrideException e ) { \
		exceptionInfo = e; \
		goto cleanup; \
	} \
	catch( cflib::CFLibNotImplementedYetException e ) { \
		exceptionInfo = e; \
		goto cleanup; \
	} \
	catch( cflib::CFLibNotSupportedException e ) { \
		exceptionInfo = e; \
		goto cleanup; \
	} \
	catch( cflib::CFLibUsageException e ) { \
		exceptionInfo = e; \
		goto cleanup; \
	} \
	catch( cflib::CFLibCodeStateException e ) { \
		exceptionInfo = e; \
		goto cleanup; \
	} \
	catch( cflib::CFLibDependentsDetectedException e ) { \
		exceptionInfo = e; \
		goto cleanup; \
	} \
	catch( cflib::CFLibPrimaryKeyNotNewException e ) { \
		exceptionInfo = e; \
		goto cleanup; \
	} \
	catch( cflib::CFLibUniqueIndexViolationException e ) { \
		exceptionInfo = e; \
		goto cleanup; \
	} \
	catch( cflib::CFLibUnrecognizedAttributeException e ) { \
		exceptionInfo = e; \
		goto cleanup; \
	} \
	catch( cflib::CFLibUnresolvedRelationException e ) { \
		exceptionInfo = e; \
		goto cleanup; \
	} \
	catch( cflib::CFLibUnsupportedClassException e ) { \
		exceptionInfo = e; \
		goto cleanup; \
	} \
	catch( cflib::CFLibIntegrityException e ) { \
		exceptionInfo = e; \
		goto cleanup; \
	} \
	catch( cflib::CFLibCollisionDetectedException e ) { \
		exceptionInfo = e; \
		goto cleanup; \
	} \
	catch( cflib::CFLibDbException e ) { \
		exceptionInfo = e; \
		goto cleanup; \
	} \
	catch( cflib::CFLibMathException e ) { \
		exceptionInfo = e; \
		goto cleanup; \
	} \
	catch( cflib::CFLibStaleCacheDetectedException e ) { \
		exceptionInfo = e; \
		goto cleanup; \
	} \
	catch( cflib::CFLibSubroutineException e ) { \
		exceptionInfo = e; \
		goto cleanup; \
	} \
	catch( cflib::CFLibWrapSystemException e ) { \
		exceptionInfo = e; \
		goto cleanup; \
	} \
	catch( cflib::CFLibWrapXercesException e ) { \
		exceptionInfo = e; \
		goto cleanup; \
	} \
	catch( cflib::CFLibRuntimeException e ) { \
		exceptionInfo = e; \
		goto cleanup; \
	} \
	catch( std::invalid_argument e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_invalid_argument ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
		goto cleanup; \
	} \
	catch( std::domain_error e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_domain_error ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
		goto cleanup; \
	} \
	catch( std::length_error e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_length_error ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
		goto cleanup; \
	} \
	catch( std::out_of_range e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_out_of_range ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
		goto cleanup; \
	} \
	catch( std::future_error e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_future_error ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
		goto cleanup; \
	} \
	catch( std::logic_error e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_logic_error ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
		goto cleanup; \
	} \
	catch( std::bad_optional_access e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_bad_optional_access ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
		goto cleanup; \
	} \
	catch( std::range_error e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_range_error ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
		goto cleanup; \
	} \
	catch( std::overflow_error e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_overflow_error ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
		goto cleanup; \
	} \
	catch( std::regex_error e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_regex_error ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
		goto cleanup; \
	} \
	catch( std::ios_base::failure e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_ios_base_failure ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
		goto cleanup; \
	} \
	catch( std::filesystem::filesystem_error e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_filesystem_error ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
		goto cleanup; \
	} \
	catch( std::system_error e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_system_error ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
		goto cleanup; \
	} \
	catch( std::bad_typeid e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_bad_typeid ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
		goto cleanup; \
	} \
	catch( std::bad_any_cast e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_bad_any_cast ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
		goto cleanup; \
	} \
	catch( std::bad_cast e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_bad_cast ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
		goto cleanup; \
	} \
	catch( std::bad_weak_ptr e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_bad_weak_ptr ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
		goto cleanup; \
	} \
	catch( std::bad_function_call e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_bad_function_call ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
		goto cleanup; \
	} \
	catch( std::bad_array_new_length e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_bad_array_new_length ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
		goto cleanup; \
	} \
	catch( std::bad_alloc e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_bad_alloc ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
		goto cleanup; \
	} \
	catch( std::bad_exception e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_bad_exception ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
		goto cleanup; \
	} \
	catch( std::bad_variant_access e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_bad_variant_access ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
		goto cleanup; \
	} \
	catch( std::exception e ) { \
		if( ! exceptionInfo.empty() ) { \
			exceptionInfo.reset(); \
		} \
		exceptionInfo.setIsSystemException(); \
		exceptionInfo.setCause( cflib::CFLibExceptionInfo::S_CaughtSystemException ); \
		exceptionInfo.setExceptionName( cflib::CFLibExceptionInfo::S_std_exception ); \
		exceptionInfo.setClassFieldName( CLASS_NAME ); \
		exceptionInfo.setMethodName( S_ProcName ); \
		exceptionInfo.setMessageText( e.what() ); \
		goto cleanup; \
	}

#define CFLIB_EXCEPTION_RETHROW_CFLIBEXCEPTION \
	if( ! exceptionInfo.empty() ) { \
		if( exceptionInfo.isCFLibException() ) { \
			throw cflib::CFLibRuntimeException( exceptionInfo ); \
		} \
		else if( exceptionInfo.isXercesException() ) { \
			throw cflib::CFLibWrapXercesException( CLASS_NAME, \
				S_ProcName, \
				exceptionInfo.getExceptionName(), \
				exceptionInfo.getMessageText() ); \
		} \
		else if( exceptionInfo.isSystemException() ) { \
			throw cflib::CFLibWrapSystemException( CLASS_NAME, \
				S_ProcName, \
				exceptionInfo.getExceptionName(), \
				exceptionInfo.getMessageText() ); \
		} \
	}

#define CFLIB_EXCEPTION_RETHROW_SAXEXCEPTION \
	if( ! exceptionInfo.empty() ) { \
		if( exceptionInfo.isCFLibException() ) { \
			throw xercesc::SAXException( exceptionInfo.getFormattedText( exceptionInfo.getCause(), \
				exceptionInfo.getExceptionName(), \
				exceptionInfo.getClassFieldName(), \
				exceptionInfo.getMethodName(), \
				exceptionInfo.getArgOffset(), \
				exceptionInfo.getArgName(), \
				exceptionInfo.getArgValueString(), \
				exceptionInfo.getArgMinValueString(), \
				exceptionInfo.getArgMaxValueString(), \
				exceptionInfo.getMessageText() ).c_str() ); \
		} \
		else if( exceptionInfo.isXercesException() ) { \
			if( exceptionInfo.getExceptionName() == cflib::CFLibExceptionInfo::S_SAXException ) { \
				throw xercesc::SAXException( exceptionInfo.getMessageText().c_str() ); \
			} \
			else { \
				throw xercesc::SAXException( exceptionInfo.getFormattedXercesText( exceptionInfo.getExceptionName(), \
					CLASS_NAME, \
					S_ProcName, \
					exceptionInfo.getMessageText() ).c_str() ); \
			} \
		} \
		else if( exceptionInfo.isSystemException() ) { \
			throw xercesc::SAXException( exceptionInfo.getFormattedSystemText( exceptionInfo.getExceptionName(), \
				CLASS_NAME, \
				S_ProcName, \
				exceptionInfo.getMessageText() ).c_str() ); \
		} \
		else { \
			throw xercesc::SAXException( exceptionInfo.getFormattedMessage().c_str() ); \
		} \
	}

#define CFLIB_EXCEPTION_FORMATTEDMESSAGE \
	exceptionInfo.getFormattedMessage()

#define CFLIB_EXCEPTION_FORMATTEDMESSAGEFIRSTLINE \
	exceptionInfo.getFormattedMessageFirstLine()

#define CFLIB_EXCEPTION_RESET \
	exceptionInfo.reset();

