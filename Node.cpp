/*
 *Node.cpp
 */

#include "Node.h"
#include <string>
#include <iostream>

Node::Node(int n){
	nodeSize = n;
	parent = nullptr;
	rightSibling = nullptr;
	leftSibling = nullptr;
}

Node::Node(Node& other){
	nodeSize = other.nodeSize;
	parent = other.parent;
	rightSibling = other.rightSibling;
	leftSibling = other.leftSibling;
}

Node::~Node(){
	delete parent;
	delete rightSibling;
	delete leftSibling;
}

bool Node::insert(int key, std::string value){
	return true;
}

//-----------------------------------
//InnerNode implementation
//-----------------------------------
InnerNode::InnerNode(int n) : Node(n){
	extra = nullptr;
}

bool InnerNode::insert(int key, std::string value){
	return true;
}

/*
 *returns true if the Node is full
 *a Node can only hold nodeSize keys and nodeSize+1 pointers
 *If the number of keys equals the nodeSize, the node is considered to be full
 *A full node will need to be split before new keys can be added to it
 */
bool InnerNode::isFull() const{
	return (int)keyPointerIndex.size() == nodeSize;
}

//-----------------------------------
//LeafNode implementation
//-----------------------------------
LeafNode::LeafNode(int n) : Node(n){

}

bool LeafNode::insert(int key, std::string value){
	std::vector< std::pair<int, std::string> >::iterator insertionPoint = keyValueIndex.begin();

	if(keyValueIndex.size() == 0){
		keyValueIndex.push_back(std::pair<int, std::string>(key, value));
		return true;
	}

	while((*insertionPoint).first < key && insertionPoint != keyValueIndex.end()){
		insertionPoint++;
	}

	//check if the key already exists, if so, terminate insertion
	if( (*insertionPoint).first == key){
		return false;
	}

	keyValueIndex.insert(insertionPoint, std::pair<int, std::string>(key, value));

	return true;

}

void LeafNode::printNode() const{

	std::cout << "[";
	if(keyValueIndex.size() > 0){
		std::cout << keyValueIndex.at(0).first;
		for(int i = 1; i < keyValueIndex.size(); i++){
			std::cout << ", " << keyValueIndex.at(i).first;
		}
	}
	std::cout << "] ";
}