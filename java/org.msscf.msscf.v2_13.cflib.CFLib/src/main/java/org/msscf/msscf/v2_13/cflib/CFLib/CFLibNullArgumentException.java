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

package org.msscf.msscf.v2_13.cflib.CFLib;

import java.util.*;

public class CFLibNullArgumentException extends CFLibArgumentException {

	public CFLibNullArgumentException(
		String msg )
	{
		super( msg );
	}

	public CFLibNullArgumentException(
		Class throwingClass,
		String methName,
		String msg )
	{
		super( throwingClass, methName, msg );
	}

	public CFLibNullArgumentException(
		Class throwingClass,
		String methName,
		String msg,
		Throwable th )
	{
		super( throwingClass, methName, msg, th );
	}

	public CFLibNullArgumentException(
		Class throwingClass,
		String methName,
		int argNo,
		String argName,
		String msg )
	{
		super( throwingClass, methName, argNo, argName, msg );
	}

	public CFLibNullArgumentException(
		Class throwingClass,
		String methName,
		int argNo,
		String argName,
		String msg,
		Throwable th )
	{
		super( throwingClass, methName, argNo, argName, msg, th );
	}

	public CFLibNullArgumentException(
		Class throwingClass,
		String methName,
		int argNo,
		String argName )
	{
		super( throwingClass, methName, argNo, argName,
			"is null" );
	}

	public CFLibNullArgumentException(
		Class throwingClass,
		String methName,
		int argNo,
		String argName,
		Throwable th )
	{
		super( throwingClass, methName, argNo, argName,
			"is null",
			th );
	}

	public CFLibNullArgumentException(
		String fieldName,
		String msg )
	{
		super( fieldName, msg );
	}

	public CFLibNullArgumentException(
		String fieldName,
		String methName,
		String msg )
	{
		super( fieldName, methName, msg );
	}

	public CFLibNullArgumentException(
		String fieldName,
		String methName,
		String msg,
		Throwable th )
	{
		super( fieldName, methName, msg, th );
	}

	public CFLibNullArgumentException(
		String fieldName,
		String methName,
		int argNo,
		String argName,
		String msg )
	{
		super( fieldName, methName, argNo, argName, msg );
	}

	public CFLibNullArgumentException(
		String fieldName,
		String methName,
		int argNo,
		String argName,
		String msg,
		Throwable th )
	{
		super( fieldName, methName, argNo, argName, msg, th );
	}

	public CFLibNullArgumentException(
		String fieldName,
		String methName,
		int argNo,
		String argName )
	{
		super( fieldName, methName, argNo, argName,
			"is null" );
	}

	public CFLibNullArgumentException(
		String fieldName,
		String methName,
		int argNo,
		String argName,
		Throwable th )
	{
		super( fieldName, methName, argNo, argName,
			"is null",
			th );
	}
}
