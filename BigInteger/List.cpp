#include<iostream>
#include<string>
#include<stdexcept>
#include "List.h"

/*
Wichapas Pichetpongsa
wpichetp
ucsc spring 2022 CSE 101
pa6
List.cpp: List functions ADT

*/

// Node constructor ------------------------------

List::Node::Node(ListElement x){
	data = x;
	next = nullptr;
	prev = nullptr;
}

// Class Constructors & Destructors ------------------

List::List(){
	
	frontDummy = new Node(1);
	backDummy = new Node(69);
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	pos_cursor = 0;
	num_elements = 0;
}	

//copy constructor
List::List(const List& L){	
	// make this an empty List
	frontDummy = new Node(1);
	backDummy = new Node(69);
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	
	//afterCursor->next = backDummy;
	//beforeCursor->prev = frontDummy;
	pos_cursor = 0;
	num_elements = 0; 
	
	//load elements of L into the List
	Node* N = L.frontDummy->next;
	while(N != L.backDummy){
		this->insertBefore(N->data);
		N = N->next;
	}
}

// Destructor
List::~List(){
	clear();
	delete frontDummy;
	delete backDummy;
}

// Access Functions ---------------------------------------------------------

   // Returns the length of this List.
int List::length() const{
	return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
	if(length() <= 0){
		throw std::length_error("List: front(): on empty list");	
	}
	return frontDummy->next->data;
}

   // back()
   // Returns the back element in this List.
   // pre: length()>0
ListElement List::back() const{
	if(length() <= 0){
		throw std::length_error("List: back(): on empty list");
				
	}
	return backDummy->prev->data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
	return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const{
	if(position() >= length()){
		throw std::range_error("List: peekNext(): error");
	}
	
	return afterCursor->data;
	
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
	if(position() <= 0){
		throw std::range_error("List: peekPrev(): error");
	}
	return beforeCursor->data;
}


// Manipulation procedures -------------------------------------------------

// clear()
   // Deletes all elements in this List, setting it to the empty state.
void List::clear(){
	while(length() > 0){
		moveFront();
		eraseAfter();
	}
}

// moveFront()
   // Moves cursor to position 0 in this List.
void List::moveFront(){
	beforeCursor = frontDummy;
	afterCursor = frontDummy->next;
	pos_cursor = 0;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
	afterCursor = backDummy;
	beforeCursor = backDummy->prev;
	pos_cursor = length();
}


// moveNext()
   // Advances cursor to next higher position. Returns the List element that
   // was passed over. 
   // pre: position()<length() 
ListElement List::moveNext(){
	if(position() >= length()){
		throw std::range_error("List: moveNext(): error");
	}
	afterCursor = afterCursor->next;
	beforeCursor = afterCursor->prev;
	pos_cursor += 1;
	return beforeCursor->data;
}

// movePrev()
   // Advances cursor to next lower position. Returns the List element that
   // was passed over. 
   // pre: position()>0
ListElement List::movePrev(){
	if(position() <= 0){
		throw std::range_error("List: movePrev(): error");
	}
	beforeCursor = beforeCursor->prev;
	afterCursor = beforeCursor->next;
	pos_cursor -= 1;
	return afterCursor->data;
}

// insertAfter()
   // Inserts x after cursor.
   //chck here could be the problem
void List::insertAfter(ListElement x){
	Node* n = new Node(x);
	beforeCursor->next = n;
	afterCursor->prev = n;
	n->next = afterCursor;
	n->prev = beforeCursor;
	afterCursor = n;
	num_elements += 1;
}

void List::insertBefore(ListElement x){
	Node *n = new Node(x);
	afterCursor->prev = n;
	beforeCursor->next = n;
	n->prev = beforeCursor;
	n->next = afterCursor;
	beforeCursor = n;
	pos_cursor += 1;
	num_elements += 1;
}

// setAfter()
   // Overwrites the List element after the cursor with x.
   // pre: position()<length()
void List::setAfter(ListElement x){
	if(position()>= length()){
		throw std::range_error("List: setAfter(): error");
	}
	afterCursor->data = x;
}

void List::setBefore(ListElement x){
	if(position() <= 0){
		throw std::range_error("List: setBefore(): error");
	}
	beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
	if(position() >= length()){
		throw std::range_error("List: eraseAfter(): error");
	}

	beforeCursor->next = afterCursor->next;
	afterCursor->next->prev= beforeCursor;
	delete afterCursor;
	afterCursor = beforeCursor->next;
	num_elements -= 1;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
	if(position()<= 0){
		throw std::range_error("List: eraseBefore(): error");
	}
	//Node *N;
	afterCursor->prev = beforeCursor->prev;
	beforeCursor->prev->next = afterCursor;
	delete beforeCursor;
	beforeCursor = afterCursor->prev;
	num_elements -= 1;
	pos_cursor -= 1;
}


// Other Functions ---------------------------------------------------------

// Starting from the current cursor position, performs a linear search (in 
   // the direction front-to-back) for the first occurrence of element x. If x
   // is found, places the cursor immediately after the found element, then 
   // returns the final cursor position. If x is not found, places the cursor 
   // at position length(), and returns -1. 
int List::findNext(ListElement x){
	while(position() != length()){
		if(afterCursor->data == x){
			moveNext();
			return position();
		}
		moveNext();
	}
	return -1;
}

// Starting from the current cursor position, performs a linear search (in 
   // the direction back-to-front) for the first occurrence of element x. If x
   // is found, places the cursor immediately before the found element, then
   // returns the final cursor position. If x is not found, places the cursor 
   // at position 0, and returns -1. 
int List::findPrev(ListElement x){
	while(position() != 0){
		if(beforeCursor->data == x){
			movePrev();
			return position();
		}
		movePrev();
	}
	return -1;
}

// cleanup()
   // Removes any repeated elements in this List, leaving only unique elements.
   // The order of the remaining elements is obtained by retaining the frontmost 
   // occurrance of each element, and removing all other occurances. The cursor 
   // is not moved with respect to the retained elements, i.e. it lies between 
   // the same two retained elements that it did before cleanup() was called.
//implementation is from this https://www.geeksforgeeks.org/remove-duplicates-from-a-sorted-linked-list/
//I got help from that website and decided to use their logic for help

void List::cleanup(){	
	
	/*	
	int cursor = position(); //save position for later
	moveFront();
	while(position() < length()){
		moveNext();
		int temp = position();
		ListElement temp2 = peekNext();
		moveNext();
		while(findNext(temp2) >  0){
			eraseAfter();
			if(position() < cursor){
				pos_cursor -= 1;	
			}
		}
		while(position() != temp){
			movePrev();
		}
	}
	while(position() != cursor){
		movePrev();
	}
	
}
*/	
	
	

	Node *temp1; 
	Node *temp2;
	Node *temp3;
	int n = 0;
	int m;
	//n and m can be treated like first and second node respectively
	
	temp1 = frontDummy->next;
	
	if(length() == 1){
		return;
	}
	
	while(temp1 != backDummy && temp1->next != backDummy){
		temp2 = temp1;
		m = n+1;
		while(temp2->next != backDummy){  
			if(temp1->data == temp2->next->data){ //check if temp1 data (element before temp2) is == to the next element
				temp3 = temp2->next; 		//temp3 for storing the second node before deleting
				temp2->next = temp2->next->next;	// make the 2nd node move forward
				temp2->next->prev = temp2;
				delete(temp3);				//delete the previous location of 2nd node
				num_elements -= 1;			
				if(m == position()){			//now check for 1 of the 3 cases: if position m is == to starting position()
					afterCursor = temp2->next;	//the afterCursor is now
				}
				else if (m+1 == position()){		//2nd case: it's at the after cursor
					beforeCursor = temp2;		//before cursor is temp2 because 
				}
				if(m < position()){			//3rd case: far away dup from cursor
					pos_cursor -= 1;		
				}
			}
			else{
				temp2 = temp2->next;
				m += 1;
			}
		}
		temp1 = temp1->next;					//after going thru the whole list, move the 1st node next
		n += 1;						
		
	}
	
}



// concat()
   // Returns a new List consisting of the elements of this List, followed by
   // the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
	List newList = *this;
	List copy = L;
	newList.moveBack();
	
	for(copy.moveFront(); copy.position() != copy.length(); copy.moveNext()){
		newList.insertBefore(copy.peekNext());
	}
	newList.moveFront();
	return newList;
}

// to_string()
   // Returns a string representation of this List consisting of a comma 
   // separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
	
	List copy = *this;
	std::string s = "(";
	

	for(copy.moveFront(); copy.position() != copy.length(); copy.moveNext()){
		s += std::to_string(copy.peekNext());
		if(copy.position() != copy.length()-1){
			s += ", ";
			//fix this later
		} 
	}
	s += ")";
	return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
	
	List copy = *this;
	List R_copy = R;
	
	if(copy.length() != R_copy.length()){
		return false;
	}
	
	copy.moveFront();
	R_copy.moveFront();
	while(copy.position() != copy.length()){
		if(copy.peekNext() != R_copy.peekNext()){
			return false;
		}
		R_copy.moveNext();
		copy.moveNext();
	}
	return true;		
}

// Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
	return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
	return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
if( this != &L ){ // not self assignment
      // make a copy of Q
      List temp = L;

      // then swap the copy's fields with fields of this
      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
      std::swap(num_elements, temp.num_elements);
      std::swap(pos_cursor, temp.pos_cursor);
      std::swap(beforeCursor, temp.beforeCursor);
      std::swap(afterCursor, temp.afterCursor);
      
      
      
   }

   // return this with the new data installed
   return *this;
   
   // the copy, if there is one, is deleted upon return
}




