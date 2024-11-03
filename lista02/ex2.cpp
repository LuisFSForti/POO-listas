//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <iostream>

static long long int mdc(long long int a, long long int b)
{
    //https://www.geeksforgeeks.org/gcd-in-cpp/

    //Se a = 0, então o maior divisor comum é o valor de b
    if (a == 0)
        return b;
    //Se b = 0, então o maior divisor comum é o valor de a
    if (b == 0)
        return a;

    //Se a é menor do que b
    if (a < b)
        //Calcula novamente utilizando o valor de a e o resto de b/a
        return mdc(a, b % a);
    //Se b é menor do que a
    else
        //Calcula novamente utilizando o valor de b e o resto de a/b
        return mdc(b, a % b);
}


class Fracao
{
private:
    long long int _numerador, _denominador;

    void reduz()
    {
        //Se o numerador é 0, o denominador deve ser 1
        if(this->_numerador == 0)
        {
            this->_numerador = 0;
            this->_denominador = 1;
            return;
        }

        //Se o denominador estiver negtaivo
        if(this->_denominador < 0)
        {
            //Multiplica em cima e em baixo por -1
            this->_denominador *= -1;
            this->_numerador *= -1;
        }

        /*//Pega o resultado da fração em forma de double
        double valor = double(*this);

        double parteFracionada = valor - (long long int)(valor);

        long long int a;

        if(valor < 0)
            a = -parteFracionada * this->_denominador + 0.5;
        else
            a = parteFracionada * this->_denominador + 0.5;

        long long int aux = mdc(a, this->_denominador);

        this->_denominador = this->_denominador / aux;
        this->_numerador = this->_numerador / aux;*/

        long long int aux;
        if(this->_numerador < 0)
            aux = mdc(-this->_numerador, this->_denominador);
        else
            aux = mdc(this->_numerador, this->_denominador);

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
