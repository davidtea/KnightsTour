#ifndef COORD_H
#define COORD_H

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
        x = other.x;
        y = other.y;
    }

    friend
    coord operator +(const coord &left, const coord &right)
    {
        coord temp(left.x+right.x, left.y+right.y);
        return temp;
    }

    int x;
    int y;
};

#endif // COORD_H
