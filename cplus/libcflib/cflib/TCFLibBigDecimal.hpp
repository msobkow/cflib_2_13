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

#include <memory.h>

#include <cflib/CFLib.hpp>
#include <cflib/CFLibGenericBigDecimal.hpp>
#include <cflib/CFLibArgumentOverflowException.hpp>
#include <cflib/CFLibArgumentUnderflowException.hpp>
#include <cflib/CFLibEmptyArgumentException.hpp>
#include <cflib/CFLibInvalidArgumentException.hpp>
#include <cflib/CFLibMathException.hpp>
#include <cflib/CFLibNotImplementedYetException.hpp>
#include <cflib/CFLibNullArgumentException.hpp>
#include <cflib/CFLibSubroutineException.hpp>

namespace cflib {

	/**
	 *	The TCFLibBigDecimal template is what is used to define
	 *	data instances that can be cast to the CFLibGenericBigDecimal
	 *	base for manipulation.  It is expressed with the following
	 *	arguments:
	 *
	 *	tDigits - The number of digits required for the integer and
	 *		fractional portions of values of this number type.
	 *
	 *	tPrecis - The number of fractional digits to use for this
	 *		number type.  All values applied to this instance are
	 *		truncated to the specified number of fractional digits.
	 *
	 *	The TCFLibBigDecimal methods and operators implement financial
	 *	constraint rules, enforcing the minimum and maximum values for
	 *	the value, and applying MPFR_RNDN rounding to the specified
	 *	precision after each modification of the mpfr_t value behind
	 *	the CFLibGenericBigDecimal and TCFLibBigDecimal implementations.
	 *	You must round all calculations to the required precision when
	 *	performing financial calculations, and that is the main target
	 *	of MSS Code Factory's manufacturing efforts to date.
	 *
	 *	Read-only access to the mpfr_srcptr referencing the MPFR mpfr_t
	 *	value associated with each TCFLibBigDecimal instance is provided
	 *	via getValue(), making it easy to pass them along as arguments
	 *	to custom MPFR-invoking code.
	 *
	 *	Later I will add a C++ CFLibBigPhysics MPFR wrapper
	 *	created by copy-paste-editing TCFLibBigDecimal, but making
	 *	the digits and precision dynamic member values that refer to
	 *	the number decimal places occupied before and after the decimal point.
	 *	The digits and precision in physics are dynamic; physics creates
	 *	and destroys digits of precision all the time.
	 */

	template< const int tDigits, const int tPrecis > class TCFLibBigDecimal : public CFLibGenericBigDecimal {

	protected:
		mpfr_t val = { 0 };

	public:

		/*
		 *	I originally had a table of bits actually required to store
		 *	values with the desired number of digits, but then I realized
		 *	that won't work when calculations exceed MAX_DIGITS for
		 *	intermediate values.  So instead, I now estimate 4 bits
		 *	per digit.
		 */
		static const int digits = tDigits;
		static const int precis = tPrecis;
		static const int integerDigits = tDigits - tPrecis;
		static const mpfr_prec_t BITS_REQUIRED = tDigits * 4;

		const int getDigits() const {
			return( digits );
		}

		const int getPrecision() const {
			return( precis );
		}

		const int getIntegerDigits() const {
			return( integerDigits );
		}

		const mpfr_prec_t getBitsRequired() const {
			return( BITS_REQUIRED );
		}

		/**
		 *	Get the absolute minimum and maximum value that
		 *	can be stored by a number defined by this template's
		 *	digits and precision.
		 */
		static mpfr_srcptr getAbsoluteMinValue() {
			static const std::string S_ProcName("getAbsoluteMinValue");
			static mpfr_ptr mpfrAbsMinValue = NULL;
			if( mpfrAbsMinValue == NULL ) {
				if( digits < MIN_DIGITS ) {
					throw CFLibArgumentUnderflowException( CLASSNAME_TCFLIBBIGDECIMAL,
						S_ProcName,
						0,
						S_Digits,
						digits,
						MIN_DIGITS );
				}
				if( digits > MAX_DIGITS ) {
					throw CFLibArgumentOverflowException( CLASSNAME_TCFLIBBIGDECIMAL,
						S_ProcName,
						0,
						S_Digits,
						digits,
						MAX_DIGITS );
				}
				if( precis < MIN_PRECISION ) {
					throw CFLibArgumentUnderflowException( CLASSNAME_TCFLIBBIGDECIMAL,
						S_ProcName,
						0,
						S_Precis,
						precis,
						MIN_PRECISION );
				}
				if( precis > MAX_PRECISION ) {
					throw CFLibArgumentOverflowException( CLASSNAME_TCFLIBBIGDECIMAL,
						S_ProcName,
						0,
						S_Precis,
						precis,
						MAX_PRECISION );
				}
				if( precis >= digits ) {
					throw CFLibArgumentOverflowException( CLASSNAME_TCFLIBBIGDECIMAL,
						S_ProcName,
						0,
						S_Precis,
						precis,
						digits - 1 );
				}
				char c_nines[MAX_DIGITS+1];
				memset( c_nines, '9', MAX_DIGITS+1 );
				c_nines[MAX_DIGITS] = '\000';
				std::string S_Nines( c_nines );
				std::string strAbsMinValue;
				if( precis <= 0 ) {
					strAbsMinValue.append("-");
					strAbsMinValue.append( S_Nines.substr( 0, integerDigits ));
				}
				else {
					strAbsMinValue.append("-");
					strAbsMinValue.append( S_Nines.substr( 0, integerDigits ));
					strAbsMinValue.append(".");
					strAbsMinValue.append( S_Nines.substr( 0, precis ));
				}
				mpfrAbsMinValue = new mpfr_t;
				mpfr_init2( mpfrAbsMinValue, BITS_REQUIRED );
				int substatus = mpfr_set_str( mpfrAbsMinValue, strAbsMinValue.c_str(), 10, MPFR_RNDN );
				if( substatus != 0 ) {
					CFLibSubroutineException toThrow( CLASSNAME_TCFLIBBIGDECIMAL,
						S_ProcName,
						S_MpfrSetStr,
						substatus,
						S_MpfrSetStrFailure );
					mpfr_clear( mpfrAbsMinValue );
					delete mpfrAbsMinValue;
					mpfrAbsMinValue = NULL;
					throw toThrow;
				}
			}
			return( mpfrAbsMinValue );
		}

		static mpfr_srcptr getAbsoluteMaxValue() {
			static const std::string S_ProcName("getAbsoluteMaxValue");
			static mpfr_ptr mpfrAbsMaxValue = NULL;
			if( mpfrAbsMaxValue == NULL ) {
				if( digits < MIN_DIGITS ) {
					throw CFLibArgumentUnderflowException( CLASSNAME_TCFLIBBIGDECIMAL,
						S_ProcName,
						0,
						S_Digits,
						digits,
						MIN_DIGITS );
				}
				if( digits > MAX_DIGITS ) {
					throw CFLibArgumentOverflowException( CLASSNAME_TCFLIBBIGDECIMAL,
						S_ProcName,
						0,
						S_Digits,
						digits,
						MAX_DIGITS );
				}
				if( precis < MIN_PRECISION ) {
					throw CFLibArgumentUnderflowException( CLASSNAME_TCFLIBBIGDECIMAL,
						S_ProcName,
						0,
						S_Precis,
						precis,
						MIN_PRECISION );
				}
				if( precis > MAX_PRECISION ) {
					throw CFLibArgumentOverflowException( CLASSNAME_TCFLIBBIGDECIMAL,
						S_ProcName,
						0,
						S_Precis,
						precis,
						MAX_PRECISION );
				}
				if( precis >= digits ) {
					throw CFLibArgumentOverflowException( CLASSNAME_TCFLIBBIGDECIMAL,
						S_ProcName,
						0,
						S_Precis,
						precis,
						digits - 1 );
				}
				char c_nines[MAX_DIGITS+1];
				memset( c_nines, '9', MAX_DIGITS+1 );
				c_nines[MAX_DIGITS] = '\000';
				std::string S_Nines( c_nines );
				std::string strAbsMaxValue;
				if( precis <= 0 ) {
					strAbsMaxValue.append( S_Nines.substr( 0, integerDigits ));
				}
				else {
					strAbsMaxValue.append( S_Nines.substr( 0, integerDigits ));
					strAbsMaxValue.append(".");
					strAbsMaxValue.append( S_Nines.substr( 0, precis ));
				}
				mpfrAbsMaxValue = new mpfr_t;
				mpfr_init2( mpfrAbsMaxValue, BITS_REQUIRED );
				int substatus = mpfr_set_str( mpfrAbsMaxValue, strAbsMaxValue.c_str(), 10, MPFR_RNDN );
				if( substatus != 0 ) {
					CFLibSubroutineException toThrow( CLASSNAME_TCFLIBBIGDECIMAL,
						S_ProcName,
						S_MpfrSetStr,
						substatus,
						S_MpfrSetStrFailure );
					mpfr_clear( mpfrAbsMaxValue );
					delete mpfrAbsMaxValue;
					mpfrAbsMaxValue = NULL;
					throw toThrow;
				}
			}
			return( mpfrAbsMaxValue );
		}

protected:

		/**
		 *	Minimize repetitive flag analysis code.
		 */
		static inline void analyseFlags( const std::string& procName,
			mpfr_ptr clearMe1 = NULL,
			mpfr_ptr clearMe2 = NULL )
		{
			static const std::string S_ProcName( "analyseFlags" );
			mpfr_flags_t f = mpfr_flags_test( MPFR_FLAGS_UNDERFLOW
				| MPFR_FLAGS_OVERFLOW
				| MPFR_FLAGS_NAN
				| MPFR_FLAGS_ERANGE
				| MPFR_FLAGS_DIVBY0
				| MPFR_FLAGS_ERANGE );
			if( f ) {
				if( clearMe1 != NULL ) {
					mpfr_clear( clearMe1 );
				}
				if( clearMe2 != NULL ) {
					mpfr_clear( clearMe2 );
				}
				if( f & MPFR_FLAGS_UNDERFLOW ) {
					throw CFLibArgumentUnderflowException( CLASSNAME_TCFLIBBIGDECIMAL, procName, S_Underflow );
				}
				else if( f & MPFR_FLAGS_OVERFLOW ) {
					throw CFLibArgumentOverflowException( CLASSNAME_TCFLIBBIGDECIMAL, procName, S_Overflow );
				}
				else if( f & MPFR_FLAGS_NAN ) {
					throw CFLibMathException( CLASSNAME_TCFLIBBIGDECIMAL, procName, S_NaN );
				}
				else if( f & MPFR_FLAGS_ERANGE ) {
					throw CFLibArgumentOverflowException( CLASSNAME_TCFLIBBIGDECIMAL, procName, S_ERange );
				}
				else if( f & MPFR_FLAGS_DIVBY0 ) {
					throw CFLibMathException( CLASSNAME_TCFLIBBIGDECIMAL, procName, S_DivBy0 );
				}
				else {
					throw CFLibNotImplementedYetException( CLASSNAME_TCFLIBBIGDECIMAL, S_ProcName );
				}
			}
		}

		static inline void checkAbsoluteRange( const std::string& procName,
			const int varIndex,
			const std::string& varName,
			mpfr_srcptr var,
			mpfr_ptr clearMe1 = NULL,
			mpfr_ptr clearMe2 = NULL )
		{
			if( 0 > mpfr_cmp( var, getAbsoluteMinValue() ) ) {
				CFLibArgumentUnderflowException toThrow( CLASSNAME_TCFLIBBIGDECIMAL,
					procName,
					varIndex,
					varName,
					var,
					getAbsoluteMinValue() );
				if( clearMe1 != NULL ) {
					mpfr_clear( clearMe1 );
				}
				if( clearMe2 != NULL ) {
					mpfr_clear( clearMe2 );
				}
				throw toThrow;
			}
			if( 0 < mpfr_cmp( var, getAbsoluteMaxValue() ) ) {
				CFLibArgumentOverflowException toThrow( CLASSNAME_TCFLIBBIGDECIMAL,
					procName,
					varIndex,
					varName,
					var,
					getAbsoluteMaxValue() );
				if( clearMe1 != NULL ) {
					mpfr_clear( clearMe1 );
				}
				if( clearMe2 != NULL ) {
					mpfr_clear( clearMe2 );
				}
				throw toThrow;
			}
		}

		static inline void analyseMpfrTernary( const std::string& procName,
			int retval,
			mpfr_ptr clearMe1 = NULL,
			mpfr_ptr clearMe2 = NULL )
		{
			if( 0 != retval ) {
				if( retval < 0 ) {
					CFLibMathException toThrow( CLASSNAME_TCFLIBBIGDECIMAL,
						procName,
						S_MpfrFunctionRoundedUp );
					if( clearMe1 != NULL ) {
						mpfr_clear( clearMe1 );
					}
					if( clearMe2 != NULL ) {
						mpfr_clear( clearMe2 );
					}
					throw toThrow;
				}
				else {
					CFLibMathException toThrow( CLASSNAME_TCFLIBBIGDECIMAL,
						procName,
						S_MpfrFunctionRoundedDown );
					if( clearMe1 != NULL ) {
						mpfr_clear( clearMe1 );
					}
					if( clearMe2 != NULL ) {
						mpfr_clear( clearMe2 );
					}
					throw toThrow;
				}
			}
		}

public:

		/**
		 *	Default constructor.
		 */
		TCFLibBigDecimal<tDigits, tPrecis>()
		: CFLibGenericBigDecimal()
		{
			mpfr_init2( val, BITS_REQUIRED );
		}

		/**
		 *	Copy generic constructor.
		 *
		 *		src - The CFLibGenericBigDecimal instance to use to
		 *			set the value of the new instance.
		 */
		TCFLibBigDecimal<tDigits, tPrecis>( const CFLibGenericBigDecimal& src )
		: CFLibGenericBigDecimal()
		{
			static const std::string S_ProcName("copy-generic-constructor");
			mpfr_init2( val, BITS_REQUIRED );
			mpfr_srcptr pSrc = src.getValue();
			checkAbsoluteRange( S_ProcName, 1, S_Src, pSrc, val );
			mpfr_set( val, pSrc, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
		}

		/**
		 *	Copy constructor.
		 *
		 *		src - The TCFLibBigDecimal instance to use to set the value of the new instance.
		 */
		TCFLibBigDecimal<tDigits, tPrecis>( const TCFLibBigDecimal& src )
		: CFLibGenericBigDecimal()
		{
			static const std::string S_ProcName("copy-constructor");
			mpfr_init2( val, BITS_REQUIRED );
			mpfr_srcptr pSrc = src.getValue();
			checkAbsoluteRange( S_ProcName, 1, S_Src, pSrc, val );
			mpfr_set( val, pSrc, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
		}

		/**
		 *	Set mpfr_t value constructor.
		 *
		 *		src - mpfr_t to use to set the value of the new instance.
		 */
		TCFLibBigDecimal<tDigits, tPrecis>( const mpfr_t& src )
		: CFLibGenericBigDecimal()
		{
			static const std::string S_ProcName("mpfr-reference-constructor");
			mpfr_init2( val, BITS_REQUIRED );
			mpfr_srcptr pSrc = &(src[0]);
			checkAbsoluteRange( S_ProcName, 1, S_Src, pSrc, val );
			mpfr_set( val, pSrc, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
		}

		/**
		 *	Set mpfr srcptr constructor.
		 *
		 *		src - The mpfr srcptr to use to set the value of the new instance.
		 *			May not be NULL.
		 */
		TCFLibBigDecimal<tDigits, tPrecis>( const mpfr_srcptr src )
		: CFLibGenericBigDecimal()
		{
			static const std::string S_ProcName("mpfr-pointer-constructor");
			mpfr_init2( val, BITS_REQUIRED );
			checkAbsoluteRange( S_ProcName, 1, S_Src, src, val );
			mpfr_set( val, src, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
		}

		/**
		 *	Set string value constructor.
		 *
		 *		src - signed decimal fraction value to use to set the value of the new instance.
		 *			May not be NULL or empty.
		 */
		TCFLibBigDecimal<tDigits, tPrecis>( const std::string& src )
		: CFLibGenericBigDecimal()
		{
			static const std::string S_ProcName("string-constructor");
			mpfr_init2( val, BITS_REQUIRED );
			if( src.length() <= 0 ) {
				mpfr_clear( val );
				throw CFLibEmptyArgumentException( CLASSNAME_TCFLIBBIGDECIMAL,
					S_ProcName,
					1,
					S_Src );
			}
			int substatus = mpfr_set_str( val, src.c_str(), 10, MPFR_RNDN );
			if( substatus != 0 ) {
				mpfr_clear( val );
				throw CFLibSubroutineException( CLASSNAME_TCFLIBBIGDECIMAL,
					S_ProcName,
					S_MpfrSetStr,
					substatus,
					S_MpfrSetStrFailure );
			}
			checkAbsoluteRange( S_ProcName, 1, S_Src, val, val );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
		}

		/**
		 *	Set unsigned long int value constructor.
		 *
		 *		src - unsigned long int to use to set the value of the new instance.
		 */
		TCFLibBigDecimal<tDigits, tPrecis>( unsigned long int src )
		: CFLibGenericBigDecimal()
		{
			static const std::string S_ProcName("unsigned-long-int-constructor");
			mpfr_init2( val, BITS_REQUIRED );
			mpfr_t tmpval;
			mpfr_init2( tmpval, sizeof( unsigned long int ) * 8 + 4 );
			mpfr_set_ui( tmpval, src, MPFR_RNDN );
			checkAbsoluteRange( S_ProcName, 1, S_Src, tmpval, val, tmpval );
			mpfr_set( val, tmpval, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmpval );
		}

		/**
		 *	Set long int value constructor.
		 *
		 *		src - long int to use to set the value of the new instance.
		 */
		TCFLibBigDecimal<tDigits, tPrecis>( long int src )
		: CFLibGenericBigDecimal()
		{
			static const std::string S_ProcName("long-int-constructor");
			mpfr_init2( val, BITS_REQUIRED );
			mpfr_t tmpval;
			mpfr_init2( tmpval, sizeof( long int ) * 8 + 4 );
			mpfr_set_si( tmpval, src, MPFR_RNDN );
			checkAbsoluteRange( S_ProcName, 1, S_Src, tmpval, val, tmpval );
			mpfr_set( val, tmpval, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmpval );
		}

		/**
		 *	Set double value constructor.
		 *
		 *		src - double to use to set the value of the new instance.
		 */
		TCFLibBigDecimal<tDigits, tPrecis>( double src )
		: CFLibGenericBigDecimal()
		{
			static const std::string S_ProcName("double-constructor");
			mpfr_init2( val, BITS_REQUIRED );
			mpfr_t tmpval;
			mpfr_init2( tmpval, sizeof( double ) * 8 * 2 );
			mpfr_set_d( tmpval, src, MPFR_RNDN );
			checkAbsoluteRange( S_ProcName, 1, S_Src, tmpval, val, tmpval );
			mpfr_set( val, tmpval, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmpval );
		}

		/**
		 *	The virtual destructor has to release the locally allocated storage.
		 */
		virtual ~TCFLibBigDecimal<tDigits, tPrecis>() {
			mpfr_clear( val );
		}

		/**
		 *	NaN accessors
		 */
		virtual void setNaN() {
			mpfr_set_nan( val );
		}

		virtual bool isNaN() const {
			if( mpfr_nan_p( val ) ) {
				return( true );
			}
			else {
				return( false );
			}
		}

		/**
		 *	Is this value infinite?
		 */
		virtual bool isInfinite() const {
			if( mpfr_inf_p( val ) ) {
				return( true );
			}
			else {
				return( false );
			}
		}

		virtual void setInfinite( int sign ) {
			mpfr_set_inf( val, sign );
		}

		/**
		 *	Is this value a valid number?
		 */
		virtual bool isNumber() const {
			if( mpfr_number_p( val ) ) {
				return( true );
			}
			else {
				return( false );
			}
		}

		/**
		 *	Is this value an integer?
		 *	In other words, is the fractional
		 *	portion, if any, all zeroes.
		 */
		virtual bool isInteger() const {
			if( mpfr_integer_p( val ) ) {
				return( true );
			}
			else {
				return( false );
			}
		}

		/**
		 *	Is this value equal to zero?
		 */
		virtual bool isZero() const {
			if( mpfr_zero_p( val ) ) {
				return( true );
			}
			else {
				return( false );
			}
		}

		virtual void setZero( int sign ) {
			mpfr_set_zero( val, sign );
		}

		/**
		 *	I'm not sure what a "regular" number is.
		 *	Maybe they're referring to it being rational?
		 *	I suppose I could read more documentation.
		 *
		 *	MSS TODO WORKING read up on this and document
		 *	accordingly.
		 */
		virtual bool isRegular() const {
			if( mpfr_regular_p( val ) ) {
				return( true );
			}
			else {
				return( false );
			}
		}

		/**
		 *	Get a convenient read-only pointer to the
		 *	mpfr_t value of this instance.
		 */
		virtual mpfr_srcptr getValue() const {
			return( val );
		}

		/**
		 *	Various setters for mpfr_t, mpfr_srcptr,
		 *	unsigned long int, long int, double,
		 *	signed decimal fraction number string,
		 *	CFLibGenericBigDecimal, and	TCFLibBigDecimal
		 *	arguments.
		 */
		virtual void setValue( const mpfr_t& argValue ) {
			static const std::string S_ProcName("setValue");
			checkAbsoluteRange( S_ProcName, 1, S_Value, argValue );
			mpfr_set( val, argValue, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
		}

		virtual void setValue( mpfr_srcptr argValue ) {
			static const std::string S_ProcName("setValue");
			if( argValue == NULL ) {
				throw CFLibNullArgumentException( CLASSNAME_TCFLIBBIGDECIMAL,
					S_ProcName,
					1,
					S_Value );
			}
			checkAbsoluteRange( S_ProcName, 1, S_Value, argValue );
			mpfr_set( val, argValue, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
		}

		virtual void setValue( unsigned long int src )
		{
			static const std::string S_ProcName("setValue-unsigned-long-int");
			mpfr_t rawValue;
			mpfr_init2( rawValue, sizeof( unsigned long int ) * 8 + 4 );
			mpfr_set_ui( rawValue, src, MPFR_RNDN );
			checkAbsoluteRange( S_ProcName, 1, S_Value, rawValue, rawValue  );
			mpfr_set( val, rawValue, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( rawValue );
		}

		virtual void setValue( long int src )
		{
			static const std::string S_ProcName("setValue-long-int");
			mpfr_t rawValue;
			mpfr_init2( rawValue, sizeof( long int ) * 8 + 4 );
			mpfr_set_si( rawValue, src, MPFR_RNDN );
			checkAbsoluteRange( S_ProcName, 1, S_Value, rawValue, rawValue );
			mpfr_set( val, rawValue, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( rawValue );
		}

		virtual void setValue( double src )
		{
			static const std::string S_ProcName("setValue-double");
			mpfr_t rawValue;
			mpfr_init2( rawValue, sizeof( double ) * 8 * 2 );
			mpfr_set_d( rawValue, src, MPFR_RNDN );
			checkAbsoluteRange( S_ProcName, 1, S_Value, rawValue, rawValue );
			mpfr_set( val, rawValue, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( rawValue );
		}

		virtual void setValue( const std::string& src )
		{
			static const std::string S_ProcName("setValue-string");
			if( src.length() <= 0 ) {
				throw CFLibEmptyArgumentException( CLASSNAME_TCFLIBBIGDECIMAL,
					S_ProcName,
					1,
					S_Src );
			}
			mpfr_t rawValue;
			mpfr_init2( rawValue, ( src.length() + 1 ) * 4 );
			int substatus = mpfr_set_str( rawValue, src.c_str(), 10, MPFR_RNDN );
			if( substatus != 0 ) {
				CFLibSubroutineException toThrow( CLASSNAME_TCFLIBBIGDECIMAL,
					S_ProcName,
					S_MpfrSetStr,
					substatus,
					S_MpfrSetStrFailure );
				mpfr_clear( rawValue );
				throw toThrow;
			}
			checkAbsoluteRange( S_ProcName, 1, S_Value, rawValue, rawValue );
			mpfr_set( val, rawValue, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( rawValue );
		}

		/**
		 *	Assignment operators for various mpfr_t, mpfr_srcptr,
		 *	unsigned long int, long int, double,
		 *	signed decimal fraction number string,
		 *	CFLibGenericBigDecimal, and	TCFLibBigDecimal
		 *	arguments.
		 */
		TCFLibBigDecimal<tDigits,tPrecis>& operator =( const CFLibGenericBigDecimal& src ) {
			static const std::string S_ProcName("operator=");
			if( this != &src ) {
				mpfr_srcptr srcValue = src.getValue();
				checkAbsoluteRange( S_ProcName, 1, S_Src, srcValue );
				mpfr_set( val, srcValue, MPFR_RNDN );
				cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			}
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator =( const TCFLibBigDecimal& src ) {
			static const std::string S_ProcName("operator=");
			if( this != &src ) {
				mpfr_srcptr srcValue = src.getValue();
				checkAbsoluteRange( S_ProcName, 1, S_Src, srcValue );
				mpfr_set( val, srcValue, MPFR_RNDN );
				cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			}
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator =( const mpfr_t& src ) {
			static const std::string S_ProcName("operator=");
			mpfr_srcptr pSrc = &(src[0]);
			checkAbsoluteRange( S_ProcName, 1, S_Src, pSrc );
			mpfr_set( val, pSrc, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator =( mpfr_srcptr src ) {
			static const std::string S_ProcName("operator=");
			if( src == NULL ) {
				mpfr_set_nan( val );
			}
			else {
				checkAbsoluteRange( S_ProcName, 1, S_Src, src );
				mpfr_set( val, src, MPFR_RNDN );
				cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			}
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator =( const std::string& src ) {
			static const std::string S_ProcName("operator=");
			if( src.length() <= 0 ) {
				throw CFLibEmptyArgumentException( CLASSNAME_TCFLIBBIGDECIMAL,
					S_ProcName,
					1,
					S_Src );
			}
			if( src.length() <= 0 ) {
				throw CFLibEmptyArgumentException( CLASSNAME_TCFLIBBIGDECIMAL,
					S_ProcName,
					1,
					S_Src );
			}
			mpfr_t rawValue;
			mpfr_init2( rawValue, ( src.length() + 1 ) * 4 );
			int substatus = mpfr_set_str( rawValue, src.c_str(), 10, MPFR_RNDN );
			if( substatus != 0 ) {
				CFLibSubroutineException toThrow( CLASSNAME_TCFLIBBIGDECIMAL,
					S_ProcName,
					S_MpfrSetStr,
					substatus,
					S_MpfrSetStrFailure );
				mpfr_clear( rawValue );
				throw toThrow;
			}
			checkAbsoluteRange( S_ProcName, 1, S_Src, rawValue, rawValue );
			mpfr_set( val, rawValue, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( rawValue );
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator =( unsigned long int src ) {
			static const std::string S_ProcName("operator=");
			mpfr_t tmpval;
			mpfr_init2( tmpval, sizeof( unsigned long int ) * 8 + 4 );
			mpfr_set_ui( tmpval, src, MPFR_RNDN );
			checkAbsoluteRange( S_ProcName, 1, S_Src, tmpval, tmpval );
			mpfr_set( val, tmpval, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmpval );
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator =( long int src ) {
			static const std::string S_ProcName("operator=");
			mpfr_init2( val, BITS_REQUIRED );
			mpfr_t tmpval;
			mpfr_init2( tmpval, sizeof( long int ) * 8 + 4 );
			mpfr_set_si( tmpval, src, MPFR_RNDN );
			checkAbsoluteRange( S_ProcName, 1, S_Src, tmpval, tmpval );
			mpfr_set( val, tmpval, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmpval );
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator =( double src ) {
			static const std::string S_ProcName("operator=");
			mpfr_init2( val, BITS_REQUIRED );
			mpfr_t tmpval;
			mpfr_init2( tmpval, sizeof( double ) * 8 * 2 );
			mpfr_set_d( tmpval, src, MPFR_RNDN );
			checkAbsoluteRange( S_ProcName, 1, S_Src, tmpval, tmpval );
			mpfr_set( val, tmpval, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmpval );
			return( *this );
		}

		/**
		 *	Add and assign operators for various mpfr_t, mpfr_srcptr,
		 *	unsigned long int, long int, double,
		 *	CFLibGenericBigDecimal, and	TCFLibBigDecimal
		 *	arguments.
		 */
		TCFLibBigDecimal<tDigits,tPrecis>& operator +=( const CFLibGenericBigDecimal& src ) {
			static const std::string S_ProcName("operator+=-CFLibGenericBigDecimal");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_add( tmp, val, src.getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp);
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator +=( const TCFLibBigDecimal& src ) {
			static const std::string S_ProcName("operator+=-TCFLibBigDecimal");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_add( tmp, val, src.getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator +=( const mpfr_t& src ) {
			static const std::string S_ProcName("operator+=-mpfr_t");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_add( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator +=( mpfr_srcptr src ) {
			static const std::string S_ProcName("operator+=-mpfr_srcptr");
			if( src == NULL ) {
				mpfr_set_nan( val );
			}
			else {
				mpfr_t tmp;
				mpfr_init2( tmp, BITS_REQUIRED );
				clearFlags();
				int mpfrTernary = mpfr_add( tmp, val, src, MPFR_RNDN );
				// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
				analyseFlags( S_ProcName, tmp );
				checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
				mpfr_set( val, tmp, MPFR_RNDN );
				cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
				mpfr_clear( tmp );
			}
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator +=( unsigned long int src ) {
			static const std::string S_ProcName("operator+=-unsigned-long-int");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_add_ui( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator +=( long int src ) {
			static const std::string S_ProcName("operator+=-long-int");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_add_si( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator +=( double src ) {
			static const std::string S_ProcName("operator+=-double");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			mpfr_add_d( tmp, val, src, MPFR_RNDN );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( *this );
		}

		/**
		 *	Add operators for various mpfr_t, mpfr_srcptr,
		 *	unsigned long int, long int, double,
		 *	CFLibGenericBigDecimal, and	TCFLibBigDecimal
		 *	arguments.
		 */
		TCFLibBigDecimal operator +( const CFLibGenericBigDecimal& src ) {
			static const std::string S_ProcName("operator+-CFLibGenericBigDecimal");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_add( tmp, val, src.getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal operator +( const TCFLibBigDecimal& src ) {
			static const std::string S_ProcName("operator+-TCFLibBigDecimal");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_add( tmp, val, src.getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal operator +( const mpfr_t& src ) {
			static const std::string S_ProcName("operator+-mpfr_t");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_add( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal operator +( mpfr_srcptr src ) {
			static const std::string S_ProcName("operator+-mpfr_srcptr");
			if( src == NULL ) {
				TCFLibBigDecimal<tDigits,tPrecis> retval;
				return( retval );
			}
			else {
				mpfr_t tmp;
				mpfr_init2( tmp, BITS_REQUIRED );
				clearFlags();
				int mpfrTernary = mpfr_add( tmp, val, src, MPFR_RNDN );
				// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
				analyseFlags( S_ProcName, tmp );
				checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
				TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
				mpfr_clear( tmp );
				return( retval );
			}
		}

		TCFLibBigDecimal operator +( unsigned long int src ) {
			static const std::string S_ProcName("operator+-unsigned-long-int");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_add_ui( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal operator +( long int src ) {
			static const std::string S_ProcName("operator+-long-int");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_add_si( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal operator +( double src ) {
			static const std::string S_ProcName("operator+-double");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_add_d( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		/**
		 *	Unary minus operator.
		 */
		TCFLibBigDecimal operator -() const {
			TCFLibBigDecimal<digits,precis> retval( ZERO );
			retval -= val;
			return( retval );
		}

		/**
		 *	Subtract and assign operators for various mpfr_t, mpfr_srcptr,
		 *	unsigned long int, long int, double,
		 *	CFLibGenericBigDecimal, and	TCFLibBigDecimal
		 *	arguments.
		 */
		TCFLibBigDecimal<tDigits,tPrecis>& operator -=( const CFLibGenericBigDecimal& src ) {
			static const std::string S_ProcName("operator-=-CFLibGenericBigDecimal");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_sub( tmp, val, src.getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator -=( const TCFLibBigDecimal& src ) {
			static const std::string S_ProcName("operator-=-TCFLibBigDecimal");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_sub( tmp, val, src.getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator -=( const mpfr_t& src ) {
			static const std::string S_ProcName("operator-=-mpfr_t");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_sub( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator -=( mpfr_srcptr src ) {
			static const std::string S_ProcName("operator-=-mpfr_srcptr");
			if( src == NULL ) {
				mpfr_set_nan( val );
			}
			else {
				mpfr_t tmp;
				mpfr_init2( tmp, BITS_REQUIRED );
				clearFlags();
				int mpfrTernary = mpfr_sub( tmp, val, src, MPFR_RNDN );
				// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
				analyseFlags( S_ProcName, tmp );
				checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
				mpfr_set( val, tmp, MPFR_RNDN );
				cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
				mpfr_clear( tmp );
			}
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator -=( unsigned long int src ) {
			static const std::string S_ProcName("operator-=-unsigned-long-int");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_sub_ui( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator -=( long int src ) {
			static const std::string S_ProcName("operator-=-long-int");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_sub_si( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator -=( double src ) {
			static const std::string S_ProcName("operator-=-double");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_sub_d( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( *this );
		}

		/**
		 *	Subtract operators for various mpfr_t, mpfr_srcptr,
		 *	unsigned long int, long int, double,
		 *	CFLibGenericBigDecimal, and	TCFLibBigDecimal
		 *	arguments.
		 */
		TCFLibBigDecimal operator -( const CFLibGenericBigDecimal& src ) {
			static const std::string S_ProcName("operator--CFLibGenericBigDecimal");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_sub( tmp, val, src.getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal operator -( const TCFLibBigDecimal& src ) {
			static const std::string S_ProcName("operator--TCFLibBigDecimal");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_sub( tmp, val, src.getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal operator -( const mpfr_t& src ) {
			static const std::string S_ProcName("operator--mpfr_t");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_sub( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal operator -( mpfr_srcptr src ) {
			static const std::string S_ProcName("operator--mpfr_srcptr");
			if( src == NULL ) {
				TCFLibBigDecimal<tDigits,tPrecis> retval;
				return( retval );
			}
			else {
				mpfr_t tmp;
				mpfr_init2( tmp, BITS_REQUIRED );
				clearFlags();
				int mpfrTernary = mpfr_sub( tmp, val, src, MPFR_RNDN );
				// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
				analyseFlags( S_ProcName, tmp );
				checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
				TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
				mpfr_clear( tmp );
				return( retval );
			}
		}

		TCFLibBigDecimal operator -( unsigned long int src ) {
			static const std::string S_ProcName("operator--unsigned-long-int");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_sub_ui( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal operator -( long int src ) {
			static const std::string S_ProcName("operator--long-int");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_sub_si( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal operator -( double src ) {
			static const std::string S_ProcName("operator--double");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_sub_d( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		/**
		 *	Multiply and assign operators for various mpfr_t, mpfr_srcptr,
		 *	unsigned long int, long int, double,
		 *	CFLibGenericBigDecimal, and	TCFLibBigDecimal
		 *	arguments.
		 */
		TCFLibBigDecimal<tDigits,tPrecis>& operator *=( const CFLibGenericBigDecimal& src ) {
			static const std::string S_ProcName("operator*=-CFLibGenericBigDecimal");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_mul( tmp, val, src.getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator *=( const TCFLibBigDecimal& src ) {
			static const std::string S_ProcName("operator*=-TCFLibBigDecimal");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_mul( tmp, val, src.getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator *=( const mpfr_t& src ) {
			static const std::string S_ProcName("operator*=-mpfr_t");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_mul( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator *=( mpfr_srcptr src ) {
			static const std::string S_ProcName("operator*=-mpfr_srcptr");
			if( src == NULL ) {
				mpfr_set_nan( val );
			}
			else {
				mpfr_t tmp;
				mpfr_init2( tmp, BITS_REQUIRED );
				clearFlags();
				int mpfrTernary = mpfr_mul( tmp, val, src, MPFR_RNDN );
				// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
				analyseFlags( S_ProcName, tmp );
				checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
				mpfr_set( val, tmp, MPFR_RNDN );
				cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
				mpfr_clear( tmp );
			}
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator *=( unsigned long int src ) {
			static const std::string S_ProcName("operator*=-unsigned-long-int");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_mul_ui( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator *=( long int src ) {
			static const std::string S_ProcName("operator*=-long-int");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_mul_si( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator *=( double src ) {
			static const std::string S_ProcName("operator*=-double");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_mul_d( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( *this );
		}

		/**
		 *	Multiply operators for various mpfr_t, mpfr_srcptr,
		 *	unsigned long int, long int, double,
		 *	CFLibGenericBigDecimal, and	TCFLibBigDecimal
		 *	arguments.
		 */
		TCFLibBigDecimal operator *( const CFLibGenericBigDecimal& src ) {
			static const std::string S_ProcName("operator*-CFLibGenericBigDecimal");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_mul( tmp, val, src.getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal operator *( const TCFLibBigDecimal& src ) {
			static const std::string S_ProcName("operator*-TCFLibBigDecimal");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_mul( tmp, val, src.getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal operator *( const mpfr_t& src ) {
			static const std::string S_ProcName("operator*-mpfr_t");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_mul( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal operator *( mpfr_srcptr src ) {
			static const std::string S_ProcName("operator*-mpfr_srcptr");
			if( src == NULL ) {
				TCFLibBigDecimal<tDigits,tPrecis> retval;
				return( retval );
			}
			else {
				mpfr_t tmp;
				mpfr_init2( tmp, BITS_REQUIRED );
				clearFlags();
				int mpfrTernary = mpfr_mul( tmp, val, src, MPFR_RNDN );
				// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
				analyseFlags( S_ProcName, tmp );
				checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
				TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
				mpfr_clear( tmp );
				return( retval );
			}
		}

		TCFLibBigDecimal operator *( unsigned long int src ) {
			static const std::string S_ProcName("operator*-unsigned-long-int");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_mul_ui( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal operator *( long int src ) {
			static const std::string S_ProcName("operator*-long-int");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_mul_si( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal operator *( double src ) {
			static const std::string S_ProcName("operator*-double");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_mul_d( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		/**
		 *	Divide and assign operators for various mpfr_t, mpfr_srcptr,
		 *	unsigned long int, long int, double,
		 *	CFLibGenericBigDecimal, and	TCFLibBigDecimal
		 *	arguments.
		 */
		TCFLibBigDecimal<tDigits,tPrecis>& operator /=( const CFLibGenericBigDecimal& src ) {
			static const std::string S_ProcName("operator/=-CFLibGenericBigDecimal");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_div( tmp, val, src.getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator /=( const TCFLibBigDecimal& src ) {
			static const std::string S_ProcName("operator/=-TCFLibBigDecimal");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_div( tmp, val, src.getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator /=( const mpfr_t& src ) {
			static const std::string S_ProcName("operator/=-mpfr_t");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_div( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator /=( mpfr_srcptr src ) {
			static const std::string S_ProcName("operator/=-mpfr_srcptr");
			if( src == NULL ) {
				mpfr_set_nan( val );
			}
			else {
				mpfr_t tmp;
				mpfr_init2( tmp, BITS_REQUIRED );
				clearFlags();
				int mpfrTernary = mpfr_div( tmp, val, src, MPFR_RNDN );
				// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
				analyseFlags( S_ProcName, tmp );
				checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
				mpfr_set( val, tmp, MPFR_RNDN );
				cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
				mpfr_clear( tmp );
			}
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator /=( unsigned long int src ) {
			static const std::string S_ProcName("operator/=-unsigned-long-int");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_div_ui( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator /=( long int src ) {
			static const std::string S_ProcName("operator/=-long-int");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_div_si( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator /=( double src ) {
			static const std::string S_ProcName("operator/=-double");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_div_d( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( *this );
		}

		/**
		 *	Divide operators
		 */
		TCFLibBigDecimal operator /( const CFLibGenericBigDecimal& src ) {
			static const std::string S_ProcName("operator/-CFLibGenericBigDecimal");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_div( tmp, val, src.getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal operator /( const TCFLibBigDecimal& src ) {
			static const std::string S_ProcName("operator/-TCFLibBigDecimal");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_div( tmp, val, src.getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal operator /( const mpfr_t& src ) {
			static const std::string S_ProcName("operator/-mpfr_t");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_div( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal operator /( mpfr_srcptr src ) {
			static const std::string S_ProcName("operator/-mpfr_srcptr");
			if( src == NULL ) {
				TCFLibBigDecimal<tDigits,tPrecis> retval;
				return( retval );
			}
			else {
				mpfr_t tmp;
				mpfr_init2( tmp, BITS_REQUIRED );
				clearFlags();
				int mpfrTernary = mpfr_div( tmp, val, src, MPFR_RNDN );
				// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
				analyseFlags( S_ProcName, tmp );
				checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
				TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
				mpfr_clear( tmp );
				return( retval );
			}
		}

		TCFLibBigDecimal operator /( unsigned long int src ) {
			static const std::string S_ProcName("operator/-unsigned-long-int");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_div_ui( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal operator /( long int src ) {
			static const std::string S_ProcName("operator/-long-int");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_div_si( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal operator /( double src ) {
			static const std::string S_ProcName("operator/-double");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_div_d( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		/**
		 *	Remainder and assign operators for various mpfr_t, mpfr_srcptr,
		 *	unsigned long int, long int, double,
		 *	CFLibGenericBigDecimal, and	TCFLibBigDecimal
		 *	arguments.
		 */
		TCFLibBigDecimal<tDigits,tPrecis>& operator %=( const CFLibGenericBigDecimal& src ) {
			static const std::string S_ProcName("operator%=-CFLibGenericBigDecimal");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_remainder( tmp, val, src.getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator %=( const TCFLibBigDecimal& src ) {
			static const std::string S_ProcName("operator%=-TCFLibBigDecimal");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_remainder( tmp, val, src.getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator %=( const mpfr_t& src ) {
			static const std::string S_ProcName("operator%=-mpfr_t");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_remainder( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator %=( mpfr_srcptr src ) {
			static const std::string S_ProcName("operator%=-mpfr_srcptr");
			if( src == NULL ) {
				mpfr_set_nan( val );
			}
			else {
				mpfr_t tmp;
				mpfr_init2( tmp, BITS_REQUIRED );
				clearFlags();
				int mpfrTernary = mpfr_remainder( tmp, val, src, MPFR_RNDN );
				// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
				analyseFlags( S_ProcName, tmp );
				checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
				mpfr_set( val, tmp, MPFR_RNDN );
				cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
				mpfr_clear( tmp );
			}
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator %=( unsigned long int src ) {
			static const std::string S_ProcName("operator%=-unsigned-long-int");
			mpfr_t tmpval;
			mpfr_init2( tmpval, sizeof( unsigned long int ) * 8 + 4 );
			clearFlags();
			mpfr_set_ui( tmpval, src, MPFR_RNDN );
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_remainder( tmp, val, tmpval, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp, tmpval );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			mpfr_clear( tmpval );
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator %=( long int src ) {
			static const std::string S_ProcName("operator%=-long-int");
			mpfr_t tmpval;
			mpfr_init2( tmpval, sizeof( long int ) * 8 + 4 );
			clearFlags();
			mpfr_set_si( tmpval, src, MPFR_RNDN );
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_remainder( tmp, val, tmpval, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp, tmpval );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			mpfr_clear( tmpval );
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator %=( double src ) {
			static const std::string S_ProcName("operator%=-double");
			mpfr_t tmpval;
			mpfr_init2( tmpval, sizeof( double ) * 8 * 2 );
			clearFlags();
			mpfr_set_d( tmpval, src, MPFR_RNDN );
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_remainder( tmp, val, tmpval, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp, tmpval );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			mpfr_clear( tmpval );
			return( *this );
		}

		/**
		 *	Remainder operators
		 */
		TCFLibBigDecimal operator %( const CFLibGenericBigDecimal& src ) {
			static const std::string S_ProcName("operator%-CFLibGenericBigDecimal");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_remainder( tmp, val, src.getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal operator %( const TCFLibBigDecimal& src ) {
			static const std::string S_ProcName("operator%-TCFLibBigDecimal");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_remainder( tmp, val, src.getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal operator %( const mpfr_t& src ) {
			static const std::string S_ProcName("operator%-mpfr_t");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_remainder( tmp, val, src, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal operator %( mpfr_srcptr src ) {
			static const std::string S_ProcName("operator%-mpfr_srcptr");
			if( src == NULL ) {
				TCFLibBigDecimal<tDigits,tPrecis> retval;
				return( retval );
			}
			else {
				mpfr_t tmp;
				mpfr_init2( tmp, BITS_REQUIRED );
				clearFlags();
				int mpfrTernary = mpfr_remainder( tmp, val, src, MPFR_RNDN );
				// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
				analyseFlags( S_ProcName, tmp );
				checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
				TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
				mpfr_clear( tmp );
				return( retval );
			}
		}

		TCFLibBigDecimal operator %( unsigned long int src ) {
			static const std::string S_ProcName("operator%-unsigned-long-int");
			mpfr_t tmpval;
			mpfr_init2( tmpval, sizeof( unsigned long int ) * 8 + 4 );
			clearFlags();
			mpfr_set_ui( tmpval, src, MPFR_RNDN );
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_remainder( tmp, val, tmpval, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
			mpfr_clear( tmp );
			mpfr_clear( tmpval );
			return( retval );
		}

		TCFLibBigDecimal operator %( long int src ) {
			static const std::string S_ProcName("operator%-long-int");
			mpfr_t tmpval;
			mpfr_init2( tmpval, sizeof( long int ) * 8 + 4 );
			clearFlags();
			mpfr_set_si( tmpval, src, MPFR_RNDN );
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_remainder( tmp, val, tmpval, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
			mpfr_clear( tmp );
			mpfr_clear( tmpval );
			return( retval );
		}

		TCFLibBigDecimal operator %( double src ) {
			static const std::string S_ProcName("operator%-double");
			mpfr_t tmpval;
			mpfr_init2( tmpval, sizeof( double ) * 8 * 2 );
			clearFlags();
			mpfr_set_d( tmpval, src, MPFR_RNDN );
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_remainder( tmp, val, tmpval, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tDigits,tPrecis> retval( tmp );
			mpfr_clear( tmp );
			mpfr_clear( tmpval );
			return( retval );
		}

		/**
		 *	Prefix increment and decrement operators.
		 */
		TCFLibBigDecimal<tDigits,tPrecis>& operator++() {
			static const std::string S_ProcName("operator++prefix");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_add_si( tmp, val, 1L, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( *this );
		}

		TCFLibBigDecimal<tDigits,tPrecis>& operator--() {
			static const std::string S_ProcName("operator--prefix");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_sub_si( tmp, val, 1L, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( *this );
		}

		/**
		 *	Postfix increment and decrement operators.
		 */
		TCFLibBigDecimal operator++( int dummy ) {
			static const std::string S_ProcName("operator++postfix");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_add_si( tmp, val, 1L, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tPrecis,tDigits> retval( *this );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal operator--( int dummy ) {
			static const std::string S_ProcName("operator--postfix");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_sub_si( tmp, val, 1L, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<tPrecis,tDigits> retval( *this );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( retval );
		}

		/**
		 *	Template class methods
		 */
		static const std::string& getNumberFormat() {
			static std::string* strNumberFormat = NULL;
			if( strNumberFormat == NULL ) {
				char fmtbuff[16] = { 0 };
				sprintf(&fmtbuff[0], "%%.%dRf", precis );
				strNumberFormat = new std::string( fmtbuff );
			}
			return(*strNumberFormat );
		}

		/**
		 *	Get the minimum value allowed by this
		 *	template as an mpfr_srcptr.
		 */
		virtual mpfr_srcptr getMinValue() const {
			return( getAbsoluteMinValue());
		}

		/**
		 *	Get the maximum value allowed by this
		 *	template as an mpfr_srcptr.
		 */
		virtual mpfr_srcptr getMaxValue() const {
			return( getAbsoluteMaxValue());
		}

		/**
		 *	The coerce APIs provide an enhanced constructor for
		 *	reporting constraint violations in terms of an optional
		 *	field or class name instead of a hard-coded class name,
		 *	a version of those methods that uses a hard-coded field
		 *	name as a default, and any of CFLibGenericBigDecimal&,
		 *	TCFLibBigDecimal, mpfr_t&, mpfr_srcptr, returning an
		 *	instance of this template that has been range-checked
		 *	and rounded as an instance of this template.
		 */
		static TCFLibBigDecimal<tDigits,tPrecis>* coerce( const std::string& fieldOrClassName, const TCFLibBigDecimal& value ) {
			static const std::string S_ProcName("coerce");
			mpfr_srcptr srcValue = value.getValue();
			checkAbsoluteRange( S_ProcName, 0, S_Src, srcValue );
			return( new TCFLibBigDecimal<tDigits,tPrecis>( srcValue ) );
		}

		static TCFLibBigDecimal<tDigits,tPrecis>* coerce( const std::string& fieldOrClassName, const CFLibGenericBigDecimal& value ) {
			static const std::string S_ProcName("coerce");
			mpfr_srcptr srcValue = value.getValue();
			checkAbsoluteRange( S_ProcName, 0, S_Src, srcValue );
			return( new TCFLibBigDecimal<tDigits,tPrecis>( srcValue ) );
		}

		static TCFLibBigDecimal<tDigits,tPrecis>* coerce( CFLibGenericBigDecimal& value ) {
			return( coerce( S_Field, value ));
		}

		static TCFLibBigDecimal<tDigits,tPrecis>* coerce( const std::string& fieldOrClassName, const CFLibGenericBigDecimal* value ) {
			static const std::string S_ProcName("coerce");
			if( value == NULL ) {
				return( NULL );
			}
			mpfr_srcptr srcValue = value->getValue();
			TCFLibBigDecimal<tDigits,tPrecis>* retval = new TCFLibBigDecimal<tDigits,tPrecis>( srcValue );
			return( retval );
		}

		static TCFLibBigDecimal<tDigits,tPrecis>* coerce( const CFLibGenericBigDecimal* value ) {
			return( coerce( S_Field, value ));
		}

		static mpfr_ptr coerce( const std::string& fieldOrClassName, mpfr_srcptr value ) {
			static const std::string S_ProcName("coerce");
			if( value == NULL ) {
				return( NULL );
			}
			mpfr_ptr retval = new mpfr_t;
			mpfr_init2( retval, BITS_REQUIRED );
			clearFlags();
			mpfr_set( retval, value, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( retval, precis );
			return( retval );
		}

		static mpfr_ptr coerce( mpfr_srcptr value ) {
			return( coerce( S_Field, value ));
		}

		/**
		 *	Parse a number expressed as a signed decimal fraction
		 *	string and assign it to a new mpfr value instance returned
		 *	by the parse.  If the value string is NULL or empty,
		 *	return NULL.  The first argument may be an optional
		 *	field or class name to use instead of the hard-coded
		 *	default "field", with string reference or string pointer
		 *	arguments to be evaluated.
		 */
		static TCFLibBigDecimal<tDigits,tPrecis>* parse( const std::string& fieldOrClassName, const std::string& value ) {
			static const std::string S_ProcName("parse");
			if( value.length() <= 0 ) {
				return( NULL );
			}
			if( 0 == value.compare( S_Null )) {
				return( NULL );
			}
			else if( 0 == value.compare( S_LowerNull )) {
				return( NULL );
			}
			TCFLibBigDecimal<tDigits,tPrecis>* retval = new TCFLibBigDecimal<tDigits,tPrecis>( value );
			return( retval );
		}

		static TCFLibBigDecimal<tDigits,tPrecis>* parse( const std::string& value ) {
			return( parse( S_Field, value ));
		}

		static TCFLibBigDecimal<tDigits,tPrecis>* parse( const std::string& fieldOrClassName, const std::string* value ) {
			if( ( value == NULL ) || ( value->length() <= 0 )) {
				return( NULL );
			}
			else {
				return( parse( fieldOrClassName, *value ));
			}
		}

		static TCFLibBigDecimal<tDigits,tPrecis>* parse( const std::string* value ) {
			if( ( value == NULL ) || ( value->length() <= 0 )) {
				return( NULL );
			}
			else {
				return( parse( S_Field, *value ));
			}
		}

		/**
		 *	Convert the specified value to a signed decimal fraction
		 *	string, with appropriate digits of precision for this
		 *	template's parameters.
		 *
		 *		fieldOrClassName - the required name of the field or invoking class
		 *
		 *		value - the mpfr_t or mpfr_srcptr value to be formatted into a
		 *			signed decimal fraction string with the number of fractional
		 *			digits specified by this template's parameters.  A NULL srcptr
		 *			results in an empty string being returned.
		 */
		static std::string toString( const std::string& fieldOrClassName, const mpfr_t& value ) {
			static const std::string S_ProcName("toString");
			const std::string& fmt = getNumberFormat();
			char fmtBuff[MAX_DIGITS + MAX_DIGITS] = { 0 };
			mpfr_sprintf( fmtBuff, fmt.c_str(), value );
			std::string retval( fmtBuff );
			return( retval );
		}

		static std::string toString( const mpfr_t& value ) {
			return( toString( S_Field, value ));
		}

		static std::string toString( const std::string& fieldOrClassName, mpfr_srcptr value ) {
			std::string retval;
			if( value != NULL ) {
				retval = toString( fieldOrClassName, *value );
			}
			return( retval );
		}

		static std::string toString( mpfr_srcptr value ) {
			std::string retval;
			if( value != NULL ) {
				retval = toString( S_Field, *value );
			}
			return( retval );
		}

		/**
		 *	One of the more common interpretation of toString() in manufactured
		 *	code is to return the signed decimal fraction string representing
		 *	this instance's value.
		 *
		 *		fieldOrClassName - the required name of the field or invoking class
		 */
		virtual std::string toString( const std::string& fieldOrClassName ) const {
			std::string retval;
			if( val == NULL ) {
				retval = std::string();
			}
			else {
				const std::string& fmt = getNumberFormat();
				char fmtBuff[MAX_DIGITS + MAX_DIGITS] = { 0 };
				mpfr_sprintf( fmtBuff, fmt.c_str(), val );
				retval = std::string( fmtBuff );
			}
			return( retval );
		}

		/**
		 *	The most common interpretation of toString() by a C++ or Java
		 *	programmer is to expect to get the signed decimal fractions string
		 *	representing this instance's value without providing any extra
		 *	arguments at all.
		 */
		virtual std::string toString() const {
			std::string retval;
			if( val == NULL ) {
				retval = std::string();
			}
			else {
				const std::string& fmt = getNumberFormat();
				char fmtBuff[MAX_DIGITS + MAX_DIGITS] = { 0 };
				mpfr_sprintf( fmtBuff, fmt.c_str(), val );
				retval = std::string( fmtBuff );
			}
			return( retval );
		}

		virtual int checkRange( int t, mpfr_rnd_t rnd = MPFR_RNDN ) {
			return( mpfr_check_range( val, t, rnd ) );
		}

		virtual mpfr_prec_t minPrec() const {
			return( mpfr_min_prec( val ) );
		}

		virtual mpfr_exp_t getExp() const {
			return( mpfr_get_exp( val ) );
		}

		virtual mpfr_prec_t getPrec() const {
			return( mpfr_get_prec( val ) );
		}

		virtual int set2Exp( long value,
			mpfr_exp_t exp,
			mpfr_rnd_t rnd = MPFR_RNDN )
		{
			static const std::string S_ProcName("set2Exp");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_set_si_2exp( tmp, value, exp, rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( mpfrTernary );
		}

		virtual int set2Exp( unsigned long value,
			mpfr_exp_t exp,
			mpfr_rnd_t rnd = MPFR_RNDN )
		{
			static const std::string S_ProcName("set2Exp");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_set_ui_2exp( tmp, value, exp, rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			mpfr_set( val, tmp, MPFR_RNDN );
			cflib::CFLibGenericBigDecimal::precisionRounding( val, precis );
			mpfr_clear( tmp );
			return( mpfrTernary );
		}

		TCFLibBigDecimal abs() const {
			static const std::string S_ProcName("abs");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_abs( tmp, val, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal neg() const {
			static const std::string S_ProcName("net");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_neg( tmp, val, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		virtual bool isNegative() const {
			static const std::string S_ProcName("isNegative");
			if( mpfr_signbit( val ) ) {
				return( true );
			}
			else {
				return( false );
			}
		}

		virtual mpfr_exp_t getZ2Exp( mpz_ptr p ) const {
			static const std::string S_ProcName("getZ2Exp");
			if( p == NULL ) {
				throw CFLibNullArgumentException( CLASSNAME_TCFLIBBIGDECIMAL,
					S_ProcName,
					1,
					S_P );
			}
			mpfr_exp_t retval = mpfr_get_z_2exp( p, val );
			return( retval );
		}

		virtual float getFloat() {
			float retval = mpfr_get_flt( val, MPFR_RNDN );
			return( retval );
		}

		virtual float getDouble() {
			double retval = mpfr_get_d( val, MPFR_RNDN );
			return( retval );
		}

		virtual long double getLongDouble() {
			long double retval = mpfr_get_ld( val, MPFR_RNDN );
			return( retval );
		}

		virtual double getDouble2Exp( long * p ) const {
			static const std::string S_ProcName("getDouble2Exp");
			if( p == NULL ) {
				throw CFLibNullArgumentException( CLASSNAME_TCFLIBBIGDECIMAL,
					S_ProcName,
					1,
					S_P );
			}
			double retval = mpfr_get_d_2exp( p, val, MPFR_RNDN );
			return( retval );
		}

		virtual long double getLongDouble2Exp( long * p ) const {
			static const std::string S_ProcName("getLongDouble2Exp");
			if( p == NULL ) {
				throw CFLibNullArgumentException( CLASSNAME_TCFLIBBIGDECIMAL,
					S_ProcName,
					1,
					S_P );
			}
			double retval = mpfr_get_ld_2exp( p, val, MPFR_RNDN );
			return( retval );
		}

		virtual long getSignedInteger()  const {
			long retval = mpfr_get_si( val, MPFR_RNDN );
			return( retval );
		}

		virtual long getUnsignedInteger()  const {
			long retval = mpfr_get_ui( val, MPFR_RNDN );
			return( retval );
		}

		virtual mpfr_exp_t getZ( mpz_ptr p ) const {
			static const std::string S_ProcName("getZ");
			if( p == NULL ) {
				throw CFLibNullArgumentException( CLASSNAME_TCFLIBBIGDECIMAL,
					S_ProcName,
					1,
					S_P );
			}
			mpfr_exp_t retval = mpfr_get_z( p, val, MPFR_RNDN );
			return( retval );
		}

		static TCFLibBigDecimal uRandom( gmp_randstate_t randstate ) {
			static const std::string S_ProcName("uRandom");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_urandom( tmp, randstate, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		static TCFLibBigDecimal nRandom( gmp_randstate_t randstate ) {
			static const std::string S_ProcName("nRandom");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_nrandom( tmp, randstate, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		static TCFLibBigDecimal eRandom( gmp_randstate_t randstate ) {
			static const std::string S_ProcName("eRandom");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_erandom( tmp, randstate, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		static TCFLibBigDecimal uRandomB( gmp_randstate_t randstate ) {
			static const std::string S_ProcName("uRandomB");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_urandomb( tmp, randstate );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal& nextAbove() {
			static const std::string S_ProcName("nextAbove");
			mpfr_nextabove( val );
			analyseFlags( S_ProcName, val );
			checkAbsoluteRange( S_ProcName, 0, S_Value, val );
			return( this );
		}

		TCFLibBigDecimal& nextBelow() {
			static const std::string S_ProcName("nextBelow");
			mpfr_nextbelow( val );
			analyseFlags( S_ProcName, val );
			checkAbsoluteRange( S_ProcName, 0, S_Value, val );
			return( this );
		}

		TCFLibBigDecimal& nextToward( const CFLibGenericBigDecimal& arg ) {
			static const std::string S_ProcName("nextToward");
			mpfr_nexttoward( val, arg.getValue() );
			analyseFlags( S_ProcName, val );
			checkAbsoluteRange( S_ProcName, 0, S_Value, val );
			return( this );
		}

		TCFLibBigDecimal pow( const CFLibGenericBigDecimal& value ) const {
			static const std::string S_ProcName("pow-CFLibGenericBigDecimal");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_pow( tmp, val, value.getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal pow( unsigned long value ) const {
			static const std::string S_ProcName("pow-ulong");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_pow_ui( tmp, val, value, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal pow( long value ) const {
			static const std::string S_ProcName("pow-long");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_pow_si( tmp, val, value, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal pow( mpz_t value ) const {
			static const std::string S_ProcName("pow-Z");
			if( value == NULL ) {
				throw CFLibNullArgumentException( CLASSNAME_TCFLIBBIGDECIMAL,
					S_ProcName,
					1,
					S_Value );
			}
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_pow_z( tmp, val, value, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		static TCFLibBigDecimal uiPow( unsigned long value, unsigned long exp ) {
			static const std::string S_ProcName("uiPow-long");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_ui_pow_ui( tmp, value, exp, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		static TCFLibBigDecimal uiPow( unsigned long value, const CFLibGenericBigDecimal& exp ) {
			static const std::string S_ProcName("uiPow-CFLibGenericBigDecimal");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_ui_pow_ui( tmp, value, exp.getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal squareRoot() const {
			static const std::string S_ProcName("squareRoot");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_sqrt( tmp, getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal squareRoot( unsigned long value ) const {
			static const std::string S_ProcName("squareRoot");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_sqrt_ui( tmp, getValue(), value, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal reciprocalSquareRoot() const {
			static const std::string S_ProcName("reciprocalSquareRoot");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_rec_sqrt( tmp, getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal cubicSquareRoot() const {
			static const std::string S_ProcName("cubicSquareRoot");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_cbrt( tmp, getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal rootN( unsigned long int value ) const {
			static const std::string S_ProcName("rootN");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_rootn_ui( tmp, getValue(), value, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal root( unsigned long int value ) const {
			static const std::string S_ProcName("root");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_root( tmp, getValue(), value, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal square() const {
			static const std::string S_ProcName("square");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_sqr( tmp, getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		static TCFLibBigDecimal constPi() {
			static const std::string S_ProcName("constPi");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_const_pi( tmp, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		static TCFLibBigDecimal constLog2() {
			static const std::string S_ProcName("constLog2");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_const_log2( tmp, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		static TCFLibBigDecimal constEuler() {
			static const std::string S_ProcName("constEuler");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_const_euler( tmp, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		static TCFLibBigDecimal constCatalan() {
			static const std::string S_ProcName("constCatalan");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_const_catalan( tmp, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal arithmeticGeometricMean( const CFLibGenericBigDecimal& value ) const {
			static const std::string S_ProcName("arithmeticGeometricMean");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_agm( tmp, getValue(), value.getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal log() const {
			static const std::string S_ProcName("log");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_log( tmp, getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		static TCFLibBigDecimal log( unsigned long value ) {
			static const std::string S_ProcName("log-ulong");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_log_ui( tmp, value, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal log2() const {
			static const std::string S_ProcName("log2");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_log2( tmp, getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal log10() const {
			static const std::string S_ProcName("log10");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_log10( tmp, getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal log1p() const {
			static const std::string S_ProcName("log1p");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_log1p( tmp, getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal exp() const {
			static const std::string S_ProcName("exp");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_exp( tmp, getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal exp2() const {
			static const std::string S_ProcName("exp2");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_exp2( tmp, getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal exp10() const {
			static const std::string S_ProcName("exp10");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_exp10( tmp, getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal expM1() const {
			static const std::string S_ProcName("expM1");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_expm1( tmp, getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal eInt() const {
			static const std::string S_ProcName("eInt");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_eint( tmp, getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal li2() const {
			static const std::string S_ProcName("li2");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_li2( tmp, getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal relDiff( const CFLibGenericBigDecimal& value ) const {
			static const std::string S_ProcName("relDiff");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_reldiff( tmp, getValue(), value.getValue(), MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		virtual int sign() const {
			return( mpfr_sgn( val ) );
		}

		TCFLibBigDecimal mul2( long int value ) const {
			static const std::string S_ProcName("mul2-long");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_mul_2si( tmp, getValue(), value, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal mul2( unsigned long int value ) const {
			static const std::string S_ProcName("mul2-ulong");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_mul_2ui( tmp, getValue(), value, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal div2( long int value ) const {
			static const std::string S_ProcName("div2-long");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_div_2si( tmp, getValue(), value, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal div2( unsigned long int value ) const {
			static const std::string S_ProcName("div2-ulong");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_div_2ui( tmp, getValue(), value, MPFR_RNDN );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal rint( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("rint");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_rint( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal ceil() const {
			static const std::string S_ProcName("ceil");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_ceil( tmp, getValue() );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal floor() const {
			static const std::string S_ProcName("floor");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_floor( tmp, getValue() );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal round() const {
			static const std::string S_ProcName("round");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_round( tmp, getValue() );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal roundEven() const {
			static const std::string S_ProcName("roundEven");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_roundeven( tmp, getValue() );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal trunc() const {
			static const std::string S_ProcName("trunc");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_trunc( tmp, getValue() );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal rintCeil( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("rintCeil");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_rint_ceil( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal rintFloor( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("rintFloor");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_rint_floor( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal rintRound( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("rintRound");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_rint_round( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal rintRoundEven( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("roundEven");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_rint_roundeven( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal rintTrunc( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("rintTrunc");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_rint_trunc( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal frac( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("frac");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_frac( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		virtual bool fitsLong( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			if( mpfr_fits_slong_p( val, rnd ) ) {
				return( true );
			}
			else {
				return( false );
			}
		}

		virtual bool fitsULong( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			if( mpfr_fits_ulong_p( val, rnd ) ) {
				return( true );
			}
			else {
				return( false );
			}
		}

		virtual bool fitsInt( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			if( mpfr_fits_sint_p( val, rnd ) ) {
				return( true );
			}
			else {
				return( false );
			}
		}

		virtual bool fitsUInt( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			if( mpfr_fits_uint_p( val, rnd ) ) {
				return( true );
			}
			else {
				return( false );
			}
		}

		virtual bool fitsShort( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			if( mpfr_fits_sshort_p( val, rnd ) ) {
				return( true );
			}
			else {
				return( false );
			}
		}

		virtual bool fitsUShort( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			if( mpfr_fits_ushort_p( val, rnd ) ) {
				return( true );
			}
			else {
				return( false );
			}
		}

		virtual bool fitsUIntMax( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			if( mpfr_fits_uintmax_p( val, rnd ) ) {
				return( true );
			}
			else {
				return( false );
			}
		}

		virtual bool fitsIntMax( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			if( mpfr_fits_intmax_p( val, rnd ) ) {
				return( true );
			}
			else {
				return( false );
			}
		}

		virtual bool isUnordered( const CFLibGenericBigDecimal& value ) const {
			if( mpfr_unordered_p( val, value.getValue() ) ) {
				return( true );
			}
			else {
				return( false );
			}
		}

		TCFLibBigDecimal modf( TCFLibBigDecimal& value, mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("modf");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_modf( tmp, getValue(), value.val, rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal fmod( const CFLibGenericBigDecimal& value, mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("fmod");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_fmod( tmp, getValue(), value.getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal fmodQuo( const CFLibGenericBigDecimal& value, mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("fmodQuo");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_fmodquo( tmp, getValue(), value.getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal remainder( const CFLibGenericBigDecimal& value, mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("remainder");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_remainder( tmp, getValue(), value.getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal remQuo( const CFLibGenericBigDecimal& value, mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("remQuo");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_remquo( tmp, getValue(), value.getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		virtual bool greaterThan( const CFLibGenericBigDecimal& value ) const {
			if( mpfr_greater_p( getValue(), value.getValue() ) ) {
				return( true );
			}
			else {
				return( false );
			}
		}

		virtual bool greaterOrEqual( const CFLibGenericBigDecimal& value ) const {
			if( mpfr_greaterequal_p( getValue(), value.getValue() ) ) {
				return( true );
			}
			else {
				return( false );
			}
		}

		virtual bool lessThan( const CFLibGenericBigDecimal& value ) const {
			if( mpfr_less_p( getValue(), value.getValue() ) ) {
				return( true );
			}
			else {
				return( false );
			}
		}

		virtual bool lessOrEqual( const CFLibGenericBigDecimal& value ) const {
			if( mpfr_lessequal_p( getValue(), value.getValue() ) ) {
				return( true );
			}
			else {
				return( false );
			}
		}

		virtual bool equal( const CFLibGenericBigDecimal& value ) const {
			if( mpfr_equal_p( getValue(), value.getValue() ) ) {
				return( true );
			}
			else {
				return( false );
			}
		}

		virtual void dump() const {
			mpfr_dump( getValue() );
		}

		TCFLibBigDecimal atanh( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("atanh");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_atanh( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal acosh( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("acosh");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_acosh( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal asinh( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("asinh");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_asinh( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal cosh( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("cosh");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_cosh( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal sinh( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("sinh");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_sinh( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal tanh( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("tanh");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_tanh( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal sech( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("sech");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_sech( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal csch( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("csch");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_csch( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal coth( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("coth");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_coth( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal acos( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("acos");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_acos( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal asin( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("asin");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_asin( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal atan( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("atan");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_atan( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal sin( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("sin");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_sin( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal cos( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("cos");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_cos( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal tan( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("tan");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_tan( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal sec( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("sec");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_sec( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal csc( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("csc");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_csc( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal cot( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("cot");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_cot( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal sinhCosh( TCFLibBigDecimal& value, mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("sinhCosh");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_sinh_cosh( tmp, value.val, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal sinCos( TCFLibBigDecimal& value, mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("sinCos");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_sin_cos( tmp, value.val, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal atan2( const CFLibGenericBigDecimal& value, mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("atan2");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_atan2( tmp, getValue(), value.getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal hypot( const CFLibGenericBigDecimal& value, mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("hypot");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_hypot( tmp, getValue(), value.getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal erf( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("erf");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_erf( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal erfc( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("erfc");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_erfc( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal gamma( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("gamma");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_gamma( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal gamma( int* p, mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("gamma-long");
			if( p == NULL ) {
				throw CFLibNullArgumentException( CLASSNAME_TCFLIBBIGDECIMAL,
					S_ProcName,
					1,
					S_P );
			}
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_lgamma( tmp, p, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal gammaInc( const CFLibGenericBigDecimal& value, mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("gammaInc");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_gamma_inc( tmp, getValue(), value.getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal lngamma( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("lngamma");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_lngamma( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal digamma( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("digamma");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_digamma( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal beta( const CFLibGenericBigDecimal& value, mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("beta");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_beta( tmp, getValue(), value.getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal zeta( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("zeta");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_zeta( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal zeta( unsigned long value, mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("zeta-long");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_zeta_ui( tmp, value, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal fac( unsigned long value, mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("fac");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_fac_ui( tmp, value, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal j0( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("j0");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_j0( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal j1( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("j1");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_j1( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal jn( long value, mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("jn");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_jn( tmp, value, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal y0( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("y0");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_y0( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal y1( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("y1");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_y1( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal yn( long value, mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("yn");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_yn( tmp, value, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal ai( mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("ai");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_ai( tmp, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal min( const CFLibGenericBigDecimal& value, mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("min");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_min( tmp, getValue(), value.getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal max( const CFLibGenericBigDecimal& value, mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("max");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_max( tmp, getValue(), value.getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal dim( const CFLibGenericBigDecimal& value, mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("dim");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_dim( tmp, getValue(), value.getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal mul( mpz_srcptr p, mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("mul");
			if( p == NULL ) {
				throw CFLibNullArgumentException( CLASSNAME_TCFLIBBIGDECIMAL,
					S_ProcName,
					1,
					S_P );
			}
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_mul_z( tmp, getValue(), p, rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal div( mpz_srcptr p, mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("div");
			if( p == NULL ) {
				throw CFLibNullArgumentException( CLASSNAME_TCFLIBBIGDECIMAL,
					S_ProcName,
					1,
					S_P );
			}
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_div_z( tmp, getValue(), p, rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal sub( mpz_srcptr p, mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("sub");
			if( p == NULL ) {
				throw CFLibNullArgumentException( CLASSNAME_TCFLIBBIGDECIMAL,
					S_ProcName,
					1,
					S_P );
			}
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_sub_z( tmp, getValue(), p, rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal zsub( mpz_srcptr p, mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("zsub");
			if( p == NULL ) {
				throw CFLibNullArgumentException( CLASSNAME_TCFLIBBIGDECIMAL,
					S_ProcName,
					1,
					S_P );
			}
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_z_sub( tmp, p, getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		int cmp( mpz_srcptr p ) const {
			static const std::string S_ProcName("cmp");
			if( p == NULL ) {
				throw CFLibNullArgumentException( CLASSNAME_TCFLIBBIGDECIMAL,
					S_ProcName,
					1,
					S_P );
			}
			int mpfrTernary = mpfr_cmp_z( getValue(), p );
			return( mpfrTernary );
		}

		TCFLibBigDecimal subnormalize( int value, mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("subnormalize");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_subnormalize( tmp, getValue(), value, rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal strtofr( const char *value, char **p, int base, mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("strtofr");
			if( value == NULL ) {
				throw CFLibNullArgumentException( CLASSNAME_TCFLIBBIGDECIMAL,
					S_ProcName,
					1,
					S_Value );
			}
			if( p == NULL ) {
				throw CFLibNullArgumentException( CLASSNAME_TCFLIBBIGDECIMAL,
					S_ProcName,
					2,
					S_P );
			}
			if( base < 0 ) {
				throw CFLibArgumentUnderflowException( CLASSNAME_TCFLIBBIGDECIMAL,
					S_ProcName,
					3,
					S_Base,
					base,
					0 );
			}
			if( base > 62 ) {
				throw CFLibArgumentOverflowException( CLASSNAME_TCFLIBBIGDECIMAL,
					S_ProcName,
					3,
					S_Base,
					base,
					62 );
			}
			if( base == 1 ) {
				throw CFLibInvalidArgumentException( CLASSNAME_TCFLIBBIGDECIMAL,
					S_ProcName,
					S_BaseArg3CannotBeOne );
			}
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_strtofr( tmp, value, p, base, rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal fma( const CFLibGenericBigDecimal& value, const CFLibGenericBigDecimal& p, mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("fma");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_fma( tmp, getValue(), value.getValue(), p.getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal fms( const CFLibGenericBigDecimal& value, const CFLibGenericBigDecimal& p, mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("fms");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_fms( tmp, getValue(), value.getValue(), p.getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal fmma( const CFLibGenericBigDecimal& value, const CFLibGenericBigDecimal& m, const CFLibGenericBigDecimal& p, mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("fmma");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_fmma( tmp, getValue(), value.getValue(), m.getValue(), p.getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}

		TCFLibBigDecimal fmms( const CFLibGenericBigDecimal& value, const CFLibGenericBigDecimal& m, const CFLibGenericBigDecimal& p, mpfr_rnd_t rnd = MPFR_RNDN ) const {
			static const std::string S_ProcName("fmms");
			mpfr_t tmp;
			mpfr_init2( tmp, BITS_REQUIRED );
			clearFlags();
			int mpfrTernary = mpfr_fmms( tmp, getValue(), value.getValue(), m.getValue(), p.getValue(), rnd );
			// analyseMpfrTernary( S_ProcName, mpfrTernary, tmp );
			analyseFlags( S_ProcName, tmp );
			checkAbsoluteRange( S_ProcName, 0, S_Tmp, tmp, tmp );
			TCFLibBigDecimal<digits,precis> retval( tmp );
			mpfr_clear( tmp );
			return( retval );
		}
	};
	typedef TCFLibBigDecimal<1,0> BigInteger1;
	typedef TCFLibBigDecimal<2,0> BigInteger2;
	typedef TCFLibBigDecimal<3,0> BigInteger3;
	typedef TCFLibBigDecimal<4,0> BigInteger4;
	typedef TCFLibBigDecimal<5,0> BigInteger5;
	typedef TCFLibBigDecimal<6,0> BigInteger6;
	typedef TCFLibBigDecimal<7,0> BigInteger7;
	typedef TCFLibBigDecimal<8,0> BigInteger8;
	typedef TCFLibBigDecimal<9,0> BigInteger9;
	typedef TCFLibBigDecimal<10,0> BigInteger10;
	typedef TCFLibBigDecimal<11,0> BigInteger11;
	typedef TCFLibBigDecimal<12,0> BigInteger12;
	typedef TCFLibBigDecimal<13,0> BigInteger13;
	typedef TCFLibBigDecimal<14,0> BigInteger14;
	typedef TCFLibBigDecimal<15,0> BigInteger15;
	typedef TCFLibBigDecimal<16,0> BigInteger16;
	typedef TCFLibBigDecimal<17,0> BigInteger17;
	typedef TCFLibBigDecimal<18,0> BigInteger18;
	typedef TCFLibBigDecimal<19,0> BigInteger19;
	typedef TCFLibBigDecimal<20,0> BigInteger20;
	typedef TCFLibBigDecimal<21,0> BigInteger21;
	typedef TCFLibBigDecimal<22,0> BigInteger22;
	typedef TCFLibBigDecimal<23,0> BigInteger23;
	typedef TCFLibBigDecimal<24,0> BigInteger24;
	typedef TCFLibBigDecimal<25,0> BigInteger25;
	typedef TCFLibBigDecimal<26,0> BigInteger26;
	typedef TCFLibBigDecimal<27,0> BigInteger27;
	typedef TCFLibBigDecimal<28,0> BigInteger28;
	typedef TCFLibBigDecimal<29,0> BigInteger29;
	typedef TCFLibBigDecimal<30,0> BigInteger30;
	typedef TCFLibBigDecimal<31,0> BigInteger31, BigInteger;
}
