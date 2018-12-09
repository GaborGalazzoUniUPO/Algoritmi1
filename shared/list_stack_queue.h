#ifndef ELEMENT_H
#define ELEMENT_H
typedef void* element_t;
#endif


/* *************************************************************************************** */
/* Definizione del tipo lista i cui elementi sono di tipo element_t (per il momento int)
 * con le operazioni di inserzione in testa, estrazione dalla testa,  accesso all'emento
 * in testa (first),  costruzione della lista vuota (makeLista) e test se vuota (is_empty)     */
/* *************************************************************************************** */

#ifndef NODE_LIST_H
#define NODE_LIST_H
typedef struct node {
    element_t    inf;
    struct node *next;
} node_t;

typedef node_t* list_t ;
#endif


int list__is_empty(list_t);
void list__insert(element_t, list_t *);
element_t list__remove(list_t *);
element_t list__first(list_t);
list_t list__init();
int list__size(list_t list);
void list__sort(list_t list,int (*f)(element_t, element_t));
void list__foreach(list_t list, void (*f)(element_t));


/* *************************************************************************************** */
/* Definizione del tipo stack_t con le operazioni pop push top test se vuota (emptyP) e
 * costruzione della pila vuota (makePila) implementato con una lista                      */
/* *************************************************************************************** */

#ifndef STACK_H
#define STACK_H
typedef list_t stack_t;

#endif

int stack__is_empty(stack_t);
void stack__push(element_t,stack_t*);
element_t stack__pop(stack_t*);
element_t stack__top(stack_t);
stack_t stack__init();

/* *************************************************************************************** */
/* Definizione del tipo Coda con le operazioni enqueue dequeue first test se vuota (emptyC)
 * costruzione dalla coda vuota (makeCoda) implementato con una struttura contenente
 * una lista (cont) e puntatori al first e last elemento  (first, last)                  */
/* *************************************************************************************** */

#ifndef QUEUE_H
#define QUEUE_H
typedef struct {
    list_t first;
    list_t last;
} queue_t;
#endif


int queue__is_empty(queue_t*);
void queue__enqueue(element_t,queue_t*);
queue_t* queue__init();
element_t queue__dequeue(queue_t*);
element_t queue__first(queue_t*);
