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

#include <ctype.h>
#include <uuid/uuid.h>
#include <time.h>
#include <memory.h>

#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <chrono>
#include <ctime>
#include <list>
#include <string>
#include <tuple>
#include <vector>
#include <stdexcept>

#include <cflib/ICFLibAnyObj.hpp>
#include <cflib/ICFLibMessageLog.hpp>

#include <cflib/CFLibGenericBigDecimal.hpp>

#include <cflib/CFLibNullable.hpp>
#include <cflib/CFLibNullableBool.hpp>
#include <cflib/CFLibNullableInt16.hpp>
#include <cflib/CFLibNullableInt32.hpp>
#include <cflib/CFLibNullableInt64.hpp>
#include <cflib/CFLibNullableUInt16.hpp>
#include <cflib/CFLibNullableUInt32.hpp>
#include <cflib/CFLibNullableUInt64.hpp>
#include <cflib/CFLibNullableFloat.hpp>
#include <cflib/CFLibNullableDouble.hpp>

#ifdef _WINDOWS
extern "C" char * strtok_r(char *str, const char *delim, char **saveptr);
#endif

#ifndef uuid_ptr_t
#	define uuid_ptr_t unsigned char *
#endif

#ifndef classcode_t
#	define classcode_t int32_t
#endif

namespace cflib {

	typedef unsigned char BYTE;

	class CFLib {
	public:

		static const std::string CLASS_NAME;
		static const std::string S_EMPTY;
		static const std::string S_TRUE;
		static const std::string S_FALSE;
		static const std::string S_DOUBLE_COLON;
		static const std::string S_DOT;
		static const std::string S_DOT_DOT;
		static const std::string S_SPACE;
		static const std::string S_PAREN_SPACE;
		static const std::string S_PAREN_SPACE_ARGUMENT;
		static const std::string S_VALUE_SPACE;
		static const std::string S_NO_MESSAGE_PROVIDED;
		static const std::string S_SUBROUTINE;
		static const std::string S_RETURNED;
		static const std::string S_COMMASPACE;
		static const std::string LinkName;
		static const std::string LinkVersion;
		static const std::string S_MsgInitMustBeCalledFirst;

	protected:

		static bool initialized;

	public:
		CFLib();
		virtual ~CFLib();

		static bool isInitialized();
		static void init();
		static void release();

		static const classcode_t evalClassCode( const std::string& classCode );
		static std::string formatClassCode( const classcode_t classCode );

		static std::string base64_encode(BYTE const* buf, unsigned int bufLen);
		static std::vector<BYTE>* base64_decode(const std::string& encoded_string);

		static void beep();

		/* Look for tag=someValue within filename.  When found, return someValue
		 * in the provided value parameter up to valueSize in length.  If someValue
		 * is enclosed in quotes, remove them. */
		static char* getValue( const char* filename, const char* tag, char* value, std::string::size_type valueSize );

		static std::chrono::system_clock::time_point* getUTCTimestamp();
		static std::chrono::system_clock::time_point getUTCTimestampInstance();

		static std::chrono::system_clock::time_point* getUTCGregorianCalendar(
			int year,
			int month,
			int day,
			int hour,
			int minute,
			int second );
		static std::chrono::system_clock::time_point getUTCGregorianCalendarInstance(
			int year,
			int month,
			int day,
			int hour,
			int minute,
			int second );

		static void uuidFromString( uuid_t& target, const char* value );

		const std::string* getLinkName();
	
		const std::string* getLinkVersion();

		static size_t hash( const uuid_ptr_t value );

		static size_t hash( const std::string* value );

		static size_t hash( const std::string& value );

		static size_t hash( const std::chrono::system_clock::time_point& value );

		static size_t hash( const std::vector<BYTE>& value );

		static bool startsWith( const std::string& str, const std::string& match );
		static void createDirectory( const std::string& fullDirPath );
	};
}
