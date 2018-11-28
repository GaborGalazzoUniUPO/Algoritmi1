#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../shared/itree.h"

BinaryTree make_random_tree(int n){
    if(n>0){
        int n_sx = (n-1)/2;
        int n_dx = n -1 -n_sx;
        BinaryNode* bn = btree__make_node(rand()%5);
        bn->sx = make_random_tree(n_sx);
        bn->dx = make_random_tree(n_dx);
        return bn;
    }
    return NULL;
}

bool returnTrue(int v){
    return true;
}

bool isOdd(int n){
    return n %2 == 0;
}

int main(int argc, char* argv[]){
        srand(time(NULL)); 

    int n = atoi(argv[1]);

    BinaryTree bt = make_random_tree(n);
    btree__print(bt, 0, stdout);
    puts("\n");
    //Ex 1: calcolare l’altezza di un albero binario 
    int h =  btree__height(bt);
    printf("h: %d, n: %d\n", h, n);


    //Ex 2: Calcolare il numero di foglie di un albero binario. 
    int l = btree__count_leaf(bt, returnTrue);
    //Variante: calcolare il numero di foglie con chiave pari di un albero binario. 
    int lo = btree__count_leaf(bt, isOdd);


    //Ex 3: Calcolare il numero di nodi di un albero binario. 
    int nds = btree__count_node(bt);
    printf("l: %d, lo: %d, nds: %d\n", l, lo, nds);

    //Ex 4: Cercare un elemento x tra le chiavi di un albero binario
    bool found =  btree__find(bt,2);
    printf("NEEDLE: %d, found: %d\n", 2, found);

    //Ex 5. Sommare le chiavi di un albero binario (ricorsivamente ed iterativamente)
    int sum = btree__sum(bt);
    int sumr = btree__sum_r(bt);
    printf("SUM: %d, SUM_r: %d\n", sum, sumr);

    //Ex 6: Trasformare un albero da un array posizionale
    puts("\n\n");
    int a[6] = {1,2,3,4,5,6};
    BinaryTree pnA = btree__from_array(a,6);
    btree__print(pnA, 0, stdout);
    btree__destroy(pnA);

    btree__destroy(bt);
    

    exit(EXIT_SUCCESS);
}