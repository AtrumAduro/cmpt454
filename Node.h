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

		Node(int n);

		Node(Node& other);

		~Node();

		bool insert(int key, std::string value);

	private:
		int nodeSize; //max number of keys in the node
		Node* parent; //The parent of the node
		Node* rightSibling; //pointer to the next pointer in the same level of the B+tree
		Node* leftSibling; //pointer to the previous pointer in the same level of the B+tree

};

// class InnerNode : Node{
// 	public:
// 		/*
// 		 *Default constructor. Constructs of node with a max number of keys n
// 		 */
// 		InnerNode(int n);

// 		/*
// 		 *Default destructor
// 		 */
// 		~InnerNode();

// 		bool insert(int key, std::string value);

// 	private:
// 		//list of integer keys and their corresponding Node pointers to children within the B+tree
// 		//When searching through the tree, look for the largest index i such that index[i] < key <= index[i+1]
// 		//if the search key is larger than the last key in the vector, follow the extra pointer to the correct node
// 		std::vector <pair <int, Node*> > keyPointerIndex; 
// 		Node* extra;

// };

// class LeafNode : Node{
// 	public:
// 		/*
// 		 *Default constructor. Constructs a leaf node with a max number of keys n
// 		 */
// 		LeafNode(int n);

// 		/*
// 		 *Default destructor
// 		 */
// 		~LeafNode();

// 		bool insert(int key, std::string value);

// 	private:
// 		//list of integer keys and their corresponding string values
// 		std::vector <pair <int, std::string> > keyValueIndex;
// };
#endif