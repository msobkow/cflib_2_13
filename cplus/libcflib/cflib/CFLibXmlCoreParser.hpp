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
#include <string>
#include <tuple>
#include <vector>

#include <xercesc/validators/common/Grammar.hpp>
#include <xercesc/framework/XMLGrammarPool.hpp>
#include <xercesc/framework/XMLGrammarPoolImpl.hpp>
#include <xercesc/framework/XMLGrammarDescription.hpp>
#include <xercesc/sax/Locator.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/Xerces_autoconf_config.hpp>
#include <xercesc/util/XMLString.hpp>

#include <cflib/CFLib.hpp>
#include <cflib/ICFLibMessageLog.hpp>
#include <cflib/CFLibXmlUtil.hpp>
#include <cflib/CFLibXmlCoreContext.hpp>
#include <cflib/ICFLibXmlCoreContextFactory.hpp>

namespace cflib {

	class CFLibXmlCoreParser
	: public xercesc::DefaultHandler,
	  public ICFLibXmlCoreContextFactory
	{

	public:
		static const bool DEFAULT_XINCLUDE;
		static const bool DEFAULT_SECURE_PROCESSING;

	private:
		ICFLibMessageLog* log;
		CFLibXmlCoreElementHandler* rootElementHandler;
		std::vector<CFLibXmlCoreContext*>* contextStack;
		ICFLibXmlCoreContextFactory* xmlCoreContextFactory;
		static xercesc::XMLGrammarPoolImpl* grammarPool;
		xercesc::Locator* docLocator;

	public:

		static const std::string CLASS_NAME;

		static bool isInitialized();
		static void init();
		static void release();

		CFLibXmlCoreParser();
		CFLibXmlCoreParser( ICFLibMessageLog* jlog );
		virtual ~CFLibXmlCoreParser();

		static xercesc::XMLGrammarPool* getGrammarPool();
	
		static xercesc::Grammar* addToGrammarPool( const std::string& name, xercesc::Grammar* grammar );

		virtual const xercesc::Locator* getDocumentLocator() const;
		virtual void setDocumentLocator( xercesc::Locator* newLocator );

		virtual ICFLibMessageLog* getLog() const;
		virtual void setLog( ICFLibMessageLog* jlog );

		CFLibXmlCoreElementHandler* getRootElementHandler();

	protected:
		void setRootElementHandler( CFLibXmlCoreElementHandler* handler );

	public:
		std::string getLocationInfo();

		CFLibXmlCoreContext* getCurContext();

		ICFLibXmlCoreContextFactory* getXmlCoreContextFactory();

		void setXmlCoreContextFactory( ICFLibXmlCoreContextFactory* factory );

		virtual CFLibXmlCoreContext* newXmlCoreContext(
			CFLibXmlCoreContext* src,
	        const XMLCh* const qName,
			CFLibXmlCoreElementHandler* handler ) const;

		virtual CFLibXmlCoreContext* newXmlCoreContext(
			CFLibXmlCoreParser* coreParser,
			ICFLibMessageLog* jlog,
			CFLibXmlCoreElementHandler* handler ) const;
	
		virtual void clearElementText();
		virtual std::string getElementText();

	protected:
		std::string formatMessage( const xercesc::SAXParseException& ex );

	public:
		virtual void warning( const xercesc::SAXParseException& ex );
		virtual void error( const xercesc::SAXParseException& ex );
		virtual void fatalError( const xercesc::SAXParseException& ex );

		std::string getFormattedNearLocation();

	    virtual void startElement(
	        const XMLCh* const uri,
	        const XMLCh* const localname,
	        const XMLCh* const qname,
	        const xercesc::Attributes& attrs );

	    virtual void endElement (
			const XMLCh* const uri,
			const XMLCh* const localname,
			const XMLCh* const qname );

    	virtual void characters (
			const XMLCh* const chars,
			const XMLSize_t length );

	protected:
		std::string* appendLocatorInformation( std::string* buff );

		virtual void initParser();
	};
}
