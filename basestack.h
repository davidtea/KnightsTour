#ifndef BASESTACK_H
#define BASESTACK_H

#include <cstdlib>

using namespace std;

class baseStack
{
    public:
        baseStack();
        ~baseStack();

        bool empty();
        bool full();
        void clear();
        virtual void resize(int x) = 0;
        int size() const;
        int capacity() const;

    protected:
        void **stack;
        int total;

        virtual void nukem() = 0;
        virtual void newStack(int s) = 0;

        void increment();
        void decrement();
        int topOfStack();
        virtual void makeStack(int s) = 0;
        virtual void deleteStack() = 0;

    private:
        int tos;
};

#endif // BASESTACK_H
