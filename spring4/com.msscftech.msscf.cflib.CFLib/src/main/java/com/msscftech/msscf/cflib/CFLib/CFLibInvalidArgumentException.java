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

package com.msscftech.msscf.cflib.CFLib;

import java.util.*;

public class CFLibInvalidArgumentException extends CFLibArgumentException {

	public CFLibInvalidArgumentException(
		String msg )
	{
		super( msg );
	}

	public CFLibInvalidArgumentException(
		Class throwingClass,
		String methName,
		String msg )
	{
		super( throwingClass, methName, msg );
	}

	public CFLibInvalidArgumentException(
		Class throwingClass,
		String methName,
		String msg,
		Throwable th )
	{
		super( throwingClass, methName, msg, th );
	}

	public CFLibInvalidArgumentException(
		Class throwingClass,
		String methName,
		int argNo,
		String argName,
		String msg )
	{
		super( throwingClass, methName, argNo, argName, msg );
	}

	public CFLibInvalidArgumentException(
		Class throwingClass,
		String methName,
		int argNo,
		String argName,
		String msg,
		Throwable th )
	{
		super( throwingClass, methName, argNo, argName, msg, th );
	}

	public CFLibInvalidArgumentException(
		String fieldName,
		String msg )
	{
		super( fieldName, msg );
	}

	public CFLibInvalidArgumentException(
		String fieldName,
		String methName,
		String msg )
	{
		super( fieldName, methName, msg );
	}

	public CFLibInvalidArgumentException(
		String fieldName,
		String methName,
		String msg,
		Throwable th )
	{
		super( fieldName, methName, msg, th );
	}

	public CFLibInvalidArgumentException(
		String fieldName,
		String methName,
		int argNo,
		String argName,
		String msg )
	{
		super( fieldName, methName, argNo, argName, msg );
	}

	public CFLibInvalidArgumentException(
		String fieldName,
		String methName,
		int argNo,
		String argName,
		String msg,
		Throwable th )
	{
		super( fieldName, methName, argNo, argName, msg, th );
	}

	public CFLibInvalidArgumentException(
		String fieldName,
		String methName,
		int argNo,
		String argName )
	{
		super( fieldName, methName, argNo, argName, "Invalid argument" );
	}

	public CFLibInvalidArgumentException(
		String fieldName,
		String methName,
		int argNo,
		String argName,
		Throwable th )
	{
		super( fieldName, methName, argNo, argName, "Invalid argument", th );
	}
}
