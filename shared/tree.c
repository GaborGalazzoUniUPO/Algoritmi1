#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include "list_stack_queue.h"
#include <assert.h>

bnode_t *bnode__make(info_t inf)
{
    bnode_t *bnode = malloc(sizeof(bnode_t));
    bnode->inf = inf;
    bnode->l = NULL;
    bnode->r = NULL;
    return bnode;
}

#define COUNT 4
void _btree__print(FILE *fp, btree_t btree, int space, int single)
{
    // Base case
    if (btree == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

// Process right child first
    _btree__print(fp, btree->r, space, btree->l == NULL);
    // Print current node after space
    // count
    //printf("\x0c3\x0c4");
    for (int i = COUNT; i < space; i++)
    {
        if (i < (space - COUNT))
        {
            fprintf(fp, " ");
        }
        else if (i == (space - COUNT))
        {
            if (single)
            {
                printf("\x0c0\x0c4");
            }
            else
            {
                printf("\x0c3\x0c4");
            }
        }
        else
        {
            fprintf(fp, "\x0c4");
        }
    }
    fprintf(fp, "%d\n", btree->inf.key);

    

    // Process left child
    _btree__print(fp, btree->l, space, 1);
}

void print2DUtil(FILE* fp, btree_t root, int space) 
{ 
    // Base case 
    if (root == NULL) 
        return; 
  
    // Increase distance between levels 
    space += COUNT; 
  
    // Process right child first 
    print2DUtil(fp, root->r, space); 
  
    // Print current node after space 
    // count 
    fprintf(fp, "\n"); 
    for (int i = COUNT; i < space; i++) 
        fprintf(fp, " "); 
    fprintf(fp, "%d\n", root->inf.key); 
  
    // Process left child 
    print2DUtil(fp, root->l, space); 
} 

#if 0
void btree__print(FILE *fp, btree_t btree)
{
    _btree__print(fp, btree, 0, 0);
}
#endif

void btree__print(FILE *fp, btree_t btree)
{
    print2DUtil(fp, btree, 0); 
}

void btree__destroy(btree_t* btree)
{
    if (*btree == NULL)
        return;
    btree__destroy(&((*btree)->l));
    btree__destroy(&((*btree)->r));
    free(*btree);
    (*btree) = NULL;
}

#define max(a, b) \
    ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a, b) \
    ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

int btree__height(btree_t btree)
{
    if (btree == NULL)
        return -1;
    return 1 + max(btree__height(btree->l), btree__height(btree->r));
}

int btree__leaf_count(btree_t btree)
{
    if (btree == NULL)
        return 0;
    return (btree->l == NULL && btree->r == NULL ? 1 : 0) + btree__leaf_count(btree->l) + btree__leaf_count(btree->r);
}

int btree__leaf_count_odd(btree_t btree)
{
    if (btree == NULL)
        return 0;
    return (btree->l == NULL && btree->r == NULL && (btree->inf.key % 2 == 0) ? 1 : 0) + btree__leaf_count_odd(btree->l) + btree__leaf_count_odd(btree->r);
}

int btree__node_count(btree_t btree)
{
    if (btree == NULL)
        return 0;
    return 1 + btree__node_count(btree->l) + btree__node_count(btree->r);
}

bool btree__contains_key(btree_t btree, int key)
{
    if (btree == NULL)
        return false;
    return btree->inf.key == key || btree__contains_key(btree->l, key) || btree__contains_key(btree->r, key);
}

int btree__sum_keys(btree_t btree){
    if(btree == NULL)
        return 0;
    return btree->inf.key + btree__sum_keys(btree->l) + btree__sum_keys(btree->r);
}

int btree__sum_keys_i(btree_t btree){
    queue_t* queue = queue__init();
    queue__enqueue(btree, queue);
    int acc = 0;
    while(!queue__is_empty(queue)){
        bnode_t* bnode = queue__dequeue(queue);
        if(bnode!=NULL){
            acc+=bnode->inf.key;
            queue__enqueue(bnode->l, queue);
            queue__enqueue(bnode->r, queue);
        }
    }
    free(queue);
    return acc;
}

btree_t _btree__from_array(int* array,int num, int father){
    if(father >= num)
        return NULL;
    info_t inf;
    inf.key = array[father];
    inf.value = NULL;
    bnode_t* bnode = bnode__make(inf);
    bnode->l = _btree__from_array(array, num, (father+1)*2 - 1);
    bnode->r = _btree__from_array(array, num, (father+1)*2 );
    return bnode;
}

btree_t btree__from_array(int* array,int num){
    return _btree__from_array(array, num, 0);
}

int btree__max_key(btree_t btree){
    assert(btree != NULL);
    queue_t* queue = queue__init();
    queue__enqueue(btree, queue);
    int max = btree->inf.key;
    while(!queue__is_empty(queue)){
        bnode_t* bnode = queue__dequeue(queue);
        if(bnode!=NULL){
            if(bnode->inf.key>max)
                max = bnode->inf.key;
            queue__enqueue(bnode->l, queue);
            queue__enqueue(bnode->r, queue);
        }
    }
    free(queue);
    return max;
}

bool btree__is_full(btree_t btree){
    if(btree == NULL)
        return true;
    if(btree->l == NULL && btree->r == NULL)
        return true;
    if(btree->r == NULL && btree->l->l == NULL && btree->l->r == NULL)
        return true;
    return btree__is_full(btree->l) && btree__is_full(btree->r);    
}

int btree__height_min(btree_t btree){
    if (btree == NULL)
        return -1;
    return 1 + min(btree__height(btree->l), btree__height(btree->r));
}
