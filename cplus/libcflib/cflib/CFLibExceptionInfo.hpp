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

namespace cflib {

#	ifndef CFLIB_EXCEPT_EMPTY
#		define CFLIB_EXCEPT_EMPTY 0x0
#	endif
#	ifndef CFLIB_EXCEPT_SYSTEM
#		define CFLIB_EXCEPT_SYSTEM 0x1
#	endif
#	ifndef CFLIB_EXCEPT_XERCES
#		define CFLIB_EXCEPT_XERCES 0x2
#	endif
#	ifndef CFLIB_EXCEPT_CFLIB
#		define CFLIB_EXCEPT_CFLIB 0x4
#	endif

	typedef int32_t cflibexcflags_t;

	class CFLibExceptionInfo {

	public:
		static const std::string S_Empty;
		static const std::string S_EXCEPTION;
		static const std::string S_CaughtXercesException;
		static const std::string S_CaughtSystemException;
		static const std::string S_SAXNotRecognizedException;
		static const std::string S_SAXNotSupportedException;
		static const std::string S_SAXParseException;
		static const std::string S_SAXException;
		static const std::string S_invalid_argument;
		static const std::string S_domain_error;
		static const std::string S_length_error;
		static const std::string S_out_of_range;
		static const std::string S_future_error;
		static const std::string S_logic_error;
		static const std::string S_bad_optional_access;
		static const std::string S_range_error;
		static const std::string S_overflow_error;
		static const std::string S_regex_error;
		static const std::string S_ios_base_failure;
		static const std::string S_filesystem_error;
		static const std::string S_system_error;
		static const std::string S_nonexistent_local_time;
		static const std::string S_ambiguous_local_time;
		static const std::string S_format_error;
		static const std::string S_bad_typeid;
		static const std::string S_bad_any_cast;
		static const std::string S_bad_cast;
		static const std::string S_bad_weak_ptr;
		static const std::string S_bad_function_call;
		static const std::string S_bad_array_new_length;
		static const std::string S_bad_alloc;
		static const std::string S_bad_exception;
		static const std::string S_bad_variant_access;
		static const std::string S_std_exception;

	protected:
		cflibexcflags_t excFlags;
		std::string excCause;
		std::string excExceptionName;
		std::string excClassFieldName;
		std::string excMethodName;
		size_t excArgOffset;
		std::string excArgName;
		std::string excArgValueString;
		std::string excArgMinValueString;
		std::string excArgMaxValueString;
		std::string excMessageText;

	public:
		virtual ~CFLibExceptionInfo();

		CFLibExceptionInfo( const CFLibExceptionInfo& src );

		CFLibExceptionInfo();

		CFLibExceptionInfo( 
			cflibexcflags_t argFlags,
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

		CFLibExceptionInfo( 
			cflibexcflags_t argFlags,
			const std::string& argCause,
			const std::string& argExceptionName,
			const std::string& argClassFieldName,
			const std::string& argMethodName,
			size_t argArgOffset,
			const std::string& argArgName,
			const std::string& argArgValueString,
			const std::string& argMessageText );

		CFLibExceptionInfo( 
			cflibexcflags_t argFlags,
			const std::string& argCause,
			const std::string& argExceptionName,
			const std::string& argClassFieldName,
			const std::string& argMethodName,
			const std::string& argMessageText );

		CFLibExceptionInfo( 
			cflibexcflags_t argFlags,
			const std::string& argCause,
			const std::string& argClassFieldName,
			const std::string& argMethodName,
			const std::string& argMessageText );

		CFLibExceptionInfo( 
			cflibexcflags_t argFlags,
			const std::string& argCause,
			const std::string& argClassFieldName,
			const std::string& argMessageText );

		CFLibExceptionInfo( 
			cflibexcflags_t argFlags,
			const std::string& argClassFieldName,
			const std::string& argMessageText );

		CFLibExceptionInfo( 
			cflibexcflags_t argFlags,
			const std::string& argMessageText );

		CFLibExceptionInfo& operator =( const CFLibExceptionInfo& src );

		inline cflibexcflags_t getFlags() const {
			return( excFlags );
		}

		inline bool empty() const {
			return( excFlags == CFLIB_EXCEPT_EMPTY );
		}

		inline bool isCFLibException() const {
			return( ( excFlags & CFLIB_EXCEPT_CFLIB ) == CFLIB_EXCEPT_CFLIB );
		}

		inline bool isSystemException() const {
			return( ( excFlags & CFLIB_EXCEPT_SYSTEM ) == CFLIB_EXCEPT_SYSTEM );
		}

		inline bool isXercesException() const {
			return( ( excFlags & CFLIB_EXCEPT_XERCES ) == CFLIB_EXCEPT_XERCES );
		}

		inline void setIsCFLibException() {
			excFlags = CFLIB_EXCEPT_CFLIB;
		}

		inline void setIsSystemException() {
			excFlags = CFLIB_EXCEPT_SYSTEM;
		}

		inline void setIsXercesException() {
			excFlags = CFLIB_EXCEPT_XERCES;
		}

		// Reset the exception info to its new/empty state
		virtual void reset();

		virtual const std::string& getCause() const;
		virtual void setCause( const std::string& value );

		virtual const std::string& getExceptionName() const;
		virtual void setExceptionName( const std::string& value );

		virtual const std::string& getClassFieldName() const;
		virtual void setClassFieldName( const std::string& value );

		virtual const std::string& getMethodName() const;
		virtual void setMethodName( const std::string& value );

		virtual size_t getArgOffset() const;
		virtual void setArgOffset( size_t value );

		virtual const std::string& getArgName() const;
		virtual void setArgName( const std::string& value );

		virtual const std::string& getArgValueString() const;
		virtual void setArgValueString( const std::string& value );

		virtual const std::string& getArgMinValueString() const;
		virtual void setArgMinValueString( const std::string& value );

		virtual const std::string& getArgMaxValueString() const;
		virtual void setArgMaxValueString( const std::string& value );

		virtual const std::string& getMessageText() const;
		virtual std::string getMessageTextFirstLine();
		virtual void setMessageText( const std::string& value );
	
		virtual std::string getFormattedSystemText( 
			const std::string& argExceptionName,
			const std::string& argClassFieldName,
			const std::string& argMethodName,
			const std::string& argMessageText );
	
		virtual std::string getFormattedXercesText( 
			const std::string& argExceptionName,
			const std::string& argClassFieldName,
			const std::string& argMethodName,
			const std::string& argMessageText );

		virtual std::string getFormattedText( 
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

		virtual std::string getEffectiveMessage();
		virtual std::string getEffectiveMessageFirstLine();

		virtual std::string getFormattedMessage();
		virtual std::string getFormattedMessageFirstLine();
	};
}
