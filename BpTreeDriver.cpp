/*
 *BpTreeDriver.cpp
 *driver program to test the B+Tree and Nodes
 */

#include <iostream>
#include "Node.h"
#include "BpTree.h"

int main(){
	std::cout <<"Driver program\n";
	void* testNode = new LeafNode(3);
	std::cout <<"Made node\n";
	for(int i = 1; i < 20; i++){
		std::cout << "Inserting " << i <<"\n";
		((Node*)testNode)->insert(i, "");
	
	}
	((LeafNode*)testNode)->printNode();
	//testNode.printNode();
	return 0;
}