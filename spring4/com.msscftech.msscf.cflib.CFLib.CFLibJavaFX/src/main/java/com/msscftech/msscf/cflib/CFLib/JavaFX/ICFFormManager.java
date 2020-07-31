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

package com.msscftech.msscf.cflib.CFLib.JavaFX;

import javafx.scene.Node;

import com.msscftech.msscf.cflib.CFLib.*;

/**
 *	The ICFDesktopManager specifies the interface from an application's
 *	forms to the desktop display manager in charge of that facet of forms.
 */
public interface ICFFormManager
{
	/**
	 *	Sometimes you'll want to check to see what the current node
	 *	form being displayed is.
	 */
	Node getCurrentForm();
	
	/**
	 *	Set the currently displayed form, clearing the form stack
	 *	and making the specified the root form for processing.
	 */
	void setRootForm( Node value );
	
	/**
	 *	Push a form on the stack.  The specified form becomes the current
	 *	displayed form.  You should never push the same set of nodes
	 *	more than once to the form manager, and you should never push
	 *	a root form on the stack.
	 */
	void pushForm( Node value );
	
	/**
	 *	Close the current form.  If you're paranoid, you can use
	 *	getCurrentForm() to make sure you're the current form before
	 *	invoking this method.
	 *
	 *	If the stack is empty and you are logged in, calling
	 *	closeCurrentForm() will cause showRootMainForm() to be
	 *	invoked.
	 */
	void closeCurrentForm();
	
	/**
	 *	Show the root main form for the facet.
	 */
	void showRootMainForm();
}
