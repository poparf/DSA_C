#pragma once
// create the linearised version of the binary tree - possible exam subject

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

struct BstNode
{
	int data;
	struct BstNode* left;
	struct BstNode* right;
};

typedef struct BstNode BstNode;


// queue code
//##########################################################################
typedef struct Node {
	struct BstNode* data;
	struct Node* next;
}Node;

Node* front = NULL;
Node* rear = NULL;

void Enqueue(BstNode* x) {
	Node* temp = (Node*)malloc(sizeof(struct Node*));
	temp->data = x;
	temp->next = NULL;
	if (front == NULL && rear == NULL) {
		front = rear = temp;
		return;
	}
	rear->next = temp;
	rear = temp;
}

void Dequeue() {
	Node* temp = front;
	if (front == NULL) {
		return;
	}
	if (front == rear) {
		front = rear = NULL;
	}
	else {
		front = front->next;
	}
	//aici crapa
	//free(temp);
}

BstNode* peek() {
	return front->data;
}

bool isEmpty() {

	return front == NULL ? true : false;
}
//##########################################################################


BstNode* Insert(BstNode* root, int data);
BstNode* GetNewNode(int data);
bool Search(BstNode* root, int data);
void bfTraversal(BstNode* root);
bool OptimIsBinarySearchTree(BstNode* root, int minValue, int maxValue);

void main()
{
	BstNode* root = NULL;
	root = Insert(root, 15);
	root = Insert(root, 20);
	root = Insert(root, 10);
	root = Insert(root, 30);
	root = Insert(root, 12);
	root = Insert(root, 14);
	root = Insert(root, 16);
	//printf("Search fo%d", Search(root, 11));
	printf("\nMin recursive: %d", FindMaxRecursive(root));
	printf("\nHeight: %d\n", FindHeight(root));
	dfTravPreorder(root);
	printf("\n");
	dfTravInorder(root);
	printf("\n");
	dfTravPostorder(root);
	printf("\n");
	bfTraversal(root);

	printf("\n");
	printf("BST: %d", IsBST(root));
}

BstNode* GetNewNode(int data) {
	BstNode* newNode = (BstNode*)malloc(sizeof(BstNode));
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

BstNode* Insert(BstNode* root, int data) {
	if (root == NULL)
		root = GetNewNode(data);
	else if (data <= root->data)
		root->left = Insert(root->left, data);
	else
		root->right = Insert(root->right, data);
	return root;
}

bool Search(BstNode* root, int data) {
	if (root == NULL) return false;
	if (root->data == data) return true;
	if (data <= root->data) return Search(root->left, data);
	else return Search(root->right, data);
}


BstNode* FindMin(BstNode* root) {
	if (root == NULL) return NULL;
	BstNode* current = root;
	while (current->left) {
		current = current->left;
	}
	return current;
}

int FindMinRecursive(BstNode* root) {
	if (root == NULL) return -1;
	if (root->left == NULL) return root->data;
	else return FindMinRecursive(root->left);
}

int FindMaxRecursive(BstNode* root) {
	if (root == NULL) return -1;
	if (root->right == NULL) return root->data;
	else return FindMaxRecursive(root->right);
}

int max(int a, int b) {
	return a > b ? a : b;
}

// O(n)
int FindHeight(BstNode* root) {
	if (root == NULL) return -1; // -1 to account for the first edge.
	// 0 if we want to count the nodes.
	return max(FindHeight(root->left), FindHeight(root->right)) + 1;
}

// tree traversal
// process of visiting each node in the tree exactly once in some order
// to process each node:
// 
// Breadth-first traversal
// Depth-first traversal
/*
	- preorder data left right
	- inorder left data right
	- postorder left right data
*/

int dfTravPreorder(BstNode* root) {
	if (root == NULL) return -1;
	printf("%d ", root->data); // process

	dfTravPreorder(root->left);
	dfTravPreorder(root->right);
}

int dfTravInorder(BstNode* root) {
	if (root == NULL) return -1;

	dfTravPreorder(root->left);
	printf("%d ", root->data); // process
	dfTravPreorder(root->right);
}

int dfTravPostorder(BstNode* root) {
	if (root == NULL) return -1;

	dfTravPreorder(root->left);
	dfTravPreorder(root->right);
	printf("%d ", root->data); // process
}

void bfTraversal(BstNode* root) {
	if (root == NULL)  return;

	Enqueue(root);

	while (!isEmpty())
	{
		BstNode* nextNode = peek();
		printf("%d ", nextNode->data);
		Dequeue();

		if (nextNode->left != NULL)
			Enqueue(nextNode->left);
		if (nextNode->right != NULL)
			Enqueue(nextNode->right);
	}

}

bool isSubtreeGreater(BstNode* root, int value) {
	if (root == NULL) return true;
	if (root->data > value
		&& isSubtreeGreater(root->left, value)
		&& isSubtreeGreater(root->right, value))
		return true;
	else return false;
}

bool isSubtreeLesser(BstNode* root, int value) {
	if (root == NULL) return true;
	if (root->data < value
		&& isSubtreeLesser(root->left, value)
		&& isSubtreeLesser(root->right, value))
		return true;
	else return false;
}

// Check if a given binary tree is bst
bool isBinarySearchTree(BstNode* root) {
	if (root == NULL) return true;
	if (isSubtreeLesser(root->left, root->data)
		&& isSubtreeGreater(root->right, root->data)
		&& isBinarySearchTree(root->left)
		&& isBinarySearchTree(root->right))
		return true;
	else return false;
}


bool OptimIsBinarySearchTree(BstNode* root, int minValue, int maxValue) {
	if (root == NULL) return true;
	if (
		root->data > minValue
		&& root->data < maxValue
		&& OptimIsBinarySearchTree(root->left, minValue, root->data)
		&& OptimIsBinarySearchTree(root->right, root->data, maxValue)
		)
		return true;
	else
		return false;
}

bool IsBST(BstNode* root) {
	return OptimIsBinarySearchTree(root, -_CRT_INT_MAX, _CRT_INT_MAX);
}

// Delete a node from BST
// case 1: no child
// case 2: one child

// case 3
/*
* Find min in right
* copy the value in targeted node
* delete duplicate from right subtree
*
* find max in left
* copy the value in targeted node
* delete duplicate from left subtree
*/


// passing a local copy of root node
BstNode* Delete(BstNode* root, int data) {
	if (root == NULL) return root;
	else if (data < root->data) root->left = Delete(root->left, data);
	else if (data > root->data) root->right = Delete(root->right, data);
	else
	{
		// Case 1: No child
		if (root->left == NULL && root->right == NULL) {
			free(root);
			root = NULL;
		}
		// Case 2: One child
		else if (root->left == NULL) {
			BstNode* temp = root;
			root = root->right;
			free(temp);
		}
		else if (root->right == NULL) {
			BstNode* temp = root;
			root = root->left;
			free(temp);
		}
		// Case 3: 2 children
		else {
			BstNode* temp = FindMin(root->right);
			root->data = temp->data;
			root->right = Delete(root->right, temp->data);
		}
	}
	return root;
}