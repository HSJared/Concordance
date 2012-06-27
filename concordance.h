/****************************************************************************
 *																			*
 *	File:		Concordance.h												*
 *																			*
 *	Author:		Jared Christian												*
 *																			*
 *	Date:		Apr 26, 2010												*
 *																			*
 *	Purpose:	----------													*
 *																			*
 ****************************************************************************/

#ifndef CONCORDANCE_H
#define CONCORDANCE_H

// Header Files

#include <iostream>
#include <string>
#include <cassert>
#include <fstream>
#include <ctype.h>
#include "circlinkedlist.h"
#include "arraylist.h"
#include "binarysearchtree.h"
#include "word.h"
#include "reference.h"


using namespace std;


class Concordance {
	
	public:
	/**************
	 Constructors
	 **************/
	Concordance(string filename) { 
		ifstream fin; fin.open(filename.c_str());
		if (!fin) { cout << "Error: File could not be opened" << endl; }
		else input(fin); 
	}
	/**************
		Inspectors
	 **************/
	string getTitle() {return title; }
	/**************
	   Called on by Concordance maker
	 **************/
	void displayWordRefs(string& s);
	void displayWordVerses(string& s); 
	void displayChapter(int ch);
	void displayVerse(int chap, int verse);
	void displayAllWords();
	void displayTree() {cout << palabras; }
	void makeEmpty() { palabras.makeEmpty(); book.MakeEmpty();	
	}
	
	//	Other functions
	string getWord(const string& s, int& i) const;
	void input(ifstream& in);
	void input(string filename);
	void addToBook(string s, int ch);
	
	bool isTreeCountBalanced() { return palabras.isCountBalanced(); }
	bool isTreeHeightBalanced() { return palabras.isHeightBalanced(); }
	int treeSize() { return palabras.size(); }
	
private:
	BinarySearchTree<Word> palabras; //palabras is spanish for words, I didn't want to confuse a the search tree of words with the word class
	ArrayList<ArrayList<string> > book;
	string title; //Hidden Feature: supports more than John
};

/****************************************************************************
 *																			*
 *	Function:	getWord														*
 *																			*
 *	Purpose:	To get the next word in the string and to update the index	*
 *																			*
 ****************************************************************************/

string Concordance::getWord(const string& s, int& i) const
{
	//	Start with an empty word
	
	string word;
	
	//	Skip over all non-alphabetic characters and '
	
	while (i < s.size() && !isalpha(s[i]) && s[i] != '\'')
		i++;
	
	//	Include all alphabetic characters and ' in the word
	
	while (i < s.size() && (isalpha(s[i]) || s[i] == '\''))
		word = word + (char)toupper(s[i++]);
	
	//	Return the word
	
	return word;
}



/****************************************************************************
 *																			*
 *	Function:	input														*
 *																			*
 *	Purpose:	To input the book into the concordance class				*
 *																			*
 ****************************************************************************/

void Concordance::input(ifstream& in) {
	
	//  1. Intialize counters
	int chap = 0;
	int verse = 1;
	
	//  2. Extract the title of the book first
	{ 
	  cout << "Reading the text";
	  getline(in, title);

//	  title.resize(title.size() - 1);
	}
	int reading = 0;
	//  3.  Scan thru book until the end of file
	while (!in.eof()) {
		
		//	A. Get the current line
		string currentLine;
		getline(in, currentLine);
		
		if ( reading % 50 == 0 )
			cout << "."; //just a visual indicator that it is working

		
		
		//	B. Process the current line
		for (int i = 0; i < currentLine.size(); i++)
		{
			// Preserve if it was the first time looking at the line
			int orig = i;
			
			//	i. Get the word
			string extractedword = getWord(currentLine, i);
			
			//	ii. Check to make sure it's not a new chapter
			if ( extractedword == "CHAPTER" )
			{	
				//If so, increment chapter and reset verse
				chap++;
				verse = -1; //I set it to -1 since verse gets incremented at the end of the while loop, even while there's a black line
			}
			
			// iii. if it's a chaper or a blank line, skip the line
			if ( extractedword == "CHAPTER" || extractedword.size() == 0 )
				break;
			
			// iiii. If it's part of a verse:
			else 
			{
				// a. Create a word object from it
				Word w(extractedword, chap, verse);
				
				//	b. look for it in the tree
				Word* result = palabras.search(w);
				
				//	c. if not found, insert it
				if (result == NULL)
				{	
					
					palabras.insert(w);
				}
				
				//	d. else if found, add a reference to the current verse
				else
				{	
					result->addReference(chap, verse);
				}
			}
			
			// iiiii. Add to book if a new verse
			if (orig == 0)
			{	
				//	a. Need to remove the leading two characters before inserting (this removes the number plus the leading space)
				currentLine.erase(0, 2);
				i = i - 2; //since we resize the verse, we also need to resize the index
				
				//	b. for verses numbered greater than 9, there's an extra character (in the number) that also needs to be removed. 
				if (verse > 9)
				{
					currentLine.erase(0, 1);
					i = i - 1;//account for resizing of string
				}
				
				//	c. Add the verse to the book
				addToBook(currentLine, chap);
				
			}
	
		}//end for loop that processes current line
		
		
		// C. Increment Counter
		verse++;
		reading++;
		
	}//end while (!in.eof)
	cout << endl << "Building the search tree..." << endl;
	
	//	4. Count Balance the tree to make seaching effcient 
	palabras.countBalance(); 
	cout << "Balancing the search tree..." << endl;
	
}

/****************************************************************************
 *																			*
 *	Function:	displayWordRefs												*
 *																			*
 *	Purpose:	display the references to a word (not the actual verses		*
 *																			*
 ****************************************************************************/

void Concordance::displayWordRefs(string& s)
{
	//	1. Make the work uppercase so it can be matched by the == operator of the word class 
	for (int i = 0; i < s.size(); i++) 
	{
		s[i] = toupper(s[i]);
	}
	
	//	2. Create a word object for the word
	Word w(s);
	
	//	3. Search for the word in the book
	Word* result = palabras.search(w);
	
	//	4. If not found, tell user. This will make sure a NULL pointer is not dereferenced. 
	if (result == NULL)
		cout << "Word Not Found" << endl;
	
	//	5. Otherwise, display the stored references 
	else 
	{
		result->displayRefs();
	}
}

/****************************************************************************
 *																			*
 *	Function:	displayWordVerses											*
 *																			*
 *	Purpose:	display the verses a word is referenced in					*
 *																			*
 ****************************************************************************/


void Concordance::displayWordVerses(string& s) 
{ 
	//	1. Make the work uppercase so it can be matched by the == operator of the word class 
	for (int i = 0; i < s.size(); i++) 
	{
		s[i] = toupper(s[i]);
	}
	
	//	2. Create a word object for the word
	Word w(s);
	
	//	3. Search for the word in the book
	Word* result = palabras.search(w);
	
	//	4. If not found, tell user. This will make sure a NULL pointer is not dereferenced. 
	if (result == NULL)
		cout << "Word Not Found" << endl;
	
	//	5. Otherwise, display the stored references along with the text of the verses
	else 
	{
		// For each element
		for (int i = 1; i <= result->verses.Size(); i++) {
			
			// a. Get the references
			int ch = result->verses[i].getChapter();
			int vr = result->verses[i].getVerse();
			
			// b. use the references to display the verse
			displayVerse(ch, vr);
		}
	}
}



/****************************************************************************
 *																			*
 *	Function:	displayAllWords												*
 *																			*
 *	Purpose:	Display all the words in the book							*
 *																			*
 ****************************************************************************/

void Concordance::displayAllWords() {
	
	//Outputs the tree, but without brackets or commas
	palabras.outputWithOutBrackets();
}

/****************************************************************************
 *																			*
 *	Function:	addToBook													*
 *																			*
 *	Purpose:	add a verse to the book, in a specfic chapter				*
 *																			*
 ****************************************************************************/

void Concordance::addToBook(string s, int ch) {
	
	//	Case 1: Chapter Exists
	if (book.Size() == ch) 
	{
		book[ch].PushBack(s);
	}
	
	//	Case 2: Chater needs to be created
	else if (book.Size() < ch)
	{
		//Create Chapter
		ArrayList<string> newChapter;
		
		//Add verse
		newChapter.PushBack(s);
		
		//Add chapter to book
		book.PushBack(newChapter);
	}
}

/****************************************************************************
 *																			*
 *	Function:	displayChapter												*
 *																			*
 *	Purpose:	show the specfic chapter									*
 *																			*
 ****************************************************************************/

void Concordance::displayChapter(int ch) {
	
	// Case 1: Chapter Exists
	if (ch <= book.Size()) 
	{
		// Display the verse
		for(int i = 1; i <= book[ch].Size(); i++)
			cout << title << " " << ch << ":" << i << "  "<< book[ch][i] << endl;
	}
	// Case 2: Chapter does not exist
	else 
	{	//Inform the user
		cout << endl << endl << "Sorry, this chapter does not exist!" << endl;
	}

}

/****************************************************************************
 *																			*
 *	Function:	displayVerse												*
 *																			*
 *	Purpose:	show the specfic verse										*
 *																			*
 ****************************************************************************/

void Concordance::displayVerse(int chap, int verse)
{
	//	Case 1: Chaper Exists
	if (chap <= book.Size())
	{	
		//If verse also exists, display verse
		if (verse <= book[chap].Size())
		{
			cout << title << " " << chap << ":" << verse << "   " << book[chap][verse] << endl;
		}
		
		//Otherwise tell user that the verse was invalid
		else cout << endl << endl << "Sorry, this verse does not exist!" << endl;
	}
	
	// Case 2: Invalid Verse
	else cout << endl << endl << "Sorry, this chapter and verse do not exist!" << endl;
}

/****************************************************************************
 *																			*
 *	Function:	input														*
 *																			*
 *	Purpose:	create a concordance from the file at filename				*
 *																			*
 ****************************************************************************/
void Concordance::input(string filename)
{
	// clear out the old stuff
	palabras.makeEmpty(); book.MakeEmpty(); 
	
	//input new data
	ifstream fin; 
	fin.open(filename.c_str());
		if (!fin) 
			cout << "Error: File could not be opened" << endl;
		else input(fin);
}
	
#endif


