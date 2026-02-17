#include <stdio.h>
#include <stdlib.h>
#include "Heap.h"

#define AT(h, k) ((void *)((char *) (h)->heap->data + (size_t)(k) * (h)->heap->oSize))

int heapifyDown(Heap *h, int i);
int heapifyUp(Heap *h, int i);


int initHeap(Heap *h, int (*compare)(const void *p1, const void *p2), size_t oSize)
{
    if (!h || !compare || oSize == 0){return -1;}

    if (!(h->heap = malloc(sizeof (ArrayList)))){
        return -1;
    }

    if (ArrayListinit(h->heap, oSize)){
        free(h->heap);
        h->heap = NULL;
        return -1;
    }

    h->compare = compare;
    return 0;
}

int heapAdd(Heap *h, void *item)
{
    if(ArrayListadd(h->heap, item)){
        return -1;
    }
    heapifyUp(h, h->heap->aSize -1);
    return 0;
}

int heapPop(Heap *h, void *item)
{
    if (!h || !h->heap || h->heap->aSize == 0){
        return -1;
    }
    return heapDelete(h, item, 0);
    
}

int heapDelete(Heap *h, void *removed, int i)
{
    if (i > h->heap->aSize -1 || i < 0){
        return -1;
    }
    ArrayListswap(h->heap, i, h->heap->aSize - 1);
    ArrayListpop(h->heap, removed);
    if (i > 0 && h->compare(AT(h,i), AT(h,(i-1)/2)) < 0){
        heapifyUp (h, i);
    } else {
        heapifyDown(h, i);
    }
    return 0;
}

int heapPeek(Heap *h, void *min)
{
    if (ArrayListget(h->heap, min, 0)){
        return -1;
    }
    return 0;
}

Heap *makeHeap(ArrayList *a,  int (*compare)(const void *p1, const void *p2))
{
    Heap *h = malloc(sizeof (Heap));
    h->heap = a;
    h->compare = compare;
    int current;
    if (h->heap->aSize <= 1) {return h;}
    for (current  = (h->heap->aSize - 1) / 2; current >= 0; current--){
        heapifyDown(h, current);
    }

    return h;
}

int heapifyDown(Heap *h, int i)
{
    int n = h->heap->aSize -1;
    int left = 2* i +1;
    int right = 2 * i + 2;
    
    if (left > n) {return 0;}
    int best = left;

    if (right <= n && h->compare(AT(h, left), AT(h, right)) > 0){
        best = right;
    }
    if (h->compare(AT(h, i), AT(h, best)) > 0){
            ArrayListswap(h->heap, i, best);
            return heapifyDown(h, best);
    }
    return 0;
}

int heapifyUp(Heap *h, int i)
{
    int parent;

    if (i >= h->heap->aSize){
        return -1;
    } else if (i < 0){
        return -1;
    } else if (i == 0){
        return 0;
    }

    parent = (i-1) /2;

    if (h->compare(AT(h, i), AT(h, parent)) < 0){
            ArrayListswap(h->heap, i, parent);
            return heapifyUp(h, parent);
    }

    return 0;
}

int heapEmpty(Heap *h)
{
    return (h->heap->aSize == 0) ? 1 : 0;
}

int heapDestroy(Heap *h)
{
    if (!h){return 0;}

    if (h->heap){
        ArrayListdestroy(h->heap);
        free(h->heap);
        h->heap = NULL;
    }

    return 0;
}