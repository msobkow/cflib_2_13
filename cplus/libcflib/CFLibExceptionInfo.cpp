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

#include <cflib/CFLib.hpp>
#include <cflib/CFLibExceptionInfo.hpp>

namespace cflib {

	const std::string CFLibExceptionInfo::S_Empty( "" );
	const std::string CFLibExceptionInfo::S_EXCEPTION( "Exception" );
	const std::string CFLibExceptionInfo::S_CaughtXercesException( "Caught xerces " );
	const std::string CFLibExceptionInfo::S_CaughtSystemException( "Caught system " );
	const std::string CFLibExceptionInfo::S_SAXNotRecognizedException( "SAXNotRecognizedException" );
	const std::string CFLibExceptionInfo::S_SAXNotSupportedException( "SAXNotSupportedException" );
	const std::string CFLibExceptionInfo::S_SAXParseException( "SAXParseException" );
	const std::string CFLibExceptionInfo::S_SAXException( "SAXException" );
	const std::string CFLibExceptionInfo::S_invalid_argument( "invalid_argument" );
	const std::string CFLibExceptionInfo::S_domain_error( "domain_error" );
	const std::string CFLibExceptionInfo::S_length_error( "length_error" );
	const std::string CFLibExceptionInfo::S_out_of_range( "out_of_range" );
	const std::string CFLibExceptionInfo::S_future_error( "future_error" );
	const std::string CFLibExceptionInfo::S_logic_error( "logic_error" );
	const std::string CFLibExceptionInfo::S_bad_optional_access( "bad_optional_access" );
	const std::string CFLibExceptionInfo::S_range_error( "range_error" );
	const std::string CFLibExceptionInfo::S_overflow_error( "overflow_error" );
	const std::string CFLibExceptionInfo::S_regex_error( "regex_error" );
	const std::string CFLibExceptionInfo::S_ios_base_failure( "ios_base_failure" );
	const std::string CFLibExceptionInfo::S_filesystem_error( "filesystem_error" );
	const std::string CFLibExceptionInfo::S_system_error( "system_error" );
	const std::string CFLibExceptionInfo::S_nonexistent_local_time( "nonexistent_local_time" );
	const std::string CFLibExceptionInfo::S_ambiguous_local_time( "ambiguous_local_time" );
	const std::string CFLibExceptionInfo::S_format_error( "format_error" );
	const std::string CFLibExceptionInfo::S_bad_typeid( "bad_typeid" );
	const std::string CFLibExceptionInfo::S_bad_any_cast( "bad_any_cast" );
	const std::string CFLibExceptionInfo::S_bad_cast( "bad_cast" );
	const std::string CFLibExceptionInfo::S_bad_weak_ptr( "bad_weak_ptr" );
	const std::string CFLibExceptionInfo::S_bad_function_call( "bad_function_call" );
	const std::string CFLibExceptionInfo::S_bad_array_new_length( "bad_array_new_length" );
	const std::string CFLibExceptionInfo::S_bad_alloc( "bad_alloc" );
	const std::string CFLibExceptionInfo::S_bad_exception( "bad_exception" );
	const std::string CFLibExceptionInfo::S_bad_variant_access( "bad_variant_access" );
	const std::string CFLibExceptionInfo::S_std_exception( "exception" );

	CFLibExceptionInfo::~CFLibExceptionInfo() {
	}

	CFLibExceptionInfo::CFLibExceptionInfo() {
		excFlags = CFLIB_EXCEPT_EMPTY;
		excCause = S_Empty;
		excExceptionName = S_Empty;
		excClassFieldName = S_Empty;
		excMethodName = S_Empty;
		excArgOffset = -1LL;
		excArgName = S_Empty;
		excArgValueString = S_Empty;
		excArgMinValueString = S_Empty;
		excArgMaxValueString = S_Empty;
		excMessageText = S_Empty;
	}

	void CFLibExceptionInfo::reset() {
		excFlags = CFLIB_EXCEPT_EMPTY;
		excCause = S_Empty;
		excExceptionName = S_Empty;
		excClassFieldName = S_Empty;
		excMethodName = S_Empty;
		excArgOffset = -1LL;
		excArgName = S_Empty;
		excArgValueString = S_Empty;
		excArgMinValueString = S_Empty;
		excArgMaxValueString = S_Empty;
	}

	CFLibExceptionInfo::CFLibExceptionInfo( const CFLibExceptionInfo& src ) {
		excFlags = src.getFlags();
		excCause = src.getCause();
		excExceptionName = src.getExceptionName();
		excClassFieldName = src.getClassFieldName();
		excMethodName = src.getMethodName();
		excArgOffset = src.getArgOffset();
		excArgName = src.getArgName();
		excArgValueString = src.getArgValueString();
		excArgMinValueString = src.getArgMinValueString();
		excArgMaxValueString = src.getArgMaxValueString();
		excMessageText = src.getMessageText();
	}

	CFLibExceptionInfo& CFLibExceptionInfo::operator =( const CFLibExceptionInfo& src ) {
		excFlags = src.getFlags();
		excCause = src.getCause();
		excExceptionName = src.getExceptionName();
		excClassFieldName = src.getClassFieldName();
		excMethodName = src.getMethodName();
		excArgOffset = src.getArgOffset();
		excArgName = src.getArgName();
		excArgValueString = src.getArgValueString();
		excArgMinValueString = src.getArgMinValueString();
		excArgMaxValueString = src.getArgMaxValueString();
		excMessageText = src.getMessageText();

		return *this;
	}

	CFLibExceptionInfo::CFLibExceptionInfo( 
		cflibexcflags_t argFlags,
		const std::string& argCause,
		const std::string& argExceptionName,
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		const std::string& argArgValueString,
		const std::string& argArgMinValueString,
		const std::string& argArgMaxValueString,
		const std::string& argMessageText )
	{
		excFlags = argFlags;
		excCause = argCause;
		excExceptionName = argExceptionName;
		excClassFieldName = argClassFieldName;
		excMethodName = argMethodName;
		excArgOffset = argArgOffset;
		excArgName = argArgName;
		excArgValueString = argArgValueString;
		excArgMinValueString = argArgMinValueString;
		excArgMaxValueString = argArgMaxValueString;
		excMessageText = argMessageText;
	}

	CFLibExceptionInfo::CFLibExceptionInfo( 
		cflibexcflags_t argFlags,
		const std::string& argCause,
		const std::string& argExceptionName,
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		const std::string& argArgValueString,
		const std::string& argMessageText )
	{
		excFlags = argFlags;
		excCause = argCause;
		excExceptionName = argExceptionName;
		excClassFieldName = argClassFieldName;
		excMethodName = argMethodName;
		excArgOffset = argArgOffset;
		excArgName = argArgName;
		excArgValueString = argArgValueString;
		excArgMinValueString = S_Empty;
		excArgMaxValueString = S_Empty;
		excMessageText = argMessageText;
	}

	CFLibExceptionInfo::CFLibExceptionInfo( 
		cflibexcflags_t argFlags,
		const std::string& argCause,
		const std::string& argExceptionName,
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		const std::string& argMessageText )
	{
		excFlags = argFlags;
		excCause = argCause;
		excExceptionName = argExceptionName;
		excClassFieldName = argClassFieldName;
		excMethodName = argMethodName;
		excArgOffset = -1LL;
		excArgName = S_Empty;
		excArgValueString = S_Empty;
		excArgMinValueString = S_Empty;
		excArgMaxValueString = S_Empty;
		excMessageText = argMessageText;
	}

	CFLibExceptionInfo::CFLibExceptionInfo( 
		cflibexcflags_t argFlags,
		const std::string& argCause,
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		const std::string& argMessageText )
	{
		excFlags = argFlags;
		excCause = argCause;
		excExceptionName = S_Empty;
		excClassFieldName = argClassFieldName;
		excMethodName = argMethodName;
		excArgOffset = -1LL;
		excArgName = S_Empty;
		excArgValueString = S_Empty;
		excArgMinValueString = S_Empty;
		excArgMaxValueString = S_Empty;
		excMessageText = argMessageText;
	}

	CFLibExceptionInfo::CFLibExceptionInfo( 
		cflibexcflags_t argFlags,
		const std::string& argCause,
		const std::string& argClassFieldName,
		const std::string& argMessageText )
	{
		excFlags = argFlags;
		excCause = argCause;
		excExceptionName = S_Empty;
		excClassFieldName = argClassFieldName;
		excMethodName = S_Empty;
		excArgOffset = -1LL;
		excArgName = S_Empty;
		excArgValueString = S_Empty;
		excArgMinValueString = S_Empty;
		excArgMaxValueString = S_Empty;
		excMessageText = argMessageText;
	}

	CFLibExceptionInfo::CFLibExceptionInfo( 
		cflibexcflags_t argFlags,
		const std::string& argClassFieldName,
		const std::string& argMessageText )
	{
		excFlags = argFlags;
		excCause = S_Empty;
		excExceptionName = S_Empty;
		excClassFieldName = argClassFieldName;
		excMethodName = S_Empty;
		excArgOffset = -1LL;
		excArgName = S_Empty;
		excArgValueString = S_Empty;
		excArgMinValueString = S_Empty;
		excArgMaxValueString = S_Empty;
		excMessageText = argMessageText;
	}

	CFLibExceptionInfo::CFLibExceptionInfo( 
		cflibexcflags_t argFlags,
		const std::string& argMessageText )
	{
		excFlags = argFlags;
		excCause = S_Empty;
		excExceptionName = S_Empty;
		excClassFieldName = S_Empty;
		excMethodName = S_Empty;
		excArgOffset = -1LL;
		excArgName = S_Empty;
		excArgValueString = S_Empty;
		excArgMinValueString = S_Empty;
		excArgMaxValueString = S_Empty;
		excMessageText = argMessageText;
	}

	const std::string& CFLibExceptionInfo::getCause() const {
		return( excCause );
	}

	void CFLibExceptionInfo::setCause( const std::string& value ) {
		excCause = value;
	}

	const std::string& CFLibExceptionInfo::getExceptionName() const {
		return( excExceptionName );
	}

	void CFLibExceptionInfo::setExceptionName( const std::string& value ) {
		excExceptionName = value;
	}

	const std::string& CFLibExceptionInfo::getClassFieldName() const {
		return( excClassFieldName );
	}

	void CFLibExceptionInfo::setClassFieldName( const std::string& value ) {
		excClassFieldName = value;
	}

	const std::string& CFLibExceptionInfo::getMethodName() const {
		return( excMethodName );
	}

	void CFLibExceptionInfo::setMethodName( const std::string& value ) {
		excMethodName = value;
	}

	size_t CFLibExceptionInfo::getArgOffset() const {
		return( excArgOffset );
	}

	void CFLibExceptionInfo::setArgOffset( size_t value ) {
		excArgOffset = value;
	}

	const std::string& CFLibExceptionInfo::getArgName() const {
		return( excArgName );
	}

	void CFLibExceptionInfo::setArgName( const std::string& value ) {
		excArgName = value;
	}

	const std::string& CFLibExceptionInfo::getArgValueString() const {
		return( excArgValueString );
	}

	void CFLibExceptionInfo::setArgValueString( const std::string& value ) {
		excArgValueString = value;
	}

	const std::string& CFLibExceptionInfo::getArgMinValueString() const {
		return( excArgMinValueString );
	}

	void CFLibExceptionInfo::setArgMinValueString( const std::string& value ) {
		excArgMinValueString = value;
	}

	const std::string& CFLibExceptionInfo::getArgMaxValueString() const {
		return( excArgMaxValueString );
	}

	void CFLibExceptionInfo::setArgMaxValueString( const std::string& value ) {
		excArgMaxValueString = value;
	}

	const std::string& CFLibExceptionInfo::getMessageText() const {
		return( excMessageText );
	}

	std::string CFLibExceptionInfo::getMessageTextFirstLine() {
		auto firstCR = excMessageText.find_first_of( '\r' );
		auto firstNL = excMessageText.find_first_of( '\n' );
		if( ( firstCR == std::string::npos ) && ( firstNL == std::string::npos ) ) {
			return( excMessageText );
		}
		else if( ( firstCR != std::string::npos ) && ( firstNL == std::string::npos ) ) {
			return( excMessageText.substr( 0, firstCR ) );
		}
		else if( ( firstCR == std::string::npos ) && ( firstNL != std::string::npos ) ) {
			return( excMessageText.substr( 0, firstNL ) );
		}
		else if( firstCR < firstNL ) {
			return( excMessageText.substr( 0, firstCR ) );
		}
		else {
			return( excMessageText.substr( 0, firstNL ) );
		}
	}

	void CFLibExceptionInfo::setMessageText( const std::string& value ) {
		excMessageText = value;
	}

	std::string CFLibExceptionInfo::getFormattedSystemText( 
		const std::string& argExceptionName,
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		const std::string& argMessageText )
	{
		std::string retval( S_CaughtSystemException );

		retval.append( argExceptionName );
		retval.push_back( ' ' );

		retval.append( argClassFieldName );

		if( ! argMethodName.empty() ) {
			retval.push_back( '.' );
			retval.append( argMethodName );
		}

		retval.push_back( ' ' );

		retval.append( argMessageText );

		return( retval );
	}

	std::string CFLibExceptionInfo::getFormattedXercesText( 
		const std::string& argExceptionName,
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		const std::string& argMessageText )
	{
		std::string retval( S_CaughtXercesException );

		retval.append( argExceptionName );
		retval.push_back( ' ' );

		retval.append( argClassFieldName );

		if( ! argMethodName.empty() ) {
			retval.push_back( '.' );
			retval.append( argMethodName );
		}

		retval.push_back( ' ' );

		retval.append( argMessageText );

		return( retval );
	}

	std::string CFLibExceptionInfo::getFormattedText( 
		const std::string& argCause,
		const std::string& argExceptionName,
		const std::string& argClassFieldName,
		const std::string& argMethodName,
		size_t argArgOffset,
		const std::string& argArgName,
		const std::string& argArgValueString,
		const std::string& argArgMinValueString,
		const std::string& argArgMaxValueString,
		const std::string& argMessageText )
	{
		static const std::string S_Argument( " argument " );

		std::string retval;

		retval.append( argCause );
		retval.push_back( ' ' );
		retval.append( argClassFieldName );

		if( ! argMethodName.empty() ) {
			retval.push_back( '.' );
			retval.append( argMethodName );
			if( ! argArgName.empty() ) {
				if( argArgOffset >= 0LL ) {
					retval.append( S_Argument );
					retval.append( std::to_string( argArgOffset ) );
					retval.push_back( ' ' );
					retval.push_back( '(' );
					retval.append( argArgName );
					retval.push_back( ')' );
				}
				else {
					retval.push_back( '.' );
					retval.append( argArgName );
				}
			}
		}

		retval.push_back( ' ' );

		retval.append( argMessageText );

		return( retval );
	}

	std::string CFLibExceptionInfo::getEffectiveMessage() {
		if( ( excFlags & CFLIB_EXCEPT_CFLIB ) == CFLIB_EXCEPT_CFLIB ) {
			return( getMessageText() );
		}
		else if( ( excFlags & CFLIB_EXCEPT_SYSTEM ) == CFLIB_EXCEPT_SYSTEM ) {
			return( getFormattedSystemText( getExceptionName(),
				getClassFieldName(),
				getMethodName(),
				getMessageText() ) );
		}
		else if( ( excFlags & CFLIB_EXCEPT_XERCES ) == CFLIB_EXCEPT_XERCES ) {
			return( getFormattedXercesText( getExceptionName(),
				getClassFieldName(),
				getMethodName(),
				getMessageText() ) );
		}
		else {
			return( getMessageText() );
		}
	}

	std::string CFLibExceptionInfo::getEffectiveMessageFirstLine() {
		if( ( excFlags & CFLIB_EXCEPT_CFLIB ) == CFLIB_EXCEPT_CFLIB ) {
			return( getMessageTextFirstLine() );
		}
		else if( ( excFlags & CFLIB_EXCEPT_SYSTEM ) == CFLIB_EXCEPT_SYSTEM ) {
			return( getFormattedSystemText( getExceptionName(),
				getClassFieldName(),
				getMethodName(),
				getMessageTextFirstLine() ) );
		}
		else if( ( excFlags & CFLIB_EXCEPT_XERCES ) == CFLIB_EXCEPT_XERCES ) {
			return( getFormattedXercesText( getExceptionName(),
				getClassFieldName(),
				getMethodName(),
				getMessageTextFirstLine() ) );
		}
		else {
			return( getMessageTextFirstLine() );
		}
	}

	std::string CFLibExceptionInfo::getFormattedMessage() {
		if( ( excFlags & CFLIB_EXCEPT_CFLIB ) == CFLIB_EXCEPT_CFLIB ) {
			return( getFormattedText( getCause(),
				getExceptionName(),
				getClassFieldName(),
				getMethodName(),
				getArgOffset(),
				getArgName(),
				getArgValueString(),
				getArgMinValueString(),
				getArgMaxValueString(),
				getMessageText() ) );
		}
		else if( ( excFlags & CFLIB_EXCEPT_SYSTEM ) == CFLIB_EXCEPT_SYSTEM ) {
			return( getFormattedSystemText( getExceptionName(),
				getClassFieldName(),
				getMethodName(),
				getMessageText() ) );
		}
		else if( ( excFlags & CFLIB_EXCEPT_XERCES ) == CFLIB_EXCEPT_XERCES ) {
			return( getFormattedXercesText( getExceptionName(),
				getClassFieldName(),
				getMethodName(),
				getMessageText() ) );
		}
		else {
			return( getMessageText() );
		}
	}

	std::string CFLibExceptionInfo::getFormattedMessageFirstLine() {
		if( ( excFlags & CFLIB_EXCEPT_CFLIB ) == CFLIB_EXCEPT_CFLIB ) {
			return( getFormattedText( getCause(),
				getExceptionName(),
				getClassFieldName(),
				getMethodName(),
				getArgOffset(),
				getArgName(),
				getArgValueString(),
				getArgMinValueString(),
				getArgMaxValueString(),
				getMessageTextFirstLine() ) );
		}
		else if( ( excFlags & CFLIB_EXCEPT_SYSTEM ) == CFLIB_EXCEPT_SYSTEM ) {
			return( getFormattedSystemText( getExceptionName(),
				getClassFieldName(),
				getMethodName(),
				getMessageTextFirstLine() ) );
		}
		else if( ( excFlags & CFLIB_EXCEPT_XERCES ) == CFLIB_EXCEPT_XERCES ) {
			return( getFormattedXercesText( getExceptionName(),
				getClassFieldName(),
				getMethodName(),
				getMessageTextFirstLine() ) );
		}
		else {
			return( getMessageTextFirstLine() );
		}
	}
}
