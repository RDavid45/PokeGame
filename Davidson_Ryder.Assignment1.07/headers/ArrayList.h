#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <cstddef>
#include <stdexcept>

template <typename T>
class ArrayList
{
private:
    T* data;
    size_t size_;
    size_t capacity_;

    void grow()
    {
        size_t newCap = capacity_ * 2;
        T* newData = new T[newCap];

        for (size_t i = 0; i < size_; ++i)
            newData[i] = data[i];

        delete[] data;
        data = newData;
        capacity_ = newCap;
    }

public:
    ArrayList()
        : data(new T[4]), size_(0), capacity_(4)
    {
    }

    ~ArrayList()
    {
        delete[] data;
    }

    T& operator[](size_t i)
    {
        return data[i];
    }

    const T& operator[](size_t i) const
    {
        return data[i];
    }

    T get(size_t i) const
    {
        if (i >= size_)
            throw std::out_of_range("ArrayList::get");
        return data[i];
    }

    T pop()
    {
        if (size_ == 0)
            throw std::out_of_range("ArrayList::pop");
        return data[--size_];
    }

    void add(const T& item)
    {
        if (size_ == capacity_)
            grow();
        data[size_++] = item;
    }

    void insert(const T& item, size_t i)
    {
        if (i > size_)
            throw std::out_of_range("ArrayList::insert");

        if (size_ == capacity_)
            grow();

        for (size_t j = size_; j > i; j--)
            data[j] = data[j - 1];

        data[i] = item;
        size_++;
    }

    void swap(size_t i, size_t j)
    {
        if (i >= size_ || j >= size_)
            throw std::out_of_range("ArrayList::swap");

        T temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }

    T remove(size_t i)
    {
        if (i >= size_)
            throw std::out_of_range("ArrayList::remove");

        for (size_t j = i; j + 1 < size_; j++)
            data[j] = data[j + 1];

        return pop();
    }

    size_t size() const
    {
        return size_;
    }
};

#endif