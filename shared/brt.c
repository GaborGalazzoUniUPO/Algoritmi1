#include "brt.h"

brtree_t brtree__make(){
    return NULL;
}

void brtree__insert(btree_t* brt, info_t inf){
    if(*brt == NULL)
    {
        btree_t btree = bnode__make(inf);
        (*brt) = btree;
        return;
    }
    if(inf.key<(*brt)->inf.key){
       brtree__insert(&((*brt)->l), inf);
    }else{
       brtree__insert(&((*brt)->r), inf);
    }
}