//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <iostream>
#include <math.h>

class Vetor
{
private:
    int _x, _y;

public:
    Vetor(int x = 0, int y = 0)
    {
        this->_x = x;
        this->_y = y;
    }

    friend Vetor operator+(const Vetor& a, const Vetor& b)
    {
        //v1 = (a,b)
        //v2 = (c,d)
        //v1 + v2 = (a + c, b + d)
        return Vetor(a._x + b._x, a._y + b._y);
    }

    friend Vetor operator-(const Vetor& a, const Vetor& b)
    {
        //v1 = (a,b)
        //v2 = (c,d)
        //v1 - v2 = (a - c, b - d)
        return Vetor(a._x - b._x, a._y - b._y);
    }

    //v1 = (a,b)
    //v2 = (c,d)
    //v1 * v2 = a * c + b * d
    friend int operator*(const Vetor& a, const Vetor& b)
    {
        return a._x * b._x + a._y * b._y;
    }

    //v1 = (a,b,0)
    //v2 = (c,d,0)
    //a ^ b = (i * b *0 + j * 0 * c + k * a * d) - (i * 0 * d + j * a * 0 + k * b * c)
    //a ^ b = k * a * d - k * b * c = (a * d - b * c) * k
    friend int operator^(const Vetor& a, const Vetor& b)
    {
        return a._x * b._y - a._y * b._x;
    }

    //v1 = (a,b)
    //v2 = (c,d)
    //v1 * v2 = |v1||v2|*cos(t)
    //t = arcos(v1 * v2 / (|v1|v2))
    friend double operator<(const Vetor& a, const Vetor& b)
    {
        return acos(a * b / (sqrt(a * a) * sqrt(b * b))) * 180/3.141592653;
    }

    //v1 = (a,b)
    //|v1| = sqrt(a^2 + b^2) = sqrt((a,b) * (a,b))
    //|v1| = sqrt(v1 * v1)
    double abs()
    {
        return sqrt((*this) * (*this));
    }

    friend std::ostream& operator<<(std::ostream &out, const Vetor &a)
    {
        out << "(" << a._x << "," << a._y << ")";
        return out;
    }
};
