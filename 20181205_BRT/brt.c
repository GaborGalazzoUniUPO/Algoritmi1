#include "../shared/brt.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <float.h>

#include <sys/time.h>

/* qsort int comparison function */ 
int int_cmp(const void *a, const void *b) 
{ 
    const int *ia = (const int *)a; // casting pointer types 
    const int *ib = (const int *)b;
    return *ia  - *ib; 
	/* integer comparison: returns negative if b > a 
	and positive if a > b */ 
} 


/************************************************/

void parray(int* array, int dim){
    for(int i = 0; i<dim; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

void pbrt_ord(brtree_t brt){
    if(brt == NULL)
        return;
    pbrt_ord(brt->l);
    printf("%d ", brt->inf.key);
    pbrt_ord(brt->r);
}

/*************************************************/

 int mbsearch(int array[], int n, int x)
 {
    if(n == 0)
        return 0;
    int m = n/2;
    if(x < array[m]){
        return  1 + mbsearch(array, m, x);
    }
    if(x > array[m]){
        return 1 + mbsearch(array+(m+1), n-(m+1), x);
    }
    return 1;
 }

 int bstsearch(brtree_t brt, int needle){
    if(brt == NULL)
        return 0;
    if(needle < brt->inf.key){
        return 1 + bstsearch(brt->l, needle);
    }
    if(needle > brt->inf.key){
        return 1 + bstsearch(brt->r, needle);
    }
    return 1;
 }
/************************************************/

#define MAX 100




void test(int dim, int rtempt){

    srand(time(NULL));

    //Opzione 1: Inizializzazione

    int* archive = malloc(sizeof(int)*dim);
    btree_t brt = brtree__make();

    // Opzione 2: Caricamento dell’array con numeri casual
    for(int i = 0; i<dim; i++){
        archive[i] = rand() % MAX;
    }

    // Opzione 3: Ordinamento
    struct timeval start, end;

    gettimeofday(&start, NULL);
    for(int i = 0; i<dim; i++){
        info_t inf;
        inf.key = archive[i];
        brtree__insert(&brt, inf);
    }
    gettimeofday(&end, NULL);

    double t__build_brt = (end.tv_sec + end.tv_usec*1e-6) - (start.tv_sec + start.tv_usec*1e-6) + 0.00001;

    gettimeofday(&start, NULL);
    qsort(archive, dim, sizeof(int), int_cmp);
    gettimeofday(&end, NULL);

    double t__qsort = (end.tv_sec + end.tv_usec*1e-6) - (start.tv_sec + start.tv_usec*1e-6) + 0.00001;

    FILE* fp = fopen("create_time.csv", "at+");
    if(fp == NULL){
        perror("Errore apertura file create_time.csv");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "%d,%lf,%lf\n", dim, t__build_brt, t__qsort);
    fclose(fp);

    // Opzioni 4 e 5: Stampe
    #if 0
    printf("Print ARRAY\n");
    parray(archive, dim);
    printf("\nPrint BRT\n");
    pbrt_ord(brt);
    printf("\n");
    #endif

    fp = fopen("search_time.csv", "at+");
    if(fp == NULL){
        perror("Errore apertura file create_time.csv");
        exit(EXIT_FAILURE);
    }

    // Opzione 6: ricerca
    for(int i = 0; i<rtempt; i++){
        int r = rand() % MAX;

        int h_bin = mbsearch(archive, dim, r);
        int h_brt = bstsearch(brt, r);
        fprintf(fp, "%d,%d,%d\n", dim, h_brt, h_bin);

    }

    fclose(fp);

    //Opzione 7: deallocazione
    free(archive);
    btree__destroy(brt);

}

void banchmark(int runs, int rtempt, int max, int step){
    for(int i = step; i<max; i+=step){
        for(int j = 0; j<runs; j++){
            test(i, rtempt);
        }
    }
}

int main(int argc, char* argv[]){

    if(argc!=5){
        printf("Uso: %s n_runs rtempt max_dim step", argv[0]);
    }

    banchmark(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));

}
