# LEZIONE 2018/11/14 - SCOPA
##### Gabor Galazzo 20024195 A.A. 2018/2019

Il programma è uno scheletro per il gioco di carte "scopa". Rappresenta le carte, il mazzo, i giocatori e il tavolo.
Lo scheletro è programmato per funzionare nel seguente modo:
* Situazione iniziale:
    * Giocatori: 4 stack inizializzati e vuoti
    * Carte sul tavolo: lista inizializzata e vuota
    * Mazzo di carte: coda di 40 carte “ordinate”
* Prima mano:
    * Mescolare il mazzo
    * Dare le carte ai giocatori (3 a testa)
    * Mettere 4 carte sul tavolo
* Fase di gioco:
    * Per ogni mano, ogni giocatore gioca a turno una carta fino a che le carte in mano sono esaurite
    * A questo punto, si danno altre 3 carte a testa ai giocatori
* Condizione di fine partita:
    * Le carte del mazzo sono terminate, e i giocatori hanno esaurito le carte dell’ultima mano

Il programma da la possibilità di segure il gioco “passo a 
passo":
* Per ogni carta giocata da un giocatore, visualizzare 
la carta giocata e la situazione del gioco:
    * che carte sono in mano ad ogni giocatore
    * che carte sono sul tavolo
    * che carte sono ancora nel mazzo

## Scelte progettuali

Ogni entità del progetto è rapppresentata e condivisibile tramite un *header file* associato che fornisce funzioni e strutture.  
Il gioco della *scopa* viene emulato da un'entità **engine** che ha come dipendenze tutti i domini del gioco e li gestisce secondo le regole presabilite.
<pre>
PRJ:.
├───20181114_CARTE
│   │   makefile
│   │   README.md
│   ├───out <span style="color: forestgreen">//Generated output dir</span>
│   │   ├───src
│   │   │       main
│   │   └───test
│   │           test
│   ├───src
│   │   │   main.c <span style="color: forestgreen">//Main</span>
│   │   │
│   │   ├───engine <span style="color: forestgreen">// Contiene gli engin dei giochi di carte</span>
│   │   │       scopa.c
│   │   │       scopa.h
│   │   │
│   │   └───model <span style="color: forestgreen">// Contiene il dominio del gioco</span>
│   │           card.c
│   │           card.h
│   │           deck.c
│   │           deck.h
│   │           domain.h
│   │           player.c
│   │           player.h
│   │           table.c
│   │           table.h
│   └───test
│           test.c <span style="color: forestgreen">//File di test</span>
└───shared <span style="color: forestgreen">// Filoe condivisi (librerie)</span>
        liste_code.c
        liste_code.h
</pre>

## Descrizione delle strutture dati utilizzate
Le strutture utilizzte sono estensioni dei tipi **coda** e **pila** o della struttura **lista**, precedentemente implementate nella libreria [liste_code.h](../shared/liste_code.h)

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
>Table table__init();
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

## Algoritmo di "mescolamento"

<pre>
algoritmo deck__shuffle(Deck deck)
    <span style="color: forestgreen">// Condizione di ritorno:
    // se il mazzo ha 1 carta è mescolato</span>
    <span style="color: magenta">IF</span> size(deck) < 2 <span style="color: magenta">THEN</span> return
    Deck support
    <span style="color: forestgreen">// Divido il mazzo in due</span>
    <span style="color: magenta">FOR</span> i = 0 <span style="color: magenta">TO</span> size(deck)/2 <span style="color: grey"> COSTO: n/2 </span>
        aggiungo a support la prima carta di deck
    <span style="color: forestgreen">// Mescolo i due sottomazzi che ho creato</span>
    deck__shuffle(support) <span style="color: grey"> COSTO: T(n/2) </span>
    deck__shuffle(deck) <span style="color: grey"> COSTO: T(n/2) </span>
    Deck result
    <span style="color: forestgreen">// Effettuo il "vero" ruffle shuffle</span>
    <span style="color: magenta">WHILE</span>(!is_empty(deck) && !is_empty(support)) <span style="color: grey"> COSTO: n</span>
        <span style="color: forestgreen">// Fintanto che ho carte nei sottomazzi
        // lancio una moneta (0 o 1) per capire da 
        // quale mazzo pescare una carta per comporre 
        // il mazzo mescolato "result".
        // Se in un mazzo non ci sono più carte metto in result
        // tutte le carte rimanenti</span>
        <span style="color: magenta">IF</span> (coin_flip() || is_empty(support) && !is_empty(deck)) <span style="color: magenta">THEN</span>
            aggiungo a result la prima carta di deck
        <span style="color: magenta">ELSE</span>
            aggiungo a result la prima carta di support
    cambio il riffedrimento a deck con result
</pre>
Dal precedente algoritmo si può dedurre la seguente relazione di ricorrenza:

<div align="center">

![eqazione di ricorrenza](https://latex.codecogs.com/gif.latex?%5Cbegin%7Bcases%7D%20T%280%29%20%3D%20T%281%29%20%3D%200%5C%5C%20T%28n%29%20%3D%202T%28%20%5Cfrac%7Bn%7D%7B2%7D%20%29%20&plus;%20%5Cfrac%7B3%7D%7B2%7Dn%20%5Cend%7Bcases%7D)

</div>
Dato che la relazione di ricorrenza precedente è della forma 

<div align="center">

![t_master](https://latex.codecogs.com/gif.latex?T%28n%29%20%3D%20%5Cbegin%7Bcases%7D%20aT%28%5Cfrac%7Bn%7D%7Bb%7D%29%20%5CLeftarrow%20n%20%3E%20k%5C%5C%20c%20%5CLeftarrow%20n%20%5Cleq%20k%20%5Cend%7Bcases%7D)

</div>

è applicabile il *"Teorema Master"*

<div align="center">

![applicazione](https://latex.codecogs.com/gif.latex?%5Cbegin%7Bcases%7D%20a%20%3D%202%5C%5C%20b%20%3D%202%5C%5C%20f%28n%29%20%3D%20%5Cfrac%7B3%7D%7B2%7D%5C%5Cg%28n%29%20%3D%20n%5E%7Blob_ba%7D%20%3D%20n%5E%7Blog_22%7D%3Dn%5E1%20%3D%20n%20%5Cend%7Bcases%7D)

</div>

Dala relazione possiamo stabilire che: 

<div align="center">

![asin](https://latex.codecogs.com/gif.latex?f%28n%29%20%3D%20%5CTheta%20%28g%28n%29%29%20%5CRightarrow%20T%28n%29%20%3D%20%5CTheta%20%28n%20%5Ccdot%20log%28n%29%29)
</div>