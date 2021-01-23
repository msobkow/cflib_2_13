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

import com.msscftech.msscf.cflib.CFLib.*;

/**
 *	Any Node being set as a display form must be castable to ICFForm.
 *
 *	The form manager makes calls through this interface to ensure
 *	that forms are cleaned up when an application logs out or resets
 *	to the root form for a facet.
 */
public interface ICFForm
{
	/**
	 *	Get the form manager associated with this form.
	 */
	ICFFormManager getCFFormManager();

	/**
	 *	Force the form to cancel and close.  The form should invoke
	 *	ICFFormManager.closeCurrentForm(), but if it doesn't, the
	 *	form manager will force the form off the stack after
	 *	invoking this callback.
	 */
	void forceCancelAndClose();
}
