#include "ResizingArrayQueue.h"
#include <stdexcept>
#include <sstream>
#include <string>
#include <iostream>
#include <cassert>

using std::string;
using std::stringstream;
using std::cout;

template <class Item>
ResizingArrayQueue<Item>::ResizingArrayQueue(int cap)
{
    this->capacity = cap + 1;
    this->q = new Item[capacity];
    this->head = this->tail = 0;
}

template <class Item>
ResizingArrayQueue<Item>::~ResizingArrayQueue() { delete[] q; }

template <class Item>
int ResizingArrayQueue<Item>::getCapacity() { return capacity; }

template <class Item>
int ResizingArrayQueue<Item>::size() { return (capacity - head + tail) % capacity; }

template <class Item>
bool ResizingArrayQueue<Item>::isEmpty() { return head == tail; }

template <class Item>
Item ResizingArrayQueue<Item>::front()
{
    if (isEmpty())
        throw new std::underflow_error("Stack is empty.");
    return q[head];
}

template <class Item>
void ResizingArrayQueue<Item>::enqueue(Item item)
{
    if (size() == capacity - 1)
        resize(2 * capacity);
    q[tail] = item;
    tail = (tail + 1) % capacity;
}

template <class Item>
Item ResizingArrayQueue<Item>::dequeue()
{
    if (isEmpty())
        throw new std::underflow_error("Stack is empty");
    Item item = q[head];
    q[head] = -1;
    head = (head + 1) % capacity;
    if (size() <= capacity / 4)
        resize(capacity / 2);
    return item;
}

template <class Item>
string ResizingArrayQueue<Item>::toString()
{
    stringstream stringQueue;
    int size = this->size();
    stringQueue << "[";
    for (int i = 0; i < size; i++)
    {
        stringQueue << q[(head + i) % capacity];
        if (i < size - 1)
            stringQueue << " ";
    }
    stringQueue << "]";
    return stringQueue.str();
}

template <class Item>
void ResizingArrayQueue<Item>::resize(int newCapacity)
{
    Item *temp = new Item[newCapacity];
    int size = this->size();
    for (int i = 0; i < size; i++)
        temp[i] = q[(head + i) % capacity];
    delete[] q;
    q = temp;
    head = 0;
    tail = size;
    capacity = newCapacity;
}

int main(int argc, char *argv[])
{
    // Test 1: Initialize a queue and check if it's empty
    ResizingArrayQueue<int> queue(5);
    assert(queue.isEmpty() == true);
    assert(queue.size() == 0);

    // Test 2: Enqueue elements and check its size
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    assert(queue.isEmpty() == false);
    assert(queue.size() == 3);

    // Test 3: Check the head of the queue
    assert(queue.front() == 1);

    // Test 4: Dequeue elements and check its size
    int item = queue.dequeue();
    assert(item == 1);
    assert(queue.size() == 2);

    item = queue.dequeue();
    assert(item == 2);
    assert(queue.size() == 1);
    assert(queue.front() == 3);

    // Test 5: Enqueue more elements to trigger resizing
    queue.enqueue(4);
    queue.enqueue(5);
    queue.enqueue(6);
    queue.enqueue(7);
    queue.enqueue(8);
    assert(queue.size() ==  6);

    // Test 6: Check the resizing
    assert(queue.getCapacity() == 12);

    // Test 7: Dequeue more elements to trigger the resizing
    item = queue.dequeue();
    item = queue.dequeue();
    item = queue.dequeue();
    assert(queue.size() == 3);

    // Test 8: Check the resizing
    assert(queue.getCapacity() == 6);

    // Test 9:: Check toString
    string s = queue.toString();
    assert(s == "[6 7 8]");

    // Test 10: Empty the queue and check if it's empty
    queue.dequeue();
    queue.dequeue();
    queue.dequeue();
    assert(queue.isEmpty() == true);
    assert(queue.size() == 0);
    s = queue.toString();
    assert(s == "[]");

    cout << "All tests passed succesfully!\n"; 

    return 0;
}