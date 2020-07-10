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

package org.msscf.msscf.cflib.CFLib.JavaFX;

import java.io.InputStream;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.control.Button;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;

import org.msscf.msscf.cflib.CFLib.*;

public class CFBoolEditor
extends Button
{
	public final static String FALSE_ICON_RESOURCE = "/org/msscf/msscf/cflib/CFLib/JavaFX/images/BoolFalse.gif";
	public final static String TRUE_ICON_RESOURCE = "/org/msscf/msscf/cflib/CFLib/JavaFX/images/BoolTrue.gif";
	public final static String NULL_ICON_RESOURCE = "/org/msscf/msscf/cflib/CFLib/JavaFX/images/BoolNull.gif";
	public final static Boolean S_FALSE = Boolean.valueOf( false );
	public final static Boolean S_TRUE = Boolean.valueOf( true );
	
	protected Boolean value = S_FALSE;
	protected boolean isNullable = false;

	protected Image falseImage = null;
	protected Image trueImage = null;
	protected Image nullImage = null;

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
	
	public Image getFalseImage() {
		final String S_ProcName="getFalseImage";
		if( falseImage == null ) {
			InputStream stream = CFBoolEditor.class.getResourceAsStream( FALSE_ICON_RESOURCE );
			if( stream == null ) {
				throw new CFLibNullArgumentException( getClass(),
						S_ProcName,
						0,
						"Resource " + FALSE_ICON_RESOURCE );
			}
			falseImage = new Image( stream );
		}
		return( falseImage );
	}

	public Image getTrueImage() {
		final String S_ProcName="getTrueImage";
		if( trueImage == null ) {
			InputStream stream = CFBoolEditor.class.getResourceAsStream( TRUE_ICON_RESOURCE );
			if( stream == null ) {
				throw new CFLibNullArgumentException( getClass(),
						S_ProcName,
						0,
						"Resource " + TRUE_ICON_RESOURCE );
			}
			trueImage = new Image( stream );
		}
		return( trueImage );
	}

	public Image getNullImage() {
		final String S_ProcName="getNullImage";
		if( nullImage == null ) {
			InputStream stream = CFBoolEditor.class.getResourceAsStream( NULL_ICON_RESOURCE );
			if( stream == null ) {
				throw new CFLibNullArgumentException( getClass(),
						S_ProcName,
						0,
						"Resource " + NULL_ICON_RESOURCE );
			}
			nullImage = new Image( stream );
		}
		return( nullImage );
	}
	
	public CFBoolEditor() {
		super();
		value = S_FALSE;
		setGraphic( new ImageView( getFalseImage() ) );
		setMinWidth( 25 );
		setMaxWidth( 25 );
		setPrefWidth( 25 );
		setMinHeight( 25 );
		setMaxHeight( 25 );
		setPrefHeight( 25 );
		setOnAction( new EventHandler<ActionEvent>() {
			@Override public void handle( ActionEvent e ) {
				if( value == null ) {
					if( isNullable == false ) {
						value = S_FALSE;
					}
				}
				if( value == null ) {
					value = S_FALSE;
					setGraphic( new ImageView( getFalseImage() ) );
				}
				else if( value.booleanValue() == false ) {
					value = S_TRUE;
					setGraphic( new ImageView( getTrueImage() ) );
				}
				else if( isNullable ) {
					value = null;
					setGraphic( new ImageView( getNullImage() ) );
				}
				else {
					value = S_FALSE;
					setGraphic( new ImageView( getFalseImage() ) );
				}
			}
		});
	}
	
	public boolean getIsNullable() {
		return( isNullable );
	}
	
	public void setIsNullable( boolean val ) {
		isNullable = val;
		if( ( ! isNullable ) && ( value == null ) ) {
			value = S_FALSE;
			setGraphic( new ImageView( getFalseImage() ) );
		}
	}
	
	public boolean hasValue() {
		return( true );
	}
	
	public void setBooleanValue( Boolean val ) {
		if( val == null ) {
			if( isNullable ) {
				value = null;
				setGraphic( new ImageView( getNullImage() ) );
			}
			else {
				value = S_FALSE;
				setGraphic( new ImageView( getFalseImage() ) );
			}
		}
		else if( val.booleanValue() == false ) {
			value = S_FALSE;
			setGraphic( new ImageView( getFalseImage() ) );
		}
		else {
			value = S_TRUE;
			setGraphic( new ImageView( getTrueImage() ) );
		}
	}

	public Boolean getBooleanValue() {
		if( ( ! isNullable ) && ( value == null ) ) {
			value = S_FALSE;
		}
		return( value );
	}
}
