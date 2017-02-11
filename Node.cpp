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

void* Node::insert(int key, std::string value){
 	return nullptr;
}

std::string Node::find(int key){
	return "";
}

//-----------------------------------
//InnerNode implementation
//-----------------------------------
InnerNode::InnerNode(int n) : Node(n){
	extra = nullptr;
}

void* InnerNode::insert(int key, std::string value){
	int i;
	for(i = 0; i < keyPointerIndex.size(); i++){
		if(key < keyPointerIndex.at(i).first){
			continue;
		}
		else{
			break;
		}
	}

	if(i == 0){
		return ((Node*)extra)->insert(key, value);
	}
	
	void* nextNode = keyPointerIndex.at(i-1).second;
	return ((Node*)nextNode)->insert(key, value);
}

void* InnerNode::findLeaf(int key){
	int i;
	for(i = 0; i < keyPointerIndex.size(); i++){
		if(key < keyPointerIndex.at(i).first){
			continue;
		}
		else{
			break;
		}
	}

	if(i == 0){
		if(InnerNode* node = static_cast<InnerNode*> (extra)){ //extra is another InnerNode
			((InnerNode*)extra)->findLeaf(key);
		}
		else{
			return extra;
		}
	}
	else{
		void* nextNode = keyPointerIndex.at(i-1).second;
		if(InnerNode* node = static_cast<InnerNode*>(nextNode)){ //nextNode is another InnerNode
			((InnerNode*)extra)->findLeaf(key);	
		}
		else{
			return nextNode;
		}
	}
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

void* InnerNode::insertFromChild(int key, void* child){
	//newly created root node. First the left-most child is added to extra, 
	//all others will be added to the index vector
	if(extra == nullptr){
		extra = child;
		return this;
	}

	auto insertionPoint = keyPointerIndex.begin();

	if(keyPointerIndex.empty()){
		keyPointerIndex.push_back(std::pair<int, void*>(key, child));
		return this;
	}

	while(insertionPoint->first < key && insertionPoint != keyPointerIndex.end()){
		insertionPoint++;
	}

	//fail if inserting duplicate key
	if( insertionPoint->first == key){
		return this;
	}

	keyPointerIndex.insert(insertionPoint, std::pair<int, void*>(key, child));
	//check if node has become over-full
	if(keyPointerIndex.size() > nodeSize){
		return split();
	}
	if(parent == nullptr){
		return this;
	}
	return parent;
}


void* InnerNode::split(){
	void* temp = rightSibling;
	rightSibling = new InnerNode(nodeSize);

	//set pointers in new Node
	((InnerNode *)rightSibling)->leftSibling = this;
	((InnerNode *)rightSibling)->rightSibling = temp;
	((InnerNode *)rightSibling)->parent = parent;

	//Move last (n+1)/2 keys to the new node
	int key;
	void* child;
	std::cout << "Created new node, moving values over in InnerNode\n";
	for(int i = (nodeSize +2)/2; i  < keyPointerIndex.size(); i++){
		key = keyPointerIndex.at(i).first; //extract key
		child = keyPointerIndex.at(i).second; //extract sting value
		((InnerNode *)rightSibling)->insertFromChild(key, child);
	}
	for(int i = (nodeSize + 2)/2; i < nodeSize +1; i++){
		keyPointerIndex.pop_back(); //remove the entries we just copied over
	}
	std::cout << "Finished moving values over in InnerNode\n";
	//key, value pair of new node to insert to parent 
	std::pair<int, void*> p = ((InnerNode *)rightSibling)->keyPointerIndex.at(0);

	//Check if we split the root
	if(parent == nullptr){
		parent = new InnerNode(nodeSize);
		((InnerNode *)rightSibling)->parent = parent; //fix rightSibling's parent		
		//insert original Node pointer to parent
		((InnerNode *)parent)->insertFromChild(keyPointerIndex.at(0).first, this); 
		//insert new node pointer to parent
		((InnerNode *)parent)->insertFromChild( p.first, rightSibling);
		return parent;
	}

	//didn't create new parent, need to add new NOde to parent index
	((InnerNode *)parent)->insertFromChild( p.first, rightSibling);
	return parent;
}

std::string InnerNode::find(int key){
	return "";
}
//-----------------------------------
//LeafNode implementation
//-----------------------------------
LeafNode::LeafNode(int n) : Node(n){

}

void* LeafNode::insert(int key, std::string value){
	std::vector< std::pair<int, std::string> >::iterator insertionPoint = keyValueIndex.begin();

	if(keyValueIndex.size() == 0){
		keyValueIndex.push_back(std::pair<int, std::string>(key, value));
		return this;
	}

	while((*insertionPoint).first < key && insertionPoint != keyValueIndex.end()){
		insertionPoint++;
	}

	//check if the key already exists, if so, terminate insertion
	if( (*insertionPoint).first == key){
		return this;
	}

	//Need to check if split is needed after insertion

	keyValueIndex.insert(insertionPoint, std::pair<int, std::string>(key, value));

	if(keyValueIndex.size() > nodeSize){
		std::cout<<"preparing to split node" << std::endl;
		return split();
	}

	if(parent == nullptr){
		return this;
	}
	return parent;

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

void* LeafNode::split(){
	void* temp = rightSibling;
	rightSibling = new LeafNode(nodeSize);

	//set pointers in new Node
	((LeafNode *)rightSibling)->leftSibling = this;
	((LeafNode *)rightSibling)->rightSibling = temp;
	((LeafNode *)rightSibling)->parent = parent;

	//Move last (n+1)/2 keys to the new node
	auto iterator = keyValueIndex.end();
	iterator--;
	int key;
	std::string value;
	std::cout << "Created new node, moving values over\n";
	for(int i = 0; i < (nodeSize +1)/2; i++){
		key = iterator->first; //extract key
		value = iterator->second; //extract sting value
		iterator--; //move backwards through vector
		keyValueIndex.pop_back(); //delete old key,string pair
		((LeafNode *)rightSibling)->insert(key, value);
	}
	std::cout << "Finished moving values over\n";
	//key, value pair of new node to insert to parent 
	std::pair<int, std::string> p = ((LeafNode *)rightSibling)->keyValueIndex.at(0);

	//Check if we split the root
	if(parent == nullptr){
		parent = new InnerNode(nodeSize);
		((LeafNode *)rightSibling)->parent = parent; //fix rightSibling's parent		
		//insert original Node pointer to parent
		((InnerNode *)parent)->insertFromChild(keyValueIndex.at(0).first, this); 
		//insert new node pointer to parent
		((InnerNode *)parent)->insertFromChild( p.first, rightSibling);
		return parent;
	}

	//didn't create new parent, need to add new NOde to parent index
	((InnerNode *)parent)->insertFromChild( p.first, rightSibling);
	return parent;

}

std::string LeafNode::find(int key){
	for(int i = 0; i < keyValueIndex.size() && key <= keyValueIndex.at(i).first; i++){
		if(keyValueIndex.at(i).first == key){
			return keyValueIndex.at(i).second;
		}
	}
	return "";
}