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

/**
 *	An XML Core Context Factory instantiates new instances
 *	derived from XmlCoreContext. 
 */
public interface CFLibXmlCoreContextFactory {

	/**
	 *	Get the application processing logger.
	 *
	 *	@return	The application processing Log4J Logger.
	 */
	public ICFLibMessageLog getLog();

	/**
	 *	Copy an XML Core Context.
	 *
	 *	@param	src	The context to copy.
	 *	@param	qName	The QName of the element about to be processed.
	 *	@param	handler	The XmlCoreElementHandler which will be used for processing.
	 */
	public CFLibXmlCoreContext newXmlCoreContext(
		CFLibXmlCoreContext src,
		String qName,
		CFLibXmlCoreElementHandler handler );

	/**
	 *	Construct a "root" XML Core Context instance.
	 *
	 *	@param	coreParser	The parser which owns this instance.
	 *	@param	log	ICFLibMessageLog to use, if null, use parser's logger.
	 *	@param	handler	The XmlCoreElementHandler which will be processing the doc root.
	 */
	public CFLibXmlCoreContext newXmlCoreContext(
		CFLibXmlCoreParser coreParser,
		ICFLibMessageLog jLogger,
		CFLibXmlCoreElementHandler elementHandler );

}
