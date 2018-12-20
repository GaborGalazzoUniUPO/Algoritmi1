
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GOOD_HASH

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

unsigned long student__hash(void *st, int i, int M)
{
    student_t *student = (student_t *)st;
    
    #ifdef GOOD_HASH
    char* str = student->mat;
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return (hash + i) % M;
    #else
    int c = 0;
    for (int i = 0; i < strlen(student->mat); i++)
    {
        c += student->mat[i];
    }
    return (c + i) % M;
    #endif
    
   
    
}

unsigned long student__2hash(void *st, int i, int M)
{
    
    return (student__hash(st,0, M) + i*(1 + (student__hash(st,0,M-2)))) % M;
    
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

double benchmark_hashtl(int n, int m, char *in_filename, char* t_out)
{
    FILE *infile = fopen(in_filename, "rt");
    if (infile == NULL)
    {
        perror("ERRORE APERTURA FILE in");
        exit(EXIT_FAILURE);
    }

    FILE *t_outf = fopen(t_out, "wt");
    if (t_outf == NULL)
    {
        perror("ERRORE APERTURA FILE t_out");
        exit(EXIT_FAILURE);
    }

    hashtl_t hashtl = hashtl__make(m);

    list_t students = list__init();
    int i;
    for (i = 0; i < n && !feof(infile); i++)
    {
        student_t *student = student__read(infile);
        hentry_t *entry = hentry__make(student->mat, student);
        hashtl__insert(hashtl, m, entry, student__hash);
        list__insert(student, &students);
    }
    if (i < n)
        n = i;

    hashtl__print(hashtl, m, t_outf, "%s");

    fprintf(t_outf, "DATA: ------------\n");

    list_t next = students;
    int hits_l = 0;
    while (next != NULL)
    {
        student_t *student = next->inf;
        int hits = hashtl__search_bm(hashtl, m, student->mat, student__hash, streq);
         fprintf(t_outf, "%d\n", hits);
        hits_l += hits;
        next = next->next;
    }

    //LIBERO LA MEMORIA
    hashtl__destroy(hashtl, m, student_entry__destroy);
    while (!list__is_empty(students))
        list__remove(&students);

    fclose(infile);
    fclose(t_outf);

    return (double)hits_l/(double)n;
        

}

double benchmark_hashtsl(int n, int m, char *in_filename, char* t_out)
{
    FILE *infile = fopen(in_filename, "rt");
    if (infile == NULL)
    {
        perror("ERRORE APERTURA FILE in");
        exit(EXIT_FAILURE);
    }

    FILE *t_outf = fopen(t_out, "wt");
    if (t_outf == NULL)
    {
        perror("ERRORE APERTURA FILE t_out");
        exit(EXIT_FAILURE);
    }

    hashtsl_t hashtsl = hashtsl__make(m);

    list_t students = list__init();
    int i;
    for (i = 0; i < n && !feof(infile); i++)
    {
        student_t *student = student__read(infile);
        hentry_t *entry = hentry__make(student->mat, student);
        hashtsl__insert(hashtsl, m, entry, student__hash);
        list__insert(student, &students);
    }
    if (i < n)
        n = i;

    hashtsl__print(hashtsl, m, t_outf, "%s");

    fprintf(t_outf, "DATA: ------------\n");

    list_t next = students;
    int hits_l = 0;
    while (next != NULL)
    {
        student_t *student = next->inf;
        int hits = hashtsl__search_bm(hashtsl, m, student->mat, student__hash, streq);
        fprintf(t_outf, "%d\n", hits);
        hits_l += hits;
        next = next->next;
    }

    //LIBERO LA MEMORIA
    hashtsl__destroy(hashtsl, m, student_entry__destroy);
    while (!list__is_empty(students))
        list__remove(&students);

         fclose(infile);
    fclose(t_outf);

    return (double)hits_l/(double)n;
        

}

double benchmark_hashtsl2h(int n, int m, char *in_filename, char* t_out)
{
    FILE *infile = fopen(in_filename, "rt");
    if (infile == NULL)
    {
        perror("ERRORE APERTURA FILE in");
        exit(EXIT_FAILURE);
    }

    FILE *t_outf = fopen(t_out, "wt");
    if (t_outf == NULL)
    {
        perror("ERRORE APERTURA FILE t_out");
        exit(EXIT_FAILURE);
    }

    hashtsl_t hashtsl = hashtsl__make(m);

    list_t students = list__init();
    int i;
    for (i = 0; i < n && !feof(infile); i++)
    {
        student_t *student = student__read(infile);
        hentry_t *entry = hentry__make(student->mat, student);
        hashtsl__insert(hashtsl, m, entry, student__2hash);
        list__insert(student, &students);
    }
    if (i < n)
        n = i;

    hashtsl__print(hashtsl, m, t_outf, "%s");

    fprintf(t_outf, "DATA: ------------\n");

    list_t next = students;
    int hits_l = 0;
    while (next != NULL)
    {
        student_t *student = next->inf;
        int hits = hashtsl__search_bm(hashtsl, m, student->mat, student__hash, streq);
        fprintf(t_outf, "%d\n", hits);
        hits_l += hits;
        next = next->next;
    }

    //LIBERO LA MEMORIA
    hashtsl__destroy(hashtsl, m, student_entry__destroy);
    while (!list__is_empty(students))
        list__remove(&students);

         fclose(infile);
    fclose(t_outf);

    return (double)hits_l/(double)n;
        

}


int main(int argc, char *argv[])
{

    if (argc != 4)
    {
        fprintf(stderr, "Uso: %s in_file out_file table_dim\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int table_dim = atoi(argv[3]);

   

    FILE *out = fopen(argv[2], "wt");
    if (out == NULL)
    {
        perror("ERRORE APERTURA FILE out");
        exit(EXIT_FAILURE);
    }

    fprintf(out, "alpha,avg_lc,avg_sl,avg_sl2h\n");

    for(double d = 0.5; d<1; d+=0.1){
        
        char *t_out = malloc(80*sizeof(char));
        int len = 80*sizeof(char);
        snprintf(t_out, len, "%s~%.1lf~%s.dat", argv[1], d, "avg_lc");
        double avg_lc = benchmark_hashtl(table_dim*d,table_dim, argv[1],t_out);
        snprintf(t_out, len, "%s~%.1lf~%s.dat", argv[1], d, "avg_sl");
        double avg_sl = benchmark_hashtsl(table_dim*d,table_dim, argv[1],t_out);
        snprintf(t_out, len, "%s~%.1lf~%s.dat", argv[1], d, "avg_sl2h");
        double avg_sl2h = benchmark_hashtsl2h(table_dim*d,table_dim, argv[1],t_out);
        fprintf(out, "%.1lf,%.2lf,%.2lf,%.2lf\n", d, avg_lc, avg_sl,avg_sl2h);
        
    }

    fclose(out);
    return 0;
}