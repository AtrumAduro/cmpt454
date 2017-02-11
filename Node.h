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

		/*
		 *Inserts the specified key, string pair to the tree
		 */
		virtual void* insert(int key, std::string value);

		/*
		 *Finds the string value corresponding to the specified key
		 *If the key does not exist, return empty string ""
		 */
		virtual std::string find(int key);

		virtual void printNode();

	protected:
		int nodeSize; //max number of keys in the node
		void* parent; //The parent of the node
		void* rightSibling; //pointer to the next pointer in the same level of the B+tree
		void* leftSibling; //pointer to the previous pointer in the same level of the B+tree

};

class InnerNode : public Node{
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
		void* insert(int key, std::string value);

		/*
		 *returns true if the Node is full
		 *a Node can only hold nodeSize keys and nodeSize+1 pointers
		 *If the number of keys equals the nodeSize, the node is considered to be full
		 *A full node will need to be split before new keys can be added to it
		 */
		bool isFull() const;

		/*put stuff here
		 *
		 */
		void* insertFromChild(int key, void* child);


		std::string find(int key);

		void printNode(void);
		
	private:
		//list of integer keys and their corresponding Node pointers to children within the B+tree
		//extra points to the Node with smallest key values
		//for all other keys, serach until searchkey < indexKey, then follow previous index's pointer
		std::vector <std::pair <int, void*> > keyPointerIndex; 
		void* extra;

		/*
		 *Splits the Node into two 
		 *Nodes can only contain maximum nodeSize number of keys. If an insertion
		 *would cause this to be exceeded, the Node must be split
		 *ceiling of (n+1)/2 keys will remain in the original Node, rest will be in new NOde
		 *After splitting, reference pointer will be inserted in parent
		 *If there is no parent (ie we are splitting the root) create a new root Node and return
		 *pointer to the parent
		 */
		void* split();

		/*
		 *Locates the leaf that would contain the specified key
		 */
		void* findLeaf(int key);


};

class LeafNode : public Node{
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
		void* insert(int key, std::string value);

		/*
		 *Prints the Node's keys to the console to check structure of the tree
		 *If the node contains keys 5, 8, 11, will appear as [5, 8, 11]
		 */
		void printNode() const;

		std::string find(int key);



	private:
		//list of integer keys and their corresponding string values
		std::vector <std::pair <int, std::string> > keyValueIndex;

		/*
		 *Splits the Node into two 
		 *Nodes can only contain maximum nodeSize number of keys. If an insertion
		 *would cause this to be exceeded, the Node must be split
		 *ceiling of (n+1)/2 keys will remain in the original Node, rest will be in new NOde
		 *After splitting, reference pointer will be inserted in parent
		 *If there is no parent (ie we are splitting the root) create a new root Node and return
		 *pointer to the parent
		 */
		void* split();
};
#endif