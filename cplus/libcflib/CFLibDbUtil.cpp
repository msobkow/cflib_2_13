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
#include <cflib/CFLibDbUtil.hpp>

namespace cflib {

	time_t CFLibDbUtil::dbServerTZOffsetSeconds = -1;

	CFLibDbUtil::CFLibDbUtil() {
	}

	time_t CFLibDbUtil::getDbServerTZOffsetSeconds() {
		// MSS TODO WORKING Need to determine current system time zone and its offset, and
		// initialize dbServerTZOffsetSeconds with that value.
		if( dbServerTZOffsetSeconds == -1 ) {
			dbServerTZOffsetSeconds = 0;
		}
		return( dbServerTZOffsetSeconds );
	}
	
	void CFLibDbUtil::setDbServerTZOffsetSeconds( time_t value ) {
		dbServerTZOffsetSeconds = value;
	}

	std::chrono::system_clock::time_point* CFLibDbUtil::getDbServerTimeFromUTCTime( const std::chrono::system_clock::time_point* value ) {
		if( value == NULL ) {
			return( NULL );
		}

		std::time_t time = std::chrono::system_clock::to_time_t( *value );
		// MSS TODO WORKING Need to convert UTC time to current system time
		// time += CFLib::getUTCTimezoneOffset();
		std::tm utc = *std::localtime( &time );
#if ! defined(_WINDOWS)
		utc.tm_gmtoff = getDbServerTZOffsetSeconds();
		utc.tm_zone = NULL;
#endif
		time_t timeConverted = mktime( &utc );

		std::chrono::duration<long,std::ratio<1>> *dur = new std::chrono::duration<long,std::ratio<1>>( timeConverted );
		std::chrono::system_clock::time_point* retval = new std::chrono::system_clock::time_point( *dur );

		return( retval );
	}

	std::chrono::system_clock::time_point* CFLibDbUtil::getUTCTimeFromDBServerTime( const std::chrono::system_clock::time_point* value ) {
		if( value == NULL ) {
			return( NULL );
		}

		std::time_t time = std::chrono::system_clock::to_time_t( *value );
		time += getDbServerTZOffsetSeconds();
		std::tm dbtime = *std::localtime( &time );
		// MSS TODO WORKING Need to calculate tm_gmtoff from current system settings under WSL Ubuntu
		// dbtime.tm_gmtoff = CFLib::getUTCTimezoneOffset();
#if ! defined(_WINDOWS)
		dbtime.tm_zone = NULL;
#endif
		time_t timeConverted = mktime( &dbtime );

		std::chrono::duration<long,std::ratio<1>> *dur = new std::chrono::duration<long,std::ratio<1>>( timeConverted );
		std::chrono::system_clock::time_point* retval = new std::chrono::system_clock::time_point( *dur );

		return( retval );
	}
}
