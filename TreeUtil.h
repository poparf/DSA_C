#pragma once
#include "DataUtil.h"

typedef struct TreeN
{
	struct TreeN* left;
	Student* info;
	struct TreeN* right;
}TreeNode, * PTreeNode;

TreeNode* createTreeNode(Student* info)
{
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	node->info = info;
	node->left = node->right = NULL;
	return node;
}
Student* getMax(TreeNode* root)
{
	while (root->right)
		root = root->right;
	return root->info;
}



void inorder(TreeNode* root)
{
	if (root)
	{
		inorder(root->left);
		printf("Student: %s, reference: %d\n", root->info->name, root->info->reference.intRef);
		inorder(root->right);
	}
}

void preorder(TreeNode* root)
{
	if (root)
	{
		printf("Student: %s\n", root->info->name);
		preorder(root->left);
		preorder(root->right);
	}
}

void insertTree(TreeNode** root, Student* info)
{
	if (*root == NULL)
	{
		TreeNode* node = createTreeNode(info);
		*root = node;
	}
	else
	{
		if ((*root)->info->reference.intRef > info->reference.intRef)
			insertTree(&(*root)->left, info);
		else if ((*root)->info->reference.intRef < info->reference.intRef)
			insertTree(&(*root)->right, info);
		else
			printf("Key already exists!");

	}
}

void displayTreeStructure(TreeNode* root, int level) {
	if (root != NULL) {
		for (int i = 0; i < level; i++)
			printf("\t");

		level++;
		printf("%s\n", root->info->name);
		displayTreeStructure(root->left, level);
		displayTreeStructure(root->right, level);
	}
	else {
		for (int i = 0; i < level; i++)
		{
			printf("\t");
		}
		printf("NULL\n");
	}
}
TreeNode* FindMin(TreeNode* root) {
	if (root == NULL) return NULL;
	TreeNode* temp = root;
	while (temp->left != NULL)
		temp = temp->left;
	return temp;
}

Student* deleteNodeByKey(TreeNode** root, unsigned char key) {
	if (*root != NULL) {
		if ((*root)->info->reference.intRef > key)
			deleteNodeByKey(&(*root)->left, key);
		else if ((*root)->info->reference.intRef < key)
			deleteNodeByKey(&(*root)->right, key);
		else { // we found the key

			if ((*root)->left == NULL && (*root)->right == NULL)
			{
				deleteStudent((*root)->info);
				free(*root);
				*root = NULL;
			}
			else if ((*root)->left == NULL) {
				deleteStudent((*root)->info);
				TreeNode* temp = (*root);
				(*root) = temp->right;
				free(temp);
			}
			else if ((*root)->right == NULL) {
				deleteStudent((*root)->info);
				TreeNode* temp = (*root);
				(*root) = temp->left;
				free(temp);
			}
			else {

				/*TreeNode* temp = FindMin((*root)->right);
				deleteStudent((*root)->info);
				(*root)->info = createStudent(temp->info->name,temp->info->income,temp->info->reference.extRef);
				(*root)->right = deleteNodeByKey(&(*root)->right, temp->info->reference.intRef);*/
			}
		}
	}
}

// Homework finish this deletion.
void deleteFullNode(TreeNode** root, TreeNode** rSubTree) {
	if ((*rSubTree)->left)
		deleteFullNode(root, &(*rSubTree)->left);
	else {

	}
}