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
 *	Contact Mark Stephen Sobkow at mark.sobkow@gmail.com for commercial licensing.
 */

package com.msscftech.msscf.cflib.CFLib.JavaFX;

import java.text.*;

import javafx.geometry.Pos;

import com.msscftech.msscf.cflib.CFLib.*;

public class CFFloatEditor
extends CFFormattedTextField
{
	protected static Format defaultFormat = null;

	protected Float minValue = -Float.MAX_VALUE;
	protected Float maxValue = Float.MAX_VALUE;

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

	public static Format getDefaultFormat() {
		if( defaultFormat == null ) {
			defaultFormat = new DecimalFormat( "######################################################################################################################################################################################################################################################################################################################0.0######################################################################################################################################################################################################################################################################################################################" );
		}
		return( defaultFormat );
	}

	public CFFloatEditor() {
		super();
		setAlignment( Pos.CENTER_RIGHT );
		setMinWidth( 160 );
		setPrefWidth( 160 );
		setMaxWidth( 300 );
		setMinHeight( 25 );
		setMaxHeight( 25 );
		setPrefHeight( 25 );
	}

	public Float getMinValue() {
		return( minValue );
	}

	public void setMinValue( Float value ) {
		final String S_ProcName = "setMinValue";
		if( value == null ) {
			throw new CFLibNullArgumentException( fieldName,
					S_ProcName,
					1,
					fieldName );
		}
		if( value.compareTo( -Float.MAX_VALUE ) < 0 ) {
			throw new CFLibArgumentUnderflowException( fieldName,
					S_ProcName,
					1,
					fieldName,
					value,
					-Float.MAX_VALUE );
		}
		minValue = value;
	}

	public Float getMaxValue() {
		return( maxValue );
	}

	public void setMaxValue( Float value ) {
		final String S_ProcName = "setMaxValue";
		if( value == null ) {
			throw new CFLibNullArgumentException( fieldName,
					S_ProcName,
					1,
					fieldName );
		}
		if( value.compareTo( Float.MAX_VALUE ) > 0 ) {
			throw new CFLibArgumentOverflowException( fieldName,
					S_ProcName,
					1,
					fieldName,
					value,
					Float.MAX_VALUE );
		}
		maxValue = value;
	}
	
	public void setFloatValue( Float value ) {
		if( value == null ) {
			setText( "" );
		}
		else {
			String text = getDefaultFormat().format( value );
			setText( text );
		}
	}
	
	public Float getFloatValue() {
		final String S_ProcName = "getFloatValue";
		Float retval;
		String text = getText();
		if( ( text == null ) || ( text.length() <= 0 ) ) {
			retval = null;
		}
		else {
			Float v = Float.valueOf( text );
			if( v == null ) {
				throw new CFLibInvalidArgumentException( fieldName,
						S_ProcName,
						0,
						"text",
						text );
			}
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
