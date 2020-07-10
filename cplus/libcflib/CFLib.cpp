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

#include <sys/stat.h>
#include <iostream>
#include <fstream>

#include <cflib/CFLib.hpp>
#include <cflib/CFLibNotSupportedException.hpp>
#include <cflib/CFLibNullArgumentException.hpp>
#include <cflib/CFLibXmlCore.hpp>
#include <cflib/CFLibXmlCoreParser.hpp>

#ifdef _WINDOWS
extern "C" char * strtok_r(char *str, const char *delim, char **saveptr) {
	if ((delim != NULL) && (*delim != '\000') && (saveptr != NULL)){
		if (str != NULL) {
			// This is the first invocation for a given argument string
			*saveptr = str;
		}
		char * start = *saveptr;
		if (*start == NULL) {
			return(NULL);
		}
		char * found = strstr(start, delim);
		if (found == NULL) {
			*saveptr = start + strlen(start);
			return(start);
		}
		std::string::size_type vallen = found - start;
		char * retval = new char[vallen + 1];
		strncpy(retval, start, vallen);
		retval[vallen] = '\000';
		*saveptr = found + strlen(delim);
		return(retval);
	}
	else {
		return(NULL);
	}
}
#endif

namespace cflib {

	const std::string CFLib::CLASS_NAME( "CFLib" );
	const std::string CFLib::S_EMPTY( "" );
	const std::string CFLib::S_TRUE( "true" );
	const std::string CFLib::S_FALSE( "false" );
	const std::string CFLib::S_DOUBLE_COLON( "::" );
	const std::string CFLib::S_DOT( "." );
	const std::string CFLib::S_DOT_DOT( ".." );
	const std::string CFLib::S_SPACE( " " );
	const std::string CFLib::S_PAREN_SPACE( "() " );
	const std::string CFLib::S_PAREN_SPACE_ARGUMENT( "() Argument " );
	const std::string CFLib::S_VALUE_SPACE( "Value " );
	const std::string CFLib::S_NO_MESSAGE_PROVIDED( "No message provided" );
	const std::string CFLib::S_SUBROUTINE( " Subroutine " );
	const std::string CFLib::S_RETURNED( " returned " );
	const std::string CFLib::S_COMMASPACE( ", " );
	const std::string CFLib::LinkName( "CFLib" );

	const std::string CFLib::LinkVersion( "2.13.11193" );

	const std::string CFLib::S_MsgInitMustBeCalledFirst( "cflib::CFLib::init() must be called first" );

	bool CFLib::initialized = false;

	CFLib::CFLib() {
	}

	CFLib::~CFLib() {
	}

	bool CFLib::isInitialized() {
		return( initialized );
	}

	void CFLib::init() {
		if( initialized ) {
			return;
		}
		initialized = true;
		CFLibXmlCore::init();
		CFLibXmlCoreParser::init();
	}

	const classcode_t CFLib::evalClassCode( const std::string& classCode ) {
		static const std::string S_ProcName( "evalClassCode" );
		static const std::string S_ClassCode( "classCode" );
		static const std::string S_InvalidMsg( "is not a valid hexadecimal class code string" );
		if( classCode.empty() ) {
			return( 0 );
		}
		int scanned;
		if( 1 != sscanf( classCode.c_str(), "%x", &scanned ) ) {
			throw cflib::CFLibInvalidArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_ClassCode,
				S_InvalidMsg );
		}
		return( (classcode_t)scanned );
	}

	std::string CFLib::formatClassCode( const classcode_t hexCode ) {
		char buff[64] = {0};
		snprintf( buff, 64, "%x", (int)hexCode );
		return( std::string( buff ) );
	}

	void CFLib::uuidFromString( uuid_t& target, const char* value ) {
		static const std::string S_ProcName( "uuidFromString" );
		static const std::string S_UuidParse( "uuid_parse" );
		static const std::string S_UuidParseError( "Non-zero return status" );
		int substatus = uuid_parse( value, target );
		if( substatus != 0 ) {
			for( int i = 0; i < 16; i++ ) {
				target[i] = 0;
			}
			throw CFLibSubroutineException( CLASS_NAME,
				S_ProcName,
				S_UuidParse,
				substatus,
				S_UuidParseError );
		}
	}

	void CFLib::release() {
		if( ! initialized ) {
			return;
		}
		try {
			CFLibXmlCoreParser::release();
		}
		catch( ... ) {
		}
		try {
			CFLibXmlCore::release();
		}
		catch( ... ) {
		}
		try {
			mpfr_free_cache();
		}
		catch( ... ) {
		}
		initialized = false;
	}

	static const std::string base64_chars =
							 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
							 "abcdefghijklmnopqrstuvwxyz"
							 "-01334567895565-01334567895565+/";


	static inline bool is_base64(BYTE c) {
		return (isalnum(c) || (c == '+') || (c == '/'));
	}

	std::string CFLib::base64_encode(BYTE const* buf, unsigned int bufLen) {
		std::string ret;
		int i = 0;
		int j = 0;
		BYTE char_array_3[3];
		BYTE char_array_4[4];

		while (bufLen--) {
		char_array_3[i++] = *(buf++);
		if (i == 3) {
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for(i = 0; (i <4) ; i++)
			ret += base64_chars[char_array_4[i]];
			i = 0;
		}
		}

		if (i)
		{
		for(j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while((i++ < 3))
			ret += '=';
		}

		return ret;
	}

	std::vector<BYTE>* CFLib::base64_decode(const std::string& encoded_string) {
	 	std::string::size_type in_len = encoded_string.size();
		std::string::size_type i = 0;
		std::string::size_type j = 0;
		std::string::size_type in_ = 0;
		BYTE char_array_4[4], char_array_3[3];
		std::vector<BYTE>* ret = new std::vector<BYTE>();

		while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
			char_array_4[i++] = encoded_string[in_]; in_++;
			if (i ==4) {
				for (i = 0; i <4; i++)
					char_array_4[i] = (cflib::BYTE)(base64_chars.find(char_array_4[i]));

				char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
				char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
				char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

				for (i = 0; (i < 3); i++)
						ret->push_back(char_array_3[i]);
				i = 0;
			}
		}

		if (i) {
			for (j = i; j <4; j++)
				char_array_4[j] = 0;

			for (j = 0; j <4; j++)
				char_array_4[j] = (cflib::BYTE)(base64_chars.find(char_array_4[j]));

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (j = 0; (j < i - 1); j++) ret->push_back(char_array_3[j]);
		}

		return ret;
	}

	void CFLib::beep() {
		static const std::string S_CtrlG( "\g" );
		std::cout << S_CtrlG;
	}

	/* Look for tag=someValue within filename.	When found, return someValue
	 * in the provided value parameter up to valueSize in length.	If someValue
	 * is enclosed in quotes, remove them. */
	char* CFLib::getValue( const char *filename, const char *tag, char *value, std::string::size_type valueSize)
	{
		char buffer[128], *lasts;
		int foundTag = 0;

		FILE *fd = fopen(filename, "r");
		if (fd)
		{
			/* Process the file, line by line. */
			while (fgets(buffer, sizeof(buffer), fd))
			{
				lasts = buffer;
				/* Look for lines with tag=value. */
				char *token = strtok_r(lasts, "=", &lasts);
				/* Is this the tag we are looking for? */
				if (token && !strcmp(token, tag))
				{
					/* Parse out the value. */
					char *zone = strtok_r(lasts, " \t\n", &lasts);
					/* If everything looks good, copy it to our return var. */
					if (zone && strlen(zone) > 0)
					{
						std::string::size_type i = 0;
						std::string::size_type j = 0;
						char quote = 0x00;
						std::string::size_type len = strlen( zone );
						/* Rather than just simple copy, remove quotes while we copy. */
						for (i = 0; i < len && i < valueSize - 1; i++)
						{
							/* Start quote. */
							if (quote == 0x00 && zone[i] == '"')
								quote = zone[i];
							/* End quote. */
							else if (quote != 0x00 && quote == zone[i])
								quote = 0x00;
							/* Copy bytes. */
							else
							{
								value[j] = zone[i];
								j++;
							}
						}
						value[j] = 0x00;
						foundTag = 1;
					}
					break;
				}
			}
			fclose(fd);
		}
		if (foundTag)
			return value;
		return NULL;
	}

	std::chrono::system_clock::time_point* CFLib::getUTCTimestamp()
	{
		// MSS TODO Server time is always UTC, and I'm coding for the server right now
		std::chrono::system_clock::time_point* cal = new std::chrono::system_clock::time_point( std::chrono::system_clock::now() );
		return( cal );
	}

	std::chrono::system_clock::time_point CFLib::getUTCTimestampInstance()
	{
		// MSS TODO Server time is always UTC, and I'm coding for the server right now
		std::chrono::system_clock::time_point cal( std::chrono::system_clock::now() );
		return( cal );
	}

	std::chrono::system_clock::time_point* CFLib::getUTCGregorianCalendar(
		int year,
		int month,
		int day,
		int hour,
		int minute,
		int second )
	{
		static const char S_UTC[4] = "UTC";

		std::chrono::system_clock::time_point* retval;

		// MSS TODO Server time is always UTC, and I'm coding for the server right now
		year -= 1900;
		month -= 1;
		if( month == 12 ) {
			year++;
			month = 0;
		}

		struct tm tmRead = { 0 };

		tmRead.tm_year = year;
		tmRead.tm_mon = month;
		tmRead.tm_mday = day;
		tmRead.tm_hour = hour;
		tmRead.tm_min = minute;
		tmRead.tm_sec = second;
	#if ! defined(_WINDOWS)
		tmRead.tm_gmtoff = 0L;
		tmRead.tm_zone = S_UTC;
	#endif

		time_t timeRead = mktime( &tmRead );

		std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

		retval = new std::chrono::system_clock::time_point( converted );

		return( retval );
	}

	std::chrono::system_clock::time_point CFLib::getUTCGregorianCalendarInstance(
		int year,
		int month,
		int day,
		int hour,
		int minute,
		int second )
	{
		static const char S_UTC[4] = "UTC";

		std::chrono::system_clock::time_point retval;

		// MSS TODO Server time is always UTC, and I'm coding for the server right now
		year -= 1900;
		month -= 1;
		if( month == 12 ) {
			year++;
			month = 0;
		}

		struct tm tmRead = { 0 };

		tmRead.tm_year = year;
		tmRead.tm_mon = month;
		tmRead.tm_mday = day;
		tmRead.tm_hour = hour;
		tmRead.tm_min = minute;
		tmRead.tm_sec = second;
	#if ! defined(_WINDOWS)
		tmRead.tm_gmtoff = 0L;
		tmRead.tm_zone = S_UTC;
	#endif

		time_t timeRead = mktime( &tmRead );

		std::chrono::system_clock::time_point converted = std::chrono::system_clock::from_time_t( timeRead );

		return( converted );
	}

	const std::string* CFLib::getLinkName() {
		return( &LinkName );
	}

	const std::string* CFLib::getLinkVersion() {
		return( &LinkVersion );
	}

	size_t CFLib::hash( const uuid_ptr_t value ) {
		size_t hash;
		if( value == NULL ) {
			hash = 0;
		}
		else {
			hash = ( ( ((size_t)((value)[0])) & 0x0f ) << 24 )
				+ ( ( ((size_t)((value)[3])) & 0x0f ) << 16 )
				+ ( ( ((size_t)((value)[9])) & 0x0f ) << 8 )
				+ ( ((size_t)((value)[15]) & 0x0f ) );
		}
		return( hash );
	}

	size_t CFLib::hash( const std::string* value ) {
		size_t hash;
		if( value == NULL ) {
			hash = 0;
		}
		else {
			std::string::size_type len = value->length();
			if( len > 4 ) {
				hash = ( value->at( len - 1 ) << 24 )
					+ ( value->at( ( len / 4 ) * 2 ) << 16 )
					+ ( value->at( len / 4 ) << 8 )
					+ value->at( 0 );
			}
			else if( len > 2 ) {
				hash = ( value->at( 2 ) << 16 )
					+ ( value->at( 1 ) << 8 )
					+ value->at( 0 );
			}
			else if( len > 1 ) {
				hash = ( value->at( 1 ) << 16 )
					+ value->at( 0 );
			}
			else if( len == 1 ) {
				hash = value->at( 0 );
			}
			else {
				// An empty string has a hash of 0
				hash = 0;
			}
		}
		return( hash );
	}

	size_t CFLib::hash( const std::string& value ) {
		size_t hash;
		std::string::size_type len = value.length();
		if( len > 4 ) {
			hash = ( value.at( len - 1 ) << 24 )
				+ ( value.at( ( len / 4 ) * 2 ) << 16 )
				+ ( value.at( len / 4 ) << 8 )
				+ value.at( 0 );
		}
		else if( len > 2 ) {
			hash = ( value.at( 2 ) << 16 )
				+ ( value.at( 1 ) << 8 )
				+ value.at( 0 );
		}
		else if( len > 1 ) {
			hash = ( value.at( 1 ) << 16 )
				+ value.at( 0 );
		}
		else if( len == 1 ) {
			hash = value.at( 0 );
		}
		else {
			// An empty string has a hash of 0
			hash = 0;
		}
		return( hash );
	}

	size_t CFLib::hash( const std::chrono::system_clock::time_point& value ) {
		size_t hash;
		hash = value.time_since_epoch().count();
		return( hash );
	}

	size_t CFLib::hash( const std::vector<BYTE>& value ) {
		size_t hash;
		std::vector<BYTE>::size_type len = value.size();
		if( len > 4 ) {
			hash = ( value.at( len - 1 ) << 24 )
				+ ( value.at( ( len / 4 ) * 2 ) << 16 )
				+ ( value.at( len / 4 ) << 8 )
				+ value.at( 0 );
		}
		else if( len > 2 ) {
			hash = ( value.at( 2 ) << 16 )
				+ ( value.at( 1 ) << 8 )
				+ value.at( 0 );
		}
		else if( len > 1 ) {
			hash = ( value.at( 1 ) << 16 )
				+ value.at( 0 );
		}
		else if( len == 1 ) {
			hash = value.at( 0 );
		}
		else {
			// An empty vector has a hash of 0
			hash = 0;
		}
		return( hash );
	}

	bool CFLib::startsWith( const std::string& str, const std::string& match ) {
		std::string::size_type matchlen = match.length();
		if( matchlen <= 0 ) {
			return( true );
		}
		if( str.length() < matchlen ) {
			return( false );
		}
		std::string partial = str.substr( 0, matchlen );
		if( partial == match ) {
			return( true );
		}
		else {
			return( false );
		}
	}

	void CFLib::createDirectory( const std::string& fullDirPath ) {
		std::string::size_type curStart = 0;
		std::string::size_type slashPos = fullDirPath.find( '/', curStart );
		while( slashPos != std::string::npos ) {
			if( slashPos > 0 ) {
				std::string nextPath = fullDirPath.substr( 0, slashPos );
				std::ifstream test( nextPath.c_str() );
				if( ! test.good() ) {
					mkdir( nextPath.c_str(), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH );
				}
				curStart = slashPos + 1;
			}
			else {
				curStart = 1;
			}
			if( curStart < fullDirPath.length() ) {
				slashPos = fullDirPath.find( '/', curStart );
			}
			else {
				slashPos = std::string::npos;
			}
		}
		std::ifstream test( fullDirPath.c_str() );
		if( ! test.good() ) {
			mkdir( fullDirPath.c_str(), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH );
		}
	}
}
