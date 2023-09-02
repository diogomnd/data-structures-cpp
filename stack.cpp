#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::underflow_error;

template <class Item>
class Stack
{
private:
    int capacity;
    int top;
    Item *array;

public:
    Stack(int cap)
    {
        capacity = cap;
        top = -1;
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
        if (isEmpty())
            throw underflow_error("Stack is empty");
        return array[top];
    }

    void push(Item item)
    {
        if (size() == capacity)
            resize(2 * capacity);
        array[++top] = item;
    }

    Item pop()
    {
        if (isEmpty())
            throw underflow_error("Stack is empty");
        Item item = array[top--];
        if (size() > 0 && size() == capacity / 4)
            resize(capacity / 2);
        return item;
    }

    void resize(int newSize)
    {
        capacity = newSize;
        Item *temp = new Item[capacity];
        for (int i = 0; i < size(); i++)
            temp[i] = array[i];
        delete[] array;
        array = temp;
    }

    string toString()
    {
        stringstream stackString;
        stackString << "[";

        for (int i = 0; i < size() - 1; i++)
            stackString << array[i] << " ";

        stackString << array[top];
        stackString << "]";
        return stackString.str();
    }
};

int main()
{
    Stack<string> stack(3);
    stack.push("Hello");
    stack.push("World");
    stack.push("!");

    cout << "Stack size: " << stack.size() << endl;
    cout << "Top element: " << stack.peek() << endl;

    stack.pop();
    stack.pop();
    stack.push(",");
    stack.push("my");
    stack.push("friend");

    cout << "New stack size: " << stack.size() << endl;
    cout << "New top element: " << stack.peek() << endl;
    cout << "Stack: " << stack.toString() << endl;

    return 0;
}
