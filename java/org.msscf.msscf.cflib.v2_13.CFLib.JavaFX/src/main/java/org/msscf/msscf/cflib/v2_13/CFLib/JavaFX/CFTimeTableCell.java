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

package org.msscf.msscf.cflib.v2_13.CFLib.JavaFX;

import java.text.Format;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.UUID;
import javafx.scene.control.TableCell;

import org.msscf.msscf.cflib.v2_13.CFLib.*;

public class CFTimeTableCell<T>
extends TableCell<T,Calendar>
{
	protected static Format defaultFormat = null;
	public static Format getDefaultFormat() {
		if( defaultFormat == null ) {
			defaultFormat = new SimpleDateFormat( "HH:mm:ss" );
		}
		return( defaultFormat );
	}

	@Override protected void updateItem( Calendar item, boolean empty ) {
		super.updateItem( item, empty );
		if( ( item == null ) || empty ) {
			setText( null );
			setStyle( "" );
		}
		else {
			Format fmt = getDefaultFormat();
			Calendar withoutDate = Calendar.getInstance();
			withoutDate.clear();
			withoutDate.set( Calendar.HOUR_OF_DAY, item.get( Calendar.HOUR_OF_DAY ) );
			withoutDate.set( Calendar.MINUTE, item.get( Calendar.MINUTE ) );
			withoutDate.set( Calendar.SECOND, item.get( Calendar.SECOND ) );
			String cellText = fmt.format( withoutDate.getTime() );
			setText( cellText );
			setStyle( "-fx-alignment: CENTER-LEFT" );
		}
	}
}