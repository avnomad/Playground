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