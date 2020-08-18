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

package org.msscf.msscf.v2_13.cflib.CFLib.JavaFX;

import java.math.*;
import java.text.*;
import javafx.geometry.Pos;

import org.msscf.msscf.v2_13.cflib.CFLib.*;

public class CFUInt64Editor
extends CFFormattedTextField
{
	protected static Format defaultFormat = null;
	public final static BigDecimal MIN_VALUE = new BigDecimal( "0" );
	public final static BigDecimal MAX_VALUE = new BigDecimal( "18446744073709551616" );
	
	protected BigDecimal minValue = MIN_VALUE;
	protected BigDecimal maxValue = MAX_VALUE;

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

	public CFUInt64Editor() {
		super();
		setAlignment( Pos.CENTER_RIGHT );
		setMinWidth( 210 );
		setMaxWidth( 210 );
		setPrefWidth( 210 );
		setMinHeight( 25 );
		setMaxHeight( 25 );
		setPrefHeight( 25 );
	}

	public BigDecimal getMinValue() {
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
		if( value.compareTo( MIN_VALUE ) < 0 ) {
			throw new CFLibArgumentUnderflowException( fieldName,
					S_ProcName,
					1,
					"value",
					value,
					MIN_VALUE );
		}
		minValue = value;
	}

	public BigDecimal getMaxValue() {
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
		if( value.compareTo( MAX_VALUE ) > 0 ) {
			throw new CFLibArgumentOverflowException( fieldName,
					S_ProcName,
					1,
					"value",
					value,
					MAX_VALUE );
		}
		maxValue = value;
	}
	
	public void setUInt64Value( BigDecimal value ) {
		if( value == null ) {
			setText( "" );
		}
		else {
			String text = value.toPlainString();
			setText( text );
		}
	}
	
	public BigDecimal getUInt64Value() {
		final String S_ProcName = "getUInt64Value";
		BigDecimal retval;
		String text = getText();
		if( ( text == null ) || ( text.length() <= 0 ) ) {
			retval = null;
		}
		else {
			BigDecimal v = new BigDecimal( text );
			if( v.compareTo( minValue ) < 0 ) {
				throw new CFLibArgumentUnderflowException( fieldName,
						S_ProcName,
						1,
						fieldName,
						v,
						minValue );
			}
			if( v.compareTo( maxValue ) > 0 ) {
				throw new CFLibArgumentOverflowException( fieldName,
						S_ProcName,
						1,
						fieldName,
						v,
						maxValue );
			}
			retval = v;
		}
		return( retval );
	}
}
