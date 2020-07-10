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

package com.github.msobkow.cflib.CFLib.JavaFX;

import javafx.scene.control.TableCell;

import com.github.msobkow.cflib.CFLib.*;

public class CFReferenceTableCell<T,R>
extends TableCell<T,R>
{
	@Override protected void updateItem( R item, boolean empty ) {
		super.updateItem( item, empty );
		if( ( item == null ) || empty ) {
			setText( null );
			setStyle( "" );
		}
		else {
			String cellText = ((ICFLibAnyObj)item).getObjQualifiedName();
			if( cellText == null ) {
				cellText = "";
			}
			int firstNewline = cellText.indexOf( '\n' );
			if( firstNewline < 0 ) {
				firstNewline = cellText.indexOf( '\r' );
				if( firstNewline < 0 ) {
					firstNewline = cellText.indexOf( '\f' );
					if( firstNewline < 0 ) {
						firstNewline = cellText.length();
					}
				}
			}
			String firstLine = cellText.substring( 0, firstNewline );
			setText( firstLine );
			setStyle( "-fx-alignment: CENTER-LEFT" );
		}
	}
}