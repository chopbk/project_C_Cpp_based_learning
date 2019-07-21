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
//@des: hash fucntion
static int ht_hash(const char* s, const int prime_num, const int hash_size)
//@des: double hashing function
static int ht_get_hash(
    const char *s, const int num_buckets, const int attempt
);

//Define hash funtions API
//@des: This function insert a new key-value pair
void ht_insert(ht_hash_table* ht, const char* key, const char* value);
//@des: This function search a key value in hash tables
char* ht_search(ht_hash_table* ht, const char* key);
//@des: This function delete a key value in hash tables
void ht_delete(ht_hash_table* h, const char* key);