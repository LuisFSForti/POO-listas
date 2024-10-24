//Luis Filipe Silva Forti - 14592348

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
        if(this->_numerador == 0)
        {
            this->_numerador = 0;
            this->_denominador = 1;
            return;
        }

        if(this->_denominador < 0)
        {
            this->_denominador *= -1;
            this->_numerador *= -1;
        }

        double valor = double(*this);

        double parteFracionada = valor - (long long int)(valor);

        long long int a;
        long long int b = this->_denominador;

        if(valor < 0)
            a = -parteFracionada * this->_denominador + 0.5;
        else
            a = parteFracionada * this->_denominador + 0.5;

        long long int aux = mdc(a, this->_denominador);

        this->_denominador = this->_denominador / aux;
        this->_numerador = this->_numerador / aux;
    }

public:
    Fracao(long long int numerador = 0, long long int denominador = 1)
    {
        this->_numerador = numerador;
        this->_denominador = denominador;

        this->reduz();
    }

    Fracao(double x, double eps = 1e-10)
    {
        this->_numerador = (long long int) (x / eps);
        this->_denominador = (long long int) (1/eps);

        this->reduz();
    }

    friend Fracao operator+(const Fracao& a, const Fracao& b)
    {
        long long int numerador, denominador;
        numerador = a._numerador * b._denominador + b._numerador * a._denominador;
        denominador = a._denominador * b._denominador;

        return Fracao(numerador, denominador);
    }

    friend Fracao operator-(const Fracao& a, const Fracao& b)
    {
        long long int numerador, denominador;
        numerador = a._numerador * b._denominador - b._numerador * a._denominador;
        denominador = a._denominador * b._denominador;

        return Fracao(numerador, denominador);
    }

    friend Fracao operator*(const Fracao& a, const Fracao& b)
    {
        long long int numerador, denominador;
        numerador = a._numerador * b._numerador;
        denominador = a._denominador * b._denominador;

        return Fracao(numerador, denominador);
    }

    friend Fracao operator/(const Fracao& a, const Fracao& b)
    {
        long long int numerador, denominador;
        numerador = a._numerador * b._denominador;
        denominador = a._denominador * b._numerador;

        return Fracao(numerador, denominador);
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

        return out;
    }
};
