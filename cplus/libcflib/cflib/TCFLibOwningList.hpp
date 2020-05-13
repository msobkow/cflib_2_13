#pragma once
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

#include <memory.h>

#include <cflib/CFLib.hpp>

namespace std {

	template< class EltClass > class TCFLibOwningList : public std::list< EltClass > {

	public:

		/**
		 *	Default constructor.
		 */
		TCFLibOwningList<EltClass>()
		: std::list<EltClass>()
		{
		}

		/**
		 *	Copy constructor.  Note that elements MUST implement ICFLibCloneableObj.
		 */
		TCFLibOwningList<EltClass>( const TCFLibOwningList<EltClass>& src )
		: std::list<EltClass>()
		{
			auto iter = src.begin();
			auto endit = src.end();
			while( iter != endit ) {
				if( *iter != NULL ) {
					std::list<EltClass>::push_back( dynamic_cast<EltClass>( (*iter)->clone() ) );
				}
				else {
					std::list<EltClass>::push_back( *iter );
				}
				iter ++;
			}
		}

		/**
		 *	Copy constructor.  Note that elements MUST implement ICFLibCloneableObj.
		 */
		TCFLibOwningList<EltClass>( const std::list<EltClass>& src )
		: std::list<EltClass>()
		{
			auto iter = src.begin();
			auto endit = src.end();
			while( iter != endit ) {
				if( *iter != NULL ) {
					std::list<EltClass>::push_back( dynamic_cast<EltClass>( (*iter)->clone() ) );
				}
				else {
					std::list<EltClass>::push_back( *iter );
				}
				iter ++;
			}
		}

		/**
		 *	The destructor has to release the elements, but because the
		 *	underlying STL template does not implement a virtual destructor,
		 *	you have to rely on the application code being specific about
		 * 	the kind of vectors it is dealing with, and pass them around
		 *	as full objects and object references, rather than trying to delete
		 *	pointers to instances.
		 */
		~TCFLibOwningList<EltClass>() {
			EltClass elt = NULL;
			auto iter = std::list<EltClass>::begin();
			while( iter != std::list<EltClass>::end() ) {
				elt = *iter;
				if( elt != NULL ) {
					*iter = NULL;
					try {
						delete elt;
						elt = NULL;
					}
					catch( std::runtime_error e ) {
					}
				}
				iter ++;
			}
			// Now the std::list destructor runs, deleting the vector array itself,
			// whose elements are all NULL pointers now
		}

	};
}
