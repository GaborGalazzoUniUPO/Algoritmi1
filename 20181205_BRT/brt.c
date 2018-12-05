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
    return *ia - *ib;
    /* integer comparison: returns negative if b > a 
	and positive if a > b */
}

/************************************************/

void parray(int *array, int dim)
{
    for (int i = 0; i < dim; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void pbrt_ord(brtree_t brt)
{
    if (brt == NULL)
        return;
    pbrt_ord(brt->l);
    printf("%d ", brt->inf.key);
    pbrt_ord(brt->r);
}

/*************************************************/

int mbsearch(int array[], int n, int x)
{
    if (n == 0)
        return 0;
    int m = n / 2;
    if (x < array[m])
    {
        return 1 + mbsearch(array, m, x);
    }
    if (x > array[m])
    {
        return 1 + mbsearch(array + (m + 1), n - (m + 1), x);
    }
    return 1;
}

int bstsearch(brtree_t brt, int needle)
{
    if (brt == NULL)
        return 0;
    if (needle < brt->inf.key)
    {
        return 1 + bstsearch(brt->l, needle);
    }
    if (needle > brt->inf.key)
    {
        return 1 + bstsearch(brt->r, needle);
    }
    return 1;
}
/************************************************/

int brtree__insert_hc(btree_t *brt, info_t inf)
{
    if (*brt == NULL)
    {
        btree_t btree = bnode__make(inf);
        (*brt) = btree;
        return 0;
    }
    if (inf.key < (*brt)->inf.key)
    {
        return 1 + brtree__insert_hc(&((*brt)->l), inf);
    }
    else
    {
        return 1 + brtree__insert_hc(&((*brt)->r), inf);
    }
}

/********************************************/

/* C implementation QuickSort */
#include <stdio.h>

// A utility function to swap two elements
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

/* This function takes last element as pivot, places 
   the pivot element at its correct position in sorted 
    array, and places all smaller (smaller than pivot) 
   to left of pivot and all greater elements to right 
   of pivot */
int partition(int arr[], int low, int high, int *hit)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1);     // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        (*hit)++;
        if (arr[j] <= pivot)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort 
 arr[] --> Array to be sorted, 
  low  --> Starting index, 
  high  --> Ending index */
int quickSort_hc(int arr[], int low, int high)
{
    int hit = 0;
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now 
           at right place */

        int pi = partition(arr, low, high, &hit);

        // Separately sort elements before
        // partition and after partition
        hit += quickSort_hc(arr, low, pi - 1);
        hit += quickSort_hc(arr, pi + 1, high);
    }
    return hit;
}

/*************************************/

#define MAX 100

void test(FILE *fp, int dim, int rtempt, int narray)
{

    //Opzione 1: Inizializzazione

    int *temp = malloc(sizeof(int) * dim);
    double t__build_brt = 0;
    double t__qsort = 0;
    double h__build_brt = 0;
    double h__qsort = 0;

    int *archive = malloc(sizeof(int) * dim);
    btree_t brt = brtree__make();

    for (int k = 0; k < narray; k++)
    {

        // Opzione 2: Caricamento dell’array con numeri casual
        for (int i = 0; i < dim; i++)
        {
            temp[i] = rand() % dim * 5;
        }

        

        // Opzione 3: Ordinamento
        struct timeval start, end;

        gettimeofday(&start, NULL);
        for (int i = 0; i < dim; i++)
        {
            info_t inf;
            inf.key = temp[i];
            h__build_brt += brtree__insert_hc(&brt, inf);
        }
        gettimeofday(&end, NULL);

        t__build_brt += (end.tv_sec + end.tv_usec * 1e-6) - (start.tv_sec + start.tv_usec * 1e-6) + 0.00001;

        gettimeofday(&start, NULL);
        for (int i = 0; i < dim; i++)
        {
            archive[i] = temp[i];
        }
        h__qsort += quickSort_hc(archive, 0, dim - 1);
        gettimeofday(&end, NULL);

        t__qsort += (end.tv_sec + end.tv_usec * 1e-6) - (start.tv_sec + start.tv_usec * 1e-6) + 0.00001;

        if(k < (narray -1))
            btree__destroy(&brt);
    }

    fprintf(fp, "%d,%lf,%lf,%.2lf,%.2lf,", dim, t__build_brt / narray, t__qsort / narray, h__build_brt/narray , h__qsort/narray);

// Opzioni 4 e 5: Stampe
#if 0
    printf("Print ARRAY\n");
    parray(archive, dim);
    printf("\nPrint BRT\n");
    pbrt_ord(brt);
    printf("\n");
#endif

    double h_bin = 0;
    double h_brt = 0;

    // Opzione 6: ricerca
    for (int i = 0; i < rtempt; i++)
    {
        int r; //= rand() % dim;
               //  if(rand()%3<2)
        r = archive[rand() % (dim - 1)];
        h_bin += mbsearch(archive, dim, r);
        h_brt += bstsearch(brt, r);
    }

    fprintf(fp, "%.2lf,%.2lf\n", h_brt / rtempt, h_bin / rtempt);

    //Opzione 7: deallocazione
    free(archive);
    btree__destroy(&brt);
}

void banchmark(int narray, int rtempt, int max, int step)
{
    FILE *fp = fopen("benchmark.csv", "wt+");
    fprintf(fp, "\"dim array\",\"avg time build brt\",\"avg time qsort\",\"avg hit build brt\",\"avg hit qsort\",\"agv hit brtr\",\"avg hit bsearch\"\n");
    if (fp == NULL)
    {
        perror("Errore apertura file create_time.csv");
        exit(EXIT_FAILURE);
    }
    for (int i = step; i <= max; i += step)
    {
        test(fp, i, rtempt, narray);
    }
    fclose(fp);
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    if (argc != 5)
    {
        printf("Uso: %s n_array n_ricerche max_dim step", argv[0]);
        exit(EXIT_FAILURE);
    }

    banchmark(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
}
