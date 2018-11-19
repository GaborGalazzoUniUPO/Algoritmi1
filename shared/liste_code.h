#ifndef ELEMENT_H
#define ELEMENT_H
typedef void* Element;
#endif


/* *************************************************************************************** */
/* Definizione del tipo lista i cui elementi sono di tipo Element (per il momento int)
 * con le operazioni di inserzione in testa, estrazione dalla testa,  accesso all'emento
 * in testa (primo),  costruzione della lista vuota (makeLista) e test se vuota (is_empty)     */
/* *************************************************************************************** */

#ifndef NODE_LIST_H
#define NODE_LIST_H
struct Node {
    Element    inf;
    struct Node *next;
} Node;

typedef struct Node *List ;
#endif 


int list__is_empty(List);
void list__insert(Element, List *);
Element list__remove(List *);
Element list__first(List);
List list__init();
int list__size(List list);
void list__sort(List list,int (*f)(Element, Element));
void list__foreach(List list, void (*f)(Element));


/* *************************************************************************************** */
/* Definizione del tipo Stack con le operazioni pop push top test se vuota (emptyP) e
 * costruzione della pila vuota (makePila) implementato con una lista                      */
/* *************************************************************************************** */

#ifndef STACK_H
#define STACK_H
typedef List Stack;

#endif

int stack__is_empty(Stack);
void stack__push(Element,Stack*);
Element stack__pop(Stack*);
Element stack__top(Stack);
Stack stack__init();

/* *************************************************************************************** */
/* Definizione del tipo Coda con le operazioni enqueue dequeue first test se vuota (emptyC)
 * costruzione dalla coda vuota (makeCoda) implementato con una struttura contenente
 * una lista (cont) e puntatori al primo e ultimo elemento  (primo, ultimo)                  */
/* *************************************************************************************** */

#ifndef QUEUE_H
#define QUEUE_H
typedef struct queue {
    List primo;
    List ultimo;
} Queue;
#endif


int queue__is_empty(Queue*);
void queue__enqueue(Element,Queue*);
Queue* queue__init();
Element queue__dequeue(Queue*);
Element queue__first(Queue*);
