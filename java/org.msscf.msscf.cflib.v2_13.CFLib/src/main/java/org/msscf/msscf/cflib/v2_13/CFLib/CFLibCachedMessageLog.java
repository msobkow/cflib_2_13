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

import java.io.*;
import java.util.*;

public class CFLibCachedMessageLog
implements ICFLibMessageLog {

	private StringBuffer cacheContents = new StringBuffer();
	private int		   	indent = 0;
	
	/**
	 *	Default constructor.
	 */
	public CFLibCachedMessageLog() {
		indent = 0;
	}

	public void clearCache() {
		cacheContents.setLength( 0 );
	}

	public String getCacheContents() {
		return( cacheContents.toString() );
	}
	
	public int getMessageLogIndent() {
		return( indent );
	}
	
	public synchronized void dedent() {
		if( indent > 0 ) {
			indent --;
		}
		else {
			indent = 0;
		}
	}
	
	public synchronized void indent() {
		indent ++;
	}
	
	public synchronized void message( String msg ) {

		if( msg == null ) {
			return;
		}

		int			i;
		for( i = ( ( cacheContents.length() <= 0 ) ? 1 : 0 ); i < indent; i ++ ) {
			cacheContents.append( "\t" );
		}
		cacheContents.append( msg );
		if( ! msg.endsWith( "\n" ) ) {
			cacheContents.append( "\n" );
		}
	}

//	OLD API's that need to go away

	public PrintStream getPrintStream() {
		return( null );
	}

	public void openLogFile( String fileName )
		throws FileNotFoundException
	{
		// Do-nothing stub; cached message logs don't write to files
	}
	
	public void closeLogFile() {
		// Do-nothing stub; cached message logs don't write to files
	}
}
