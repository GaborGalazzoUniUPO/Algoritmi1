#include "../model/domain.h"

# define MAX_PLAYERS 4

#ifndef SCOPA_E_H
#define SCOPA_E_H
typedef struct {

    Table table;
    Deck* deck;
    Player players[MAX_PLAYERS];
    int num_players;
    int turn;

} Scopa_e;
#endif

Scopa_e* scopa_engine__init(int num_players);

void scopa_engine__step(Scopa_e* scopa_engine);

void scopa_engine__reset(Scopa_e* scopa_engine);

void scopa_engine__print_status(Scopa_e* scopa_engine);

int scopa_engine__is_game_end(Scopa_e* scopa_engine);