
/**
 * Rappresentiamo un giocatore di carte
 */

#include "../../../shared/list_stack_queue.h"
#include "deck.h"

#ifndef PLAYER_H
#define PLAYER_H
//Il giocatore è una pila (le carte che ha in male)
typedef stack_t Player;
#endif

//Inizializza il giocatore
Player player__init();
// Dato un deck il giocatore ne pesta num_cards carte
void player__draw(Deck* deck, Player* player, int num_cards);
// Verifica se il giocatore ha la mano vuota
int player__empty_hand(Player player);
// Fa giocare una carta (pop sulla lista)
Card* player__play(Player* player);

// Utilities

// Stampa tutte le carte in mano ad un giocatore
void player__print(Player player);