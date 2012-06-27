/****************************************************************************
*																			*
*	Program:	ConcordanceMaker.cpp										*
*																			*
*	Author:		Robb T. Koether												*
*																			*
*	Date:		Apr 8, 2010													*
*																			*
*	Purpose:	This program will build a concordance of the Book of John	*
*				and then let the user access the concordance				*
*																			*
****************************************************************************/

//	Header files

#include <iostream>
#include "concordance.h"

using namespace std;

//	Enum type for menu choices

enum ChoiceType {NULL_CHOICE, WORD_REFS, WORD_VERSES, CHAPTER, VERSE, ALL_WORDS, QUIT, SWITCH};
// enum DevType {NCHO, NIX, BINSIZE, CBAL, HBAL, DISPLAY};

//Bool for if on UNIX-Like system
bool UNIX = false; //since I develop on on a UNIX based system, I need this bool
bool John = true;
string bookTitle;

//	Function prototypes

void printMenu();
void printDev();
void displayOppBook();
ChoiceType getMenuChoice();
// DevType getDevChoice();
string getLocation();

/****************************************************************************
*																			*
*	Function:	main														*
*																			*
****************************************************************************/

int main()
{
//	Create the concordance

	Concordance concordance(getLocation());
	bookTitle = concordance.getTitle();
	
//	Get the first menu choice

	int choice = getMenuChoice();

//	Process menu choices until user quits

	while (choice != QUIT)
	{
	//	Take action on menu choice
	
		switch (choice)
		{
		//	Print list of references to the word
		
			case WORD_REFS:
			{
				cout << "Which word? ";
				string word;
				cin >> word;
				concordance.displayWordRefs(word);
				break;
			}
		
		//	Print the verses that contain the word
		
			case WORD_VERSES:
			{
				cout << "Which word? ";
				string word;
				cin >> word;
				concordance.displayWordVerses(word);
				break;
			}
			
		//	Display the requested chapter
		
			case CHAPTER:
			{
				cout << "Which chapter? ";
				int ch;
				cin >> ch;
				concordance.displayChapter(ch);
				break;
			}
		
		//	Display the requested verse
		
			case VERSE:
			{
				cout << "Which chapter? ";
				int ch;
				cin >> ch;
				cout << "Which verse? ";
				int v;
				cin >> v;
				concordance.displayVerse(ch, v);
				break;
			}
		
		//	Display all the words in the text
		
			case ALL_WORDS:
			{
				concordance.displayAllWords();
				break;
			}
			
			//Switch between Genesis and John
			case SWITCH:
			{
				John = !(John);
				if (John)
			    	concordance.input(getLocation());
				else
					concordance.input("Genesis.txt");
				bookTitle = concordance.getTitle();	
				break;
			}
			/*
			case DEVMODE:
			{
				int menu = getDevChoice();
				switch (menu) {
					case NIX:
					{
						if (UNIX == true)
							cout << "Currently running in UNIX mode." << endl; 
						else
							cout << "Currently set in Windows Mode." << endl;
						break;
					}
					case BINSIZE:
					{	
						cout << "The tree has  " << concordance.treeSize() << " nodes." << endl;
						break;
					}
					case CBAL:
					{ if (concordance.isTreeCountBalanced())
						 cout << "Tree is Count Balanced!";
					  else cout << "Tree is NOT Count Balanced!";
						break;
					}
						
					case HBAL:
					{ if (concordance.isTreeCountBalanced())
						cout << "Tree is Height Balanced!";
					else cout << "Tree is NOT Height Balanced!";
						break;
					}
					case DISPLAY:
					{
						concordance.displayTree();
						break;
					}
					case SWITCH:
					{
						cout << "John 1: " << John << endl;
						John = !(John);
						if (John)
							concordance.input(getLocation());
						else
							concordance.input("//hams-acad-fs/students/harrisj/Genesis.txt");
						bookTitle = concordance.getTitle();
						cout << "John 2: " << John << endl;
					}



				}
				*/
				

		}
	
	//	Get the next menu choice
	
		choice = getMenuChoice();
	}
	return 0;	
}

/****************************************************************************
*																			*
*	Function:	printMenu													*
*																			*
*	Purpose:	To print the menu											*
*																			*
****************************************************************************/

void printMenu()
{
	cout << endl << endl << endl;
	cout << "The Book of " << bookTitle << endl;
	cout << endl;
	cout << "(1) Display references to a word" << endl;
	cout << "(2) Display verses containing a word" << endl;
	cout << "(3) Display a chapter" << endl;
	cout << "(4) Display a verse" << endl;
	cout << "(5) Display all words" << endl;
	cout << "(6) Quit" << endl;
	cout << "(7) Switch to the book of "; 
	displayOppBook();
	cout << endl;
//	cout << "(7) Develper Options" << endl;
	cout << "Enter choice: ";
	return;
}

void displayOppBook()
{
	if (John)
		cout << "Genesis";
	else
		cout << "John";
}

/*void printDev()
{
	cout << endl;
	cout << "The Book of " << bookTitle << endl;
	cout << endl;
	cout << "(1) UNIX or PC?" << endl;
	cout << "(2) Binary Tree Size" << endl;
	cout << "(3) isTreeCountBalanced?" << endl;
	cout << "(4) isHeightCountBalanced?" << endl;
	cout << "(5) Display Tree" << endl;
	cout << "(6) Switch Books " << endl;
	cout << "Enter choice: ";
	return;
}
*/

/****************************************************************************
*																			*
*	Function:	getMenuChoice												*
*																			*
*	Purpose:	To get the user's menu choice								*
*																			*
****************************************************************************/

ChoiceType getMenuChoice()
{
//	Display the menu and get the user's choice

	printMenu();
	int choice;
	cin >> choice;
	choice;
	
//	As long as the choice is invalid, request another choice

	while (choice <= NULL_CHOICE || choice > SWITCH)
	{
		cout << "Invalid. Re-enter: ";
		cin >> choice;
	}
	
//	Return the choice (cast as the enum type)

	return (ChoiceType)choice;
}

/****************************************************************************
*																			*
*	Function:	getDevChoice												*
*																			*
*	Purpose:	To get the dev's menu choice								*
*																			*
****************************************************************************/

/*DevType getDevChoice()
{
	//	Display the menu and get the user's choice
	
	printDev();
	int choice;
	cin >> choice;
	choice;
	
	//	As long as the choice is invalid, request another choice
	
	while (choice <= NCHO || choice > SWITCH)
	{
		cout << "Invalid. Re-enter: ";
		cin >> choice;
	}
	
	//	Return the choice (cast as the enum type)
	
	return (DevType)choice;
}
*/
/****************************************************************************
*																			*
*	Function:	getLocation													*
*																			*
*	Purpose:	To get the location of the 	file							*
*																			*
****************************************************************************/

string getLocation()
{ 
	switch (UNIX)
	{
		case true:
			return "John.txt";
		case false:
			return "John.txt"; 
	}
}

