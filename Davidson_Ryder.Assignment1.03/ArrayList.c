#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ArrayList.h"


int ArrayListinit(ArrayList *a, size_t objectSize){
    if (!a || objectSize == 0){ return -1;}
    a->max = 4;
    a->aSize = 0;
    a->oSize = objectSize;
    a->data = malloc(a->oSize * a->max);
    return 0;
}
int ArrayListget(ArrayList *a, void* item, int i)
{
    if (!a || i > a->aSize -1 || i < 0){
        return -1;
    }
    memcpy(item, (char*)a->data + (i) * a->oSize, a->oSize);
    return 0;
}
int ArrayListpop(ArrayList *a, void *removed)
{
    if (a->aSize <= 0){
        return -1;
    }
    memcpy(removed, (char*)a->data + (a->aSize - 1) * a->oSize, a->oSize);
    a->aSize--;
    return 0;
}
int ArrayListinsert(ArrayList *a,  void *item, int i)
{
    if(!a || !item || i > a->aSize || i < 0){
        return -1;
    }
    if (a->aSize + 1 > a->max){
        growArrayList(a);
    }
    memmove((char*)a->data + (i+1) * a->oSize, (char*)a->data + (i) * a->oSize, a->oSize * (a->aSize - i));
    memcpy((char*)a->data + (i) * a->oSize, item, a->oSize);
    a->aSize++;
    return 0;
}
int ArrayListswap(ArrayList *a, int i, int j)
{
    if (i < 0 || i > a->aSize -1 || j < 0 || j > a->aSize -1){
        return -1;
    }
    void *temp = malloc(a->oSize);
    memcpy(temp, (char*)a->data + (i) * a->oSize, a->oSize);
    memcpy((char*)a->data + (i) * a->oSize, (char*)a->data + (j) * a->oSize, a->oSize);
    memcpy((char*)a->data + (j) * a->oSize, temp, a->oSize);
    free(temp);
    return 0;
}
int ArrayListadd(ArrayList *a, void *item)
{
    if (a->aSize + 1 > a->max){
        if(growArrayList(a)){
            return -1;
        }
    }
    memcpy((char*)a->data + a->oSize * a->aSize, item, a->oSize);
    a->aSize++;
    return 0;
}
int ArrayListremove(ArrayList *a, int i, void*removed)
{
    if (a->aSize <= 0){
        return -1;
    }
    if (i == a->aSize -1){
        ArrayListpop(a, removed);
        return 0;
    }
    memcpy(removed, (char*)a->data + (i) * a->oSize, a->oSize);
    a->aSize--;
    memmove((char*)a->data + (i) * a->oSize, (char*)a->data + (i+1) * a->oSize, a->oSize * (a->aSize - i));
    return 0;
}

int growArrayList(ArrayList *a)
{
    a->max *= 2;
    void *temp = realloc(a->data, a->oSize * a->max);
    if (!temp){
        return -1;
    }
    a->data = temp;
    return 0;
}

int ArrayListdestroy(ArrayList *a){
    free(a->data);
    return 0;
}