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

package org.msscf.msscf.v2_13.cflib.CFLib;

import java.math.BigDecimal;
import java.text.DecimalFormat;
import java.util.*;

import org.apache.commons.codec.binary.Base64;

public class CFLibXmlUtil {

	public final static Calendar localCalendar = new GregorianCalendar();
	public final static int localTZOffsetMillis = localCalendar.get( Calendar.ZONE_OFFSET );
	
	protected final static String S_emptyString = "";
	
	/**
	 *	Formatting for XML attribute content strings.
	**/

	public static Calendar parseDate( String value ) {
		final String S_ProcName = "parseDate";
		if( ( value == null ) || ( value.length() == 0 ) ) {
			return( null );
		}

		if( value.length() != 10 ) {
			throw new CFLibInvalidArgumentException( CFLibXmlUtil.class,
				S_ProcName,
				1,
				"value",
				"Invalid value format, must be YYYY-MM-DD, \"" + value + "\" is invalid");
		}
		
		if( ! ( Character.isDigit( value.charAt(0) )
				&& Character.isDigit( value.charAt(1) )
				&& Character.isDigit( value.charAt(2) )
				&& Character.isDigit( value.charAt(3) )
				&& ( value.charAt(4) == '-' )
				&& Character.isDigit( value.charAt(5) )
				&& Character.isDigit( value.charAt(6) )
				&& ( value.charAt(7) == '-' )
				&& Character.isDigit( value.charAt(8) )
				&& Character.isDigit( value.charAt(9) ) ) )
		{
			throw new CFLibInvalidArgumentException( CFLibXmlUtil.class,
				S_ProcName,
				1,
				"value",
				"Invalid value format, must be YYYY-MM-DD, \"" + value + "\" is invalid");
		}

        int year = Integer.parseInt( value.substring( 0, 4 ) );
        int month = Integer.parseInt( value.substring( 5, 7 ) );
        int day = Integer.parseInt( value.substring( 8, 10 ) );
		
		Calendar retval = new GregorianCalendar( year, month - 1, day, 0, 0, 0 );

		return( retval );
	}

	public static Calendar parseDate( String fieldName, String value ) {
		final String S_ProcName = "parseDate";
		if( ( fieldName == null ) || ( fieldName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
				S_ProcName,
				1,
				"fieldName" );
		}
		if( ( value == null ) || ( value.length() == 0 ) ) {
			return( null );
		}

		if( value.length() != 10 ) {
			throw new CFLibInvalidArgumentException( fieldName,
				S_ProcName,
				2,
				"value",
				"Invalid value format, must be YYYY-MM-DD, \"" + value + "\" is invalid");
		}
		
		if( ! ( Character.isDigit( value.charAt(0) )
				&& Character.isDigit( value.charAt(1) )
				&& Character.isDigit( value.charAt(2) )
				&& Character.isDigit( value.charAt(3) )
				&& ( value.charAt(4) == '-' )
				&& Character.isDigit( value.charAt(5) )
				&& Character.isDigit( value.charAt(6) )
				&& ( value.charAt(7) == '-' )
				&& Character.isDigit( value.charAt(8) )
				&& Character.isDigit( value.charAt(9) ) ) )
		{
			throw new CFLibInvalidArgumentException( fieldName,
				S_ProcName,
				2,
				"value",
				"Invalid value format, must be YYYY-MM-DD, \"" + value + "\" is invalid");
		}

        int year = Integer.parseInt( value.substring( 0, 4 ) );
        int month = Integer.parseInt( value.substring( 5, 7 ) );
        int day = Integer.parseInt( value.substring( 8, 10 ) );
		
		Calendar retval = new GregorianCalendar( year, month - 1, day, 0, 0, 0 );

		return( retval );
	}

	public static Calendar parseTime( String value ) {
		final String S_ProcName = "parseTime";
		if( ( value == null ) || ( value.length() == 0 ) ) {
			return( null );
		}
		
		if( value.length() != 8 ) {
			throw new CFLibInvalidArgumentException( CFLibXmlUtil.class,
				S_ProcName,
				1,
				"value",
				"Invalid value format, must be HH:MI:SS, \"" + value + "\" is invalid");
		}
		
		if( ! ( Character.isDigit( value.charAt(0) )
				&& Character.isDigit( value.charAt(1) )
				&& ( value.charAt(2) == ':' )
				&& Character.isDigit( value.charAt(3) )
				&& Character.isDigit( value.charAt(4) )
				&& ( value.charAt(5) == ':' )
				&& Character.isDigit( value.charAt(6) )
				&& Character.isDigit( value.charAt(7) ) ) )
		{
			throw new CFLibInvalidArgumentException( CFLibXmlUtil.class,
				S_ProcName,
				1,
				"value",
				"Invalid value format, must be HH:MI:SS, \"" + value + "\" is invalid");
		}

		int hour = Integer.parseInt( value.substring( 0, 2 ) );
		int minute = Integer.parseInt( value.substring( 3, 5 ) );
		int second = Integer.parseInt( value.substring( 6, 8 ) );
		
		Calendar retval = new GregorianCalendar( 1970, 0, 1, hour, minute, second );
			
		return( retval );
	}

	public static Calendar parseTime( String fieldName, String value ) {
		final String S_ProcName = "parseTime";
		if( ( fieldName == null ) || ( fieldName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
				S_ProcName,
				1,
				"fieldName" );
		}
		if( ( value == null ) || ( value.length() == 0 ) ) {
			return( null );
		}
		
		if( value.length() != 8 ) {
			throw new CFLibInvalidArgumentException( fieldName,
				S_ProcName,
				2,
				"value",
				"Invalid value format, must be HH:MI:SS, \"" + value + "\" is invalid");
		}
		
		if( ! ( Character.isDigit( value.charAt(0) )
				&& Character.isDigit( value.charAt(1) )
				&& ( value.charAt(2) == ':' )
				&& Character.isDigit( value.charAt(3) )
				&& Character.isDigit( value.charAt(4) )
				&& ( value.charAt(5) == ':' )
				&& Character.isDigit( value.charAt(6) )
				&& Character.isDigit( value.charAt(7) ) ) )
		{
			throw new CFLibInvalidArgumentException( fieldName,
				S_ProcName,
				2,
				"value",
				"Invalid value format, must be HH:MI:SS, \"" + value + "\" is invalid");
		}

		int hour = Integer.parseInt( value.substring( 0, 2 ) );
		int minute = Integer.parseInt( value.substring( 3, 5 ) );
		int second = Integer.parseInt( value.substring( 6, 8 ) );
		
		Calendar retval = new GregorianCalendar( 1970, 0, 1, hour, minute, second );
			
		return( retval );
	}

	public static Calendar parseTimestamp( String value ) {
		final String S_ProcName="parseTimestamp";
		if( ( value == null ) || ( value.length() == 0 ) ) {
			return( null );
		}

		if( value.length() != 19 ) {
			throw new CFLibInvalidArgumentException( CFLibXmlUtil.class,
				S_ProcName,
				1,
				"value",
				"Invalid value format, must be YYYY-MM-DDTHH:MI:SS, \"" + value + "\" is invalid");
		}
		
		if( ! ( Character.isDigit( value.charAt(0) )
				&& Character.isDigit( value.charAt(1) )
				&& Character.isDigit( value.charAt(2) )
				&& Character.isDigit( value.charAt(3) )
				&& ( value.charAt(4) == '-' )
				&& Character.isDigit( value.charAt(5) )
				&& Character.isDigit( value.charAt(6) )
				&& ( value.charAt(7) == '-' )
				&& Character.isDigit( value.charAt(8) )
				&& Character.isDigit( value.charAt(9) )
				&& ( value.charAt(10) == 'T' )
				&& Character.isDigit( value.charAt(11) )
				&& Character.isDigit( value.charAt(12) )
				&& ( value.charAt(13) == ':' )
				&& Character.isDigit( value.charAt(14) )
				&& Character.isDigit( value.charAt(15) )
				&& ( value.charAt(16) == ':' )
				&& Character.isDigit( value.charAt(17) )
				&& Character.isDigit( value.charAt(18) ) ) )
		{
			throw new CFLibInvalidArgumentException( CFLibXmlUtil.class,
				S_ProcName,
				1,
				"value",
				"Invalid value format, must be YYYY-MM-DDTHH:MI:SS, \"" + value + "\" is invalid");
		}
		
        int year = Integer.parseInt( value.substring( 0, 4 ) );
        int month = Integer.parseInt( value.substring( 5, 7 ) );
        int day = Integer.parseInt( value.substring( 8, 10 ) );
		int hour = Integer.parseInt( value.substring( 11, 13 ) );
		int minute = Integer.parseInt( value.substring( 14, 16 ) );
		int second = Integer.parseInt( value.substring( 17, 19 ) );
		
		Calendar retval = new GregorianCalendar( year, month - 1, day, hour, minute, second );

		return( retval );
	}

	public static Calendar parseTimestamp( String fieldName, String value ) {
		final String S_ProcName="parseTimestamp";
		if( ( fieldName == null ) || ( fieldName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
				S_ProcName,
				1,
				"fieldName" );
		}
		if( ( value == null ) || ( value.length() == 0 ) ) {
			return( null );
		}

		if( value.length() != 19 ) {
			throw new CFLibInvalidArgumentException( fieldName,
				S_ProcName,
				1,
				"value",
				"Invalid value format, must be YYYY-MM-DDTHH:MI:SS, \"" + value + "\" is invalid");
		}
		
		if( ! ( Character.isDigit( value.charAt(0) )
				&& Character.isDigit( value.charAt(1) )
				&& Character.isDigit( value.charAt(2) )
				&& Character.isDigit( value.charAt(3) )
				&& ( value.charAt(4) == '-' )
				&& Character.isDigit( value.charAt(5) )
				&& Character.isDigit( value.charAt(6) )
				&& ( value.charAt(7) == '-' )
				&& Character.isDigit( value.charAt(8) )
				&& Character.isDigit( value.charAt(9) )
				&& ( value.charAt(10) == 'T' )
				&& Character.isDigit( value.charAt(11) )
				&& Character.isDigit( value.charAt(12) )
				&& ( value.charAt(13) == ':' )
				&& Character.isDigit( value.charAt(14) )
				&& Character.isDigit( value.charAt(15) )
				&& ( value.charAt(16) == ':' )
				&& Character.isDigit( value.charAt(17) )
				&& Character.isDigit( value.charAt(18) ) ) )
		{
			throw new CFLibInvalidArgumentException( fieldName,
				S_ProcName,
				1,
				"value",
				"Invalid value format, must be YYYY-MM-DDTHH:MI:SS, \"" + value + "\" is invalid");
		}
		
        int year = Integer.parseInt( value.substring( 0, 4 ) );
        int month = Integer.parseInt( value.substring( 5, 7 ) );
        int day = Integer.parseInt( value.substring( 8, 10 ) );
		int hour = Integer.parseInt( value.substring( 11, 13 ) );
		int minute = Integer.parseInt( value.substring( 14, 16 ) );
		int second = Integer.parseInt( value.substring( 17, 19 ) );
		
		Calendar retval = new GregorianCalendar( year, month - 1, day, hour, minute, second );

		return( retval );
	}

	public static Calendar parseTZDate( String value ) {
		final String S_ProcName = "parseTZDate";
		if( ( value == null ) || ( value.length() == 0 ) ) {
			return( null );
		}

		if( ( value.length() != 11 ) && ( value.length() != 16 ) ) {
			throw new CFLibInvalidArgumentException( CFLibXmlUtil.class,
				S_ProcName,
				1,
				"value",
				"Invalid value format, must be YYYY-MM-DDZ or YYYY-MM-DD+HO:MO, \"" + value + "\" is invalid");
		}
		
		if( ! ( Character.isDigit( value.charAt(0) )
				&& Character.isDigit( value.charAt(1) )
				&& Character.isDigit( value.charAt(2) )
				&& Character.isDigit( value.charAt(3) )
				&& ( value.charAt(4) == '-' )
				&& Character.isDigit( value.charAt(5) )
				&& Character.isDigit( value.charAt(6) )
				&& ( value.charAt(7) == '-' )
				&& Character.isDigit( value.charAt(8) )
				&& Character.isDigit( value.charAt(9) ) ) )
		{
			throw new CFLibInvalidArgumentException( CFLibXmlUtil.class,
				S_ProcName,
				1,
				"value",
				"Invalid value format, must be YYYY-MM-DDZ or YYYY-MM-DD+HO:MO, \"" + value + "\" is invalid");
		}

		Calendar retval = null;
		
		if( value.charAt( 10 ) == 'Z' ) {
            int year = Integer.parseInt( value.substring( 0, 4 ) );
            int month = Integer.parseInt( value.substring( 5, 7 ) );
            int day = Integer.parseInt( value.substring( 8, 10 ) );
            TimeZone tz = TimeZone.getTimeZone( "GMT+0000" );
            retval = new GregorianCalendar( tz );
            retval.set( Calendar.YEAR, year );
            retval.set( Calendar.MONTH, month - 1 );
            retval.set( Calendar.DAY_OF_MONTH, day );
            retval.set( Calendar.HOUR_OF_DAY, 0 );
            retval.set( Calendar.MINUTE, 0 );
            retval.set( Calendar.SECOND, 0 );
            retval.getTimeInMillis(); // Force calendar resync based on input values
		}
		else if( ( value.charAt( 10 ) == '-' )
			&& ( Character.isDigit( value.charAt( 11 ) ) )
			&& ( Character.isDigit( value.charAt( 12 ) ) )
			&& ( value.charAt( 13 ) == ':' )
			&& ( Character.isDigit( value.charAt( 14 ) ) )
			&& ( Character.isDigit( value.charAt( 15 ) ) ) )
		{
            int year = Integer.parseInt( value.substring( 0, 4 ) );
            int month = Integer.parseInt( value.substring( 5, 7 ) );
            int day = Integer.parseInt( value.substring( 8, 10 ) );
            String tzCustomName = "GMT" + value.substring( 10, 13 ) + value.substring( 14, 16 );
            TimeZone tz = TimeZone.getTimeZone( tzCustomName );
            retval = new GregorianCalendar( tz );
            retval.set( Calendar.YEAR, year );
            retval.set( Calendar.MONTH, month - 1 );
            retval.set( Calendar.DAY_OF_MONTH, day );
            retval.set( Calendar.HOUR_OF_DAY, 0 );
            retval.set( Calendar.MINUTE, 0 );
            retval.set( Calendar.SECOND, 0 );
            retval.getTimeInMillis(); // Force calendar resync based on input values
		}
		else if( ( value.charAt( 10 ) == '+' )
			&& ( Character.isDigit( value.charAt( 11 ) ) )
			&& ( Character.isDigit( value.charAt( 12 ) ) )
			&& ( value.charAt( 13 ) == ':' )
			&& ( Character.isDigit( value.charAt( 14 ) ) )
			&& ( Character.isDigit( value.charAt( 15 ) ) ) )
		{
            int year = Integer.parseInt( value.substring( 0, 4 ) );
            int month = Integer.parseInt( value.substring( 5, 7 ) );
            int day = Integer.parseInt( value.substring( 8, 10 ) );
            String tzCustomName = "GMT" + value.substring( 10, 13 ) + value.substring( 14, 16 );
            TimeZone tz = TimeZone.getTimeZone( tzCustomName );
            retval = new GregorianCalendar( tz );
            retval.set( Calendar.YEAR, year );
            retval.set( Calendar.MONTH, month - 1 );
            retval.set( Calendar.DAY_OF_MONTH, day );
            retval.set( Calendar.HOUR_OF_DAY, 0 );
            retval.set( Calendar.MINUTE, 0 );
            retval.set( Calendar.SECOND, 0 );
            retval.getTimeInMillis(); // Force calendar resync based on input values
		}
		else {
			throw new CFLibInvalidArgumentException( CFLibXmlUtil.class,
				S_ProcName,
				1,
				"value",
				"Invalid value format, must be YYYY-MM-DDZ or YYYY-MM-DD+HO:MO, \"" + value + "\" is invalid");
		}

		return( retval );
	}

	public static Calendar parseTZDate( String fieldName, String value ) {
		final String S_ProcName = "parseTZDate";
		if( ( fieldName == null ) || ( fieldName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
				S_ProcName,
				1,
				"fieldName" );
		}
		if( ( value == null ) || ( value.length() == 0 ) ) {
			return( null );
		}

		if( ( value.length() != 11 ) && ( value.length() != 16 ) ) {
			throw new CFLibInvalidArgumentException( fieldName,
				S_ProcName,
				2,
				"value",
				"Invalid value format, must be YYYY-MM-DDZ or YYYY-MM-DD+HO:MO, \"" + value + "\" is invalid");
		}
		
		if( ! ( Character.isDigit( value.charAt(0) )
				&& Character.isDigit( value.charAt(1) )
				&& Character.isDigit( value.charAt(2) )
				&& Character.isDigit( value.charAt(3) )
				&& ( value.charAt(4) == '-' )
				&& Character.isDigit( value.charAt(5) )
				&& Character.isDigit( value.charAt(6) )
				&& ( value.charAt(7) == '-' )
				&& Character.isDigit( value.charAt(8) )
				&& Character.isDigit( value.charAt(9) ) ) )
		{
			throw new CFLibInvalidArgumentException( fieldName,
				S_ProcName,
				2,
				"value",
				"Invalid value format, must be YYYY-MM-DDZ or YYYY-MM-DD+HO:MO, \"" + value + "\" is invalid");
		}

		Calendar retval = null;
		
		if( value.charAt( 10 ) == 'Z' ) {
            int year = Integer.parseInt( value.substring( 0, 4 ) );
            int month = Integer.parseInt( value.substring( 5, 7 ) );
            int day = Integer.parseInt( value.substring( 8, 10 ) );
            TimeZone tz = TimeZone.getTimeZone( "GMT+0000" );
            retval = new GregorianCalendar( tz );
            retval.set( Calendar.YEAR, year );
            retval.set( Calendar.MONTH, month - 1 );
            retval.set( Calendar.DAY_OF_MONTH, day );
            retval.set( Calendar.HOUR_OF_DAY, 0 );
            retval.set( Calendar.MINUTE, 0 );
            retval.set( Calendar.SECOND, 0 );
            retval.getTimeInMillis(); // Force calendar resync based on input values
		}
		else if( ( value.charAt( 10 ) == '-' )
			&& ( Character.isDigit( value.charAt( 11 ) ) )
			&& ( Character.isDigit( value.charAt( 12 ) ) )
			&& ( value.charAt( 13 ) == ':' )
			&& ( Character.isDigit( value.charAt( 14 ) ) )
			&& ( Character.isDigit( value.charAt( 15 ) ) ) )
		{
            int year = Integer.parseInt( value.substring( 0, 4 ) );
            int month = Integer.parseInt( value.substring( 5, 7 ) );
            int day = Integer.parseInt( value.substring( 8, 10 ) );
            String tzCustomName = "GMT" + value.substring( 10, 13 ) + value.substring( 14, 16 );
            TimeZone tz = TimeZone.getTimeZone( tzCustomName );
            retval = new GregorianCalendar( tz );
            retval.set( Calendar.YEAR, year );
            retval.set( Calendar.MONTH, month - 1 );
            retval.set( Calendar.DAY_OF_MONTH, day );
            retval.set( Calendar.HOUR_OF_DAY, 0 );
            retval.set( Calendar.MINUTE, 0 );
            retval.set( Calendar.SECOND, 0 );
            retval.getTimeInMillis(); // Force calendar resync based on input values
		}
		else if( ( value.charAt( 10 ) == '+' )
			&& ( Character.isDigit( value.charAt( 11 ) ) )
			&& ( Character.isDigit( value.charAt( 12 ) ) )
			&& ( value.charAt( 13 ) == ':' )
			&& ( Character.isDigit( value.charAt( 14 ) ) )
			&& ( Character.isDigit( value.charAt( 15 ) ) ) )
		{
            int year = Integer.parseInt( value.substring( 0, 4 ) );
            int month = Integer.parseInt( value.substring( 5, 7 ) );
            int day = Integer.parseInt( value.substring( 8, 10 ) );
            String tzCustomName = "GMT" + value.substring( 10, 13 ) + value.substring( 14, 16 );
            TimeZone tz = TimeZone.getTimeZone( tzCustomName );
            retval = new GregorianCalendar( tz );
            retval.set( Calendar.YEAR, year );
            retval.set( Calendar.MONTH, month - 1 );
            retval.set( Calendar.DAY_OF_MONTH, day );
            retval.set( Calendar.HOUR_OF_DAY, 0 );
            retval.set( Calendar.MINUTE, 0 );
            retval.set( Calendar.SECOND, 0 );
            retval.getTimeInMillis(); // Force calendar resync based on input values
		}
		else {
			throw new CFLibInvalidArgumentException( fieldName,
				S_ProcName,
				2,
				"value",
				"Invalid value format, must be YYYY-MM-DDZ or YYYY-MM-DD+HO:MO, \"" + value + "\" is invalid");
		}

		return( retval );
	}

	public static Calendar parseTZTime( String value ) {
		final String S_ProcName = "parseTZTime";
		if( ( value == null ) || ( value.length() == 0 ) ) {
			return( null );
		}
		
		if( ( value.length() != 9 ) && ( value.length() != 14 ) ) {
			throw new CFLibInvalidArgumentException( CFLibXmlUtil.class,
				S_ProcName,
				1,
				"value",
				"Invalid value format, must be HH:MI:SSZ or HH:MI:SS+HO:MO, \"" + value + "\" is invalid");
		}
		
		if( ! ( Character.isDigit( value.charAt(0) )
				&& Character.isDigit( value.charAt(1) )
				&& ( value.charAt(2) == ':' )
				&& Character.isDigit( value.charAt(3) )
				&& Character.isDigit( value.charAt(4) )
				&& ( value.charAt(5) == ':' )
				&& Character.isDigit( value.charAt(6) )
				&& Character.isDigit( value.charAt(7) ) ) )
		{
			throw new CFLibInvalidArgumentException( CFLibXmlUtil.class,
				S_ProcName,
				1,
				"value",
				"Invalid value format, must be HH:MI:SSZ or HH:MI:SS+HO:MO, \"" + value + "\" is invalid");
		}

		Calendar retval = null;

		if( value.charAt( 8 ) == 'Z' ) {
			int hour = Integer.parseInt( value.substring( 0, 2 ) );
			int minute = Integer.parseInt( value.substring( 3, 5 ) );
			int second = Integer.parseInt( value.substring( 6, 8 ) );
            TimeZone tz = TimeZone.getTimeZone( "+0000" );
            retval = new GregorianCalendar( tz );
            retval.set( Calendar.YEAR, 1970 );
            retval.set( Calendar.MONTH, 0 );
            retval.set( Calendar.DAY_OF_MONTH, 1 );
            retval.set( Calendar.HOUR_OF_DAY, hour );
            retval.set( Calendar.MINUTE, minute );
            retval.set( Calendar.SECOND, second );
            retval.getTimeInMillis(); // Force calendar resync based on input values
   			retval = new GregorianCalendar( 1970, 0, 1, hour, minute, second );
		}
		else if( ( value.charAt( 8 ) == '-' )
			&& ( Character.isDigit( value.charAt( 9 ) ) )
			&& ( Character.isDigit( value.charAt( 10 ) ) )
			&& ( value.charAt( 11 ) == ':' )
			&& ( Character.isDigit( value.charAt( 12 ) ) )
			&& ( Character.isDigit( value.charAt( 13 ) ) ) )
		{
			int hour = Integer.parseInt( value.substring( 0, 2 ) );
			int minute = Integer.parseInt( value.substring( 3, 5 ) );
			int second = Integer.parseInt( value.substring( 6, 8 ) );
            String tzCustomName = "GMT" + value.substring( 8, 11 ) + value.substring( 12, 14 );
            TimeZone tz = TimeZone.getTimeZone( tzCustomName );
            retval = new GregorianCalendar( tz );
            retval.set( Calendar.YEAR, 1970 );
            retval.set( Calendar.MONTH, 0 );
            retval.set( Calendar.DAY_OF_MONTH, 1 );
            retval.set( Calendar.HOUR_OF_DAY, hour );
            retval.set( Calendar.MINUTE, minute );
            retval.set( Calendar.SECOND, second );
            retval.getTimeInMillis(); // Force calendar resync based on input values
		}
		else if( ( value.charAt( 8 ) == '+' )
				&& ( Character.isDigit( value.charAt( 9 ) ) )
				&& ( Character.isDigit( value.charAt( 10 ) ) )
				&& ( value.charAt( 11 ) == ':' )
				&& ( Character.isDigit( value.charAt( 12 ) ) )
				&& ( Character.isDigit( value.charAt( 13 ) ) ) )
		{
			int hour = Integer.parseInt( value.substring( 0, 2 ) );
			int minute = Integer.parseInt( value.substring( 3, 5 ) );
			int second = Integer.parseInt( value.substring( 6, 8 ) );
            String tzCustomName = "GMT" + value.substring( 8, 11 ) + value.substring( 12, 14 );
            TimeZone tz = TimeZone.getTimeZone( tzCustomName );
            retval = new GregorianCalendar( tz );
            retval.set( Calendar.YEAR, 1970 );
            retval.set( Calendar.MONTH, 0 );
            retval.set( Calendar.DAY_OF_MONTH, 1 );
            retval.set( Calendar.HOUR_OF_DAY, hour );
            retval.set( Calendar.MINUTE, minute );
            retval.set( Calendar.SECOND, second );
            retval.getTimeInMillis(); // Force calendar resync based on input values
		}
		else {
			throw new CFLibInvalidArgumentException( CFLibXmlUtil.class,
				S_ProcName,
				1,
				"value",
				"Invalid value format, must be HH:MI:SSZ or HH:MI:SS+HO:MO, \"" + value + "\" is invalid");
		}
		
		return( retval );
	}

	public static Calendar parseTZTime( String fieldName, String value ) {
		final String S_ProcName = "parseTZTime";
		if( ( fieldName == null ) || ( fieldName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
				S_ProcName,
				1,
				"fieldName" );
		}
		if( ( value == null ) || ( value.length() == 0 ) ) {
			return( null );
		}
		
		if( ( value.length() != 9 ) && ( value.length() != 14 ) ) {
			throw new CFLibInvalidArgumentException( fieldName,
				S_ProcName,
				2,
				"value",
				"Invalid value format, must be HH:MI:SSZ or HH:MI:SS+HO:MO, \"" + value + "\" is invalid");
		}
		
		if( ! ( Character.isDigit( value.charAt(0) )
				&& Character.isDigit( value.charAt(1) )
				&& ( value.charAt(2) == ':' )
				&& Character.isDigit( value.charAt(3) )
				&& Character.isDigit( value.charAt(4) )
				&& ( value.charAt(5) == ':' )
				&& Character.isDigit( value.charAt(6) )
				&& Character.isDigit( value.charAt(7) ) ) )
		{
			throw new CFLibInvalidArgumentException( fieldName,
				S_ProcName,
				2,
				"value",
				"Invalid value format, must be HH:MI:SSZ or HH:MI:SS+HO:MO, \"" + value + "\" is invalid");
		}

		Calendar retval = null;

		if( value.charAt( 8 ) == 'Z' ) {
			int hour = Integer.parseInt( value.substring( 0, 2 ) );
			int minute = Integer.parseInt( value.substring( 3, 5 ) );
			int second = Integer.parseInt( value.substring( 6, 8 ) );
            TimeZone tz = TimeZone.getTimeZone( "+0000" );
            retval = new GregorianCalendar( tz );
            retval.set( Calendar.YEAR, 1970 );
            retval.set( Calendar.MONTH, 0 );
            retval.set( Calendar.DAY_OF_MONTH, 1 );
            retval.set( Calendar.HOUR_OF_DAY, hour );
            retval.set( Calendar.MINUTE, minute );
            retval.set( Calendar.SECOND, second );
            retval.getTimeInMillis(); // Force calendar resync based on input values
   			retval = new GregorianCalendar( 1970, 0, 1, hour, minute, second );
		}
		else if( ( value.charAt( 8 ) == '-' )
			&& ( Character.isDigit( value.charAt( 9 ) ) )
			&& ( Character.isDigit( value.charAt( 10 ) ) )
			&& ( value.charAt( 11 ) == ':' )
			&& ( Character.isDigit( value.charAt( 12 ) ) )
			&& ( Character.isDigit( value.charAt( 13 ) ) ) )
		{
			int hour = Integer.parseInt( value.substring( 0, 2 ) );
			int minute = Integer.parseInt( value.substring( 3, 5 ) );
			int second = Integer.parseInt( value.substring( 6, 8 ) );
            String tzCustomName = "GMT" + value.substring( 8, 11 ) + value.substring( 12, 14 );
            TimeZone tz = TimeZone.getTimeZone( tzCustomName );
            retval = new GregorianCalendar( tz );
            retval.set( Calendar.YEAR, 1970 );
            retval.set( Calendar.MONTH, 0 );
            retval.set( Calendar.DAY_OF_MONTH, 1 );
            retval.set( Calendar.HOUR_OF_DAY, hour );
            retval.set( Calendar.MINUTE, minute );
            retval.set( Calendar.SECOND, second );
            retval.getTimeInMillis(); // Force calendar resync based on input values
		}
		else if( ( value.charAt( 8 ) == '+' )
				&& ( Character.isDigit( value.charAt( 9 ) ) )
				&& ( Character.isDigit( value.charAt( 10 ) ) )
				&& ( value.charAt( 11 ) == ':' )
				&& ( Character.isDigit( value.charAt( 12 ) ) )
				&& ( Character.isDigit( value.charAt( 13 ) ) ) )
		{
			int hour = Integer.parseInt( value.substring( 0, 2 ) );
			int minute = Integer.parseInt( value.substring( 3, 5 ) );
			int second = Integer.parseInt( value.substring( 6, 8 ) );
            String tzCustomName = "GMT" + value.substring( 8, 11 ) + value.substring( 12, 14 );
            TimeZone tz = TimeZone.getTimeZone( tzCustomName );
            retval = new GregorianCalendar( tz );
            retval.set( Calendar.YEAR, 1970 );
            retval.set( Calendar.MONTH, 0 );
            retval.set( Calendar.DAY_OF_MONTH, 1 );
            retval.set( Calendar.HOUR_OF_DAY, hour );
            retval.set( Calendar.MINUTE, minute );
            retval.set( Calendar.SECOND, second );
            retval.getTimeInMillis(); // Force calendar resync based on input values
		}
		else {
			throw new CFLibInvalidArgumentException( fieldName,
				S_ProcName,
				2,
				"value",
				"Invalid value format, must be HH:MI:SSZ or HH:MI:SS+HO:MO, \"" + value + "\" is invalid");
		}
		
		return( retval );
	}

	public static Calendar parseTZTimestamp( String value ) {
		final String S_ProcName = "parseTZTimestamp";
		if( ( value == null ) || ( value.length() == 0 ) ) {
			return( null );
		}

		if( ( value.length() != 20 ) && ( value.length() != 25 ) ){
			throw new CFLibInvalidArgumentException( CFLibXmlUtil.class,
				S_ProcName,
				1,
				"value",
				"Invalid value format, must be YYYY-MM-DDTHH:MI:SSZ or YYYY-MM-DDTHH:MI:SS+HO:MO, \"" + value + "\" is invalid");
		}
		
		if( ! ( Character.isDigit( value.charAt(0) )
				&& Character.isDigit( value.charAt(1) )
				&& Character.isDigit( value.charAt(2) )
				&& Character.isDigit( value.charAt(3) )
				&& ( value.charAt(4) == '-' )
				&& Character.isDigit( value.charAt(5) )
				&& Character.isDigit( value.charAt(6) )
				&& ( value.charAt(7) == '-' )
				&& Character.isDigit( value.charAt(8) )
				&& Character.isDigit( value.charAt(9) )
				&& ( value.charAt(10) == 'T' )
				&& Character.isDigit( value.charAt(11) )
				&& Character.isDigit( value.charAt(12) )
				&& ( value.charAt(13) == ':' )
				&& Character.isDigit( value.charAt(14) )
				&& Character.isDigit( value.charAt(15) )
				&& ( value.charAt(16) == ':' )
				&& Character.isDigit( value.charAt(17) )
				&& Character.isDigit( value.charAt(18) ) ) )
		{
			throw new CFLibInvalidArgumentException( CFLibXmlUtil.class,
				S_ProcName,
				1,
				"value",
				"Invalid value format, must be YYYY-MM-DDTHH:MI:SSZ or YYYY-MM-DDTHH:MI:SS+HO:MO, \"" + value + "\" is invalid");
		}
		
		Calendar retval = null;

		if( value.charAt( 19 ) == 'Z' ) {
            int year = Integer.parseInt( value.substring( 0, 4 ) );
            int month = Integer.parseInt( value.substring( 5, 7 ) );
            int day = Integer.parseInt( value.substring( 8, 10 ) );
			int hour = Integer.parseInt( value.substring( 11, 13 ) );
			int minute = Integer.parseInt( value.substring( 14, 16 ) );
			int second = Integer.parseInt( value.substring( 17, 19 ) );
            TimeZone tz = TimeZone.getTimeZone( "+0000" );
            retval = new GregorianCalendar( tz );
            retval.set( Calendar.YEAR, year );
            retval.set( Calendar.MONTH, month - 1 );
            retval.set( Calendar.DAY_OF_MONTH, day );
            retval.set( Calendar.HOUR_OF_DAY, hour );
            retval.set( Calendar.MINUTE, minute );
            retval.set( Calendar.SECOND, second );
            retval.getTimeInMillis(); // Force calendar resync based on input values
   			retval = new GregorianCalendar( year, month - 1, day, hour, minute, second );
		}
		else if( ( value.charAt( 19 ) == '-' )
			&& ( Character.isDigit( value.charAt( 20 ) ) )
			&& ( Character.isDigit( value.charAt( 21 ) ) )
			&& ( value.charAt( 22 ) == ':' )
			&& ( Character.isDigit( value.charAt( 23 ) ) )
			&& ( Character.isDigit( value.charAt( 24 ) ) ) )
		{
            int year = Integer.parseInt( value.substring( 0, 4 ) );
            int month = Integer.parseInt( value.substring( 5, 7 ) );
            int day = Integer.parseInt( value.substring( 8, 10 ) );
			int hour = Integer.parseInt( value.substring( 11, 13 ) );
			int minute = Integer.parseInt( value.substring( 14, 16 ) );
			int second = Integer.parseInt( value.substring( 17, 19 ) );
            String tzCustomName = "GMT" + value.substring( 19, 22 ) + value.substring( 23, 25 );
            TimeZone tz = TimeZone.getTimeZone( tzCustomName );
            retval = new GregorianCalendar( tz );
            retval.set( Calendar.YEAR, year );
            retval.set( Calendar.MONTH, month - 1 );
            retval.set( Calendar.DAY_OF_MONTH, day );
            retval.set( Calendar.HOUR_OF_DAY, hour );
            retval.set( Calendar.MINUTE, minute );
            retval.set( Calendar.SECOND, second );
            retval.getTimeInMillis(); // Force calendar resync based on input values
		}
		else if( ( value.charAt( 19 ) == '+' )
				&& ( Character.isDigit( value.charAt( 20 ) ) )
				&& ( Character.isDigit( value.charAt( 21 ) ) )
				&& ( value.charAt( 22 ) == ':' )
				&& ( Character.isDigit( value.charAt( 23 ) ) )
				&& ( Character.isDigit( value.charAt( 24 ) ) ) )
		{
            int year = Integer.parseInt( value.substring( 0, 4 ) );
            int month = Integer.parseInt( value.substring( 5, 7 ) );
            int day = Integer.parseInt( value.substring( 8, 10 ) );
			int hour = Integer.parseInt( value.substring( 11, 13 ) );
			int minute = Integer.parseInt( value.substring( 14, 16 ) );
			int second = Integer.parseInt( value.substring( 17, 19 ) );
            String tzCustomName = "GMT" + value.substring( 19, 22 ) + value.substring( 23, 25 );
            TimeZone tz = TimeZone.getTimeZone( tzCustomName );
            retval = new GregorianCalendar( tz );
            retval.set( Calendar.YEAR, year );
            retval.set( Calendar.MONTH, month - 1 );
            retval.set( Calendar.DAY_OF_MONTH, day );
            retval.set( Calendar.HOUR_OF_DAY, hour );
            retval.set( Calendar.MINUTE, minute );
            retval.set( Calendar.SECOND, second );
            retval.getTimeInMillis(); // Force calendar resync based on input values
		}
		else {
			throw new CFLibInvalidArgumentException( CFLibXmlUtil.class,
				S_ProcName,
				1,
				"value",
				"Invalid value format, must be YYYY-MM-DDTHH:MI:SSZ or YYYY-MM-DDTHH:MI:SS+HO:MO, \"" + value + "\" is invalid");
		}

		return( retval );
	}

	public static Calendar parseTZTimestamp( String fieldName, String value ) {
		final String S_ProcName = "parseTZTimestamp";
		if( ( fieldName == null ) || ( fieldName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
				S_ProcName,
				1,
				"fieldName" );
		}
		if( ( value == null ) || ( value.length() == 0 ) ) {
			return( null );
		}

		if( ( value.length() != 20 ) && ( value.length() != 25 ) ){
			throw new CFLibInvalidArgumentException( CFLibXmlUtil.class,
				S_ProcName,
				2,
				"value",
				"Invalid value format, must be YYYY-MM-DDTHH:MI:SSZ or YYYY-MM-DDTHH:MI:SS+HO:MO, \"" + value + "\" is invalid");
		}
		
		if( ! ( Character.isDigit( value.charAt(0) )
				&& Character.isDigit( value.charAt(1) )
				&& Character.isDigit( value.charAt(2) )
				&& Character.isDigit( value.charAt(3) )
				&& ( value.charAt(4) == '-' )
				&& Character.isDigit( value.charAt(5) )
				&& Character.isDigit( value.charAt(6) )
				&& ( value.charAt(7) == '-' )
				&& Character.isDigit( value.charAt(8) )
				&& Character.isDigit( value.charAt(9) )
				&& ( value.charAt(10) == 'T' )
				&& Character.isDigit( value.charAt(11) )
				&& Character.isDigit( value.charAt(12) )
				&& ( value.charAt(13) == ':' )
				&& Character.isDigit( value.charAt(14) )
				&& Character.isDigit( value.charAt(15) )
				&& ( value.charAt(16) == ':' )
				&& Character.isDigit( value.charAt(17) )
				&& Character.isDigit( value.charAt(18) ) ) )
		{
			throw new CFLibInvalidArgumentException( CFLibXmlUtil.class,
				S_ProcName,
				2,
				"value",
				"Invalid value format, must be YYYY-MM-DDTHH:MI:SSZ or YYYY-MM-DDTHH:MI:SS+HO:MO, \"" + value + "\" is invalid");
		}
		
		Calendar retval = null;

		if( value.charAt( 19 ) == 'Z' ) {
            int year = Integer.parseInt( value.substring( 0, 4 ) );
            int month = Integer.parseInt( value.substring( 5, 7 ) );
            int day = Integer.parseInt( value.substring( 8, 10 ) );
			int hour = Integer.parseInt( value.substring( 11, 13 ) );
			int minute = Integer.parseInt( value.substring( 14, 16 ) );
			int second = Integer.parseInt( value.substring( 17, 19 ) );
            TimeZone tz = TimeZone.getTimeZone( "+0000" );
            retval = new GregorianCalendar( tz );
            retval.set( Calendar.YEAR, year );
            retval.set( Calendar.MONTH, month - 1 );
            retval.set( Calendar.DAY_OF_MONTH, day );
            retval.set( Calendar.HOUR_OF_DAY, hour );
            retval.set( Calendar.MINUTE, minute );
            retval.set( Calendar.SECOND, second );
            retval.getTimeInMillis(); // Force calendar resync based on input values
   			retval = new GregorianCalendar( year, month - 1, day, hour, minute, second );
		}
		else if( ( value.charAt( 19 ) == '-' )
			&& ( Character.isDigit( value.charAt( 20 ) ) )
			&& ( Character.isDigit( value.charAt( 21 ) ) )
			&& ( value.charAt( 22 ) == ':' )
			&& ( Character.isDigit( value.charAt( 23 ) ) )
			&& ( Character.isDigit( value.charAt( 24 ) ) ) )
		{
            int year = Integer.parseInt( value.substring( 0, 4 ) );
            int month = Integer.parseInt( value.substring( 5, 7 ) );
            int day = Integer.parseInt( value.substring( 8, 10 ) );
			int hour = Integer.parseInt( value.substring( 11, 13 ) );
			int minute = Integer.parseInt( value.substring( 14, 16 ) );
			int second = Integer.parseInt( value.substring( 17, 19 ) );
            String tzCustomName = "GMT" + value.substring( 19, 22 ) + value.substring( 23, 25 );
            TimeZone tz = TimeZone.getTimeZone( tzCustomName );
            retval = new GregorianCalendar( tz );
            retval.set( Calendar.YEAR, year );
            retval.set( Calendar.MONTH, month - 1 );
            retval.set( Calendar.DAY_OF_MONTH, day );
            retval.set( Calendar.HOUR_OF_DAY, hour );
            retval.set( Calendar.MINUTE, minute );
            retval.set( Calendar.SECOND, second );
            retval.getTimeInMillis(); // Force calendar resync based on input values
		}
		else if( ( value.charAt( 19 ) == '+' )
				&& ( Character.isDigit( value.charAt( 20 ) ) )
				&& ( Character.isDigit( value.charAt( 21 ) ) )
				&& ( value.charAt( 22 ) == ':' )
				&& ( Character.isDigit( value.charAt( 23 ) ) )
				&& ( Character.isDigit( value.charAt( 24 ) ) ) )
		{
            int year = Integer.parseInt( value.substring( 0, 4 ) );
            int month = Integer.parseInt( value.substring( 5, 7 ) );
            int day = Integer.parseInt( value.substring( 8, 10 ) );
			int hour = Integer.parseInt( value.substring( 11, 13 ) );
			int minute = Integer.parseInt( value.substring( 14, 16 ) );
			int second = Integer.parseInt( value.substring( 17, 19 ) );
            String tzCustomName = "GMT" + value.substring( 19, 22 ) + value.substring( 23, 25 );
            TimeZone tz = TimeZone.getTimeZone( tzCustomName );
            retval = new GregorianCalendar( tz );
            retval.set( Calendar.YEAR, year );
            retval.set( Calendar.MONTH, month - 1 );
            retval.set( Calendar.DAY_OF_MONTH, day );
            retval.set( Calendar.HOUR_OF_DAY, hour );
            retval.set( Calendar.MINUTE, minute );
            retval.set( Calendar.SECOND, second );
            retval.getTimeInMillis(); // Force calendar resync based on input values
		}
		else {
			throw new CFLibInvalidArgumentException( CFLibXmlUtil.class,
				S_ProcName,
				2,
				"value",
				"Invalid value format, must be YYYY-MM-DDTHH:MI:SSZ or YYYY-MM-DDTHH:MI:SS+HO:MO, \"" + value + "\" is invalid");
		}

		return( retval );
	}

	public static String formatBoolean( boolean val ) {
		final String S_False = "false";
		final String S_True = "true";
		String retval;
		if( val ) {
			retval = S_True;
		}
		else {
			retval = S_False;
		}
		return( retval );
	}

	public static String formatBlob( byte[] val ) {
		final String S_ProcName = "formatBlob";
		if( val == null ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"val" );
		}
		byte[] encoded = Base64.encodeBase64( val );
		String retval = new String( encoded );
		return( retval );
	}
	
	public static String formatInt16( short val ) {
		String retval = Short.toString( val );
		return( retval );
	}

	public static String formatInt32( int val ) {
		String retval = Integer.toString( val );
		return( retval );
	}

	public static String formatInt64( long val ) {
		String retval = Long.toString( val );
		return( retval );
	}

	public static String formatUInt16( int val ) {
		final String S_ProcName = "formatUInt16";
		if( val < 0 ) {
			throw new CFLibArgumentUnderflowException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"val",
					val,
					0 );
		}
		String retval = Integer.toString( val );
		return( retval );
	}

	public static String formatUInt32( long val ) {
		String retval = Long.toString( val );
		return( retval );
	}

	public static String formatUInt64( BigDecimal val ) {
		final String S_ProcName = "formatUInt64";
		if( val == null ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"val" );
		}
		String retval = val.toString();
		return( retval );
	}

	public static String formatFloat( float val ) {
		final DecimalFormat fmt = new DecimalFormat( "#################################################################################################################################0.##################################################################################################################################" );
		String retval = fmt.format( val );
		return( retval );
	}

	public static String formatDouble( double val ) {
		final DecimalFormat fmt = new DecimalFormat( "#########################################################################################################################################################################################################################################################################################################################################0.##########################################################################################################################################################################################################################################################################################################################################" );
		String retval = fmt.format( val );
		return( retval );
	}

	public static String formatNumber( BigDecimal val ) {
		final String S_ProcName = "formatNumber";
		final DecimalFormat fmt = new DecimalFormat( "#########################################################################################################################################################################################################################################################################################################################################0.#########################################################################################################################################################################################################################################################################################################################################" );
		if( val == null ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"val" );
		}
		String retval = fmt.format( val );
		return( retval );
	}

	public static String formatXmlString( String str ) {
		final String S_ProcName = "formatXmlString";
		if( str == null ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
				S_ProcName,
				1,
				"str" );
		}
		StringBuffer buff = new StringBuffer();
		char ch;
		int idx;
		int len = str.length();
		for( idx = 0; idx < len; idx ++ ) {
			ch = str.charAt( idx );
			switch( ch ) {
				case '\n':
					buff.append( "&#10;");
					break;
				case '\r':
					buff.append( "&#13;" );
					break;
				case ' ':
				case '\t':
				case '@':
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
				case 'a':
				case 'b':
				case 'c':
				case 'd':
				case 'e':
				case 'f':
				case 'g':
				case 'h':
				case 'i':
				case 'j':
				case 'k':
				case 'l':
				case 'm':
				case 'n':
				case 'o':
				case 'p':
				case 'q':
				case 'r':
				case 's':
				case 't':
				case 'u':
				case 'v':
				case 'w':
				case 'x':
				case 'y':
				case 'z':
				case 'A':
				case 'B':
				case 'C':
				case 'D':
				case 'E':
				case 'F':
				case 'G':
				case 'H':
				case 'I':
				case 'J':
				case 'K':
				case 'L':
				case 'M':
				case 'N':
				case 'O':
				case 'P':
				case 'Q':
				case 'R':
				case 'S':
				case 'T':
				case 'U':
				case 'V':
				case 'W':
				case 'X':
				case 'Y':
				case 'Z':
				case '~':
				case '!':
				case '#':
				case '$':
				case '%':
				case '^':
				case '*':
				case '(':
				case ')':
				case '-':
				case '_':
				case '+':
				case '=':
				case '{':
				case '}':
				case '[':
				case ']':
				case ':':
				case ';':
				case ',':
				case '.':
				case '?':
				case '/':
				case '\\':
				case '|':
					buff.append( ch );
					break;
				case '\'':
					buff.append( "&apos;" );
					break;
				case '"':
					buff.append( "&quot;" );
					break;
				case '&':
					buff.append( "&amp;" );
					break;
				case '<':
					buff.append( "&lt;" );
					break;
				case '>':
					buff.append( "&gt;" );
					break;
				default:
					if( ! Character.isValidCodePoint( ch ) ) {
						throw new CFLibArgumentRangeException( CFLibXmlUtil.class,
							S_ProcName,
							"Only valid code points can be formatted, ch is out of range" );
					}
					int charCode = (int)ch;
					String seq = "&#" + Integer.toString( charCode ) + ";";
					buff.append( seq );
					break;
			}
		}
		String retval = buff.toString();
		return( retval );
	}

	public static String formatXmlStringWhitespacePreserve( String str ) {
		final String S_ProcName = "formatXmlStringWhitespacePreserve";
		if( str == null ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
				S_ProcName,
				1,
				"str" );
		}
		StringBuffer buff = new StringBuffer();
		char ch;
		int idx;
		int len = str.length();
		for( idx = 0; idx < len; idx ++ ) {
			ch = str.charAt( idx );
			switch( ch ) {
				case '\n':
				case '\r':
				case ' ':
				case '\t':
				case '@':
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
				case 'a':
				case 'b':
				case 'c':
				case 'd':
				case 'e':
				case 'f':
				case 'g':
				case 'h':
				case 'i':
				case 'j':
				case 'k':
				case 'l':
				case 'm':
				case 'n':
				case 'o':
				case 'p':
				case 'q':
				case 'r':
				case 's':
				case 't':
				case 'u':
				case 'v':
				case 'w':
				case 'x':
				case 'y':
				case 'z':
				case 'A':
				case 'B':
				case 'C':
				case 'D':
				case 'E':
				case 'F':
				case 'G':
				case 'H':
				case 'I':
				case 'J':
				case 'K':
				case 'L':
				case 'M':
				case 'N':
				case 'O':
				case 'P':
				case 'Q':
				case 'R':
				case 'S':
				case 'T':
				case 'U':
				case 'V':
				case 'W':
				case 'X':
				case 'Y':
				case 'Z':
				case '~':
				case '!':
				case '#':
				case '$':
				case '%':
				case '^':
				case '*':
				case '(':
				case ')':
				case '-':
				case '_':
				case '+':
				case '=':
				case '{':
				case '}':
				case '[':
				case ']':
				case ':':
				case ';':
				case ',':
				case '.':
				case '?':
				case '/':
				case '\\':
				case '|':
					buff.append( ch );
					break;
				case '\'':
					buff.append( "&apos;" );
					break;
				case '"':
					buff.append( "&quot;" );
					break;
				case '&':
					buff.append( "&amp;" );
					break;
				case '<':
					buff.append( "&lt;" );
					break;
				case '>':
					buff.append( "&gt;" );
					break;
				default:
					if( ! Character.isValidCodePoint( ch ) ) {
						throw new CFLibArgumentRangeException( CFLibXmlUtil.class,
							S_ProcName,
							"Only valid code points can be formatted, ch is out of range" );
					}
					int charCode = (int)ch;
					String seq = "&#" + Integer.toString( charCode ) + ";";
					buff.append( seq );
					break;
			}
		}
		String retval = buff.toString();
		return( retval );
	}

	public static String formatDate( Calendar cal ) {
		final String S_ProcName = "formatDate";
		if( cal == null ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
				S_ProcName,
				1,
				"cal" );
		}
		StringBuffer buff = new StringBuffer();
		Formatter fmt = new Formatter( buff );
		fmt.format( "%1$04d",  cal.get( Calendar.YEAR ) );
		buff.append( '-' );
		fmt.format( "%1$02d",  cal.get( Calendar.MONTH ) + 1 );
		buff.append( '-' );
		fmt.format( "%1$02d",  cal.get( Calendar.DAY_OF_MONTH ) );
		String retval = buff.toString();
		fmt.close();
		return( retval );
	}

	public static String formatTime( Calendar cal ) {
		final String S_ProcName = "formatTime";
		if( cal == null ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"cal" );
		}
		StringBuffer buff = new StringBuffer();
		Formatter fmt = new Formatter( buff );
		fmt.format( "%1$02d",  cal.get( Calendar.HOUR_OF_DAY ) );
		buff.append( ':' );
		fmt.format( "%1$02d",  cal.get( Calendar.MINUTE ) );
		buff.append( ':' );
		fmt.format( "%1$02d",  cal.get( Calendar.SECOND ) );
		String retval = buff.toString();
		fmt.close();
		return( retval );
	}

	public static String formatTimestamp( Calendar cal ) {
		final String S_ProcName = "formatTimestamp";
		if( cal == null ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName, 
					1,
					"cal" );
		}
		StringBuffer buff = new StringBuffer();
		Formatter fmt = new Formatter( buff );
		fmt.format( "%1$04d",  cal.get( Calendar.YEAR ) );
		buff.append( '-' );
		fmt.format( "%1$02d",  cal.get( Calendar.MONTH ) + 1 );
		buff.append( '-' );
		fmt.format( "%1$02d",  cal.get( Calendar.DAY_OF_MONTH ) );
		buff.append( 'T' );
		fmt.format( "%1$02d",  cal.get( Calendar.HOUR_OF_DAY ) );
		buff.append( ':' );
		fmt.format( "%1$02d",  cal.get( Calendar.MINUTE ) );
		buff.append( ':' );
		fmt.format( "%1$02d",  cal.get( Calendar.SECOND ) );
		String retval = buff.toString();
		fmt.close();
		return( retval );
	}

	public static String formatTZDate( Calendar cal ) {
		final String S_ProcName = "formatTZDate";
		if( cal == null ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"cal" );
		}
		StringBuffer buff = new StringBuffer();
		Formatter fmt = new Formatter( buff );
		fmt.format( "%1$04d",  cal.get( Calendar.YEAR ) );
		buff.append( '-' );
		fmt.format( "%1$02d",  cal.get( Calendar.MONTH ) + 1);
		buff.append( '-' );
		fmt.format( "%1$02d",  cal.get( Calendar.DAY_OF_MONTH ) );
		int tzoff = cal.getTimeZone().getRawOffset() / 60000;
		if( tzoff < 0 ) {
			tzoff = 0 - tzoff;
			buff.append( '-' );
		}
		else {
			buff.append( '+' );
		}
		int tzhour = tzoff / 60;
		int tzmin = tzoff % 60;
		if( tzhour > 12 ) {
			fmt.close();
			throw new CFLibArgumentOverflowException( CFLibXmlUtil.class,
				S_ProcName,
				0,
				"tzhour",
				tzhour,
				12 );
		}
		fmt.format( "%1$02d", tzhour );
		buff.append( ':' );
		fmt.format( "%1$02d", tzmin );
		String retval = buff.toString();
		fmt.close();
		return( retval );
	}

	public static String formatTZTime( Calendar cal ) {
		final String S_ProcName = "formatTZTime";
		if( cal == null ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"cal" );
		}
		StringBuffer buff = new StringBuffer();
		Formatter fmt = new Formatter( buff );
		fmt.format( "%1$02d",  cal.get( Calendar.HOUR_OF_DAY ) );
		buff.append( ':' );
		fmt.format( "%1$02d",  cal.get( Calendar.MINUTE ) );
		buff.append( ':' );
		fmt.format( "%1$02d",  cal.get( Calendar.SECOND ) );
		int tzoff = cal.getTimeZone().getRawOffset() / 60000;
		if( tzoff < 0 ) {
			tzoff = 0 - tzoff;
			buff.append( '-' );
		}
		else {
			buff.append( '+' );
		}
		int tzhour = tzoff / 60;
		int tzmin = tzoff % 60;
		if( tzhour > 12 ) {
			fmt.close();
			throw new CFLibArgumentOverflowException( CFLibXmlUtil.class,
				S_ProcName,
				0,
				"tzhour",
				tzhour,
				12 );
		}
		fmt.format( "%1$02d", tzhour );
		buff.append( ':' );
		fmt.format( "%1$02d", tzmin );
		String retval = buff.toString();
		fmt.close();
		return( retval );
	}

	public static String formatTZTimestamp( Calendar cal ) {
		final String S_ProcName = "formatTZTimestamp";
		if( cal == null ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"cal" );
		}
		StringBuffer buff = new StringBuffer();
		Formatter fmt = new Formatter( buff );
		fmt.format( "%1$04d",  cal.get( Calendar.YEAR ) );
		buff.append( '-' );
		fmt.format( "%1$02d",  cal.get( Calendar.MONTH ) + 1);
		buff.append( '-' );
		fmt.format( "%1$02d",  cal.get( Calendar.DAY_OF_MONTH ) );
		buff.append( 'T' );
		fmt.format( "%1$02d",  cal.get( Calendar.HOUR_OF_DAY ) );
		buff.append( ':' );
		fmt.format( "%1$02d",  cal.get( Calendar.MINUTE ) );
		buff.append( ':' );
		fmt.format( "%1$02d",  cal.get( Calendar.SECOND ) );
		int tzoff = cal.getTimeZone().getRawOffset() / 60000;
		if( tzoff < 0 ) {
			tzoff = 0 - tzoff;
			buff.append( '-' );
		}
		else {
			buff.append( '+' );
		}
		int tzhour = tzoff / 60;
		int tzmin = tzoff % 60;
		if( tzhour > 12 ) {
			fmt.close();
			throw new CFLibArgumentOverflowException( CFLibXmlUtil.class,
				S_ProcName,
				0,
				"tzhour",
				tzhour,
				12 );
		}
		fmt.format( "%1$02d", tzhour );
		buff.append( ':' );
		fmt.format( "%1$02d", tzmin );
		String retval = buff.toString();
		fmt.close();
		return( retval );
	}

	public static String formatUuid( UUID val ) {
		final String S_ProcName = "formatUuid";
		if( val == null ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"val" );
		}
		String retval = val.toString();
		return( retval );
	}

	/**
	 *	Formatting for Required XML attributes.
	**/
	
	public static String formatRequiredBoolean( String separator, String attrName, boolean val ) {
		final String S_ProcName = "formatRequiredBoolean";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval = (( separator != null ) ? separator : S_emptyString ) + attrName + "=\"" + formatBoolean( val ) + "\"";
		return( retval );
	}

	public static String formatRequiredBlob( String separator, String attrName, byte[] val ) {
		final String S_ProcName = "formatRequiredBlob";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval = (( separator != null ) ? separator : S_emptyString ) + attrName + "=\"" + formatBlob( val ) + "\"";
		return( retval );
	}
	
	public static String formatRequiredInt16( String separator, String attrName, short val ) {
		final String S_ProcName = "formatRequiredInt16";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval = (( separator != null ) ? separator : S_emptyString ) + attrName + "=\"" + formatInt16( val ) + "\"";
		return( retval );
	}

	public static String formatRequiredInt32( String separator, String attrName, int val ) {
		final String S_ProcName = "formatRequiredInt32";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval = (( separator != null ) ? separator : S_emptyString ) + attrName + "=\"" + formatInt32( val ) + "\"";
		return( retval );
	}

	public static String formatRequiredInt64( String separator, String attrName, long val ) {
		final String S_ProcName = "formatRequiredInt64";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval = (( separator != null ) ? separator : S_emptyString ) + attrName + "=\"" + formatInt64( val ) + "\"";
		return( retval );
	}

	public static String formatRequiredUInt16( String separator, String attrName, int val ) {
		final String S_ProcName = "formatRequiredUInt16";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval = (( separator != null ) ? separator : S_emptyString ) + attrName + "=\"" + formatUInt16( val ) + "\"";
		return( retval );
	}

	public static String formatRequiredUInt32( String separator, String attrName, long val ) {
		final String S_ProcName = "formatRequiredUInt32";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval = (( separator != null ) ? separator : S_emptyString ) + attrName + "=\"" + formatUInt32( val ) + "\"";
		return( retval );
	}

	public static String formatRequiredUInt64( String separator, String attrName, BigDecimal val ) {
		final String S_ProcName = "formatRequiredUInt64";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval = (( separator != null ) ? separator : S_emptyString ) + attrName + "=\"" + formatUInt64( val ) + "\"";
		return( retval );
	}

	public static String formatRequiredFloat( String separator, String attrName, float val ) {
		final String S_ProcName = "formatRequiredFloat";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval = (( separator != null ) ? separator : S_emptyString ) + attrName + "=\"" + formatFloat( val ) + "\"";
		return( retval );
	}

	public static String formatRequiredDouble( String separator, String attrName, double val ) {
		final String S_ProcName = "formatRequiredDouble";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval = (( separator != null ) ? separator : S_emptyString ) + attrName + "=\"" + formatDouble( val ) + "\"";
		return( retval );
	}

	public static String formatRequiredNumber( String separator, String attrName, BigDecimal val ) {
		final String S_ProcName = "formatRequiredNumber";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval = (( separator != null ) ? separator : S_emptyString ) + attrName + "=\"" + formatNumber( val ) + "\"";
		return( retval );
	}

	public static String formatRequiredXmlString( String separator, String attrName, String str ) {
		final String S_ProcName = "formatRequiredXmlString";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval = (( separator != null ) ? separator : S_emptyString ) + attrName + "=\"" + formatXmlString( str ) + "\"";
		return( retval );
	}

	public static String formatRequiredDate( String separator, String attrName, Calendar cal ) {
		final String S_ProcName = "formatRequiredDate";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval = (( separator != null ) ? separator : S_emptyString ) + attrName + "=\"" + formatDate( cal ) + "\"";
		return( retval );
	}

	public static String formatRequiredTime( String separator, String attrName, Calendar cal ) {
		final String S_ProcName = "formatRequiredTime";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval = (( separator != null ) ? separator : S_emptyString ) + attrName + "=\"" + formatTime( cal ) + "\"";
		return( retval );
	}

	public static String formatRequiredTimestamp( String separator, String attrName, Calendar cal ) {
		final String S_ProcName = "formatRequiredTimestamp";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval = (( separator != null ) ? separator : S_emptyString ) + attrName + "=\"" + formatTimestamp( cal ) + "\"";
		return( retval );
	}

	public static String formatRequiredTZDate( String separator, String attrName, Calendar cal ) {
		final String S_ProcName = "formatRequiredTZDate";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval = (( separator != null ) ? separator : S_emptyString ) + attrName + "=\"" + formatTZDate( cal ) + "\"";
		return( retval );
	}

	public static String formatRequiredTZTime( String separator, String attrName, Calendar cal ) {
		final String S_ProcName = "formatRequiredTZTime";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval = (( separator != null ) ? separator : S_emptyString ) + attrName + "=\"" + formatTZTime( cal ) + "\"";
		return( retval );
	}

	public static String formatRequiredTZTimestamp( String separator, String attrName, Calendar cal ) {
		final String S_ProcName = "formatRequiredTZTimestamp";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval = (( separator != null ) ? separator : S_emptyString ) + attrName + "=\"" + formatTZTimestamp( cal ) + "\"";
		return( retval );
	}

	public static String formatRequiredUuid( String separator, String attrName, UUID val ) {
		final String S_ProcName = "formatRequiredUuid";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval = (( separator != null ) ? separator : S_emptyString ) + attrName + "=\"" + formatUuid( val ) + "\"";
		return( retval );
	}

	/**
	 *	Formatting for Optional XML attributes.
	**/
	
	public static String formatOptionalBoolean( String separator, String attrName, Boolean val ) {
		final String S_ProcName = "formatOptionalBoolean";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval;
		if( val != null ) {
			retval = formatRequiredBoolean( separator, attrName, val.booleanValue() );
		}
		else {
			retval = S_emptyString;
		}
		return( retval );
	}

	public static String formatOptionalBlob( String separator, String attrName, byte[] val ) {
		final String S_ProcName = "formatOptionalBlob";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval;
		if( val != null ) {
			retval = formatRequiredBlob( separator, attrName, val );
		}
		else {
			retval = S_emptyString;
		}
		return( retval );
	}
	
	public static String formatOptionalInt16( String separator, String attrName, Short val ) {
		final String S_ProcName = "formatOptionalInt16";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval;
		if( val != null ) {
			retval = formatRequiredInt16( separator, attrName, val.shortValue() );
		}
		else {
			retval = S_emptyString;
		}
		return( retval );
	}

	public static String formatOptionalInt32( String separator, String attrName, Integer val ) {
		final String S_ProcName = "formatOptionalInt32";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval;
		if( val != null ) {
			retval = formatRequiredInt32( separator, attrName, val.intValue() );
		}
		else {
			retval = S_emptyString;
		}
		return( retval );
	}

	public static String formatOptionalInt64( String separator, String attrName, Long val ) {
		final String S_ProcName = "formatOptionalInt64";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval;
		if( val != null ) {
			retval = formatRequiredInt64( separator, attrName, val.longValue() );
		}
		else {
			retval = S_emptyString;
		}
		return( retval );
	}

	public static String formatOptionalUInt16( String separator, String attrName, Integer val ) {
		final String S_ProcName = "formatOptionalUInt16";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval;
		if( val != null ) {
			retval = formatRequiredUInt16( separator, attrName, val.intValue() );
		}
		else {
			retval = S_emptyString;
		}
		return( retval );
	}

	public static String formatOptionalUInt32( String separator, String attrName, Long val ) {
		final String S_ProcName = "formatOptionalUInt32";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval;
		if( val != null ) {
			retval = formatRequiredUInt32( separator, attrName, val.longValue() );
		}
		else {
			retval = S_emptyString;
		}
		return( retval );
	}

	public static String formatOptionalUInt64( String separator, String attrName, BigDecimal val ) {
		final String S_ProcName = "formatOptionalUInt64";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval;
		if( val != null ) {
			retval = formatRequiredUInt64( separator, attrName, val );
		}
		else {
			retval = S_emptyString;
		}
		return( retval );
	}

	public static String formatOptionalFloat( String separator, String attrName, Float val ) {
		final String S_ProcName = "formatOptionalFloat";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval;
		if( val != null ) {
			retval = formatRequiredFloat( separator, attrName, val.floatValue() );
		}
		else {
			retval = S_emptyString;
		}
		return( retval );
	}

	public static String formatOptionalDouble( String separator, String attrName, Double val ) {
		final String S_ProcName = "formatOptionalDouble";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval;
		if( val != null ) {
			retval = formatRequiredDouble( separator, attrName, val.doubleValue() );
		}
		else {
			retval = S_emptyString;
		}
		return( retval );
	}

	public static String formatOptionalNumber( String separator, String attrName, BigDecimal val ) {
		final String S_ProcName = "formatOptionalNumber";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval;
		if( val != null ) {
			retval = formatRequiredNumber( separator, attrName, val );
		}
		else {
			retval = S_emptyString;
		}
		return( retval );
	}

	public static String formatOptionalXmlString( String separator, String attrName, String str ) {
		final String S_ProcName = "formatOptionalXmlString";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval;
		if( str != null ) {
			retval = formatRequiredXmlString( separator, attrName, str );
		}
		else {
			retval = S_emptyString;
		}
		return( retval );
	}

	public static String formatOptionalDate( String separator, String attrName, Calendar cal ) {
		final String S_ProcName = "formatOptionalDate";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval;
		if( cal != null ) {
			retval = formatRequiredDate( separator, attrName, cal );
		}
		else {
			retval = S_emptyString;
		}
		return( retval );
	}

	public static String formatOptionalTime( String separator, String attrName, Calendar cal ) {
		final String S_ProcName = "formatOptionalTime";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval;
		if( cal != null ) {
			retval = formatRequiredTime( separator, attrName, cal );
		}
		else {
			retval = S_emptyString;
		}
		return( retval );
	}

	public static String formatOptionalTimestamp( String separator, String attrName, Calendar cal ) {
		final String S_ProcName = "formatOptionalTimestamp";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval;
		if( cal != null ) {
			retval = formatRequiredTimestamp( separator, attrName, cal );
		}
		else {
			retval = S_emptyString;
		}
		return( retval );
	}

	public static String formatOptionalTZDate( String separator, String attrName, Calendar cal ) {
		final String S_ProcName = "formatOptionalTZDate";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval;
		if( cal != null ) {
			retval = formatRequiredTZDate( separator, attrName, cal );
		}
		else {
			retval = S_emptyString;
		}
		return( retval );
	}

	public static String formatOptionalTZTime( String separator, String attrName, Calendar cal ) {
		final String S_ProcName = "formatOptionalTZTime";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval;
		if( cal != null ) {
			retval = formatRequiredTZTime( separator, attrName, cal );
		}
		else {
			retval = S_emptyString;
		}
		return( retval );
	}

	public static String formatOptionalTZTimestamp( String separator, String attrName, Calendar cal ) {
		final String S_ProcName = "formatOptionalTZTimestamp";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval;
		if( cal != null ) {
			retval = formatRequiredTZTimestamp( separator, attrName, cal );
		}
		else {
			retval = S_emptyString;
		}
		return( retval );
	}

	public static String formatOptionalUuid( String separator, String attrName, UUID val ) {
		final String S_ProcName = "formatOptionalUuid";
		if( ( attrName == null ) || ( attrName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibXmlUtil.class,
					S_ProcName,
					1,
					"attrName" );
		}
		String retval;
		if( val != null ) {
			retval = formatRequiredUuid( separator, attrName, val );
		}
		else {
			retval = S_emptyString;
		}
		return( retval );
	}
	
}
