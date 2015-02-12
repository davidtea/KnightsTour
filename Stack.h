#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include "basestack.h"

using namespace std;

enum ERRORS {FULL, EMPTY};

template<typename T>
class Stack : public baseStack
{
    public:
        Stack(unsigned int s = 5);
        Stack(T data, int s = 5);
        Stack(const Stack<T> &other);
        Stack<T>& operator=(const Stack<T> &other);

        void push(const T &data);
        T top();
        T pop();
        void resize(int x);

        Stack<T>& operator<<(const T &data);
        Stack<T>& operator>>(T &data);

        template<typename U>
        friend
        ostream& operator<<(ostream &out, const Stack<U> &stack);

        template<typename U>
        friend
        istream& operator>>(istream &in, Stack<U> &stack);

    protected:

    private:
        void copy(const Stack<T> &other);
        void nukem();
        void newStack(int s);
        void makeStack(int s);
        void deleteStack();
};

template<typename T>
Stack<T>::Stack(unsigned int s)
{
    resize(s);
}

template<typename T>
Stack<T>::Stack(T data, int s)
{
    resize(s);
    push(data);
}


template<typename T>
void Stack<T>::resize(int x)
{
    deleteStack();
    makeStack(x);
    newStack(x);
}

template<typename T>
Stack<T>::Stack(const Stack<T> &other)
{
    copy(other);
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T> &other)
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}

template<typename T>
void Stack<T>::copy(const Stack<T> &other)
{
    resize(other.capacity());
    for(int i = 0; i < other.size(); ++i)
        (*(T*)stack[i]) = (*(T*)other.stack[i]);
}

template<typename T>
void Stack<T>::push(const T &data)
{
    if(full())
        throw FULL;
    increment();
    *((T *)stack[topOfStack()]) = data;
}

template<typename T>
T Stack<T>::top()
{
    if(empty())
        throw EMPTY;
    return stack[size()-1];
}

template<typename T>
Stack<T>& Stack<T>::operator<<(const T &data)
{
    push(data);
    return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator>>(T &data)
{
    data = pop();
    return *this;
}


template<typename T>
T Stack<T>::pop()
{
    if(empty())
        throw EMPTY;
    T data =*((T *) stack[topOfStack()]);
    decrement();
    return data;

}

template<typename T>
void Stack<T>::nukem()
{
    for(int i = 0; i < size()-1; ++i)
        delete (T*)stack[i];
}

template<typename T>
void Stack<T>::newStack(int s)
{
    for(int i = 0; i < s; i++)
        stack[i] = new T;
}


template<typename U>
ostream& operator<<(ostream &out, const Stack<U> &stack)
{
    if(out == cout)
    {
        for(int i = stack.size()-1; i>-1; --i)
            out<<"stack["<<i<<"] = "<<*(U*)stack.stack[i]<<endl;
//        *((T *)stack[topOfStack()]) = data;
    }
    else
    {
        out<<"Capacity = "<<stack.capacity()<<endl;
        for(int i = 0; i < stack.size(); i++)
            out<<(U*)stack.stack[i]<<endl;
    }
    return out;
}


template<typename U>
istream& operator>>(istream &in, Stack<U> &stack)
{
    string line;
    stringstream ss;
    int size;
    U data;
    if(in == cin)
    {
        cout<<"Input Stack capacity: ";
        in>>size;
    }
    else
    {
        getline(in, line);
        ss<<line.substr(line.find('=')+1);
        ss>> size;
    }
    stack.resize(size);
    while(in>>data && !stack.full())
        stack.push(data);
    return in;
}



template<typename T>
void Stack<T>::deleteStack()
{
    delete [] stack;
}

template<typename T>
void Stack<T>::makeStack(int s)
{
    total = s;
    stack = new void*[s];
    clear();
}

#endif // STACK_H
