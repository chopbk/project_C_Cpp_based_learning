//hash_table.h
#include <stdlib.h>
#include <string.h>
/************************define const parameter************************************* */
#define HT_INITIAL_BASE_SIZE 53
/**************define data struct****************** */
//key-value pairs (items) will each be stored in a struct
typedef struct {
    char *key;
    char *value;
}ht_item;

/* hash table stores an array of pointers to items,
 * and some details about its size and how full it is: */
typdef struct {
    int size;
    int count;
    ht_item **items;
} ht_hash_table;

/*************************define functions************************************** */
//@des: This function create a new hash_table
ht_hash_table *ht_new();
//@des: This function create a new item in hash_table
static ht_item *ht_new_item(const char *k, const char *v);
//@des: This function delete an item 
static void ht_del_item(ht_item* i);
//@des: This function delete a hash table
void ht_del_hash_table(ht_hash_table* ht) ;