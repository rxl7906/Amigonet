/*
hashtable.c 
*/

hash_table *create_hash_table(){

    int size = 100;	  
    //if (size<1) return NULL; /* invalid size for table */
  	
    /* Attempt to allocate memory for the table structure */
    hash_table hashtable = (hash_table*) malloc(sizeof(hash_table)*size);    

    hashtable->size = size;
    /* Attempt to allocate memory for the table itself */
    LinkedList* linkedList = (LinkedList*) malloc(sizeof(LinkedList));
    hashtable->table = linkedList;
    return hashtable;
}

unsigned int hash(hash_table *hashtable, char *str)
{
    unsigned int hashval;
    
    /* we start our hash out at 0 */
    hashval = 0;

    /* for each character, we multiply the old hash by 31 and add the current
     * character.  Remember that shifting a number left is equivalent to 
     * multiplying it by 2 raised to the number of places shifted.  So we 
     * are in effect multiplying hashval by 32 and then subtracting hashval.  
     * Why do we do this?  Because shifting and subtraction are much more 
     * efficient operations than multiplication.
     */
    for(; *str != '\0'; str++) hashval = *str + (hashval << 5) - hashval;

    /* we then return the hash value mod the hashtable size so that it will
     * fit into the necessary range
     */
    return hashval % hashtable->size;
}
/*
LinkedList *lookup_string(hash_table hashtable, char *str)
{
    LinkedList *list;
    unsigned int hashval = hash(hashtable, str);

    // Go to the correct list based on the hash value and see if str is
     // in the list.  If it is, return return a pointer to the list element.
     // If it isn't, the item isn't in the table, so return NULL.
     //
    for(list = hashtable->table[hashval]; list != NULL; list = list->next) {
        if (strcmp(str, list->str) == 0) return list;
    }
    return NULL;
}*/

void add_string(char *str)
{
    LinkedList *new_list;
    //list *current_list;
    unsigned int hashval = hash(hashtable, str);

    /* Attempt to allocate memory for list */
    //if ((new_list = malloc(sizeof(list_t))) == NULL) return 1;
    new_list = malloc(sizeof(LinkedList));
    /* Does item already exist? */
    //current_list = lookup_string(hashtable, str);
        /* item already exists, don't insert it again. */
    //if (current_list != NULL) return 2;
    /* Insert into list */
    new_list->string = str;
    //new_list->next = NULL;
    //hashtable->table[hashval] = new_list;
}
/*
void free_table(hash_table_t *hashtable)
{
    int i;
    list_t *list, *temp;

    if (hashtable==NULL) return;

    // Free the memory for every item in the table, including the 
    // strings themselves.
     
    for(i=0; i<hashtable->size; i++) {
        list = hashtable->table[i];
        while(list!=NULL) {
            temp = list;
            list = list->next;
            free(temp->str);
            free(temp);
        }
    }

    // Free the table itself 
    free(hashtable->table);
    free(hashtable);
}
*/
int main() {
	add_string("Bob");
	//add_string("Kelsey");
	//add_string("Kate");
	//lookup_string("Bob");
	//lookup_string("Kelsey");
	//lookup_string("Kate");
}
