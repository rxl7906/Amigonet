


#include <stdio.h>
#include <stdlib.h>

#include "amigonet.h"
#include "queueADT.h"
// linked list of users which is visited list
// 

bool search(QueueADT queue, const User *user) {
	QueueNode *ptrNode = queue->initial; 
	while(ptrNode != NULL) {
		if(ptrNode->data == user){
			printf("%s\n","worked!");
		}
	}
	
}
