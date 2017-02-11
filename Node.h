/*
 *Node.h
 *Header file for a node of a B+Tree. Nodes are split into inner nodes which contain pointers
 *to other nodes in the tree or leaf nodes, which contain string values
 *
 *Authors: Dave Gill, Jackie Lang
 */

#ifndef NODE_H
#define NODE_H

#include <vector> 
#include <utility> //std::pair
#include <string>
class Node{
	public:
		/*
		 *Constructs an empty node with maximum size n
		 */
		Node(int n);

		Node(Node& other);

		~Node();

		bool insert(int key, std::string value);

	protected:
		int nodeSize; //max number of keys in the node
		void* parent; //The parent of the node
		void* rightSibling; //pointer to the next pointer in the same level of the B+tree
		void* leftSibling; //pointer to the previous pointer in the same level of the B+tree

};

class InnerNode : Node{
	public:
		/*
		 *Default constructor. Constructs of node with a max number of keys n
		 */
		InnerNode(int n);

		/*
		 *Default destructor
		 */
		~InnerNode();

		/*
		 *Inserts the string value to the node, referenced by search key
		 *Duplicates are forbidden and so if the key already exists in
		 *the tree, insert will return false to specify that the insertion failed
		 *returns true if the insertion succeeds
		 */
		bool insert(int key, std::string value);

		/*
		 *returns true if the Node is full
		 *a Node can only hold nodeSize keys and nodeSize+1 pointers
		 *If the number of keys equals the nodeSize, the node is considered to be full
		 *A full node will need to be split before new keys can be added to it
		 */
		bool isFull() const;

	private:
		//list of integer keys and their corresponding Node pointers to children within the B+tree
		//When searching through the tree, look for the largest index i such that index[i] < key <= index[i+1]
		//if the search key is larger than the last key in the vector, follow the extra pointer to the correct node
		std::vector <std::pair <int, void*> > keyPointerIndex; 
		void* extra;

};

class LeafNode : Node{
	public:
		/*
		 *Default constructor. Constructs a leaf node with a max number of keys n
		 */
		LeafNode(int n);

		/*
		 *Default destructor
		 */
		//~LeafNode();

		/*
		 *Inserts the key, value pair into the leaf node
		 *Duplicates are not allowed in the tree. If the new key already exists, insertion will fail
		 *and will return false
		 *If insertion is successful, will return true
		 */
		bool insert(int key, std::string value);

		/*
		 *Prints the Node's keys to the console to check structure of the tree
		 *If the node contains keys 5, 8, 11, will appear as [5, 8, 11]
		 */
		void printNode() const;

	private:
		//list of integer keys and their corresponding string values
		std::vector <std::pair <int, std::string> > keyValueIndex;
};
#endif