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

#include <iostream>
#include <iomanip>
#include <sstream>

#include <cflib/CFLib.hpp>
#include <cflib/ICFLibMessageLog.hpp>
#include <cflib/CFLibCachedMessageLog.hpp>

namespace cflib {

	CFLibCachedMessageLog::~CFLibCachedMessageLog() {
	}

	CFLibCachedMessageLog::CFLibCachedMessageLog() {
		ndnt = 1;
	}

	void CFLibCachedMessageLog::clearCache() {
		static const std::string S_Empty( "" );
		cacheContents = S_Empty;
	}

	const std::string& CFLibCachedMessageLog::getCacheContents() const {
		return( cacheContents );
	}

	int CFLibCachedMessageLog::getMessageLogIndent() const {
		return( ndnt );
	}

	void CFLibCachedMessageLog::dedent() {
		if( ndnt > 1 ) {
			ndnt --;
		}
		else {
			ndnt = 1;
		}
	}

	void CFLibCachedMessageLog::indent() {
		ndnt ++;
	}

	void CFLibCachedMessageLog::message( const std::string& msg ) {
		int i;
		for( i = (( cacheContents.empty() ) ? 1 : 0 ); i < ndnt; i ++ ) {
			cacheContents.push_back( '\t' );
		}
		cacheContents.append( msg );
		if( cacheContents.back() != '\n' ) {
			cacheContents.push_back( '\n' );
		}
	}

	void CFLibCachedMessageLog::openLogFile( const std::string& fileName ) {
		// Do-nothing stub; cached message logs don't write to files
	}

	void CFLibCachedMessageLog::closeLogFile() {
		// Do-nothing stub; cached message logs don't write to files
	}
}
