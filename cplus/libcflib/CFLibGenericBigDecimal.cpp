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
#include <cflib/TCFLibBigDecimal.hpp>

namespace cflib {

	const std::string CFLibGenericBigDecimal::CLASS_NAME("CFLibGenericBigDecimal");
	const std::string CFLibGenericBigDecimal::CLASSNAME_TCFLIBBIGDECIMAL( "TCFLibBigDecimal" );
	const std::string CFLibGenericBigDecimal::S_Digits( "digits" );
	const std::string CFLibGenericBigDecimal::S_Field( "field" );
	const std::string CFLibGenericBigDecimal::S_Precis( "precis" );
	const std::string CFLibGenericBigDecimal::S_Value( "value" );
	const std::string CFLibGenericBigDecimal::S_Null( "NULL" );
	const std::string CFLibGenericBigDecimal::S_Base( "base" );
	const std::string CFLibGenericBigDecimal::S_P( "p" );
	const std::string CFLibGenericBigDecimal::S_LowerNull("null");
	const std::string CFLibGenericBigDecimal::S_Src( "src" );
	const std::string CFLibGenericBigDecimal::S_Tmp( "tmp" );
	const std::string CFLibGenericBigDecimal::S_Underflow( "MPFR function raised an underflow" );
	const std::string CFLibGenericBigDecimal::S_Overflow( "MPFR function raised an overflow" );
	const std::string CFLibGenericBigDecimal::S_NaN( "MPFR function raised not a number" );
	const std::string CFLibGenericBigDecimal::S_ERange( "MPFR function raised a range error" );
	const std::string CFLibGenericBigDecimal::S_DivBy0( "MPFR function raised division by zero" );
	const std::string CFLibGenericBigDecimal::S_MpfrSetStrFailure( "Bad input string" );
	const std::string CFLibGenericBigDecimal::S_MpfrFlagsTestFailure( "MPFR function mpfr_flags_test() returned an unrecognized bit flag" );
	const std::string CFLibGenericBigDecimal::S_MpfrFunctionRoundedDown( "MPFR function rounded down the result" );
	const std::string CFLibGenericBigDecimal::S_MpfrFunctionRoundedUp( "MPFR function rounded up the result" );
	const std::string CFLibGenericBigDecimal::S_MpfrSetStr( "mpfr_set_str" );
	const std::string CFLibGenericBigDecimal::S_BaseArg3CannotBeOne( "base (arg 3) cannot be 1" );

	const int CFLibGenericBigDecimal::MIN_DIGITS = 1;
	const int CFLibGenericBigDecimal::MAX_DIGITS = ((( MPFR_PREC_MAX / 8 ) - 1) > 1990 ) ? 1990 : ((int)(( MPFR_PREC_MAX / 8 ) - 1 ));
	const int CFLibGenericBigDecimal::MIN_PRECISION = 0;
	const int CFLibGenericBigDecimal::MAX_PRECISION = MAX_DIGITS - 1;

	const CFLibGenericBigDecimal* CFLibGenericBigDecimal::ZERO			= new TCFLibBigDecimal<21,0>( "0" );
	const CFLibGenericBigDecimal* CFLibGenericBigDecimal::ONE			= new TCFLibBigDecimal<21,0>( "1" );
	const CFLibGenericBigDecimal* CFLibGenericBigDecimal::TEN			= new TCFLibBigDecimal<21,0>( "10" );
	const CFLibGenericBigDecimal* CFLibGenericBigDecimal::ONE_HUNDRED	= new TCFLibBigDecimal<21,0>( "100" );
	const CFLibGenericBigDecimal* CFLibGenericBigDecimal::ONE_THOUSAND	= new TCFLibBigDecimal<21,0>( "1000" );
	const CFLibGenericBigDecimal* CFLibGenericBigDecimal::ONE_MILLION	= new TCFLibBigDecimal<21,0>( "1000000" );
	const CFLibGenericBigDecimal* CFLibGenericBigDecimal::ONE_BILLION	= new TCFLibBigDecimal<21,0>( "1000000000" );
	const CFLibGenericBigDecimal* CFLibGenericBigDecimal::ONE_TRILLION	= new TCFLibBigDecimal<21,0>( "1000000000000" );

	/**
	 *	Construct a CFLibGenericBigDecimal.
	 */
	CFLibGenericBigDecimal::CFLibGenericBigDecimal() {}

	/**
	 *	Pure virtual base classes need to have a virtual destructor.
	 */
	CFLibGenericBigDecimal::~CFLibGenericBigDecimal() {}
	
	/**
	 *	static inline void precisionRounding( vbl, argPrecis )
	 *		Round vbl to argPrecis fractional digits.
	 */
	inline void CFLibGenericBigDecimal::precisionRounding(mpfr_ptr vbl, const long argPrecis) {
		static const std::string S_ProcName("precisionRounding");
		static const std::string S_ArgPrecis("argPrecis");
		mpfr_t mpfrCalc;
		mpfr_prec_t mpfrCalcPrecis = mpfr_get_prec(vbl) + ( 4 * ( MAX_PRECISION + 1 ));	// Allow for worst case
		mpfr_init2(mpfrCalc, mpfrCalcPrecis);
		if( argPrecis > 0 ) {
			char decimalShift[MAX_DIGITS+4];
			memset( decimalShift, '0', MAX_DIGITS+4 );
			decimalShift[0] = '1';
			decimalShift[argPrecis+1] = '\000';
			mpfr_t mpfrDecimalShift;
			mpfr_init2(mpfrDecimalShift, 4 * (argPrecis + 1));
			mpfr_t mpfrCalc2;
			mpfr_init2(mpfrCalc2, mpfrCalcPrecis);
			decimalShift[argPrecis+1] = '\000';
			int substatus = mpfr_set_str( mpfrDecimalShift, decimalShift, 10, MPFR_RNDN );
			if( substatus != 0 ) {
				throw CFLibSubroutineException( CLASS_NAME,
					S_ProcName,
					S_MpfrSetStr,
					substatus,
					S_MpfrSetStrFailure );
			}
			int mpfrTernary = mpfr_mul(mpfrCalc, vbl, mpfrDecimalShift, MPFR_RNDN);
			mpfrTernary = mpfr_round(mpfrCalc2, mpfrCalc);
			mpfrTernary = mpfr_div(vbl, mpfrCalc2, mpfrDecimalShift, MPFR_RNDN);
			mpfr_clear(mpfrCalc2);
			mpfr_clear(mpfrDecimalShift);
		}
		else {
			mpfr_set(mpfrCalc, vbl, MPFR_RNDN);
			int mpfrTernary = mpfr_round(vbl, mpfrCalc);
		}
		mpfr_clear(mpfrCalc);
	}
}

namespace std {

	/**
	 *	< Comparison operators
	 */

	bool operator <( const cflib::CFLibGenericBigDecimal& lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		if (0 > mpfr_cmp( lhs.getValue(), rhs.getValue())) {
			return( true );
		}
		else {
			return( false );
		}
	}

	bool operator <( const cflib::CFLibGenericBigDecimal& lhs, const mpfr_t& rhs ) {
		if (0 > mpfr_cmp( lhs.getValue(), rhs)) {
			return( true );
		}
		else {
			return( false );
		}
	}

	bool operator <( const cflib::CFLibGenericBigDecimal& lhs, const mpfr_srcptr rhs ) {
		if( rhs == NULL ) {
			return( false );
		}
		else if (0 > mpfr_cmp( lhs.getValue(), rhs)) {
			return( true );
		}
		else {
			return( false );
		}
	}

	bool operator <( const cflib::CFLibGenericBigDecimal& lhs, unsigned long int rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( unsigned long int ) + 4 );
		mpfr_set_ui( tmpval, rhs, MPFR_RNDN );

		if( 0 > mpfr_cmp( lhs.getValue(), tmpval )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	bool operator <( const cflib::CFLibGenericBigDecimal& lhs, long int rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( long int ) + 4 );
		mpfr_set_si( tmpval, rhs, MPFR_RNDN );

		if( 0 > mpfr_cmp( lhs.getValue(), tmpval )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	bool operator <( const cflib::CFLibGenericBigDecimal& lhs, double rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( double ) + 4 );
		mpfr_set_d( tmpval, rhs, MPFR_RNDN );

		if( 0 > mpfr_cmp( lhs.getValue(), tmpval )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	bool operator <( const mpfr_t& lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		if (0 > mpfr_cmp( lhs, rhs.getValue() )) {
			return( true );
		}
		else {
			return( false );
		}
	}

	bool operator <( const mpfr_srcptr lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		if( lhs == NULL ) {
			return( false );
		}
		else if (0 > mpfr_cmp( lhs, rhs.getValue() )) {
			return( true );
		}
		else {
			return( false );
		}
	}

	bool operator <( unsigned long int lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( unsigned long int ) + 4 );
		mpfr_set_ui( tmpval, lhs, MPFR_RNDN );

		if( 0 > mpfr_cmp( tmpval, rhs.getValue() )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	bool operator <( long int lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( long int ) + 4 );
		mpfr_set_si( tmpval, lhs, MPFR_RNDN );

		if( 0 > mpfr_cmp( tmpval, rhs.getValue() )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	bool operator <( double lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( double ) + 4 );
		mpfr_set_d( tmpval, lhs, MPFR_RNDN );

		if( 0 > mpfr_cmp( tmpval, rhs.getValue() )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	/**
	 *	<= Comparison operators
	 */

	bool operator <=( const cflib::CFLibGenericBigDecimal& lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		if (0 >= mpfr_cmp( lhs.getValue(), rhs.getValue())) {
			return( true );
		}
		else {
			return( false );
		}
	}

	bool operator <=( const cflib::CFLibGenericBigDecimal& lhs, const mpfr_t& rhs ) {
		if (0 >= mpfr_cmp( lhs.getValue(), rhs)) {
			return( true );
		}
		else {
			return( false );
		}
	}

	bool operator <=( const cflib::CFLibGenericBigDecimal& lhs, const mpfr_srcptr rhs ) {
		if( rhs == NULL ) {
			return( false );
		}
		else if (0 >= mpfr_cmp( lhs.getValue(), rhs)) {
			return( true );
		}
		else {
			return( false );
		}
	}

	bool operator <=( const cflib::CFLibGenericBigDecimal& lhs, unsigned long int rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( unsigned long int ) + 4 );
		mpfr_set_ui( tmpval, rhs, MPFR_RNDN );

		if( 0 >= mpfr_cmp( lhs.getValue(), tmpval )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	bool operator <=( const cflib::CFLibGenericBigDecimal& lhs, long int rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( long int ) + 4 );
		mpfr_set_si( tmpval, rhs, MPFR_RNDN );

		if( 0 >= mpfr_cmp( lhs.getValue(), tmpval )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	bool operator <=( const cflib::CFLibGenericBigDecimal& lhs, double rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( double ) + 4 );
		mpfr_set_d( tmpval, rhs, MPFR_RNDN );

		if( 0 >= mpfr_cmp( lhs.getValue(), tmpval )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	bool operator <=( const mpfr_t& lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		if (0 >= mpfr_cmp( lhs, rhs.getValue() )) {
			return( true );
		}
		else {
			return( false );
		}
	}

	bool operator <=( const mpfr_srcptr lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		if( lhs == NULL ) {
			return( false );
		}
		else if (0 >= mpfr_cmp( lhs, rhs.getValue() )) {
			return( true );
		}
		else {
			return( false );
		}
	}

	bool operator <=( unsigned long int lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( unsigned long int ) + 4 );
		mpfr_set_ui( tmpval, lhs, MPFR_RNDN );

		if( 0 >= mpfr_cmp( tmpval, rhs.getValue() )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	bool operator <=( long int lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( long int ) + 4 );
		mpfr_set_si( tmpval, lhs, MPFR_RNDN );

		if( 0 >= mpfr_cmp( tmpval, rhs.getValue() )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	bool operator <=( double lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( double ) + 4 );
		mpfr_set_d( tmpval, lhs, MPFR_RNDN );

		if( 0 >= mpfr_cmp( tmpval, rhs.getValue() )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	/**
	 *	== Comparison operators
	 */

	bool operator ==( const cflib::CFLibGenericBigDecimal& lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		if (0 == mpfr_cmp( lhs.getValue(), rhs.getValue())) {
			return( true );
		}
		else {
			return( false );
		}
	}

	bool operator ==( const cflib::CFLibGenericBigDecimal& lhs, const mpfr_t& rhs ) {
		if (0 == mpfr_cmp( lhs.getValue(), rhs)) {
			return( true );
		}
		else {
			return( false );
		}
	}

	bool operator ==( const cflib::CFLibGenericBigDecimal& lhs, const mpfr_srcptr rhs ) {
		if( rhs == NULL ) {
			return( false );
		}
		else if (0 == mpfr_cmp( lhs.getValue(), rhs)) {
			return( true );
		}
		else {
			return( false );
		}
	}

	bool operator ==( const cflib::CFLibGenericBigDecimal& lhs, unsigned long int rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( unsigned long int ) + 4 );
		mpfr_set_ui( tmpval, rhs, MPFR_RNDN );

		if( 0 == mpfr_cmp( lhs.getValue(), tmpval )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	bool operator ==( const cflib::CFLibGenericBigDecimal& lhs, long int rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( long int ) + 4 );
		mpfr_set_si( tmpval, rhs, MPFR_RNDN );

		if( 0 == mpfr_cmp( lhs.getValue(), tmpval )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	bool operator ==( const cflib::CFLibGenericBigDecimal& lhs, double rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( double ) + 4 );
		mpfr_set_d( tmpval, rhs, MPFR_RNDN );

		if( 0 == mpfr_cmp( lhs.getValue(), tmpval )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	bool operator ==( const mpfr_t& lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		if (0 == mpfr_cmp( lhs, rhs.getValue() )) {
			return( true );
		}
		else {
			return( false );
		}
	}

	bool operator ==( const mpfr_srcptr lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		if( lhs == NULL ) {
			return( false );
		}
		else if (0 == mpfr_cmp( lhs, rhs.getValue() )) {
			return( true );
		}
		else {
			return( false );
		}
	}

	bool operator ==( unsigned long int lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( unsigned long int ) + 4 );
		mpfr_set_ui( tmpval, lhs, MPFR_RNDN );

		if( 0 == mpfr_cmp( tmpval, rhs.getValue() )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	bool operator ==( long int lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( long int ) + 4 );
		mpfr_set_si( tmpval, lhs, MPFR_RNDN );

		if( 0 == mpfr_cmp( tmpval, rhs.getValue() )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	bool operator ==( double lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( double ) + 4 );
		mpfr_set_d( tmpval, lhs, MPFR_RNDN );

		if( 0 == mpfr_cmp( tmpval, rhs.getValue() )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	/**
	 *	!= Comparison operators
	 */

	bool operator !=( const cflib::CFLibGenericBigDecimal& lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		if (0 != mpfr_cmp( lhs.getValue(), rhs.getValue())) {
			return( true );
		}
		else {
			return( false );
		}
	}

	bool operator !=( const cflib::CFLibGenericBigDecimal& lhs, const mpfr_t& rhs ) {
		if (0 != mpfr_cmp( lhs.getValue(), rhs)) {
			return( true );
		}
		else {
			return( false );
		}
	}

	bool operator !=( const cflib::CFLibGenericBigDecimal& lhs, const mpfr_srcptr rhs ) {
		if( rhs == NULL ) {
			return( true );
		}
		else if (0 != mpfr_cmp( lhs.getValue(), rhs)) {
			return( true );
		}
		else {
			return( false );
		}
	}

	bool operator !=( const cflib::CFLibGenericBigDecimal& lhs, unsigned long int rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( unsigned long int ) + 4 );
		mpfr_set_ui( tmpval, rhs, MPFR_RNDN );

		if( 0 != mpfr_cmp( lhs.getValue(), tmpval )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	bool operator !=( const cflib::CFLibGenericBigDecimal& lhs, long int rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( long int ) + 4 );
		mpfr_set_si( tmpval, rhs, MPFR_RNDN );

		if( 0 != mpfr_cmp( lhs.getValue(), tmpval )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	bool operator !=( const cflib::CFLibGenericBigDecimal& lhs, double rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( double ) + 4 );
		mpfr_set_d( tmpval, rhs, MPFR_RNDN );

		if( 0 != mpfr_cmp( lhs.getValue(), tmpval )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	bool operator !=( const mpfr_t& lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		if (0 != mpfr_cmp( lhs, rhs.getValue() )) {
			return( true );
		}
		else {
			return( false );
		}
	}

	bool operator !=( const mpfr_srcptr lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		if( lhs == NULL ) {
			return( false );
		}
		else if (0 != mpfr_cmp( lhs, rhs.getValue() )) {
			return( true );
		}
		else {
			return( false );
		}
	}

	bool operator !=( unsigned long int lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( unsigned long int ) + 4 );
		mpfr_set_ui( tmpval, lhs, MPFR_RNDN );

		if( 0 != mpfr_cmp( tmpval, rhs.getValue() )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	bool operator !=( long int lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( long int ) + 4 );
		mpfr_set_si( tmpval, lhs, MPFR_RNDN );

		if( 0 != mpfr_cmp( tmpval, rhs.getValue() )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	bool operator !=( double lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( double ) + 4 );
		mpfr_set_d( tmpval, lhs, MPFR_RNDN );

		if( 0 != mpfr_cmp( tmpval, rhs.getValue() )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	/**
	 *	>= Comparison operators
	 */

	bool operator >=( const cflib::CFLibGenericBigDecimal& lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		if (0 <= mpfr_cmp( lhs.getValue(), rhs.getValue())) {
			return( true );
		}
		else {
			return( false );
		}
	}

	bool operator >=( const cflib::CFLibGenericBigDecimal& lhs, const mpfr_t& rhs ) {
		if (0 <= mpfr_cmp( lhs.getValue(), rhs)) {
			return( true );
		}
		else {
			return( false );
		}
	}

	bool operator >=( const cflib::CFLibGenericBigDecimal& lhs, const mpfr_srcptr rhs ) {
		if( rhs == NULL ) {
			return( true );
		}
		else if (0 <= mpfr_cmp( lhs.getValue(), rhs)) {
			return( true );
		}
		else {
			return( false );
		}
	}

	bool operator >=( const cflib::CFLibGenericBigDecimal& lhs, unsigned long int rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( unsigned long int ) + 4 );
		mpfr_set_ui( tmpval, rhs, MPFR_RNDN );

		if( 0 <= mpfr_cmp( lhs.getValue(), tmpval )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	bool operator >=( const cflib::CFLibGenericBigDecimal& lhs, long int rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( long int ) + 4 );
		mpfr_set_si( tmpval, rhs, MPFR_RNDN );

		if( 0 <= mpfr_cmp( lhs.getValue(), tmpval )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	bool operator >=( const cflib::CFLibGenericBigDecimal& lhs, double rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( double ) + 4 );
		mpfr_set_si( tmpval, rhs, MPFR_RNDN );

		if( 0 <= mpfr_cmp( lhs.getValue(), tmpval )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	bool operator >=( const mpfr_t& lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		if (0 <= mpfr_cmp( lhs, rhs.getValue() )) {
			return( true );
		}
		else {
			return( false );
		}
	}

	bool operator >=( const mpfr_srcptr lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		if( lhs == NULL ) {
			return( false );
		}
		else if (0 <= mpfr_cmp( lhs, rhs.getValue() )) {
			return( true );
		}
		else {
			return( false );
		}
	}

	bool operator >=( unsigned long int lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( unsigned long int ) + 4 );
		mpfr_set_ui( tmpval, lhs, MPFR_RNDN );

		if( 0 <= mpfr_cmp( tmpval, rhs.getValue() )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	bool operator >=( long int lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( long int ) + 4 );
		mpfr_set_si( tmpval, lhs, MPFR_RNDN );

		if( 0 <= mpfr_cmp( tmpval, rhs.getValue() )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	bool operator >=( double lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( double ) + 4 );
		mpfr_set_d( tmpval, lhs, MPFR_RNDN );

		if( 0 <= mpfr_cmp( tmpval, rhs.getValue() )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	/**
	 *	> Comparison operators
	 */

	bool operator >( const cflib::CFLibGenericBigDecimal& lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		if (0 < mpfr_cmp( lhs.getValue(), rhs.getValue())) {
			return( true );
		}
		else {
			return( false );
		}
	}

	bool operator >( const cflib::CFLibGenericBigDecimal& lhs, const mpfr_t& rhs ) {
		if (0 < mpfr_cmp( lhs.getValue(), rhs)) {
			return( true );
		}
		else {
			return( false );
		}
	}

	bool operator >( const cflib::CFLibGenericBigDecimal& lhs, const mpfr_srcptr rhs ) {
		if( rhs == NULL ) {
			return( true );
		}
		else if (0 < mpfr_cmp( lhs.getValue(), rhs)) {
			return( true );
		}
		else {
			return( false );
		}
	}

	bool operator >( const cflib::CFLibGenericBigDecimal& lhs, unsigned long int rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( unsigned long int ) + 4 );
		mpfr_set_ui( tmpval, rhs, MPFR_RNDN );

		if( 0 < mpfr_cmp( lhs.getValue(), tmpval )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	bool operator >( const cflib::CFLibGenericBigDecimal& lhs, long int rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( long int ) + 4 );
		mpfr_set_si( tmpval, rhs, MPFR_RNDN );

		if( 0 < mpfr_cmp( lhs.getValue(), tmpval )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	bool operator >( const cflib::CFLibGenericBigDecimal& lhs, double rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( double ) + 4 );
		mpfr_set_d( tmpval, rhs, MPFR_RNDN );

		if( 0 < mpfr_cmp( lhs.getValue(), tmpval )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	bool operator >( const mpfr_t& lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		if (0 < mpfr_cmp( lhs, rhs.getValue() )) {
			return( true );
		}
		else {
			return( false );
		}
	}

	bool operator >( const mpfr_srcptr lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		if( lhs == NULL ) {
			return( false );
		}
		else if (0 < mpfr_cmp( lhs, rhs.getValue() )) {
			return( true );
		}
		else {
			return( false );
		}
	}

	bool operator >( unsigned long int lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( unsigned long int ) + 4 );
		mpfr_set_ui( tmpval, lhs, MPFR_RNDN );

		if( 0 < mpfr_cmp( tmpval, rhs.getValue() )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	bool operator >( long int lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( long int ) + 4 );
		mpfr_set_si( tmpval, lhs, MPFR_RNDN );

		if( 0 < mpfr_cmp( tmpval, rhs.getValue() )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}

	bool operator >( double lhs, const cflib::CFLibGenericBigDecimal& rhs ) {
		bool retval;
		mpfr_t tmpval;
		mpfr_init2( tmpval, sizeof( double ) + 4 );
		mpfr_set_d( tmpval, lhs, MPFR_RNDN );

		if( 0 < mpfr_cmp( tmpval, rhs.getValue() )) {
			retval = true;
		}
		else {
			retval = false;
		}

		mpfr_clear( tmpval );

		return( retval );
	}
}
