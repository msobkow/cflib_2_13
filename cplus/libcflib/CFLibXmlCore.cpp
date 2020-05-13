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

#include <cflib/CFLibXmlCore.hpp>
#include <cflib/CFLibXmlCoreParser.hpp>

namespace cflib {

	const std::string CFLibXmlCore::CLASS_NAME( "CFLibXmlCore" );

	volatile bool CFLibXmlCore::initialized = false;

	CFLibXmlCore::CFLibXmlCore() {
	}

	CFLibXmlCore::~CFLibXmlCore() {
	}

	bool CFLibXmlCore::isInitialized() {
		return( initialized );
	}

	void CFLibXmlCore::init() {
		static const std::string S_ProcName( "init" );
		if( initialized ) {
			return;
		}
		try {
			if( ! CFLib::isInitialized() ) {
				throw CFLibUsageException( CLASS_NAME,
					S_ProcName,
					CFLib::S_MsgInitMustBeCalledFirst );
			}
			xercesc::XMLPlatformUtils::Initialize();
			initialized = true;
			CFLibXmlCoreParser::init();
		}
		catch( const xercesc::XMLException& ) {
			try {
				CFLibXmlCoreParser::release();
			}
			catch( ... ) {
			}
			initialized = false;
		}
	}

	void CFLibXmlCore::release() {
		if( ! initialized ) {
			return;
		}
		try {
			CFLibXmlCoreParser::release();
		}
		catch( ... ) {
		}
		try {
			xercesc::XMLPlatformUtils::Terminate();
			initialized = false;
		}
		catch( const xercesc::XMLException& ) {
			initialized = false;
		}
	}
}
