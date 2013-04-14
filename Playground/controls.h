//	Copyright (C) 2010-2012 Vaptistis Anogeianakis <nomad@cornercase.gr>
/*
 *	This file is part of Playground.
 *
 *	Playground is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Playground is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Playground.  If not, see <http://www.gnu.org/licenses/>.
 */

struct Control
{
	virtual void display(){}
	virtual void getFocus(){}
	virtual void looseFocus(){}
	virtual void pickUp(){}
	virtual void drag(){}
	virtual void drop(){}
}; // end struct Control


struct FocusAwareControl : public Control
{
	bool hasFocus;

	virtual void getFocus()
	{
		hasFocus = true;
	} // end function getFocus

	virtual void looseFocus()
	{
		hasFocus = false;
	} // end function looseFocus
}; // end struct FocusAwareControl


#include "box.h"
#include "handle.h"
#include "arrow.h"