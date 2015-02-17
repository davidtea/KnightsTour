#ifndef PQUEUE_H
#define PQUEUE_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <fstream>
#include "pnode.h"

using namespace std;

enum ERRORS1 {BAD_SIZE, FULL, EMPTY};

template<typename T, typename U>
class pQueue
{
    public:
        pQueue(int s = 5);
        ~pQueue();
        pQueue(const pQueue<T,U> &other);
        pQueue<T,U>& operator=(const pQueue<T,U> &other);

        bool empty();
        bool full();
        void resize(int s = 5);
        int size();
        int capacity();
        void clear();

        void enqueue(const T &d, const U &p);
        void dequeue(T &d);
        pQueue<T,U>& operator>>(T &d);
        T front();

        template<typename A, typename B>
        friend
        ostream& operator<<(ostream &out, const pQueue<A,B> &pQ);

        template<typename A, typename B>
        friend
        istream& operator>>(istream &in,  pQueue<A,B> &pQ);

    private:
        pnode<T,U> *head, *tail;
        int mySize, myCapacity;

        void nukem();
        void copy(const pQueue<T,U>&other);
};

template<typename T, typename U>
pQueue<T,U>::pQueue(int s)
{
   head = tail = NULL;
   mySize = 0;
   myCapacity = s;
}

template<typename T, typename U>
pQueue<T,U>::~pQueue()
{
    nukem();
}

template<typename T, typename U>
pQueue<T,U>::pQueue(const pQueue<T,U> &other)
{
    copy(other);
}

template<typename T, typename U>
pQueue<T,U>& pQueue<T,U>::operator=(const pQueue<T,U> &other)
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}

template<typename T, typename U>
bool pQueue<T,U>::empty()
{
    return !head;
}

template<typename T, typename U>
bool pQueue<T,U>::full()
{
    return mySize == myCapacity;
}

template<typename T, typename U>
void pQueue<T,U>::resize(int s)
{
    pnode<T,U> *ptr;
    if(s <= 0)
        throw BAD_SIZE;

    if(s > myCapacity)
        myCapacity = s;
    else
    {
        int times = myCapacity - s;
        for(int i = 0; i < times; ++i)
        {
            ptr = tail;
            tail = tail->nextLink();
            delete ptr;
        }

    }
}

template<typename T, typename U>
int pQueue<T,U>::size()
{
    return mySize;
}

template<typename T, typename U>
int pQueue<T,U>::capacity()
{
    return myCapacity;
}

template<typename T, typename U>
void pQueue<T,U>::clear()
{
    nukem();
}


//This works, excepting if the inserted pnode needs to go all the way to the front!!
template<typename T, typename U>
void pQueue<T,U>::enqueue(const T &d, const U &p)
{
    if(full())
        throw FULL;
    pnode<T,U> *newpnode = new pnode<T,U>(d,p), *ptr = tail;

    if(!head)
        head = tail = newpnode;
    else
    {
        if(!higherPriority(*tail, *newpnode))
        {
            tail->prevLink() = newpnode;
            newpnode->nextLink() = tail;
            tail = newpnode;
        }
        else
        {
            while(higherPriority(*ptr->nextLink(), *newpnode))
            {
                ptr = ptr->nextLink();
            }
            if(!ptr)
            {
                newpnode->prevLink() = head;
                head->nextLink() = newpnode;
                head = newpnode;
            }
            else
            {
                newpnode->prevLink()=ptr->prevLink();
                newpnode->prevLink()->nextLink() = newpnode;
                newpnode->nextLink() = ptr;
                ptr->prevLink() &&  (ptr->prevLink() = newpnode);
            }
        }
    }

    ++mySize;
}

template<typename T, typename U>
void pQueue<T,U>::dequeue(T &d)
{
    pnode<T,U> *ptr = head;
    if(empty())
        throw EMPTY;
    d = head->theData();
    head = head->prevLink();
    delete ptr;
    --mySize;
}

template<typename T, typename U>
pQueue<T,U>& pQueue<T,U>::operator>>(T &d)
{
    dequeue(d);
    return *this;
}

template<typename T, typename U>
T pQueue<T,U>::front()
{
    if(empty())
        throw EMPTY;
    return head->theData();
}

template<typename T, typename U>
void pQueue<T,U>::nukem()
{
    for(pnode<T,U> *ptr = head; head; ptr = head)
    {
        head = head->prevLink();
        delete ptr;
    }
    head = tail = NULL;
    mySize = 0;
}

template<typename T, typename U>
void pQueue<T,U>::copy(const pQueue<T,U>&other)
{
    mySize = 0;
    myCapacity = other.myCapacity;
    head = tail = NULL;
    pnode<T,U> *ptr = other.head;
    for(; ptr; ptr = ptr->prevLink())
    {
        enqueue(ptr->theData(), ptr->thePriority());
    }
}


template<typename A, typename B>
ostream& operator<<(ostream &out, const pQueue<A,B> &pQ)
{
    for(pnode<A,B> *ptr = pQ.head; ptr; ptr = ptr->prevLink())
        out<<*ptr<<" ";
    return out;
}

template<typename A, typename B>
istream& operator>>(istream &in,  pQueue<A,B> &pQ)
{
    pnode<A,B> newpnode;
    while(in>>newpnode)
        pQ.enqueue(newpnode.theData(),newpnode.thePriority());
    return in;
}

#endif // PQUEUE_H
