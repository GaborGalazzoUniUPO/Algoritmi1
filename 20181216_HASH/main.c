
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_DIM 80

// funzione per leggere una riga dal file di testo ed eliminarel il \n finale

void fgets2(char *s, int size, FILE *stream) {
    char* e = fgets(s, size, stream);
    if (e == NULL){
        perror("ERRORE LETTURA FILE");
        exit(EXIT_FAILURE);
    }
	s[strlen(s)-1]= '\0';
}

// STUDENT 

typedef struct {
    char* mat;
    char* name;
    char* surname;
} student_t;

student_t* student__make(char* mat, char* name, char* surname){
    student_t* student = malloc(sizeof(student_t));
    strcpy(student->mat, mat);
    strcpy(student->name, name);
    strcpy(student->surname, surname);
    return student;
}

student_t *student__read (FILE *stream) {
	char mat[30], name[60], surname[60];

	fgets2(mat, 29, stream);
	fgets2(name, 59, stream);
	fgets2(surname, 59, stream);

	return student__make(mat, name, surname);
}

int student__hash(student_t student, int i, int N){
    
}

int main(int argc, char* argv[]){

    if(argc!=2){
        fprintf(stderr, "Uso: %s nome_file", argv[0]);
        exit(EXIT_FAILURE);
    }

    hashtl_t hashtl = hashtl__make(TABLE_DIM);

    FILE* fp = fopen(argv[1], "rt");
    if(fp == NULL){
        perror("ERRORE APERTURA FILE");
        exit(EXIT_FAILURE);
    }

    while(!feof(fp)){
        student_t* student = student__read(fp);
        hentry_t* entry = hentry__make(student->mat, student);
        hashtl__insert(hashtl, TABLE_DIM, entry,entry, NULL );
    }


    hashtl__print(hashtl,TABLE_DIM, stdout, "%d");

    fclose(fp);

    return 0;
}