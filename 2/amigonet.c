/*
Author: Robin Li
Project 2: Graph Manipulations
File: amigonet.c
Description:
This project is a study of the operations needed for a centralized social network.
People can register as new users and can connect ("friending") and disconnect ("unfriending"). Also determining the distance between two users is known as the degrees of separation. 

Data Structure:
-This project uses a linked list of linked lists. The linked list is all the users in the "social network". Each user has their own linked list which is essentially their friend list. 

Function Descriptions:
-create_amigonet(): Initializes the system with some memory allocated.
-destroy_amigonet(): Shuts down the system by freeing all the memory allocated.
-addUser(const char *name): Add a new user initially with no friends. 
-findUser(const char *name): Locate a user structure using "name" parameter.
-addAmigo(User *user,User *amigo): Take two users and make them friends. 
-removeAmigo(User *user,User *ex_amigo): "Un-friend" two users. 
-separation(const User *user1,const User *user2): find the minimum degree of separation between two users. Breadth-first search and a queueADT is implemented. 
- dump_data(): Print each user and the user's list of friends. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strcmp

#include "amigonet.h"
#include "queueADT.h"

// User node in the linked list
typedef struct Node Node;
struct Node {
	User *data; // user struct
	Node *next; // next node
};

// Represent a linked list which is a user's friend list
typedef struct Friends_struct { 
	int numFriends; // number of friends of the user
	Node *head; // first friend a user has 
}Friends_struct;

// Represent a graph. 
typedef struct Graph {
	int size; // number of users in the graph
	Friends_struct *linkedlist; // all the users in the graph
}Graph;

static Graph *graph; // make graph static so it can be seen thruout this file

/**
 * Initialize the system.
 * (This is where some memory is initially allocated.)
 */
void create_amigonet() {
	graph = (Graph*) malloc(sizeof(Graph));
	graph->size = 0;	
	graph->linkedlist = (Friends_struct*) malloc(sizeof(Friends_struct));
}

/**
 * Shut down the system.
 * (This is where a bunch of memory is freed.)
 */
void destroy_amigonet() {
	// get the first user and free his friend list then free him
	Node *user = graph->linkedlist->head;
	while(user != NULL) {
		Node *temp1 = user;
		//printf("%s\n","Looking thru user's friend list");
		// loop thru thru user's friend list
		Node *userFriends = temp1->data->amigos->head;
		while(userFriends != NULL) {
			Node *temp2 = userFriends;
			userFriends = userFriends->next;
			//free(temp2->data->amigos); // free user's friend list struct
			//free(temp2->data->name); // free user's name
			//free(temp2->data); // free user's user struct
			free(temp2); // free user node
		}
		//printf("%s\n","Finished looking thru user's friend list");
		user = user->next; // move to next user
		//free(temp1->data->amigos); // free user's friend list struct
		//free(temp1->data->name); // free user's name
		//free(temp1->data); // free user's user struct
		free(temp1); // free user node
	}	
}

/**
 * Add a new user initially with no friends.
 * The parameter 'name' is use to initialize the new user entry.
 * Note: it must be copied to prevent the caller from changing
 * the name later.
 * If the name already exists, then this function does nothing.
 */
void addUser(const char*name) {
	// check if name already exists
	if(findUser(name) != NULL){
		//printf("%s already exists!\n",name);
		return;
	}
	// make empty friend's list
	Friends empty = (Friends) malloc(sizeof(Friends));
	empty->numFriends = 0;
	empty->head = NULL;
	// make user structure
	User* user = (User*) malloc(sizeof(User));
	user->name = (char *) malloc(sizeof(char *));
	strcpy(user->name, name);
	//user->name = name;
	user->amigos = empty;
	// make user node
	Node *userNode = (Node*) malloc(sizeof(Node));
	userNode->data = user;
	userNode->next = NULL;

	// add user to graph
	if (graph->size == 0) { // if no body is in the graph
		graph->linkedlist->head = userNode;
		graph->size+=1;
	} else { // if there are users already in the graph
		Node *ptr = graph->linkedlist->head;
		while(ptr->next != NULL) {
			ptr = ptr->next;
		}
		ptr->next = userNode;
		graph->size+=1;
	}
}

/**
 * Locate a user structure using the user's name as a key.
 * User structures are needed for the addAmigo, remove Amigo,
 * and separation functions.
 * If the user does not exist, NULL is returend.
 */
User *findUser( const char *name ) {
	Node *ptrNode = graph->linkedlist->head; // first user in graph
	while(ptrNode != NULL) { // loop thru all users in the graph
		if(strcmp(ptrNode->data->name,name) == 0){ // find user in graph
			return ptrNode->data; // return that user
		}
		ptrNode = ptrNode->next; // set new ptrNode
	}
	return NULL;
}

/**
 * Add a friend (the "amigo") to the user. This should be a two-way
 * addition. If the two users are already friends, this function 
 * does nothing.
 */
void addAmigo(User *user, User *amigo) {
	// check if the user  exist
	if(findUser(user->name) != NULL){
		//printf("%s is registered!\n",user->name);
	} else { // if the user doesn't exist
		return; // do nothing
	}
	// check if amigo exists
	if(findUser(amigo->name) != NULL){
		//printf("%s is registered!\n",amigo->name);
	} else { // if the amigo doesn't exist
		return; // do nothing
	}
	
	// if the user is already friends with amigo do nothing
	// check if you can find amigo in user's friend list 

	// start from user's head friend list
	Node *amigoNode = user->amigos->head;
	while(amigoNode != NULL) { // look thru user's friend list
		// check if amigoNode has amigo's name
		if(strcmp(amigoNode->data->name,amigo->name) == 0) {
			return; // enter if statement, then do nothing
		}
		amigoNode = amigoNode->next;
	}
	
	// user get's a new friend!
	Node *newFriend1 = (Node*) malloc(sizeof(Node));
	newFriend1->data = amigo;
	newFriend1->next = NULL;

	// amigo get's a new friend!
	Node *newFriend2 = (Node*) malloc(sizeof(Node));
	newFriend2->data = user;
	newFriend2->next = NULL;

	// if user's linked list has no head (if he has no friends)
	if(user->amigos->head == NULL) {
		user->amigos->head = newFriend1;
		// increase his number of friends
		user->amigos->numFriends+=1;
	} else { // if user's linked list has more than one friend
		Node *ptrNode = user->amigos->head;
		
		while(ptrNode->next != NULL) {
			ptrNode = ptrNode->next;
		}
		ptrNode->next = newFriend1;
		user->amigos->numFriends+=1;
	}

	// if amigo's linked link has no head (if he has no friends)
	if(amigo->amigos->head == NULL) {
		amigo->amigos->head = newFriend2;
		// increase his number of friends
		amigo->amigos->numFriends+=1;
	} else{ // if amigo's linked list has more than one friend
		Node *amigoptrNode = amigo->amigos->head;
		
		while(amigoptrNode->next != NULL) {
			amigoptrNode = amigoptrNode->next;
		}
		amigoptrNode->next = newFriend2;
		amigo->amigos->numFriends+=1;
	}
}

/**
 * "Un-friend" two users. This is, again, a two-way operation.
 * If the two users were not friends, this function does nothing.
 */
void removeAmigo( User *user, User *ex_amigo) {
	// find user's friend(ex_amigo)
	// access user's friend list first

	// user's first friend in friend list
	Node *ptrNode1 = user->amigos->head;
	
	// ex_amigo's first friend in first list
	Node *ptrNode2 = ex_amigo->amigos->head;

	// if removing the head of friend list (linked list)
	if (ptrNode1->data->name == ex_amigo->name) {
		// remove from user's friend list
		// set user's linked list head to next
		user->amigos->head = ptrNode1->next;
		free(ptrNode1);
		user->amigos->numFriends-=1;

		// remove from ex_amigo's friend list
		// set ex_amigo's linked list head to next
		ex_amigo->amigos->head = ptrNode2->next;
		free(ptrNode2);
		ex_amigo->amigos->numFriends-=1;
		return;
	}
		
	Node *prev1 = ptrNode1; // previous node
	Node *curr1 = ptrNode1->next; // current node

	// if removing the middle section of user's friend list (linked list)
	while(curr1 != NULL) {
		// if ptrNode1 matches name of user
		if(prev1->data->name == user->name) {
			user->amigos->head = ptrNode1->next;
			user->amigos->numFriends-=1;
			free(curr1);
			break;
		}
		// if ptrNode1 matches name of ex_amigo
		if(curr1->data->name == ex_amigo->name) {
			// remove from user's friend list
			prev1->next = curr1->next;
			user->amigos->numFriends-=1;
			free(curr1);
			break;	
		}

		prev1 = prev1->next;
		curr1 = curr1->next;
	}

	Node *prev2 = ptrNode2; // previous node
	Node *curr2 = ptrNode2->next; // current node
	
	// if removing the middle section of ex_amigo's friend list (linked list)
	while(curr2 != NULL) {
		// if ptrNode2 matches name of user
		if(prev2->data->name == user->name) {
			ex_amigo->amigos->head = ptrNode2->next;
			ex_amigo->amigos->numFriends-=1;
			free(curr2);
			break;
		}
		// if ptrNode2 matches name of ex_amigo
		if(curr2->data->name == user->name) {
			// remove from ex_amigo's friend list
			prev2->next = curr2->next;
			free(curr2);
			ex_amigo->amigos->numFriends-=1;
			break;
		}
		prev2 = prev2->next;
		curr2 = curr2->next;
	}
}

/**(Used for separation function)
 * Queue node data structure to keep track of the distance from source
 */
typedef struct AmigoNode{
	User *user;
	size_t distance;
} *AmigoNode;

/**(Used for separation function)
 * Create AmigoNode(queue nodes) to put in the queue
 */
static AmigoNode amig_create(const User *user, size_t distance) {
	AmigoNode node = (AmigoNode) malloc(sizeof(struct AmigoNode));
	node->user = user;
	//strcpy(node->user->name,user->name);
	node->distance = distance;
	return node;
}

/**(Used for separation function)
 * Helper function to search a user in the visited list(queue)
 */
bool search(QueueADT queue, const User *user) {
        QueueNode *ptrNode = queue->initial;
        while(ptrNode != NULL) {
                if(((AmigoNode)(ptrNode->data))->user == user) {
                        //printf("Searching %s\n", user->name); // print test
                        return true;
                }
                ptrNode = ptrNode->next;
        }
        return false;
}

/**(Used for separation function)
 * This is a test function to print all the nodes in the queue.
 * To use this function uncomment the printHelp function in the else.
 */
void printNode(QueueADT queue) {	
	if ( que_empty( queue) ) { // check if queue is empty
		return; // return if queue is empty
	} else { // if queue is not empty
		//printHelp(queue->initial); // print nodes in the queue
	}
}

/**(Used for separation function)
 * Helper function to recursively print all the nodes in the queue. 
 */
void printHelp(QueueNode *node) {
	if(!node->next){ // if there is no next node
		printf("%s  ", ((AmigoNode) node->data)->user->name); // print the current node and return
		return;
	} else { // recursively print nodes until you hit base case
		printHelp(node);
	}
}
/**(Separation function: uses a Breadth-First Search with a queueADT to implement a   * queue for the BFS to use. The visited list also uses a queueADT.)
 * Determine the minimum degree of separation between two users.
 * A user is degree 0 from him/her self. If user a is degree n from 
 * user b, then user a is at most degree n+1 from user b's friends.
 * If the users are no connected by a chain of friends, this 
 * functions return -1.
 */
size_t separation( const User *user1, const User *user2 ) {	
	// initialize queue (create with NULL to do FIFO)
	QueueADT queue;
	queue = que_create(NULL);
	// make a queue which is the visited link (a linked list)
	QueueADT visitedQueue;
	visitedQueue = que_create(NULL);
	
	// make initial node struct to put in both queues with distance 0 from source
	AmigoNode visitNode = amig_create(user1, 0);
	// enqueue user1 to queue
	que_insert(queue,( visitNode));
	// enqueue user1 to visitedQueue (add to visited list)
	que_insert(visitedQueue,(visitNode));

	while(!que_empty(queue)){ // while queue is not empty
		//printNode(queue); // uncomment this to print the queue

		AmigoNode current = que_remove(queue); // dequeue from queue
		if(current->user ==  user2) { // check if you found user2
			size_t separation = current->distance; // track the distance
			que_destroy(queue); // destroy the queue
			//que_destroy(visitedQueue);
			return separation;
		}
		//printf("Looking thru %s's friend list\n",current->user->name);
		// look through the current's friend list
		Friends_struct *ptrNode = current->user->amigos; // friend list
		Node *friend = ptrNode->head; // head of friend list

		// look thru friend list
		for(int i = 0; i < ptrNode->numFriends; i++) { 	
			// if node is not in visited list			
			if (search(visitedQueue,friend->data) == false) {
				size_t temp = (current->distance) +1;
				AmigoNode enqueueNode = amig_create(friend->data,temp);
				// add to visited list
				que_insert(visitedQueue,enqueueNode);
				// enqueue to queue
				que_insert(queue,enqueueNode);
			}
			friend = friend->next; // set new head
		}
		//printf("not in %s's friend list\n",current->user->name);
	}
	//printf("Queue is empty!\n");
	que_destroy(queue);
	//que_destroy(visitedQueue);
	return -1;
}
/**
 * For each user, print on standard output the user's name, and a list
 * of that user's friends.
 * The function ouputs an empty line at the beginning and at the end. 
 * FORMAT OF EACH LINE:
 * User <username>; friends: <friendname1> ... <friendnameN>
 */
void dump_data(){
	// loop through linked list of users
	Node *ptrNode = graph->linkedlist->head;
	while(ptrNode != NULL) { 
		printf("User %s; friends: ",ptrNode->data->name);
		
		// loop through user's list of friends
		Node *ptrNodeFriends = ptrNode->data->amigos->head;
		while(ptrNodeFriends != NULL) {
			printf("%s ",ptrNodeFriends->data->name);
			ptrNodeFriends = ptrNodeFriends->next;
		}
		ptrNode = ptrNode->next;
		printf("\n");
	}
}

