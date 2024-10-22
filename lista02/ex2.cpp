#include <stdio.h>
#include <iostream>

static long long int mdc(long long int a, long long int b)
{
    //std::cout << a << " " << b << std::endl;

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

        //std::cout << valor << " " << this->_numerador << " " << this->_denominador << std::endl;
        double parteFracionada = valor - (long long int)(valor);

        long long int a;
        long long int b = this->_denominador;

        if(valor < 0)
            a = -parteFracionada * this->_denominador + 0.5;
        else
            a = parteFracionada * this->_denominador + 0.5;

        //std::cout << a << std::endl;

        long long int aux = mdc(a, this->_denominador);

        this->_denominador = this->_denominador / aux;
        this->_numerador = this->_numerador / aux;

        //std::cout << valor << " " << this->_numerador << " " << this->_denominador << " : " << aux << std::endl;
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
        this->_numerador = (long long int) (x / eps);
        this->_denominador = (long long int) (1/eps);

        this->reduz();
    }

    Fracao(double x)
    {
        *this = Fracao(x, 1e-10);
    }

    friend Fracao operator+(const Fracao& a, const Fracao& b)
    {
        //std::cout << a._numerador << " " << a._denominador << " - " << b._numerador << " " << b._denominador << std::endl;

        Fracao aux;
        aux._numerador = a._numerador * b._denominador + b._numerador * a._denominador;
        aux._denominador = a._denominador * b._denominador;

        aux.reduz();

        return aux;
    }

    friend Fracao operator-(const Fracao& a, const Fracao& b)
    {
        //std::cout << a._numerador << " " << a._denominador << " - " << b._numerador << " " << b._denominador << std::endl;

        Fracao aux;
        aux._numerador = a._numerador * b._denominador - b._numerador * a._denominador;
        aux._denominador = a._denominador * b._denominador;

        aux.reduz();

        return aux;
    }

    friend Fracao operator*(const Fracao& a, const Fracao& b)
    {
        //std::cout << a._numerador << " " << a._denominador << " - " << b._numerador << " " << b._denominador << std::endl;

        Fracao aux;

        aux._numerador = a._numerador * b._numerador;
        aux._denominador = a._denominador * b._denominador;

        aux.reduz();

        return aux;
    }

    friend Fracao operator/(const Fracao& a, const Fracao& b)
    {
        //std::cout << a._numerador << " " << a._denominador << " - " << b._numerador << " " << b._denominador << std::endl;

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
    Fracao f(-0.8214285714285714, 1e-10);
    std::cout << f << " " << double(f) << std::endl;
    f = f - Fracao(-30LL, 87LL);
    f = f / Fracao(-81LL, 62LL);
    f = f * Fracao(33LL, 63LL);
    f = f + Fracao(6LL, 78LL);
    f = f * Fracao(-9LL, 46LL);
    return 0;
}
