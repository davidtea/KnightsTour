#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

// Stack in linked list structure
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include "node.h"

using namespace std;

enum ERRORS {FULL, EMPTY};

template<typename T = char>
class LinkedStack
{
public:
    LinkedStack(unsigned int s = 5);
    ~LinkedStack();
    LinkedStack(T data, int s = 5);
    LinkedStack(const LinkedStack<T> &other);
    LinkedStack<T>& operator=(const LinkedStack<T> &other);

    bool empty();
    bool full();
    void clear();
    int size();
    int capacity() const;

    void push(const T &data);
    T top();
    T pop();
    void resize(int x);

    LinkedStack<T>& operator<<(const T &data);
    LinkedStack<T>& operator>>(T &data);

    template<typename U>
    friend
    ostream& operator<<(ostream &out, const LinkedStack<U> &LinkedStack);

    template<typename U>
    friend
    istream& operator>>(istream &in, LinkedStack<U> &LinkedStack);

private:
    int myCapacity;
    int mySize;
    void copy(const LinkedStack<T> &other);
    void nukem();
    void newLinkedStack(int s);

    node<T> *head;
};


template<typename T>
LinkedStack<T>::LinkedStack(unsigned int s)
{
    head = NULL;
    resize(s);
}


template<typename T>
LinkedStack<T>::~LinkedStack()
{
    nukem();
}

template<typename T>
LinkedStack<T>::LinkedStack(T data, int s)
{
    head = NULL;
    resize(s);
    push(data);
}

template<typename T>
bool LinkedStack<T>::empty()
{
    return !head;
}

template<typename T>
bool LinkedStack<T>::full()
{
    return (mySize == myCapacity);
}

template<typename T>
void LinkedStack<T>::clear()
{
    nukem();
}

template<typename T>
int LinkedStack<T>::size()
{
    return mySize;
}

template<typename T>
int LinkedStack<T>::capacity() const
{
    return myCapacity;
}

template<typename T>
void LinkedStack<T>::resize(int x)
{
    nukem();
    newLinkedStack(x);
}

template<typename T>
LinkedStack<T>::LinkedStack(const LinkedStack<T> &other)
{
    copy(other);
}

template<typename T>
LinkedStack<T>& LinkedStack<T>::operator=(const LinkedStack<T> &other)
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}

template<typename T>
void LinkedStack<T>::copy(const LinkedStack<T> &other)
{
    newLinkedStack(other.capacity());
    node<T> *ptr;
    for(ptr = other.head; ptr; ptr = ptr->theLink())
        push(ptr->theData());
}

template<typename T>
void LinkedStack<T>::push(const T &data)
{
    cout << "Pushing " << data << " onto the stack." << endl;
    if(full())
        throw FULL;
    node<T> *newNode = new node<T>(data);
    newNode->theLink() = head;
    head = newNode;
    ++mySize;
}

template<typename T>
T LinkedStack<T>::top()
{
    if(empty())
        throw EMPTY;
    return head->theData();
}

template<typename T>
LinkedStack<T>& LinkedStack<T>::operator<<(const T &data)
{
    push(data);
    return *this;
}

template<typename T>
LinkedStack<T>& LinkedStack<T>::operator>>(T &data)
{
    data = pop();
    return *this;
}


template<typename T>
T LinkedStack<T>::pop()
{
    if(empty())
        throw EMPTY;
    T data = head->theData();
    node<T> *ptr = head;
    head = head->theLink();
    delete ptr;
    --mySize;
    return data;

}

template<typename T>
void LinkedStack<T>::nukem()
{
    node<T> *ptr = head;
    while(head)
    {
        ptr = head;
        head = head->theLink();
        delete ptr;
    }
}

template<typename T>
void LinkedStack<T>::newLinkedStack(int s)
{
    mySize = 0;
    myCapacity = s;
    head = NULL;
}


template<typename U>
ostream& operator<<(ostream &out, const LinkedStack<U> &stack)
{
    int i = -1;
    if(out == cout)
    {
        for(node<U> *ptr = stack.head; ptr; ptr = ptr->theLink())
            out<<"Stack["<<++i<<"] = "<<ptr->theData()<<endl;
    }
    else
    {
//        out<<"Capacity = "<<stack.capacity()<<endl;
        for(node<U> *ptr = stack.head; ptr; ptr = ptr->theLink())
            out<<ptr->theData()<<endl;
    }
    return out;
}

template<typename U>
istream& operator>>(istream &in, LinkedStack<U> &LinkedStack)
{
    string line;
    stringstream ss;
    int size;
    U data;
    if(in == cin)
    {
        cout<<"LinkedStack capacity: ";
        in>>size;
    }
    else
    {
        getline(in, line);
        ss<<line.substr(line.find('=')+1);
        ss>> size;
    }
    LinkedStack.resize(size);
    while(in>>data)
        LinkedStack.push(data);
    return in;
}

#endif // LINKEDSTACK_H
