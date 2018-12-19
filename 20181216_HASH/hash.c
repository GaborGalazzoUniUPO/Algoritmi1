#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"


// funzione per leggere una riga dal file di testo ed eliminarel il \n finale

void fgets2(char *s, int size, FILE *stream) {
	fgets(s, size, stream);
	s[strlen(s)-1]= '\0';
}



// funzioni per calcolo dell'hash lineare

int h (long int k, int i, int N) {
	return 0;
}


// funzioni per calcolo dell'hash doppio

int h1d (long int k, int N) {
	return 0;
}

int h2d (long int k, int N) {
	return 0;
}

int hd (long int k, int i, int table_dim) {
	return 0;
}



// --------------  LISTE CONCATENATE  ------------------- //

// creazione e rimozione della tabella di hash - liste concatenate

bucket_lista **newTable_lista(int N) {
	bucket_lista **T= (bucket_lista **)calloc (N, sizeof (bucket_lista *));
	return T;
}

void freeTable_lista (bucket_lista **T) {
	free (T);
}

// funzione per la creazione di un nuovo bucket data la sua chiave, il nome e il cognome

bucket_lista *newBucket_lista (long int id, char *nome, char *cognome) {
	bucket_lista *nuovoBucket = (bucket_lista *)malloc (sizeof(bucket_lista));
	if (nuovoBucket == NULL) printf ("ERRORE: mancata allocazione della memoria per il nuovo bucket\n\n");
	else {
		nuovoBucket->id= id;
		strcpy(nuovoBucket->nome, nome);
		strcpy(nuovoBucket->cognome, cognome);
		nuovoBucket->next= NULL;
	}
	return nuovoBucket;
}

// inserimento di un nuovo bucket b, precedentemente creato con la funzione newBucket()

int hash_insert_lista(bucket_lista **T, bucket_lista *b, int N) {
	return 0;
}

// Ricerca di un elemento, dato l'ID

bucket_lista *hash_search_lista(bucket_lista **T, long int k, int N) {
	return NULL;
}



// --------------  INDIRIZZAMENTO APERTO  ------------------- //

// creazione e rimozione della tabella di hash - indirizzamento aperto

bucket **newTable(int N) {
	bucket **T= (bucket **)calloc (N, sizeof (bucket *));
	return T;
}

void freeTable (bucket **T) {
	free (T);
}

// funzione per la creazione di un nuovo bucket data la sua chiave, il nome e il cognome

bucket *newBucket (long int id, char *nome, char *cognome) {
	bucket *nuovoBucket = (bucket *)malloc (sizeof(bucket));
	if (nuovoBucket == NULL) printf ("ERRORE: mancata allocazione della memoria per il nuovo bucket\n\n");
	else {
		nuovoBucket->id= id;
		strcpy(nuovoBucket->nome, nome);
		strcpy(nuovoBucket->cognome, cognome);
	}
	return nuovoBucket;
}

// inserimento di un nuovo bucket b, precedentemente creato con la funzione newBucket()

int hash_insert(bucket **T, bucket *b, int N) {
	return 0;
}


// Ricerca di un elemento, dato l'ID


int hash_search(bucket **T, long int k, int N) {
	return 0;
}


// Funzioni per il caricamento del prossimo studente dal fine in input


bucket_lista *loadNextStudent_lista (FILE *stream) {
	bucket_lista *p;
	long int id;
	char nome[60], cognome[60];

	fscanf(stream, "%li", &id);
	fgets2(nome, 59, stream);
	fgets2(cognome, 59, stream);

	p= newBucket_lista (id, nome, cognome);
	return p;
}

bucket *loadElementAt (FILE *stream) {
	bucket *p;
	long int id;
	char nome[60], cognome[60];

	fscanf(stream, "%li", &id);
	fgets2(nome, 59, stream);
	fgets2(cognome, 59, stream);

	p= newBucket (id, nome, cognome);
	return p;
}
