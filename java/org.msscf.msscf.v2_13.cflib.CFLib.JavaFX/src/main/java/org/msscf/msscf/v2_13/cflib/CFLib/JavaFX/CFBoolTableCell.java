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

package org.msscf.msscf.v2_13.cflib.CFLib.JavaFX;

import javafx.scene.control.TableCell;

import org.msscf.msscf.v2_13.cflib.CFLib.*;

public class CFBoolTableCell<T>
extends TableCell<T,Boolean>
{
	@Override protected void updateItem( Boolean item, boolean empty ) {
		super.updateItem( item, empty );
		if( empty ) {
			setText( null );
			setStyle( "" );
		}
		else if( item == null ) {
			setText( "?" );
			setStyle( "-fx-alignment: CENTER" );
		}
		else {
			boolean value = item.booleanValue();
			String cellText;
			if( value ) {
				cellText = "T";
			}
			else {
				cellText = "F";
			}
			setText( cellText );
			setStyle( "-fx-alignment: CENTER" );
		}
	}
}