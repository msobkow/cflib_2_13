// Description: C++18 Implementation of a RAM CFSec loader.

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

using namespace std;

#include <array>
#include <cassert>
#include <cstddef>
#include <chrono>
#include <ctime>
#include <functional>
#include <list>
#include <string>

#include <cflib/ICFLibPublic.hpp>

static const std::string CLASS_NAME( "TestCFLib" );

int main( int argc, char* argv[] ) {

	if( argc < 1 ) {
		std::cerr << CLASS_NAME + " ERROR: Program name is not available\n";
		return( 1 );
	}
	std::string S_ProcName( argv[0] );
	CFLIB_EXCEPTION_DECLINFO
	static const std::string S_System( "system" );

	cflib::CFLib::init();

	int retval = 0;

	bool anyTestsFailed = false;

	try {
		std::cout << "MPFR_PREC_MAX is " << MPFR_PREC_MAX << "\n";
		std::cout << "( MPFR_PREC_MAX / 8 ) is " << ( MPFR_PREC_MAX / 8 ) << "\n";

		std::cout << "MIN_DIGITS is " << cflib::CFLibGenericBigDecimal::MIN_DIGITS << "\n";
		std::cout << "MAX_DIGITS is " << cflib::CFLibGenericBigDecimal::MAX_DIGITS << "\n";
		std::cout << "MIN_PRECISION is " << cflib::CFLibGenericBigDecimal::MIN_PRECISION << "\n";
		std::cout << "MAX_PRECISION is " << cflib::CFLibGenericBigDecimal::MAX_PRECISION << "\n";

		try {
			cflib::TCFLibBigDecimal<2001,0> forceDigitsOverflow( "1" );
			std::cout << "Failed! Forced digits overflow constructor should have generated an exception\n";
			anyTestsFailed = true;
		}
		CFLIB_EXCEPTION_CATCH_FALLTHROUGH
		if( ! CFLIB_EXCEPTION_EMPTY ) {
			std::cout << "Success: Forced digits overflow constructor generated exception "  << " - " <<  CFLIB_EXCEPTION_FORMATTEDMESSAGE << "\n";
			CFLIB_EXCEPTION_RESET
		}

		try {
			cflib::TCFLibBigDecimal<20,-1> forcePrecisDigitsUnderflow( "1" );
			std::cout << "Failed! Forced precision underflow constructor should have generated an exception\n";
			anyTestsFailed = true;
		}
		CFLIB_EXCEPTION_CATCH_FALLTHROUGH
		if( ! CFLIB_EXCEPTION_EMPTY ) {
			std::cout << "Success: Forced precision underflow constructor generated exception "  << " - " << CFLIB_EXCEPTION_FORMATTEDMESSAGE << "\n";
			CFLIB_EXCEPTION_RESET
		}

		try {
			cflib::TCFLibBigDecimal<1990,1992> forcePrecisDigitsOverflow( "1" );
			std::cout << "Failed! Forced precision overflow constructor should have generated an exception\n";
			anyTestsFailed = true;
		}
		CFLIB_EXCEPTION_CATCH_FALLTHROUGH
		if( ! CFLIB_EXCEPTION_EMPTY ) {
			std::cout << "Success: Forced precision overflow constructor generated exception "  << " - " << CFLIB_EXCEPTION_FORMATTEDMESSAGE << "\n";
			CFLIB_EXCEPTION_RESET
		}

		try {
			cflib::TCFLibBigDecimal<20,21> forcePrecisDigitsUnderflow( "1" );
			std::cout << "Failed! Forced precision overflow constructor should have generated an exception\n";
			anyTestsFailed = true;
		}
		CFLIB_EXCEPTION_CATCH_FALLTHROUGH
		if( ! CFLIB_EXCEPTION_EMPTY ) {
			std::cout << "Success: Forced precision overflow constructor generated exception "  " - " << CFLIB_EXCEPTION_FORMATTEDMESSAGE << "\n";
			CFLIB_EXCEPTION_RESET
		}

		cflib::TCFLibBigDecimal<20,0> constructDefault;
		cflib::TCFLibBigDecimal<20,0> uintFive( 5UL );
		cflib::TCFLibBigDecimal<20,0> intTen( 10L );
		cflib::TCFLibBigDecimal<20,5> fracFive( "12345678901234.56789" );
		cflib::TCFLibBigDecimal<20,3> fracThree( "12345678901234.567" );
		cflib::TCFLibBigDecimal<20,3> constructRound( "12345678901234.46789" );
		cflib::TCFLibBigDecimal<20,3> constructPad( "12345678901234.4" );
		cflib::TCFLibBigDecimal<20,3> roundedCopy( fracFive );
		std::cout << "constructDefault is " << constructDefault.toString() << "\n";
		std::cout << "uintFive is " << uintFive.toString() << "\n";
		std::cout << "intTen is " << intTen.toString() << "\n";
		std::cout << "fracFive is " << fracFive.toString() << "\n";
		std::cout << "fracThree is " << fracThree.toString() << "\n";
		std::cout << "constructRound is " << constructRound.toString() << "\n";
		std::cout << "constructPad is " << constructPad.toString() << "\n";
		std::cout << "roundedCopy is " << roundedCopy.toString() << "\n";

		try {
			cflib::TCFLibBigDecimal<3,0> forceOverflow( 9999UL );
			std::cout << "Failed! Forced unsigned long integer constructor overflow should have generated an exception\n";
			anyTestsFailed = true;
		}
		CFLIB_EXCEPTION_CATCH_FALLTHROUGH
		if( ! CFLIB_EXCEPTION_EMPTY ) {
			std::cout << "Success: Forced unsigned long integer constructor overflow generated exception "  " - " << CFLIB_EXCEPTION_FORMATTEDMESSAGE << "\n";
			CFLIB_EXCEPTION_RESET
		}

		std::cout << "There is no way to foce an underflow for an unsigned long integer\n";

		try {
			cflib::TCFLibBigDecimal<3,0> forceOverflow( 9999L );
			std::cout << "Failed! Forced long integer constructor overflow should have generated an exception\n";
			anyTestsFailed = true;
		}
		CFLIB_EXCEPTION_CATCH_FALLTHROUGH
		if( ! CFLIB_EXCEPTION_EMPTY ) {
			std::cout << "Success: Forced long integer constructor overflow generated exception "  " - " << CFLIB_EXCEPTION_FORMATTEDMESSAGE << "\n";
			CFLIB_EXCEPTION_RESET
		}

		try {
			cflib::TCFLibBigDecimal<3,0> forceUnderflow( -9999L );
			std::cout << "Failed! Forced long integer constructor underflow should have generated an exception\n";
			anyTestsFailed = true;
		}
		CFLIB_EXCEPTION_CATCH_FALLTHROUGH
		if( ! CFLIB_EXCEPTION_EMPTY ) {
			std::cout << "Success: Forced long integer constructor underflow generated exception "   << " - " << CFLIB_EXCEPTION_FORMATTEDMESSAGE << "\n";
			CFLIB_EXCEPTION_RESET
		}

		try {
			cflib::TCFLibBigDecimal<3,0> forceOverflow( "9999" );
			std::cout << "Failed! Forced string constructor overflow should have generated an exception\n";
			anyTestsFailed = true;
		}
		CFLIB_EXCEPTION_CATCH_FALLTHROUGH
		if( ! CFLIB_EXCEPTION_EMPTY ) {
			std::cout << "Success: Forced string constructor overflow generated exception "   << " - " << CFLIB_EXCEPTION_FORMATTEDMESSAGE << "\n";
			CFLIB_EXCEPTION_RESET
		}

		try {
			cflib::TCFLibBigDecimal<3,0> forceUnderflow( "-9999" );
			std::cout << "Failed! Forced string constructor underflow should have generated an exception\n";
			anyTestsFailed = true;
		}
		CFLIB_EXCEPTION_CATCH_FALLTHROUGH
		if( ! CFLIB_EXCEPTION_EMPTY ) {
			std::cout << "Success: Forced string constructor underflow generated exception "   << " - " << CFLIB_EXCEPTION_FORMATTEDMESSAGE << "\n";
			CFLIB_EXCEPTION_RESET
		}

		if( 5UL < fracThree ) {
			std::cout << "Success: 5UL is < fracThree\n";
		}
		else {
			std::cout << "Failed! 5UL should be < fracThree\n";
			anyTestsFailed = true;
		}
		if( 10L < fracThree ) {
			std::cout << "Success: 10L is < fracThree\n";
		}
		else {
			std::cout << "Failed! 10L should be < fracThree\n";
			anyTestsFailed = true;
		}
		if( fracThree < 5UL ) {
			std::cout << "Failed! fracThree should not be < 5UL\n";
			anyTestsFailed = true;
		}
		else {
			std::cout << "Success: fracThree is not < 5UL\n";
		}
		if( fracThree < 10L ) {
			std::cout << "Failed! fracThree should not be < 10L\n";
			anyTestsFailed = true;
		}
		else {
			std::cout << "Success: fracThree is not < 10L\n";
		}
		if( fracThree < fracFive ) {
			std::cout << "Success: fracThree is < fracFive\n";
		}
		else {
			std::cout << "Failed! fracThree should be < fracFive\n";
			anyTestsFailed = true;
		}
		if( fracFive < fracThree ) {
			std::cout << "Failed! fracFive should not be < fracThree\n";
			anyTestsFailed = true;
		}
		else {
			std::cout << "Success: fracFive is not < fracThree\n";
		}
		if( fracFive < fracFive ) {
			std::cout << "Failed! fracFive should not be < fracFive\n";
			anyTestsFailed = true;
		}
		else {
			std::cout << "Success: fracFive is not < fracFive\n";
		}

		if( 5UL <= fracThree ) {
			std::cout << "Success: 5UL is <= fracThree\n";
		}
		else {
			std::cout << "Failed! 5UL should be <= fracThree\n";
			anyTestsFailed = true;
		}
		if( 10L <= fracThree ) {
			std::cout << "Success: 10L is <= fracThree\n";
		}
		else {
			std::cout << "Failed! 10L should be <= fracThree\n";
			anyTestsFailed = true;
		}
		if( fracThree <= 5UL ) {
			std::cout << "Failed! fracThree should not be <= 5UL\n";
			anyTestsFailed = true;
		}
		else {
			std::cout << "Success: fracThree is not <= 5UL\n";
		}
		if( fracThree <= 10L ) {
			std::cout << "Failed! fracThree should not be <= 10L\n";
			anyTestsFailed = true;
		}
		else {
			std::cout << "Success: fracThree is not <= 10L\n";
		}
		if( fracThree <= fracFive ) {
			std::cout << "Success: fracThree is <= fracFive\n";
		}
		else {
			std::cout << "Failed! fracThree should be <= fracFive\n";
			anyTestsFailed = true;
		}
		if( fracFive <= fracFive ) {
			std::cout << "Success: fracFive is <= fracFive\n";
		}
		else {
			std::cout << "Failed! fracFive should be <= fracFive\n";
			anyTestsFailed = true;
		}
		if( fracFive <= fracThree ) {
			std::cout << "Failed! fracFive should not be <= fracThree\n";
			anyTestsFailed = true;
		}
		else {
			std::cout << "Success: fracFive is not <= fracThree\n";
		}

		if( 5UL == fracThree ) {
			std::cout << "Failed! 5UL should not be == fracThree\n";
			anyTestsFailed = true;
		}
		else {
			std::cout << "Success: 5UL is not == fracThree\n";
		}
		if( 10L == fracThree ) {
			std::cout << "Failed! 10L should not be == fracThree\n";
			anyTestsFailed = true;
		}
		else {
			std::cout << "Success: 10L is not == fracThree\n";
		}
		if( fracThree == 5UL ) {
			std::cout << "Failed! fracThree should not be == 5UL\n";
			anyTestsFailed = true;
		}
		else {
			std::cout << "Success: fracThree is not == 5UL\n";
		}
		if( fracThree == 10L ) {
			std::cout << "Failed! fracThree should not be == 10L\n";
			anyTestsFailed = true;
		}
		else {
			std::cout << "Success: fracThree is not == 10L\n";
		}
		if( fracThree == fracFive ) {
			std::cout << "Failed! fracThree should not be == fracFive\n";
			anyTestsFailed = true;
		}
		else {
			std::cout << "Success: fracThree is not == fracFive\n";
		}
		if( fracFive == fracThree ) {
			std::cout << "Failed! fracFive should not be == fracThree\n";
			anyTestsFailed = true;
		}
		else {
			std::cout << "Success: fracFive is not == fracThree\n";
		}
		if( fracFive == fracFive ) {
			std::cout << "Success: fracFive is == fracFive\n";
		}
		else {
			std::cout << "Failed! fracFive should be == fracFive\n";
			anyTestsFailed = true;
		}

		if( 5UL != fracThree ) {
			std::cout << "Success: 5UL is != fracThree\n";
		}
		else {
			std::cout << "Failed! 5UL should be != fracThree\n";
			anyTestsFailed = true;
		}
		if( 10L != fracThree ) {
			std::cout << "Success: 10L is != fracThree\n";
		}
		else {
			std::cout << "Failed! 10L should be != fracThree\n";
			anyTestsFailed = true;
		}
		if( fracThree != 5UL ) {
			std::cout << "Success: fracThree is != 5UL\n";
		}
		else {
			std::cout << "Failed! fracThree should be !== 5UL\n";
			anyTestsFailed = true;
		}
		if( fracThree != 10L ) {
			std::cout << "Success: fracThree is != 10L\n";
		}
		else {
			std::cout << "Failed! fracThree should be !== 10L\n";
			anyTestsFailed = true;
		}
		if( fracThree != fracFive ) {
			std::cout << "Success: fracThree is != fracFive\n";
		}
		else {
			std::cout << "Failed! fracThree should be != fracFive\n";
			anyTestsFailed = true;
		}
		if( fracFive != fracThree ) {
			std::cout << "Success: fracFive is != fracThree\n";
		}
		else {
			std::cout << "Failed! fracFive should be != fracThree\n";
			anyTestsFailed = true;
		}
		if( fracFive != fracFive ) {
			std::cout << "Failed! fracFive should not be != fracFive\n";
			anyTestsFailed = true;
		}
		else {
			std::cout << "Success: fracFive is not != fracFive\n";
		}

		if( 5UL >= fracThree ) {
			std::cout << "Failed! 5UL should not be >= fracThree\n";
			anyTestsFailed = true;
		}
		else {
			std::cout << "Success: 5UL is not >= fracThree\n";
		}
		if( 10L >= fracThree ) {
			std::cout << "Failed! 10L should not be >= fracThree\n";
			anyTestsFailed = true;
		}
		else {
			std::cout << "Success: 10L is not >= fracThree\n";
		}
		if( fracFive >= 5UL ) {
			std::cout << "Success: fracFive is >= 5UL\n";
		}
		else {
			std::cout << "Failed! fracFive should be >= 5UL\n";
			anyTestsFailed = true;
		}
		if( fracFive >= 10L ) {
			std::cout << "Success: fracFive is >= 10L\n";
		}
		else {
			std::cout << "Failed! fracFive should be >= 10L\n";
			anyTestsFailed = true;
		}
		if( fracThree >= fracFive ) {
			std::cout << "Failed! fracThree should not be >= fracFive\n";
			anyTestsFailed = true;
		}
		else {
			std::cout << "Success: fracThree is not >= fracFive\n";
		}
		if( fracFive >= fracFive ) {
			std::cout << "Success: fracFive >= fracFive\n";
		}
		else {
			std::cout << "Failed! fracFive should be >= fracFive\n";
			anyTestsFailed = true;
		}
		if( fracFive >= fracThree ) {
			std::cout << "Success: fracFive is >= fracThree\n";
		}
		else {
			std::cout << "Failed! fracFive should be >= fracThree\n";
			anyTestsFailed = true;
		}

		if( 5UL > fracThree ) {
			std::cout << "Failed! 5UL should not be > fracThree\n";
			anyTestsFailed = true;
		}
		else {
			std::cout << "Success: 5UL is not > fracThree\n";
		}
		if( 10L > fracThree ) {
			std::cout << "Failed! 10L should not be > fracThree\n";
			anyTestsFailed = true;
		}
		else {
			std::cout << "Success: 10L is not > fracThree\n";
		}
		if( fracFive > 5UL ) {
			std::cout << "Success: fracFive is > 5UL\n";
		}
		else {
			std::cout << "Failed! fracFive should be > 5UL\n";
			anyTestsFailed = true;
		}
		if( fracFive > 10L ) {
			std::cout << "Success: fracFive is > 10L\n";
		}
		else {
			std::cout << "Failed! fracFive should be > 10L\n";
			anyTestsFailed = true;
		}
		if( fracThree > fracFive ) {
			std::cout << "Failed! fracThree should not be > fracFive\n";
			anyTestsFailed = true;
		}
		else {
			std::cout << "Success: fracThree is > fracFive\n";
		}
		if( fracFive > fracThree ) {
			std::cout << "Success: fracFive is > fracThree\n";
		}
		else {
			std::cout << "Failed! fracFive should be > fracThree\n";
			anyTestsFailed = true;
		}
		if( fracFive > fracFive ) {
			std::cout << "Failed! fracFive should not be > fracFive\n";
			anyTestsFailed = true;
		}
		else {
			std::cout << "Success: fracFive is not > fracFive\n";
		}

		cflib::TCFLibBigDecimal<20,5> assignFive;
		cflib::TCFLibBigDecimal<20,3> assignThree;
		cflib::TCFLibBigDecimal<20,0> assignInt;
		std::cout << "Execute assignInt = assignThree = assignFive = fracFive;\n";
		assignInt = assignThree = assignFive = fracFive;
		std::cout << "\tassignFive is " << assignFive.toString() << "\n";
		std::cout << "\tassignThree is " << assignThree.toString() << "\n";
		std::cout << "\tassignInt is " << assignInt.toString() << "\n";

		std::cout << "Executing various assignment overloads\n";
		cflib::TCFLibBigDecimal<20,0> uintAssignFive;
		uintAssignFive = 5UL;
		cflib::TCFLibBigDecimal<20,0> intAssignTen;
		intAssignTen = 10L;
		cflib::TCFLibBigDecimal<20,5> stringAssignDecimalString;
		stringAssignDecimalString = "12345678901234.56789";
		std::cout << "\tuintAssignFive is " << uintAssignFive.toString() << "\n";
		std::cout << "\tintAssignTen is " << intAssignTen.toString() << "\n";
		std::cout << "\tstringAssignDecimalString is " << stringAssignDecimalString.toString() << "\n";

		cflib::TCFLibBigDecimal<20,5> five( 5UL );
		cflib::TCFLibBigDecimal<20,5> ten( 10UL );
		std::cout << "five is " << five.toString() << "\n";
		std::cout << "ten is " << ten.toString() << "\n";

		cflib::TCFLibBigDecimal<20,5> uintFivePlusTen = five + 10UL;
		if( uintFivePlusTen != 15L ) {
			anyTestsFailed = true;
			std::cout << "Failed! uintFivePlusTen is " << uintFivePlusTen.toString() << ", should be 15\n";
		}
		else {
			std::cout << "Success! uintFivePlusTen is " << uintFivePlusTen.toString() << "\n";
		}
		cflib::TCFLibBigDecimal<20,5> intFivePlusTen = five + 10L;
		if( intFivePlusTen != 15L ) {
			anyTestsFailed = true;
			std::cout << "Failed! intFivePlusTen is " << intFivePlusTen.toString() << ", should be 15\n";
		}
		else {
			std::cout << "Success! intFivePlusTen is " << intFivePlusTen.toString() << "\n";
		}
		cflib::TCFLibBigDecimal<20,5> doubleFivePlusTen = five + ((double)10.0);
		if( doubleFivePlusTen != 15L ) {
			anyTestsFailed = true;
			std::cout << "Failed! doubleFivePlusTen is " << doubleFivePlusTen.toString() << ", should be 15\n";
		}
		else {
			std::cout << "Success! doubleFivePlusTen is " << doubleFivePlusTen.toString() << "\n";
		}
		cflib::TCFLibBigDecimal<20,5> mpfrFivePlusTen = five + ten.getValue();
		if( mpfrFivePlusTen != 15L ) {
			anyTestsFailed = true;
			std::cout << "Failed! mpfrFivePlusTen is " << mpfrFivePlusTen.toString() << ", should be 15\n";
		}
		else {
			std::cout << "Success! mpfrFivePlusTen is " << mpfrFivePlusTen.toString() << "\n";
		}
		cflib::TCFLibBigDecimal<20,5> cflibFivePlusTen = five + ten;
		if( cflibFivePlusTen != 15L ) {
			anyTestsFailed = true;
			std::cout << "Failed! cflibFivePlusTen is " << cflibFivePlusTen.toString() << ", should be 15\n";
		}
		else {
			std::cout << "Success! cflibFivePlusTen is " << cflibFivePlusTen.toString() << "\n";
		}

		cflib::TCFLibBigDecimal<20,5> uintTenMinusFive = ten - 5UL;
		if( uintTenMinusFive != 5L ) {
			anyTestsFailed = true;
			std::cout << "Failed! uintTenMinusFive is " << uintTenMinusFive.toString() << ", should be 5\n";
		}
		else {
			std::cout << "Success! uintTenMinusFive is " << uintTenMinusFive.toString() << "\n";
		}
		cflib::TCFLibBigDecimal<20,5> intTenMinusFive = ten - 5L;
		if( intTenMinusFive != 5L ) {
			anyTestsFailed = true;
			std::cout << "Failed! intTenMinusFive is " << intTenMinusFive.toString() << ", should be 5\n";
		}
		else {
			std::cout << "Success! intTenMinusFive is " << intTenMinusFive.toString() << "\n";
		}
		cflib::TCFLibBigDecimal<20,5> doubleTenMinusFive = ten - ((double)5.0);
		if( doubleTenMinusFive != 5L ) {
			anyTestsFailed = true;
			std::cout << "Failed! doubleTenMinusFive is " << doubleTenMinusFive.toString() << ", should be 5\n";
		}
		else {
			std::cout << "Success! doubleTenMinusFive is " << doubleTenMinusFive.toString() << "\n";
		}
		cflib::TCFLibBigDecimal<20,5> mpfrTenMinusFive = ten - five.getValue();
		if( mpfrTenMinusFive != 5L ) {
			anyTestsFailed = true;
			std::cout << "Failed! mpfrTenMinusFive is " << mpfrTenMinusFive.toString() << ", should be 5\n";
		}
		else {
			std::cout << "Success! mpfrTenMinusFive is " << mpfrTenMinusFive.toString() << "\n";
		}
		cflib::TCFLibBigDecimal<20,5> cflibTenMinusFive = ten - five;
		if( cflibTenMinusFive != 5L ) {
			anyTestsFailed = true;
			std::cout << "Failed! cflibTenMinusFive is " << cflibTenMinusFive.toString() << ", should be 5\n";
		}
		else {
			std::cout << "Success! cflibTenMinusFive is " << cflibTenMinusFive.toString() << "\n";
		}

		cflib::TCFLibBigDecimal<20,5> uintFiveTimesTen = five * 10UL;
		if( uintFiveTimesTen != 50L ) {
			anyTestsFailed = true;
			std::cout << "Failed! uintFiveTimesTen is " << uintFiveTimesTen.toString() << ", should be 50\n";
		}
		else {
			std::cout << "Success! uintFiveTimesTen is " << uintFiveTimesTen.toString() << "\n";
		}
		cflib::TCFLibBigDecimal<20,5> intFiveTimesTen = five * 10L;
		if( intFiveTimesTen != 50L ) {
			anyTestsFailed = true;
			std::cout << "Failed! intFiveTimesTen is " << intFiveTimesTen.toString() << ", should be 50\n";
		}
		else {
			std::cout << "Success! intFiveTimesTen is " << intFiveTimesTen.toString() << "\n";
		}
		cflib::TCFLibBigDecimal<20,5> doubleFiveTimesTen = five * ((double)10.0);
		if( doubleFiveTimesTen != 50L ) {
			anyTestsFailed = true;
			std::cout << "Failed! doubleFiveTimesTen is " << doubleFiveTimesTen.toString() << ", should be 50\n";
		}
		else {
			std::cout << "Success! doubleFiveTimesTen is " << doubleFiveTimesTen.toString() << "\n";
		}
		cflib::TCFLibBigDecimal<20,5> mpfrFiveTimesTen = five * ten.getValue();
		if( mpfrFiveTimesTen != 50L ) {
			anyTestsFailed = true;
			std::cout << "Failed! mpfrFiveTimesTen is " << mpfrFiveTimesTen.toString() << ", should be 50\n";
		}
		else {
			std::cout << "Success! mpfrFiveTimesTen is " << mpfrFiveTimesTen.toString() << "\n";
		}
		cflib::TCFLibBigDecimal<20,5> cflibFiveTimesTen = five * ten;
		if( cflibFiveTimesTen != 50L ) {
			anyTestsFailed = true;
			std::cout << "Failed! cflibFiveTimesTen is " << cflibFiveTimesTen.toString() << ", should be 50\n";
		}
		else {
			std::cout << "Success! cflibFiveTimesTen is " << cflibFiveTimesTen.toString() << "\n";
		}

		cflib::TCFLibBigDecimal<20,5> uintFiveDividedByTen = five / 10UL;
		if( uintFiveDividedByTen != ((double)0.5) ) {
			anyTestsFailed = true;
			std::cout << "Failed! uintFiveDividedByTen is " << uintFiveDividedByTen.toString() << ", should be 0.5\n";
		}
		else {
			std::cout << "Success! uintFiveDividedByTen is " << uintFiveDividedByTen.toString() << "\n";
		}
		cflib::TCFLibBigDecimal<20,5> intFiveDividedByTen = five / 10L;
		if( intFiveDividedByTen != ((double)0.5) ) {
			anyTestsFailed = true;
			std::cout << "Failed! intFiveDividedByTen is " << intFiveDividedByTen.toString() << ", should be 0.5\n";
		}
		else {
			std::cout << "Success! intFiveDividedByTen is " << intFiveDividedByTen.toString() << "\n";
		}
		cflib::TCFLibBigDecimal<20,5> doubleFiveDividedByTen = five / ((double)10.0);
		if( doubleFiveDividedByTen != ((double)0.5) ) {
			anyTestsFailed = true;
			std::cout << "Failed! doubleFiveDividedByTen is " << doubleFiveDividedByTen.toString() << ", should be 0.5\n";
		}
		else {
			std::cout << "Success! doubleFiveDividedByTen is " << doubleFiveDividedByTen.toString() << "\n";
		}
		cflib::TCFLibBigDecimal<20,5> mpfrFiveDividedByTen = five / ten.getValue();
		if( mpfrFiveDividedByTen != ((double)0.5) ) {
			anyTestsFailed = true;
			std::cout << "Failed! mpfrFiveDividedByTen is " << mpfrFiveDividedByTen.toString() << ", should be 0.5\n";
		}
		else {
			std::cout << "Success! mpfrFiveDividedByTen is " << mpfrFiveDividedByTen.toString() << "\n";
		}
		cflib::TCFLibBigDecimal<20,5> cflibFiveDividedByTen = five / ten;
		if( cflibFiveDividedByTen != ((double)0.5) ) {
			anyTestsFailed = true;
			std::cout << "Failed! cflibFiveDividedByTen is " << cflibFiveDividedByTen.toString() << ", should be 0.5\n";
		}
		else {
			std::cout << "Success! cflibFiveDividedByTen is " << cflibFiveDividedByTen.toString() << "\n";
		}

		cflib::TCFLibBigDecimal<20,5> uintTenRemainderFive = ten % 5UL;
		if( uintTenRemainderFive != 0L ) {
			anyTestsFailed = true;
			std::cout << "Failed! uintTenRemainderFive is " << uintTenRemainderFive.toString() << ", should be 0\n";
		}
		else {
			std::cout << "Success! uintTenRemainderFive is " << uintTenRemainderFive.toString() << "\n";
		}
		cflib::TCFLibBigDecimal<20,5> intTenRemainderFive = ten % 5L;
		if( intTenRemainderFive != 0L ) {
			anyTestsFailed = true;
			std::cout << "Failed! intTenRemainderFive is " << intTenRemainderFive.toString() << ", should be 0\n";
		}
		else {
			std::cout << "Success! intTenRemainderFive is " << intTenRemainderFive.toString() << "\n";
		}
		cflib::TCFLibBigDecimal<20,5> doubleTenRemainderFive = ten % ((double)5.0);
		if( doubleTenRemainderFive != 0L ) {
			anyTestsFailed = true;
			std::cout << "Failed! doubleTenRemainderFive is " << doubleTenRemainderFive.toString() << ", should be 0\n";
		}
		else {
			std::cout << "Success! doubleTenRemainderFive is " << doubleTenRemainderFive.toString() << "\n";
		}
		cflib::TCFLibBigDecimal<20,5> mpfrTenRemainderFive = ten % five.getValue();
		if( mpfrTenRemainderFive != 0L ) {
			anyTestsFailed = true;
			std::cout << "Failed! mpfrTenRemainderFive is " << mpfrTenRemainderFive.toString() << ", should be 0\n";
		}
		else {
			std::cout << "Success! mpfrTenRemainderFive is " << mpfrTenRemainderFive.toString() << "\n";
		}
		cflib::TCFLibBigDecimal<20,5> cflibTenRemainderFive = ten % five;
		if( cflibTenRemainderFive != 0L ) {
			anyTestsFailed = true;
			std::cout << "Failed! cflibTenRemainderFive is " << cflibTenRemainderFive.toString() << ", should be 0\n";
		}
		else {
			std::cout << "Success! cflibTenRemainderFive is " << cflibTenRemainderFive.toString() << "\n";
		}
	}
	CFLIB_EXCEPTION_CATCH_GOTO( report_test_failed )
	goto cleanup_and_exit;

report_test_failed:
	anyTestsFailed = true;
	retval = 1;
	std::cerr << S_ProcName + " EXCEPTION: Test failed: " + CFLIB_EXCEPTION_FORMATTEDMESSAGE + "\n";

cleanup_and_exit:
	if( anyTestsFailed ) {
		std::cout << "\nTCFLibBigDecimal FAILED " + S_ProcName + " TESTING\n";
	}
	else {
		std::cout << "\nSUCCESS!!! TCFLibBigDecimal passed " + S_ProcName + " testing\n";
	}

	try {
		cflib::CFLib::release();
	}
	catch( ... ) {
	}

	return( retval );
}
