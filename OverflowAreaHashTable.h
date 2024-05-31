#pragma once
#include "DataUtil.h"

/*
Splits the hash table in two regions:
•Primary area used for storing the initial elements;
•Secondary area used for storing the collisions;
•When searching for an element a pointer is used for referring to
the collision area locations;
•The access to the secondary area is made by using a pointer
stored in the primary area;
•The search time operation is almost constant O(1), much better
than other types of implementations;
*/

/*
Explicatie:
 ai un hash table si inca unul care tine valorile care intra in coliziune.
 se introduc unul dupa altul iar cautarea este liniara
*/

#define HASHT_SIZE 13

typedef struct HTable
{
	Student** items;
	int size;

	Student** overflowArea;
	int overflowAreaSize;
	int position;
}HashTable;

int hash(const char* name) {
	int sum = 0;
	for (int i = 0; i < strlen(name); i++) {
		sum += name[i] * 31;
	}
	return sum % HASHT_SIZE;
}

void initHashTable(HashTable** hashTable) {
	(*hashTable) = (HashTable*)malloc(sizeof(HashTable));
	(*hashTable)->items = (Student**)calloc(HASHT_SIZE, sizeof(Student*) * HASHT_SIZE);
	(*hashTable)->overflowArea = (Student**)calloc(HASHT_SIZE, sizeof(Student*) * HASHT_SIZE); // decide on the size you want the overflow area to be
	(*hashTable)->overflowAreaSize = 0;
	(*hashTable)->position = 0;
	(*hashTable)->size = HASHT_SIZE;
}

void putHT(HashTable** hashTable, Student* stud) {
	if ((*hashTable) == NULL) {
		initHashTable(&(*hashTable));
	}

	int hashValue = hash(stud->name);

	if ((*hashTable)->items[hashValue] != NULL) {
		// place already occupied
		if ((*hashTable)->position < (*hashTable)->overflowAreaSize) {
			(*hashTable)->overflowArea[(*hashTable)->position] = stud;
			(*hashTable)->position += 1;
		}
		else {
			// What do we do if we don t have enough space?
		}
	}
	else {
		(*hashTable)->items[hashValue] = stud;
	}
}

Student* getHT(HashTable* hashTable, const char* name) {
	if (hashTable == NULL) {
		return;
	}

	int hashValue = hash(name);

	if (hashTable->items[hashValue] != NULL) {
		if (strcmp(hashTable->items[hashValue]->name, name) == 0) {
			return hashTable->items[hashValue];
		}
		else {
			// Search in the overflow area
			for (int i = 0; i < hashTable->overflowAreaSize; i++) {
				if (strcmp(hashTable->overflowArea[i]->name, name) == 0) {
					return hashTable->overflowArea[i];
				}
			}

		}
	}
	return NULL;
}

void deleteHT(HashTable* hashTable, const char* name) {
	if (hashTable->items == NULL || hashTable->overflowArea == NULL) {
		return;
	}

	int hashValue = hash(name);

	if (hashTable->items[hashValue] != NULL) {
		if (strcmp(hashTable->items[hashValue]->name, name) == 0) {
			deleteStudent(hashTable->items[hashValue]);
			hashTable->items[hashValue] = NULL;
			return;
		}
		else {
			// Search in the overflow area
			for (int i = 0; i < hashTable->overflowAreaSize; i++) {
				if (strcmp(hashTable->overflowArea[i]->name, name) == 0) {
					deleteStudent(hashTable->items[hashValue]);
					hashTable->items[hashValue] = NULL;
					return;
				}
			}

		}
	}
}

void printHT(HashTable* hashTable) {
	printf("\nMain hashtable:\n");
	for (int i = 0; i < hashTable->size; i++) {
		printStudent(hashTable->items[i]);
	}

	printf("\nOverflow area:\n");
	for (int i = 0; i < hashTable->overflowAreaSize; i++) {
		printStudent(hashTable->overflowArea[i]);
	}
}