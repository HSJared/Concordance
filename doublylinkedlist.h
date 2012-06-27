/*****************************************************************************																			**	File:		doublylinkedlist.h											**																			**	Author:		Robb T. Koether												**																			**	Date:		Mar 8, 2007													**																			**	Purpose:	This file defines the DoublyLinkedList template class and 	**				implements its member functions								**																			*****************************************************************************/#ifndef DOUBLYLINKEDLIST_H#define DOUBLYLINKEDLIST_H//	Header files#include <iostream>#include <cassert>#include "doublylinkedlistnode.h"using namespace std;/*****************************************************************************																			**	The DoublyLinkedList class definition									**																			*****************************************************************************/template <class T>class DoublyLinkedList{//	Public member functions	public:	//	Constructors		DoublyLinkedList(int sz = 0, const T& value = T());		DoublyLinkedList(const DoublyLinkedList<T>& lst) {makeCopy(lst);}		//	Destructor			~DoublyLinkedList() {makeEmpty();}	//	Inspectors		T getElement(int pos) const {return locateNode(pos)->data;}		T& getElement(int pos) {return locateNode(pos)->data;}		int size() const {return mSize;}		bool isEmpty() const {return mSize == 0;}	//	Mutators		void setElement(int pos, const T& value) {getElement(pos) = value;}		void insert(int pos, const T& value);		void remove(int);		void pushFront(const T& value);		void pushBack(const T& value);		T popFront();		T popBack();		void makeEmpty();	//	Facilitators			void input(istream&);		void output(ostream&) const;		bool isEqual(const DoublyLinkedList<T>& lst) const;	//	Operators		DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>&);		T operator[](int pos) const {return getElement(pos);}		T& operator[](int pos) {return getElement(pos);}	//	Other functions			void swap(DoublyLinkedList<T>& lst);		int search(const T& value) const;		void sort();		bool isValid() const;	//	Private member functions		private:		void makeCopy(const DoublyLinkedList<T>&);		DoublyLinkedListNode<T>* locateNode(int pos) const;//	Data members	protected:		int mSize;		DoublyLinkedListNode<T>* head;		DoublyLinkedListNode<T>* tail;};//	List operatorstemplate <class T>istream& operator>>(istream& in, DoublyLinkedList<T>& list);template <class T>ostream& operator<<(ostream& out, const DoublyLinkedList<T>& list);template <class T>bool operator==(const DoublyLinkedList<T>& list1, const DoublyLinkedList<T>& list2);template <class T>bool operator!=(const DoublyLinkedList<T>& list1, const DoublyLinkedList<T>& list2);/*****************************************************************************																			**	Function:	DoublyLinkedList(int = 0, T = T())							**																			**	Purpose:	To construct a doubly linked list containing a specified	**				number of nodes containing default values					**																			*****************************************************************************/template <class T>inline DoublyLinkedList<T>::DoublyLinkedList(int sz, const T& value){//	Check that sz is valid	assert(sz >= 0);		mSize = sz;//	Establish an empty list	if (mSize == 0)		head = tail = NULL;	else	{	//	Establish and initialize a non-empty list		head = new DoublyLinkedListNode<T>(value);		DoublyLinkedListNode<T>* node = head;		for (int i = 1; i < mSize; i++)		{			node->next = new DoublyLinkedListNode<T>(value);			node->next->prev = node;			node = node->next;		}		tail = node;	}		return;}/*****************************************************************************																			**	Function:	insert														**																			**	Purpose:	To insert a new element into the specified position of the	**				list														**																			*****************************************************************************/template <class T>void DoublyLinkedList<T>::insert(int pos, const T& value){	assert(pos >= 0 && pos <= mSize);//	Create a new node	DoublyLinkedListNode<T>* new_node = new DoublyLinkedListNode<T>(value);//	Locate the new position	DoublyLinkedListNode<T>* curr_node;	if (pos < mSize/2)	{		curr_node = head;		for (int i = 0; i < pos; i++)			curr_node = curr_node->next;	}	else if (pos < mSize)	{		curr_node = tail;		for (int i = 0; i < mSize - pos - 1; i++)			curr_node = curr_node->prev;	}	else		curr_node = NULL;//	Get pointer to the previous node	DoublyLinkedListNode<T>* prev_node;		if (curr_node == NULL)		prev_node = tail;	else		prev_node = curr_node->prev;//	Set the pointers of the new node	new_node->prev = prev_node;	new_node->next = curr_node;//	Set the next pointer of the new node's predecessor	if (prev_node == NULL)		head = new_node;	else		prev_node->next = new_node;//	Set the prev pointer of the new node's successor	if (curr_node == NULL)		tail = new_node;	else		curr_node->prev = new_node;//	Update the size	mSize++;	return;}/*****************************************************************************																			**	Function:	remove														**																			**	Purpose:	To delete from the list the element in the specified		**				position													**																			*****************************************************************************/template <class T>void DoublyLinkedList<T>::remove(int pos){	assert(pos >= 0 && pos < mSize);//	Locate the node to be deleted	DoublyLinkedListNode<T>* node;		if (pos < mSize/2)	{		node = head;		for (int i = 0; i < pos; i++)			node = node->next;	}	else	{		node = tail;		for (int i = 0; i < mSize - pos - 1; i++)			node = node->prev;	}//	Delete the node from the list		if (node == head)			// Deleting first node		head = node->next;	else		node->prev->next = node->next;		if (node == tail)			// Deleting last node		tail = node->prev;	else		node->next->prev = node->prev;//	Deallocate the memory	delete node;//	Update the size	mSize--;	return;}/*****************************************************************************																			**	Function:	pushFront													**																			**	Purpose:	To append the specified element onto the end of the list	**																			*****************************************************************************/template <class T>void DoublyLinkedList<T>::pushFront(const T& value){//	Create a new node	DoublyLinkedListNode<T>* new_node = new DoublyLinkedListNode<T>(value);//	Append the new node	if (mSize > 0)		head->prev = new_node;	else		tail = new_node;	new_node->next = head;	head = new_node;//	Update the size	mSize++;	return;}/*****************************************************************************																			**	Function:	pushBack													**																			**	Purpose:	To append the specified element onto the end of the list	**																			*****************************************************************************/template <class T>void DoublyLinkedList<T>::pushBack(const T& value){//	Create a new node	DoublyLinkedListNode<T>* new_node = new DoublyLinkedListNode<T>(value);//	Append the new node	if (mSize > 0)		tail->next = new_node;	else		head = new_node;	new_node->prev = tail;	tail = new_node;//	Update the size	mSize++;	return;}/*****************************************************************************																			**	Function:	popFront													**																			**	Purpose:	To delete the element at the end of the list				**																			*****************************************************************************/template <class T>T DoublyLinkedList<T>::popFront(){	assert(mSize > 0);//	Get value from the first node and adjust the head	T value = head->data;	head = head->next;//	Remove the node from the list	DoublyLinkedListNode<T>*& node = (head == NULL) ? tail : head->prev;	delete node;	node = NULL;	mSize--;	return value;}/*****************************************************************************																			**	Function:	popBack														**																			**	Purpose:	To delete the element at the end of the list				**																			*****************************************************************************/template <class T>T DoublyLinkedList<T>::popBack(){	assert(mSize > 0);	//	Get value from the last node and adjust the tail	T value = tail->data;	tail = tail->prev;	//	Remove the node from the list	DoublyLinkedListNode<T>*& node = (tail == NULL) ? head : tail->next;	delete node;	node = NULL;	mSize--;	return value;}/*****************************************************************************																			**	Function:	makeEmpty													**																			**	Purpose:	To remove all elements from the list, returning the list	**				to the empty state											**																			*****************************************************************************/template <class T>void DoublyLinkedList<T>::makeEmpty(){//	Deallocate each of the nodes	DoublyLinkedListNode<T>* prev_node = NULL;	DoublyLinkedListNode<T>* curr_node = head;	for (int i = 0; i < mSize; i++)	{		prev_node = curr_node;		curr_node = curr_node->next;		delete prev_node;	}//	Reinitialize the data members	mSize = 0;	tail = NULL;	head = NULL;	return;}/*****************************************************************************																			**	Function:	input														**																			**	Purpose:	To extract a doubly linked list from the input stream		**																			*****************************************************************************/template <class T>void DoublyLinkedList<T>::input(istream& in){//	Clear out the old list	makeEmpty();	//	Read the left brace	char c;	in >> c;	assert(c == '{');//	Check for an empty list	in >> c;	if (c == '}')		return;		in.putback(c);	T value;//	Read the values and put them in the list	while (c != '}')	{		in >> value;		pushBack(value);		in >> c;	}		return;}/*****************************************************************************																			**	Function:	output														**																			**	Purpose:	To insert a doubly linked list into the output stream		**																			*****************************************************************************/template <class T>void DoublyLinkedList<T>::output(ostream& out) const{//	Output the left brace	out << "{";	if (mSize > 0)	{	//	Output the first value			out << head->data;		DoublyLinkedListNode<T>* node = head->next;		//	Output the remaining values, with commas			while (node != NULL)		{			out << ", " << node->data;			node = node->next; 		}	}//	Output the right brace	out << "}";	return;}/*****************************************************************************																			**	Function:	isEqual														**																			**	Purpose:	This function will determine whether two lists are equal	**																			*****************************************************************************/template <class T>bool DoublyLinkedList<T>::isEqual(const DoublyLinkedList<T>& lst) const{	if (mSize != lst.mSize)		return false;		DoublyLinkedListNode<T>* p1 = head;	DoublyLinkedListNode<T>* p2 = lst.head;	for (int i = 0; i < mSize; i++)		if (p1->data != p2->data)			return false;		else		{			p1 = p1->next;			p2 = p2->next;		}		return true;}/*****************************************************************************																			**	Function:	operator=													**																			**	Purpose:	To assign one doubly linked list to another doubly linked	**				list.  This is the assignment operator.						**																			*****************************************************************************/template <class T>DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& lst){	if (this != &lst)	{		makeEmpty();		makeCopy(lst);	}	return *this;}/*****************************************************************************																			**	Function:	swap														**																			**	Purpose:	To swap two doubly linked lists								**																			*****************************************************************************/template <class T>void DoublyLinkedList<T>::swap(DoublyLinkedList<T>& lst){//	Swap the sizes	int tempSize = mSize;	mSize = lst.mSize;	lst.mSize = tempSize;	//	Swap the heads	DoublyLinkedListNode<T>* tempHead = head;	head = lst.head;	lst.head = tempHead;	//	Swap the tails	DoublyLinkedListNode<T>* tempTail = tail;	tail = lst.tail;	lst.tail = tempTail;		return;}/*****************************************************************************																			**	Function:	search(T)													**																			**	Purpose:	To search the list for the specified value.  If the value	**				is found, then its position is returned.  If it is not		**				found, then 0 is returned.									**																			*****************************************************************************/template <class T>int DoublyLinkedList<T>::search(const T& value) const{//	Start at the head	DoublyLinkedListNode<T>* node = head;	int pos = 0;//	Look in each node for the value	while (node != NULL && node->data != value)	{		node = node->next;		pos++;	}//	Report where it was found, or 0 if not found	if (node == NULL)		return -1;	else		return pos;}/*****************************************************************************																			**	Function:	sort														**																			**	Purpose:	To sort the elements into ascending order					**																			*****************************************************************************/template <class T>void DoublyLinkedList<T>::sort(){	for (DoublyLinkedListNode<T>* base = head; base != NULL; base = base->next)	{	//	Find minimal element in remainder of list			DoublyLinkedListNode<T>* min = base;		for (DoublyLinkedListNode<T>* curr = min; curr != NULL; curr = curr->next)			if (curr->data < min->data)				min = curr;		//	Swap minimal element with base element			T temp = base->data;		base->data = min->data;		min->data = temp;	}}/*****************************************************************************																			**	Function:	isValid														**																			**	Purpose:	To validate the doubly linked list							**																			*****************************************************************************/template <class T>bool DoublyLinkedList<T>::isValid() const{	if (mSize < 0)	{		cerr << "Error: mSize < 0" << endl;		return false;	}		if (mSize == 0)	{		if (head != NULL)		{			cerr << "Error: mSize == 0 && head != NULL" << endl;			return false;		}		if (tail != NULL)		{			cerr << "Error: mSize == 0 && tail != NULL" << endl;			return false;		}	}		DoublyLinkedListNode<T>* curr_node = head;	// Node[1] (NULL if mSize == 0)	DoublyLinkedListNode<T>* prev_node = NULL;	// NULL	DoublyLinkedListNode<T>* prev2_node;		if (mSize >= 1)	{		assert(head != NULL);		assert(curr_node->prev == NULL);		prev2_node = NULL;				// NULL		prev_node = curr_node;			// Node[1]		curr_node = curr_node->next;	// Node[2] (NULL if mSize == 1)				if (mSize >= 2)		{			assert(curr_node->prev == head);	// Node[2].prev == head			for (int i = 2; i < mSize; i++)			{				prev2_node = prev_node;			// Node[i - 1]				prev_node = curr_node;			// Node[i]				curr_node = curr_node->next;	// Node[i + 1]				assert(prev2_node->next == curr_node->prev);	// Node[i - 1].next == Node[i + 1].prev			}			prev2_node = prev_node;			// Node[mSize - 1]			prev_node = curr_node;			// Node[mSize]			curr_node = curr_node->next;	// NULL		}		assert(curr_node == NULL);	// Node[mSize].next == NULL		assert(prev_node == tail);	// Node[mSize - 1].next == tail (head == tail if mSize == 1)	}		return true;}/*****************************************************************************																			**	Function:	makeCopy													**																			**	Purpose:	To make a copy of the nodes of a list						**																			*****************************************************************************/template <class T>void DoublyLinkedList<T>::makeCopy(const DoublyLinkedList<T>& lst){	mSize = lst.mSize;//	If new list is empty, set pointers to null	if (mSize == 0)		head = tail = NULL;	else	{	//	Create the first node			head = new DoublyLinkedListNode<T>(lst.head->data);		//	Chase pointers, copying nodes along the way			DoublyLinkedListNode<T>* new_node = head;		DoublyLinkedListNode<T>* old_node = lst.head->next;				while (old_node != NULL)		{			new_node->next = new DoublyLinkedListNode<T>(old_node->data);			new_node->next->prev = new_node;			new_node = new_node->next;			old_node = old_node->next;		}		//	set tail to last node			tail = new_node;	}	return;}/*****************************************************************************																			**	Function:	locateNode													**																			**	Purpose:	To a pointer to the node in the specified position			**																			*****************************************************************************/template <class T>DoublyLinkedListNode<T>* DoublyLinkedList<T>::locateNode(int pos) const{	assert(pos >= 0 && pos < mSize);	DoublyLinkedListNode<T>* node;//	If element is closer to head, start at head	if (pos < mSize/2)	{		node = head;		for (int i = 0; i < pos; i++)			node = node->next;	}//	If element is closer to tail, start at tail	else	{		node = tail;		for (int i = 0; i < mSize - pos - 1; i++)			node = node->prev;	}		return node;}/*****************************************************************************																			**	Function:	operator>>													**																			**	Purpose:	To extract a doubly linked list from the input stream		**																			*****************************************************************************/template <class T>istream& operator>>(istream& in, DoublyLinkedList<T>& lst){	lst.input(in);	return in;}/*****************************************************************************																			**	Function:	operator<<													**																			**	Purpose:	To insert a doubly linked list into the output stream		**																			*****************************************************************************/template <class T>ostream& operator<<(ostream& out, const DoublyLinkedList<T>& lst){	lst.output(out);	return out;}/*****************************************************************************																			**	Function:	operator==													**																			**	Purpose:	This function will determine whether two lists are equal	**																			*****************************************************************************/template <class T>bool operator==(const DoublyLinkedList<T>& list1, const DoublyLinkedList<T>& list2){	return list1.isEqual(list2);}/*****************************************************************************																			**	Function:	operator!=													**																			**	Purpose:	This function will determine whether two lists are not		**				equal														**																			*****************************************************************************/template <class T>bool operator!=(const DoublyLinkedList<T>& list1, const DoublyLinkedList<T>& list2){	return !list1.isEqual(list2);}#endif