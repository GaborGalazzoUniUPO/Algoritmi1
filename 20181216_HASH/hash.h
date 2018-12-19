
#include "../shared/list_stack_queue.h"
#include <stdbool.h>
#include <stdio.h>


typedef list_t* hashtl_t;

typedef struct h_entry{
    void* key;
    element_t value;
} hentry_t;

hashtl_t hashtl__make(int dim);

void hashtl__print(hashtl_t hashtl, int dim, FILE* fp, char* key_format);
void hashtl__insert(hashtl_t hashtl, int dim, hentry_t* entry, int (*hash)(void *));
element_t hashtl__search(hashtl_t hashtl, int dim, void* key, int (*hash)(void *), bool (*keq)(void*, void*));

hentry_t* hentry__make(void* key, void* value);
void hashtl__destroy(hashtl_t hashtl, int dim, void (*destroy)(hentry_t*));





typedef void** hasht_t;
hasht_t hasht__make(int dim);
void hasht__insert(void* elem, void* key, int (hash)(void *));