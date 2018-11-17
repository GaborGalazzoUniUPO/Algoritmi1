#include "../src/engine/scopa.h"
#include <stdio.h>
#include <stdlib.h>

void print_hello(){
    puts("Algoritmi 1, Lezione 2: Esercitazione \"CARTE\" - 2018-11-14");
    puts("Gabor Galazzo 20024195 II Anno -  A.A. 2018-2019");
    puts("\n\n");
    puts("Premi un tasto per continuare...");
    getchar();  
}


int main()
{
    print_hello();
    Scopa_e *se = scopa_engine__init(4);
    scopa_engine__print_status(se);
    puts("Engine Creato\n");
    puts("Premi un tasto per continuare...");
    getchar(); 
    scopa_engine__reset(se);
    scopa_engine__print_status(se);
    puts("Engine Inizializzato\n");
    puts("Da questo momento in poi digitare 1");
    puts("se si vuole fare un stem in avanti nella partita.");
    puts("Altrimenti si esce dal gioco.");
    int next = 0;
    printf("\n>");
    scanf("%d", &next);
    while (next)
    {

        scopa_engine__step(se);
        if (!scopa_engine__is_game_end(se))
            scopa_engine__print_status(se);
        else
        {
            scopa_engine__step(se);
            break;
        }

        printf("\n>");
        scanf("%d", &next);
    }
    return 0;
}