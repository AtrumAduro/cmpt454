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
	// Allows LeafNode and InnerNode to have access to protected members of Node
	friend class LeafNode;
	friend class InnerNode;
	friend class BpTree;

	public:
		/*
		 *Constructs an empty node with maximum size n
		 */
		Node(int n);

		Node(Node& other);

		~Node();

		/*
		 *Insertion to general Node. All real implementation is taken care of
		 *in the subclasses InnerNode and LeafNode
		 */
		virtual void* insert(int key, std::string value);

		/*
		 *search in general Node. All real implementation is taken care of
		 *in the subclasses InnerNode and LeafNode
		 */
		virtual std::string find(int key);

		/*
		 *General printNode. All real implementation is taken care of
		 *in the subclasses InnerNode and LeafNode
		 */
		virtual void printNode() const;
		
		/*
		 *General removal. All real implementation is taken care of
		 *in the subclasses InnerNode and LeafNode
		 */
		virtual void remove(int key);
		
		/*
		 *General key lookup. All real implementation is taken care of
		 *in the subclasses InnerNode and LeafNode
		 */
		virtual int getKey() const;

		/*
		 *returns a pointer to the parent of the node
		 */
		virtual void* getParent() const;

		/*
		 *Updates the parent pointer of the node
		 *used when the parent has split and needs to inform its new children of the change
		 */
		virtual void setParent(void* newParent);

		/*
		 *Prints the values of the tree to standard output
		 */
		virtual void printValues();

		/*returns true if there are no keys in the vector*/
		virtual bool isEmpty() const;

		/*deletes all child nodes and values*/
		virtual void fullDeletion();

		virtual void* findLeaf(int key);
		
	protected:
		int nodeSize; //max number of keys in the node
		void* parent; //The parent of the node
		void* rightSibling; //pointer to the next pointer in the same level of the B+tree
		void* leftSibling; //pointer to the previous pointer in the same level of the B+tree

};

class InnerNode : public Node{
	friend class BpTree;
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
		 *Inserts the key, value pair to the B+Tree
		 *Values are stored in leaf nodes, so the InnerNode searches for the correct node
		 *to store the value.
		 *
		 *Returns a pointer to the root of the B+tree
		 */
		void* insert(int key, std::string value);

		/*
		 *returns true if the Node is full
		 *a Node can only hold nodeSize keys and nodeSize+1 pointers
		 *If the number of keys equals the nodeSize, the node is considered to be full
		 *A full node will need to be split before new keys can be added to it
		 */
		bool isFull() const;

		/*
		 *If a child node has too many values inserted, it will split. The new Node created will then need to be
		 *added to its parent.
		 *Inserts the search key and Node pointer to the new child in the keyPointerIndex and returns the root
		 *of the B+tree
		 */
		void* insertFromChild(int key, void* child);

		/*
		 *Searches through the B+tree to retrieve the value corresponding to the specified key
		 *if the key is not found within the tree, returns the empty string ""
		 */
		std::string find(int key);

		/*
		 *Prints the contents of the Node to standard output
		 */
		void printNode() const;

		/*
		 *Removes the key and its corresponding value from the B+Tree
		 *If this causes a Node or Nodes to be less than half full, keys and reference pointers may
		 *need to be rearranged to maintain proper tree structure
		 */
		void remove(int key);

		/*
		 *updates the keys to match a modified child node
		 */
		void updateChildKey(int old, int newKey);

		/*
		 *Removes the references to the deleted child Node from the InnerNode
		 */
		void removeLeftChild(void* deadChild);

		/*Removes the reference to the deleted child Node from the InnerNOde
		*/
		void removeRightChild(void* deadChild);

		/*
		 *Returns the first key of the Node for indexing
		 */
		int getKey() const;

		/*
		 *returns a pointer to the parent of the node
		 */
		void* getParent() const;

		/*
		 *Updates the parent pointer of the node
		 *used when the parent has split and needs to inform its new children of the change
		 */
		virtual void setParent(void* newParent);

		/*
		 *Prints the values of the tree to standard output
		 */
		void printValues();

		bool isEmpty() const;

		virtual void fullDeletion();

		
	protected:
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
		 *Returns a pointer to the leafNode that either contains the specified key, or would hold
		 *the key after it was inserted to the Tree
		 */
		void* findLeaf(int key);

		/*
		 *Helper function for removal
		 *If a node becomes less than half full, it may try borrowing from its
		 *sibling to maintain the correct structure of the tree
		 */
		void borrowLeft();

		/*
		 *Helper function for removal
		 *If a node becomes less than half full, it may try borrowing from its
		 *sibling to maintain the correct structure of the tree
		 */
		void borrowRight();

		/*
		 *If we cannot borrow from siblings, need to merge the siblings
		 *together
		 */
		void coaleseLeft();

		void coaleseRight();

		/*
		 *Called when borrowing key from right sibling
		 *after the key, pointer has been copied, need to shift everything
		 *down
		 */
		void shiftPointersLeft();




};

class LeafNode : public Node{
	friend class BpTree;
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

		/*
		 *Returns the string value corresonding with key
		 *If key is not in the tree, returns the empty string ""
		 */
		std::string find(int key);

		/*
		 *Removes the key from the leaf Node. If this would cause the node to be less than half full
		 *will rearrange keys and values from sibling nodes to maintain structure of the tree
		 */
		void remove(int key);

		/*
		 *Returns the first key of the Node for indexing
		 */
		int getKey() const;

		/*
		 *returns a pointer to the parent of the node
		 */
		void* getParent() const;

		/*
		 *Updates the parent pointer of the node
		 *used when the parent has split and needs to inform its new children of the change
		 */
		void setParent(void* newParent);

		/*
		 *Prints the values of the tree to standard output
		 */
		void printValues();

		//returns true if the node contains the key, false otherwise
		bool contains(int key);

		bool isEmpty() const;

		void fullDeletion();

		void* findLeaf(int key);

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

		/*
		 *Helper function for removal
		 *If a node becomes less than half full, it may try borrowing from its
		 *sibling to maintain the correct structure of the tree
		 */
		void borrowLeft(int oldKey);

		/*
		 *Helper function for removal
		 *If a node becomes less than half full, it may try borrowing from its
		 *sibling to maintain the correct structure of the tree
		 */
		void borrowRight();

		/*
		 *If we cannot borrow from siblings, need to merge the siblings
		 *together
		 */
		void* coaleseLeft();

		void* coaleseRight();
};
#endif