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

import java.io.BufferedInputStream;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.net.URISyntaxException;
import java.net.URL;
import java.util.Calendar;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.DataLine;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.UnsupportedAudioFileException;
import javafx.scene.control.TextArea;

import org.msscf.msscf.cflib.CFLib.*;

public class CFConsole
extends TextArea
{
	protected static boolean logExceptionsToSystem = true;
	protected static CFConsole sharedConsole = null;
	
	public CFConsole() {
		super();
		setPrefWidth( 660 );
		setMinHeight( 50 );
		setPrefHeight( 50 );
		setEditable( false );
		setWrapText( true );
		if( sharedConsole == null ) {
			sharedConsole = this;
		}
	}

	public static boolean getLogExceptionsToSystem() {
		return( logExceptionsToSystem );
	}
	
	public static void setLogExceptionsToSystem( boolean value ) {
		logExceptionsToSystem = value;
	}
	
	protected void logMessage( String msg ) {
		if( msg == null ) {
			return;
		}
		StringBuffer buff = new StringBuffer();
		Calendar cal = Calendar.getInstance();
		String stamp = String.format( "%1$tY-%1$tm-%1$td %1$tH:%1$tM:%1$tS.%1$tL ", cal );
		buff.append( stamp );
		buff.append( msg );
		if( ! msg.endsWith( "\n" ) ) {
			buff.append( "\n" );
		}
		appendText( buff.toString() );
		positionCaret( getLength() );
	}
	
	public static void message( String msg ) {
		if( sharedConsole != null ) {
			sharedConsole.logMessage( msg );
		}
	}
	
	protected void logFormException( String formName, String actionName, Throwable t ) {
		String useFormName = ( formName != null ) ? formName : "?";
		String useActionName = ( actionName != null ) ? actionName : "?";
		if( t == null ) {
			return;
		}
		String msg = t.getMessage();
		if( msg == null ) {
			msg = "";
		}
		String className = t.getClass().getName();
		int lastDot = className.lastIndexOf( '.' );
		String strippedClassName = className.substring( lastDot + 1 );
		StringBuffer buff = new StringBuffer();
		Calendar cal = Calendar.getInstance();
		String stamp = String.format( "%1$tY-%1$tm-%1$td %1$tH:%1$tM:%1$tS.%1$tL ", cal );
		buff.append( stamp );
		buff.append( useFormName + "." + useActionName + " caught " + strippedClassName + " - " + msg );
		buff.append( "\n" );
		String buffString = buff.toString();
		appendText( buffString );
		positionCaret( getLength() );
		CFLib.beep();
		if( logExceptionsToSystem ) {
			System.out.print( buffString );
			t.printStackTrace( System.out );
		}
	}

	public static void formException( String formName, String actionName, Throwable t ) {
		if( sharedConsole != null ) {
			sharedConsole.logFormException( formName, actionName, t );
		}
	}
}
