#include "../../../shared/list_stack_queue.h"
#include "card.h"

#ifndef TABLE_H
#define TABLE_H
typedef list_t Table;
#endif

Table table__init();
void table__play(Table *table, Card *card);

void table__print(Table table);