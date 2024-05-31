#pragma once
#include "DataUtil.h"

//Animal Shelter : An animal shelter, which holds only dogsand cats, operates on a strictly"first in, first
//out" basis. People must adopt either the "oldest" (based on arrival time) of all animals at the shelter,
//or they can select whether they would prefer a dog or a cat(and will receive the oldest animal of
//	that type).They cannot select which specific animal they would like.Create the data structures to
//	maintain this system and implement operations such as enqueue, dequeueAny, dequeueDog,
//	and dequeueCat.You may use the built - in Linked list data structure.
//	Hints : #22, #56, #63

// Double circular linked list
typedef struct QueueNode {
	char id;
	struct QueueNode* next;
}QueueNode;

typedef struct Queue {
	struct QueueNode* head;
	struct QueueNode* tail;
}Queue;

typedef struct Shelter {
	Queue dogs;
	Queue cats;
}Shelter;

enum Type {
	DOG, CAT
};

void enqueue(Shelter* shelter, char id, Type type) {
	if (shelter) {
		QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
		newNode->id = id;
		if (type == DOG) {
			if ((*shelter).dogs.tail == NULL) {
				(*shelter).dogs.tail = (*shelter).dogs.head = newNode;
			}
			else {
				(*shelter).dogs.tail->next = newNode;
				(*shelter).dogs.tail = newNode;
			}
		}
		else {
			if ((*shelter).cats.tail == NULL) {
				(*shelter).cats.tail = (*shelter).cats.head = newNode;
			}
			else {
				(*shelter).cats.tail->next = newNode;
				(*shelter).cats.tail = newNode;
			}
		}
	}
}

char dequeueAny(Shelter* shelter) {
	if (shelter) {
		if (shelter->cats.head) {
			char retVal = shelter->cats.head->id;
			QueueNode* temp = shelter->cats.head;

			shelter->cats.head = shelter->cats.head->next;
			free(shelter->cats.head);
			return retVal;
		}
		else if (shelter->dogs.head) {
			char retVal = shelter->dogs.head->id;
			QueueNode* temp = shelter->dogs.head;

			shelter->dogs.head = shelter->dogs.head->next;
			free(shelter->dogs.head);
			return retVal;
		}
		else {
			return 0;
		}
	}
}
