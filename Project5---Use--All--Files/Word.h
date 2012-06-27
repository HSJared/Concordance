/****************************************************************************
 *																			*
 *	File:		Word.h													*
 *																			*
 *	Author:		Jared Christian												*
 *																			*
 *	Date:		Apr 26, 2010												*
 *																			*
 *	Purpose:	----------													*
 *																			*
 ****************************************************************************/

#ifndef WORD_H
#define WORD_H

#include <iostream>
#include <string>
#include <cassert>
#include "reference.h"
#include "arraylist.h"

using namespace std;


class Word {
	
	friend class Concordance;
public:
	/**************
	 Constructors
	 **************/
	Word() { }
	Word(string s) {value = s; }
	Word(string s, int chap, int verse) 
	{ 
		value = s; 
		Reference r(chap, verse); 
		verses.PushBack(r); 		
	}	
	/**************
	  Inspectors
	 **************/
	string getWord() const { return value; }
	int getNumberRefs() { return verses.Size(); }
	ArrayList<Reference>* getVerses() { ArrayList<Reference>* list = &verses; return list; }
	/**************
	  Mutators
	 **************/
	void addReference(int ch, int ver) { Reference r(ch, ver); verses.PushBack(r); }
	void addReference(Reference r) { verses.PushBack(r); }
	/**************
	  Operators
	 **************/
	
	//just seemed to make more sense to make them member functions, it's just accessing some strings
	bool operator==(const Word& w) const {return value == w.value; }
	bool operator!=(const Word& w)const {return value != w.value; }
	bool operator<(const Word& w)const {return value < w.value; }
	bool operator>(const Word& w)const {return value > w.value; }
	bool operator<=(const Word& w)const {return value <= w.value; }
	bool operator>=(const Word& w)const {return value >= w.value; }
	/**************
	 Facilitators
	 **************/
	void displayRefs() const;
	void display(ostream& out) const { displayRefs(); }

	/**************
	 Other
	 **************/
private:
	string value;
	ArrayList<Reference> verses;
	
};

/*******************************************
 
      ___                                
    /(,  )                               
   /    /  __    _  __  _  _/_ _____  _  
  /    /   /_)__(/_/ (_(_(_(__(_)/ (_/_)_
 (___ / .-/                              
 (_/                               
 
 ********************************************/


ostream& operator<<(ostream& out, const Word& w); 


/****************************************************************************
 *																			*
 *	Function: operator<<													*
 *																			*
 *	Purpose:  Output a word object											*
 *																			*
 ****************************************************************************/

ostream& operator<<(ostream& out, const Word& w) 
{
	w.display(out);
	return out;
}

/****************************************************************************
 *																			*
 *	Function:	displayRefs													*
 *																			*
 *	Purpose:	Display the numeric references in the book					*
 *																			*
 ****************************************************************************/

void Word::displayRefs() const 
{ 
	cout << endl << endl << "There are " << verses.Size() << " references to the word '" << value << "' .\n" << endl;
	for (int i = 1; i <= verses.Size(); i++) 
	{	
		cout << " " << verses[i].getChapter() << ":" << verses[i].getVerse() << " ";
		if (i % 15 == 0)
			cout << endl;
	}
}

#endif