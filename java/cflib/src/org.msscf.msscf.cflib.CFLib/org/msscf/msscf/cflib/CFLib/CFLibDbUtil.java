/*
 *	MSS Code Factory CFLib 2.13
 *
 *	Copyright (c) 2020 Mark Stephen Sobkow
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
 *	Contact Mark Stephen Sobkow at msobkow@sasktel.net for commercial licensing.
 */

package org.msscf.msscf.cflib.CFLib;

import java.util.*;

public class CFLibDbUtil {

	public final static TimeZone tzUTC = TimeZone.getTimeZone( "GMT+0000" );
	public final static Calendar localCalendar = new GregorianCalendar();
	public final static int localTZOffsetMillis = localCalendar.get( Calendar.ZONE_OFFSET );
	public static int dbServerTZOffsetMillis = localTZOffsetMillis;
	public static TimeZone dbServerTimeZone = null;

	public static int getDbServerTZOffsetMillis() {
		return( dbServerTZOffsetMillis );
	}
	
	public static void setDbServerTZOffsetMillis( int value ) {
		dbServerTZOffsetMillis = value;
		dbServerTimeZone = null;
	}

	public static TimeZone getDbServerTimeZone() {
		if( dbServerTimeZone == null ) {
			int secondsOnly = dbServerTZOffsetMillis / 1000;
			int minutesOnly = secondsOnly / 60;
			int absMinutes = ( minutesOnly < 0 ) ? ( 0 - minutesOnly ) : minutesOnly;
			int minutes = absMinutes % 60;
			int hours = absMinutes / 60;
			StringBuffer buff = new StringBuffer();
			Formatter fmt = new Formatter( buff );
			if( minutesOnly < 0 ) {
				buff.append( "GMT-" );
			}
			else {
				buff.append( "GMT+" );
			}
			fmt.format( "%1$02d", hours );
			fmt.format( "%1$02d", minutes );
			dbServerTimeZone = TimeZone.getTimeZone( buff.toString() );
			fmt.close();
		}
		return( dbServerTimeZone );
	}
	
	public static void setDbServerTimeZone( TimeZone tz ) {
		if( tz == null ) {
			throw new CFLibNullArgumentException( CFLibDbUtil.class,
				"setDbServerTimeZone",
				1,
				"tz" );
		}
		dbServerTimeZone = tz;
		dbServerTZOffsetMillis = tz.getRawOffset();
	}

	public static Calendar getDbServerCalendar( Calendar value ) {
		if( value == null ) {
			return( null );
		}
		Calendar cal = Calendar.getInstance( getDbServerTimeZone() );
		cal.setTimeInMillis( value.getTimeInMillis() );
		return( cal );
	}

	public static Calendar getUTCCalendar( Calendar value ) {
		if( value == null ) {
			return( null );
		}
		Calendar cal = Calendar.getInstance( tzUTC );
		cal.setTimeInMillis( value.getTimeInMillis() );
		return( cal );
	}
}
