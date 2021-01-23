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

import javafx.geometry.Pos;

import com.msscftech.msscf.cflib.CFLib.*;

public class CFTokenEditor
extends CFTextField
{
	protected int maxLen = 1;

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

	public CFTokenEditor() {
		super();
		setAlignment( Pos.CENTER_LEFT );
		setMinHeight( 25 );
		setMaxHeight( 25 );
		setPrefHeight( 25 );
	}
	
	public int getMaxLen() {
		return( maxLen );
	}

	public void setMaxLen( int value ) {
		final String S_ProcName = "setMaxLen";
		if( maxLen < 1 ) {
			throw new CFLibArgumentUnderflowException( fieldName,
					S_ProcName,
					1,
					"value",
					value,
					1 );
		}
		maxLen = value;
		if( maxLen > 58 ) {
			setMinWidth( 660 );
			setPrefWidth( 660 );
		}
		else if( maxLen > 0 ) {
			setMinWidth( ( maxLen + 2 ) * 11 );
			setMaxWidth( ( maxLen + 2 ) * 11 );
			setPrefWidth( ( maxLen + 2 ) * 11 );
		}
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
	
	public boolean isEditValid() {
		String str = getText();
		if( str == null ) {
			return( true );
		}
		
		int len = str.length();
		if( len > maxLen ) {
			return( false );
		}
		else {
			return( true );
		}
	}
	
	public void setTokenValue( String value ) {
		if( value != null ) {
			setText( value );
		}
		else {
			setText( "" );
		}
	}

	public String getTokenValue() {
		final String S_ProcName = "getTokenValue";
		String text = getText();
		if( text == null ) {
			return( null );
		}
		else if( text.length() > maxLen ) {
			throw new CFLibArgumentOverflowException( fieldName,
					S_ProcName,
					0,
					"MaxLen",
					text.length(),
					maxLen );
		}
		else {
			return( text );
		}
	}
}
