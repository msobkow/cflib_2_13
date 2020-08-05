/*
 *	MSS Code Factory CFLib 2.13
 *
 *	Copyright (c) 2020 Mark Stephen Sobkow
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
 *	Contact Mark Stephen Sobkow at msobkow@sasktel.net for commercial licensing.
 */

package org.msscf.msscf.cflib.CFLib;

public class CFLibFireOnInstanceOf {
	
    @SuppressWarnings("rawtypes")
	protected Class instOf = null;

    public CFLibFireOnInstanceOf() {
    	setInstanceOf( Object.class );
    }

    public CFLibFireOnInstanceOf( @SuppressWarnings("rawtypes") Class value ) {
    	setInstanceOf( value );
    }

    public void setInstanceOf( @SuppressWarnings("rawtypes") Class value ) {
    	final String S_ProcName = "setInstanceOf";
        if( value == null ) {
            throw new CFLibNullArgumentException( getClass(),
                S_ProcName,
                1,
                "value" );
        }
        instOf = value;
    }

    @SuppressWarnings("rawtypes")
	public Class getInstanceOf() {
        return( instOf );
    }

    public boolean isInstanceOf( ICFLibAnyObj obj ) {
    	if( obj == null ) {
    		return( false );
    	}

    	if( instOf == null ) {
    		return( false );
    	}

    	return( instOf.isInstance( obj ) );
    }

    public void onInstanceOf( ICFLibAnyObj obj ) {
        final String S_ProcName = "onInstanceOf";
        if( obj == null ) {
            return;
        }
        throw new CFLibNotImplementedYetException( getClass(),
        	S_ProcName );
    }

    public final void fireOnInstanceOf( ICFLibAnyObj obj ) {
    	if( obj == null ) {
    		return;
    	}
        if( isInstanceOf( obj ) ) {
            onInstanceOf( obj );
        }
    }
}
