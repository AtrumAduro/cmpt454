/*
 *BpTreeDriver.cpp
 *driver program to test the B+Tree and Nodes
 */

#include <iostream>
#include "Node.h"
#include "BpTree.h"

void testPrint(){
	void* testNode = new LeafNode(3);

	for(int i = 1; i <= 10; i++){
		testNode = ((Node*)testNode)->insert(i, "test");
		((Node*)testNode)->printNode();
		std::cout << "\n";
	}
}

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

bool testDeletion(){
	void* testNode = new LeafNode(3);
	testNode = ((Node*)testNode)->insert(0, "test");
	testNode = ((Node*)testNode)->insert(1, "test");
	testNode = ((Node*)testNode)->insert(3, "test");
	testNode = ((Node*)testNode)->insert(4, "test");
	testNode = ((Node*)testNode)->insert(2, "test");
	testNode = ((Node*)testNode)->insert(9, "test");

	std::cout << "Testing base case\n";
	//test base case, already exists, no restructuring needed

	((Node*)testNode)->remove(9);
	if( ((Node*)testNode)->find(9) != ""){
		std::cout << "Test 1 failed\n";
		return false;
	}

	//test case 1 -- deletion requires borrowing from left sibling
	((Node*)testNode)->remove(3);
	if( ((Node*)testNode)->find(3) != ""){
		std::cout << "Test 2 failed\n";
		return false;
	}

	//test case 2 -- deletion requires borrowing from right sibling
	testNode = ((Node*)testNode)->insert(5, "test");
	((Node*)testNode)->remove(1);
	if( ((Node*)testNode)->find(1) != ""){
		std::cout << "Test 3 failed\n";
		return false;
	}

	//test case 3 -- deletion requires coalescing with left sibling
	//Tree structure at this point SPECIAL CASE BAD EXAMPLE
	// [4]
	// [0 2] [4 5]
	// delete 4 to force left coalesce
	((Node*)testNode)->remove(4);

	std::cout << "removal finished\n";
	if( ((Node*)testNode)->find(4) != ""){
		std::cout << "Test 4 Failed\n"; //ruh roh
 		return false;
	}
	


	return true;
}

int main(){
	std::cout <<"Driver program\n";

	std::cout <<"Testing printing of the tree\n";
	testPrint();

	std::cout << "\nTesting find() in LeafNode\n";
	if(testSearchLeaf()){
		std::cout << "Find in LeafNode passes tests\n";
	}
	else{
		std::cout << "Find in LeafNode failed a test\n";
		return 1;
	}

	std::cout << "\nTesting find() with InnerNodes\n";
	if(testSearchFull()){
		std::cout << "Find with InnerNodes passes tests\n";
	}
	else{
		std::cout << "Find with InnerNodes failed a test\n";
		return 1;
	}


	std::cout << "\nTesting deletion\n";
	if(testDeletion()){
		std::cout << "deletion passes tests\n";
	}
	else{
		std::cout << "deletion failed a test";
		return 1;
	}
	return 0;
}