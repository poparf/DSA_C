#include "DataUtil.h"


//Varianta 1

//typedef struct QueueNode {
//	Student* info;
//	struct QueueNode* next;
//}QueueNode, *PQueueNode;
//
//
//typedef struct Queue {
//	QueueNode* head;
//	QueueNode* tail;
//}Queue;

// Varianta 2

typedef struct NodeQ {
	struct NodeQ* prev;
	Student* info;
	struct NodeQ* next;
}QueueNode, * PQueueNode;

QueueNode* createQueueNode(Student* info) {
	QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
	node->info = info;
	node->next = node->prev = NULL;
	return node;
}

void putNode(QueueNode** queue, Student* stud) {
	QueueNode* node = createQueueNode(stud);
	if ((*queue) == NULL) {
		node->next = node->prev = node;
		*queue = node;
	}
	else {
		// Connect the node to the structure
		node->prev = (*queue)->prev;
		node->next = (*queue);
		// Connect the structure to the node
		(*queue)->prev->next = node;
		(*queue)->prev = node;
	}
}

Student* popNode(QueueNode** queue) {
	Student* info = NULL;
	if (*queue != NULL)
	{
		if ((*queue)->next == (*queue)->prev && (*queue)->prev == (*queue)) {
			info = (*queue)->info;
			free(*queue);
			*queue = NULL;
		}
		else
		{
			info = (*queue)->info;
			QueueNode* temp = (*queue);
			(*queue)->prev->next = (*queue)->next;
			(*queue)->next->prev = (*queue)->prev;
			*queue = (*queue)->next;
			free(temp);
		}
	}

	return info;
}