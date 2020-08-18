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
import java.text.Format;

public class CFLibBigDecimalUtil {

	public final static int MAX_DIGITS = 31;
	public final static int MAX_PRECISION = 30;
	
	final static String S_Hashes = "###############################";
	final static String S_Zeroes = "0000000000000000000000000000000";
	final static String S_Nines =  "9999999999999999999999999999999";

	public static Format getNumberFormat( String fieldOrClassName, int argDigits, int argPrecis ) {
		final String S_ProcName = "getNumberFormat";

		if( ( fieldOrClassName == null ) || ( fieldOrClassName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibBigDecimalUtil.class,
				S_ProcName,
				1,
				"fieldOrClassName" );
		}

		if( argDigits < 1 ) {
			throw new CFLibArgumentUnderflowException( fieldOrClassName,
				S_ProcName,
				2,
				"argDigits",
				argDigits,
				1 );
		}
		else if( argDigits > MAX_DIGITS ) {
			throw new CFLibArgumentOverflowException( fieldOrClassName,
				S_ProcName,
				2,
				"argDigits",
				argDigits,
				MAX_DIGITS );
		}

		if( argPrecis < 0 ) {
			throw new CFLibArgumentUnderflowException( fieldOrClassName,
				S_ProcName,
				3,
				"argPrecis",
				argPrecis,
				0 );
		}
		else if( argPrecis > MAX_PRECISION ) {
			throw new CFLibArgumentOverflowException( fieldOrClassName,
				S_ProcName,
				3,
				"argPrecis",
				argPrecis,
				MAX_PRECISION );
		}

		if( argPrecis >= argDigits ) {
			throw new CFLibArgumentOverflowException( fieldOrClassName,
				S_ProcName,
				3,
				"argPrecis",
				argPrecis,
				argDigits - 1 );
		}

		int integerDigits = argDigits - argPrecis;
		
		String usePrefixHash = S_Hashes.substring( 0, integerDigits - 1 );
		
		String useSuffix;
		if( argPrecis > 0 ) {
			useSuffix = "." + S_Zeroes.substring( 0, argPrecis );
		}
		else {
			useSuffix = "";
		}
		
		Format numberFormat = new DecimalFormat(
			usePrefixHash + "0" + useSuffix + ";-" + usePrefixHash + "0" + useSuffix );
		
		return( numberFormat );
	}

	public static BigDecimal getAbsoluteMinValue( String fieldOrClassName, int argDigits, int argPrecis ) {
		final String S_ProcName = "getAbsoluteMinValue";

		if( ( fieldOrClassName == null ) || ( fieldOrClassName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibBigDecimalUtil.class,
				S_ProcName,
				1,
				"fieldOrClassName" );
		}

		if( argDigits < 1 ) {
			throw new CFLibArgumentUnderflowException( fieldOrClassName,
				S_ProcName,
				2,
				"argDigits",
				argDigits,
				1 );
		}
		else if( argDigits > MAX_DIGITS ) {
			throw new CFLibArgumentOverflowException( fieldOrClassName,
				S_ProcName,
				2,
				"argDigits",
				argDigits,
				MAX_DIGITS );
		}

		if( argPrecis < 0 ) {
			throw new CFLibArgumentUnderflowException( fieldOrClassName,
				S_ProcName,
				3,
				"argPrecis",
				argPrecis,
				0 );
		}
		else if( argPrecis > MAX_PRECISION ) {
			throw new CFLibArgumentOverflowException( fieldOrClassName,
				S_ProcName,
				3,
				"argPrecis",
				argPrecis,
				MAX_PRECISION );
		}

		if( argPrecis >= argDigits ) {
			throw new CFLibArgumentOverflowException( fieldOrClassName,
				S_ProcName,
				3,
				"argPrecis",
				argPrecis,
				argDigits - 1 );
		}

		int integerDigits = argDigits - argPrecis;

		String strval;
		if( argPrecis == 0 ) {
			strval = "-" + S_Nines.substring( 0, integerDigits );
		}
		else {
			strval = "-" + S_Nines.substring( 0, integerDigits ) + "." + S_Nines.substring( 0, argPrecis );
		}
		
		BigDecimal absoluteMinValue = new BigDecimal( strval );
		
		return( absoluteMinValue );
	}

	public static BigDecimal getAbsoluteMaxValue( String fieldOrClassName, int argDigits, int argPrecis ) {
		final String S_ProcName = "getAbsoluteMaxValue";

		if( ( fieldOrClassName == null ) || ( fieldOrClassName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibBigDecimalUtil.class,
				S_ProcName,
				1,
				"fieldOrClassName" );
		}

		if( argDigits < 1 ) {
			throw new CFLibArgumentUnderflowException( fieldOrClassName,
				S_ProcName,
				2,
				"argDigits",
				argDigits,
				1 );
		}
		else if( argDigits > MAX_DIGITS ) {
			throw new CFLibArgumentOverflowException( fieldOrClassName,
				S_ProcName,
				2,
				"argDigits",
				argDigits,
				MAX_DIGITS );
		}

		if( argPrecis < 0 ) {
			throw new CFLibArgumentUnderflowException( fieldOrClassName,
				S_ProcName,
				3,
				"argPrecis",
				argPrecis,
				0 );
		}
		else if( argPrecis > MAX_PRECISION ) {
			throw new CFLibArgumentOverflowException( fieldOrClassName,
				S_ProcName,
				3,
				"argPrecis",
				argPrecis,
				MAX_PRECISION );
		}

		if( argPrecis >= argDigits ) {
			throw new CFLibArgumentOverflowException( fieldOrClassName,
				S_ProcName,
				3,
				"argPrecis",
				argPrecis,
				argDigits - 1 );
		}

		int integerDigits = argDigits - argPrecis;

		String strval;
		if( argPrecis == 0 ) {
			strval = S_Nines.substring( 0, integerDigits );
		}
		else {
			strval = S_Nines.substring( 0, integerDigits ) + "." + S_Nines.substring( 0, argPrecis );
		}
		
		BigDecimal absoluteMaxValue = new BigDecimal( strval );
		
		return( absoluteMaxValue );
	}

	public static BigDecimal coerce( String fieldOrClassName, int argDigits, int argPrecis, BigDecimal value ) {
		final String S_ProcName = "coerce";

		if( ( fieldOrClassName == null ) || ( fieldOrClassName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibBigDecimalUtil.class,
				S_ProcName,
				1,
				"fieldOrClassName" );
		}

		if( value == null ) {
			throw new CFLibNullArgumentException( fieldOrClassName,
				S_ProcName,
				4,
				"value" );
		}
		
		if( argDigits < 1 ) {
			throw new CFLibArgumentUnderflowException( fieldOrClassName,
				S_ProcName,
				2,
				"argDigits",
				argDigits,
				1 );
		}
		else if( argDigits > MAX_DIGITS ) {
			throw new CFLibArgumentOverflowException( fieldOrClassName,
				S_ProcName,
				2,
				"argDigits",
				argDigits,
				MAX_DIGITS );
		}

		if( argPrecis < 0 ) {
			throw new CFLibArgumentUnderflowException( fieldOrClassName,
				S_ProcName,
				3,
				"argPrecis",
				argPrecis,
				0 );
		}
		else if( argPrecis > MAX_PRECISION ) {
			throw new CFLibArgumentOverflowException( fieldOrClassName,
				S_ProcName,
				3,
				"argPrecis",
				argPrecis,
				MAX_PRECISION );
		}

		if( argPrecis >= argDigits ) {
			throw new CFLibArgumentOverflowException( fieldOrClassName,
				S_ProcName,
				3,
				"argPrecis",
				argPrecis,
				argDigits - 1 );
		}

		BigDecimal minValue = getAbsoluteMinValue( fieldOrClassName, argDigits, argPrecis );
		if( value.compareTo( minValue ) < 0 ) {
			throw new CFLibArgumentUnderflowException( fieldOrClassName,
				S_ProcName,
				4,
				"value",
				value,
				minValue );
		}
		
		BigDecimal maxValue = getAbsoluteMaxValue( fieldOrClassName, argDigits, argPrecis );
		if( value.compareTo( maxValue ) > 0 ) {
			throw new CFLibArgumentOverflowException( fieldOrClassName,
				S_ProcName,
				4,
				"value",
				value,
				maxValue );
		}

		String coercedString = getNumberFormat( fieldOrClassName, argDigits, argPrecis ).format( value );
		
		BigDecimal coercedValue = new BigDecimal( coercedString );
		
		return( coercedValue );
	}

	public static BigDecimal parse( String fieldOrClassName, int argDigits, int argPrecis, String value ) {
		final String S_ProcName = "parse";

		if( ( fieldOrClassName == null ) || ( fieldOrClassName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibBigDecimalUtil.class,
				S_ProcName,
				1,
				"fieldOrClassName" );
		}

		if( ( value == null ) || ( value.length() <= 0 ) ) {
			return( null );
		}
		
		if( argDigits < 1 ) {
			throw new CFLibArgumentUnderflowException( fieldOrClassName,
				S_ProcName,
				2,
				"argDigits",
				argDigits,
				1 );
		}
		else if( argDigits > MAX_DIGITS ) {
			throw new CFLibArgumentOverflowException( fieldOrClassName,
				S_ProcName,
				2,
				"argDigits",
				argDigits,
				MAX_DIGITS );
		}

		if( argPrecis < 0 ) {
			throw new CFLibArgumentUnderflowException( fieldOrClassName,
				S_ProcName,
				3,
				"argPrecis",
				argPrecis,
				0 );
		}
		else if( argPrecis > MAX_PRECISION ) {
			throw new CFLibArgumentOverflowException( fieldOrClassName,
				S_ProcName,
				3,
				"argPrecis",
				argPrecis,
				MAX_PRECISION );
		}

		if( argPrecis >= argDigits ) {
			throw new CFLibArgumentOverflowException( fieldOrClassName,
				S_ProcName,
				3,
				"argPrecis",
				argPrecis,
				argDigits - 1 );
		}
		
		BigDecimal rawValue = new BigDecimal( value );
		BigDecimal minValue = getAbsoluteMinValue( fieldOrClassName, argDigits, argPrecis );
		BigDecimal maxValue = getAbsoluteMaxValue( fieldOrClassName, argDigits, argPrecis );

		if( rawValue.compareTo( minValue ) < 0 ) {
			throw new CFLibArgumentUnderflowException( fieldOrClassName,
				S_ProcName,
				4,
				"value",
				rawValue,
				minValue );
		}
		
		if( rawValue.compareTo( maxValue ) > 0 ) {
			throw new CFLibArgumentOverflowException( fieldOrClassName,
				S_ProcName,
				4,
				"value",
				rawValue,
				maxValue );
		}

		String coercedString = getNumberFormat( fieldOrClassName, argDigits, argPrecis ).format( rawValue );
		
		BigDecimal coercedValue = new BigDecimal( coercedString );
		
		return( coercedValue );
	}

	public static String format( String fieldOrClassName, int argDigits, int argPrecis, BigDecimal value ) {
		final String S_ProcName = "format";

		if( ( fieldOrClassName == null ) || ( fieldOrClassName.length() <= 0 ) ) {
			throw new CFLibNullArgumentException( CFLibBigDecimalUtil.class,
				S_ProcName,
				1,
				"fieldOrClassName" );
		}

		if( value == null ) {
			throw new CFLibNullArgumentException( fieldOrClassName,
				S_ProcName,
				4,
				"value" );
		}
		
		if( argDigits < 1 ) {
			throw new CFLibArgumentUnderflowException( fieldOrClassName,
				S_ProcName,
				2,
				"argDigits",
				argDigits,
				1 );
		}
		else if( argDigits > MAX_DIGITS ) {
			throw new CFLibArgumentOverflowException( fieldOrClassName,
				S_ProcName,
				2,
				"argDigits",
				argDigits,
				MAX_DIGITS );
		}

		if( argPrecis < 0 ) {
			throw new CFLibArgumentUnderflowException( fieldOrClassName,
				S_ProcName,
				3,
				"argPrecis",
				argPrecis,
				0 );
		}
		else if( argPrecis > MAX_PRECISION ) {
			throw new CFLibArgumentOverflowException( fieldOrClassName,
				S_ProcName,
				3,
				"argPrecis",
				argPrecis,
				MAX_PRECISION );
		}

		if( argPrecis >= argDigits ) {
			throw new CFLibArgumentOverflowException( fieldOrClassName,
				S_ProcName,
				3,
				"argPrecis",
				argPrecis,
				argDigits - 1 );
		}

		BigDecimal minValue = getAbsoluteMinValue( fieldOrClassName, argDigits, argPrecis );
		if( value.compareTo( minValue ) < 0 ) {
			throw new CFLibArgumentUnderflowException( fieldOrClassName,
				S_ProcName,
				4,
				"value",
				value,
				minValue );
		}
		
		BigDecimal maxValue = getAbsoluteMaxValue( fieldOrClassName, argDigits, argPrecis );
		if( value.compareTo( maxValue ) > 0 ) {
			throw new CFLibArgumentOverflowException( fieldOrClassName,
				S_ProcName,
				4,
				"value",
				value,
				maxValue );
		}

		String coercedString = getNumberFormat( fieldOrClassName, argDigits, argPrecis ).format( value );
		
		return( coercedString );
	}
}
