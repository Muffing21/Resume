
#Wichapas Pichetpongsa
#wpichetp
#ucsc spring 2022 CSE 101
#pa5
#Makefile




#------------------------------------------------------------------------------
#  Makefile for List ADT
#
#  make                makes Shuffle
#  make ListClient     make ListClient
#  make clean          removes binary files
#  make check1         runs valgrind on ListClient
#  make check2         runs valgrind on Shuffle with CLA 35
#------------------------------------------------------------------------------

Arithmetic : Arithmetic.o List.o BigInteger.o
	g++ -std=c++17 -Wall -g -o Arithmetic Arithmetic.o List.o BigInteger.o

Arithmetic.o : List.h BigInteger.h  Arithmetic.cpp
	g++ -std=c++17 -Wall -g -c Arithmetic.cpp

ListTest : ListTest.o List.o
	g++ -std=c++17 -Wall -g -o ListTest ListTest.o List.o 

ListTest.o : List.h ListTest.cpp
	g++ -std=c++17 -Wall -c ListTest.cpp

BigIntegerTest : BigIntegerTest.o BigInteger.o List.o
	g++ -std=c++17 -Wall -g -o BigIntegerTest BigIntegerTest.o BigInteger.o List.o

List.o : List.h List.cpp
	g++ -std=c++17 -Wall -c List.cpp

BigIntegerTest.o : BigInteger.h BigIntegerTest.cpp List.h List.cpp
	g++ -std=c++17 -Wall -g -c BigIntegerTest.cpp


BigInteger.o : BigInteger.h BigInteger.cpp
	g++ -std=c++17 -Wall -g -c BigInteger.cpp

clean :
	rm -f Arithmetic Arithmetic.o ListTest ListTest.o List.o BigIntegerTest BigIntegerTest.o BigInteger.o

check1 : ListTest
	valgrind --leak-check=full ListTest

check2 : Arithmetic
	valgrind --leak-check=full Arithmetic i35
