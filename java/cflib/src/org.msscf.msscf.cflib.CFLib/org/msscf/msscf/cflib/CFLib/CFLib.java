/*
 *  MSS Code Factory CFLib 2.13
 *
 *	Copyright 2020 Mark Stephen Sobkow
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
 *	Please contact Mark Stephen Sobkow at msobkow@sasktel.net for commercial licensing.
 */

package org.msscf.msscf.cflib.CFLib;

import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.TimeZone;

import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.DataLine;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.UnsupportedAudioFileException;

/**
 *	The performance of exception handling in a high-volume Java system cannot
 *	be underestimated.  Anything you can do to speed up exception
 *	instantiation and initialization will dramatically improve the
 *	performance of the system under real life workloads, where users
 *	do input bad data.
 *	<p>
 *	The exception factory model eliminates the resolution of NLS translations
 *	of key system implementation error conditions using a plug-in/registry
 *	model instead of tolerating the resource load overhead of the default
 *	Java NLS string resource approach.
 */
public class CFLib {
	public final static String LinkName = "CFLib";
	public final static String LinkVersion = "2.13.11193";

	public final static TimeZone UTC_TIMEZONE = TimeZone.getTimeZone( "+0000" );

	public static void beep() {
		Clip clip = null;
		// The audio is courtesy of a whole whack of articles from stackoverflow.com, each of which got me one line closer to working
		try {
			InputStream resource = CFLib.class.getResourceAsStream("/org/msscf/msscf/cflib/CFLib/sounds/alert.wav");
			if( resource != null ) {
				AudioInputStream audioInputStream = AudioSystem.getAudioInputStream( new BufferedInputStream( resource ) );
				DataLine.Info info = new DataLine.Info( Clip.class, audioInputStream.getFormat() );
				clip = (Clip)AudioSystem.getLine( info );
				clip.open( audioInputStream );
				clip.start();
				clip.drain();
			}
		} catch (LineUnavailableException e) {
		} catch (UnsupportedAudioFileException e) {
		} catch (IOException e) {
		} catch (NullPointerException e) {
		} catch (IllegalArgumentException e) {
		}
	}

	public static Calendar getUTCGregorianCalendar(
		int year,
		int month,
		int day,
		int hour,
		int minute,
		int second )
	{
		Calendar cal = new GregorianCalendar( UTC_TIMEZONE );
		cal.clear();
		cal.set( year, month, day, hour, minute, second );
        cal.getTimeInMillis(); // Force calendar resync based on input values
		return( cal );
	}
	
	public String getLinkName() {
		return( LinkName );
	}

	public String getLinkVersion() {
		return( LinkVersion );
	}
}
