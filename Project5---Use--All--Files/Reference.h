/****************************************************************************
 *																			*
 *	File:		Reference.h													*
 *																			*
 *	Author:		Jared Christian												*
 *																			*
 *	Date:		Apr 26, 2010												*
 *																			*
 *	Purpose:	----------													*
 *																			*
 ****************************************************************************/

#ifndef REFERENCE_H
#define REFERENCE_H

//	Header Files

#include <iostream>

using namespace std;


/****************************************************************************
 *																			*
 *	The Reference class definition											*
 *																			*
 ****************************************************************************/


class Reference {
	
public:
	/**************
	 Constructors
	 **************/
	Reference() { }
	Reference(int ch, int ver) { chapter = ch; verse = ver; }
	/**************
	   Inspectors
	 **************/
	int getChapter() { return chapter; }
	int getVerse() { return verse; }

	/**************
	 Facilitators
	 **************/
	void display(ostream& out) const { out << " " << chapter << ":" << verse << " "; } 
	/**************
	    Other
	 **************/
private:
	int chapter;
	int verse;
};
	
ostream& operator<<(Reference r, ostream& out);
bool operator==(const Reference r,const Reference& r2);
bool operator!=(const Reference r,const Reference& r2);

/****************************************************************************
 *																			*
 *	Function:	operator<<													*
 *																			*
 *	Purpose:	Output a reference object									*
 *																			*
 ****************************************************************************/


ostream& operator<<(const Reference& r, ostream& out)
{
		r.display(out);
		return out;
}


#endif