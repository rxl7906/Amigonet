/*
Author: Robin Li
Project 2: Graph Manipulations
File: amigonet.c
Description:

*/

#include <stdio.h>
#include <stdlib.h>

#include "amigonet.h"
//#include "hashtable.h"
// Represent an linked list
typedef struct LinkedList {
	User *head; // pointer to head node of list	
}LinkedList;
/*
struct Friends_struct {
	struct User *head;
	struct User *friends;
	
};*/
// Represent a graph. Graph is an array of adjacency lists
typedef struct Graph {
	int size;
	struct LinkedList** array;
}Graph;

static Graph *graph;

// Initialize system (With some memory initially allocated)
void create_amigonet() {
	graph = (Graph*) malloc(sizeof(Graph));
	graph->size = 0;
	//LinkedList* linkedList = (LinkedList*) malloc(sizeof(LinkedList));
	// Create array of adjacency lists.
	graph->array = (LinkedList*) malloc(sizeof(LinkedList));
}
//static int listCount = 0;
// Add a new user
void addUser(const char*name) {
	User* userNode = (User*) malloc(sizeof(User));
	userNode->name = name;
	userNode->amigos = NULL;
	
	//userNode->next = graph->array[count]->head;
	graph->array[graph->size]->head = userNode;
	//listCount+=1;
	graph->size+=1;
}
/*
void addAmigo(User *user, User *amigo) {
	user->amigos->friends = amigo;
	amigo->amigos->friends = user;
	
}*/
// For each user, print on standard output user's name and list of that user's
// friends
void dump_data(){
	for(int i = 0; i < graph->size; i++) {
		User* userNode = graph->array[i]->head;
		printf("Adjaceny list of node %d\n", i);
		printf("%s\n", graph->array[i]->head->name);
		printf("%s\n", userNode->name);
		//while(userNode) {
		//	printf("Friends: %s\n", userNode->amigos[i].friends[i]->name);
			//userNode = 
		//}
		//printf("Friends: %s\n", userNode->amigos[i]
		//printf("Friends: %s\n", graph->array[i].head->amigos->friends[i]->name);
		//printf("head-> %s\n", userNode->name);
		//printf("%s",userNode->amigos->friends->name);
/*		while(userNode) {
			printf("-> %s", userNode->name);
			//pCrawl = pCrawl->next;
		}*/
		//printf("\n");	
	}
	//printf("head->%s\n",graph->array[0].head->name);

	//printf("%d\n", listCount);
}

int main() {
	create_amigonet();
	addUser("Bob");
	addUser("Phil");
	addUser("Jacky");
	//addAmigo(graph->array[0].head,graph->array[1].head);
	dump_data();	
}
