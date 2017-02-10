/*
 *BpTree.cp
 */

#include "BpTree.h"
#include "Node.h"
#include <string>
#include <iostream>

BpTree::BpTree(int n){
	nodeSize = n;
	root = nullptr;
}

BpTree::BpTree(BpTree& other){
	nodeSize = other.nodeSize;
	root = other.root; //temporary just to compile. Needs to be made proper
}

BpTree::~BpTree(){
	delete root; //temporary just to compile. Needs to be made proper
}

bool BpTree::insert(int key, std::string value){
	return true;
}

bool BpTree::remove(int key){
	return true;
}

std::string BpTree::find(int key) const{
	return "";
}

void BpTree::printKeys() const{
	std::cout << "printKeys\n";
}

void BpTree::printValues() const{
	std::cout << "printValues\n";
}