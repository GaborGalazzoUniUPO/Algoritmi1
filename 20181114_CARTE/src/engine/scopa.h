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

//Inizializza l'engin con n giocatori con la mano
// vuota, un mazzo non mescolato e il tavolo
// vuoto
Scopa_e* scopa_engine__init(int num_players);

// Passa al sucessivo "frame" di gioco
void scopa_engine__step(Scopa_e* scopa_engine);

// Mischia il mazzo, fa pescare a tutti i giocatori
// tre carte e ne mette quattro sul tavolo
void scopa_engine__reset(Scopa_e* scopa_engine);

// Stampa la condizione di gioco
void scopa_engine__print_status(Scopa_e* scopa_engine);

// Verifica se siamo arrivati ad 
// una condizione di gioco finito
int scopa_engine__is_game_end(Scopa_e* scopa_engine);