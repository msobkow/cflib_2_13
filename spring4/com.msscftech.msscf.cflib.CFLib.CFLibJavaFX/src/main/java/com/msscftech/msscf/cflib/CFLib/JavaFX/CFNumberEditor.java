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

package com.msscftech.msscf.cflib.CFLib.JavaFX;

import java.math.*;
import javafx.geometry.Pos;

import com.msscftech.msscf.cflib.CFLib.*;

public class CFNumberEditor
extends CFFormattedTextField
{
	protected int digits;
	protected int precis;
	protected BigDecimal minValue = null;
	protected BigDecimal maxValue = null;

	protected String fieldName = "?";
	
	public String getFieldName() {
		return( fieldName );
	}
	
	public void setFieldName( String value ) {
		if( ( value == null ) || ( value.length() <= 0 ) ) {
			fieldName = "?";
		}
		else {
			fieldName = value;
		}
	}

	public CFNumberEditor( int argDigits, int argPrecis ) {
		super();
		final String S_ProcName = "construct";
		setAlignment( Pos.CENTER_RIGHT );
		if( argDigits < 1 ) {
			throw new CFLibArgumentUnderflowException( fieldName,
					S_ProcName,
					1,
					"argDigits",
					argDigits,
					1 );
		}
		else if( argDigits > CFLibBigDecimalUtil.MAX_DIGITS ) {
			throw new CFLibArgumentOverflowException( fieldName,
				S_ProcName,
				1,
				"argDigits",
				argDigits,
				CFLibBigDecimalUtil.MAX_DIGITS );
		}
		if( argPrecis < 0 ) {
			throw new CFLibArgumentUnderflowException( fieldName,
				S_ProcName,
				1,
				"argPrecis",
				argPrecis,
				0 );
		}
		else if( argPrecis > CFLibBigDecimalUtil.MAX_PRECISION ) {
			throw new CFLibArgumentOverflowException( fieldName,
				S_ProcName,
				1,
				"argPrecis",
				argPrecis,
				CFLibBigDecimalUtil.MAX_PRECISION );
		}
		if( argPrecis >= argDigits ) {
			throw new CFLibArgumentOverflowException( fieldName,
				S_ProcName,
				1,
				"argPrecis",
				argPrecis,
				argDigits - 1 );
		}
		minValue = null;
		maxValue = null;
		digits = argDigits;
		precis = argPrecis;
		int width = ( argDigits + argPrecis + 2 ) * 10;
		if( width > 500 ) {
			width = 500;
		}
		setMinWidth( width );
		setMaxWidth( width );
		setPrefWidth( width );
		setMinHeight( 25 );
		setMaxHeight( 25 );
		setPrefHeight( 25 );
	}

	public int getDigits() {
		return( digits );
	}

	public void setDigits( int argDigits ) {
		final String S_ProcName = "setDigits";
		if( argDigits < 1 ) {
			throw new CFLibArgumentUnderflowException( fieldName,
					S_ProcName,
					1,
					"argDigits",
					argDigits,
					1 );
		}
		else if( argDigits > CFLibBigDecimalUtil.MAX_DIGITS ) {
			throw new CFLibArgumentOverflowException( fieldName,
				S_ProcName,
				1,
				"argDigits",
				argDigits,
				CFLibBigDecimalUtil.MAX_DIGITS );
		}
		digits = argDigits;
		minValue = null;
		maxValue = null;
	}
	
	public int getPrecision() {
		return( precis );
	}

	public void setPrecision( int argPrecis ) {
		final String S_ProcName = "setPrecision";
		if( argPrecis < 0 ) {
			throw new CFLibArgumentUnderflowException( fieldName,
				S_ProcName,
				1,
				"argPrecis",
				argPrecis,
				0 );
		}
		else if( argPrecis > CFLibBigDecimalUtil.MAX_PRECISION ) {
			throw new CFLibArgumentOverflowException( fieldName,
				S_ProcName,
				1,
				"argPrecis",
				argPrecis,
				CFLibBigDecimalUtil.MAX_PRECISION );
		}

		if( argPrecis >= digits ) {
			throw new CFLibArgumentOverflowException( fieldName,
				S_ProcName,
				1,
				"argPrecis",
				argPrecis,
				digits - 1 );
		}

		precis = argPrecis;
		minValue = null;
		maxValue = null;
	}

	public void setDigitsAndPrecision( int argDigits, int argPrecis ) {
		final String S_ProcName = "setDigitsAndPrecision";
		if( argDigits < 1 ) {
			throw new CFLibArgumentUnderflowException( fieldName,
					S_ProcName,
					1,
					"argDigits",
					argDigits,
					1 );
		}
		else if( argDigits > CFLibBigDecimalUtil.MAX_DIGITS ) {
			throw new CFLibArgumentOverflowException( fieldName,
				S_ProcName,
				1,
				"argDigits",
				argDigits,
				CFLibBigDecimalUtil.MAX_DIGITS );
		}
		if( argPrecis < 0 ) {
			throw new CFLibArgumentUnderflowException( fieldName,
				S_ProcName,
				1,
				"argPrecis",
				argPrecis,
				0 );
		}
		else if( argPrecis > CFLibBigDecimalUtil.MAX_PRECISION ) {
			throw new CFLibArgumentOverflowException( fieldName,
				S_ProcName,
				1,
				"argPrecis",
				argPrecis,
				CFLibBigDecimalUtil.MAX_PRECISION );
		}
		if( argPrecis >= argDigits ) {
			throw new CFLibArgumentOverflowException( fieldName,
				S_ProcName,
				1,
				"argPrecis",
				argPrecis,
				argDigits - 1 );
		}
		digits = argDigits;
		precis = argPrecis;
		
		if( minValue != null ) {
			BigDecimal newMinValue = CFLibBigDecimalUtil.getAbsoluteMinValue( getClass().getName(), argDigits, argPrecis );
			if( minValue.compareTo( newMinValue ) < 0 ) {
				minValue = newMinValue;
			}
		}
		
		if( maxValue != null ) {
			BigDecimal newMaxValue = CFLibBigDecimalUtil.getAbsoluteMaxValue( getClass().getName(), argDigits, argPrecis );
			if( maxValue.compareTo( newMaxValue ) > 0 ) {
				maxValue = newMaxValue;
			}
		}
		
		BigDecimal numberValue = getNumberValue();
		setNumberValue( numberValue );
	}

	public BigDecimal getMinValue() {
		if( minValue == null ) {
			minValue = CFLibBigDecimalUtil.getAbsoluteMinValue( fieldName, digits, precis );
		}
		return( minValue );
	}

	public void setMinValue( BigDecimal value ) {
		final String S_ProcName = "setMinValue";
		
		if( value == null ) {
			throw new CFLibNullArgumentException( fieldName,
				S_ProcName,
				1,
				"value" );
		}
		
		BigDecimal coerced = CFLibBigDecimalUtil.coerce( fieldName, digits, precis, value );

		minValue = coerced;
	}

	public BigDecimal getMaxValue() {
		if( maxValue == null ) {
			minValue = CFLibBigDecimalUtil.getAbsoluteMaxValue( fieldName, digits, precis );
		}
		return( maxValue );
	}

	public void setMaxValue( BigDecimal value ) {
		final String S_ProcName = "setMaxValue";
		
		if( value == null ) {
			throw new CFLibNullArgumentException( fieldName,
				S_ProcName,
				1,
				"value" );
		}
		
		BigDecimal coerced = CFLibBigDecimalUtil.coerce( fieldName, digits, precis, value );

		maxValue = coerced;
	}
	
	public void setNumberValue( BigDecimal value ) {
		if( value == null ) {
			setText( "" );
		}
		else {
			String formatted = CFLibBigDecimalUtil.format( fieldName, digits, precis, value );
			setText( formatted );
		}
	}

	public BigDecimal getNumberValue() {
		String text = getText();
		BigDecimal retval;
		if( ( text == null ) || ( text.length() <= 0 ) ) {
			retval = null;
		}
		else {
			retval = CFLibBigDecimalUtil.parse( fieldName, digits, precis, text );
		}
		return( retval );
	}
}
