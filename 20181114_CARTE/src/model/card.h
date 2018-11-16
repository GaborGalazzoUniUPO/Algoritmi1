
/*
* Rappresentiamo una carta tipo "francese"
*/
#include <stdio.h>
#include <stdlib.h>

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

// Inizializza la carta
Card* card__init(int value, Suit suit);

// Stampa una carta su fp
void card__print(Card* card, FILE* fp);

//Stampa generico per foreach di List
void card__print_for_list(void* card);
