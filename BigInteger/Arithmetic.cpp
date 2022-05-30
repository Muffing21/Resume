#include<iostream>
#include <fstream>
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
Arithmetic.cpp: Arithmetic use bigint functions

*/

int main(int argc, char **argv){
	std::string A;
	std::string B;
	std::string nine = "9";
	std::string sixteen = "16";
	std::string three = "3";
	std::string two = "2";
	std::string blank;
	std::ifstream infile;
	std::ofstream outfile;
	
	if (argc == 3) {
		
		infile.open(argv[1]);
    		outfile.open(argv[2]);
	}
	
	if(!(argc == 3)){
		throw std::range_error("not enough arguments passed in");
	}
	
	if(infile.is_open() && outfile.is_open()){
		std::getline(infile, A);		
		std::getline(infile, blank);			
		std::getline(infile, B);
		BigInteger temp;
		
		BigInteger a = BigInteger(A);
		BigInteger b = BigInteger(B);
		BigInteger song = BigInteger(two);
		BigInteger sam = BigInteger(three);
		BigInteger gao = BigInteger(nine);
		BigInteger sibhok = BigInteger(sixteen);
		
		
		outfile << a << std::endl;
		outfile << std::endl;
		
		outfile << b << std::endl;
		outfile << std::endl;
		
		temp = a + b;
		outfile << temp << std::endl;
		outfile << std::endl;
		
		temp = a - b;
		outfile << temp << std::endl;
		outfile << std::endl;
		
		temp = a - a;
		outfile << temp << std::endl;
		outfile << std::endl;
		
		
		temp = (sam*a) - (song*b);
		outfile << temp << std::endl;
		outfile << std::endl;		
		
		temp = a * b;
		outfile << temp << std::endl;
		outfile << std::endl;		
		
		temp = a * a;
		outfile << temp << std::endl;
		outfile << std::endl;		
		
		temp = b * b;
		outfile << temp << std::endl;
		outfile << std::endl;
				
		temp = (gao*(a*a*a*a)) + (sibhok*(b*b*b*b*b));
		outfile << temp << std::endl;
		
		
	}
	infile.close();
	outfile.close();

	return 0;
}
