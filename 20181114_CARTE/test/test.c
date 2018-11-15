#include "../src/engine/scopa.h"
#include <stdio.h>
#include <stdlib.h>

int main(){

    Scopa_e* se = scopa_engine__init(4);
    scopa_engine__print_status(se);
    scopa_engine__reset(se);
    scopa_engine__print_status(se);
    int next = 0;
    do{
        scopa_engine__step(se);
        scopa_engine__print_status(se);

        
        printf("\n>");
        scanf("%d", &next);
    }while(next);
    return 0;

}