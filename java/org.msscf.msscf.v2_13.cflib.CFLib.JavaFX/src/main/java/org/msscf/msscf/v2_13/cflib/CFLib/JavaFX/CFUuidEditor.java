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

import java.util.*;
import javafx.geometry.Pos;

import org.msscf.msscf.v2_13.cflib.CFLib.*;

public class CFUuidEditor
extends CFTextField
{
	protected UUID value = null;

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
	
	public CFUuidEditor() {
		super();
		setAlignment( Pos.CENTER_LEFT );
		setMinWidth( 200 );
		setPrefWidth( 300 );
		setMaxWidth( 370 );
		setMinHeight( 25 );
		setMaxHeight( 25 );
		setPrefHeight( 25 );
	}
	
	public void setUuidValue( UUID val ) {
		value = val;
		String str;
		if( value != null ) {
			str = value.toString();
		}
		else {
			str = "";
		}
		setText( str );
	}
	
	public UUID getUuidValue() {
		final String S_ProcName = "getUuidValue";
		String str = getText();
		if( ( str == null ) || ( str.length() <= 0 ) ) {
			value = null;
		}
		else {
			try {
				UUID val = UUID.fromString( str );
				if( val == null ) {
					throw new CFLibInvalidArgumentException( fieldName,
							S_ProcName,
							0,
							"text",
							getText() );
				}
				value = val;
			}
			catch( Exception e ) {
				throw new CFLibInvalidArgumentException( fieldName,
						S_ProcName,
						0,
						"text",
						getText() );
			}
		}
		return( value );
	}
}
