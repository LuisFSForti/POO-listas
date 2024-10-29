//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <iostream>

class C
{
protected:
    double _real, _imag;

public:
    C(double real = 0, double imag = 0)
    {
        _real = real;
        _imag = imag;
    }

    C& operator=(const C& b)
    {
        if(this == &b)
            return *this;

        this->_real = b._real;
        this->_imag = b._imag;

        return *this;
    }

    friend bool operator==(const C& a, const C& b)
    {
        if(&a == &b)
            return true;

        if(a._real != b._real)
            return false;

        if(a._imag != b._imag)
            return false;
    }

    C operator-() const
    {
        C ret;
        ret._real = -(*this)._real;
        ret._imag = -(*this)._imag;
        return ret;
    }

    friend C operator+(const C& a, const C& b)
    {
        C ret;

        ret._real = a._real + b._real;
        ret._imag = a._imag + b._imag;

        return ret;
    }

    friend C operator-(const C& a, const C& b)
    {
        return a + (-b);
    }

    friend C operator*(const C& a, const C& b)
    {
        C ret;

        ret._real = a._real * b._real - a._imag * b._imag;
        ret._imag = a._real * b._imag + a._imag * b._real;

        return ret;
    }

    friend C operator/(const C& a, const C& b)
    {
        C ret;

        ret._real = (a._real * b._real + a._imag * b._imag) / (b._real * b._real + b._imag * b._imag);
        ret._imag = (a._imag * b._real - a._real * b._imag) / (b._real * b._real + b._imag * b._imag);

        return ret;
    }

    friend std::ostream& operator<<(std::ostream &out, const C &a)
    {
        out << a.Print();
        return out;
    }

    virtual std::string Print() const
    {
        return std::to_string(this->_real) + " + " + std::to_string(this->_imag) + "i";
    }
};

class R : public C
{
public:
    R(double real = 0) : C(real, 0) {};

    virtual std::string Print() const
    {
        return std::to_string(this->_real);
    }
};

int main()
{
    C teste(-12.3, 15.3), teste2(-12.3, 15.3);
    R *teste3 = new R(-12.3), *teste4 = new R(-12.3);

    std::cout << teste * -teste2 << " " << (*teste3 * *teste4);
}
