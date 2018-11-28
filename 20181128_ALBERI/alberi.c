#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../shared/tree.h"

BinaryTree make_random_tree(int n){
    if(n>0){
        int n_sx = (n-1)/2;
        int n_dx = n -1 -n_sx;
        int* r = malloc(sizeof(int));
        *r = rand()%5;
        BinaryNode* bn = btree__make_node(r);
        bn->sx = make_random_tree(n_sx);
        bn->dx = make_random_tree(n_dx);
        return bn;
    }
    return NULL;
}

bool treturnTrue(void* v){
    return true;
}

bool isOdd(void* n){
    int* i = n;
    return *i %2 == 0;
}

void printNode(FILE* fp, void* n){
    int* i = n;
    fprintf(fp, "%d", *i);
}

bool equals(void* a, void* b){
    int* ai = a;
    int* bi = b;
    return *ai == *bi;
}

int main(int argc, char* argv[]){
    srand(time(NULL)); 

    int n = atoi(argv[1]);

    BinaryTree bt = make_random_tree(n);
    btree__print(bt, 0, printNode, stdout);
    puts("\n");
    int h =  btree__height(bt);
    printf("h: %d, n: %d\n", h, n);
    int l = btree__count_leaf(bt, treturnTrue);
    int lo = btree__count_leaf(bt, isOdd);
    int nds = btree__count_node(bt);
    printf("l: %d, lo: %d, nds: %d\n", l, lo, nds);
    int* needle = malloc(sizeof(int));
    *needle = 2;
    bool found =  btree__find(bt,needle,equals);
    printf("NEEDLE: %d, found: %d\n", *needle, found);

    puts("\n\n");
    int a[6] = {1,2,3,4,5,6};
    BinaryTree pnA = btree__from_array(a,6);
    btree__print(pnA, 0, printNode, stdout);


    btree__destroy(bt, free);

    exit(EXIT_SUCCESS);
}