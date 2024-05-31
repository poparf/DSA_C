#pragma once
#include "DataUtil.h"
// LIFO
typedef struct Stack {
	struct Student* data;
	struct StackNode* next;
} StackNode;

StackNode* createNode(Student* data) {
	StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

// pop()
Student* pop(StackNode** stack) {
	if ((*stack != NULL)) {
		StackNode* temp = (*stack);
		(*stack) = (*stack)->next;
		Student* retVal = (*stack)->data;
		free(temp);
		return retVal;
	}
}


// push(item)
void push(StackNode** stack, Student* s) {
	StackNode* newNode = createNode(s);
	if ((*stack) == NULL) {
		(*stack) == newNode;
	}
	else {
		newNode->next = (*stack);
		(*stack) = newNode;
	}
}


// peek()
Student* peek(StackNode* stack) {
	if (stack) {
		return stack->data;
	}
}



// isEmpty()
int isEmpty(StackNode* stack) {
	return stack == NULL ? 1 : 0;
}


// 3.1 pag 98 Three in one: Describe houw could you use a single array
// to implement three stacks


typedef struct ArrayStack {
	int* array;
	int size;
	// each stack has a cap of n/3 elements
	// this would be static in the context of a class
	// indexes where the stacks start in the main array
};

typedef struct ThreeStacks {
	struct ArrayStack* stacks;
	int indexes[3]; // this way that s static cause we modify only values inside 
	// array stack
};


// 32. Stack min: How would you design a stack in which, in addition to push
// and pop, has a function min which returns the min element ?
// push pop and min should all operate in O(1) time

// each stack node should keep track of the minimum element when it was
// pushed in the stack

typedef struct MinStackNode {
	int val;
	int min;
	struct MinStackNode* next;
} MinStackNode;


void pushMinStackNode(MinStackNode** node, int newVal) {
	if ((*node)->min > newVal) {
		MinStackNode* newNode = (MinStackNode*)malloc(sizeof(MinStackNode));
		newNode->min = newVal;
		newNode->next = (*node);
		newNode->val = newVal;
		(*node) = newNode;
	}
	else {
		MinStackNode* newNode = (MinStackNode*)malloc(sizeof(MinStackNode));
		newNode->min = (*node)->min;
		newNode->next = (*node);
		newNode->val = newVal;
		(*node) = newNode;
	}
}


/*
* 3.3 Stack of Plates: Imagine a (literal) stack of plates.
If the stack gets too high, it might topple.
Therefore, in real life, we would likely start a 
new stack when the previous stack exceeds some
threshold. Implement a data structure SetOfStacks 
that mimics this. SetO-fStacks should be
composed of several stacks and should create a new
stack once the previous one exceeds capacity.
SetOfStacks. push() and SetOfStacks. pop() should
behave identically to a single stack
(that is, pop () should return the same values
as it would if there were just a single stack).
FOLLOW UP
Implement a function popAt ( int index) which performs a pop operation on a specific sub-stack.
Hints:#64, #87 
*/

typedef struct SetOfStacks {
	int data[10];
	int size;
	struct SetOfStacks* next;
} SetOfStacks;

SetOfStacks* createSetOfStack() {
	SetOfStacks* stack = (SetOfStacks*)malloc(sizeof(SetOfStacks));
	stack->next = NULL;
	stack->size = 0;
	return stack;
}


void pushInSet(SetOfStacks** stacks, int val) {
	if ((*stacks) == NULL) {
		(*stacks) = createSetOfStack();
		(*stacks)->data[(*stacks)->size++] = val;
	}
	else {
		if ((*stacks)->size < 10) {
			(*stacks)->data[(*stacks)->size++] = val;
		}
		else if ((*stacks)->size = 10) {
			SetOfStacks* newStack = createSetOfStack();
			newStack->next = (*stacks);
			(*stacks) = newStack;
			newStack->data[newStack->size++] = val;
		}
	}
}


int popAt(SetOfStacks** stacks, int stackIndex) {
	if ((*stacks)) {
		SetOfStacks* trav = (*stacks);

		int i = 0;
		while (trav && i++ < stackIndex) {
			trav = trav->next;
		}

		if (i != stackIndex) {
			return;
		}

		
		int retVal = trav->data[trav->size--];

		if (trav->size == 0) {
			SetOfStacks* trav2 = (*stacks);
			while (trav2->next != trav) {
				trav2 = trav2->next;
			}

			trav2->next = trav->next;
			free(trav);
		}
		return retVal;

	}
}



// Queue via Stacks: Implement a MyQueue class which implements a queue using two stacks. 



//Sort Stack : Write a program to sort a stack such that the smallest items are on the top.You can use
//an additional temporary stack, but you may not copy the elements into any other data structure
//(such as an array).The stack supports the following operations : push, pop, peek, and is Empty.
//Hints : # 15, #32, #43


// nu e complet
void sortStack(StackNode** stack) {
	StackNode* tempStack = NULL;

	Student* maxIncomeStud;
	maxIncomeStud->income = 0;
	int noElements;
	for (int i = 0; i < noElements; i++)
	{
		do{
			Student* temp = pop(stack);
			if (temp->income > maxIncomeStud->income) {
				maxIncomeStud = temp;
			}
			push(&tempStack, temp);
		} while (!isEmpty(tempStack));
		push(stack, maxIncomeStud);
	}
}

















