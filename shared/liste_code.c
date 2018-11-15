#include <stdio.h>
#include <stdlib.h>

#include "liste_code.h"



/* *************************************************************************************** */
/* Implementazione funzioni delle liste                                                  */
/* *************************************************************************************** */

int list__is_empty(List l){
    return (l == NULL);
}

void list__insert(Element el, List *l){
    List l1=NULL;
    l1 = (List) malloc(sizeof(Node));
    if (l1 != NULL) {
        l1 ->inf = el;
        l1 ->next = (*l);
        (*l) = l1;
    }}

Element list__first(List l){
    if (l != NULL)
        return (l->inf);
    return NULL;
}

Element list__remove(List *lptr){
    if ((* lptr) != NULL) {
        Element el=list__first(*lptr);
        List l = (* lptr);
        (* lptr) = (* lptr)->next;
        free(l);
        return el;}
        return NULL;
}

List list__init(){
    return NULL;
}

int list__size(List list){
    int i = 0;
    while(list != NULL){
        i++;
        list = list->next;
    }
    return i;
}

// Recursive function to insert an item x in sorted way
void list__sort(List list, int (*f)(Element, Element))
{
    List helper = list__init();
    while (!list__is_empty(list))
    {
        Element element = list__remove(&list);
        while (!list__is_empty(helper) && f(list__first(helper), element) <0)
        {
            list__insert(list__remove(&helper), &list);
        }
        list__insert(element, &helper);
    }
    while (!list__is_empty(helper))
    {
        list__insert(list__remove(&helper), &list);
    }
}

void list__foreach(List list, void (*f)(Element)){
    while(list != NULL){
        f(list->inf);
        list = list->next;
    }
}

/* *************************************************************************************** */
/* Implementazione funzioni delle pile                                                  */
/* *************************************************************************************** */

int stack__is_empty(Stack p){
    return list__is_empty(p);
}

void stack__push(Element el,Stack *p){
    list__insert(el, p);
}

Element stack__pop(Stack *p){
    return list__remove(p);
}

Element stack__top(Stack p){
    return list__first(p);
}

Stack stack__init(){
    return list__init();
}

/* *************************************************************************************** */
/* Implementazione funzioni delle code                                                  */
/* *************************************************************************************** */


int queue__is_empty(Queue* c){
    return list__is_empty(c->primo);
}

void queue__enqueue(Element el,Queue *c){
    List l=NULL;
    list__insert(el, &l);
    if(queue__is_empty(c))
    {
        c->primo = l;
        c->ultimo = l;

    } else {
        c->ultimo->next = l;
        c->ultimo = l;
    }
}

Element queue__dequeue(Queue* c){
    return list__remove(&(c->primo));
}

Element queue__first(Queue* c){
    return list__first(c->primo);
}

Queue* queue__init(){
    Queue* c = malloc(sizeof(Queue));
    c->primo = c->ultimo = NULL;
    return c;
}



