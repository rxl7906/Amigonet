Project2: Graph Manipulations 
Author: Robin Li
AmigoNet
------------------------------------------------------------------------
FILES SUBMITTED:
- amigonet.c
- queueADT.c
- queueADT.h
- README.txt
------------------------------------------------------------------------
DATA STRUCTURE:
The AmigoNet uses a linked list of linked lists. The linked list is all 
the users in the "social network". Each user has their own linked list 
which is essentially their friend list. 
------------------------------------------------------------------------
FUNCTION DESCRIPTIONS:
-create_amigonet(): Initializes the system with some memory allocated.
-destroy_amigonet(): Shuts down the system by freeing all the memory 
allocated.
-addUser(const char *name): Add a new user initially with no friends. 
-findUser(const char *name): Locate a user structure using "name" 
parameter.
-addAmigo(User *user,User *amigo): Take two users and make them friends. 
-removeAmigo(User *user,User *ex_amigo): "Un-friend" two users. 
-separation(const User *user1,const User *user2): find the minimum 
degree of separation between two users. Breadth-first search and a 
queueADT is implemented. 
- dump_data(): Print each user and the user's list of friends. 
------------------------------------------------------------------------
ATTENTION GRADER:
- All the functions are implemented except for "destroy_amigonet". 
There are memory leaks/not everything is freed.
- There are commented out print statements which are very helpful for
anyone doing tests. That's why they were kept in the source code.
- The queueADT.c and queueADT.h files there to give the separation
function a queue to use. 
------------------------------------------------------------------------
SEPARATION USES:
Structure: 
1) "typedef struct AmigoNode"
Functions:
1) "static AmigoNode amig_create(const User *user, size_t distance)"
2) "bool search(QueueADT queue, const User *user)"
3) "void printNode(QueueADT queue)"
4) "void printHelp(QueueNode *node)"
5) "size_t separation(const User *user1, const User *user2)"
------------------------------------------------------------------------
DESIGN:
- The functions in the "FUNCTION DESCRIPTIONS" uses functions made in the
amigonet.c file, the only exception is the separation function. 
- The separation function is implemented using the "queueADT.c and 
queueADT.h" files along with the 5 functions and 1 structure mentioned
above. 
------------------------------------------------------------------------
WARNINGS:
- The first two warnings are related and it refers to the usage of 
strcpy. The function "addUser" takes in "const char*name" parameter while
the "user->name" takes in "char *" while the "const" causes the warning.
The second warning repeats the "const" problem. (LINE 109)(amigonet.c)

- The last warning is related to the amig_create where the first argument
is a "const User *user" which uses "const" and the "node->user" takes in
a "User" structure. (LINE 314)(amigonet.c)
------------------------------------------------------------------------
OVERVIEW:
AmigoNet maintains a collection of users that have friend ("amigo") connections between them. It is loosely based on some elementary features in a system like Facebook or Linkedin. Some Operations that are supported as connecting ("friending") and disconnecting ("un-friending") users, as well as determining the distance, or degrees of separation between two uesrs. 
