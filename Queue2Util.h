#pragma once
#include "DataUtil.h"

typedef struct Node {
	struct Student* info;
	struct Node* next;
}QueueNode, *PQueueNode;

QueueNode* createQueueNode(Student* info) {
	QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
	node->info = info;
	node->next = NULL;
	return node;
}

void putNode(QueueNode** tail, Student* stud) {
	QueueNode* node = createQueueNode(stud);
	if (*tail == NULL)
		node->next = node;
	else {
		node->next = (*tail)->next;
		(*tail)->next = node;

	}
	*tail = node; 
}

Student* getNode(QueueNode** tailQueue) {
	Student* result = NULL;
	if (*tailQueue != NULL) {
		result = (*tailQueue)->next->info;
		if ((*tailQueue)->next == (*tailQueue)) {
			free(*tailQueue);
			*tailQueue = NULL;
		}
		else {
			QueueNode* head = (*tailQueue)->next;
			(*tailQueue)->next = head->next;
			free(head);
		}
	}
	return result;
}

Student* peekNode(QueueNode** tailQueue) {
	Student* result = NULL;
	if ((*tailQueue) != NULL) {
		result = (*tailQueue)->next->info;
	}
	return result;
}

void displayQueue(QueueNode** tail) {
	QueueNode* newQueue = NULL;

	while ((*tail) != NULL) {
		Student* newNode = getNode(tail);
		printStudent(newNode);
		putNode(&newQueue, newNode);
	}

	while (newQueue != NULL) {
		Student* newNode = getNode(&newQueue);
		putNode(&tail, newNode);
	}
}
void displayQueue2(QueueNode** tail) {
	Student* lastInfo = getNode(tail);
	printStudent(lastInfo);
	while (lastInfo != (*tail)->info) {
		Student* temp = getNode(tail);
		printStudent(temp);
		putNode(tail, temp);
	}
}

void displayQueue3(QueueNode** tail) {
	Student* info = peekNode(*tail);
	Student* tmp = NULL;
	while (tmp != info) {
		tmp = getNode(tail);
		printStudent(tmp);
		putNode(tail, tmp);
		tmp = peekNode(*tail);
	}
}