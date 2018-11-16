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

Deck* deck__init(); //Inizializza il mazzo
void deck__shuffle(Deck* deck); //mischia il mazzo tramite "ruffle shuffle"
void deck__good_shuffle(Deck* deck); //mischia un numero rando di volte tra 3 e 6 il mazzo
Card* deck__draw(Deck* deck); //togli una carta dala cima del mazzo e te la restituisce

//Utililties
void deck__print(Deck* deck); //Stampa il deck
int deck__is_empty(Deck* deck); //Restituisce se il mmazzo è vuoto
int deck__count(Deck* deck);// Restituiisce il numero di carte dentro il deck