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
-separation(const User *user1,const User *user2): find the minimum degree of separation between two users. 
- dump_data(): Print each user and the user's list of friends. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "amigonet.h"
#include "queueADT.h"
/*
#ifndef _QUEUE_IMPL_
#define _QUEUE_IMPL_
#endif
typedef struct QueueNode{
	void *data;
	struct QueueNode *next;	
}QueueNode;

typedef struct QueueADT{
	int (*comparison)(const void*a,const*b);
	struct QueueNode *initial;
}*QueueADT;
#include "queueADT.h"
*/
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

/*		// save the next user
		Node *userNext = user->next;

		// clear user's friend's list
		
		// start from the first person in user's friend's list	
		Node *userFriends = user->data->amigos->head;

		// save the next user's friend
		//Node *userFriendsNext = userFriends->data->amigos->head->next;
		Node *userFriendsNext = userFriends->next;

		while(userFriends != NULL) {
			//Node *temp1 = userFriendsNext;
i			free(userFriends);
			userFriends = userFriendsNext;
		}
		// set the next node
		//Node *temp2 = userNext;
		free(user);
		user = userNext;
*/		Node *temp1 = user;
		
		Node *userFriends = temp1->data->amigos->head;
		while(userFriends != NULL) {
			Node *temp2 = userFriends;
			userFriends = userFriends->next;
			//free(temp2->data->amigos);
			//free(temp2->data);
			free(temp2);
		}
		user = user->next;
		//free(user->data->amigos);
		//free(user->data);
		free(temp1);		
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
	
	dump_data();
	// make empty friend's list
	Friends empty = (Friends) malloc(sizeof(Friends));
	empty->numFriends = 0;
	empty->head = NULL;
	// make user structure
	User* user = (User*) malloc(sizeof(User));
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
	Node *ptrNode = graph->linkedlist->head;
	while(ptrNode != NULL) {
		if( ptrNode->data->name == name ) {
			return ptrNode->data;
		}
		ptrNode = ptrNode->next;	
	}
	return NULL;
}

/**
 * Add a friend (the "amigo") to the user. This should be a two-way
 * addition. If the two users are already friends, this function 
 * does nothing.
 */
void addAmigo(User *user, User *amigo) {
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
	Node *ptrNode1 = user->amigos->head;
	
	Node *ptrNode2 = ex_amigo->amigos->head;
	// check the head first
	if (ptrNode1->data->name == ex_amigo->name) {
		// remove from user's friend list
		// set the head to next
		user->amigos->head = ptrNode1->next;
		free(ptrNode1);
		user->amigos->numFriends-=1;

		// remove from ex_amigo's friend list
		ex_amigo->amigos->head = ptrNode2->next;
		free(ptrNode2);
		ex_amigo->amigos->numFriends-=1;
		return;
		//continue;
	}

	// do middle
	Node *prev1 = ptrNode1;
	Node *curr1 = ptrNode1->next;
	
	while(curr1 != NULL) {
		if(prev1->data->name == user->name) {
			user->amigos->head = ptrNode1->next;
			user->amigos->numFriends-=1;
			free(curr1);
			break;
		}
		// if ptrNode matches name of ex_amigo
		if(curr1->data->name == ex_amigo->name) {
			// remove from user's friend list
			prev1->next = curr1->next;
			free(curr1);
			user->amigos->numFriends-=1;
			break;	
		}
/*		// do end case
		if( curr1->next == NULL && curr1->data->name == ex_amigo->name) {
			prev1->next = curr1->next;
			free(curr1);
			user->amigos->numFriends-=1;
			printf("%s\n","endcase!");
		}*/
		prev1 = prev1->next;
		curr1 = curr1->next;
	}
	Node *prev2 = ptrNode2;
	Node *curr2 = ptrNode2->next;

	while(curr2 != NULL) {
		if(prev2->data->name == user->name) {
			ex_amigo->amigos->head = ptrNode2->next;
			ex_amigo->amigos->numFriends-=1;
			free(curr2);
			break;
		}
		if(curr2->data->name == user->name) {
			// remove from ex_amigo's friend list
			prev2->next = curr2->next;
			free(curr2);
			ex_amigo->amigos->numFriends-=1;
			break;
			printf("%s","should have removed here!");
		}
		printf("%s\n","second case!");
/*		if (curr2->next == NULL && curr2->data->name == user->name) {
			prev2->next = curr2->next;
			free(curr2);
			user->amigos->numFriends-=1;
			printf("%s\n","endcase!");
		}*/
		prev2 = prev2->next;
		curr2 = curr2->next;
	}
}

/**
 * Helper function to search a user in the visited list(queue)
 */
bool search(QueueADT queue, const User *user) {
/*
	QueueNode *ptrNode = queue->initial;
	while(ptrNode != NULL) {
		if(((User*)(ptrNode->data)) == user) {
			printf("%s\n", "worked!");
			return true;
		}
		printf("%s\n","inside the bool search");
		ptrNode = ptrNode->next;
	}
*/
	return false;
}

/**
 * Determine the minimum degree of separation between two users.
 * A user is degree 0 from him/her self. If user a is degree n from 
 * user b, then user a is at most degree n+1 from user b's friends.
 * If the users are no connected by a chain of friends, this 
 * functions return -1.
 */
size_t separation( const User *user1, const User *user2 ) {
/*	// initialize queue (create with NULL to do FIFO)
	QueueADT queue; // queue of vertices to visit;
	//int v; 	// current vertex
	//int i; // counter
	queue = que_create(NULL);
	// make a queue which is the visited link (a linked list)
	QueueADT visitedQueue;
	visitedQueue = que_create(NULL);
	int depth = 0;
	//User *currUser = user1;
	// add user1 to the visited
	//visited[visitcount] = user1;
	// enqueue user1 as root to queue
	que_insert(queue,((void*) user1));
	// enqueue user1 to the visited
	que_insert(visitedQueue,((void*)user1));
	// while queue is not empty
	while(!que_empty(queue)){
		// dequeue an item from queue
		User *current = que_remove(queue);
		// mark item as visited
		// add to visited list
		//visitcount+=1;
		if( current == user2 ) {
			printf("User: %s\n", current->name);
			return depth; 
		}
		
		//if (search(visitedQueue,current)) {
		//	printf("Found: %s",user2->name);
		//}
		// look through the current's friend list
		Node *ptrNode = current->amigos->head;
		while(ptrNode != NULL ) {
			// if node is not in visited list
			if (search(visitedQueue,ptrNode->data) == false) {
				que_insert(visitedQueue,ptrNode->data);
				que_insert(queue,ptrNode->data);
				printf("%s\n","inside search");
				
			}
			printf("%s\n","Looking through friend list");
//			if( ptrNode->data->name == user2->name ) {
//				return visitcount;
//			}
			ptrNode = ptrNode->next;
		}
		depth+=1;
	}
	que_destroy(queue);
	que_destroy(visitedQueue);
*/
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
	// iterate through linked list of users
	Node *ptrNode = graph->linkedlist->head;
	while(ptrNode != NULL) { 
		printf("User <%s>; friends: ",ptrNode->data->name);
		
		// iterate through user's list of friends
		Node *ptrNodeFriends = ptrNode->data->amigos->head;
		while(ptrNodeFriends != NULL) {
			printf("<%s> ",ptrNodeFriends->data->name);
			ptrNodeFriends = ptrNodeFriends->next;
		}
		ptrNode = ptrNode->next;
		printf("\n");
	}
}

/*
int main() {
	create_amigonet();
	addUser("Bob");
	addUser("Phil");
	addUser("Jacky");
	addUser("Kate");
	addUser("David");
	addUser("Bob");
	User* userNode1 = findUser("Bob");
	User* userNode2 = findUser("Phil");
	User* userNode3 = findUser("Jacky");
	User* userNode4 = findUser("Kate");
	User* userNode5 = findUser("David");
	addAmigo(userNode1,userNode2);
	//addAmigo(userNode1,userNode3);
	//addAmigo(userNode1,userNode4);
	//addAmigo(userNode1,userNode5);
	addAmigo(userNode2,userNode3);
	addAmigo(userNode3,userNode4);
	addAmigo(userNode4,userNode5);
	dump_data();
	
	printf("Separation between %s and %s is: %zd\n", userNode1->name, userNode1->name, separation(userNode1,userNode1));
	printf("Separation between %s and %s is: %zd\n", userNode1->name, userNode2->name, separation(userNode1,userNode2));
	printf("Separation between %s and %s is: %zd\n", userNode1->name, userNode3->name, separation(userNode1,userNode3));
	printf("Separation between %s and %s is: %zd\n", userNode1->name, userNode4->name, separation(userNode1,userNode4)); 
	
	printf("%s\n","----------------------------------------------------");
	removeAmigo(userNode1,userNode2);
	removeAmigo(userNode2,userNode3);
	removeAmigo(userNode3,userNode4);
	removeAmigo(userNode4,userNode5);
	dump_data();
	//destroy_amigonet();
}*/
