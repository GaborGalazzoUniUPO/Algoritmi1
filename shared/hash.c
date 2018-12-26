#include "hash.h"
#include <stdlib.h>

//TABELLE HASH CON LISTE DI COLLISIONE

hashtl_t hashtl__make(int dim)
{
    hashtl_t hashtl = malloc(dim * sizeof(list_t));
    for (int i = 0; i < dim; i++)
        hashtl[i] = list__init();
    return hashtl;
}

hentry_t *hentry__make(void *key, void *value)
{
    hentry_t *e = malloc(sizeof(hentry_t));
    e->key = key;
    e->value = value;
    return e;
}

void hashtl__destroy(hashtl_t hashtl, int dim, void (*destroy)(hentry_t *))
{
    for (int i = 0; i < dim; i++)
    {
        while (!list__is_empty(hashtl[i]))
        {
            hentry_t *e = list__remove(&hashtl[i]);
            destroy(e);
            free(e);
        }
    }
    free(hashtl);
}

void hashtl__insert(hashtl_t hashtl, int dim, hentry_t *entry, unsigned long (*hash)(void *, int i, int M))
{
    int index = hash(entry->key,0,dim);
    list__insert(entry, &hashtl[index]);
}

element_t hashtl__search(hashtl_t hashtl, int dim, void *key, unsigned long (*hash)(void *, int i, int M), bool (*keq)(void *, void *))
{
    int index = hash(key,0,dim);

    list_t list = hashtl[index];
    while (list != NULL)
    {
        hentry_t *entry = list->inf;
        if (keq(entry->key, key))
            return entry->value;
        list = list->next;
    }
    return NULL;
}

int hashtl__search_bm(hashtl_t hashtl, int dim, void *key, unsigned long (*hash)(void *, int i, int M), bool (*keq)(void *, void *))
{
    int index = hash(key,0,dim);

    list_t list = hashtl[index];
    int i = 1;
    while (list != NULL)
    {
        hentry_t *entry = list->inf;
        if (keq(entry->key, key))
            return i;
        list = list->next;
        i++;
    }
    return i;
}

void hashtl__print(hashtl_t hashtl, int dim, FILE *fp, char *key_format)
{
    for (int i = 0; i < dim; i++)
    {
        fprintf(fp, "[%d] -> ", i);
        list_t list = hashtl[i];
        while (list != NULL)
        {
            hentry_t *entry = list->inf;
            fprintf(fp, "(k: ");
            fprintf(fp, key_format, entry->key);
            fprintf(fp, ") -> ");
            list = list->next;
        }
        fprintf(fp, "NULL\n");
    }
}

//TABELE HASH CON INDIRIZZAMENTO APERTO

hashtsl_t hashtsl__make(int dim)
{
    hashtsl_t hashtsl = malloc(dim * sizeof(void *));
    for (int i = 0; i < dim; i++)
        hashtsl[i] = NULL;
    return hashtsl;
}
void hashtsl__print(hashtsl_t hashtsl, int dim, FILE *fp, char *key_format)
{
    for (int i = 0; i < dim; i++)
    {
        hentry_t *entry = hashtsl[i];
        fprintf(fp, "[%d] -> ", i);
        if (entry != NULL)
        {
            fprintf(fp, key_format, entry->key);
            fprintf(fp, "\n");
        }
        else
            fprintf(fp, "NULL\n");
    }
}
void hashtsl__insert(hashtsl_t hashtsl, int dim, hentry_t *entry, unsigned long(*hash)(void *, int i, int M))
{

    int i = 0;
    do
    {
        int index = hash(entry->key,i++,dim);
        if (hashtsl[index] == NULL)
        {
            hashtsl[index] = entry;
            break;
        }
    } while (i != dim);
}

element_t hashtsl__search(hashtsl_t hashtsl, int dim, void *key, unsigned long (*hash)(void *, int i, int M), bool (*keq)(void *, void *))
{
    int i = 0;
    hentry_t *entry = NULL;
    do
    {
        int index = hash(key, i++, dim);
        entry = hashtsl[index];
        if (entry != NULL && keq(entry->key, key))
        {
            return entry->value;
        }
    } while (entry != NULL && i != dim);
    return NULL;
}

int hashtsl__search_bm(hashtsl_t hashtsl, int dim, void *key, unsigned long (*hash)(void *, int i, int M), bool (*keq)(void *, void *))
{
    int i = 0;
    hentry_t *entry = NULL;
    int hit = 0;
    do
    {
        int index = hash(key,i++,dim);
        hit++;
        entry = hashtsl[index];
        if (entry != NULL && keq(entry->key, key))
        {
            return hit;
        }
    } while (entry != NULL && i != dim);
    return hit;
}
void hashtsl__destroy(hashtsl_t hashtsl, int dim, void (*destroy)(hentry_t *))
{
    for (int i = 0; i < dim; i++)
    {
        hentry_t *entry = hashtsl[i];
        if(entry!=NULL)
            destroy(entry);
        free(entry);
    }
}