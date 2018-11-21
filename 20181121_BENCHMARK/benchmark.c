#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h> 
void swap(int * a, int * b) {
    int temp = * a;
    * a = * b;
    * b = temp;
}

int* random_array(int n){
    srand(time(NULL));
    int* arr = (int*) malloc(n*sizeof(int));
    for(int i = 0; i<n; i++)
        arr[i] = rand();
    return arr;
}

int* copy_array(int* a, int n){
    int* arr = (int *)malloc(n*sizeof(int));
    for(int i = 0; i<n; i++){
        arr[i] = a[i];
    }
    return arr;
}

// verifica che array a[0..n] sia ordinato
bool check_sort(int *a, int n)
{
    for(int i=0; i < n-1; i++)
        if(a[i] > a[i+1]) return false;
    return true;
}

/************* BUBBLE SORT ************************/

void bubblesort(int a[], int n) {
    int last = n - 1;
    int swapped = 1;
    while (swapped > 0) {
        swapped = 0;
        int temp = 0;
        for (int i = 0; i < last; i++) {
            if (a[i] > a[i + 1]) {
                swap( & a[i], & a[i + 1]);
                temp = i;
                swapped = 1;
            }
        }
        last = temp;
    }
}

/******************* QUICK SORT ******************/

int partition(int array[], int begin, int end) {
    int pivot, l, r;
    pivot = array[begin];
    l = begin + 1;
    r = end;
    while (l <= r) {
        while (array[r] > pivot)
            r = r - 1;
        while ((array[l] <= pivot) && (l <= r))
            l = l + 1;
        if (l < r) {
            swap( & array[l], & array[r]);
            l++;
            r--;
        }
    }
    swap( & array[begin], & array[r]);
    return r;
}

void quicksort(int array[], int begin, int end) {
    int q;
    if (begin < end) {
        q = partition(array, begin, end);
        quicksort(array, begin, q -
                                1);
        quicksort(array, q + 1, end);
    }
}

/****************** HEAP SORT ***************/
int left(int i) {return 2*i+1; }
int right(int i) {return 2*i+2; }
int parent(int i){ return (i-1)/2; }

void fix_heap(int a[], int i, int n){
    int l = left(i);
    int r = right(i);
    int largest;

    if(l<n && a[l] > a[i] )
        largest = l;
    else
        largest = i;

    if(r<n && a[r] > a[largest])
        largest = r;

    if(largest!=i)
    {
        swap(&a[i], &a[largest]);
        fix_heap(a, largest, n);
    }
}

void heapify(int a[], int n){
    for(int i = n/2; i>= 0; i--){
        fix_heap(a, i, n);
    }
}

void heapsort(int a[], int n){
    int size = n;
    heapify(a, n);
    for(int i = n-1; i>0; i--){
        swap(&a[0], &a[i]);
        size--;
        fix_heap(a, 0, size);
    }
}

#define array_len(x)  (sizeof(x) / sizeof((x)[0]))

int main() {
    FILE* fp = fopen("data.md", "wt");
    fprintf(fp, "Size|Bubble|Quick|Heap|\n");
    fprintf(fp, "----|------|-----|----|\n");
    int runs = 10;
    int dimensions[] = {5, 10, 25, 50, 100, 200, 500, 1000, 2000};
    for(int i = 0; i<9; i++){
        int dim = dimensions[i];

        double t_bubble = 0, t_quick = 0, t_heap = 0;
        for(int k = 0; k<runs; k++){
            int* test_a = random_array(dim);


            int* to_test = copy_array(test_a, dim);
            clock_t begin = clock();
            bubblesort(to_test, dim);
            clock_t end = clock();
            assert(check_sort(to_test, dim));
            t_bubble += (double)(end - begin) / CLOCKS_PER_SEC;
            free(to_test);


            to_test = copy_array(test_a, dim);
            begin = clock();
            quicksort(to_test,0, dim-1);
            end = clock();
            assert(check_sort(to_test, dim));
            t_quick += (double)(end - begin) / CLOCKS_PER_SEC;
            free(to_test);


            to_test = copy_array(test_a, dim);
            begin = clock();
            heapsort(to_test, dim);
            end = clock();
            assert(check_sort(to_test, dim));
            t_heap+= (double)(end - begin) / CLOCKS_PER_SEC;
            free(to_test);


            free(test_a);

        }
        //sleep(1);
        fprintf(fp, "%d|%lf|%lf|%lf|\n", dim, t_bubble/(double)runs, t_quick/(double)runs, t_heap/(double)runs);

    }
    fclose(fp);

}

/*

clock_t* banchmark(int runs, int max, void (*func_ptr[])(int*, int), int n){

    clock_t* times = malloc(n*sizeof(clock_t));
    for(int i = 0; i<max; i++){
        for(int j = 0; j<runs; j++){
            int* test_a = random_array(i);


            for(int k = 0; k<n; k++) {
                int *to_test = copy_array(test_a, i);
                clock_t begin = clock();
                func_ptr[k](to_test, i);
                clock_t end = clock();
                assert(check_sort(to_test, i));
                times[k] += (end - begin);
                free(to_test);
            }
        }
    }
    return times;
}

void start_qsort(int* a, int n){
    quicksort(a, 0, n-1);
}


int main(){
    void (*func_ptr[3])(int*, int) = {bubblesort, heapsort, start_qsort};
    clock_t* times = banchmark(10, 100, func_ptr, 3);
}
 */