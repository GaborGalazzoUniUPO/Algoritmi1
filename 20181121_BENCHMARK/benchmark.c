
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <float.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int *random_array(int n)
{
    srand(time(NULL));
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        arr[i] = rand();
    return arr;
}

int *copy_array(int *a, int n)
{
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        arr[i] = a[i];
    }
    return arr;
}

// verifica che array a[0..n] sia ordinato
bool check_sort(int *a, int n)
{
    for (int i = 0; i < n - 1; i++)
        if (a[i] > a[i + 1])
            return false;
    return true;
}

/************* BUBBLE SORT ************************/

void bubblesort(int a[], int n)
{
    int last = n - 1;
    int swapped = 1;
    while (swapped > 0)
    {
        swapped = 0;
        int temp = 0;
        for (int i = 0; i < last; i++)
        {
            if (a[i] > a[i + 1])
            {
                swap(&a[i], &a[i + 1]);
                temp = i;
                swapped = 1;
            }
        }
        last = temp;
    }
}

/******************* QUICK SORT ******************/

int partition(int array[], int begin, int end)
{
    int pivot, l, r;
    pivot = array[begin];
    l = begin + 1;
    r = end;
    while (l <= r)
    {
        while (array[r] > pivot)
            r = r - 1;
        while ((array[l] <= pivot) && (l <= r))
            l = l + 1;
        if (l < r)
        {
            swap(&array[l], &array[r]);
            l++;
            r--;
        }
    }
    swap(&array[begin], &array[r]);
    return r;
}

void quicksort(int array[], int begin, int end)
{
    int q;
    if (begin < end)
    {
        q = partition(array, begin, end);
        quicksort(array, begin, q - 1);
        quicksort(array, q + 1, end);
    }
}

/****************** HEAP SORT ***************/
int left(int i) { return 2 * i + 1; }
int right(int i) { return 2 * i + 2; }
int parent(int i) { return (i - 1) / 2; }

void fix_heap(int a[], int i, int n)
{
    int l = left(i);
    int r = right(i);
    int largest;

    if (l < n && a[l] > a[i])
        largest = l;
    else
        largest = i;

    if (r < n && a[r] > a[largest])
        largest = r;

    if (largest != i)
    {
        swap(&a[i], &a[largest]);
        fix_heap(a, largest, n);
    }
}

void heapify(int a[], int n)
{
    for (int i = n / 2; i >= 0; i--)
    {
        fix_heap(a, i, n);
    }
}

void heapsort(int a[], int n)
{
    int size = n;
    heapify(a, n);
    for (int i = n - 1; i > 0; i--)
    {
        swap(&a[0], &a[i]);
        size--;
        fix_heap(a, 0, size);
    }
}

#define array_len(x) (sizeof(x) / sizeof((x)[0]))

#define TIME
#define GENERIC

#ifdef TIME
#include <sys/time.h>
#undef CLOCK
#endif

#ifdef CLOCK

#undef TIME
#endif

#ifdef FIXED
int main()
{
    FILE *fp = fopen("data.md", "wt");
    fprintf(fp, "Size|Bubble|Quick|Heap|\n");
    fprintf(fp, "----|------|-----|----|\n");
    int runs = 100;
    int dimensions[] = {5, 10, 25, 50, 100, 200, 500, 1000, 2000};
    for (int i = 0; i < 9; i++)
    {
        int dim = dimensions[i];

        double t_bubble = 0, t_quick = 0, t_heap = 0;
        for (int k = 0; k < runs; k++)
        {
            int *test_a = random_array(dim);

#ifdef CLOCK
            int *to_test = copy_array(test_a, dim);
            clock_t begin = clock();
            bubblesort(to_test, dim);
            clock_t end = clock();
            assert(check_sort(to_test, dim));
            t_bubble += (double)(end - begin) / CLOCKS_PER_SEC;
            free(to_test);

            to_test = copy_array(test_a, dim);
            begin = clock();
            quicksort(to_test, 0, dim - 1);
            end = clock();
            assert(check_sort(to_test, dim));
            t_quick += (double)(end - begin) / CLOCKS_PER_SEC;
            free(to_test);

            to_test = copy_array(test_a, dim);
            begin = clock();
            heapsort(to_test, dim);
            end = clock();
            assert(check_sort(to_test, dim));
            t_heap += (double)(end - begin) / CLOCKS_PER_SEC;
            free(to_test);
#endif

#ifdef TIME

            struct timeval start, end;
            int *to_test = copy_array(test_a, dim);
            gettimeofday(&start, NULL);
            bubblesort(to_test, dim);
            gettimeofday(&end, NULL);
            assert(check_sort(to_test, dim));
            t_bubble += ((end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000.0);
            free(to_test);

            to_test = copy_array(test_a, dim);
            gettimeofday(&start, NULL);
            quicksort(to_test, 0, dim - 1);
            gettimeofday(&end, NULL);
            assert(check_sort(to_test, dim));
            t_quick += ((end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000.0);
            free(to_test);

            to_test = copy_array(test_a, dim);
            gettimeofday(&start, NULL);
            heapsort(to_test, dim);
            gettimeofday(&end, NULL);
            assert(check_sort(to_test, dim));
            t_heap += ((end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000.0);
            free(to_test);
#endif

            free(test_a);
        }
        //sleep(1);
        fprintf(fp, "%d|%lf|%lf|%lf|\n", dim, t_bubble / (double)runs, t_quick / (double)runs, t_heap / (double)runs);
    }
    fclose(fp);
}
#endif


void banchmark(int runs, int max, int step, char* filename, void (*func_ptr[])(int *, int), int n)
{

    FILE *fp = fopen(filename, "wt");
    fprintf(fp, "dim,suns,");
    for (int i = 0; i < n-1; i++)
    {
        fprintf(fp, "%d,", i);
    }
    fprintf(fp, "%d\n", n-1);
    for (int i = 0; i <= max; i+=step)
    {
        double times[n];
        for(int p = 0; p<n; p++)
        {
            times[p] = 0;
        }
        for (int j = 0; j < runs; j++)
        {
            int *test_a = random_array(i);

            for (int k = 0; k < n; k++)
            {
                struct timeval start, end;
                int *to_test = copy_array(test_a, i);
                gettimeofday(&start, NULL);
                func_ptr[k](to_test, i);
                gettimeofday(&end, NULL);
                assert(check_sort(to_test, i));
                times[k] += (end.tv_sec + end.tv_usec*1e-6) - (start.tv_sec + start.tv_usec*1e-6) + 0.00001;
                free(to_test);
            }
        }

        fprintf(fp, "%d,%d,",i, runs);
        for (int p = 0; p < n-1; p++)
        {
            fprintf(fp, "%lf,", (times[p]/runs));
        }
        fprintf(fp, "%lf\n", (times[n-1]/runs));
    }
    fclose(fp);
}

void start_qsort(int *a, int n)
{
    quicksort(a, 0, n - 1);
}

#ifdef GENERIC
int main(int argc, char* argv[])
{
    if(argc!=5){
        printf("Uso: %s n_runs max_dim step filename", argv[0]);
    }
    void (*func_ptr[3])(int *, int) = {bubblesort, heapsort, start_qsort};
    banchmark(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]),argv[4], func_ptr, 3);
}
#endif
