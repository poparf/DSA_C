#pragma once
#include "DataUtil.h"
typedef struct Node
{
	struct Node* prev;
	Student* info;
	struct Node* next;
}ListNode, * PListNode;

ListNode* createNode(Student* stud)
{
	ListNode* node = NULL;
	node = (ListNode*)malloc(sizeof(ListNode));
	node->info = stud;
	node->next = node->prev = NULL;
	return node;
}

void printList(const ListNode* head) {
	printf("\nFrom front to beggining.\n\n");

	while (head->next) {
		printStudent(head->info);
		head = head->next;
	}
	printStudent(head->info);/*
	printf("\n\nReverse order\n\n");
	while (head) {
		printStudent(head->info);
		head = head->prev;
	}*/
}

void printCircularList(ListNode* head) {
	// Check if the list is empty
	if (head == NULL) {
		printf("Empty list\n");
		return;
	}

	// Create a pointer to traverse the list
	ListNode* current = head;

	// Traverse the circular list starting from the head node
	do {
		printStudent(current->info);
		current = current->next;
	} while (current != head); // Stop when we reach the head node again

	printf("\n");
}

void insertTail_DLNode(const ListNode** list, Student* stud) {
	ListNode* newNode = createNode(stud);
	if (*list == NULL) {
		*list = newNode;
		return;
	}
	
	ListNode* traversal = NULL;
	for (traversal = *list; traversal->next != NULL; traversal = traversal->next) {}
	newNode->prev = traversal;
	traversal->next = newNode;
}

void deleteNode(ListNode* node)
{
	if (node != NULL)
	{
		deleteStudent(node->info);
		free(node);
	}
}



//void insertNode(ListNode** list, Student* stud)
//void insertHead_SLNode(PListNode* list, Student* stud)
//{
//	//PListNode node;
//	ListNode* node = createNode(stud);
//	node->next = *list;
//	*list = node;
//}
PListNode insertHead_SLNode(PListNode list, Student* stud)
{
	PListNode node = createNode(stud);
	node->next = list;
	return node;
}

void deleteList(ListNode** list)
{
	while (*list != NULL)
	{
		ListNode* tmp = *list;
		*list = tmp->next;
		printStudent(tmp->info);
		free(tmp->info->name);
		free(tmp->info);
		free(tmp);
	}
}

ListNode* deleteNodeByKey(ListNode* list, const char* key)
{
	
	if(list)
		if (strcmp(list->info->name, key) == 0)
		{
			ListNode* tmp = list;
			list = list->next;
			printStudent(tmp->info);
			free(tmp->info->name);
			free(tmp->info);
			free(tmp);
			return list;
		}
		else
		{
			ListNode* tmp = list;
			while (tmp->next != NULL && strcmp(tmp->next->info->name, key) != 0)
				tmp = tmp->next;
			if (tmp->next != NULL)
			{
				ListNode* aux = tmp->next;
				tmp->next = aux->next; //tmp->next->next;
				deleteNode(aux);
			}
			return list;
		}
	return list;
}

void insertTail_SLNode(ListNode** list, Student* stud) {
	ListNode* node = createNode(stud);
	if (*list == NULL)
		*list = node;
	else
	{
		ListNode* tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}


ListNode* convert(ListNode* list) {
	if (list == NULL)
		return NULL;

	ListNode* traversal = list;

	ListNode* head = NULL;
	ListNode* middleLeft = NULL;
	ListNode* middleRight = NULL;
	ListNode* tail = NULL;

	ListNode* newNode1 = createNode(traversal->info);
	ListNode* newNode2 = createNode(traversal->info);

	newNode1->next = newNode2;
	newNode2->prev = newNode1;
	head = newNode1;
	tail = newNode2;
	head->prev = tail;
	tail->next = head;

	middleLeft = head;
	middleRight = tail;
	traversal = traversal->next;
	while (traversal) {
		ListNode* newNode1 = createNode(traversal->info);
		ListNode* newNode2 = createNode(traversal->info);

		newNode1->next = newNode2;
		newNode2->prev = newNode1;

		middleLeft->next = newNode1;
		newNode1->prev = middleLeft;

		newNode2->next = middleRight;
		middleRight->prev = newNode2;

		middleLeft = newNode1;
		middleRight = newNode2;

		traversal = traversal->next;
	}
	return head;
}

//going through the list only once create a secondary list where the elements are mirrored

ListNode* reverseList(ListNode* head) {
	ListNode* temp = NULL;
	ListNode* newNode = NULL;
	
	while (head) {
		newNode = createNode(head->info);
		newNode->next = temp;
		temp = newNode;
		head = head->next;
	}
	return temp;
}

// convert a simple linked list into a double linked list with minimum time complexity

void convertSL_DL(ListNode* head) {
	/*ListNode* prev = head;
	ListNode* tempHead = head;
	ListNode* curr = head->next;
	while (curr) {
		curr->prev = prev;
		curr = curr->next;
		prev = prev->next;
	}

	prev->next = tempHead;
	tempHead->prev = prev;*/

	ListNode* newHead = NULL;

	while (head) {

		head = head->next;
	}
}

// make it circular

// Concat 2 double circular lists

void convertToCircular(ListNode* head) {
	ListNode* tempHead = head;
	while (head->next) {
		head = head->next;
	}

	head->next = tempHead;
	tempHead->prev = head;
}

ListNode* concatDoubleCircularList(ListNode* head1, ListNode* head2) {
	ListNode* temp = head1->prev;
	head1->prev = head2->prev;
	temp->next = head2;
	head2->prev->next = head1;
	head2->prev = temp;
	return head1;
}

// find the % of extern students
// crapa ca e circular
float getPercentageOfExternStudents(ListNode* head) {
	int sum = 0;
	int ctr = 0;

	ListNode* final = head;

	do{
		if (head->info->reference.extRef >> 15 == 1) {
			sum += 1;
		}
		head = head->next;
		ctr += 1;
	} while (head != final);

	return (float)sum / (float)ctr;
}