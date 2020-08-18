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

package org.msscf.msscf.v2_13.cflib.CFLib;

import java.util.*;

public class CFLibCollisionDetectedException extends CFLibRuntimeException {

	protected Object indexKey = null;

	public CFLibCollisionDetectedException(
		String msg )
	{
		super( msg );
	}

	public CFLibCollisionDetectedException(
		Class throwingClass,
		String methName,
		String msg )
	{
		super( throwingClass, methName, msg );
	}

	public CFLibCollisionDetectedException(
		Class throwingClass,
		String methName,
		String msg,
		Throwable th )
	{
		super( throwingClass, methName, msg, th );
	}

	public CFLibCollisionDetectedException(
		Class throwingClass,
		String methName,
		Object argKey )
	{
		super( throwingClass, methName,
			"Collision detected"
				+ ( ( argKey != null )
						? " for primary key " + argKey.toString()
						: "" ) );
		indexKey = argKey;
	}

	public CFLibCollisionDetectedException(
		Class throwingClass,
		String methName,
		Object argKey,
		Throwable th )
	{
		super( throwingClass, methName,
			"Collision detected"
				+ ( ( argKey != null )
						? " for primary key " + argKey.toString()
						: "" ),
			th );
		indexKey = argKey;
	}

	public Object getIndexKey() {
		return( indexKey );
	}
}
