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
	for(int i = 1; i < 10; i++){
		if(InnerNode* node = static_cast<InnerNode*>(testNode))
		{
			((InnerNode*)testNode)->insert(i, "");		
		}
		else{
			testNode = ((LeafNode*)testNode)->insert(i, "") ;
		}
	
	}
	((LeafNode*)testNode)->printNode();
	//testNode.printNode();
	return 0;
}