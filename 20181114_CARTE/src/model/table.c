#include "table.h"
#include "card.h"
#include <stdio.h>

Table table__init(){
    return list__init();
}

void table__play(Table *table, Card* card){
    list__insert(card, table);
}

void table__print(Table table){
    list__foreach(table, card__print_for_list);
}