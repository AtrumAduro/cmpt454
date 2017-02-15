all:
	rm -rf a.out
	g++ -std=c++1y -g Node.h BpTree.h Node.cpp BpTree.cpp BpTreeDriver.cpp
	
