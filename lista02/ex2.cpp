#include <stdio.h>
#include <iostream>

static long long int mdc(int a, int b)
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


class Fracao
{
private:
    long long int _numerador, _denominador;

    void reduz()
    {
        double f = double(*this);
        if(this->_denominador < 0)
            this->_denominador *= -1;

        *this = Fracao(f);
    }

public:
    Fracao(long long int numerador, long long int denominador)
    {
        this->_numerador = numerador;
        this->_denominador = denominador;
    }

    Fracao()
    {
        this->_numerador = 0;
        this->_denominador = 1;
    }

    Fracao(double x, double eps)
    {
        double parteFracionada = x - int(x);
        long long int aux = mdc(int(parteFracionada / eps + 0.5), 1/eps);

        this->_denominador = 1 / (eps * aux);
        this->_numerador = x * this->_denominador;
    }

    Fracao(double x)
    {
        double eps= 0.00000001;

        double parteFracionada = x - int(x);
        long long int aux = mdc(int(parteFracionada / eps + 0.5), 1/eps);

        this->_denominador = 1 / (eps * aux);
        this->_numerador = x * this->_denominador;
    }

    friend Fracao operator+(const Fracao& a, const Fracao& b)
    {
        Fracao aux;
        aux._numerador = a._numerador * b._denominador + b._numerador * a._denominador;
        aux._denominador = a._denominador * b._denominador;

        aux.reduz();

        return aux;
    }

    friend Fracao operator-(const Fracao& a, const Fracao& b)
    {
        Fracao aux;
        aux._numerador = a._numerador * b._denominador - b._numerador * a._denominador;
        aux._denominador = a._denominador * b._denominador;

        aux.reduz();

        return aux;
    }

    friend Fracao operator*(const Fracao& a, const Fracao& b)
    {
        Fracao aux;
        aux._numerador = a._numerador * b._numerador;
        aux._denominador = a._denominador * b._denominador;

        aux.reduz();

        return aux;
    }

    friend Fracao operator/(const Fracao& a, const Fracao& b)
    {
        Fracao aux;
        aux._numerador = a._numerador * b._denominador;
        aux._denominador = a._denominador * b._numerador;

        aux.reduz();

        return aux;
    }

    operator double()
    {
        return double(this->_numerador) / double(this->_denominador);
    }

    friend std::ostream& operator<<(std::ostream &out, const Fracao &a)
    {
        if(a._numerador % a._denominador == 0)
            out << a._numerador / a._denominador;
        else
            out << a._numerador << "/" << a._denominador;

        out << " " << double(a._numerador) / double(a._denominador);

        return out;
    }
};
