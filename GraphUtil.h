#pragma once
#include "DataUtil.h"

typedef struct PList {
	Student* info;
	struct PList* nextVertex;
	struct SList* adjacencyList;
} Node, *PNode;

// Adjacency list
typedef struct SList {
	struct PList* mainVertex;
	struct SList* nextNeighbour;
}AdjacentNode, *PAdjacentNode;



// Matrix representation by using the list to list repres
typedef struct MatNode {
	Node* src;
	AdjacentNode* dest;
}MatNode;

// Array implementation
//typedef struct GNode {
//	int nodeIndex;
//	struct GNode* next;
//}GraphNode, *PGraphNode;
//
//typedef struct Graph {
//	Student* info;
//	GraphNode* neighbours;
//	int noNeighbours;
//};
//
//struct Graph graph[10];
//

Node* createVertex(Student* info) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->info = info;
	node->nextVertex = NULL;
	node->adjacencyList = NULL;
	return node;
}

Node* searchNode(Node* graphList, Student* info) {
	while (graphList && graphList->info->reference.intRef != info->reference.intRef)
		graphList = graphList->nextVertex;

	return graphList;
}

void insertNeighbour(AdjacentNode** neighbours , Node* mainVertex) {
	AdjacentNode* adjNode = (AdjacentNode*)malloc(sizeof(AdjacentNode));
	adjNode->mainVertex = mainVertex;
	adjNode->nextNeighbour = *neighbours;
	*neighbours = adjNode;
}



void displayGraph(Node* graph) {
	while (graph) {
		printf("Vertex: %s\n", graph->info->name);
		AdjacentNode* list = graph->adjacencyList;
		printf("\nNeighbours: \n");
		while (list) {
			printf("\t\t%s\n", list->mainVertex->info->name);
			
			//MatNode el = { .src = graph, .dest = list };
			// Add here the elements usijng i and j

			list = list->nextNeighbour;
		}
		printf("------------------------");
		graph = graph->nextVertex;
	}
}
void addEdge(Node** graphList, Student* source, Student* destination) {
	Node* src = searchNode(*graphList, source);
	if (src == NULL) {
		src = createVertex(source);
		src->nextVertex = (*graphList);
		(*graphList) = src;
	}
	Node* dest = searchNode(*graphList, destination);
	if (dest == NULL) {
		dest = createVertex(destination);
		dest->nextVertex = (*graphList);
		(*graphList) = dest;
	}

	insertNeighbour(&src->adjacencyList, dest);
	insertNeighbour(&dest->adjacencyList, src);
}

