//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <iostream>

class C
{
private:
    double _real, _imag;

public:
    C(double real = 0, double imag = 0)
    {
        this->_real = real;
        this->_imag = imag;
    }

    C& operator=(const C& b)
    {
        if(this == &b)
            return *this;

        this->_real = b._real;
        this->_imag = b._imag;

        return *this;
    }

    double real() const
    {
        return this->_real;
    }

    double iamg() const
    {
        return this->_imag;
    }

    friend bool operator==(const C& a, const C& b)
    {
        if(&a == &b)
            return true;

        if(a._real != b._real)
            return false;

        if(a._imag != b._imag)
            return false;

        return true;
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

    R(const C& val) : C(val.real(), 0) {};

    virtual std::string Print() const
    {
        return std::to_string(this->real());
    }
};

class Q : public R
{
private:
    static long long int mdc(long long int a, long long int b)
    {
        if (a == 0)
            return b;
        if (b == 0)
            return a;

        if (a < b)
            return mdc(a, b % a);
        else
            return mdc(b, a % b);
    }

public:
    Q(int numerador = 0, int denominador = 1) : R((double)(numerador) / (double)(denominador)) {};

    Q(const R& val) : R(val.real()) {};

    virtual std::string Print() const
    {
        if(this->real() == 0)
        {
            return "0/1";
        }

        double parteFracionada = this->real() - (long long int)(this->real());

        long long int a, b;

        if(this->real() < 0)
            a = -parteFracionada * 1e10 + 0.5;
        else
            a = parteFracionada * 1e10 + 0.5;

        long long int aux = mdc(a, 1e10);

        b = 1e10 / aux;
        a = this->real() * 1e10 / aux;

        return std::to_string(a) + "/" + std::to_string(b);
    }
};

class Z : public Q
{
public:
    Z(int real = 0) : Q(real, 1) {};

    Z(const C& val) : Q((int)val.real(), 1) {};

    virtual std::string Print() const
    {
        if(this->real() < 0)
            return std::to_string((int)this->real());
        else
            return "+" + std::to_string((int)this->real());
    }
};

class N : public Z
{
public:
    N(int real = 0) : Z(real)
    {
        if(this->real() < 0)
            new (this) N(0);
    }

    N(const C& val) : Z((int)val.real())
    {
        if(this->real() < 0)
            new (this) N(0);
    }

    std::string Print() const
    {
        return std::to_string((int)this->real());
    }
};
