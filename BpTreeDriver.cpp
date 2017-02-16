/*
 *BpTreeDriver.cpp
 *driver program to test the B+Tree and Nodes
 */

#include <iostream>
#include "Node.h"
#include "BpTree.h"

void testPrint(){
	void* testNode = new LeafNode(3);

	for(int i = 5; i <= 8; i++){
		testNode = ((Node*)testNode)->insert(i, "test");
		((Node*)testNode)->printNode();
		std::cout << "\n";
	}
	for(int i = 1; i <= 4; i++){
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
	// void* testNode = new LeafNode(3);
	// testNode = ((Node*)testNode)->insert(0, "test");
	// testNode = ((Node*)testNode)->insert(1, "test");
	// testNode = ((Node*)testNode)->insert(3, "test");
	// testNode = ((Node*)testNode)->insert(4, "test");
	// testNode = ((Node*)testNode)->insert(2, "test");
	// testNode = ((Node*)testNode)->insert(9, "test");

	// std::cout << "Testing base case\n";
	// ((Node*)testNode)->printNode();
	// std::cout << std::endl;
	// //test base case, already exists, no restructuring needed


	// ((Node*)testNode)->remove(9);
	// if( ((Node*)testNode)->find(9) != ""){
	// 	std::cout << "Test 1 failed\n";
	// 	return false;
	// }

	// ((Node*)testNode)->printNode();
	// std::cout << std::endl;

	// //test case 1 -- deletion requires borrowing from left sibling
	// ((Node*)testNode)->remove(3);
	// if( ((Node*)testNode)->find(3) != ""){
	// 	std::cout << "Test 2 failed\n";
	// 	return false;
	// }


	// ((Node*)testNode)->printNode();
	// std::cout << std::endl;

	// //test case 2 -- deletion requires borrowing from right sibling
	// testNode = ((Node*)testNode)->insert(5, "test");
	// ((Node*)testNode)->remove(1);
	// if( ((Node*)testNode)->find(1) != ""){
	// 	std::cout << "Test 3 failed\n";
	// 	return false;
	// }

	// ((Node*)testNode)->printNode();
	// std::cout << std::endl;

	// //test case 3 -- deletion requires coalescing with left sibling
	// //Tree structure at this point SPECIAL CASE BAD EXAMPLE
	// // [4]
	// // [0 2] [4 5]
	// // delete 4 to force left coalesce
	// ((Node*)testNode)->remove(4);

	// std::cout << "removal finished\n";
	// if( ((Node*)testNode)->find(4) != ""){
	// 	std::cout << "Test 4 Failed\n"; //ruh roh
 // 		return false;
	// }

/*----------------------------------------------------------------------------------*/



	//((Node*)testNode)->printNode();
	//std::cout <<std::endl;


	//test case 4 -- deletion requires coalescing with right sibling
	//create new tree of structure
	//[4]
	//[2, 3] [4, 5]
	// void* testNode2 = new LeafNode(3);
	// testNode2 = ((Node*)testNode2)->insert(2, "hi");
	// testNode2 = ((Node*)testNode2)->insert(3, "hi");
	// testNode2 = ((Node*)testNode2)->insert(4, "hi");
	// testNode2 = ((Node*)testNode2)->insert(5, "hi");
	// ((Node*)testNode2)->printNode();

	// //remove 3
	// ((Node*)testNode2)->remove(3);
	// std::cout << "AFter deleting 3:\n";
	// ((Node*)testNode2)->printNode();


	//std::cout << std::endl;

	// std::cout << "Testing borrow left in InnerNodes\n";
	// void* testNode3 = new LeafNode(3);
	// for (int i = 2; i <=13; i++) {
	// 	testNode3 = ((Node*)testNode3)->insert(i, "mwhahaha");
	// }
	// ((Node*)testNode3)->printNode();

	// //delete 8, delete 12, delete 11
	// ((Node*)testNode3)->remove(8);
	// ((Node*)testNode3)->remove(12);
	// ((Node*)testNode3)->remove(11);
	// ((Node*)testNode3)->printNode();

//std::cout<< "\nTesting Borrow left in InnerNodes\n";
	//Current testNode3 should look like
	//              [6] 
	//      [4]           [9] 
	// [2, 3] [4, 5] [6, 7] [9, 10, 13] 
	// //to force [9] to coalese left, need to coalese its children
	// //delete 6, delete 7, to force
	// ((Node*)testNode3)->remove(6);
	// ((Node*)testNode3)->remove(7);
	// ((Node*)testNode3)->printNode();

	std::cout << std::endl;
	std::cout<< "Problems start here\n\n";

	void* testNode4 = new LeafNode(3);
	for (int i = 2; i <=14; i++) {
		if(i == 8 || i == 12 || i == 11 || i==7) continue;

		testNode4 = ((Node*)testNode4)->insert(i, "mwhahaha");
	}
	for(int i = -2; i <= 1; i++){
		testNode4 = ((Node*)testNode4)->insert(i, "test");
		std::cout << ((Node*)testNode4)->find(i) << std::endl;
	}
	((Node*)testNode4)->printNode();
	std::cout<<std::endl;
	// 	                           [6] 
	//            [0, 2, 4]               [10] 
	// [-2, -1] [0, 1] [2, 3] [4, 5] [6, 9] [10, 13, 14] 
	//delete 6, 9 to force coalese
	std::cout << "Removing 6\n";
	((Node*)testNode4)->remove(6);
	((Node*)testNode4)->printNode();
	std::cout<<std::endl;
	std::cout << "Removing 9\n";
	((Node*)testNode4)->remove(9);
	((Node*)testNode4)->printNode();
	std::cout << "\n";

	for(int i = 0; i <=3; i++){
		std::cout << "removing " << i << "\n";
		std::cout << "BEFORE REMOVING " << i << " find(-2) returns " << ((Node*)testNode4)->find(-2) << std::endl;
		((Node*)testNode4)->remove(i);
		std::cout << "AFTER REMOVING " << i << " find(-2) returns " << ((Node*)testNode4)->find(-2) << std::endl;
		((Node*)testNode4)->printNode();
		std::cout<<"\n";		
	}

	return true;
}

void newDeletion(){
	void* testNode = new LeafNode(3);
	for(int i = 0; i < 20; i++){
		testNode = ((Node*)testNode)->insert(i, "test");		
	}
	((Node*)testNode)->printNode();
	std::cout<<"\n";
	((Node*)testNode)->printValues();

	((Node*)testNode)->remove(12);
	((Node*)testNode)->printNode();
	std::cout<<std::endl;

	((Node*)testNode)->remove(19);
	((Node*)testNode)->printNode();
	std::cout<<std::endl;

	((Node*)testNode)->remove(11);
	((Node*)testNode)->printNode();
	std::cout<<std::endl;

	((Node*)testNode)->remove(8);
	((Node*)testNode)->printNode();
	std::cout<<std::endl;

	((Node*)testNode)->remove(7);
	((Node*)testNode)->printNode();
	std::cout<<std::endl;

	((Node*)testNode)->remove(4);
	((Node*)testNode)->printNode();
	std::cout<<std::endl;

	((Node*)testNode)->remove(5);
	((Node*)testNode)->printNode();
	std::cout<<std::endl;

	((Node*)testNode)->remove(0);
	((Node*)testNode)->printNode();
	std::cout<<std::endl;

	((Node*)testNode)->remove(1);
	((Node*)testNode)->printNode();
	std::cout<<std::endl;	

	((Node*)testNode)->remove(3);
	((Node*)testNode)->printNode();
	std::cout<<std::endl;

	((Node*)testNode)->remove(9);
	((Node*)testNode)->printNode();
	std::cout<<std::endl;

	((Node*)testNode)->remove(2);
	((Node*)testNode)->printNode();
	std::cout<<std::endl;

	((Node*)testNode)->remove(6);
	((Node*)testNode)->printNode();
	std::cout<<std::endl;

	((Node*)testNode)->remove(15);
	((Node*)testNode)->printNode();
	std::cout<<std::endl;

	((Node*)testNode)->remove(14);
	((Node*)testNode)->printNode();
	std::cout<<std::endl;

	for(int i = 0; i < 3; i++){
		testNode = ((Node*)testNode)->insert(i, "hi");
	}
	((Node*)testNode)->printNode();
	std::cout<<std::endl;

	((Node*)testNode)->remove(2);
	((Node*)testNode)->printNode();
	std::cout<<std::endl;

	((Node*)testNode)->remove(1);
	((Node*)testNode)->printNode();
	std::cout<<std::endl;
}


int main(){
	std::cout <<"Driver program\n";
	
	BpTree testTree(5);

	int keys [19]= {2, 11, 21, 8, 64, 5, 23, 97, 6, 19, 9,  7, 31, 39, 45, 51, 60, 93, 77};

	for(int i = 0; i < 19; i++){
		testTree.insert(keys[i], "test");
	}
	testTree.printKeys();

	for(int i = 0; i < 19; i++){
		//if(keys[i] % 2 == 0){
			std::cout << "Removing " << keys[i] << "\n";
			testTree.remove(keys[i]);
			testTree.printKeys();
			std::cout << "\n";
		//}
	}



	return 0;
}