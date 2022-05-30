#include<iostream>
#include<string>
#include<stdexcept>
#include <stdlib.h>
#include<cmath>
#include <cstring>
#include <string.h>
#include <charconv>
#include "List.h"
#include "BigInteger.h"

/*
Wichapas Pichetpongsa
wpichetp
ucsc spring 2022 CSE 101
pa6
BigInteger.cpp: List functions ADT implementation

*/

const int power = 9;
const long base = pow(10, power);

	
// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L){
	for(L.moveFront(); L.position() != L.length(); L.moveNext()){
		L.setAfter(L.peekNext()*-1);
	}				
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn){
	B.moveFront();
	A.moveFront();
	S.clear();
	
	
	while(A.position() != A.length() && B.position() != B.length()){
		S.insertBefore(A.peekNext() + B.peekNext() * sgn);
		B.moveNext();
		A.moveNext(); 	
	}
	
	while(A.position() != A.length()){
		S.insertBefore(A.moveNext());
	}
	
	while(B.position() != B.length()){
		S.insertBefore(B.moveNext() * sgn);
	}
	
	
	
}

// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List& L){
	L.moveBack();
	long temp = 0;
	while(L.length() != 0){
		L.moveBack();
		if(L.peekPrev() == 0){
			L.eraseBefore();
			if(L.length() == 0){
				return 0;
			}
	
		} else {
			break;
		}
	}
	
	if(L.length() == 0) {
		return 0;
	}
	if(L.peekPrev() >= 1){
		for(L.moveFront(); L.position() != L.length(); L.moveNext()){
			L.setAfter(L.peekNext() + temp);
			temp = 0;
			if(L.peekNext() / base >= 1){
				temp = L.peekNext() / base;
				L.setAfter(L.peekNext() % base);
			}
			else if(L.peekNext() < 0) {
				temp = L.peekNext() / base;
				long templ = L.peekNext() % base;
				if (templ != 0) {
					temp -= 1;
					templ += base;
				}
				L.setAfter(templ);
			}
		}
		if (temp > 0) {
			L.insertAfter(temp);
		}
		temp = 0;
		while(L.length() != 0){
			L.moveBack();
			if(L.peekPrev() == 0){
				L.eraseBefore();
				if(L.length() == 0){
					return 0;
				}
	
			}
			else{
				return 1;
			}
		}
	}
	if(L.peekPrev() <= -1) {
		for(L.moveFront(); L.position() != L.length(); L.moveNext()){
			L.setAfter(L.peekNext() + temp);
			temp = 0;
			if(L.peekNext() / base >= 1){
				temp = L.peekNext() / base;	
			}
			else if(L.peekNext() < 0) {
				temp = L.peekNext() / base;
				long templ = L.peekNext() % base;
				if (templ != 0) {
					temp -= 1;
					templ += base;
				}
				L.setAfter(templ);
			}
		}
		if (temp < 0) {
			L.insertAfter(-1 * temp);
		}
		temp = 0;
		while(L.length() != 0){
			L.moveBack();
			if(L.peekPrev() == 0){
				L.eraseBefore();
				if(L.length() == 0){
					return 0;
				}
	
			}
			else{
				return -1;
			}
		}
	}
	return 0;
}

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p){
	L.moveFront();
	for(int i = 0; i < p; i++){
		L.insertAfter(0);
	}
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m){
	for(L.moveFront(); L.position() != L.length(); L.moveNext()){
		L.setAfter(L.peekNext()*m);
	}
}
	
// Class Constructors & Destructors ----------------------------------------
   
BigInteger::BigInteger(){
	signum = 0;    // +1 (positive), -1 (negative), 0 (zero)
}

   // BigInteger()
   // Constructor that creates a new BigInteger from the string s.
   // Pre: s is a non-empty string consisting of (at least one) base 10 digit
   // {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){
	uint64_t z = 0;
	//char *charEnd;

	if(s.empty() == 1){
		throw std::invalid_argument("BigInteger: Constructor: empty string");
	}
	if(s.length() == 1 && !std::isdigit(s[0])) {
		throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
	}
	while(z != s.length()){
		if(s[0] == '+' || s[0] == '-'){
			z += 1;
			continue;
		}
		if(!(std::isdigit(s[z]))){
			z = 0;
			throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
		}
		z += 1;
	}
	
	
	z = 0;
	
	std::string temps = "";
	long temp;
	for(long i = s.length() - 1; i >= 0; i--){
		std::string str = s.substr(i, 1);
		if (!(str == "+" || str == "-")) {
			temps = str + temps;
		}
		if ((temps.length() == power) || (i == 0)) {
			temp = stol(temps, nullptr, 10);
			digits.insertBefore(temp);
			temps = "";
		}
	}
	
	while(digits.length() != 0){
		digits.moveBack();
		if(digits.peekPrev() == 0){
			digits.eraseBefore();
			if(digits.length() == 0){
				signum = 0;
			}
	
		}
		else{
			signum = (s[0] == '-') ? -1 : 1;
			break;
		}
	}	
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
	this->signum = N.signum;
	this->digits = N.digits;  
}
	
// Access functions --------------------------------------------------------

   // sign()
   // Returns -1, 1 or 0 according to whether this BigInteger is positive, 
   // negative or 0, respectively.
int BigInteger::sign() const{
	return signum;	
}

   // compare()
   // Returns -1, 1 or 0 according to whether this BigInteger is less than N,
   // greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{
	BigInteger n = N;
	List d = digits;
	if(N.sign() == -1 && signum != -1){
		return 1;
	}
	
	if(N.sign() != -1 && signum == -1){
		return -1;
	}
	if(N.sign() == signum){
		if(digits.length() < N.digits.length()){
			return -1 * signum;
		}
		if(digits.length() > N.digits.length()){
			return 1 * signum;
		}
		d.moveBack();
		n.digits.moveBack();
		while(d.position() != 0){
			if(d.peekPrev() > n.digits.peekPrev()){
					return 1 * signum;
				}
			if(d.peekPrev() < n.digits.peekPrev()){
				return -1 * signum;
			}
			d.movePrev();
			n.digits.movePrev();
		}
	}
	return 0;		
}

// Manipulation procedures -------------------------------------------------

   // makeZero()
   // Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
	digits.clear();
	signum = 0;
}

   // negate()
   // If this BigInteger is zero, does nothing, otherwise reverses the sign of 
   // this BigInteger positive <--> negative. 
void BigInteger::negate(){
  	if(signum == 0){
  		return;
  	}
  	signum *= -1;
  }
  
// BigInteger Arithmetic operations ----------------------------------------

   // add()
   // Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
	BigInteger n = N;
	List d = digits;
	BigInteger temp = N;
	if(signum != N.sign()) {
		if(N.sign() == -1) {
			n.negate();
			n = n.sub(*this);
			n.negate();
			return n;
		}
		if(signum == -1) {
			temp = *this;
			temp.negate();
			n = n.sub(temp);
			return n;
		}
	}
	sumList(temp.digits, d, n.digits, 1);
	temp.signum = normalizeList(temp.digits) * signum;
	return temp;
	
}

   // sub()
   // Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
	BigInteger n = N;
	List d = digits;
	BigInteger temp = N;
	bool negated = false;
	
	if(signum != N.sign()){
		if(N.sign() == -1) {
			n.negate();
			n = n.add(*this);
			return n;
		}
		if(signum == -1) {
			temp = *this;
			temp.negate();
			n = n.add(temp);
			n.negate();
			return n;
		}
	}
	
	sumList(temp.digits, d, n.digits, -1);
	if(N > *this && signum == 1){
		negateList(temp.digits);
		negated = true;
	}
	else if (N < *this && signum == -1){
		negateList(temp.digits);
		negated = true;
	} 
	
	temp.signum = normalizeList(temp.digits) * signum;
	if (negated) {
		temp.signum *= -1;
	}
	return temp;
	

}
   //scalarmult
   //shiftlist
   // mult()
   // Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{
	BigInteger n = N;
	List d = digits;
	BigInteger temp;
	temp.signum = signum * N.sign();
	
	
	for(d.moveFront(); d.position() != d.length(); d.moveNext()){
		List d2 = n.digits;
		scalarMultList(d2, d.peekNext());
		normalizeList(d2);
		shiftList(d2, d.position());
		sumList(temp.digits, temp.digits, d2, 1);
	}
	normalizeList(temp.digits);
	return temp;
}

// Other Functions ---------------------------------------------------------

   // to_string()
   // Returns a string representation of this BigInteger consisting of its
   // base 10 digits. If this BigInteger is negative, the returned string 
   // will begin with a negative sign '-'. If this BigInteger is zero, the
   // returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
	List copy = digits;
	std::string s;
	
	if(signum == -1){
		s += "-"; 
	}
	
	if(signum == 0){
		s += "0";
		return s;
	}
	
	for(digits.moveBack(); digits.position() != 0; digits.movePrev()){
			std::string s2 = std::to_string(digits.peekPrev());
			if (digits.position() <= digits.length()-1) {
				while (s2.length() < power) {
					s2 = "0" + s2;
				}
			}
			s += s2;
	}
	return s;
	
}

// Overriden Operators -----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
   	return stream << N.BigInteger::to_string();
}

// operator==()
   // Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
	return A.BigInteger::compare(B) == 0;
}

 // operator<()
   // Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
	return A.BigInteger::compare(B) == -1;
}

   // operator<=()
   // Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
	return A.BigInteger::compare(B) == -1 || A.BigInteger::compare(B) == 0;
}

   // operator>()
   // Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
	return A.BigInteger::compare(B) == 1;
}

   // operator>=()
   // Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
	return A.BigInteger::compare(B) == 1 || A.BigInteger::compare(B) == 0;
}

   // operator+()
   // Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
	return A.BigInteger::add(B);
}

   // operator+=()
   // Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
	return A = A.BigInteger::add(B);
}

   // operator-()
   // Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
	return A.BigInteger::sub(B);
}

   // operator-=()
   // Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
	return A = A.BigInteger::sub(B);
}

   // operator*()
   // Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
	return A.BigInteger::mult(B);
}

   // operator*=()
   // Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
	return A = A.BigInteger::mult(B);
}

