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

import java.math.BigDecimal;
import java.text.DecimalFormat;
import java.text.Format;
import javafx.scene.control.TableCell;

import com.github.msobkow.cflib.CFLib.*;

public class CFNumberTableCell<T>
extends TableCell<T,BigDecimal>
{
	protected int digits;
	protected int precis;

	public CFNumberTableCell( int argDigits, int argPrecision ) {
		super();
		setDigits( argDigits );
		setPrecision( argPrecision );
	}

	@Override protected void updateItem( BigDecimal item, boolean empty ) {
		super.updateItem( item, empty );
		if( ( item == null ) || empty ) {
			setText( null );
			setStyle( "" );
		}
		else {
			Format fmt = CFLibBigDecimalUtil.getNumberFormat( getClass().getName(), digits, precis );
			String cellText = fmt.format( item );
			setText( cellText );
			setStyle( "-fx-alignment: CENTER-RIGHT" );
		}
	}

	public int getDigits() {
		return( digits );
	}

	public void setDigits( int argDigits ) {
		final String S_ProcName = "setDigits";
		if( argDigits < 1 ) {
			throw new CFLibArgumentUnderflowException( getClass(),
					S_ProcName,
					1,
					"argDigits",
					argDigits,
					1 );
		}
		else if( argDigits > CFLibBigDecimalUtil.MAX_DIGITS ) {
			throw new CFLibArgumentOverflowException( getClass(),
				S_ProcName,
				1,
				"argDigits",
				argDigits,
				CFLibBigDecimalUtil.MAX_DIGITS );
		}
		digits = argDigits;
	}
	
	public int getPrecision() {
		return( precis );
	}

	public void setPrecision( int argPrecis ) {
		final String S_ProcName = "setPrecision";
		if( argPrecis < 0 ) {
			throw new CFLibArgumentUnderflowException( getClass(),
				S_ProcName,
				1,
				"argPrecis",
				argPrecis,
				0 );
		}
		else if( argPrecis > CFLibBigDecimalUtil.MAX_PRECISION ) {
			throw new CFLibArgumentOverflowException( getClass(),
				S_ProcName,
				1,
				"argPrecis",
				argPrecis,
				CFLibBigDecimalUtil.MAX_PRECISION );
		}

		if( argPrecis >= digits ) {
			throw new CFLibArgumentOverflowException( getClass(),
				S_ProcName,
				1,
				"argPrecis",
				argPrecis,
				digits - 1 );
		}

		precis = argPrecis;
	}

	public void setDigitsAndPrecision( int argDigits, int argPrecis ) {
		final String S_ProcName = "setDigitsAndPrecision";
		if( argDigits < 1 ) {
			throw new CFLibArgumentUnderflowException( getClass(),
					S_ProcName,
					1,
					"argDigits",
					argDigits,
					1 );
		}
		else if( argDigits > CFLibBigDecimalUtil.MAX_DIGITS ) {
			throw new CFLibArgumentOverflowException( getClass(),
				S_ProcName,
				1,
				"argDigits",
				argDigits,
				CFLibBigDecimalUtil.MAX_DIGITS );
		}
		if( argPrecis < 0 ) {
			throw new CFLibArgumentUnderflowException( getClass(),
				S_ProcName,
				1,
				"argPrecis",
				argPrecis,
				0 );
		}
		else if( argPrecis > CFLibBigDecimalUtil.MAX_PRECISION ) {
			throw new CFLibArgumentOverflowException( getClass(),
				S_ProcName,
				1,
				"argPrecis",
				argPrecis,
				CFLibBigDecimalUtil.MAX_PRECISION );
		}
		if( argPrecis >= argDigits ) {
			throw new CFLibArgumentOverflowException( getClass(),
				S_ProcName,
				1,
				"argPrecis",
				argPrecis,
				argDigits - 1 );
		}
		digits = argDigits;
		precis = argPrecis;
	}
}
