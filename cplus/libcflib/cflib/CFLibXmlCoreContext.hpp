#pragma once

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

#include <ctype.h>
#include <uuid/uuid.h>
#include <mpfr.h>
#include <time.h>

#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <chrono>
#include <ctime>
#include <list>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>

#include <cflib/CFLib.hpp>
#include <cflib/ICFLibAnyObj.hpp>
#include <cflib/ICFLibMessageLog.hpp>
#include <cflib/CFLibNullArgumentException.hpp>
#include <cflib/CFLibUnresolvedRelationException.hpp>
#include <cflib/CFLibUsageException.hpp>

namespace cflib {

	class CFLibXmlCoreParser;
	class CFLibXmlCoreElementHandler;

	class CFLibXmlCoreContext {

	private:

		CFLibXmlCoreContext* prevContext;
		std::string elementText;
		CFLibXmlCoreElementHandler* elementHandler;
		ICFLibMessageLog* log;
		CFLibXmlCoreParser* parser;
		std::string* elementQName;
		std::map<std::string,std::string> tagMap;
		ICFLibAnyObj* obj;

	public:
		static const std::string CLASS_NAME;

		CFLibXmlCoreContext(
			CFLibXmlCoreContext* src,
	        const XMLCh* const qName,
			CFLibXmlCoreElementHandler* handler );

		CFLibXmlCoreContext(
			CFLibXmlCoreParser* coreParser,
			ICFLibMessageLog* jlog,
			CFLibXmlCoreElementHandler* handler );

		virtual ~CFLibXmlCoreContext();

		CFLibXmlCoreContext* getPrevContext() const;

		bool hasNamedTag( const std::string& key ) const;
		const std::string& getNamedTag( const std::string& key ) const;
		void putNamedTag( const std::string& key, const std::string& tag );

		ICFLibAnyObj* getObj() const;
		void setObj( ICFLibAnyObj* value );

		CFLibXmlCoreParser* getParser();

	protected:
		void setParser( CFLibXmlCoreParser* coreParser );

	public:
		ICFLibMessageLog* getLog() const;
		void setLog( ICFLibMessageLog* jlog );

		void clearElementText();
		std::string getElementText() const;
		void appendElementText( const XMLCh* chars, std::string::size_type length );
	
		CFLibXmlCoreElementHandler* getElementHandler() const;

	protected:
		void setElementHandler( CFLibXmlCoreElementHandler* handler );

	public:
		void setQNameElementHandler( const XMLCh* const qName, CFLibXmlCoreElementHandler* handler );
	};
}
