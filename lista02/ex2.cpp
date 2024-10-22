#include <stdio.h>
#include <iostream>

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


class Fracao
{
private:
    long long int _numerador, _denominador;

    void reduz()
    {
        double f = double(*this);
        if(this->_denominador < 0)
        {
            this->_denominador *= -1;
            this->_numerador *= -1;
        }

        *this = Fracao(f);
    }

public:
    Fracao(long long int numerador, long long int denominador)
    {
        this->_numerador = numerador;
        this->_denominador = denominador;

        this->reduz();
    }

    Fracao()
    {
        this->_numerador = 0;
        this->_denominador = 1;
    }

    Fracao(double x, double eps)
    {
        double parteFracionada = x - int(x);

        int EhNegativo = 1;

        if(x < 0)
            EhNegativo *= -1;

        long long int a = EhNegativo * parteFracionada / eps + 0.5;
        long long int b = 1/eps;
        long long int aux = mdc(a, b);

        this->_denominador = EhNegativo / (eps * aux);
        this->_numerador = x * this->_denominador;
    }

    Fracao(double x)
    {
        *this = Fracao(x, 1e-10);
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
