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

package org.msscf.msscf.v2_13.cflib.CFLib.JavaFX;

import javafx.scene.control.TextArea;

import org.msscf.msscf.v2_13.cflib.CFLib.*;

public class CFTextEditor
extends TextArea
{
	protected int maxLen = 0;

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

	public CFTextEditor() {
		super();
		setPrefWidth( 660 );
		setMinHeight( 50 );
		setPrefHeight( 50 );
	}
	
	public void setTextValue( String text ) {
		final String S_ProcName = "setTextValue";
		if( text == null ) {
			setText( "" );
			return;
		}
		if( text.length() > maxLen ) {
			throw new CFLibArgumentOverflowException( fieldName,
				S_ProcName,
				"Maximum length of text editor is " + maxLen );
		}
		setText( text );
	}
	
	public String getTextValue() {
		String text = getText();
		return( text );
	}
	
	public int getMaxLen() {
		return( maxLen );
	}

	public void setMaxLen( int value ) {
		final String S_ProcName = "setMaxLen";
		if( value < 1 ) {
			throw new CFLibArgumentUnderflowException( fieldName,
					S_ProcName,
					1,
					"value",
					value,
					1 );
		}
		maxLen = value;
		String curText = getText();
		if( ( curText != null ) && ( curText.length() > maxLen ) ) {
			curText = curText.substring( 0, maxLen );
			setText( curText );
		}
	}
}
