/*
 *  MSS Code Factory CFLib 2.13
 *
 *	Copyright 2020-2021 Mark Stephen Sobkow
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
 *	Please contact Mark Stephen Sobkow at mark.sobkow@gmail.com for commercial licensing.
 */

#include <iostream>
#include <iomanip>
#include <sstream>

#include <cflib/CFLib.hpp>
#include <cflib/ICFLibMessageLog.hpp>
#include <cflib/CFLibConsoleMessageLog.hpp>

namespace cflib {

	CFLibConsoleMessageLog::~CFLibConsoleMessageLog() {
	}

	/**
	 *	Default constructor.
	 */
	CFLibConsoleMessageLog::CFLibConsoleMessageLog() {
		ndnt = 0;
	}

	/**
	 *	Get the current log indent level.
	 */
	int CFLibConsoleMessageLog::getMessageLogIndent() const {
		return( ndnt );
	}

	/**
	 *	Indent the logging messages another level
	 */
	void CFLibConsoleMessageLog::dedent() {
		if( ndnt > 0 ) {
			ndnt --;
		}
		else {
			ndnt = 0;
		}
	}

	/**
	 *	Indent the logging messages another level
	 */
	void CFLibConsoleMessageLog::indent() {
		ndnt ++;
	}

	void CFLibConsoleMessageLog::message( const std::string& msg ) {

		const static std::string S_TAB( "\t" );
		const static std::string S_NEWLINE( "\n" );

		std::string buff;

		time_t systime;
		time( &systime );
		struct tm* tms = gmtime( &systime );
		char fmt[64] = { 0 };
		snprintf( &fmt[0], 64, "%04d-%02d-%02d %02d:%02d:%02d ",
			tms->tm_year + 1900, tms->tm_mon + 1, tms->tm_mday,
			tms->tm_hour, tms->tm_min, tms->tm_sec );
		buff.append( fmt );

		int i;
		for( i = 0; i < ndnt; i ++ ) {
			buff.append( S_TAB );
		}
		buff.append( msg );
		std::string::size_type msglen = msg.length();
		if( msglen > 0 ) {
			if( msg[ msglen - 1 ] != S_NEWLINE[ 0 ] ) {
				buff.append( S_NEWLINE );
			}
		}

		std::cout << buff;
	}

	void CFLibConsoleMessageLog::openLogFile( const std::string& fileName ) {
		// Stub function.  Console wrappers don't write to files.
	}

	void CFLibConsoleMessageLog::closeLogFile() {
		// Stub function.  Console wrappers don't write to files.
	}
}
