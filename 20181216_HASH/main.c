
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// funzione per leggere una riga dal file di testo ed eliminarel il \n finale

void fgets2(char *s, int size, FILE *stream)
{
    char *e = fgets(s, size, stream);

    if (e == NULL)
    {
        perror("ERRORE LETTURA FILE");
        exit(EXIT_FAILURE);
    }
    s[strlen(s) - 1] = '\0';
}

// STUDENT

typedef struct
{
    char mat[30];
    char name[60];
    char surname[60];
} student_t;

student_t *student__make(char *mat, char *name, char *surname)
{
    student_t *student = malloc(sizeof(student_t));
    strcpy(student->mat, mat);
    strcpy(student->name, name);
    strcpy(student->surname, surname);
    return student;
}

student_t *student__read(FILE *stream)
{
    char mat[30], name[60], surname[60];

    fgets2(mat, 29, stream);
    fgets2(name, 59, stream);
    fgets2(surname, 59, stream);

    return student__make(mat, name, surname);
}

int student__hash(void *st)
{
    student_t *student = (student_t *)st;
    int c = 0;
    for (int i = 0; i < strlen(student->mat); i++)
    {
        c += student->mat[i];
    }
    return c;
}

void student_entry__destroy(hentry_t* e){
    free(e->value);
}

//BENCHMARK

bool streq(void *a1, void *a2)
{
    char *s1 = (char *)a1;
    char *s2 = (char *)a2;
    return strcmp(s1, s2) == 0;
}

void benchmark(int n, int m, FILE *infile)
{
    hashtl_t hashtl = hashtl__make(m);
    hashtsl_t hashtsl = hashtsl__make(m);

    list_t students = list__init();
    int i;
    for (i = 0; i < n && !feof(infile); i++)
    {
        student_t *student = student__read(infile);
        hentry_t *entry = hentry__make(student->mat, student);
        hashtl__insert(hashtl, m, entry, student__hash);
        hashtsl__insert(hashtsl, m, entry, student__hash);
        list__insert(student, &students);
    }
    if (i < n)
        n = i;

    hashtl__print(hashtl, m, stdout, "%s");
    hashtsl__print(hashtsl, m, stdout, "%s");

    list_t next = students;
    while (next != NULL)
    {
        student_t *student = next->inf;
        int hits = hashtl__search_bm(hashtl, m, student->mat, student__hash, streq);
        fprintf(stdout, "%d,", hits);
        hits = hashtsl__search_bm(hashtsl, m, student->mat, student__hash, streq);
        fprintf(stdout, "%d\n", hits);
        next = next->next;
    }

    //LIBERO LA MEMORIA
    hashtl__destroy(hashtl, m, student_entry__destroy);
    hashtsl__destroy(hashtsl, m, student_entry__destroy);
    while (!list__is_empty(students))
        list__remove(&students);
        

}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        fprintf(stderr, "Uso: %s nome_file table_dim\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // int table_dim = atoi(argv[2]);

    FILE *fp = fopen(argv[1], "rt");
    if (fp == NULL)
    {
        perror("ERRORE APERTURA FILE");
        exit(EXIT_FAILURE);
    }

    benchmark(80, 120, fp);
    fclose(fp);
    return 0;
}