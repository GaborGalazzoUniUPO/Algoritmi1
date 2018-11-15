#include "model/domain.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    Card* c = card__init(1, CLUBS);
    card__print(c, stdout);
    puts("");
    List list = list__init();
    list__insert(c, &list);
    Table t = table__init();
    c = list__remove(&list);
    table__play(&t, c);
    table__print(t);
    puts("");
    
    return 0;

}