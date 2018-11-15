
/*
* Rappresentiamo una carta tipo "francese"
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_CARD_VALUIE = 13

#ifndef CARD_H
#define CARD_H
typedef enum s { // Rappresentazione dei SEMI
    DIAMOND = 0,
    CLUBS = 1,
    HARTH = 2,
    SPADES = 3
} Suit;


typedef struct {
    int value;
    Suit suit;
} Card;
#endif

Card* card__init(int value, Suit suit);

void card__print(Card* card, FILE* fp);
void card__print_for_list(void* card);
