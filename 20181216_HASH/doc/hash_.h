#include <stdio.h>

#define A 0.618033989


// definizione delle strutture dati

typedef struct bucket_lista {
   long int id;
   char nome[60];
   char cognome[60];
   struct bucket_lista *next;
} bucket_lista; // struttura che definisce il contenuto di un bucket da gestire con liste concatenate

typedef struct bucket {
   long int id;
   char nome[60];
   char cognome[60];
} bucket; // struttura che definisce il contenuto di un bucket da gestire con indirizzamento aperto

void fgets2(char *s, int size, FILE *stream);

// funzioni per la gestione di una tavola di hash con lista concatenata

int h (long int k, int i, int N);
bucket_lista **newTable_lista(int N);
void freeTable_lista (bucket_lista **T);
bucket_lista *newBucket_lista (long int id, char *nome, char *cognome);
int hash_insert_lista(bucket_lista **T, bucket_lista *b, int N);
bucket_lista *hash_search_lista(bucket_lista **T, long int k, int N);


// funzioni per la gestione di una tavola di hash con indirizzamento aperto

int hd (long int k, int i, int N);
bucket **newTable(int N);
void freeTable (bucket **T);
bucket *newBucket (long int id, char *nome, char *cognome);
int hash_insert(bucket **T, bucket *b, int N);
int hash_search(bucket **T, long int k, int N);

// funzioni per il caricamento di uno studente da file

bucket_lista *loadNextStudent_lista (FILE *stream);
bucket *loadElementAt (FILE *stream);