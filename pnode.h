#ifndef PNODE_H
#define PNODE_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;
//      Data         Priority
template<typename T, typename U>
class pnode
{
    public:
        pnode();
        pnode(const T &,const U&);
        ~pnode();
        pnode(const pnode<T,U> &);
        pnode<T,U> operator=(const pnode<T,U> &);
        U& thePriority();
        T& theData();
        pnode<T,U>*& nextLink();
        pnode<T,U>*& prevLink();

        template<typename A,typename B>
        friend
        ostream& operator<<(ostream &, const pnode<A,B> &);


        template<typename A,typename B>
        friend
        istream& operator>>(istream &, pnode<A,B> &);

        template<typename A,typename B>
        friend
        bool higherPriority(pnode<A,B> &, pnode<A,B> &);


    private:

        T data;
        U priority;
        pnode<T,U> *next, *prev;

        void copy(const pnode<T,U> &);
        void nukem();
};

template<typename T, typename U>
pnode<T,U>::pnode()
{
    nukem();
}

template<typename T, typename U>
pnode<T,U>::pnode(const T &d,const U &p)
{
    data = d;
    priority = p;
    next = prev = NULL;
}

template<typename T, typename U>
pnode<T,U>::~pnode()
{
    nukem();
}

template<typename T, typename U>
pnode<T,U>::pnode(const pnode<T,U> &other)
{
    copy(other);
}

template<typename T, typename U>
pnode<T,U> pnode<T,U>::operator=(const pnode<T,U> &other)
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}


template<typename T, typename U>
U& pnode<T,U>::thePriority()
{
    return priority;
}

template<typename T, typename U>
T& pnode<T,U>::theData()
{
    return data;
}

template<typename T, typename U>
pnode<T,U>*& pnode<T,U>::nextLink()
{
    return next;
}


template<typename T, typename U>
pnode<T,U>*& pnode<T,U>::prevLink()
{
    return prev;
}


template<typename T, typename U>
void pnode<T,U>::copy(const pnode<T,U> &other)
{
    priority = other.priority;
    data = other.data;
    next = prev = NULL;
}

template<typename T, typename U>
void pnode<T,U>::nukem()
{
    next = prev = NULL;
    data = T();
    priority = U();
}

template<typename A,typename B>
ostream& operator<<(ostream &out, const pnode<A,B> &item)
{
    out<<"("<<item.data<<", "<<item.priority<<") ";
    return out;
}

template<typename A,typename B>
istream& operator>>(istream &in, pnode<A,B> &item)
{
    A data;
    B priority;
    char junk;
    if(in == cin)
    {
        cout<<"Data: ";
        in>>data;
        cout<<"Priority: ";
        in>>priority;
    }
    else
        in>>junk>>data>>junk>>priority>>junk;
    item.theData() = data;
    item.thePriority() = priority;
    item.nextLink() = item.prevLink() = NULL;
    return in;
}

template<typename A,typename B>
bool higherPriority(pnode<A,B> &left, pnode<A,B> &right)
{
    if(&left == NULL || &right == NULL)
        return false;
    else
        return (right.thePriority() > left.thePriority());
}


#endif // PNODE_H
