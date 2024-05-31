#pragma once
#include "ListUtil.h"

typedef struct StackNode {
	struct Student* info;
	struct StackNode* next;
}StackNode, *PStackNode;

StackNode* createNodeStack(Student* stud) {
	StackNode* newStud = (StackNode*)malloc(sizeof(StackNode));
	newStud->info = stud;
	newStud->next = NULL;
	return newStud;
}

void push(StackNode** stack, Student* info) 
{
	StackNode* node = createNodeStack(info);
	/*if (*stack == NULL)
		*stack = node;
	else
	{
		node->next = (*stack);
		(*stack) = node;
	}*/

	node->next = (*stack);
	*stack = node;
}

Student* pop(StackNode** stack) {
	if ((*stack) == NULL)
		return NULL;

	Student* tempInfo = (*stack)->info;
	StackNode* tempNode = (*stack);

	(*stack) = tempNode->next;
	free(tempNode);

	return tempInfo;
}

Student* peek(StackNode** stack) {
	Student* tempInfo = NULL;
	if ((*stack) != NULL)
		tempInfo = (*stack)->info;
	return tempInfo;
}

void deleteStack(StackNode** stack) {
	while ((*stack) != NULL) {
		Student* info = pop(stack);
		printStudent(info);
		deleteStudent(info);
	}
}

void printStack(StackNode** stack) {
	// Another stack implementation
	StackNode* tempStack = NULL;
	if ((*stack) != NULL) {
		while ((*stack) != NULL) {
			Student* info = pop(stack);
			printStudent(info);
			push(&tempStack, info);
		}

		while (tempStack != NULL) {
			Student* info = pop(&tempStack);
			push(stack, info);
		}
	}

	// Another array implementation
	/*Student** studArray = (Student*)malloc(sizeof(Student*) * 2);
	int studArraySize = 2;
	int idx = 0;


	if ((*stack) != NULL) {
		while ((*stack) != NULL) {
			if (idx == studArray) {
				Student** studArray2 = (Student*)malloc(sizeof(Student*) * studArraySize * 2);
				for (int i = 0; i < studArraySize; i++)
					(*studArray2)[i] = (*studArray)[i];

				free(studArray);
				studArray = studArray2;
			}

			Student* info = pop(stack);
			studArray[idx++] = info;
		}

		for (int i = studArraySize; i > 0; i--) {
			push(&stack, studArray[i]);
		}

	}*/

}

// homework

// check if 2 lists are mirrored
int areMirrored(ListNode** s1, ListNode** s2) {
	StackNode* reversedS1 = NULL;
	
	ListNode* traversal = *s1;
	while (traversal) {
		push(&reversedS1, traversal->info);
		traversal = traversal->next;
	}
	
	ListNode* traversal2 = *s2;
	while (reversedS1 && traversal2) {
		Student* temp = pop(&reversedS1);
		if (temp->income != traversal2->info->income ||
			temp->reference.extRef != traversal2->info->reference.extRef ||
			strcmp(temp->name, traversal2->info->name) != 0) {
			// If any of the corresponding elements don't match, return false
			return 0;
		}
		traversal2 = traversal2->next;
	}

	return 1;

}


bool checkIfMirrored(ListNode* list1, ListNode* list2) {
	StackNode* stack = NULL;
	ListNode* aux = list1;
	while (aux) {
		push(&stack, aux->info);
		aux = aux->next;
	}
	while (peek(&stack) != NULL) {
		Student* info = pop(&stack);
		if (list2 == NULL || (list2 != NULL && info != list2->info))
			return false;
		list2 = list2->next;
	}

	return true;
}
