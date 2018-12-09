#include "../shared/tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


btree_t btree__make(int n)
{
    if (n > 0)
    {
        int ncl = (n - 1) / 2;
        int ncr = (n - 1) - ncl;

        info_t info;
        info.key = rand() % 10;
        bnode_t *bnode = bnode__make(info);
        bnode->l = btree__make(ncl);
        bnode->r = btree__make(ncr);
        return bnode;
    }
    return NULL;
}

// genera array di n elementi con interi random tra -100000 e 100000
int *random_array(int n)
{
    int *a = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        a[i] = (rand() % 10);
    return a;
}

void print_array(int* a, int n){
    for(int i = 0; i<n; i++){
        printf("%d ",a[i]);
    }
    putchar('\n');
}

bool check_oe(btree_t btree){
    if(btree == NULL)
        return true;
    if((btree->r && btree->r->inf.key %2 == 1) || (btree->l && btree->l->inf.key %2 == 0))
        return false;
    return check_oe(btree->l) && check_oe(btree->r);

}

int main(int argc, char *argv[])
{

    srand(time(NULL));
    if (argc < 2)
    {
        fprintf(stderr, "\nUso: %s n_nodes\n", argv[0]);
        exit(1);
    }
    int num = atoi(argv[1]);

    btree_t btree = btree__make(num);

    btree__print(stdout, btree);


    // Ex 1: calcolare l’altezza di un albero binario 
    int h = btree__height(btree);
    printf("h: %d\n", h);

    // Ex 2: Calcolare il numero di foglie di un albero binario. 

    int l = btree__leaf_count(btree);
    printf("l: %d\n", l);
    
    // EX 2.1: Variante: calcolare il numero di foglie con chiave pari di un albero binario. 
    int lo = btree__leaf_count_odd(btree);
    printf("lo: %d\n", lo);

    // Ex 3: Calcolare il numero di nodi di un albero binario
    int nn = btree__node_count(btree);
    printf("nn: %d\n", nn);

    // Ex 4: Cercare un elemento x tra le chiavi di un albero binario. 
    int needle = rand()%10;
    bool found = btree__contains_key(btree, needle);
    printf("found %d:  ",needle);
    printf(found ? "true" : "false");
    putchar('\n');

    // Ex 5: Sommare le chiavi di un albero binario RIC
    int sum_r = btree__sum_keys(btree);
    printf("sum_r: %d\n", sum_r);
    // Ex 5.1: ITER
    int sum_i = btree__sum_keys_i(btree);
    printf("sum_i: %d\n", sum_i);


    //EX 6: Da albero con notazione posizionale a struttua
    
    int * array = random_array(num);
    print_array(array, num);
    btree_t barray = btree__from_array(array, num);
    btree__print(stdout, barray);
    free(array);
    btree__destroy(&btree);
    btree = barray;

    // Ex 7: Determinare se nella root di un albero binario risiede il valore 
    // più grande tra quelli presenti nell’albero stesso.

    int root = btree->inf.key;
    int max = btree__max_key(btree);
    printf("root: %d, max: %d\n", root, max);
    if(root<max)
        printf("root NO max\n");
    else
        printf("root IS max\n");
    

    // EX 8: Dato un albero binario un po’ parti
    // colare, per cui vale la seguente caratteristica: dato un nodo, il suo 
    // figlio sinistro contiene un valore dispari; il suo 
    // figlio destro contiene un valore pari. Verificare che l’albero 
    // ricevuto in ingresso possiede questa caratteristica
    bool is_oe = check_oe(btree);
    if(is_oe)
        printf("btree IS OE\n");
    else
        printf("btree IS OEn't\n");

    // EX 9: Dato un albero binario, controllare che l’albero sia completo
    bool is_fool = btree__is_full(btree);
     if(is_fool)
        printf("btree IS full\n");
    else
        printf("btree IS fulln't\n");

    // EX 10:  Restituire l’ altezza minima di un albero binario
    int min_h = btree__height_min(btree);
    printf("min_h: %d", min_h);



    btree__destroy(&btree);
}