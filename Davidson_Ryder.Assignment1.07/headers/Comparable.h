#ifndef COMPARABLE_H
#define COMPARABLE_H

template <typename T>
class Comparable{
    public:
        virtual ~Comparable() = default;

        virtual int compareTo(const T item) const = 0;
};

#endif