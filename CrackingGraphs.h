#pragma once
#include "DataUtil.h"

typedef struct PList {
	int visited; // for bfs and dfs 1 true 0 false
	Student* info;
	struct SList* adjList;
	struct PList* nextNeighbour;
}Node;

typedef struct SList {
	struct SList* nextAdj;
	struct PList* refNode;
}AdjNode;

Node* createNode(Student* info) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->info = info;
	newNode->nextNeighbour = newNode->adjList = NULL;
	newNode->visited = 0;
	return newNode;
}

Node* searchNode(Node* mainVertex, Student* s) {
	while (mainVertex && mainVertex->info->reference.extRef != s->reference.extRef) {
		mainVertex = mainVertex->nextNeighbour;
	}
	
	return mainVertex;
}

void insertNeighbour(AdjNode** adjList, Node* refNode) {
	AdjNode* newAdjNode = (AdjNode*)malloc(sizeof(AdjNode));
	newAdjNode->nextAdj = (*adjList);
	newAdjNode->refNode = refNode; // setam referinta catre nodul original si inseram la inceputul listei
	(*adjList) = newAdjNode;
}



// Add an edge
void addEdge(Node** mainVertex, Student* source, Student* destination) {
	// Exista nodul respectiv in graf ?
	Node* src = searchNode(*mainVertex, source);
	if (src == NULL) { // Daca nu exista trebuie sa il creeam si sa l adaugam in lista princiapla
		src = createNode(source);
		src->nextNeighbour = (*mainVertex);  // inseram la inceput intr o lista inlantuita
		(*mainVertex) = src;
	}

	Node* dst = searchNode(*mainVertex, destination);
	if (dst == NULL) {
		dst = createNode(destination);
		dst->nextNeighbour = (*mainVertex);
		(*mainVertex) = dst;
	}

	// Acum trebuie sa inseram si in lista adiacenta pentru ambele noduri
	insertNeighbour(&src->adjList, dst);
	//insertNeighbour(&dst->adjList, src);
}

void displayGraph(Node* graph) {
	while (graph) {
		printf("Vertex: %s\n", graph->info->name);
		AdjNode* list = graph->adjList;
		printf("\nNeighbours: \n");
		while (list) {
			printf("\t\t%s\n", list->refNode->info->name);

			//MatNode el = { .src = graph, .dest = list };
			// Add here the elements usijng i and j

			list = list->nextAdj;
		}
		printf("------------------------");
		graph = graph->nextNeighbour;
	}
}


// Implement BFS

typedef struct QueueNode {
	Node* node;
	struct QueueNode* next;
}QueueNode;

void enqueue(QueueNode** tail, Node* node) {
	QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
	
	if ((*tail) == NULL) {
		newNode->node = node;
		newNode->next = newNode;
		(*tail) = newNode;
	}
	else {
		newNode->node = node;
		newNode->next = (*tail)->next;
		(*tail)->next = newNode;
		(*tail) = newNode;
	}
}

Node* dequeue(QueueNode** tail) {
	if ((*tail)) {
		if ((*tail)->next) {
			
				Node* tempRet = (*tail)->next->node;
				QueueNode* tempN = (*tail)->next;
				(*tail)->next = tempN->next;
				free(tempN);
				return tempRet;
			
		}
		else {
			Node* tempRet = (*tail)->node;
			free((*tail));
			return tempRet;
		}
	}
	return NULL;
}

void BFS(Node* mainVertex) {
	if (mainVertex == NULL) return;
	QueueNode* tail = NULL;
	enqueue(&tail, mainVertex);
	mainVertex->visited = 1;

	while (tail != NULL ? 1 : 0) {
		Node* deqNode = dequeue(&tail);
		printStudent(deqNode->info);
		deqNode->visited = 1;
		AdjNode* adjNode = deqNode->adjList;
		while (adjNode) {
			if (adjNode->refNode->visited == 0) {
				enqueue(&tail, adjNode->refNode);
			}
			adjNode = adjNode->nextAdj;
		}
	}
}

// Implement DFS

void DFSRecursive(Node* mainVertex) {
	if (mainVertex == NULL) return;
	printStudent(mainVertex->info);
	mainVertex->visited = 1;

	AdjNode* temp = mainVertex->adjList;
	while (temp) {
		if (!temp->refNode->visited) {
			DFSRecursive(temp->refNode);
		}
		temp = temp->nextAdj;
	}
}

typedef struct Stack {
	Node* node;
	struct Stack* next;
}StackNode;

StackNode* createStackNode(Node* node) {
	StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
	newNode->next = NULL;
	newNode->node = node;
	return newNode;
}

void insertStackNode(StackNode** top, Node* node) {
	StackNode* n = createStackNode(node);
	n->next = (*top);
	(*top) = n;
}

Node* pop(StackNode** top) {
	Node* tempInfo = NULL;
	
	StackNode* temp = (*top);
	(*top) = (*top)->next;
	tempInfo = temp->node;
	free(temp);
	
	return tempInfo;
}

int isEmpty(StackNode* top) {
	return top == NULL ? 1 : 0;
}

void DFSStack(Node* mainVertex) {
	if (mainVertex == NULL) return;
	StackNode* top = NULL;
	insertStackNode(&top, mainVertex);
	mainVertex->visited = 1;

	while (!isEmpty(top)) {
		Node* poppedNode = pop(&top);
		poppedNode->visited = 1;
		if (poppedNode != NULL) {
			printStudent(poppedNode->info);
			AdjNode* temp = poppedNode->adjList;
			while (temp) {
				if(temp->refNode->visited != 1)
					insertStackNode(&top, temp->refNode);
				temp = temp->nextAdj;
			}
		}
	}
}


//Route Between Nodes : 
// Given a directed graph, design an algorithm to find out 
// whether there is a
//route between two nodes.

// BFS starting both nodes 
// we need 2 vectors that store the nodes that we re visited by each search from each node
// we could use hashmap for O(1) search
// so we have the 2 nodes that start each with each individual queue a search
// for each node that each search finds it inserts in the specific hashmap
// in java/python it would be very easy

// let s use chaining

typedef struct HashNode {
	Student* info;
	struct HashNode* next;
}HashNode;

typedef HashNode** HashTable;
#define HTABLESIZE

int hash(char key) {
	return (key * 31) % HTABLESIZE
}


void put(Student* info) {

}


void BFS(Node* n1, Node* n2) {
	/*if (mainVertex == NULL) return; */ /*
	QueueNode* tail = NULL;
	enqueue(&tail, mainVertex);
	mainVertex->visited = 1;

	while (tail != NULL ? 1 : 0) {
		Node* deqNode = dequeue(&tail);
		printStudent(deqNode->info);
		deqNode->visited = 1;
		AdjNode* adjNode = deqNode->adjList;
		while (adjNode) {
			if (adjNode->refNode->visited == 0) {
				enqueue(&tail, adjNode->refNode);
			}
			adjNode = adjNode->nextAdj;
		}
	}*/
}