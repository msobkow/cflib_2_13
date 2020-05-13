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
#include <cflib/CFLibNullableUInt32.hpp>
#include <cflib/CFLibNullArgumentException.hpp>

namespace cflib {

const std::string CFLibNullableUInt32::CLASS_NAME( "CFLibNullableUInt32" );;

CFLibNullableUInt32::CFLibNullableUInt32() {
	value = 0;
}

CFLibNullableUInt32::CFLibNullableUInt32( const uint32_t arg ) {
	setNullFlag( false );
	value = arg;
}

CFLibNullableUInt32::~CFLibNullableUInt32() {
}

const uint32_t CFLibNullableUInt32::getValue() const {
	if( nullFlag ) {
		throw CFLibNullArgumentException( CLASS_NAME,
			S_GET_VALUE,
			0,
			S_VALUE );
	}
	return( value );
}

const uint32_t* CFLibNullableUInt32::getReference() const {
	if( nullFlag ) {
		return( NULL );
	}
	else {
		return( &value );
	}
}

void CFLibNullableUInt32::setValue( const uint32_t arg ) {
	setNullFlag( false );
	value = arg;
}

void CFLibNullableUInt32::setNull() {
	setNullFlag( true );
}

}
