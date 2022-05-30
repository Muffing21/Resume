/*
Wichapas Pichetpongsa
wpichetp
ucsc spring 2022 CSE 101
pa6
ListTest.c: List functions testing

*/

#include <iostream>
#include <string>
#include <stdexcept>
#include "List.h"

int main(void){
	List A;
	List B;
	List C;
	
	int x;
	
	for(x = 1; x <= 7; x++){
		A.insertBefore(x);
		B.insertBefore(x+1);
		C.insertAfter(x);
	}
	
	std::cout << "A List: " << A << std::endl;
	std::cout << "A front: " << A.front() << std::endl;
	for(A.moveFront(); A.position() < A.length(); A.moveNext()){
		std::cout << "A position: " << A.position() << std::endl;
		std::cout << "A length: " << A.length() << std::endl;
		std::cout << "A peekNext: " << A.peekNext() << std::endl;
		if(A.position() != 0){
			std::cout << "A peekPrev: " << A.peekPrev() << std::endl;
		}
		
	}
	
	
	std::cout << "B List: " << B << std::endl;
	for(B.moveFront(); B.position() < B.length(); B.moveNext()){
		std::cout << "B position: " << B.position() << std::endl;
		std::cout << "B length: " << B.length() << std::endl;
		std::cout << "B peekNext: " << B.peekNext() << std::endl;
		if(B.position() != 0){
			std::cout << "B peekPrev: " << B.peekPrev() << std::endl;
		}
			
	}
	
	std::cout << "C List: " << C << std::endl;
	for(C.moveBack(); C.position() != 0; C.movePrev()){
		std::cout << "B position: " << B.position() << std::endl;
		std::cout << "B length: " << B.length() << std::endl;
		std::cout << "B peekPrev: " << B.peekPrev() << std::endl;
		if(B.position() != B.length()){
			std::cout << "B peekNext: " << B.peekNext() << std::endl;
		}
	}
	
	if(A.equals(C)){
		std::cout << "true" << std::endl;
	}
	else{
		std::cout << "false" << std::endl;
	}
	
	if(A.equals(B)){
		std::cout << "true" << std::endl;
	}
	else{
		std::cout << "false" << std::endl;
	}
	
	for(A.moveFront(); A.position() != A.length(); A.moveNext()){
		if(A.position() == 5){
			A.setAfter(420);
			A.setBefore(69);
			std::cout << "A after setAfter and Before: " << A << std::endl;
		}
		
		if(A.position() == 8){
			A.eraseBefore();
			A.eraseAfter();
			std::cout << "A after eraseAfter and Before: " << A << std::endl;
		}
	}
	
	
	
	
	A.moveFront();
	int z = A.findNext(69);
	std::cout << "findNext value: " << z << std::endl;
	
	C.moveBack();
	int c = C.findPrev(1);
	std::cout << "findPrev Value: " << c << std::endl;
	
	A.insertAfter(1);
	A.insertAfter(1);
	A.insertAfter(1);
	B.insertAfter(2);
	B.insertAfter(2);
	B.insertAfter(2);
	C.insertAfter(3);
	C.insertAfter(3);
	C.insertAfter(3);
	std::cout << "A List before cleanup: " << A << std::endl;
	std::cout << "B List before cleanup: " << B << std::endl;
	std::cout << "C List before cleanup: " << C << std::endl;
	
	A.cleanup();
	B.cleanup();
	C.cleanup();	
	std::cout << "A List cleanup: " << A << std::endl;
	std::cout << "B List cleanup: " << B << std::endl;
	std::cout << "C List cleanup: " << C << std::endl;
	
	
	
	std::cout << "A concat B: " << A.concat(B) << std::endl;
	A.clear();
	B.clear();
	C.clear();
	std::cout << "A clear: " << A << std::endl;
	std::cout << "B clear: " << B << std::endl;
	std::cout << "C clear: " << C << std::endl;
	
	
}
