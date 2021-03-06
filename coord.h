#ifndef COORD_H
#define COORD_H

#include <iostream>

using namespace std;

class coord
{
public:
    coord ()
    {
        x = 0;
        y = 0;
    }

    coord (int X, int Y)
    {
        x = X;
        y = Y;
    }

    coord(const coord &other)
    {
        copy(other);
    }

    coord& operator=(const coord &other)
    {
        if(this!=&other)
        {
            copy(other);
        }
        return *this;
    }

    int getX() const
    {
        return x;
    }

    int getY() const
    {
        return y;
    }

    friend
    bool operator==(const coord &left, const coord &right)
    {
        return (left.x == right.x && left.y == right.y);
    }

    friend
    bool operator!=(const coord &left, const coord &right)
    {
        return (left.x != right.x || left.y != right.y);
    }

    friend
    coord operator+(const coord &left, const coord &right)
    {
        coord temp(left.x+right.x, left.y+right.y);
        return temp;
    }

    friend
    ostream& operator <<(ostream &out, const coord &c)
    {
        out << "(" << c.x << "," << c.y << ")";
        return out;
    }

    friend
    istream& operator >>(istream &in, coord &c)
    {
        cout << "X: ";
        in >> c.x;
        cout << "Y: ";
        in >> c.y;
        return in;
    }

private:
    int x;
    int y;
    void copy(const coord &other)
    {
        x = other.x;
        y = other.y;
    }
};



#endif // COORD_H
