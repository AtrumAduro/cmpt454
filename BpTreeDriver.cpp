/*
 *BpTreeDriver.cpp
 *driver program to test the B+Tree and Nodes
 */

#include <iostream>
#include "Node.h"
#include "BpTree.h"

bool testSearchLeaf(){
	void* testNode = new LeafNode(99);
	for(int i = 0; i < 99; i++){
		((Node*)testNode)->insert(2*i, "test");
	}

	if( ((Node*)testNode)->find(0) != "test"){
		std::cout << "Failed test 1\n";
		return false;
	}

	if( ((Node*)testNode)->find(1) != ""){
		std::cout << "Failed test 2\n";
		return false;
	}

	return true;
}

int main(){
	std::cout <<"Driver program\n";
	
	std::cout << "Testing find() in LeafNode\n";

	if(testSearchLeaf()){
		std::cout << "Find in LeafNode passes tests\n";
	}
	else{
		std::cout << "Find in LeafNode failed a test\n";
		return 1;
	}
	return 0;
}