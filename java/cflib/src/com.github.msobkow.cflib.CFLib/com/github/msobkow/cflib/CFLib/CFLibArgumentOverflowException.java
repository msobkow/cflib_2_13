/*
 *  MSS Code Factory CFLib 2.13
 *
 *	Copyright 2020 Mark Stephen Sobkow
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
 *	Please contact Mark Stephen Sobkow at msobkow@sasktel.net for commercial licensing.
 */

package com.github.msobkow.cflib.CFLib;

import java.util.*;

import java.util.Calendar;
import java.math.*;

public class CFLibArgumentOverflowException extends CFLibArgumentException {

	public CFLibArgumentOverflowException(
		String msg )
	{
		super( msg );
	}

	public CFLibArgumentOverflowException(
		Class throwingClass,
		String methName,
		String msg )
	{
		super( throwingClass, methName, msg );
	}

	public CFLibArgumentOverflowException(
		Class throwingClass,
		String methName,
		String msg,
		Throwable th )
	{
		super( throwingClass, methName, msg, th );
	}

	public CFLibArgumentOverflowException(
		Class throwingClass,
		String methName,
		int argNo,
		String argName,
		String msg )
	{
		super( throwingClass, methName, argNo, argName, msg );
	}

	public CFLibArgumentOverflowException(
		Class throwingClass,
		String methName,
		int argNo,
		String argName,
		String msg,
		Throwable th )
	{
		super( throwingClass, methName, argNo, argName, msg, th );
	}

	public CFLibArgumentOverflowException(
		Class throwingClass,
		String methName,
		int argNo,
		String argName,
		short argValue,
		short maxValue )
	{
		super( throwingClass, methName, argNo, argName,
			"value " + Short.toString( argValue )
				+ " must be no more than "
				+ Short.toString( maxValue ) );
	}

	public CFLibArgumentOverflowException(
		Class throwingClass,
		String methName,
		int argNo,
		String argName,
		short argValue,
		short maxValue,
		Throwable th )
	{
		super( throwingClass, methName, argNo, argName,
			"value " + Short.toString( argValue )
				+ " must be no more than "
				+ Short.toString( maxValue ),
			th );
	}

	public CFLibArgumentOverflowException(
		Class throwingClass,
		String methName,
		int argNo,
		String argName,
		int argValue,
		int maxValue )
	{
		super( throwingClass, methName, argNo, argName,
			"value " + Integer.toString( argValue )
				+ " must be no more than "
				+ Integer.toString( maxValue ) );
	}

	public CFLibArgumentOverflowException(
		Class throwingClass,
		String methName,
		int argNo,
		String argName,
		int argValue,
		int maxValue,
		Throwable th )
	{
		super( throwingClass, methName, argNo, argName,
			"value " + Integer.toString( argValue )
				+ " must be no more than "
				+ Integer.toString( maxValue ),
			th );
	}

	public CFLibArgumentOverflowException(
		Class throwingClass,
		String methName,
		int argNo,
		String argName,
		long argValue,
		long maxValue )
	{
		super( throwingClass, methName, argNo, argName,
			"value " + Long.toString( argValue )
				+ " must be no more than "
				+ Long.toString( maxValue ) );
	}

	public CFLibArgumentOverflowException(
		Class throwingClass,
		String methName,
		int argNo,
		String argName,
		long argValue,
		long maxValue,
		Throwable th )
	{
		super( throwingClass, methName, argNo, argName,
			"value " + Long.toString( argValue )
				+ " must be no more than "
				+ Long.toString( maxValue ),
			th );
	}

	public CFLibArgumentOverflowException(
		Class throwingClass,
		String methName,
		int argNo,
		String argName,
		float argValue,
		float maxValue )
	{
		super( throwingClass, methName, argNo, argName,
			"value " + Float.toString( argValue )
				+ " must be no more than "
				+ Float.toString( maxValue ) );
	}

	public CFLibArgumentOverflowException(
		Class throwingClass,
		String methName,
		int argNo,
		String argName,
		float argValue,
		float maxValue,
		Throwable th )
	{
		super( throwingClass, methName, argNo, argName,
			"value " + Float.toString( argValue )
				+ " must be no more than "
				+ Float.toString( maxValue ),
			th );
	}

	public CFLibArgumentOverflowException(
		Class throwingClass,
		String methName,
		int argNo,
		String argName,
		double argValue,
		double maxValue )
	{
		super( throwingClass, methName, argNo, argName,
			"value " + Double.toString( argValue )
				+ " must be no more than "
				+ Double.toString( maxValue ) );
	}

	public CFLibArgumentOverflowException(
		Class throwingClass,
		String methName,
		int argNo,
		String argName,
		double argValue,
		double maxValue,
		Throwable th )
	{
		super( throwingClass, methName, argNo, argName,
			"value " + Double.toString( argValue )
				+ " must be no more than "
				+ Double.toString( maxValue ),
			th );
	}

	public CFLibArgumentOverflowException(
		Class throwingClass,
		String methName,
		int argNo,
		String argName,
		Calendar argValue,
		Calendar maxValue )
	{
		super( throwingClass, methName, argNo, argName,
			"value " + argValue.toString()
				+ " must be no more than "
				+ maxValue.toString() );
	}

	public CFLibArgumentOverflowException(
		Class throwingClass,
		String methName,
		int argNo,
		String argName,
		Calendar argValue,
		Calendar maxValue,
		Throwable th )
	{
		super( throwingClass, methName, argNo, argName,
			"value " + argValue.toString()
				+ " must be no more than "
				+ maxValue.toString(),
			th );
	}

	public CFLibArgumentOverflowException(
		Class throwingClass,
		String methName,
		int argNo,
		String argName,
		String argValue,
		String maxValue )
	{
		super( throwingClass, methName, argNo, argName,
			"value " + argValue.toString()
				+ " must be no more than "
				+ maxValue.toString() );
	}

	public CFLibArgumentOverflowException(
		Class throwingClass,
		String methName,
		int argNo,
		String argName,
		String argValue,
		String maxValue,
		Throwable th )
	{
		super( throwingClass, methName, argNo, argName,
			"value " + argValue.toString()
				+ " must be no more than "
				+ maxValue.toString(),
			th );
	}

	public CFLibArgumentOverflowException(
		Class throwingClass,
		String methName,
		int argNo,
		String argName,
		BigDecimal argValue,
		BigDecimal maxValue )
	{
		super( throwingClass, methName, argNo, argName,
			"value " + argValue.toString()
				+ " must be no more than "
				+ maxValue.toString() );
	}

	public CFLibArgumentOverflowException(
		Class throwingClass,
		String methName,
		int argNo,
		String argName,
		BigDecimal argValue,
		BigDecimal maxValue,
		Throwable th )
	{
		super( throwingClass, methName, argNo, argName,
			"value " + argValue.toString()
				+ " must be no more than "
				+ maxValue.toString(),
			th );
	}

	public CFLibArgumentOverflowException(
		String fieldName,
		String msg )
	{
		super( fieldName, msg );
	}

	public CFLibArgumentOverflowException(
		String fieldName,
		String methName,
		String msg )
	{
		super( fieldName, methName, msg );
	}

	public CFLibArgumentOverflowException(
		String fieldName,
		String methName,
		String msg,
		Throwable th )
	{
		super( fieldName, methName, msg, th );
	}

	public CFLibArgumentOverflowException(
		String fieldName,
		String methName,
		int argNo,
		String argName,
		String msg )
	{
		super( fieldName, methName, argNo, argName, msg );
	}

	public CFLibArgumentOverflowException(
		String fieldName,
		String methName,
		int argNo,
		String argName,
		String msg,
		Throwable th )
	{
		super( fieldName, methName, argNo, argName, msg, th );
	}

	public CFLibArgumentOverflowException(
		String fieldName,
		String methName,
		int argNo,
		String argName,
		short argValue,
		short maxValue )
	{
		super( fieldName, methName, argNo, argName,
			"value " + Short.toString( argValue )
				+ " must be no more than "
				+ Short.toString( maxValue ) );
	}

	public CFLibArgumentOverflowException(
		String fieldName,
		String methName,
		int argNo,
		String argName,
		short argValue,
		short maxValue,
		Throwable th )
	{
		super( fieldName, methName, argNo, argName,
			"value " + Short.toString( argValue )
				+ " must be no more than "
				+ Short.toString( maxValue ),
			th );
	}

	public CFLibArgumentOverflowException(
		String fieldName,
		String methName,
		int argNo,
		String argName,
		int argValue,
		int maxValue )
	{
		super( fieldName, methName, argNo, argName,
			"value " + Integer.toString( argValue )
				+ " must be no more than "
				+ Integer.toString( maxValue ) );
	}

	public CFLibArgumentOverflowException(
		String fieldName,
		String methName,
		int argNo,
		String argName,
		int argValue,
		int maxValue,
		Throwable th )
	{
		super( fieldName, methName, argNo, argName,
			"value " + Integer.toString( argValue )
				+ " must be no more than "
				+ Integer.toString( maxValue ),
			th );
	}

	public CFLibArgumentOverflowException(
		String fieldName,
		String methName,
		int argNo,
		String argName,
		long argValue,
		long maxValue )
	{
		super( fieldName, methName, argNo, argName,
			"value " + Long.toString( argValue )
				+ " must be no more than "
				+ Long.toString( maxValue ) );
	}

	public CFLibArgumentOverflowException(
		String fieldName,
		String methName,
		int argNo,
		String argName,
		long argValue,
		long maxValue,
		Throwable th )
	{
		super( fieldName, methName, argNo, argName,
			"value " + Long.toString( argValue )
				+ " must be no more than "
				+ Long.toString( maxValue ),
			th );
	}

	public CFLibArgumentOverflowException(
		String fieldName,
		String methName,
		int argNo,
		String argName,
		float argValue,
		float maxValue )
	{
		super( fieldName, methName, argNo, argName,
			"value " + Float.toString( argValue )
				+ " must be no more than "
				+ Float.toString( maxValue ) );
	}

	public CFLibArgumentOverflowException(
		String fieldName,
		String methName,
		int argNo,
		String argName,
		float argValue,
		float maxValue,
		Throwable th )
	{
		super( fieldName, methName, argNo, argName,
			"value " + Float.toString( argValue )
				+ " must be no more than "
				+ Float.toString( maxValue ),
			th );
	}

	public CFLibArgumentOverflowException(
		String fieldName,
		String methName,
		int argNo,
		String argName,
		double argValue,
		double maxValue )
	{
		super( fieldName, methName, argNo, argName,
			"value " + Double.toString( argValue )
				+ " must be no more than "
				+ Double.toString( maxValue ) );
	}

	public CFLibArgumentOverflowException(
		String fieldName,
		String methName,
		int argNo,
		String argName,
		double argValue,
		double maxValue,
		Throwable th )
	{
		super( fieldName, methName, argNo, argName,
			"value " + Double.toString( argValue )
				+ " must be no more than "
				+ Double.toString( maxValue ),
			th );
	}

	public CFLibArgumentOverflowException(
		String fieldName,
		String methName,
		int argNo,
		String argName,
		Calendar argValue,
		Calendar maxValue )
	{
		super( fieldName, methName, argNo, argName,
			"value " + argValue.toString()
				+ " must be no more than "
				+ maxValue.toString() );
	}

	public CFLibArgumentOverflowException(
		String fieldName,
		String methName,
		int argNo,
		String argName,
		Calendar argValue,
		Calendar maxValue,
		Throwable th )
	{
		super( fieldName, methName, argNo, argName,
			"value " + argValue.toString()
				+ " must be no more than "
				+ maxValue.toString(),
			th );
	}

	public CFLibArgumentOverflowException(
		String fieldName,
		String methName,
		int argNo,
		String argName,
		String argValue,
		String maxValue )
	{
		super( fieldName, methName, argNo, argName,
			"value " + argValue.toString()
				+ " must be no more than "
				+ maxValue.toString() );
	}

	public CFLibArgumentOverflowException(
		String fieldName,
		String methName,
		int argNo,
		String argName,
		String argValue,
		String maxValue,
		Throwable th )
	{
		super( fieldName, methName, argNo, argName,
			"value " + argValue.toString()
				+ " must be no more than "
				+ maxValue.toString(),
			th );
	}

	public CFLibArgumentOverflowException(
		String fieldName,
		String methName,
		int argNo,
		String argName,
		BigDecimal argValue,
		BigDecimal maxValue )
	{
		super( fieldName, methName, argNo, argName,
			"value " + argValue.toString()
				+ " must be no more than "
				+ maxValue.toString() );
	}

	public CFLibArgumentOverflowException(
		String fieldName,
		String methName,
		int argNo,
		String argName,
		BigDecimal argValue,
		BigDecimal maxValue,
		Throwable th )
	{
		super( fieldName, methName, argNo, argName,
			"value " + argValue.toString()
				+ " must be no more than "
				+ maxValue.toString(),
			th );
	}
}
