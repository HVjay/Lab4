#include <iostream>
#include "lab4_binary_search_tree.hpp"

using namespace std;

// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree() {
	// setting size to 0
	size = 0;
	// root must be NULL
	root = NULL;
}

void BinarySearchTree::Destructor_Helper(TaskItem *node) {
	//rescursively delete the child and parent node
	if (node) {
		Destructor_Helper(node->left);
		Destructor_Helper(node->right);
		delete node;
		node = NULL;
		// decrement size
		size--;
	}
}

// PURPOSE: Explicit destructor of the class BinarySearchTree
BinarySearchTree::~BinarySearchTree() {
	//call on the recursive helper
	Destructor_Helper(root);
}


// PURPOSE: Returns the number of nodes in the tree
unsigned int BinarySearchTree::get_size() const {
	return size;
}

// PURPOSE: Returns the maximum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
//max val is the very right node
BinarySearchTree::TaskItem BinarySearchTree::max() const {
	TaskItem* temp = root;
	if (!temp)
		return BinarySearchTree::TaskItem(-1, "N/A");
	while (temp->right) {
		temp = temp->right;
	}
	return *temp;
}

// PURPOSE: Returns the minimum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
//min val is the very left node
BinarySearchTree::TaskItem BinarySearchTree::min() const {
	TaskItem* temp = root;
	if (!root)
		return BinarySearchTree::TaskItem(-1, "N/A");
	while (temp->left)
		temp = temp->left;
	//cout << temp->priority << endl;
	return *temp;
}

// PURPOSE: Returns the tree height
unsigned int BinarySearchTree::height()
{
	// Returns height of root (number of edges). Equal to longest path of nodes - 1
	return getHeight(root) - 1;
}

unsigned int BinarySearchTree::getHeight(BinarySearchTree::TaskItem *node)
{
	if (node == NULL) {
		return 0;
	}

	// recursively trying to find the longest path from passed node to bottom of tree
	unsigned int lh = getHeight(node->left);
	unsigned int rh = getHeight(node->right);

	// Finds maximum path
	return 1 + helper_max(lh, rh);
}


unsigned int BinarySearchTree::helper_max(unsigned int a, unsigned int b)
{
	return ((a > b) ? a : b);
}


// Recursive helper function to print values of the brain inOrder
void BinarySearchTree::inorder(TaskItem * node) const
{
	if (node != NULL) {
		cout << "Priority:" << node->priority << "  Description:" << node->description << "    ";
		inorder(node->left);
		inorder(node->right);
	}
}

// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const {
	inorder(root);
}


// PURPOSE: Returns true if a node with the value val exists in the tree	
// otherwise, returns false
bool BinarySearchTree::exists(BinarySearchTree::TaskItem val) const {
	//empty tree
	if (!root)
		return false;
	else if (root->priority == val.priority)
		return true;
	TaskItem* temp = root;
	while (temp) {
		if (temp->priority == val.priority)
			return true;
		//compare nodes and move temp accordingly 
		else if (temp->priority > val.priority)
			temp = temp->left;
		else
			temp = temp->right;
	}
	return false;
}



// PURPOSE: Optional helper function that returns a pointer to the root node
BinarySearchTree::TaskItem* BinarySearchTree::get_root_node() {
	return root;
}

// PURPOSE: Optional helper function that returns the root node pointer address
BinarySearchTree::TaskItem** BinarySearchTree::get_root_node_address() {
	return &root;
}

// PURPOSE: Optional helper function that gets the maximum depth for a given node
int BinarySearchTree::get_node_depth(BinarySearchTree::TaskItem* n) const {
	return 0;
}


// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool BinarySearchTree::insert(BinarySearchTree::TaskItem val) {
	if (exists(val) == true)
		return false;
	//empty true
	if (!root) {
		root = new TaskItem(val);
		root->left = NULL;
		root->right = NULL;
		size++;
		return true;
	}

	TaskItem* temp = root;
	//iterate through the tree until finding the correct node to insert to
	while (temp) {
		if (temp->priority > val.priority && (temp->left == NULL)) {
			temp->left = new TaskItem(val);
			temp->left->left = NULL;
			temp->left->right = NULL;
			size++;
			return true;
		}
		else if (temp->priority < val.priority && (temp->right == NULL)) {
			temp->right = new TaskItem(val);
			temp->right->left = NULL;
			temp->right->right = NULL;
			size++;
			return true;
		}
		else if (temp->priority > val.priority) {
			temp = temp->left;
		}
		else {
			temp = temp->right;
		}
	}
	return false;
}

// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise

//start from remove function at the bottom and work read down-up

//case of a single leaf node
bool BinarySearchTree::remove_cases_2(TaskItem* node) {
	TaskItem* temp = root;
	while (temp) {
		//case of finding the parent of node you want to delete
		if (temp->left == node) {
			//single left child node
			if (node->left) {
				temp->left = node->left;
				delete node;
				size--;
				return true;
			}

			else if (node->right) {
				temp->left = node->right;
				delete node;
				size--;
				return true;
			}
		}

		//single right
		else if (temp->right == node) {
			if (node->left) {
				temp->right = node->left;
				delete node;
				node = NULL;
				size--;
				return true;
			}
			else if (node->right) {
				temp->right = node->right;
				delete node;
				node = NULL;
				size--;
				return true;
			}
		}

		//iterating through the tree
		else if (temp->priority > node->priority) {
			temp = temp->left;
		}
		else if (temp->priority < node->priority) {
			temp = temp->right;
		}
	}
	return false;
}

//finds and returns parent of the node to be removed
BinarySearchTree::TaskItem* BinarySearchTree::find_parent(TaskItem* node) {
	TaskItem* temp = root;
	while (temp) {
		if (temp->left == node || temp->right == node)
			return temp;
		else if (temp->priority > node->priority) {
			temp = temp->left;
		}
		else if (temp->priority < node->priority) {
			temp = temp->right;
		}
	}
}


bool BinarySearchTree::remove_cases(TaskItem* node) {
	//case 1: single leaf node
	if (node->left == NULL && node->right == NULL) {
		if (node == root) {
			delete root;
			root = NULL;
			size = 0;
			return true;
		}
		//ensuring parent->child =NULL
		//helper function to find parent of the one to be removed
		TaskItem* parent = find_parent(node);
		if (parent->left == node) {
			parent->left = NULL;
			delete node;
			node = NULL;
			size--;
			return true;
		}
		else if (parent->right == node) {
			parent->right = NULL;
			delete node;
			node = NULL;
			size--;
			return true;
		}

	}

	//case 2: non-leaf, with one child
	else if ((node->left == NULL && node->right != NULL) || (node->right == NULL && node->left != NULL)) {

		//if the one to be removed is the root, the child node is now the new root
		if (node == root) {
			if (node->right) {
				root = node->right;
				size--;
				return true;
			}
			else if (node->left) {
				root = node->left;
				size--;
				return true;
			}

		}
		else {
			//helper function to find parent of the one to be removed
			bool is_equal = remove_cases_2(node);
			return is_equal;
		}
	}

	//case 3: contain two children
	else {
		//create a new BST based of the right child node
		BinarySearchTree* tempBSTright = new BinarySearchTree;
		tempBSTright->root = node->right;

		//call the min of the rightBST to find successor of the list
		TaskItem successor = (tempBSTright->min());

		//swap root contents with sucessor contents
		if (root == node) {
			remove(successor);
			root->priority = successor.priority;
			root->description = successor.description;
			size--;
			return true;
		}

		// recursively remove the successor of the initial BST
		remove(successor);

		//set node contents to be successor contents
		node->priority = successor.priority;
		node->description = successor.description;
		size--;
		return true;
	}
}

bool BinarySearchTree::remove(BinarySearchTree::TaskItem val) {
	if (!root)
		return false;
	else if (!exists(val))
		return false;
	else {
		TaskItem* temp = root;
		//finds node to be removed
		while (temp) {
			if (temp->priority == val.priority) {
				//call on helper function
				bool worked = remove_cases(temp);
				return worked;
			}
			else if (temp->priority > val.priority)
				temp = temp->left;
			else
				temp = temp->right;
		}
		return false;
	}

}
