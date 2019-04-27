#include <limits>
#include <iostream>
#include <list>
#include <assert.h>
#include <algorithm>
#include <functional>
#include <memory>
#include <fstream>
#include <chrono>

#include "structures.h"
using namespace std;
//main nodes, and parts of lists

class DoesNotContain : std::exception {
	string err;
public:
	explicit DoesNotContain(string err) {
		this->err = err;
	}
	const char* what() const noexcept override {
		return err.c_str();
	}
};
class DuplicateKey : std::exception {
	string err;
public:
	explicit DuplicateKey(string err) {
		this->err = err;
	}
	const char* what() const noexcept override {
		return err.c_str();
	}
};

/**Links */
template <class K, class V> class Pair {
public:
	K key;
	V val;
	Pair(K key, V val) {
		this->key = key;
		this->val = val;
	}
};
/**A single-directional lined node (template)
 * Can be used in CLL*/
template<class T> struct LinkedNode {
	LinkedNode<T> *next = nullptr;
	T val;
	LinkedNode<T>(T val) {
		this->val = val;
	}
	LinkedNode<T>(T val, LinkedNode* next) {
		this->val = val;
		this->next = next;
	}
	~LinkedNode() {
//		delete val;
		cerr<<"HOW TO REMOVE LINKED NODE AHHHHHH";
	}
};
/**A linked node is a part of a linked list
 * @var prev The previous linked node in the chain
 * @var next The next linked node in the chain
 * @var val The value of the link
 * */
/**A linked list is a group of linked nodes.
 * It is a template, so can be any object*/
template<class T> class LinkedList {
public:
	LinkedNode<T> *root;

	/**Prints the list forwards then backwards, with commentary*/
	void print() {
		auto *curNode = root;
		cout << "\n\n-----------------------------------\nPrinting linked list from \n";

		while (curNode) {
//		cout<<"The firstNode's value is "<<curNode->val<<'\n';
			cout << curNode <<" -> "<< curNode->val << "\n";
			curNode = curNode->next;
		}
		cout << flush << "-----------------------------------\n\n";
	}

	/**inserts a linked node at end*/
	void putEnd(T val) {
		if (root == nullptr) {
			root = new LinkedNode<T>(val);
			return;
		}
		auto* end = root;
		while (end->next != nullptr) {
			end = end->next;
		}
		end->next = new LinkedNode<T>(val);
	}
	void put(T val) {
		if (root==nullptr) {
			root = new LinkedNode<T>(val);
			return;
		}
		LinkedNode<T>* movedRoot = root;
		root = new LinkedNode<T>(val);
		root->next = movedRoot;
	}

	T& operator[](size_t index) {
		auto* node = root;
		for(;index>0;index--) {
			node = node->next;
		}
		return node->val;
	}
	const T& operator[](size_t index) const {
		auto* node = root;
		for(;index>0;index--) {
			node = node->next;
		}
		return node->val;
	}

	/**removes item from linked list, and changes adjacent elements so it's "skipped over"*/
	//TODO needs to be able to remove root node
	void remove(T val) {
		auto* nodeBeforeRemoval = root;

		if (root->val == val) {
			//remove root node
			root = root->next;
			return;
		}
		//find node to remove
		while (nodeBeforeRemoval != nullptr && nodeBeforeRemoval->next->val != val) {
			nodeBeforeRemoval = nodeBeforeRemoval->next;
		}
		if (nodeBeforeRemoval == nullptr) throw DoesNotContain("The linked list doesnt have that value");

		//remove node
		//TODO delete
		nodeBeforeRemoval->next = nodeBeforeRemoval->next->next;

	}
	/**Remove the node after the node specified. Useful if external code is used to iterate and remove LinkedList objects
	 * @param node - The pointer to the node desired. IF NODE IS NULLPTR, REMOVES ROOT.
	 * */
	void removeNodeAfter(LinkedNode<T>* node) {
		if (node == nullptr) {
			//delete the root
//			auto* next = root->next;
//			delete root;
			//cout<<"REMOVING"<<root->val.first;
			root = root->next;
//			cout<<"REMOVING"<<root->val.first;
		} else {
			//remove node that isn't the first node
			//cout<<"REMOVING"<<node->next->val.first;
			node->next = node->next->next;
			//TODO learn how to delete
//			delete (node->next->val);
		}
	}
};

template<class T> class DoublyLinkedNode {
public:
	DoublyLinkedNode *prev = nullptr;
	DoublyLinkedNode *next = nullptr;
	T val;
	explicit DoublyLinkedNode(DoublyLinkedNode *prev, DoublyLinkedNode *next, T val) {
		this->prev = prev;
		this->next = next;
		this->val = val;
	}
};
template<class T> std::ostream& operator<<(std::ostream &strm, const DoublyLinkedNode<T> &o) {
	return strm << "LinkedNode(val "<<o.val<<", adj "<<o.prev<<" | "<<o.next<<")";
}
/**A node in a binary tree. Everything less is left, everything more is right.*/
template <class T> struct BinaryTreeNode {
	BinaryTreeNode* left;
	BinaryTreeNode* right;
	T val;
	BinaryTreeNode(T val) {
		this->val = val;
	}
};
template<class T> std::ostream& operator<<(std::ostream &strm, const BinaryTreeNode<T> &o) {
	return strm << "(val "<<o.val<<", adj "<<o.left<<" | "<<o.right<<")";
}

template <class K,class V> struct BinaryTreeMapNode {
	BinaryTreeMapNode* left;
	BinaryTreeMapNode* right;
	K key;
	V val;
	BinaryTreeMapNode(K key, V val) {
		this->key = key;
		this->val = val;
	}
};

//main lists made of nodes

/**A linked list is a group of linked nodes.
 * It is a template, so can be any object*/
template<class T> class DoublyLinkedList {
public:
	DoublyLinkedNode<T> *first;
	DoublyLinkedNode<T> *last = nullptr;

	explicit DoublyLinkedList<T>(DoublyLinkedNode<T> *firstN) {
		first = firstN;
		first->next = last;
	}

	/**Prints the list forwards then backwards, with commentary*/
	void printArr() {
		auto *curNode = first;
		cout << "\n\n-----------------------------------\nPrinting linked list from " << first << " to " << last
		     << "\n";

		while (curNode) {
//		cout<<"The firstNode's value is "<<curNode->val<<'\n';
			cout << '\"' << curNode->val << "\" at (F) with order " << curNode->prev << " (" << curNode << ") "
			     << curNode->next << "\n";
			curNode = curNode->next;
		}
		cout << flush << "Last Node: " << last
		     << "\n-----------------------------------\nHere is the entire linked list BACKWARDS:\n";
		curNode = last;
		while (curNode) {
//		cout<<"The firstNode's value is "<<curNode->val<<'\n';
			cout << '\"' << curNode->val << "\" at (B) with order " << curNode->prev << " (" << curNode << ") "
			     << curNode->next << "\n";
			curNode = curNode->prev;
		}
		cout << flush << "-----------------------------------\n\n";
	}

	/**inserts a linked node after the specified node*/
	DoublyLinkedNode<T> *insertNodeAfter(DoublyLinkedNode<T> &backNode, T val) {
//	cout<<"BACKNODE INFO"<<backNode.val<< " at with order "<<backNode.prev<<" ("<<&backNode<<") "<<backNode.next<<"\n";
//		cout<<"backnode "<<&backNode<<'\n';
		auto *node = new DoublyLinkedNode<T>(&backNode, backNode.next, val);
		//if adding on to end of stack
		if (backNode.next == nullptr) {
			//make a new node, where before it is backNode and after it is null
			//backNode's next node is this
			backNode.next = node;
			//set list end node
			last = node;
		} else {
			//make a new node, where before it is backNode and after it is the next node
			//backNode's next node is this
			backNode.next = node;
			//set the next node to link to the new node
			node->next->prev = node;
		}
		return node;
		//set the previous node to link to the new node
	}

	/**inserts a linked node before the specified node*/
	DoublyLinkedNode<T> *insertNodeBefore(DoublyLinkedNode<T> &nextNode, T val) {
		//cout<<"BACKNODE INFO"<<backNode.val<< " at with order "<<backNode.prev<<" ("<<&backNode<<") "<<backNode.next<<"\n";

		//make a new node, where before it is null and after it is the next node, duh
		auto *node = new DoublyLinkedNode<T>(nextNode.prev, &nextNode, val);
		//if adding on before the start of stack
		if (nextNode.prev == nullptr) {
			//set list end node
			first = node;
		} else {
			//set the previous node to link here
			node->prev->next = node;
		}
		//the next node's previous node is this
		nextNode.prev = node;
		//return the made node
		return node;
	}

	/**removes item from linked list, and changes adjacent elements so it's "skipped over"*/
	void removeNode(DoublyLinkedNode<T> &node) {
		//cout<<"Removing "<<&node<<'\n';

		//if at end of list
		if (node.next == nullptr) {
			last = node.prev;
		} else {
			//the next node's previous is this node's previous
			node.next->prev = node.prev;
		}

		//if at start of list
		if (node.prev == nullptr) {
			first = node.next;
		} else {
			//the previous node's next is this node's next
			node.prev->next = node.next;
		}
		delete &node;
	}
};
/**A circular linked list
 * */
template<class T> class CircularLinkedList {
private:
	/**the nodePtr is any node in the list. it is NOT the start
	 * To iterate, you keep going till you have the original starting address
	 * To grab the next node, you move it forward one.
	 * */
	LinkedNode<T> *nodePtr = nullptr;
public:
	/**The default constructor*/
	explicit CircularLinkedList<T>() = default;

	/**get current selection*/
	T getCur() {
		return nodePtr->val;
	}

	/**Gets the next node (and assigns next node to nodePtr)*/
	LinkedNode<T> *getNext() {
		if (nodePtr == nullptr) return nullptr;
		return nodePtr = nodePtr->next;
	}

	/**Prints the list forwards then backwards, with commentary*/
	void printArr() {
		cout << "\n\n-----------------------------------\nPrinting linked list from " << nodePtr << "\n";
		if (nodePtr == nullptr) {
			cout << "This is an empty CLL\n";
		} else {
			auto endNode = nodePtr;
			do {
				cout << (nodePtr->val) << " at " << nodePtr << " pointing to " << nodePtr->next << "\n";
			} while (getNext() != endNode);
		}
		cout << flush << "-----------------------------------\n\n";
	}

	/**Inserts a linked node after the specified node.
	 * @param val The value of the new node
	 * @return A pointer to the new node. This is equal to the nodePtr of the CLL
	*/
	LinkedNode<T> *insertNode(T val) {
		if (nodePtr == nullptr) {
			//main if nodePtr is nullptr, make the initial newNode
			nodePtr = new LinkedNode<T>(val);
			nodePtr->next = nodePtr;
		} else {
			//main if there's more than one node, neatly make a new node
			//insert it after the node pointer. Then move the node pointer forward.
			nodePtr = nodePtr->next = new LinkedNode<T>(val, nodePtr->next);
		}
		return nodePtr;
	}

	/**Removes selected node, thus skipping it in looping*/
	void removeNextNode() {
		//return if there are no nodes
		if (nodePtr == nullptr) return;

		if (nodePtr->next == nodePtr) {
			delete nodePtr;
			nodePtr = nullptr;
		} else {
			//save the node you need to delete
			auto *toDelete = nodePtr->next;
			//delete the node (the next node is replaced by the node two ahead)
			nodePtr->next = nodePtr->next->next;
			delete toDelete;
		}
	}

	/**Removes item from linked list, and changes adjacent elements so it's "skipped over"
	 * @param node - node to remove
	 * @return True if found and deleted, false if not found*/
	bool removeNode(LinkedNode<T> *node) {
		if (setNextNode(node)) {
			removeNextNode();
			return true;
		} else {
			return false;
		}
	}

	/**Finds a node in the lists, sets found node as nodePtr->next, and returns if it was found
	 * @param node - the node you want to find
	 * @return True if found, false if not found (not in list or deleted)*/
	bool setNextNode(LinkedNode<T> *node) {
		//if empty, return false
		if (node == nullptr) {
			return false;
		}
		//used so it doesn't infinitely loop
		auto cycleStart = nodePtr;
		//while the curNode is not the desired node AND a full cycle has not been done
		do {
			//if the desired node is the node pointer, return true
			if (node == nodePtr->next) return true;
		} while ((nodePtr = nodePtr->next) != cycleStart);
		//the node was not found
		return false;
	}
};

/**A LIFO stack (like a *stack* of plates)*/
template <class T> class StackLIFO {
	LinkedNode<T> *topNode = nullptr;
public:
	StackLIFO<T>() = default;
	//Pushes something to the end
	void push(T val) {
		topNode = new LinkedNode<T>(val, topNode);
	}
	T peek() {
		//cant peek empty list
		if (topNode == nullptr) throw DoesNotContain("The Stack is Empty");
		//return top value
		return topNode->val;
	}
	T pop() {
		//can't pop empty list
		if (topNode == nullptr) throw DoesNotContain("The Stack is Empty");
		//get return value
		T ret = topNode->val;
		//delete top value
		topNode = topNode->next;
		return ret;
	}
	bool isEmpty() {
		return topNode == nullptr;
	}
};

template <class T> class QueueFIFO {
	LinkedNode<T>* head = nullptr;
	LinkedNode<T>* foot = nullptr;
public:
	QueueFIFO() = default;
	void put(T val) {
		//move head to the left, and have it point to the next item
		LinkedNode<T>* oldFoot = foot;
		foot = new LinkedNode<T>(val);
		if (oldFoot) {
			oldFoot->next = foot;
		}
		//if the list is empty, set the head equal to the foot
		if (head == nullptr) head = foot;
	}
	T pop() {
		if (head==nullptr) throw DoesNotContain("pop() called on empty QueueFIFO");
		T ret = head->val;
		head = head->next;
		return ret;
	}
	T peek() {
		if (head==nullptr) throw DoesNotContain("peek() called on empty QueueFIFO");
		return head->val;
	}
	bool isEmpty() {
		//the head is null (the foot would also be null)
		return head==nullptr;
	}
};

/**Your average binary tree, I guess
 *
 * SORTING?
 *      Iterate it into an array*/
template <class T> class BinaryTree {
private:
	BinaryTreeNode<T> *root = nullptr;

	/**Insert the node into the binary tree
	 * @param val - The value you want to add
	 * @param forkNode - The node you want to fork off of (use other insertNode for public access)
	 * @return Weather or not it was added. Returns false if it already exists.*/
	void insertNode(T val, BinaryTreeNode<T> &forkNode) {
		if (val < forkNode.val) {
			//add on left branch
			if (forkNode.left == nullptr) {
				forkNode.left = new BinaryTreeNode<T>(val);
			} else {
				insertNode(val, *forkNode.left);
			}
		} else if (val > forkNode.val) {
			//add on right branch
			if (forkNode.right == nullptr) {
				forkNode.right = new BinaryTreeNode<T>(val);
			} else {
				insertNode(val, *forkNode.right);
			}
		}
	}

	/**Removes a node from the binary tree. This is the PRIVATE function. For public use remove(T)
	 * @param T val the value you are finding to remove
	 * @param BinaryTreeNode<T> forkNode - The node you are looking from (used recursively, should start at root)*/
	bool removeNode(T val, BinaryTreeNode<T> *&forkNode) {

		//if the node is null, it doesn't exist
		if (forkNode == nullptr) return false;

		//search the tree for the node
		if (val < forkNode->val) {
			//go left
			return removeNode(val, forkNode->left);
		} else if (val > forkNode->val) {
			//go right
			return removeNode(val, forkNode->right);
		} else {
			//now delete forkNode

			//where the tree looks
			BinaryTreeNode<T>* tempPoint = forkNode;

			if (forkNode->left == nullptr) {
				//replace itself (pointer) with its right node
				forkNode = forkNode->right;
			} else if (forkNode->right == nullptr) {
				//replace itself (pointer) with its left node
				forkNode = forkNode->left;
			} else {
				//advanced pointer trick; make right node point to the left

				//get right node
				BinaryTreeNode<T>* rightsLeftestChild = forkNode->right;
				//go down the right node to find the leftest child
				while (rightsLeftestChild->left != nullptr) {
					rightsLeftestChild = rightsLeftestChild->left;
				}
				rightsLeftestChild->left = forkNode->left;

				//set the deleted node to instead point to it's right child
				forkNode = forkNode->right;
			}
			delete tempPoint;

			return true;
		}
	}

	/**Used for fancy printing of tree structure*/
	void indentOut(int indents) {
		while (indents-- > 0) {
			cout << "  ";
		}
	}

	void printTree(int tabs, BinaryTreeNode<T> *node) {
		indentOut(tabs);
		cout<<node->val<<'\n';

		if (node->left != nullptr) {
			indentOut(tabs);cout<<"to left:\n";
			printTree(tabs + 1, node->left);
		}
		if (node->right != nullptr) {
			indentOut(tabs);cout<<"to right:\n";
			printTree(tabs + 1, node->right);
		}
	}

	/**Simple functions showing how pre-order, in-order, and post-order work.*/
	void preOrder(BinaryTreeNode<T> *node) {
		if (node == nullptr) return;
		cout << node->val << '\n';
		preOrder(node->left);
		preOrder(node->right);
	}
	void inOrder(BinaryTreeNode<T> *node) {
		if (node == nullptr) return;
		inOrder(node->left);
		cout << node->val << '\n';
		inOrder(node->right);
	}
	void postOrder(BinaryTreeNode<T> *node) {
		if (node == nullptr) return;
		postOrder(node->left);
		postOrder(node->right);
		cout << node->val << '\n';
	}

public:
	void preOrder() {
		preOrder(root);
	}
	void inOrder() {
		inOrder(root);
	}
	void postOrder() {
		postOrder(root);
	}

	void put(T val) {
		if (root==nullptr) {
			root = new BinaryTreeNode<T>(val);
		} else {
			insertNode(val, *root);
		}
	}
	void print() {
		cout<<"Binary Tree \n-----------------------\n";
		printTree(0, root);
		cout<<"-----------------------\nEnd of Tree\n";
	}
	bool containsKey(T val) {
		BinaryTreeNode<T>* node = root;
		while (node) {
			if (node->val == val) {
				return true;
			} else if (val < node->val) {
				node = node->left;
			} else {
				node = node->right;
			}
		}
		return false;
	}

	void remove(T val) {
		removeNode(val, root);
	}
};
template <class K, class V> class BinaryTreeMap {
private:
	BinaryTreeMapNode<K,V> *root = nullptr;
	/**Insert the node into the binary tree
	 * @param val - The value you want to add
	 * @param forkNode - The node you want to fork off of (use other insertNode for public access)
	 * @return Weather or not it was added. Returns false if it already exists.*/
	void put(K key,V val,BinaryTreeMapNode<K,V> &forkNode) {
		if (key < forkNode.key) {
			//add on left branch
			if (forkNode.left == nullptr) {
				forkNode.left = new BinaryTreeMapNode<K,V>(key,val);
			} else {
				put(key, val, *forkNode.left);
			}
		} else if (key > forkNode.key) {
			//add on right branch
			if (forkNode.right == nullptr) {
				forkNode.right = new BinaryTreeMapNode<K,V>(key,val);
			} else {
				put(key, val, *forkNode.right);
			}
		}
	}

	/**Removes a node from the binary tree. This is the PRIVATE function. For public use remove(T)
	 * @param T val the value you are finding to remove
	 * @param BinaryTreeMapNode<T> forkNode - The node you are looking from (used recursively, should start at root)*/
	bool removeKey(K key, BinaryTreeMapNode<K,V> *&forkNode) {

		//if the node is null, it doesn't exist
		if (forkNode == nullptr) return false;

		//search the tree for the node
		if (key < forkNode->key) {
			//go left
			return removeKey(key, forkNode->left);
		} else if (key > forkNode->key) {
			//go right
			return removeKey(key, forkNode->right);
		} else {
			//now delete forkNode

			//where the tree looks
			BinaryTreeMapNode<K,V>* tempPoint = forkNode;

			if (forkNode->left == nullptr) {
				//replace itself (pointer) with its right node
				forkNode = forkNode->right;
			} else if (forkNode->right == nullptr) {
				//replace itself (pointer) with its left node
				forkNode = forkNode->left;
			} else {
				//advanced pointer trick; make right node point to the left

				//get right node
				BinaryTreeMapNode<K,V>* rightsLeftestChild = forkNode->right;
				//go down the right node to find the leftest child
				while (rightsLeftestChild->left != nullptr) {
					rightsLeftestChild = rightsLeftestChild->left;
				}
				rightsLeftestChild->left = forkNode->left;

				//set the deleted node to instead point to it's right child
				forkNode = forkNode->right;
			}
			delete tempPoint;

			return true;
		}
	}
	void removeSubTree(BinaryTreeMapNode<K,V> *node) {
		if (node->left != nullptr) removeSubTree(node->left);
		if (node->right != nullptr) removeSubTree(node->right);
		delete node;
	}
	/**Used for fancy printing of tree structure*/
	void indentOut(int indents) {
		while (indents-- > 0) {
			cout << "  ";
		}
	}

	void printTree(int tabs, BinaryTreeMapNode<K,V> *node) {
		indentOut(tabs);
		cout<<node->val<<'\n';

		if (node->left != nullptr) {
			indentOut(tabs);cout<<"to left:\n";
			printTree(tabs + 1, node->left);
		}
		if (node->right != nullptr) {
			indentOut(tabs);cout<<"to right:\n";
			printTree(tabs + 1, node->right);
		}
	}

	/**Simple functions showing how pre-order, in-order, and post-order work.*/
	void preOrder(BinaryTreeMapNode<K,V> *node) {
		if (node == nullptr) return;
		cout << node->key<<"\t\t: "<<node->val << '\n';
		preOrder(node->left);
		preOrder(node->right);
	}
	void inOrder(BinaryTreeMapNode<K,V> *node) {
		if (node == nullptr) return;
		inOrder(node->left);
		cout << node->key<<"\t\t: "<<node->val << '\n';
		inOrder(node->right);
	}
	void postOrder(BinaryTreeMapNode<K,V> *node) {
		if (node == nullptr) return;
		postOrder(node->left);
		postOrder(node->right);
		cout << node->key<<"\t\t: "<<node->val << '\n';
	}
	long getLength(BinaryTreeMapNode<K,V> *node) {
		if (node == nullptr) return 0;

		//have a variable with the running total (count itself)
		long sum = 1;

		//count things to the sides
		if (node->left != nullptr)  sum += getLength(node->left);
		if (node->right != nullptr)  sum += getLength(node->right);
		return sum;//count itself
	}
public:
	~BinaryTreeMap() {
		removeSubTree(root);
	}
	void preOrder() {
		preOrder(root);
	}
	void inOrder() {
		inOrder(root);
	}
	void postOrder() {
		postOrder(root);
	}

	void put(K key, V val) {
		if (root==nullptr) {
			root = new BinaryTreeMapNode<K,V>(key,val);
		} else {
			put(key, val, *root);
		}
	}
	V* get(K key) {
		auto node = root;
		while (node) {
			if (key == node->key) {
				return &node->val;
			} else if (key < node->key) {
				node = node->left;
			} else {
				node = node->right;
			}
		}
		return nullptr;
	}
	void print() {
		cout<<"Binary Tree \n-----------------------\n";
		printTree(0, root);
		cout<<"-----------------------\nEnd of Tree\n";
	}
	bool containsKey(K key) {
		auto* node = root;
		while (node) {
			if (node->key == key) {
				return true;
			} else if (key < node->key) {
				node = node->left;
			} else {
				node = node->right;
			}
		}
		return false;
	}

	void removeKey(K key) {
		removeKey(key, root);
	}

	void dumpTree(int arr[], int arrLen) {

	}
	long getLength() {
		return getLength(root);
	}
	void sortTree() {
		//TODO have a method that makes it into a "Complete" binary tree
		//main A complete binary tree is a binary tree in which every level, except possibly the last, is completely filled, and all nodes are as far left as possible.
		//TODO make it on your own, with only the book to help

		//main step: get the length
		long length = getLength();
		//main step: make it an array, so you can read the data
		//unique pointers deallocate themselves
		unique_ptr<int[]> ptr(new int[length]);
	}
};

/**An open hash map is where every item is inserted by hashing and then putting into the hash table.
 * If there is already something there, it goes into the next slot (or can iterate empty spots x+like 3*i, x+pow(3,i), x-i) where x is first slot
 *
 *
 * */
template <
        //main like a Binary Tree, used to help you find data
        class Key,
        //main the actual data you are finding
        class T,
        //the size of the array
        //size_t size,
        //The hash of the key
        class Hash = hash<Key>,
        //unsure used to see if two keys are the same
        class KeyEqual = equal_to<Key>
        //unsure the list your are supposed to store things in? main im going to initially use an array
        //todo class Allocator = allocator< pair<const Key, V> >
        		> class OpenHashMap {
	//the actual array/vector holding all data
	std::vector< pair<Key,T> > datastore;
	virtual void shiftIndex(size_t& index) {
		//clock up
		index++;
		//make it not overflow
		index%=size;
	}

	//main current size of vector holding data (NOT CURRENT NUMBER OF ELEMENTS)
	size_t size;

	/**A list of booleans where if datastoreState[i] is true, datastore[i] is populated.
	 * datastoreState.size() == datastore.size()*/
	std::vector<bool> datastoreState;
	//The number of elements inside of datastore (equal to count of "true" booleans in datastoreState)
	size_t datastoreLoad = 0;
	//once the map is loadFactor percent filled, it should resize
	float loadFactor;
	const unsigned long sizeMultiplier = 2;
	//main call whenever (before or after) you are adding elements, this will adjust the threshhold if neccessary
	void holdThreshhold() {
		//cout<<"Checking threshhold. At "<<((float)datastoreLoad/size) <<"/"<<loadFactor<<"\n";
		//if it is over the
		if (((float)datastoreLoad/size >= loadFactor)) {
			//cout<<"Doubling size of OpenHashMap\n";
			//print(true, "BEFORE DOUBLING VVV");
			size *= sizeMultiplier;
			//rehashing is where you, for every item, calculate they key's hash then modulus it into its spot (or if the spot is filled, keep going)
			std::vector< pair<Key,T> > rehash;
			std::vector<bool> rehashState;
			rehash.resize(size);
			rehashState.resize(size);
			for(size_t i=0;i<datastore.size();i++) {
				if (datastoreState[i]) {
					//hash the key
					size_t hash= Hash(datastore[i].first);
					//get the hash's index. main This is the reason you have to rehash, since this modulus would return different places based off of the size
					size_t index = hash % size;
					//have the new table point to the old one
					rehash.at(index) = datastore.at(i);
					rehashState.at(index) = true;
				}
			}
			datastore = rehash;
			datastoreState = rehashState;
			//print(true, "AFTER DOUBLING VVV");

		}
	}
public:
	OpenHashMap(size_t size = 16, float loadFactor = .75) {
		this->size = size;
		this->loadFactor = loadFactor;
		datastore.resize(size);
		datastoreState.resize(size);
		//all spots start out as empty
		for (_Bit_iterator::reference b : datastoreState) {
			b = false;
		}
	}
	void put(Key k, T val) {
		size_t hash= Hash(k);
		size_t index = hash % size;

		//cout<<"Finding spot for "<<hash<<" in index "<<index<<'\n';
		//while that spot is taken (find empty spot)
		while (datastoreState[index]) {
			//cout<<"current point in index "<<index<<" is "<<(datastoreState[index]?"populated":"unpopulated")<<'\n';
			//go to the next spot
			shiftIndex(index);
		}
		//cout<<"putting hash "<<hash<<" in index "<<index<<'\n';
		datastore[index] = pair<Key,T>(k,val);
		datastoreState[index] = true;
		datastoreLoad++;
		//make sure it has space to grow
		holdThreshhold();
	}
	T get(Key k) {
		size_t hash= Hash(k);
		size_t index = hash % size;
		//while there is something there (once there isn't means it doesn't contain it at all)
		while (datastoreState[index]) {
			cout<<"Looking in index "<<index<<'\n';
			if (datastore[index].first == k) {
				return datastore[index].second;
			}
			shiftIndex(index);
		}
		throw DoesNotContain("The HashMap does not contain it");
	}
	void print(bool all = true, string label = "\n") {
		cout<<"-------------------------------\n"
		<<label     <<"\nPrinting datastore\n";
		for(size_t i=0;i<size;i++) {
			if (all || datastoreState[i]) {
				auto p = datastore[i];
				cout<<"Index "<<i<<" Key "<<p.first<<" -> "<<p.second<<'\n';
			}
		}
		cout<<"-------------------------------\n";
	}
};
/**A closed hash map is a HashMap that doesn't change in size. It is an array of linked lists.
 * To find an item, hash the key to get the index, and it is in that linked list.
 * To add an item, hash the key and add it onto that linked list.*/
template <
		//main like a Binary Tree, used to help you find data
		class Key,
		//main the actual data you are finding
		class T,
		//the size of the array
		size_t size,
		//The hash of the key
		class Hash = hash<Key>,
		//unsure used to see if two keys are the same
		class KeyEqual = equal_to<Key>
		//unsure the list your are supposed to store things in? main im going to initially use an array
		//todo class Allocator = allocator< pair<const Key, V> >
> class ClosedHashMap {
	//the actual array/vector holding all data
	std::vector<LinkedList<pair<Key, T> > > datastore;
public:
	ClosedHashMap() {
		datastore.resize(size);
	}

	void put(Key k, T val) {
		size_t hash = Hash(k);
		size_t index = hash % size;

		//cout<<"putting hash "<<hash<<" in index "<<index<<'\n';
		datastore[index].put(pair<Key, T>(k, val));
	}

	T get(Key k) {
		size_t hash = Hash(k);
		size_t index = hash % size;
		LinkedList<pair<Key, T> > list = datastore.at(index);
		//main note code duplicated for get(key) and remove(key) so change that too
		LinkedNode<pair<Key, T> > *node = list.root;
		//while there is something there (once there isn't means it doesn't contain it at all)
		//scroll through the Linked List so you
	    while (node) {
		 	if (node->val.first == k) {
		 		return node->val.second;
		 	}
		    //i don't actually need a reinterpret_cast here, the IDE is just being an ass...
		    node = reinterpret_cast<LinkedNode<pair<Key, T>> *>(node->next);
	    }
		throw DoesNotContain("The HashMap does not contain it");
	}
	void remove(Key k) {
		size_t hash = Hash(k);
		size_t index = hash % size;
		//main note code duplicated for get(key) and remove(key) so change that too
		LinkedNode<pair<Key, T> >* node = datastore.at(index).root;

		//if the root node is to be removed, tell it to remove nullptr
		if (node->val.first == k) {
			cout<<"removing key "<<node->val.first<<" val "<<node->val.second<<'\n';
			datastore.at(index).removeNodeAfter(nullptr);
		} else {
			//while there is something there (once there isn't means it doesn't contain it at all)
			//scroll through the Linked List so you
			while (node->next/* != nullptr*/) {
				if (node->next->val.first == k) {
					cout<<"removing key "<<node->next->val.first<<" val "<<node->next->val.second<<'\n';
					datastore.at(index).removeNodeAfter(node);
					return;
				}
				//i don't actually need a reinterpret_cast here, the IDE is just being an ass...
				node = reinterpret_cast<LinkedNode<pair<Key, T>> *>(node->next);
			}
			throw DoesNotContain("The HashMap does not contain it");
		}
	}
	void print(bool all = true, string label = "\n") {
		cout << "-------------------------------\n"
		     << label << "\nPrinting datastore\n";
		for (size_t i = 0; i < size; i++) {
			cout << "\nLinked List at " << i << '\n';
			LinkedList<pair<Key, T> >* list = &(datastore[i]);

			LinkedNode<pair<Key, T>>* node = list->root;
			while (node) {
				cout << "Key " << node->val.first << " -> " << node->val.second << "\n";
				//i don't actually need a reinterpret_cast here, the IDE is just being an ass...
				node = reinterpret_cast<LinkedNode<pair<Key, T>> *>(node->next);
//				node = nullptr;
			}
		}
		cout << "-------------------------------\n";
	}
};


template <class K, class T> struct SkipNode {
	//todo to avoid duplication, it and all nodes below it should be the same pointer to the same V value
	K* key = nullptr;
	T* val = nullptr;
	SkipNode<K,T>* right = nullptr;
	SkipNode<K,T>* below = nullptr;

	SkipNode() = default;

	SkipNode(K key,T val) {
		this->key = new K(key);
		this->val = new T(val);
	}
	template <class KM,class TM> friend std::ostream& operator<<(std::ostream &strm, const SkipNode<KM,TM> &o);
};
template <class K,class T> std::ostream& operator<<(std::ostream &strm, const SkipNode<K,T> &o) {
	assert (&o != nullptr && "O is a nullptr");
	strm<<"SkipNode(at "<<&o<<" ("<<(o.key)<<"->";
	if (o.key==nullptr) {
		strm<<"NULL";
	} else {
		strm<<(*o.key);
	}
	strm<<">>"<<(o.val)<<"->";
	if (o.val==nullptr) {
		strm<<"NULL";
	} else {
		strm<<(*o.val);
	}
	strm<<") -V>"<<o.below<<") ";
	return strm;
}
template <class K,class V, int leftHeight = 50> class SkipList {

	using Node = SkipNode<K,V>;

	//every vector node is a valueless node main roots[x] = layer x root
	vector<Node*> roots;
	//the biggest height of any prong
	size_t biggestHeight = 0;

	size_t generateHeight() {
		size_t ret = 1;
		while (ret<roots.size()-1 && rand()%2==0) {
			ret++;
		}
		return ret;
	}

public:
	SkipList() {
		roots.resize(leftHeight);
		for (auto i = 0; i < roots.size(); ++i) {
			roots.at(i) = new Node();
			if (i!=0) {
				roots.at(i)->below = roots.at(i-1);
			}
		}
	}
	void put(const K& k, const V& val) {
		auto thisHeight = generateHeight();
		biggestHeight = max(thisHeight,biggestHeight);
		//used for generating lastVisitedOnThatLevel
		size_t currentLevel = biggestHeight;
		//level0 = lotl[0]
		vector<Node*> lastVisitedOnThatLevel;
		lastVisitedOnThatLevel.resize(biggestHeight);
		//get the node, but remember the last on each level
		Node* dropAfter = roots.at(biggestHeight);
		//find dropAfter, so you know when to drop
		do {
			//main if you need to go down
			if (dropAfter->right == nullptr || *dropAfter->right->key > k) {
				if (dropAfter->below == nullptr) {
					if (currentLevel==1) {
						lastVisitedOnThatLevel.at(--currentLevel) = dropAfter;
					}
					break;
				} else {
					//remember where yo went down
					lastVisitedOnThatLevel.at(--currentLevel) = dropAfter;
					dropAfter = dropAfter->below;
					continue;
				}
			} else {
				if (*dropAfter->right->key == k) {
					throw DuplicateKey("SkipList already contains that key");
				}
				//go forward one
				dropAfter = dropAfter->right;
			}
		} while (true);
		assert(currentLevel==0 && "Not on right level");
		for (; currentLevel < thisHeight; ++currentLevel) {
			Node *insertAfter = lastVisitedOnThatLevel.at(currentLevel);

			//main insert this in each slot
			Node* toInsert = new Node(k, val);
			toInsert->right = insertAfter->right;
			insertAfter->right = toInsert;

			//main downlink similar columns
			if (currentLevel != 0) {
				toInsert->below = lastVisitedOnThatLevel.at(currentLevel - 1)->right;
			}
		}
	}
	/*void putWithLogging(const K& k, const V& val) {
		auto thisHeight = generateHeight();
		cout<<"\nPutting "<<val<<" with Height "<<thisHeight<<'\n';

		biggestHeight = max(thisHeight,biggestHeight);

		//used for generating lastVisitedOnThatLevel
		size_t currentLevel = biggestHeight;


		//level0 = lotl[0]
		vector<Node*> lastVisitedOnThatLevel;
		lastVisitedOnThatLevel.resize(biggestHeight);

		//get the node, but remember the last on each level
		Node* dropAfter = roots.at(biggestHeight);

		//find dropAfter, so you know when to drop
		do {
			cout<<"At level "<<currentLevel<<'\n';
//			cout<<"\tComparing "<< *(dropAfter->right->key) << " and "<< k <<'\n';

			//if the next value is null, you can't go any further
			//if the node after you is bigger than you need to be
			if (dropAfter->right == nullptr || *dropAfter->right->key > k) {
				//if you can't go down any more, you're done
				if (dropAfter->below == nullptr) {
					cout<<"\tEND - Ended by finding spot"<<*dropAfter<<"\n";
					if (currentLevel==1) {
						lastVisitedOnThatLevel.at(--currentLevel) = dropAfter;
					}
					break;
				} else {
					cout<<"\tDOWN - Going down because value after me ";
					if (dropAfter->right== nullptr) {cout<<"NULL";} else {cout<<*dropAfter->right;}
					cout<<" is null or more than "<<k<<"\n";
					//remember where yo went down
					lastVisitedOnThatLevel.at(--currentLevel) = dropAfter;
					cout<<"\t\tLast visited["<<currentLevel<<"] is "<<*dropAfter<<'\n';
					//go down a layer
					dropAfter = dropAfter->below;
					continue;
				}
			} else {
				if (*dropAfter->right->key == k) {
					throw DuplicateKey("SkipList already contains that key");
				}
				cout<<"\tRIGHT - Going forward one because I'm less than the next value ("<<*(dropAfter->right->key)<<" <= "<<(k)<<"), passing "<<*(dropAfter->right->key)<<'\n';
				//go forward one
				dropAfter = dropAfter->right;
			}
		} while (true);
		assert(currentLevel==0 && "Not on right level");
//		if (dropAfter->val == nullptr) cout<<"drop after is left wall\n";
		cout<<"Done with mapping, on level "<<currentLevel<<'\n';

		for (; currentLevel < thisHeight; ++currentLevel) {
			Node *insertAfter = lastVisitedOnThatLevel.at(currentLevel);

			cout << "Applying level " << currentLevel << '\n';
			if (insertAfter->key == nullptr) {
				cout << "\tputting after left wall\n";
			} else {
				cout << "\tputting after " << *insertAfter->key << '\n';
			}

			//main insert this in each slot
			Node* toInsert = new Node(k, val);
//			cout<<"node "<<toInsert<<'\n';
//			toInsert = new Node(1,"15");
			toInsert->right = insertAfter->right;
			insertAfter->right = toInsert;
//			cout<<"MAKING KEY "<<toInsert->key<<"->"<<*toInsert->key<<'\n';

			//main downlink similar columns
			if (currentLevel != 0) {
				toInsert->below = lastVisitedOnThatLevel.at(currentLevel - 1)->right;
			}
		}
		cout<<"Done putting "<<val<<"\n\n";
	}*/

	/**@param key - The key of the value you want to get
	 * @return The value, if it is there. If not, DoesNotContain is thrown*/
	V get(K k) {
		//start on highest point
		Node* loc = roots.at(biggestHeight);
		do {
			//main if you need to go down
			if (loc->right == nullptr || *loc->right->key > k) {
				if (loc->below == nullptr) {
					throw DoesNotContain("Made it to bottom right, and it's not there");
				} else {
					loc = loc->below;
					continue;
				}
			} else {
				if (*loc->right->key == k) {
					//going "right" into it
					return *loc->right->val;
				}
				loc = loc->right;
			}
		} while (true);
	}

	void remove(K k) {
		auto thisHeight = generateHeight();
		biggestHeight = max(thisHeight,biggestHeight);
		//used for generating lastVisitedOnThatLevel
		size_t currentLevel = biggestHeight;
		//level0 = lotl[0]
		vector<Node*> lastVisitedOnThatLevel;
		lastVisitedOnThatLevel.resize(biggestHeight);
		//get the node, but remember the last on each level
		Node* dropAfter = roots.at(biggestHeight);
		//find dropAfter, so you know when to drop
		do {
			//main if you need to go down
			if (dropAfter->right == nullptr || *dropAfter->right->key > k) {
				if (dropAfter->below == nullptr) {
					if (currentLevel==1) {
						lastVisitedOnThatLevel.at(--currentLevel) = dropAfter;
					}
					break;
				} else {
					//remember where yo went down
					lastVisitedOnThatLevel.at(--currentLevel) = dropAfter;
					dropAfter = dropAfter->below;
					continue;
				}
			} else {
				//if it is found, go down
				if (*dropAfter->right->key == k) {
					lastVisitedOnThatLevel.at(--currentLevel) = dropAfter;
					if (currentLevel==0) break;
					dropAfter = dropAfter->below;
					continue;
				} else {
					//go forward one
					dropAfter = dropAfter->right;
				}
			}
		} while (true);
		assert(currentLevel==0 && "Not on right level");
		for (; currentLevel < thisHeight; ++currentLevel) {
			Node *removeAfter = lastVisitedOnThatLevel.at(currentLevel);

			//main insert this in each slot
			if (removeAfter->right == nullptr) {
				continue;
			}
			removeAfter->right = removeAfter->right->right;

			//todo delete
		}
	}

	void print() {
		//for every height
//		cout<<"height:"<<(biggestHeight-1)<<'\n';
		for (size_t h = biggestHeight-1; h!= numeric_limits<size_t>::max(); --h) {
//			cout<<"H"<<h<<'\n';
			//if empty layer, skip
			if (roots.at(h)->right == nullptr) continue;
			//for every node at that height
			Node* n = roots.at(h);
			while (n != nullptr){
				//print node
				if (n->key == nullptr) {
					cout<<"[start]\t-\t";
				} else {
					cout<<*(n->val)<<"\t-\t";
				}
				//go to next node
				n = n->right;
			}
			cout<<'\n';
		}
	}

	void printKeyMap() {
		//for every height
//		cout<<"height:"<<(biggestHeight-1)<<'\n';
		for (size_t h = biggestHeight-1; h!= numeric_limits<size_t>::max(); --h) {
//			cout<<"H"<<h<<'\n';
			//if empty layer, skip
			if (roots.at(h)->right == nullptr) continue;
			//for every node at that height
			Node* n = roots.at(h);
			while (n != nullptr){
				//print node
				if (n->key == nullptr) {
					cout<<"(start "<<n<<")\t-\t";
				} else {
					cout<<*n<<"\t-\t";
				}
				//go to next node
				n = n->right;
			}
			cout<<'\n';
		}
	}
};

//todo boolean template for min or max choice
/**MinHeap is where the smallest value rises*/
class MinHeap {

};