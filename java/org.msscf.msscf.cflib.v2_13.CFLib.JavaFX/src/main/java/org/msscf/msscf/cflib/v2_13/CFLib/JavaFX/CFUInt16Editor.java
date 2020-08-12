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

package org.msscf.msscf.cflib.v2_13.CFLib.JavaFX;

import java.text.*;
import javafx.geometry.Pos;

import org.msscf.msscf.cflib.v2_13.CFLib.*;

public class CFUInt16Editor
extends CFFormattedTextField
{
	protected static Format defaultFormat = null;
	public final static int MIN_VALUE = 0;
	public final static int MAX_VALUE = 65536;
	protected int minValue = MIN_VALUE;
	protected int maxValue = MAX_VALUE;

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
			defaultFormat = new DecimalFormat( "####0" );
		}
		return( defaultFormat );
	}

	public CFUInt16Editor() {
		super();
		setAlignment( Pos.CENTER_RIGHT );
		setMinWidth( 60 );
		setMaxWidth( 60 );
		setPrefWidth( 60 );
		setMinHeight( 25 );
		setMaxHeight( 25 );
		setPrefHeight( 25 );
	}
	
	public int getMinValue() {
		return( minValue );
	}

	public void setMinValue( int value ) {
		if( value < MIN_VALUE ) {
			throw new CFLibArgumentUnderflowException( fieldName,
					"setMinValue",
					1,
					"value",
					value,
					MIN_VALUE );
		}
		minValue = value;
	}
	
	public int getMaxValue() {
		return( maxValue );
	}
	
	public void setMaxValue( int value ) {
		if( value > MAX_VALUE ) {
			throw new CFLibArgumentOverflowException( fieldName,
					"setMaxValue",
					1,
					"value",
					value,
					MAX_VALUE );
		}
		maxValue = value;
	}
	
	public boolean hasValue() {
		boolean retval;
		String text = getText();
		if( ( text == null ) || ( text.length() <= 0 ) ) {
			retval = false;
		}
		else {
			retval = true;
		}
		return( retval );
	}
	
	public void setUInt16Value( Integer value ) {
		if( value == null ) {
			setText( "" );
		}
		else {
			String text = getDefaultFormat().format( value );
			setText( text );
		}
	}
	
	public Integer getUInt16Value() {
		final String S_ProcName = "getUInt16Value";
		Integer retval;
		String text = getText();
		if( ( text == null ) || ( text.length() <= 0 ) ) {
			retval = null;
		}
		else {
			Integer v = Integer.valueOf( text );
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
