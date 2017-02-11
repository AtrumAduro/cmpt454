/*
 *BpTreeDriver.cpp
 *driver program to test the B+Tree and Nodes
 */

#include <iostream>
#include "Node.h"
#include "BpTree.h"

bool testSearchLeaf(){
	void* testNode = new LeafNode(5);
	for(int i = 0; i < 4; i++){
		testNode = ((Node*)testNode)->insert(2*i, "test");
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

bool testSearchFull(){
	void* testNode = new LeafNode(3);
	for(int i = 0; i < 9; i++){
		if(i == 4) continue;
		testNode = ((Node*)testNode)->insert(i, "test");
		
	}

	//search for entry at beginning of index
	if( ((Node*)testNode)->find(1).compare("test") != 0){
		std::cout << "Failed test 1\n";
		return false;
	}

	//search for entry towards end of index
	if( ((Node*)testNode)->find(8) != "test"){
		std::cout << "Failed test 2\n";
		return false;
	}

	//search for entry below index's range
	if( ((Node*)testNode)->find(-1) != ""){
		std::cout << "Failed test 3\n";
		return false;
	}

	//search for entry within index's range, but not included
	if( ((Node*)testNode)->find(4) != ""){
		std::cout << "Failed test 4\n";
		return false;
	}

	//search for entry above index's range
	if( ((Node*)testNode)->find(15) != ""){
		std::cout << "Failed test 5\n";
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

	std::cout << "Testing find() with InnerNodes\n";
	if(testSearchFull()){
		std::cout << "Find with InnerNodes passes tests\n";
	}
	else{
		std::cout << "Find with InnerNodes failed a test\n";
	}
	return 0;
}