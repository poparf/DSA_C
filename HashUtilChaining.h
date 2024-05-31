#pragma once
#include "DataUtil.h"

typedef struct HashN
{
	Student* info;
	struct HashN* next;
}HashNode, *PHashNode;

#define HASHT_SIZE 26

// Search for overflow area hash table and probing

//HashNode** hashTable0;
//// or
//PHashNode* hashTable1;
//// or
//typedef HashNode** HashTable;
//HashTable hashTable2;

HashNode* createHashNode(Student* info) {
	HashNode* node = (HashNode*)malloc(sizeof(HashNode));
	node->info = info;
	node->next = NULL;
	return node;
}

int fHash(const char* key) {
	return key[0] % HASHT_SIZE;
}

void initHashTable(HashNode*** hashTable) {
	if (*hashTable == NULL) {
		(*hashTable) = (HashNode**)malloc(sizeof(HashNode*) * HASHT_SIZE); // or calloc
		memset((*hashTable), NULL, sizeof(HashNode*) * HASHT_SIZE);
	}
}

void putHT(HashNode*** hashTable, Student* stud) {
	if (hashTable == NULL) {
		initHashTable(hashTable);
	}
	HashNode* node = createHashNode(stud);
	int hashValue = fHash(stud->name);
	node->next = (*hashTable)[hashValue];
	(*hashTable)[hashValue] = node;
}

Student* getHT(HashNode** hashTable, const char* name) {
	if (hashTable == NULL) {
		return NULL;
	}

	int hashValue = fHash(name);
	if (hashTable[hashValue] != NULL) {
		HashNode* temp = hashTable[hashValue];
		while (temp) {
			if (strcmp(temp->info->name, name) == 0) {
				return temp->info;
			}
			temp = temp->next;
		}
	}
	return NULL;
}

void deleteHT(HashNode** hashTable, const char* name) {
	if (hashTable == NULL)
		return;

	int hashValue = fHash(name);
	if (hashTable[hashValue] != NULL) {
		HashNode* curr = hashTable[hashValue];
		
		if (strcmp(curr->info->name, name) == 0) {
			hashTable[hashValue] = curr->next;
			deleteStudent(curr->info);
			free(curr);
			return;
		}

		HashNode* prev = hashTable[hashValue];
		curr = hashTable[hashValue]->next;
		while (curr) {
			if (strcmp(curr->info->name, name) == 0) {
				prev->next = curr->next;
				deleteStudent(curr->info);
				free(curr);
			}
			prev = prev->next;
			curr = curr->next;
		}
	}
}

void freeHT(HashNode*** hashTable) {
	for (int i = 0; i < HASHT_SIZE; i++) {
		HashNode* temp = (*hashTable)[i];
		while (temp) {
			HashNode* temp2 = temp;
			temp = temp->next;
			
			deleteStudent(temp2->info);
			free(temp2);
		}
		(*hashTable)[i] = NULL;
	}
	free((*hashTable));
}