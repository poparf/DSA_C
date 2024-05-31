#pragma once

#include "DataUtil.h"


typedef struct BSTree {
	struct BSTree* left;
	struct Student* data;
	struct BSTree* right;
} BSTNode;







// In order traversal // ascending order if left first then rgiht
// descending order if right then left
// visit the left branch then the current node then the right branch

void inOrderTraversal(BSTNode* root) {
	while (root) {
		inOrderTraversal(root->left);
		printf("%d", root->data->income);
		inOrderTraversal(root->right);
	}
}

// Pre order traversal
// the root is always the first node visited
void preOrderTraversal(BSTNode* root) {
	while (root) {
		printf("%d", root->data->income);
		inOrderTraversal(root->left);
		inOrderTraversal(root->right);
	}
}

// Descending order. visiting the childs before the root
void postOrderTraversal(BSTNode* root) {
	while (root) {
		inOrderTraversal(root->left);
		inOrderTraversal(root->right);
		printf("%d", root->data->income);
	}
}




