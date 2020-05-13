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

#include <fstream>
#include <iostream>
#include <cflib/CFLibXmlCoreSaxParser.hpp>
#include <cflib/ICFLibPublic.hpp>
#include <xercesc/framework/MemoryManager.hpp>
#include <xercesc/sax/Locator.hpp>

namespace cflib {

	const std::string CFLibXmlCoreSaxParser::CLASS_NAME( "CFLibXmlCoreSaxParser" );
	const std::string CFLibXmlCoreSaxParser::S_SaxXmlReaderMustBeInitialized( "XmlReader must be initialized first" );

	CFLibXmlCoreSaxParser::CFLibXmlCoreSaxParser()
	: CFLibXmlCoreParser()
	{
		static const std::string S_ProcName( "construct-default" );
		if( ! CFLib::isInitialized() ) {
			throw CFLibUsageException( CLASS_NAME,
				S_ProcName,
				CFLib::S_MsgInitMustBeCalledFirst );
		}
		saxXmlReader = NULL;
		memBufInputSource = NULL;
	}

	CFLibXmlCoreSaxParser::CFLibXmlCoreSaxParser( ICFLibMessageLog* jLogger )
	: CFLibXmlCoreParser( jLogger )
	{
		static const std::string S_ProcName( "construct-log" );
		if( ! CFLib::isInitialized() ) {
			throw CFLibUsageException( CLASS_NAME,
				S_ProcName,
				CFLib::S_MsgInitMustBeCalledFirst );
		}
		saxXmlReader = NULL;
		memBufInputSource = NULL;
	}

	CFLibXmlCoreSaxParser::~CFLibXmlCoreSaxParser() {
		if( saxXmlReader != NULL ) {
			delete saxXmlReader;
			saxXmlReader = NULL;
		}
		if( memBufInputSource != NULL ) {
			delete memBufInputSource;
			memBufInputSource = NULL;
		}
	}

	void CFLibXmlCoreSaxParser::initParser() {
		static const std::string S_ProcName( "initParser" );
		static const char* S_GrammarPoolPropertyName = "http://apache.org/xml/properties/internal/grammar-pool";
		static XMLCh* xchGrammarPoolPropertyName = NULL;
		if( xchGrammarPoolPropertyName == NULL ) {
			std::string::size_type len = strlen( S_GrammarPoolPropertyName );
			xchGrammarPoolPropertyName = new XMLCh[len+1];
			for( std::string::size_type i = 0; i < len; i++ ) {
				xchGrammarPoolPropertyName[i] = (XMLCh)( S_GrammarPoolPropertyName[i] );
			}
			xchGrammarPoolPropertyName[len] = 0;
		}
		if( saxXmlReader != NULL ) {
			return;
		}
		CFLibXmlCoreParser::initParser();
		xercesc::SAX2XMLReader* xmlReader = xercesc::XMLReaderFactory::createXMLReader();
		xmlReader->setFeature( xercesc::XMLUni::fgSAX2CoreValidation, true );
		xmlReader->setFeature( xercesc::XMLUni::fgSAX2CoreNameSpaces, true );
		xmlReader->setFeature( xercesc::XMLUni::fgXercesSchema, true );
		// MSS TODO WORKING BLOWS CHUNKS xmlReader->setProperty( xercesc::XMLString::replicate( xchGrammarPoolPropertyName ), CFLibXmlCoreParser::getGrammarPool() );
		xmlReader->setFeature( xercesc::XMLUni::fgXercesUseCachedGrammarInParse, true );
		xmlReader->setContentHandler( this );
		xmlReader->setErrorHandler( this );
		saxXmlReader = xmlReader;
	}

	xercesc::Grammar* CFLibXmlCoreSaxParser::loadGrammar( const std::string& xsdFileName ) {
		static const std::string S_ProcName( "loadGrammar" );
		static const std::string S_MsgInitParserMustBeCalledFirst( "initParser() must be called first" );
		if( ! CFLib::isInitialized() ) {
			throw CFLibUsageException( CLASS_NAME,
				S_ProcName,
				CFLib::S_MsgInitMustBeCalledFirst );
		}
		if( saxXmlReader == NULL ) {
			throw CFLibUsageException( CLASS_NAME,
				S_ProcName,
				S_MsgInitParserMustBeCalledFirst );
		}
		xercesc::Grammar* grammar = saxXmlReader->loadGrammar( xsdFileName.data(), xercesc::Grammar::GrammarType::SchemaGrammarType, true );
		return( grammar );
	}

	/**
	 *	Parse the specified URI
	 *
	 *	@param	uri - The URI for the document to parse.
	 */
	void CFLibXmlCoreSaxParser::parse( const char* systemid ) {
		static const std::string S_ProcName( "parse" );
		static const std::string S_ArgSystemId( "systemid" );
		CFLIB_EXCEPTION_DECLINFO
		if( ( systemid == NULL ) || ( *systemid == 0 ) ) {
			throw CFLibEmptyArgumentException( CLASS_NAME,
				S_ProcName,
				1,
				S_ArgSystemId );
		}
		if( saxXmlReader == NULL ) {
			throw CFLibUsageException( CLASS_NAME,
				S_ProcName,
				S_SaxXmlReaderMustBeInitialized );
		}

		std::ifstream input( systemid );
		if( ! input.good() ) {
			static const std::string S_CouldNotAccess( "Could not access file " );
			static const std::string S_ForReading( " for reading" );
			std::string Msg( S_CouldNotAccess );
			Msg.append( systemid );
			Msg.append( S_ForReading );
			throw CFLibInvalidArgumentException( CLASS_NAME, S_ProcName, Msg );
		}

		input.seekg( 0, std::ios::end );
		size_t sz = input.tellg();
		std::string buff( sz, ' ' );		
		input.seekg( 0 );
		input.read( &buff[0], sz );
		input.close();
		if( memBufInputSource != NULL ) {
			delete memBufInputSource;
			memBufInputSource = NULL;
		}
		std::string::size_type len = buff.length();
		XMLByte *xmlbuff = new XMLByte[len+1];
		for( std::string::size_type i = 0; i < len; i++ ) {
			xmlbuff[i] = buff.at( i );
		}
		xmlbuff[len] = 0;
		memBufInputSource = new CFLibXmlCoreLineCountMemBufInputSource( this, xmlbuff, len, systemid, false, xercesc::XMLPlatformUtils::fgMemoryManager );
		try {
			saxXmlReader->parse( *memBufInputSource );
		}
		CFLIB_EXCEPTION_CATCH_FALLTHROUGH

		delete memBufInputSource;
		memBufInputSource = NULL;
		delete[] xmlbuff;
		xmlbuff = NULL;

		CFLIB_EXCEPTION_RETHROW_SAXEXCEPTION
	}

	/**
	 *	Parse the specified string contents.
	 *	<p>
	 *	The string passed to this method is typically
	 *	a request or response XML document to be processed
	 *	by an appropriate parser and applied to a storage
	 *	server layer.
	 *
	 *	@param	str The string contents to be parsed.
	 */
	void CFLibXmlCoreSaxParser::parseStringContents( const std::string& bufname, const std::string& str ) {
		const static std::string S_ProcName( "parseStringContents" );
		CFLIB_EXCEPTION_DECLINFO
		if( saxXmlReader == NULL ) {
			throw CFLibUsageException( CLASS_NAME,
				S_ProcName,
				S_SaxXmlReaderMustBeInitialized );
		}
		if( memBufInputSource != NULL ) {
			delete memBufInputSource;
			memBufInputSource = NULL;
		}
		std::string::size_type len = str.length();
		XMLByte *xmlbuff = new XMLByte[len+1];
		for( std::string::size_type i = 0; i < len; i++ ) {
			xmlbuff[i] = str[i];
		}
		xmlbuff[len] = 0;
		memBufInputSource = new CFLibXmlCoreLineCountMemBufInputSource( this, xmlbuff, len, bufname.c_str(), false, xercesc::XMLPlatformUtils::fgMemoryManager );
		try {
			saxXmlReader->parse( *memBufInputSource );
		}
		CFLIB_EXCEPTION_CATCH_FALLTHROUGH

		delete memBufInputSource;
		memBufInputSource = NULL;
		delete[] xmlbuff;
		xmlbuff = NULL;

		CFLIB_EXCEPTION_RETHROW_SAXEXCEPTION
	}

	/**
	 *	Parse the specified InputSource.
	 *	<p>
	 *	The InputSource passed to this method is typically
	 *	a piece of glue tying together some other objects output
	 *	as the input for a parse.
	 *
	 *	@param	src The InputSource contents to be parsed.
	 */
	void CFLibXmlCoreSaxParser::parse( const xercesc::InputSource& src ) {
		const static std::string S_ProcName( "parseStringContents" );
		if( saxXmlReader == NULL ) {
			throw CFLibUsageException( CLASS_NAME,
				S_ProcName,
				S_SaxXmlReaderMustBeInitialized );
		}
		saxXmlReader->parse( src );
	}
}
