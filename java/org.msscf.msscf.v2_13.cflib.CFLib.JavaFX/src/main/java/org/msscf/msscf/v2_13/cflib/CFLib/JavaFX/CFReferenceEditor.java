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

import java.io.InputStream;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.AnchorPane;

import org.msscf.msscf.v2_13.cflib.CFLib.*;

public class CFReferenceEditor
extends AnchorPane
{
	public final static String PICK_ICON_RESOURCE = "/org.msscf.msscf.v2_13.cflib.CFLib/JavaFX/images/PickReference.gif";
	public final static String VIEW_ICON_RESOURCE = "/org.msscf.msscf.v2_13.cflib.CFLib/JavaFX/images/ViewReference.gif";
	protected ICFLibAnyObj referencedObject = null;
	protected TextField textFieldQualifiedName = null;
	protected Button buttonPickReference = null;
	protected Button buttonViewReference = null;
	protected boolean customDisable = false;
	
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

	public interface ICFReferenceCallback {
		void chose( org.msscf.msscf.v2_13.cflib.CFLib.ICFLibAnyObj value );
		void view( org.msscf.msscf.v2_13.cflib.CFLib.ICFLibAnyObj value );
	}
	
	protected ICFReferenceCallback callback = null;
	
	public CFReferenceEditor( ICFReferenceCallback argCallback ) {
		super();
		final String S_ProcName = "construct";
		if( argCallback == null ) {
			throw new CFLibNullArgumentException( fieldName,
				S_ProcName,
				1,
				"argCallback" );
		}
		callback = argCallback;
		referencedObject = null;

		setMinWidth( 300 );
		setPrefWidth( 400 );
		setMaxWidth( 800 );
		setMinHeight( 25 );
		setMaxHeight( 25 );
		setPrefHeight( 25 );
		
		textFieldQualifiedName = new TextField();
		textFieldQualifiedName.setMinHeight( 25 );
		textFieldQualifiedName.setMaxHeight( 25 );
		textFieldQualifiedName.setPrefHeight( 25 );
		textFieldQualifiedName.setEditable( false );

		buttonPickReference = new Button();
		buttonPickReference.setGraphic( new ImageView( getPickIcon() ) );
		buttonPickReference.setMinHeight( 25 );
		buttonPickReference.setMaxHeight( 25 );
		buttonPickReference.setPrefHeight( 25 );
		buttonPickReference.setMinWidth( 25 );
		buttonPickReference.setMaxWidth( 25 );
		buttonPickReference.setPrefWidth( 25 );
		buttonPickReference.setOnAction( new EventHandler<ActionEvent>() {
			@Override public void handle( ActionEvent e ) {
				if( callback != null ) {
					callback.chose( referencedObject );
				}
			}
		});

		buttonViewReference = new Button();
		buttonPickReference.setGraphic( new ImageView( getViewIcon() ) );
		buttonViewReference.setMinHeight( 25 );
		buttonViewReference.setMaxHeight( 25 );
		buttonViewReference.setPrefHeight( 25 );
		buttonViewReference.setMinWidth( 25 );
		buttonViewReference.setMaxWidth( 25 );
		buttonViewReference.setPrefWidth( 25 );
		buttonViewReference.setOnAction( new EventHandler<ActionEvent>() {
			@Override public void handle( ActionEvent e ) {
				if( callback != null ) {
					callback.view( referencedObject );
				}
			}
		});
		
		getChildren().addAll( textFieldQualifiedName, buttonPickReference, buttonViewReference );

		setLeftAnchor( textFieldQualifiedName, 0.0 );
		setRightAnchor( textFieldQualifiedName, 50.0 );
		setRightAnchor( buttonPickReference, 25.0 );
		setRightAnchor( buttonViewReference, 0.0 );
	}

	public ICFLibAnyObj getReferencedObject() {
		return( referencedObject );
	}
	
	public void setReferencedObject( ICFLibAnyObj value ) {
		referencedObject = value;
		TextField textField = getTextFieldQualifiedName();
		if( referencedObject != null ) {
			String qualifiedName = referencedObject.getObjQualifiedName();
			if( qualifiedName != null ) {
				textField.setText( qualifiedName );
			}
			else {
				textField.setText( "" );
			}
		}
		else {
			textField.setText( "" );
		}
		textField.selectEnd();
		textField.deselect();
	}
	
	public Image getPickIcon() {
		final String S_ProcName="getPickIcon";
		InputStream stream = CFReferenceEditor.class.getResourceAsStream( PICK_ICON_RESOURCE );
		if( stream == null ) {
			throw new CFLibNullArgumentException( getClass(),
					S_ProcName,
					0,
					"Resource " + PICK_ICON_RESOURCE );
		}
		Image icon = new Image( stream );
		return( icon );
	}
	
	public Image getViewIcon() {
		final String S_ProcName="getViewIcon";
		InputStream stream = CFReferenceEditor.class.getResourceAsStream( VIEW_ICON_RESOURCE );
		if( stream == null ) {
			throw new CFLibNullArgumentException( getClass(),
					S_ProcName,
					0,
					"Resource " + VIEW_ICON_RESOURCE );
		}
		Image icon = new Image( stream );
		return( icon );
	}

	public TextField getTextFieldQualifiedName() {
		return( textFieldQualifiedName );
	}

	public Button getButtonPickReference() {
		return( buttonPickReference );
	}

	public Button getButtonViewReference() {
		return( buttonViewReference );
	}
	
	public void setCustomDisable( boolean value ) {
		setDisable( false );
		customDisable = value;
		if( customDisable ) {
			buttonPickReference.setDisable( true );
			buttonViewReference.setDisable( false );
			textFieldQualifiedName.setDisable( true );
		}
		else {
			buttonPickReference.setDisable( false );
			buttonViewReference.setDisable( false );
			textFieldQualifiedName.setDisable( false );
		}
	}
	
	public boolean getCustomDisable() {
		return( customDisable );
	}
}
