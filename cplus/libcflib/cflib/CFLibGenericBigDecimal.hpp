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

#include <mpfr.h>
#include <cflib/CFLib.hpp>
#include <cflib/CFLibExceptionInfo.hpp>
#include <cflib/CFLibRuntimeException.hpp>
#include <cflib/CFLibSubroutineException.hpp>
#include <cflib/CFLibMathException.hpp>

namespace cflib {

	/**
	 *	The CFLibGenericBigDecimal class is a pure virtual base
	 *	from which all TCFLibBigDecimal template expressions
	 *	derive.  This allows you to write generic logic that manipulates
	 *	any expression of numeric data, such as iterating through
	 *	a list and adding up virtual values.
	 */
	class CFLibGenericBigDecimal {
	public:

		/**
		 * Constant strings for messaging in the implementation template.
		 */
		static const std::string CLASS_NAME;
		static const std::string CLASSNAME_TCFLIBBIGDECIMAL;
		static const std::string S_Digits;
		static const std::string S_Field;
		static const std::string S_Precis;
		static const std::string S_Value;
		static const std::string S_Null;
		static const std::string S_Base;
		static const std::string S_P;
		static const std::string S_LowerNull;
		static const std::string S_Src;
		static const std::string S_Tmp;
		static const std::string S_Underflow;
		static const std::string S_Overflow;
		static const std::string S_NaN;
		static const std::string S_ERange;
		static const std::string S_DivBy0;
		static const std::string S_MpfrSetStrFailure;
		static const std::string S_MpfrFlagsTestFailure;
		static const std::string S_MpfrFunctionRoundedDown;
		static const std::string S_MpfrFunctionRoundedUp;
		static const std::string S_MpfrSetStr;
		static const std::string S_BaseArg3CannotBeOne;
		static const std::string S_MsgSetStrFailure;

		/**
		 *	MIN_DIGITS is always one.
		 *	MAX_DIGITS is either a value calculated using MPFR_MAX_PREC
		 *		or 1990, whichever is less.  I want to ensure
		 *		that formatted strings of a number will always fit
		 *		in a database VARCHAR2 column.
		 *	MIN_PRECISION is zero.
		 *	MAX_PRECISION is MAX_DIGITS - 1.  You must always have
		 *		at least one integer digit, even if it is a zero.
		 */
		static const int MIN_DIGITS;
		static const int MAX_DIGITS;
		static const int MIN_PRECISION;
		static const int MAX_PRECISION;

		/**
		 *	Get the number of digits used to define this template instance.
		 *	Digits must always exceed precision.
		 */
		virtual const int getDigits() const = 0;

		/**
		 *	Get the precision used to define this template instance.
		 */
		virtual const int getPrecision() const = 0;

		/**
		 *	Get the maximum number of integer digits before the decimal point
		 *	for values defined by this template instance.
		 */
		virtual const int getIntegerDigits() const = 0;

		/**
		 *	Get the number of bits required for the mpfr mantissa
		 *	to store minimum and maximum values supported by
		 *	this decimal template instance.
		 */
		virtual const mpfr_prec_t getBitsRequired() const = 0;

		/**
		 *	Construct a CFLibGenericBigDecimal.
		 */
		CFLibGenericBigDecimal();

		/**
		 *	Pure virtual base classes need to have a virtual destructor.
		 */
		virtual ~CFLibGenericBigDecimal();

		/**
		 *	Useful constants.
		 */
		static const CFLibGenericBigDecimal* ZERO;
		static const CFLibGenericBigDecimal* ONE;
		static const CFLibGenericBigDecimal* TEN;
		static const CFLibGenericBigDecimal* ONE_HUNDRED;
		static const CFLibGenericBigDecimal* ONE_THOUSAND;
		static const CFLibGenericBigDecimal* ONE_MILLION;
		static const CFLibGenericBigDecimal* ONE_BILLION;
		static const CFLibGenericBigDecimal* ONE_TRILLION;

		/**
		 *	NaN accessors
		 */
		virtual void setNaN() = 0;
		virtual bool isNaN() const = 0;
	
		/**
		 *	static inline void precisionRounding( vbl, argPrecis )
		 *		Round vbl to argPrecis fractional digits.
		 */
		static void precisionRounding(mpfr_ptr vbl, const long argPrecis);

		/**
		 *	Other value classifications
		 */
		virtual bool isInfinite() const = 0;
		virtual void setInfinite( int sign ) = 0;

		virtual bool isNumber() const = 0;
		virtual bool isInteger() const = 0;

		virtual bool isZero() const = 0;
		virtual void setZero( int sign ) = 0;

		virtual bool isRegular() const = 0;

		/**
		 *	Get a read-only pointer to this instance's mpfr_t value.
		 */
		virtual mpfr_srcptr getValue() const = 0;

		/**
		 *	Set the value of this instance to the specified value,
		 *	with NULL or empty values resulting in an exception.
		 */
		virtual void setValue(const mpfr_t& argValue) = 0;
		virtual void setValue(mpfr_srcptr argValue) = 0;
		virtual void setValue(unsigned long int src) = 0;
		virtual void setValue(long int src) = 0;
		virtual void setValue(double src) = 0;
		virtual void setValue(const std::string& src) = 0;

		/**
		 *	Get the template parameter's minimum and maximum
		 *	value allowed for instances	of this template's
		 *	parameters, or the absolute minimum and maximum
		 *	if no such restrictions were specified for this
		 *	template.
		 */
		virtual mpfr_srcptr getMinValue() const = 0;
		virtual mpfr_srcptr getMaxValue() const = 0;

		/**
		 *	The most common interpretation of toString() is to return
		 *	the signed decimal fraction string representing this
		 *	instance's value.
		 *
		 *		fieldOrClassName - the required name of the field or invoking class
		 */
		virtual std::string toString(const std::string& fieldOrClassName) const = 0;
		virtual std::string toString() const = 0;

		/**
		 *	MPFR version string
		 */
		static inline const char * getMPFRVersion() {
			return( mpfr_get_version() );
		}

		/**
		 *	MPFR configuration
		 */
		static inline void setDefaultPrec( mpfr_prec_t value ) {
			mpfr_set_default_prec( value );
		}

		static inline mpfr_prec_t getDefaultPrec() {
			return( mpfr_get_default_prec() );
		}

		static inline mpfr_exp_t getEMin() {
			return( mpfr_get_emin() );
		}

		static inline int setEMin( mpfr_exp_t value ) {
			return( mpfr_set_emin( value ) );
		}

		static inline mpfr_exp_t getMinMin() {
			return( mpfr_get_emin_min() );
		}

		static inline mpfr_exp_t getEMinMax() {
			return( mpfr_get_emin_max() );
		}

		static inline mpfr_exp_t getEMax() {
			return( mpfr_get_emax() );
		}

		static inline int setEMax( mpfr_exp_t value ) {
			return( mpfr_set_emax( value ) );
		}

		static inline mpfr_exp_t getEMaxMin() {
			return( mpfr_get_emax_min() );
		}

		static inline mpfr_exp_t getMaxMax() {
			return( mpfr_get_emax_max() );
		}

		/**
		 *	MPFR exception flags
		 */
		static inline void clearFlags() {
			mpfr_clear_flags();
		}

		static inline void clearUnderflow() {
			mpfr_clear_underflow();
		}

		static inline void clearOverflow() {
			mpfr_clear_overflow();
		}

		static inline void clearDivBy0() {
			mpfr_clear_divby0();
		}

		static inline void clearNaNFlag() {
			mpfr_clear_nanflag();
		}

		static inline void clearInExFlag() {
			mpfr_clear_inexflag();
		}

		static inline void clearERangeFlag() {
			mpfr_clear_erangeflag();
		}

		static inline void setUnderflow() {
			mpfr_set_underflow();
		}

		static inline void setOverflow() {
			mpfr_set_overflow();
		}

		static inline void setDivBy0() {
			mpfr_set_divby0();
		}

		static inline void setNaNFlag() {
			mpfr_set_nanflag();
		}

		static inline void setInExFlag() {
			mpfr_set_inexflag();
		}

		static inline void setERangeFlag() {
			mpfr_set_erangeflag();
		}

		static inline bool getUnderflow() {
			if( mpfr_underflow_p() ) {
				return( true );
			}
			else {
				return( false );
			}
		}

		static inline bool getOverflow() {
			if( mpfr_overflow_p() ) {
				return( true );
			}
			else {
				return( false );
			}
		}

		static inline bool getDivBy0() {
			if( mpfr_divby0_p() ) {
				return( true );
			}
			else {
				return( false );
			}
		}

		static inline bool getNaNFlag() {
			if( mpfr_nanflag_p() ) {
				return( true );
			}
			else {
				return( false );
			}
		}

		static inline bool getInExFlag() {
			if( mpfr_inexflag_p() ) {
				return( true );
			}
			else {
				return( false );
			}
		}

		static inline bool getERangeFlag() {
			if( mpfr_erangeflag_p() ) {
				return( true );
			}
			else {
				return( false );
			}
		}

		static inline void flagsClear( mpfr_flags_t value ) {
			mpfr_flags_clear( value );
		}

		static inline void flagsSet( mpfr_flags_t value ) {
			mpfr_flags_set( value );
		}

		static inline mpfr_flags_t flagsTest( mpfr_flags_t value ) {
			return( mpfr_flags_test( value ) );
		}

		static inline mpfr_flags_t flagsSave() {
			return( mpfr_flags_save() );
		}

		static inline void flagsRestore( mpfr_flags_t a,
			mpfr_flags_t b )
		{
			mpfr_flags_restore( a, b );
		}

		/**
		 *	MPFR cache management
		 */
		static inline void freeCache() {
			mpfr_free_cache();
		}

		static inline void freeCache( mpfr_free_cache_t value ) {
			mpfr_free_cache2( value );
		}

		static inline void freePool() {
			mpfr_free_pool();
		}

		static inline int mpMemoryCleanup() {
			return( mpfr_mp_memory_cleanup() );
		}

		/**
		 *	Virtual methods provided by TCFLibBigDecimal implementations.
		 *	You can't overload the operators in CFLibGenericBigDecimal
		 *	itself because it is not an instantiable class due to the
		 *	specification of abstract virtuals.
		 */

		virtual int checkRange( int t, mpfr_rnd_t rnd = MPFR_RNDN ) = 0;
		virtual mpfr_prec_t minPrec() const = 0;
		virtual mpfr_exp_t getExp() const = 0;
		virtual mpfr_prec_t getPrec() const = 0;
		virtual int set2Exp( long value,
			mpfr_exp_t exp,
			mpfr_rnd_t rnd = MPFR_RNDN ) = 0;
		virtual int set2Exp( unsigned long value,
			mpfr_exp_t exp,
			mpfr_rnd_t rnd = MPFR_RNDN ) = 0;
		virtual bool isNegative() const = 0;
		virtual mpfr_exp_t getZ2Exp( mpz_ptr p ) const = 0;
		virtual float getFloat() = 0;
		virtual float getDouble() = 0;
		virtual long double getLongDouble() = 0;
		virtual double getDouble2Exp( long * p ) const = 0;
		virtual long double getLongDouble2Exp( long * p ) const = 0;
		virtual long getSignedInteger()  const = 0;
		virtual long getUnsignedInteger()  const = 0;
		virtual mpfr_exp_t getZ( mpz_ptr p ) const = 0;
		virtual int sign() const = 0;
		virtual bool fitsLong( mpfr_rnd_t rnd = MPFR_RNDN ) const = 0;
		virtual bool fitsInt( mpfr_rnd_t rnd = MPFR_RNDN ) const = 0;
		virtual bool fitsUInt( mpfr_rnd_t rnd = MPFR_RNDN ) const = 0;
		virtual bool fitsShort( mpfr_rnd_t rnd = MPFR_RNDN ) const = 0;
		virtual bool fitsUShort( mpfr_rnd_t rnd = MPFR_RNDN ) const = 0;
		virtual bool fitsUIntMax( mpfr_rnd_t rnd = MPFR_RNDN ) const = 0;
		virtual bool fitsIntMax( mpfr_rnd_t rnd = MPFR_RNDN ) const = 0;
		virtual bool isUnordered( const CFLibGenericBigDecimal& value ) const = 0;
		virtual bool greaterThan( const CFLibGenericBigDecimal& value ) const = 0;
		virtual bool greaterOrEqual( const CFLibGenericBigDecimal& value ) const = 0;
		virtual bool lessThan( const CFLibGenericBigDecimal& value ) const = 0;
		virtual bool lessOrEqual( const CFLibGenericBigDecimal& value ) const = 0;
		virtual bool equal( const CFLibGenericBigDecimal& value ) const = 0;
		virtual void dump() const = 0;
	};
}

namespace std {

	/**
	 *	< Comparison operators
	 */

	bool operator <( const cflib::CFLibGenericBigDecimal& lhs, const cflib::CFLibGenericBigDecimal& rhs );
	bool operator <( const cflib::CFLibGenericBigDecimal& lhs, const mpfr_t& rhs );
	bool operator <( const cflib::CFLibGenericBigDecimal& lhs, const mpfr_srcptr rhs );
	bool operator <( const cflib::CFLibGenericBigDecimal& lhs, unsigned long int rhs );
	bool operator <( const cflib::CFLibGenericBigDecimal& lhs, long int rhs );
	bool operator <( const cflib::CFLibGenericBigDecimal& lhs, double rhs );
	bool operator <( const mpfr_t& lhs, const cflib::CFLibGenericBigDecimal& rhs );
	bool operator <( const mpfr_srcptr lhs, const cflib::CFLibGenericBigDecimal& rhs );
	bool operator <( unsigned long int lhs, const cflib::CFLibGenericBigDecimal& rhs );
	bool operator <( long int lhs, const cflib::CFLibGenericBigDecimal& rhs );
	bool operator <( double lhs, const cflib::CFLibGenericBigDecimal& rhs );

	/**
	 *	<= Comparison operators
	 */

	bool operator <=( const cflib::CFLibGenericBigDecimal& lhs, const cflib::CFLibGenericBigDecimal& rhs );
	bool operator <=( const cflib::CFLibGenericBigDecimal& lhs, const mpfr_t& rhs );
	bool operator <=( const cflib::CFLibGenericBigDecimal& lhs, const mpfr_srcptr rhs );
	bool operator <=( const cflib::CFLibGenericBigDecimal& lhs, unsigned long int rhs );
	bool operator <=( const cflib::CFLibGenericBigDecimal& lhs, long int rhs );
	bool operator <=( const cflib::CFLibGenericBigDecimal& lhs, double rhs );
	bool operator <=( const mpfr_t& lhs, const cflib::CFLibGenericBigDecimal& rhs );
	bool operator <=( const mpfr_srcptr lhs, const cflib::CFLibGenericBigDecimal& rhs );
	bool operator <=( unsigned long int lhs, const cflib::CFLibGenericBigDecimal& rhs );
	bool operator <=( long int lhs, const cflib::CFLibGenericBigDecimal& rhs );
	bool operator <=( double lhs, const cflib::CFLibGenericBigDecimal& rhs );

	/**
	 *	== Comparison operators
	 */

	bool operator ==( const cflib::CFLibGenericBigDecimal& lhs, const cflib::CFLibGenericBigDecimal& rhs );
	bool operator ==( const cflib::CFLibGenericBigDecimal& lhs, const mpfr_t& rhs );
	bool operator ==( const cflib::CFLibGenericBigDecimal& lhs, const mpfr_srcptr rhs );
	bool operator ==( const cflib::CFLibGenericBigDecimal& lhs, unsigned long int rhs );
	bool operator ==( const cflib::CFLibGenericBigDecimal& lhs, long int rhs );
	bool operator ==( const cflib::CFLibGenericBigDecimal& lhs, double rhs );
	bool operator ==( const mpfr_t& lhs, const cflib::CFLibGenericBigDecimal& rhs );
	bool operator ==( const mpfr_srcptr lhs, const cflib::CFLibGenericBigDecimal& rhs );
	bool operator ==( unsigned long int lhs, const cflib::CFLibGenericBigDecimal& rhs );
	bool operator ==( long int lhs, const cflib::CFLibGenericBigDecimal& rhs );
	bool operator ==( double lhs, const cflib::CFLibGenericBigDecimal& rhs );

	/**
	 *	!= Comparison operators
	 */

	bool operator !=( const cflib::CFLibGenericBigDecimal& lhs, const cflib::CFLibGenericBigDecimal& rhs );
	bool operator !=( const cflib::CFLibGenericBigDecimal& lhs, const mpfr_t& rhs );
	bool operator !=( const cflib::CFLibGenericBigDecimal& lhs, const mpfr_srcptr rhs );
	bool operator !=( const cflib::CFLibGenericBigDecimal& lhs, unsigned long int rhs );
	bool operator !=( const cflib::CFLibGenericBigDecimal& lhs, long int rhs );
	bool operator !=( const cflib::CFLibGenericBigDecimal& lhs, double rhs );
	bool operator !=( const mpfr_t& lhs, const cflib::CFLibGenericBigDecimal& rhs );
	bool operator !=( const mpfr_srcptr lhs, const cflib::CFLibGenericBigDecimal& rhs );
	bool operator !=( unsigned long int lhs, const cflib::CFLibGenericBigDecimal& rhs );
	bool operator !=( long int lhs, const cflib::CFLibGenericBigDecimal& rhs );
	bool operator !=( double lhs, const cflib::CFLibGenericBigDecimal& rhs );

	/**
	 *	>= Comparison operators
	 */

	bool operator >=( const cflib::CFLibGenericBigDecimal& lhs, const cflib::CFLibGenericBigDecimal& rhs );
	bool operator >=( const cflib::CFLibGenericBigDecimal& lhs, const mpfr_t& rhs );
	bool operator >=( const cflib::CFLibGenericBigDecimal& lhs, const mpfr_srcptr rhs );
	bool operator >=( const cflib::CFLibGenericBigDecimal& lhs, unsigned long int rhs );
	bool operator >=( const cflib::CFLibGenericBigDecimal& lhs, long int rhs );
	bool operator >=( const cflib::CFLibGenericBigDecimal& lhs, double rhs );
	bool operator >=( const mpfr_t& lhs, const cflib::CFLibGenericBigDecimal& rhs );
	bool operator >=( const mpfr_srcptr lhs, const cflib::CFLibGenericBigDecimal& rhs );
	bool operator >=( unsigned long int lhs, const cflib::CFLibGenericBigDecimal& rhs );
	bool operator >=( long int lhs, const cflib::CFLibGenericBigDecimal& rhs );
	bool operator >=( double lhs, const cflib::CFLibGenericBigDecimal& rhs );

	/**
	 *	> Comparison operators
	 */

	bool operator >( const cflib::CFLibGenericBigDecimal& lhs, const cflib::CFLibGenericBigDecimal& rhs );
	bool operator >( const cflib::CFLibGenericBigDecimal& lhs, const mpfr_t& rhs );
	bool operator >( const cflib::CFLibGenericBigDecimal& lhs, const mpfr_srcptr rhs );
	bool operator >( const cflib::CFLibGenericBigDecimal& lhs, unsigned long int rhs );
	bool operator >( const cflib::CFLibGenericBigDecimal& lhs, long int rhs );
	bool operator >( const cflib::CFLibGenericBigDecimal& lhs, double rhs );
	bool operator >( const mpfr_t& lhs, const cflib::CFLibGenericBigDecimal& rhs );
	bool operator >( const mpfr_srcptr lhs, const cflib::CFLibGenericBigDecimal& rhs );
	bool operator >( unsigned long int lhs, const cflib::CFLibGenericBigDecimal& rhs );
	bool operator >( long int lhs, const cflib::CFLibGenericBigDecimal& rhs );
	bool operator >( double lhs, const cflib::CFLibGenericBigDecimal& rhs );
}
