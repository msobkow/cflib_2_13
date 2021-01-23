#pragma once

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

#include <uuid/uuid.h>
#include <mpfr.h>

#include <array>
#include <cassert>
#include <cstddef>
#include <chrono>
#include <ctime>
#include <iostream>
#include <list>
#include <string>

#include <cflib/ICFLibMessageLog.hpp>

namespace cflib {

	class CFLibConsoleMessageLog : public virtual ICFLibMessageLog {
	
	private:
	
		/**
		 *	What is the current indent level for logging?
		 */
		int ndnt = 0;

	public:

		/**
		 *	Default constructor.
		 */
		CFLibConsoleMessageLog();

		/**
		 *	Destructor
		 */
		virtual ~CFLibConsoleMessageLog();

		/**
		 *	Get the current log indent level.
		 */
		virtual int getMessageLogIndent() const;

		/**
		 *	Indent the logging messages another level
		 */
		virtual void dedent();

		/**
		 *	Indent the logging messages another level
		 */
		virtual void indent();

		/**
		 *	Log a message to the console.
		 */
		virtual void message( const std::string& msg );

		/**
		 *	Open the specified file for logging.
		 *	<p>
		 *	Does nothing; console logs don't write to files.
		 */
		virtual void openLogFile( const std::string& fileName );

		/**
		 *	Close the log file.
		 *	<p>
		 *	Does nothing; console logs don't write to files.
		 */
		virtual void closeLogFile();
	};
}
