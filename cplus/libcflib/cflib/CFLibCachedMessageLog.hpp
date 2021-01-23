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

	class CFLibCachedMessageLog : public virtual ICFLibMessageLog {
	
	private:
		std::string cacheContents;
		int ndnt = 1;

	public:

		/**
		 *	Default constructor.
		 */
		CFLibCachedMessageLog();

		/**
		 *	Destructor
		 */
		virtual ~CFLibCachedMessageLog();

		/**
		 *	Clear the cache.
		 *	<p>
		 *	Messages are appended to the cache buffer , not logged
		 *	to a file.  After collecting messages with a cache log,
		 *	you can use getCacheContents() to retrieve the messages
		 *	that have been added to the cache buffer since the last
		 *	time clearCache() was invoked..
		 */
		virtual void clearCache();

		/**
		 *	Retrieve the contents of the cache.
		 *	Each message logged is newline-terminated as if it were to
		 *	be immediately written to the log.
		 */
		virtual const std::string& getCacheContents() const;

		/**
		 *	Get the current log indent level.
		 */
		virtual int getMessageLogIndent() const;

		/**
		 *	Decrease the indent of the logged messages another level.
		 *	<p>
		 *	The cached message log enforces a minimum indent of 1.
		 */
		virtual void dedent();

		/**
		 *	Indent the logging messages another level.
		 */
		virtual void indent();

		/**
		 *	Log a message to the cache.
		 *	<p>
		 *	If msg is not newline-terminated, one will be added before
		 *	appending it to the cache buffer.  No timestamp information
		 *	is inserted.
		 */
		virtual void message( const std::string& msg );

		/**
		 *	Open the specified file for logging.
		 *	<p>
		 *	This dummy function does nothing with the file name.
		 *	Cached message logs don't write directly to files.
		 */
		virtual void openLogFile( const std::string& fileName );

		/**
		 *	Close the log file.
		 *	<p>
		 *	Does absolutely nothing.  Cached message logs don't write
		 *	directlty to files.
		 */
		virtual void closeLogFile();
	};
}
