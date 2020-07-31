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

import java.util.Calendar;
import javafx.geometry.Pos;

import com.msscftech.msscf.cflib.CFLib.*;

public class CFTZDateEditor
extends CFTextField
{
	public final static Calendar MIN_VALUE = CFLib.getUTCGregorianCalendar( 0, 0, 0, 0, 0, 0 );
	public final static Calendar MAX_VALUE = CFLib.getUTCGregorianCalendar( 9999, 11, 31, 0, 0, 0 );

	protected Calendar curValue = null;

	protected Calendar minValue = MIN_VALUE;
	protected Calendar maxValue = MAX_VALUE;

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

	public CFTZDateEditor() {
		super();
		setAlignment( Pos.CENTER_LEFT );
		setMinWidth( 160 );
		setMaxWidth( 160 );
		setPrefWidth( 160 );
		setMinHeight( 25 );
		setMaxHeight( 25 );
		setPrefHeight( 25 );
	}

	public Calendar getMinValue() {
		return( minValue );
	}
	
	public void setMinValue( Calendar value ) {
		minValue = value;
	}
	
	public Calendar getMaxValue() {
		return( maxValue );
	}
	
	public void setMaxValue( Calendar value ) {
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
	
	public boolean isEditValid() {
		String text = getText();
		if( ( text == null ) || ( text.length() <= 0 ) ) {
			curValue = null;
			return( true );
		}
		curValue = null;
		curValue = CFLibXmlUtil.parseTZDate( fieldName, text );
		return( true );
	}

	public void setTZDateValue( Calendar value ) {
		curValue = value;
		if( curValue != null ) {
			String str = CFLibXmlUtil.formatTZDate( value );
			setText( str );
		}
		else {
			setText( "" );
		}
	}
	
	public Calendar getTZDateValue() {
		final String S_ProcName = "getTZDateValue";
		if( ! hasValue() ) {
			return( null );
		}
		else if( isEditValid() ) {
			return( curValue );
		}
		else {
			throw new CFLibInvalidArgumentException( fieldName,
					S_ProcName,
					0,
					"text",
					getText() );
		}
	}
}
