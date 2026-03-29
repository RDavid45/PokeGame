#include "ArrayList.h"


ArrayList(){
    : data(nullptr), aSize(0), max(4)
    {
        data = new T[max];
    }
}

T get(size_t i) const
{
    return data[i];
}

T pop()
{  
    return data[--aSize];
}

void add(T item)
{
    if (aSize + 1 > max){
        grow();
    }
    data[aSize++] = item;
}

void add(T item, size_t i)
{
    if(item == NULL || i > aSize){
        return;
    }
    if (aSize + 1 > max){
        grow();
    }
    aSize++;
    for (int j = aSize -1; j > i; j--){
        swap(j, j - 1);
    }
    data[i] = item;
}

void swap(size_t i, size_t j)
{
    if (i > aSize -1 || j > aSize -1){
        return;
    }
    T temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}

T remove(size_t i)
{
    if (aSize <= 0 || i >= aSize){
        return NULL;
    }
    for (int j = aSize -1; j > i; j--){
        swap(j, j - 1);
    }
    return pop();
}

void grow()
{
    void *temp = (T *) realloc(a->data, a->oSize * a->max * 2);
    if (!temp){
        return;
    }
    a->max *= 2;
    a->data = temp;
}

~ArrayList(){
    delete[] data;
}

size_t arraySize(){
    return aSize;
}