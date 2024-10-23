//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <iostream>
#include <math.h>

class Vetor
{
private:
    int _x, _y;

public:
    Vetor(int x, int y)
    {
        this->_x = x;
        this->_y = y;
    }

    Vetor()
    {
        *this = Vetor(0,0);
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
        out << "(" << a._x << ", " << a._y << ")" << std::endl;
        return out;
    }
};

int main() {
    Vetor v(-85, 51);
    std::cout << (v < Vetor(-41,4)) << std::endl;
    std::cout << v << std::endl;
    std::cout << (v * Vetor(90,62)) << std::endl;
    v = v - Vetor(88, -38);
    std::cout << v << std::endl;
    std::cout << (v * Vetor(-74,-84)) << std::endl;
    v = v - Vetor(53, -53);
    std::cout << (v < Vetor(52,-84)) << std::endl;
    v = v + Vetor(76, -26);
    std::cout << (v * Vetor(-23,40)) << std::endl;
    std::cout << v.abs() << std::endl;
    std::cout << v << std::endl;
    std::cout << (v * Vetor(39,-85)) << std::endl;
    std::cout << v.abs() << std::endl;
    v = v - Vetor(-9, -22);
    std::cout << v << std::endl;
    v = v + Vetor(12, 92);
    std::cout << v.abs() << std::endl;
    std::cout << (v ^ Vetor(75,-60)) << std::endl;
    v = v + Vetor(17, 61);
    std::cout << v << std::endl;
    std::cout << v.abs() << std::endl;
    std::cout << (v ^ Vetor(29,49)) << std::endl;
    std::cout << (v * Vetor(14,18)) << std::endl;
    v = v - Vetor(62, 31);
    std::cout << v << std::endl;
    v = v + Vetor(-68, -12);
    std::cout << (v ^ Vetor(-1,-30)) << std::endl;
    std::cout << (v * Vetor(-98,29)) << std::endl;
    std::cout << v << std::endl;
    std::cout << v.abs() << std::endl;
    v = v - Vetor(19, -11);
    v = v + Vetor(-96, -78);
    std::cout << v << std::endl;
    std::cout << (v ^ Vetor(0,75)) << std::endl;
    v = v - Vetor(63, -83);
    std::cout << (v < Vetor(11,-79)) << std::endl;
    std::cout << v.abs() << std::endl;
    v = v - Vetor(-64, -23);
    std::cout << v.abs() << std::endl;
    v = v - Vetor(-21, 82);
    v = v + Vetor(-93, 100);
    v = v - Vetor(-99, 91);
    std::cout << (v * Vetor(74,-83)) << std::endl;
    std::cout << (v < Vetor(32,85)) << std::endl;
    std::cout << v << std::endl;
    v = v - Vetor(-16, 32);
    std::cout << (v * Vetor(-2,74)) << std::endl;
    v = v + Vetor(-12, 47);
    std::cout << (v ^ Vetor(-90,38)) << std::endl;
    std::cout << (v * Vetor(40,-93)) << std::endl;
    std::cout << (v ^ Vetor(-27,-29)) << std::endl;
    std::cout << v << std::endl;
    return 0;
}
