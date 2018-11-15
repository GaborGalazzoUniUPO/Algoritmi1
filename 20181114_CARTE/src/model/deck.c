#include "deck.h"
#include "card.h"

/**
 * Initialize a reqular 52 card french deck
 */
Deck* deck__init(){
    Deck* d = queue__init();
    for(int i = 1; i<=13;i++)
        for(int j = 0 ; j<4; j++)
            queue__enqueue(card__init(i,j), d);
    
    return d;
}

/**
 * RUFFLE SHUFFLE ALGORYTHM @link https://www.youtube.com/watch?v=rkUHEeKZxTs
 * detto anche merge(non)sort
 */


void deck__shuffle(Deck* deck){
    srand(time(NULL));
    int size = list__size(deck->primo);
    if(size < 2)
        return;
    Deck* support = queue__init();
    int i;
     //DIVIDO IL MAZZO IN DUE
    for(i = 0; i< size/2 ; i++){ 
        queue__enqueue(queue__dequeue(deck), support);
    }
   
     //FACCIO IL RUFFLE OGNI MAZZETTO CHE VADO A CREARE
    deck__shuffle(support);
    deck__shuffle(deck);
    
    Deck* result = queue__init();
    while(!queue__is_empty(deck) || !queue__is_empty(support)){ //FACCIO IL MERGE DEI DUE MAZZETTI ALTERNANDO LE CARTE A RANDOM
        if(rand() %2)
        {
            if(!queue__is_empty(deck))
                queue__enqueue(queue__dequeue(deck), result);
        }else{
            if(!queue__is_empty(support))
                queue__enqueue(queue__dequeue(support), result);
        }
    }
    (*deck) = (*result);
}

void deck__good_shuffle(Deck* deck){
    srand(time(NULL));
    int cuts = 3 + rand()%3;
    for(int i = 0; i<cuts; i++)
        deck__shuffle(deck);
}

int deck__is_empty(Deck* deck){
    return queue__is_empty(deck);
}


Card* deck__draw(Deck *deck){
    return queue__dequeue(deck);
}

void deck__print(Deck *deck){
    list__foreach(deck->primo, card__print_for_list);
}

int deck__count(Deck* deck){
	return list__size(deck->primo);
}