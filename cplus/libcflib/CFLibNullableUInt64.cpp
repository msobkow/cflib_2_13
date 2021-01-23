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

#include <cflib/CFLib.hpp>
#include <cflib/CFLibNullableUInt64.hpp>
#include <cflib/CFLibNullArgumentException.hpp>

namespace cflib {

const std::string CFLibNullableUInt64::CLASS_NAME( "CFLibNullableUInt64" );;

CFLibNullableUInt64::CFLibNullableUInt64() {
	value = 0;
}

CFLibNullableUInt64::CFLibNullableUInt64( const uint64_t arg ) {
	setNullFlag( false );
	value = arg;
}

CFLibNullableUInt64::~CFLibNullableUInt64() {
}

const uint64_t CFLibNullableUInt64::getValue() const {
	if( nullFlag ) {
		throw CFLibNullArgumentException( CLASS_NAME,
			S_GET_VALUE,
			0,
			S_VALUE );
	}
	return( value );
}

const uint64_t* CFLibNullableUInt64::getReference() const {
	if( nullFlag ) {
		return( NULL );
	}
	else {
		return( &value );
	}
}

void CFLibNullableUInt64::setValue( const uint64_t arg ) {
	setNullFlag( false );
	value = arg;
}

void CFLibNullableUInt64::setNull() {
	setNullFlag( true );
}

}
