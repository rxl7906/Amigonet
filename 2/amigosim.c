/*
 * amigosim.c
 * $Revision: 1.7 $
 *
 * Simulate AmigoNet activity by reading actions from a text file.
 *
 * James Heliotis
 *
 * COMMAND FORMATS:
 * register <name>
 * friend <name1> <name2>
 * separation <name1> <name2>
 * unfriend <name1> <name2>
 * dump
 *
 * Comment lines begin with "#".
 * They are echoed in the output, but otherwise ignored.
 *
 * This module is currently input format error - intolerant, although
 * it will detect illegal command names..
 */

#include <stdio.h>
#include <string.h>

// #define DEBUG
#define onlyNotNull(name,ans) \
    if (!ans) { \
        fprintf(stderr,"%s does not exist.\n",name); \
        return; \
    }

#include "amigonet.h"

static const char REGISTER[] = "register";
static const char FRIEND[] = "friend";
static const char UNFRIEND[] = "unfriend";
static const char SEPARATION[] = "separation";
static const char DUMP[] = "dump";

#define MAX_LEN 100 // This big for comments

/*************************************************************
 *                                                           *
 * Calls to the AmigoNet API                                 *
 *                                                           *
 *************************************************************/

void do_register( const char *name ) {
    addUser( name );
}

void do_friend( const char *name1, const char *name2 ) {
    User *user1 = findUser( name1 );
    onlyNotNull(name1,user1)
    User *user2 = findUser( name2 );
    onlyNotNull(name2,user2)
    addAmigo( user1, user2 );
}

void do_unfriend( const char *name1, const char *name2 ) {
    User *user1 = findUser( name1 );
    onlyNotNull(name1,user1)
    User *user2 = findUser( name2 );
    onlyNotNull(name2,user2)
    removeAmigo( user1, user2 );
}

void do_separation( const char *name1, const char *name2 ) {
    User *user1 = findUser( name1 );
    onlyNotNull(name1,user1)
    User *user2 = findUser( name2 );
    onlyNotNull(name2,user2)
    printf( "Separation between %s and %s is %ld.\n", name1, name2,
            separation( user1, user2 ) );
}

void do_dump() {
    dump_data();
}

/*************************************************************
 *                                                           *
 * Command input loop                                        *
 *                                                           *
 *************************************************************/

int main() {
    create_amigonet();
    char line[ MAX_LEN ];
    char *result, *cmd, *arg1, *arg2;
    while ( ( result = fgets( line, MAX_LEN, stdin ) ) ) {
	//printf("%s\n","WHERE IS IT?!!");
        if ( line[ 0 ] == '#' ) {
            printf( "%s", line );
        }
        else {
	//	printf("%s\n","ENTER ELSE CASE");
            #ifdef DEBUG
            printf( "->%s", line );
            #endif
            cmd = strtok( line, " \n" );
	//	printf("%s\n","GETTING DEEPTER");
            if ( strcmp( cmd, REGISTER ) == 0 ) {
	//	printf("%s\n","IN REGISTER");
                arg1 = strtok( NULL, " \n" );
                do_register( arg1 );
            }
            else if ( strcmp( cmd, FRIEND ) == 0 ) {
	//	printf("%s\n","IN FRIEND");
                arg1 = strtok( NULL, " \n" );
                arg2 = strtok( NULL, " \n" );
                do_friend( arg1, arg2 );
            }
            else if ( strcmp( cmd, UNFRIEND ) == 0 ) {
	//	printf("%s\n","IN UNFRIEND");
                arg1 = strtok( NULL, " \n" );
                arg2 = strtok( NULL, " \n" );
                do_unfriend( arg1, arg2 );
            }
            else if ( strcmp( cmd, SEPARATION ) == 0 ) {
	//	printf("%s\n","IN SEPARATION");
                arg1 = strtok( NULL, " \n" );
                arg2 = strtok( NULL, " \n" );
                do_separation( arg1, arg2 );
            }
            else if ( strcmp( cmd, DUMP ) == 0 ) {
                do_dump();
            }
            else {
                fprintf( stderr, "Illegal command \"%s\"\n", line );
            }
	//	printf("%s\n","right after many if else cases");
        }
    }
    destroy_amigonet();
}

