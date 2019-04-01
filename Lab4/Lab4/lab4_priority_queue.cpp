/*
Harris Vijayagopal- 20775920
Surya Pandiaraju - 20783404
Tyler Pinto - 20762174
*/


#include "lab4_priority_queue.hpp"
#include<string>
#include <iostream>
using namespace std;

// PURPOSE: Parametric constructor 
// initializes heap to an array of (n_capacity + 1) elements
PriorityQueue::PriorityQueue(unsigned int n_capacity) {
	capacity = n_capacity;
	size = 0;
	heap = new TaskItem*[n_capacity + 1];
}

// PURPOSE: Explicit destructor of the class PriorityQueue
PriorityQueue::~PriorityQueue() {
	for (unsigned int i = 1; i <= size; i++) {
		delete heap[i];
		heap[i] = NULL;
	}
	delete[] heap;
	heap = NULL;

}

// PURPOSE: Returns the number of elements in the priority queue
unsigned int PriorityQueue::get_size() const {
	return size;
}

// PURPOSE: Returns true if the priority queue is empty; false, otherwise
bool PriorityQueue::empty() const {
	if (size == 0)
		return true;
	return false;
}

// PURPOSE: Returns true if the priority queue is full; false, otherwise
bool PriorityQueue::full() const {
	if (size == capacity)
		return true;
	return false;
}

// PURPOSE: Prints the contents of the priority queue; format not specified
void PriorityQueue::print() const {
	for (int i = 0; i < size; i++) {
		TaskItem* curr_item = heap[i];
		cout<< "Priority:|"<< curr_item->priority << "Descrption:|" << curr_item->description << endl;
	}
}

// PURPOSE: Returns the max element of the priority queue without removing it
// if the priority queue is empty, it returns (-1, "N/A")
PriorityQueue::TaskItem PriorityQueue::max() const {
	if (size == 0) {
		TaskItem* blank = new TaskItem(-1, "N/A");
		return *blank;
	}
	return *heap[1];
}

// PURPOSE: Inserts the given value into the priority queue
// re-arranges the elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::enqueue( TaskItem val ) {
	if (size == capacity) {
		return false;
	}
	else if (size == 0) {
		TaskItem* new_val = new TaskItem(val);
		heap[1] = new_val;
	}
	else {
		int i = size + 1;
		heap[i] = new TaskItem(val);
		while (i > 1 && heap[i / 2]->priority < heap[i]->priority) {
			TaskItem* temp = heap[i];
			heap[i] = heap[i / 2];
			heap[i / 2] = temp;
			i /= 2;
		}
	}
	size++;
	return true;

}

// PURPOSE: Removes the top element with the maximum priority
// re-arranges the remaining elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::dequeue() {
	if (size == 0)
		return false;
	else if (size == 1) {
		delete heap[1];
		heap[1] = NULL;
		size--;
		return true;
	}
	else {
		delete heap[1];
		heap[1] = heap[size];
		heap[size] = NULL;
		size--;
		int i = 1;

		while (i * 2+1 <= size) {

			//if left is bigger or equal than right and left is bigger than parent...swap left
			  if (heap[i * 2]->priority >= heap[2 * i + 1]->priority && heap[i * 2]->priority > heap[i]->priority) {
				TaskItem* temp = heap[i];
				heap[i] = heap[i * 2];
				heap[i * 2] = temp;
				i = i * 2;
			}

			//if right is bigger than left and right is better than parent...swap right
			else if (heap[i * 2 + 1]->priority > heap[2 * i]->priority && heap[i * 2 + 1]->priority > heap[i]->priority){
				TaskItem* temp = heap[i];
				heap[i] = heap[i*2+1];
				heap[i * 2+1] = temp;
				i = i * 2+ 1;
			}

		}
		
		//check if last node is a single leaf node
		if (2 * i == size && heap[2*i]->priority > heap[i]->priority) {
			TaskItem* temp = heap[i];
			heap[i] = heap[size];
			heap[size] = temp;
			i = i * 2;
		}

	}
	return true;

}
