#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int key;
    void* value;
} info_t;

typedef struct bnode{
    info_t inf;
    struct bnode *l, *r;
} bnode_t;

typedef bnode_t* btree_t;

bnode_t* bnode__make(info_t inf);

void btree__print(FILE *fp, btree_t btree);

void btree__destroy(btree_t* btree);

int btree__height(btree_t btree);

int btree__leaf_count(btree_t btree);

int btree__leaf_count_odd(btree_t btree);

int btree__node_count(btree_t btree);

bool btree__contains_key(btree_t btree, int key);

int btree__sum_keys(btree_t btree);

int btree__sum_keys_i(btree_t btree);

btree_t btree__from_array(int* array,int num);

int btree__max_key(btree_t btree);

bool btree__is_full(btree_t btree);

int btree__height_min(btree_t btree);