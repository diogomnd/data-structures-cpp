#include <stdexcept>

template <typename Item>

class Stack
{
private:
    Item* array;
    int top;

public:
    Stack(int capacity) : top(-1)
    {
        array = new Item[capacity];
    }

    ~Stack()
    {
        delete[] array;
    }

    int size()
    {
        return top + 1;
    }

    bool isEmpty()
    {
        return top < 0;
    }

    Item peek()
    {
        if (isEmpty()) throw std::underflow_error("Stack is empty");
        return array[top];
    }

    void push(Item element)
    {
        if (size() == sizeof(array) / sizeof(array[0])) 
            resize(2 * sizeof(array) / sizeof(array[0]));
        top++;
        array[top] = element;
    }

    Item pop()
    {
        if (isEmpty()) throw std::underflow_error("Stack is empty");
        if (size() > 0 && size() == (sizeof(array) / sizeof(array[0])) / 4)
            resize((sizeof(array) / sizeof(array[0])) / 2);
        Item item = array[top];
        top--;
        return item;
    }

    void resize(int newSize)
    {
        Item* temp = new Item[newSize];
        for (int i = 0; i < size(); i++)
            temp[i] = array[i];
        delete[] array;
        array = temp;
    }

};

