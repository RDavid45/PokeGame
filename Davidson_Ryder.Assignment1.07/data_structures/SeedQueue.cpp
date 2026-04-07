#include "SeedQueue.h"
#include <stdexcept>

SeedQueue::SeedQueue(){
    front = nullptr;
    back = nullptr;
    this->size = 0;
}

SeedQueue::~SeedQueue(){
    clear();
}

void SeedQueue::clear(){
    while (!isEmpty()){
        dequeue();
    }
    size = 0;
}

void SeedQueue::enqueue(int x, int y, char c){
    Seed *newseed = new Seed(x, y, c);
    if (size > 0) {
        back->next = newseed;
        back = back->next;
    } else {
        front = back = newseed;
    }
    size++;
}

SeedQueue::Seed *SeedQueue::dequeue(){
    if (size <= 0){
        throw std::runtime_error("Queue is empty");
    }
    Seed *temp = front;
    
    Seed *value = new Seed(temp->x, temp->y, temp->chr);

    front = front->next;
    if (!front) {
        back = nullptr;
    }
    delete temp;
    size--;

    return value;
}

const SeedQueue::Seed *SeedQueue::peek() const{
    return front;
}

int SeedQueue::getSize() const{
    return size;
}

bool SeedQueue::isEmpty() const{
    return back == nullptr;
}