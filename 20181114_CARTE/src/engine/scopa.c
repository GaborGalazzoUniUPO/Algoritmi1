#include "scopa.h"

int all_players_empty_hand(Scopa_e *scopa_engine);

Scopa_e *scopa_engine__init(int num_players)
{
    if (num_players < 1 || num_players > MAX_PLAYERS)
    {
        fprintf(stderr, "ERRORE NUMERO GIOCATORI %d\n! MAX: %d, MIN: 1", num_players, MAX_PLAYERS);
        exit(1);
    }
    Scopa_e *scopa_engine = malloc(sizeof(Scopa_e));
    scopa_engine->table = table__init();
    scopa_engine->deck = deck__init();
    scopa_engine->num_players = num_players;
    for (int i = 0; i < num_players; i++)
    {
        scopa_engine->players[i] = player__init();
    }
    scopa_engine->turn = -1;
    return scopa_engine;
}

int all_players_empty_hand(Scopa_e *scopa_engine)
{
    int all_empty = 1;
    for (int i = 0; i < scopa_engine->num_players; i++)
    {
        all_empty = all_empty && player__empty_hand(scopa_engine->players[i]);
    }
    return all_empty;
}

void all_players_draw(Scopa_e *scopa_engine, int cards)
{
    for (int j = 0; j < cards; j++)
        for (int i = 0; i < scopa_engine->num_players; i++)
        {
            player__draw(scopa_engine->deck, &(scopa_engine->players[i]), 1);
        }
}

int scopa_engine__is_game_end(Scopa_e *scopa_engine)
{
    return all_players_empty_hand(scopa_engine) && deck__is_empty(scopa_engine->deck);
}

void scopa_engine__step(Scopa_e *scopa_engine)
{
    if (scopa_engine__is_game_end(scopa_engine))
    {
        puts("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        puts("!!!!!!!!!!!!!! GIOCO FINITO !!!!!!!!!!!!!!!!!");
        puts("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    }
    else if (scopa_engine->turn == -1)
        scopa_engine__reset(scopa_engine);
    else if (all_players_empty_hand(scopa_engine))
    {
        all_players_draw(scopa_engine, 3);
        puts("\n-------------------------------------------------");
        puts("------------ NUOVO TURNO TUTTI PESCANO 3 ----------");
        puts("-------------------------------------------------\n\n");
    }
    else
    {

        int turn_of = scopa_engine->turn % scopa_engine->num_players;
        if (!player__empty_hand(scopa_engine->players[turn_of]))
        {

            Card *c = player__play(&(scopa_engine->players[turn_of]));
            table__play(&(scopa_engine->table), c);
            puts("\n\n\n-------------------------------------------------");
            printf("GIOCATORE %d ha giocato ", turn_of + 1);
            card__print(c, stdout);
            puts("\n-------------------------------------------------\n\n\n");
        }
        scopa_engine->turn++;
    }
}

void scopa_engine__reset(Scopa_e *scopa_engine)
{
    scopa_engine->table = table__init();
    scopa_engine->deck = deck__init();
    deck__good_shuffle(scopa_engine->deck);
    for (int i = 0; i < scopa_engine->num_players; i++)
    {
        scopa_engine->players[i] = player__init();
        player__draw(scopa_engine->deck, &(scopa_engine->players[i]), 3);
    }
    for(int i = 0; i<4; i++){
        Card* c = deck__draw(scopa_engine->deck);
        table__play(&(scopa_engine->table), c);
    }
    scopa_engine->turn = 0;
}

void scopa_engine__print_status(Scopa_e *scopa_engine)
{
    puts("\n\n-------------------------------------------------\n\n");
    printf("SCOPA, Turno %d\n", scopa_engine->turn);
    printf("Giocatori %d\n", scopa_engine->num_players);
    puts("\n-------------------------------------------------");
    puts("------------CARTE NEL MAZZO ---------------------");
    puts("-------------------------------------------------");
    deck__print(scopa_engine->deck);
    puts("\n-------------------------------------------------");
    puts("------------CARTE SUL TAVOLO --------------------");
    puts("-------------------------------------------------");
    table__print(scopa_engine->table);
    for (int i = 0; i < scopa_engine->num_players; i++)
    {
        puts("\n-------------------------------------------------");
        printf("------------CARTE GIOCATORE %d ------------------\n", i + 1);
        puts("-------------------------------------------------");
        player__print(scopa_engine->players[i]);
    }
    puts("-------------------------------------------------");
    puts("\n\n-------------------------------------------------\n\n");
}