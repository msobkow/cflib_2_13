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
 *	Contact Mark Stephen Sobkow at mark.sobkow@gmail.com for commercial licensing.
 */

package com.msscftech.msscf.cflib.CFLib.JavaFX;

import javafx.scene.control.TitledPane;

import com.msscftech.msscf.cflib.CFLib.*;

public class CFTitledPane
extends TitledPane
implements ICFPaneCommon
{
	protected ICFLibAnyObj javaFXFocus = null;
	protected CFPane.PaneMode paneMode = CFPane.PaneMode.Unknown;
	
	public CFTitledPane() {
		super();
	}

	public ICFLibAnyObj getJavaFXFocus() {
		return( javaFXFocus );
	}
	
	public void setJavaFXFocus( ICFLibAnyObj value ) {
		javaFXFocus = value;
	}
	
	public CFPane.PaneMode getPaneMode() {
		return( paneMode );
	}
	
	public void setPaneMode( CFPane.PaneMode value ) {
		paneMode = value;
	}
}
