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
#include <list>
#include <string>

#include <cflib/CFLibRuntimeException.hpp>
#include <cflib/CFLibArgumentException.hpp>

namespace cflib {

	/**
	 *	MessageLog implementations support indented application messaging.
	 *	A given log implementation might also implement the ErrorLog interface,
	 *	allowing it to display an interleaved mix of application and error
	 *	messages.
	 *	<p>
	 *	All methods of the interface are expected to be synchronized.
	 */
	class ICFLibMessageLog {
	
	public:

		ICFLibMessageLog();
		virtual ~ICFLibMessageLog();

		/**
		 *	Get the current log indent level.
		 */
		virtual int getMessageLogIndent() const = 0;

		/**
		 *	Increase the log indentation.
		 */
		virtual void indent() = 0;

		/**
		 *	Decrease the log indentation.
		 */
		virtual void dedent() = 0;

		/**
		 *	Log an application message.
		 */
		virtual void message( const std::string& msg ) = 0;

		/**
		 *	Open the specified file for logging
		 *
		 *	@param	fileName	The name of the file to open as a log.
		 */
		virtual void openLogFile( const std::string& fileName ) = 0;

		/**
		 *	Close the log file.
		 */
		virtual void closeLogFile() = 0;
	};
}
