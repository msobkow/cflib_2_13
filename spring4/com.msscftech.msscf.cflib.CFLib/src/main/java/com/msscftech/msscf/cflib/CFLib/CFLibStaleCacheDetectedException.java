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

package com.msscftech.msscf.cflib.CFLib;

import java.util.*;

public class CFLibStaleCacheDetectedException extends IllegalStateException {

	public CFLibStaleCacheDetectedException(
		String msg )
	{
		super( msg );
	}

	public CFLibStaleCacheDetectedException(
		Class throwingClass,
		String methName,
		String msg )
	{
		super( throwingClass.getName()
					+ ( ( ( methName != null ) && ( methName.length() > 0 ))
						? "." + methName
						: "" )
					+ "() "
					+ ( ( ( msg != null ) && ( msg.length() > 0 ) )
						? msg
						: "" ) );
	}

	public CFLibStaleCacheDetectedException(
		Class throwingClass,
		String methName,
		String msg,
		Throwable th )
	{
		super( throwingClass.getName()
					+ ( ( ( methName != null ) && ( methName.length() > 0 ))
						? "." + methName
						: "" )
					+ "() "
					+ ( ( ( msg != null ) && ( msg.length() > 0 ) )
						? msg
						: "" ),
				th );
	}

	public CFLibStaleCacheDetectedException(
		String fieldName,
		String msg )
	{
		super( fieldName + "() "
					+ ( ( ( msg != null ) && ( msg.length() > 0 ) )
						? msg
						: "" ) );
	}

	public CFLibStaleCacheDetectedException(
		String fieldName,
		String methName,
		String msg )
	{
		super( fieldName
					+ ( ( ( methName != null ) && ( methName.length() > 0 ))
						? "." + methName
						: "" )
					+ "() "
					+ ( ( ( msg != null ) && ( msg.length() > 0 ) )
						? msg
						: "" ) );
	}

	public CFLibStaleCacheDetectedException(
		String fieldName,
		String methName,
		String msg,
		Throwable th )
	{
		super( fieldName
					+ ( ( ( methName != null ) && ( methName.length() > 0 ))
						? "." + methName
						: "" )
					+ "() "
					+ ( ( ( msg != null ) && ( msg.length() > 0 ) )
						? msg
						: "" ),
				th );
	}

	public CFLibStaleCacheDetectedException()
	{
		super( "Stale cache detected" );
	}

	public CFLibStaleCacheDetectedException(
		Class throwingClass,
		String methName )
	{
		super( throwingClass.getName()
					+ ( ( ( methName != null ) && ( methName.length() > 0 ))
						? "." + methName
						: "" )
					+ "() Stale cache detected" );
	}

	public CFLibStaleCacheDetectedException(
		Class throwingClass,
		String methName,
		Throwable th )
	{
		super( throwingClass.getName()
					+ ( ( ( methName != null ) && ( methName.length() > 0 ))
						? "." + methName
						: "" )
					+ "() Stale cache detected",
				th );
	}

	public CFLibStaleCacheDetectedException(
		String fieldName,
		String methName,
		Throwable th )
	{
		super( fieldName
					+ ( ( ( methName != null ) && ( methName.length() > 0 ))
						? "." + methName
						: "" )
					+ "() Stale cache detected",
				th );
	}

	public CFLibStaleCacheDetectedException(
		Class throwingClass,
		String methName,
		String msgCause,
		String targetTable,
		Object argKey )
	{
		super( throwingClass.getName()
					+ ( ( ( methName != null ) && ( methName.length() > 0 ))
						? "." + methName
						: ""
				+ "Stale cache detected due to " + msgCause
					+ ( ( ( targetTable != null ) && ( targetTable.length() > 0 ) )
							? " by " + targetTable
							: "" )
					+ ( ( argKey != null )
							? " key " + argKey.toString()
							: "" ) ) );
	}

	public CFLibStaleCacheDetectedException(
		Class throwingClass,
		String methName,
		String msgCause,
		String targetTable,
		Object argKey,
		Throwable th )
	{
		super( throwingClass.getName()
					+ ( ( ( methName != null ) && ( methName.length() > 0 ))
						? "." + methName
						: ""
				+ "Stale cache detected due to " + msgCause
					+ ( ( ( targetTable != null ) && ( targetTable.length() > 0 ) )
							? " by " + targetTable
							: "" )
					+ ( ( argKey != null )
							? " key " + argKey.toString()
							: "" ) ),
				th );
	}
}
