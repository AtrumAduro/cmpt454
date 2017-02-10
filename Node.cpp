/*
 *Node.cpp
 */

#include "Node.h"
#include <string>

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