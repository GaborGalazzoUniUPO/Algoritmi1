#include <stdio.h>
#include <stdlib.h>

#include "list_stack_queue.h"



/* *************************************************************************************** */
/* Implementazione funzioni delle liste                                                  */
/* *************************************************************************************** */

int list__is_empty(list_t l){
    return (l == NULL);
}

void list__insert(element_t el, list_t *l){
    list_t l1 = malloc(sizeof(node_t));
    if (l1 != NULL) {
        l1->inf = el;
        l1->next = (*l);
        (*l) = l1;
    }}

element_t list__first(list_t l){
    if (l != NULL)
        return (l->inf);
    return NULL;
}

element_t list__remove(list_t *lptr){
    if ((* lptr) != NULL) {
        element_t el=list__first(*lptr);
        list_t l = (* lptr);
        (* lptr) = (* lptr)->next;
        free(l);
        return el;}
        return NULL;
}

list_t list__init(){
    return NULL;
}

int list__size(list_t list){
    int i = 0;
    while(list != NULL){
        i++;
        list = list->next;
    }
    return i;
}

// Recursive function to insert an item x in sorted way
void list__sort(list_t list, int (*f)(element_t, element_t))
{
    list_t helper = list__init();
    while (!list__is_empty(list))
    {
        element_t element_t = list__remove(&list);
        while (!list__is_empty(helper) && f(list__first(helper), element_t) <0)
        {
            list__insert(list__remove(&helper), &list);
        }
        list__insert(element_t, &helper);
    }
    while (!list__is_empty(helper))
    {
        list__insert(list__remove(&helper), &list);
    }
}

void list__foreach(list_t list, void (*f)(element_t)){
    while(list != NULL){
        f(list->inf);
        list = list->next;
    }
}

/* *************************************************************************************** */
/* Implementazione funzioni delle pile                                                  */
/* *************************************************************************************** */

int stack__is_empty(stack_t p){
    return list__is_empty(p);
}

void stack__push(element_t el,stack_t *p){
    list__insert(el, p);
}

element_t stack__pop(stack_t *p){
    return list__remove(p);
}

element_t stack__top(stack_t p){
    return list__first(p);
}

stack_t stack__init(){
    return list__init();
}

/* *************************************************************************************** */
/* Implementazione funzioni delle code                                                  */
/* *************************************************************************************** */


int queue__is_empty(queue_t* c){
    return list__is_empty(c->first);
}

void queue__enqueue(element_t el,queue_t *c){
    list_t l=NULL;
    list__insert(el, &l);
    if(queue__is_empty(c))
    {
        c->first = l;
        c->last = l;

    } else {
        c->last->next = l;
        c->last = l;
    }
}

element_t queue__dequeue(queue_t* c){
    return list__remove(&(c->first));
}

element_t queue__first(queue_t* c){
    return list__first(c->first);
}

queue_t* queue__init(){
    queue_t* c = malloc(sizeof(queue_t));
    c->first = c->last = NULL;
    return c;
}



