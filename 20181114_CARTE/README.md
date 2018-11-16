# LEZIONE 2018/11/14 - SCOPA
##### Gabor Galazzo 20024195 A.A. 2018/2019

Il programma è uno scheletro per il gioco di carte "scopa" rappresenta le carte, il mazzo, i giocatori e il tavolo.

## Scelte progettuali

Ogni entità del progetto è rapppresentata con un *header file* che fornisce le funzioni e strutture.  
Il gioco della *scopa* viene emulato da un'entità **engine** che ha come dipendenze tutti i domini del gioco e li gestisce secondo le regole presabilite.

## Descrizione delle strutture dati utilizzate
Le strutture utilizzte sono estensioni dei tipi **coda** e **pila** o della struttura lista, precedentemente implementate nella libreria [liste_code.h](../shared/liste_code.h)

> ### Carta - [src/model/card.h](src/model/card.h)
> ```c
> typedef enum s { // Rappresentazione dei SEMI
>    DIAMOND = 0,
>    CLUBS = 1,
>    HARTH = 2,
>    SPADES = 3
> } Suit;
> typedef struct {
>    int value;
>    Suit suit;
> } Card;
>
> // Inizializza la carta
> Card* card__init(int value, Suit suit);
> // Stampa una carta su fp
> void card__print(Card* card, FILE* fp);
> //Stampa generico per foreach di List
> void card__print_for_list(void* card);
> ```

> ### Mazzo - [src/model/deck.h](src/model/deck.h)
> ```c
> //il mazzo è una coda
>typedef Queue Deck; 
>
>//Inizializza il mazzo
>Deck* deck__init(); 
>//mischia il mazzo tramite "ruffle shuffle"
>void deck__shuffle(Deck* deck);
>//mischia un numero rando di volte tra 3 e 6 il mazzo
>void deck__good_shuffle(Deck* deck); 
>//togli una carta dala cima del mazzo e te la restituisce
>Card* deck__draw(Deck* deck);
>
>//Utililties
>
>//Stampa il deck
>void deck__print(Deck* deck); 
>//Restituisce se il mmazzo è vuoto
>int deck__is_empty(Deck* deck); 
>// Restituiisce il numero di carte dentro il deck
>int deck__count(Deck* deck);
> ```

> ### Tavolo - [src/model/table.h](src/model/table.h)
> ```c
>//Il Tavolo è una lista
>typedef List Table;
>
>// Inizializza il tavolo
>Table table__init();ù
>//Prende una carta card e la mette sul tavolo
>void table__play(Table *table, Card *card);
>
>//Utilities
>
>//Stampa tutte le carte che ci sono sul tavolo
>void table__print(Table table);
> ```

> ### Giocatore - [src/model/player.h](src/model/player.h)
> ```c
>//Il giocatore è una pila (le carte che ha in male)
>typedef Stack Player;
>
>//Inizializza il giocatore
>Player player__init();
>// Dato un deck il giocatore ne pesta num_cards carte
>void player__draw(Deck* deck, Player* player, int num_cards);
>// Verifica se il giocatore ha la mano vuota
>int player__empty_hand(Player player);+
>// Fa giocare una carta (pop sulla lista)
>Card* player__play(Player* player);
>
>// Utilities
>
>// Stampa tutte le carte in mano ad un giocatore
>void player__print(Player player);
> ```

> ### Engine di Scopa - [src/engine/scopa.h](src/engine/scopa.h)
> ```c
>#define MAX_PLAYERS 4
>
>typedef struct {
>    Table table;
>    Deck* deck;
>    Player players[MAX_PLAYERS];
>    int num_players;
>    int turn;
>} Scopa_e;
>
>//Inizializza l'engin con n giocatori con la mano
>// vuota, un mazzo non mescolato e il tavolo
>// vuoto
>Scopa_e* scopa_engine__init(int num_players);
>
>// Passa al sucessivo "frame" di gioco
>void scopa_engine__step(Scopa_e* scopa_engine);
>
>// Mischia il mazzo, fa pescare a tutti i giocatori
>// tre carte e ne mette quattro sul tavolo
>void scopa_engine__reset(Scopa_e* scopa_engine);
>
>// Stampa la condizione di gioco
>void scopa_engine__print_status(Scopa_e* scopa_engine);
>
>// Verifica se siamo arrivati ad 
>// una condizione di gioco finito
>int scopa_engine__is_game_end(Scopa_e* scopa_engine);
> ```



