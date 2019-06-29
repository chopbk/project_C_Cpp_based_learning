#include "hash_table.h"

/*************************define functions************************************** */
/* @des: a function ht_new_item allocates a chunk of memory the size of an ht_item
 * and saves a copy of the strings k and v in the new chunk of memory
 * */
static ht_item *ht_new_item(const char *k, const char *v) {
    ht_item* i = malloc(sizeof(ht_item));
    i->key = strdup(k);
    i->value = strdup(v);
    /*strdup(const char *s) This function returns a pointer to a null-terminated byte 
    string, which is a duplicate of the string pointed to by s. The memory obtained is 
    done dynamically using malloc and hence it can be freed using free().*/
    return i;
}

/*  
 * @des: a function ht_new initialises a new hash table.
 */
ht_hash_table *ht_new() {
    ht_hash_table* ht = malloc(sizeof(ht_hash_table));
    ht->size = HT_INITIAL_BASE_SIZE;
    ht->count = 0;
    ht->items = calloc(ht->size,sizeof(ht_item*));
    return ht;
}

/* 
 * @des: function ht_items and ht_hash_tables,which free the memory we've allocated,
 * so we don't cause memory leaks.
 * */
static void ht_del_item(ht_item* i) {
    free(i->key);
    free(i->value);
    free(i);
}

/* 
 * @des: This function delete a hash table
 * */
void ht_del_hash_table(ht_hash_table* ht) {
    ht_item *item;
    //loop in all pointer items and call ht_del_item()
    for(int i = 0; i < ht->size; i++) {
        item = ht->items[i];
        if(item != NULL) {
            ht_del_item(item);
        }
    }
    free(ht->items);
    free(ht);
}