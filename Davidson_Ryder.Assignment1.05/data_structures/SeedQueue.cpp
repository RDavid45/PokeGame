#include "SeedQueue.h"
#include <stdexcept>

SeedQueue(){
    front = nullptr;
    back = nullptr;
    size = 0;
}

~SeedQueue(){
    clear();
}

void clear(){
    while (!isEmpty()){
        dequeue();
    }
}

void enqueue(int x, int y, char c){
    Seed *newseed = new Seed(x, y, c);
    if (size > 0) {
        back->next = newseed;
        back = back->next;
    } else {
        front = back = newseed;
    }
}

Seed dequeue(){
    if (size <= 0){
        throw std::runtime_error("Queue is empty");
    }
    Seed *temp = front;
    
    Seed value;
    value.x = temp->x;
    value.y = temp->y;
    value.chr = temp->chr;
    value.next = nullptr;

    front = front->next;
    if (!front) {
        back = nullptr;
    }
    delete temp;
    size--;

    return value;
}

Seed peek() const{
    return *front;
}

int size() const{
    return size;
}

bool isEmpty() const{
    return front = back = nullptr;
}