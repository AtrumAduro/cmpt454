/*
 *BpTreeDriver.cpp
 *driver program to test the B+Tree and Nodes
 */

#include <iostream>
#include "Node.h"
#include "BpTree.h"

int main(){
	std::cout <<"Driver program\n";
	LeafNode testNode(5);
	testNode.insert(1, "1");
	testNode.insert(2, "2");
	testNode.insert(3, "3");
	testNode.insert(4, "4");
	testNode.insert(5, "5");

	testNode.printNode();
	return 0;
}