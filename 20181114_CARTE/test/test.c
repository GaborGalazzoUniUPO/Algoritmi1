#include "../src/engine/scopa.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{

    Scopa_e *se = scopa_engine__init(4);
    scopa_engine__print_status(se);
    scopa_engine__reset(se);
    scopa_engine__print_status(se);
    int next = 0;
    printf("\n>");
    scanf("%d", &next);
    while (next)
    {
       
        scopa_engine__step(se);
         if (!scopa_engine__is_game_end(se))
            scopa_engine__print_status(se);
            else{
                scopa_engine__step(se);
                break;
            }
        
        printf("\n>");
        scanf("%d", &next);
    }
    return 0;
}