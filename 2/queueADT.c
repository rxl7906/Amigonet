/*
Author: Robin Li
Homework: #6 - Abstract Data Type
File: queueADT.c
Description:
- Construct the Queue Abstract Data Type. 
	- Use QueueNode to represent data at each index of the queue
- Create the queue using a predefined comparison routine
- Helper Functions: 
	- freeNode- recursively free nodes in queue until empty
	- addNode - recursively add nodes until there is no next node
- que_empty - indicates if queue is empty
- que_clear - remove all contents from the queue
- que_destroy - tear down and deallocate queue
- que_insert - insert specified data into queue in appropriate place
- que_remove - indicate whether queue is empty or not
*/
#include <stdio.h>
#include <stdlib.h>

#ifndef _QUEUE_IMPL_

#define _QUEUE_IMPL_
#endif
typedef struct QueueNode{
	void *data;
	struct QueueNode *next;
}QueueNode;

typedef struct QueueADT{
	int (*comparison)(const void*a, const void*b);
	struct QueueNode *initial;
}*QueueADT;

#include "queueADT.h"

/*
Create a QueueADT which uses the supplied function as a comparison routine.

The comparison function takes two void* parameters, and returns an integer
result which indicates the relationship between the two things:
Result	Relationship
======	============
 < 0	a < b
 = 0	a == b
 > 0	a > b

where ">" and "<" are dependent upon the data being compared

@param cmp the address of the comparison function to be used for ordering
this queue, or NULL if standard FIFO behavior is desired
@return a pointer to a QueueADT, or NULL if the allocation fails
*/
QueueADT que_create( int (*cmp)(const void*a, const void*b) ) {
	// allocate memory block for queue
	QueueADT queue = malloc(sizeof(QueueADT));

	// add the cmp attribute to the queue to create predefined queue structure
	queue->comparison = cmp;
	return queue;	
}

/*
Helper Function
Free Node to remove all contents from each node recursively until 
the last node. 
*/
void freeNode(QueueNode * node) {
	if(!node->next){ // if there is no next node
		free(node); // free the current node and return
		return;
	} else { // recursively free nodes until you hit base case
		freeNode(node);
	}
}

/*
Indicate whether or not the supplied Queue is empty

@param the QueueADT to be tested
@return true if the queue is empty, otherwise false
*/
bool que_empty( QueueADT queue ) {
	if ( !queue->initial ) { // if there is no initial node
		return true; // return true that queue is empty
	} else { // if there is initial node
		return false; // return false
	}
}



/*
Remove all contents from the supplied QueueADT.

@param queue - the QueueADT to be manipulated
*/
void que_clear( QueueADT queue) {
	if ( que_empty( queue) ) { // check if queue is empty
		return; // return if queue is empty
	} else { // if queue is not empty
		freeNode(queue->initial); // free nodes in the queue
		queue->initial=NULL; // set initial node to null
	}
}

/*
Tear down and deallocate the supplied QueueADT

@param queue - the QueueADT to be manipulated
*/
void que_destroy( QueueADT queue) {
	que_clear( queue ); // remove all contents of the queue
	free( queue ); // deallocate the queue
}

/*
Helper Function
Recursively add nodes to the queue until there is no next node.
*/
void addNode( QueueNode* currentNode, QueueNode* newNode) {
	if(!currentNode->next){ // if there is no next node
		currentNode->next=newNode; // add the last node
		return;
	} else {
		addNode(currentNode->next,newNode); // recursively add nodes
	}
}

/*
Insert the specified data into the Queue in the appropriate place

Uses the queue's comparison function to deteremine the appropriate place
for the insertion.

@param queue the QueueADT into which the value is to be inserted
@param data the data to be inserted
@exception If the value cannot be inserted into the queue for
whatever reason (usually implementation-dependent), the program
should terminate with an error message. This can be done by
printing an appropriate message to the standard error output and
then exiting with EXIT_FAILURE, or by having an assert() fail.
*/
void que_insert( QueueADT queue, void *data) {
	// allocate memory block and create node
	QueueNode* node = malloc(sizeof(QueueNode));
	node->data = data; // add data attribute to node
	node->next = NULL; // add null to next node
	
	if(que_empty(queue)){ // if queue is empty
		queue->initial = node; // set initial node to new node with data
		return;
	}
	//addNode(queue->initial,node);
	
	if (!queue->comparison) { // if queue has no comparison 
		addNode(queue->initial,node); // add nodes in no particular order
		return;	
	}

	// inserted node becomes the initial node in the queue
	if(queue->comparison(data,queue->initial->data) <= 0) {
		QueueNode* previousNode = queue->initial; // create node with initial
		queue->initial = node; // set initial node to inserted node
		node->next = previousNode; // set next node to be previous node
		return;
	}

	QueueNode * lastNode = queue->initial; // set to initial node
	QueueNode * currentNode = lastNode->next; // set to node after initial
	while(true) { 
		if(!lastNode->next) { // if there is no next node
			// set last node's next to inserted node
			lastNode->next = node;
			break; 
		}
		// insert node in between last node and current node
		if(queue->comparison( data, currentNode->data) <= 0) {
			node->next = currentNode; // set node's next to current node
			lastNode->next = node; // set lastNode's next to node
			break;
		}
		// iterate moving through the queue until you hit if statements
		lastNode = currentNode;
		currentNode = currentNode->next;
	}
	return;
}	

/*
Remove and return the first element from the QueueADT.

@param queue the QueueADT to be manipulated
@return the value that was removed from the queue
@exception If the queue is empty, the program should terminate
with an error message. This can be done by printing an 
appropriate message to the standard error output and then 
exiting with EXIT_FAILURE, or by having an assert() fail.
*/
void *que_remove( QueueADT queue) {
	QueueNode * removedNode; // create node
	void * returnData; // make void pointer

	if(que_empty( queue)) { // if the queue is empty, you can't remove
		exit(EXIT_FAILURE);
	}

	returnData = queue->initial->data; // hold initial's data
	removedNode = queue->initial; // hold initial node
	queue->initial = removedNode->next; // set initial node to node after initial
	free(removedNode); // deallocate memory space of removedNode
	return returnData; // return removedNode's data
}
