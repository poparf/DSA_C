#pragma once
// Heap - a specialized tree-based data structure that satisfies the property:
// if A is parent for B then between the values of A and B a semantic relation of total order is applied\
// A binary-heap is a complete binary tree which can be linearized

// A maximum value or minimum value is always accessible with O(1) complexity time

/*
* Stacks - the newest task
* Queues - the oldest task
* Priority
* Queues - the most urgent
*/

#include "DataUtil.h"

#define PQueue_SIZE 7

typedef struct PQueue {
	Student** items;
	int size;
	int position;
}PriorityQueue, PQueue;


//void ReheapUp(PQueue* pQueue) {
//	int i = pQueue->position;
//	while (pQueue->items[i]->income > pQueue->items[i / 2]->income) {
//		Student* temp = pQueue->items[i];
//		pQueue->items[i] = pQueue->items[i / 2];
//		pQueue->items[i / 2] = temp;
//		i = i / 2;
//	}
//}

void ReheapUp(Student** items, int currentIndex)
{
	if (currentIndex > 0)
	{
		int parentIndex = (currentIndex - 1) / 2;
		if (items[parentIndex]->income < // max heap
			items[currentIndex]->income)
		{
			Student* aux = items[parentIndex];
			items[parentIndex] = items[currentIndex];
			items[currentIndex] = aux;
			ReheapUp(items, parentIndex);
		}
	}
}

void enqueue(PQueue* pQueue, Student* info) {
	if ((*pQueue).items == NULL) {
		(*pQueue).items = (Student**)malloc(sizeof(Student*) * PQueue_SIZE);
		memset((*pQueue).items, 0, sizeof(Student*) * PQueue_SIZE);
		(*pQueue).size = PQueue_SIZE;
	}

	if ((*pQueue).size > (*pQueue).position) {
		(*pQueue).items[(*pQueue).position] = info;
		ReheapUp((*pQueue).items, (*pQueue).position);
		(*pQueue).position++;
	}
}


void ReheapDown(PQueue* pQueue, int parentIndex) {
	int leftChildIndex = 2 * parentIndex + 1;
	int rightChildIndex = 2 * parentIndex + 2;

	int maxIndex = parentIndex;
	if (leftChildIndex < pQueue->position) {
		if (pQueue->items[leftChildIndex]->income > pQueue->items[parentIndex]->income)
			maxIndex = leftChildIndex;
		if (rightChildIndex < pQueue->position &&
			pQueue->items[rightChildIndex]->income > pQueue->items[parentIndex]->income)
			maxIndex = rightChildIndex;
		
		if (maxIndex != parentIndex)
		{
			Student* temp = pQueue->items[parentIndex];
			pQueue->items[parentIndex] = pQueue->items[maxIndex];
			pQueue->items[maxIndex] = temp;
			ReheapDown(pQueue, maxIndex);
		}
	}
	//while (leftChildIndex < pQueue->position) {
	//	if (pQueue->items[leftChildIndex] < pQueue->items[rightChildIndex] &&
	//		pQueue->items[parentIndex] < pQueue->items[leftChildIndex]) {

	//		//just a swap..
	//		Student* temp = pQueue->items[parentIndex];
	//		pQueue->items[parentIndex] = pQueue->items[leftChildIndex];
	//		pQueue->items[leftChildIndex] = temp;
	//		parentIndex = leftChildIndex;
	//	
	//	}
	//	else if (pQueue->items[parentIndex] < pQueue->items[rightChildIndex]) {
	//		Student* temp = pQueue->items[parentIndex];
	//		pQueue->items[parentIndex] = pQueue->items[rightChildIndex];
	//		pQueue->items[rightChildIndex] = temp;
	//		parentIndex = rightChildIndex;
	//	}
	//	else {
	//		break;
	//	}
	//}

}

Student* deque(PQueue* pQueue) {
	
	Student* result = NULL;
	if (pQueue->position > 0) {
		result = pQueue->items[0];
		pQueue->items[0] = pQueue->items[pQueue->position - 1];
		pQueue->position--;
		ReheapDown(pQueue, 0);
	}

	return result;
}

// homework
// lower to higher or higher to lower
void changePriority(PQueue *pQueue, const char* nameSearched, float newIncome) {
	// the priority is based on income
	// so if we change the income and reheapify of the root is simple
	/*Student* stud = deque(pQueue);
	stud->income = newIncome;
	enqueue(pQueue, stud);
*/
	// if we want to change a specific student in the heap the time complexity is O(n)
	// but using a heap we can take it to O(logn)
	// let's say we search based on name
	for (int i = 0; i < pQueue->position; i++) {
		if (strcmp(pQueue->items[i]->name, nameSearched) == 0) {
			pQueue->items[i]->income = newIncome;
			if (i > 0 && pQueue->items[i]->income > pQueue->items[(i - 1) / 2]->income) {
				ReheapUp(pQueue->items, i);
			}
			else {
				ReheapDown(pQueue, i);
			}
			return;
		}
	}
}



//
//int pop() {
//    if (heap_.size() == 1) {
//        // Normally we would throw an exception if heap is empty.
//        return -1;
//    }
//    if (heap_.size() == 2) {
//        int res = heap_[heap_.size() - 1];
//        heap_.pop_back();
//        return res;
//    }
//
//    int res = heap_[1];
//    // Move last value to root
//    heap_[1] = heap_[heap_.size() - 1];
//    heap_.pop_back();
//    int i = 1;
//    // Percolate down
//    while (2 * i < heap_.size()) {
//        if (2 * i + 1 < heap_.size() &&
//            heap_[2 * i + 1] < heap_[2 * i] &&
//            heap_[i] > heap_[2 * i + 1]) {
//            // Swap right child
//            int tmp = heap_[i];
//            heap_[i] = heap_[2 * i + 1];
//            heap_[2 * i + 1] = tmp;
//            i = 2 * i + 1;
//        }
//        else if (heap_[i] > heap_[2 * i]) {
//            // Swap left child
//            int tmp = heap_[i];
//            heap_[i] = heap_[2 * i];
//            heap_[2 * i] = tmp;
//            i = 2 * i;
//        }
//        else {
//            break;
//        }
//    }
//    return res;
//}