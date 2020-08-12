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

package org.msscf.msscf.cflib.v2_13.CFLib;

import java.io.FileNotFoundException;
import java.io.PrintStream;

/**
 *	MessageLog implementations support indented application messaging.
 *	A given log implementation might also implement the ErrorLog interface,
 *	allowing it to display an interleaved mix of application and error
 *	messages.
 *	<p>
 *	All methods of the interface are expected to be synchronized.
 */
public interface ICFLibMessageLog {

	/**
	 *	Get an PrintStream that wraps this log
	 */
	public PrintStream getPrintStream();
	
	/**
	 *	Get the current log indent level.
	 */
	public int getMessageLogIndent();
	
	/**
	 *	Increase the log indentation.
	 */
	public void indent();
	
	/**
	 *	Decrease the log indentation.
	 */
	public void dedent();
	
	/**
	 *	Log an application message.
	 */
	public void message( String msg );
	
	/**
	 *	Open the specified file for logging
	 *
	 *	@param	fileName	The name of the file to open as a log.
	 */
	public void openLogFile( String fileName )
		throws FileNotFoundException;
	
	/**
	 *	Close the log file.
	 */
	public void closeLogFile();
}
