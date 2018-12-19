#include "hash.h"
#include <stdlib.h>

//TABELLE HASH CON LISTE DI COLLISIONE

hashtl_t hashtl__make(int dim){
    hashtl_t hashtl = malloc(dim*sizeof(list_t));
    for(int i = 0; i<dim; i++)
        hashtl[i] = list__init();
    return hashtl;
}

hentry_t* hentry__make(void* key, void* value){
    hentry_t* e = malloc(sizeof(hentry_t));
    e->key = key;
    e->value = value;
    return e;
}

void hashtl__destroy(hashtl_t hashtl, int dim,  void (*destroy)(hentry_t*)){
    for(int i = 0; i<dim; i++){
        while(!list__is_empty(hashtl[i])){
            hentry_t* e = list__remove(&hashtl[i]);
            destroy(e);
            free(e);
        }
    }
    free(hashtl);
}

void hashtl__insert(hashtl_t hashtl, int dim,  hentry_t* entry, int (*hash)(void *)){
    int index = hash(entry->key) %dim ;
    list__insert(entry, &hashtl[index]);
}

element_t hashtl__search(hashtl_t hashtl, int dim,  void* key, int (*hash)(void *), bool (*keq)(void*, void*)){
    int index = hash(key) % dim;
   
    list_t list = hashtl[index];
    while(list != NULL){
        hentry_t* entry = list->inf;
        if(keq(entry->key,key))
            return entry->value;
        list = list->next;
    }
    return NULL;
}

void hashtl__print(hashtl_t hashtl, int dim,  FILE* fp, char* key_format){
    for(int i = 0; i<dim; i++){
        fprintf(fp, "[%d] -> ", i);
        list_t list = hashtl[i];
        while(list != NULL){
            hentry_t* entry =  list->inf;
            fprintf(fp, "(k: ");
            fprintf(fp, key_format, entry->key);
            fprintf(fp, ") -> ");
        }
        fprintf(fp, "NULL\n");
    }
}

//TABELE HASH CON INDIRIZZAMENTO APERTO

hasht_t hasht__make(int dim){
    hasht_t hasht = malloc(dim*sizeof(void*));
    for(int i = 0; i<dim; i++)
        hasht[i] = NULL;
    return hasht;
}
