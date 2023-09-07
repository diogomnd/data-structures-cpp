#ifndef RESIZINGARRAYQUEUE_H
#define RESIZINGARRAYQUEUE_H

#include <stdexcept>
#include <sstream>
#include <string>

template <class Item>
class ResizingArrayQueue
{
private:
    Item *q;
    int capacity;
    int head;
    int tail;

    void resize(int newCapacity);

public:
    ResizingArrayQueue(int cap);
    ~ResizingArrayQueue();
    int getCapacity();
    int size();
    bool isEmpty();
    Item front();
    void enqueue(Item item);
    Item dequeue();
    std::string toString();
};

#endif