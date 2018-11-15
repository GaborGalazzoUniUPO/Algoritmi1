#include "../../../shared/liste_code.h"
#include "card.h"

#ifndef TABLE_H
#define TABLE_H
typedef List Table;
#endif

Table table__init();
void table__play(Table *table, Card *card);

void table__print(Table table);