//-----------------------------------------------------------------------------
//  BigIntegerClient.cpp 
//  A test client for the BigInteger ADT
//-----------------------------------------------------------------------------

/*
Wichapas Pichetpongsa
wpichetp
ucsc spring 2022 CSE 101
pa6
BigIntegerTest.cpp: List functions ADT

*/

#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){
	int temp = 0;
	BigInteger bigTemp;
	BigInteger bigTemp2;
   string s1 = "696969420123456987654321000001";
   string s3 = "9876545439000000000000000200000000000006543654365346534";

    BigInteger A = BigInteger(s1);
    BigInteger C = BigInteger(s3);

	std::cout << "A: " << A << std::endl;
	std::cout << "C: " << C << std::endl;

	
	std::cout << "A Sign: " << A.sign() << std::endl;
	std::cout << "C Sign: " << C.sign() << std::endl;
	
	
	temp = A.compare(C);
	std::cout << "A compare with B: " << temp << std::endl;
	
	bigTemp = A + C;
	std::cout << "A + C: " << bigTemp << std::endl;
	
	bigTemp2 = C + A;
	std::cout << "C + A: " << bigTemp2 << std::endl;
	if(bigTemp == bigTemp2){
		std::cout << "A+C == C+A" << std::endl;
	}
	
	bigTemp = A - C;
	std::cout << "A - C: " << bigTemp << std::endl;
	
	bigTemp2 = C - A;
	std::cout << "C - A: " << bigTemp2 << std::endl;
	if(bigTemp < bigTemp2 || bigTemp > bigTemp2){
		std::cout << "A-C != A-C" << std::endl;
	}
	
	bigTemp2 = A * C;
	std::cout << "A * C: " << bigTemp2 << std::endl;
	
	bigTemp = C * A;
	std::cout << "C * A: " << bigTemp << std::endl;
	if(bigTemp == bigTemp2){
		std::cout << "A*C == C*A" << std::endl;
	}
	
	bigTemp = A*C*A*C;
	std::cout << "A*C*A*C: " << bigTemp << std::endl;
	
	C.negate();
	std::cout << "C negated: " << C << std::endl;
	
	A.makeZero();
	std::cout << "A to zero state: " << A << std::endl;
	
	
	

   return EXIT_SUCCESS;
}

