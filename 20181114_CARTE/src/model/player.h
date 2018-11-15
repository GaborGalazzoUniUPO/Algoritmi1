
/**
 * Rappresentiamo un giocatore di carte
 */

#include "../../../shared/liste_code.h"
#include "deck.h"

#ifndef PLAYER_H
#define PLAYER_H
typedef Stack Player;
#endif

Player player__init();
void player__draw(Deck* deck, Player* player, int num_cards);
int player__empty_hand(Player player);
Card* player__play(Player* player);

void player__print(Player player);