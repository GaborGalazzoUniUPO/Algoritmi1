
#include "../shared/list_stack_queue.h"
#include <stdbool.h>
#include <stdio.h>


typedef list_t* hashtl_t;

// TIPO DIZIONARIO

typedef struct h_entry{
    void* key;
    element_t value;
} hentry_t;

hentry_t* hentry__make(void* key, void* value);

//TABELLE HASH CON LISTE DI COLLISIONE
hashtl_t hashtl__make(int dim);
void hashtl__print(hashtl_t hashtl, int dim, FILE* fp, char* key_format);
void hashtl__insert(hashtl_t hashtl, int dim, hentry_t* entry, unsigned long (*hash)(void *, int i, int M));
element_t hashtl__search(hashtl_t hashtl, int dim, void* key, unsigned long (*hash)(void *, int i, int M), bool (*keq)(void*, void*));
int hashtl__search_bm(hashtl_t hashtl, int dim, void* key, unsigned long (*hash)(void *, int i, int M), bool (*keq)(void*, void*));


void hashtl__destroy(hashtl_t hashtl, int dim, void (*destroy)(hentry_t*));




//TABELLE HASH CON SCANSIONE LINEARE - INDIRIZZAMENTO APERTO
typedef hentry_t** hashtsl_t;
hashtsl_t hashtsl__make(int dim);
void hashtsl__print(hashtsl_t hashtsl, int dim, FILE* fp, char* key_format);
void hashtsl__insert(hashtsl_t hashtsl, int dim, hentry_t* entry, unsigned long (*hash)(void *, int i, int M));
element_t hashtsl__search(hashtsl_t hashtsl, int dim, void* key, unsigned long (*hash)(void *, int i, int M), bool (*keq)(void*, void*));
int hashtsl__search_bm(hashtsl_t hashtsl, int dim, void* key, unsigned long (*hash)(void *, int i, int M), bool (*keq)(void*, void*));
void hashtsl__destroy(hashtsl_t hashtsl, int dim, void (*destroy)(hentry_t*));