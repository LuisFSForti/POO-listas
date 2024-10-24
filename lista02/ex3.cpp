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
        return Vetor(a._x + b._x, a._y + b._y);
    }

    friend Vetor operator-(const Vetor& a, const Vetor& b)
    {
        return Vetor(a._x - b._x, a._y - b._y);
    }

    friend int operator*(const Vetor& a, const Vetor& b)
    {
        return a._x * b._x + a._y * b._y;
    }

    friend int operator^(const Vetor& a, const Vetor& b)
    {
        //Dado z = 0
        //a ^ b = (i * ay *0 + j * 0 * bx + k * ax * by) - (i * 0 * by + j * ax * 0 + k * ay * bx)
        //a ^ b = k * ax * by - k * ay * bx
        return a._x * b._y - a._y * b._x;
    }

    friend double operator<(const Vetor& a, const Vetor& b)
    {
        return acos(a * b / (sqrt(a * a) * sqrt(b * b))) * 180/3.141592653;
    }

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
