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
    Fracao(long long int numerador, long long int denominador)
    {
        this->_numerador = numerador;
        this->_denominador = denominador;

        this->reduz();
    }

    Fracao() : _numerador(0), _denominador(1) {};

    Fracao(double x, double eps)
    {
        this->_numerador = (long long int) (x / eps);
        this->_denominador = (long long int) (1/eps);

        this->reduz();
    }

    Fracao(double x) : Fracao(x, 1e-10) {};

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

        return out;
    }
};

int main() {
    Fracao f(96LL, 100LL);
    f = f + Fracao(80LL, 30LL);
    f = f / Fracao(4LL, 9LL);
    f = f + Fracao(-62LL, 20LL);
    std::cout << f << " " << double(f) << std::endl;
    f = f + Fracao(-34LL, 47LL);
    std::cout << f << " " << double(f) << std::endl;
    f = f / Fracao(-23LL, 75LL);
    f = f * Fracao(93LL, 61LL);
    f = f + Fracao(47LL, 3LL);
    f = f - Fracao(-74LL, 76LL);
    f = f / Fracao(-31LL, 44LL);
    f = f + Fracao(-8LL, 66LL);
    f = f - Fracao(51LL, 85LL);
    std::cout << f << " " << double(f) << std::endl;
    f = f * Fracao(-64LL, 5LL);
    std::cout << f << " " << double(f) << std::endl;
    f = f / Fracao(86LL, 26LL);
    f = f + Fracao(23LL, 53LL);
    f = f - Fracao(-72LL, 95LL);
    f = f + Fracao(60LL, 86LL);
    std::cout << f << " " << double(f) << std::endl;
    f = f - Fracao(94LL, 7LL);
    f = f / Fracao(-18LL, 56LL);
    f = f * Fracao(-10LL, 67LL);
    std::cout << f << " " << double(f) << std::endl;
    f = f / Fracao(-50LL, 74LL);
    return 0;
}
