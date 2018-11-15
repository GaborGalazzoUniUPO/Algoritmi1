/*
* Rappresentiamo un mazzo di carte francesi
*/

#include "../../../shared/liste_code.h"
#ifndef DECK_H
#define DECK_H
typedef Queue Deck;
#endif

#include <time.h>
#include <stdlib.h>
#include "card.h"

Deck* deck__init();
void deck__shuffle(Deck* deck);
void deck__good_shuffle(Deck* deck);
Card* deck__draw(Deck* deck);

void deck__print(Deck* deck);
int deck__is_empty(Deck* deck);
int deck__count(Deck* deck);