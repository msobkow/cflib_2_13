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

package com.msscftech.msscf.cflib.CFLib.JavaFX;

import java.text.DecimalFormat;
import java.text.Format;
import javafx.scene.control.TableCell;

import com.msscftech.msscf.cflib.CFLib.*;

public class CFUInt16TableCell<T>
extends TableCell<T,Integer>
{
	protected static Format defaultFormat = null;
	public static Format getDefaultFormat() {
		if( defaultFormat == null ) {
			defaultFormat = new DecimalFormat( "####0" );
		}
		return( defaultFormat );
	}

	@Override protected void updateItem( Integer item, boolean empty ) {
		super.updateItem( item, empty );
		if( ( item == null ) || empty ) {
			setText( null );
			setStyle( "" );
		}
		else {
			Format fmt = getDefaultFormat();
			String cellText = fmt.format( item );
			setText( cellText );
			setStyle( "-fx-alignment: CENTER-RIGHT" );
		}
	}
}
