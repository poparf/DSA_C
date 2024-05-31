#pragma once

typedef struct Arrival {
	char* trainCode;
	char* comingFrom;
	char* arrivalTime; // HH:MM
	unsigned short delay; // minutes
	unsigned short noOfPassengers; 
} Arrival;

typedef struct BST {
	struct BST* left;
	Arrival* info;
	struct BST* right;
}BSTNode;

// Create a bst having the key arrival time
// the tree must have at least 7 entries from a text file

Arrival* createArrival(const char* code, const char* src, const char* time, unsigned short delay, unsigned short pass) {
	Arrival* node = (Arrival*)malloc(sizeof(Arrival));
	node->arrivalTime = (char*)malloc(sizeof(char)* strlen(time) + 1);
	strcpy(node->arrivalTime, time);

	node->trainCode = (char*)malloc(sizeof(char) * strlen(code) + 1);
	strcpy(node->trainCode, code);

	node->comingFrom = (char*)malloc(sizeof(char) * strlen(src) + 1);
	strcpy(node->arrivalTime, src);

	node->delay = delay;
	node->noOfPassengers = pass;
	return node;
}

BSTNode* createNode(Arrival* info) {
	BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
	newNode->left = newNode->right = NULL;
	newNode->info = info;
	return newNode;
}

void insert(BSTNode** root, Arrival* info) {
	if ((*root) == NULL) {
		(*root) = createNode(info);
	}
	else {
		if (strcmp((*root)->info->arrivalTime, info->arrivalTime) > 0) {
			insert((*root)->left, info);
		}
		else if (strcmp((*root)->info->arrivalTime, info->arrivalTime) < 0) {
			insert((*root)->right, info);
		}
		else {
			printf("Duplicate value.");
			return;
		}
	}
}

void displayNode(BSTNode* n) {
	if (n) {
		printf("%s\n", n->info->arrivalTime);
	}
}

// print all arrivals in the reversed order of their arrival time
void printReverese(BSTNode* root) {
	if (root) {
		printReverse(root->right);
		displayNode(root);
		printReverese(root->left);
	}
}


// the arrival that is the last one to come in the train station.// biggest node

Arrival* getLast(BSTNode* root) {
	if (root) {
		while (root->right) {
			root = root->right;
		}
		return root->info;
	}
}


// count how many arrivals have a delay // similar to counting the leafs or height

int countDelays(BSTNode* root) {
	if (root) {
		if (root->info->delay > 0) {
			return 1 + countDelays(root->left) + countDelays(root->right);
		}
		else {
			return 0;
		}
	}
}


// the total number of passengers for the arrivals coming from a given value . count the number of nodes with the same key




// write afunction that saves all the arrivalls starting frm the root of the tree all the way to a given node in an array ( giveen as a parameter by its arrival time ) in an
// array of pointers to be displayed// the array doesn't share memory space// deep copy