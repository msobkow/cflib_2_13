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

#include <cstdint>
#include <string>
#include <cflib/CFLibNullable.hpp>

namespace cflib {

	class CFLibNullableUInt16 : public CFLibNullable {

	public:
		static const std::string CLASS_NAME;

	protected:

		uint16_t	value;

	public:
		CFLibNullableUInt16();
		CFLibNullableUInt16( const uint16_t arg );
		~CFLibNullableUInt16();

		const uint16_t getValue() const;
		const uint16_t* getReference() const;
		void setValue( const uint16_t arg );
		void setNull();
	};
}
