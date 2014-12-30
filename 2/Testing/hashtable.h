/*
hashtable.h - header file for hashtable.c
*/

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "amigonet.h"
typedef struct LinkedList {
	User *head;
}LinkedList;

typedef struct hash_table {
	int size; /* size of hashtable */
	list **table; /* table elements */
} hash_table;

// create hash table
void create_hash_table();

// hash function
unsigned int hash(char *str);


