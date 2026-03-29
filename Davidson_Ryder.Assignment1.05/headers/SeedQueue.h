#ifndef SEEDQUEUE_H
#define SEEDQUEUE_H

#include <new> // for std::nothrow

class SeedQueue
{
private:
    struct Seed
    {
        int x;
        int y;
        char chr;
        Seed* next;

        Seed(int xVal, int yVal, char c)
            : x(xVal), y(yVal), chr(c), next(nullptr) {}
        };

    Seed* front;
    Seed* back;
    int size;

public:
    SeedQueue();

    ~SeedQueue();

    void clear();

    void enqueue(int x, int y, char c);

    Seed *dequeue();

    Seed *peek() const;

    int size() const;

    bool isEmpty() const;
};

#endif