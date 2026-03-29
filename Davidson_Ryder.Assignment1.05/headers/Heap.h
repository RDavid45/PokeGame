#ifndef HEAP_H
#define HEAP_H

#include "ArrayList.h"
#include "Comparable.h"

template <typename T>
class Heap  
{
    private:
        ArrayList<T> *heap;
        
        void heapifyUp(size_t i){
            int parent;

            if (i >= heap->size()){
                return;
            } else if (i == 0){
                return;
            }

            parent = (i-1) /2;

            if (heap->get(i).compareTo(heap->get(parent)) < 0){
                    heap->swap(i, parent);
                    heapifyUp(parent);
            }
        }


        void heapifyDown(size_t i){
            int n = heap->size() -1;
            int left = 2* i +1;
            int right = 2 * i + 2;
            
            if (left > n) {return;}
            int best = left;

            if (right <= n && heap->get(left).compareTo(heap->get(right)) > 0){
                best = right;
            }
            if (heap->get(i).compareTo(heap->get(best)) > 0){
                    heap->swap(i, best);
                    heapifyDown(best);
            }
        }
    public:
        Heap(){ heap = new ArrayList<>(); }

        //Heap(const ArrayList &a){}

        ~Heap(){ delete heap; }

        bool isEmpty(){
            return heap->size() == 0;
        }

        T peek(){
            return heap->get(0);
        }

        T pop(){
            return heap->remove(0);
        }

        void add(T item){
            heap->add(item);
            heapifyUP(heap->size() -1);
        }

        T remove(size_t i){
            heap->swap(heap->size() -1, i);
            heapifyDown(i);
            return heap->pop();
        }
};

#endif