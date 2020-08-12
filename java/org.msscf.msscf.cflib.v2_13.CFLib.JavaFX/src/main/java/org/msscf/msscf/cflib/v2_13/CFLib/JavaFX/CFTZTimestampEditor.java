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

import java.util.*;
import javafx.geometry.Pos;

import org.msscf.msscf.cflib.v2_13.CFLib.*;

public class CFTZTimestampEditor
extends CFTextField
{
	public final static Calendar MIN_VALUE = CFLib.getUTCGregorianCalendar( 0, 0, 0, 0, 0, 0 );
	public final static Calendar MAX_VALUE = CFLib.getUTCGregorianCalendar( 9999, 11, 31, 23, 59, 59 );

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

	public CFTZTimestampEditor() {
		super();
		setAlignment( Pos.CENTER_LEFT );
		setMinWidth( 200 );
		setMaxWidth( 200 );
		setPrefWidth( 200 );
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
	
	
	public boolean isEditValid() {
		String text = getText();
		if( ( text == null ) || ( text.length() <= 0 ) ) {
			curValue = null;
			return( true );
		}
		curValue = null;
		curValue = CFLibXmlUtil.parseTZTimestamp( fieldName, text );
		return( true );
	}

	public void setTZTimestampValue( Calendar value ) {
		curValue = value;
		if( curValue != null ) {
			String str = CFLibXmlUtil.formatTZTimestamp( value );
			setText( str );
		}
		else {
			setText( "" );
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

	public Calendar getTZTimestampValue() {
		final String S_ProcName = "getTZTimestampValue";
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
