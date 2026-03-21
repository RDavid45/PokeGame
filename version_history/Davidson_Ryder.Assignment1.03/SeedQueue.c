#include "seedQueue.h"
#include <stdio.h>
#include <stdlib.h>



int initSeedQueue(struct SeedQueue *q)
{
    q->back = NULL;
    q->front = NULL;
    q->size = 0;

    return 0;
}


int destroySeedQueue(struct SeedQueue *q)
{
    struct seed *temp;
    while ((temp = q->front)){
        q->front = q->front->next;
        free(temp);        
    }
    q->size = 0;
    q->back = NULL;

    return 0;
}


int enqueueSeed(struct SeedQueue *q, int x, int y, char c)
{
    struct seed *temp;

    if (!(temp = malloc(sizeof (*temp)))){
        //malloc failed
        return -1;
    }

    temp->x= x;
    temp->y = y;
    temp->chr = c;
    temp->next = NULL;
    if (q->size == 0){
        q->front = temp;
    } else {
        q->back->next = temp;
    }
    q->back = temp;

    q->size++;

    return 0;
}


int dequeueSeed(struct SeedQueue *q, int *x, int *y, char *c)
{
    struct seed *temp;

    if(!q->front){
        return -1;
    }

    temp = q->front;
    q->front = q->front->next;
    q->size--;

    if (!q->front){
        q->back = NULL;
    }


    *x = temp->x;
    *y = temp->y;
    *c = temp->chr;

    free(temp);

    return 0;
}


int peekSeedQueue(struct SeedQueue *q, int *x, int *y, char *c)
{
    if (!q->front){
        return -1;
    }
    *x = q->front->x;
    *y = q->front->y;
    *c = q->front->chr;

    return 0;
}


int sizeQueue(struct SeedQueue *q, int *size)
{
    *size = q->size;

    return 0;
}

int isEmptyQueue(struct SeedQueue *q)
{
    if (q->back == NULL && q->front == NULL){
        return 1;
    }
    return 0;
}