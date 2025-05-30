    //Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <iostream>
#include <random>
#include <math.h>

class Trio
{
public:
    int a, b, c;

    Trio (int a = 1, int b = 1, int c = 1)
    {
        this->a = a;
        this->b = b;
        this->c = c;
    }
};


class Polinomio2
{
private:
    int _a, _b, _c;

public:
    Polinomio2(int a = 0, int b = 0, int c = 0)
    {
        //Se a == 0, entao b e c sao aleatorios
        if (a == 0)
        {
            this->_a = 1;
            this->_b = rand();
            this->_c = rand();
            return;
        }

        this->_a = a;
        this->_b = b;
        this->_c = c;
    }

    double *raizes() const
    {
        double* res = (double*)calloc(3, sizeof(double));

        //Calcula o delta do polinomio
        int delta = _b * _b - 4 * _a * _c;

        //Se for negativo
        if(delta < 0)
        {
            //Nao tem respostas
            res[0] = 0;
        }
        //Se for 0
        else if(delta == 0)
        {
            //Tem uma resposta
            res[0] = 1;
            res[1] = -_b / (2 * _a);
        }
        //Se for maior que 0
        else
        {
            //Tem duas respostas, uma para sqrt(delta) e uma para -sqrt(delta)
            res[0] = 2;
            res[1] = (-_b - sqrt(delta)) / (2 * _a);
            res[2] = (-_b + sqrt(delta)) / (2 * _a);
        }
        return res;
    }

    //Para calcular o valor do polinomio para um x
    double operator()(double x) const
    {
        return _a * x * x + _b * x + _c;
    }
};

Trio coeficientes(const Polinomio2& p)
{
    //Variáveis auxiliares
    int a, b, c;

    //ax^2 + bx + c -> x = 0 -> a*0 + b*0 + c = c
    c = (int)p(0);

    //x = 1
    //a*1^2 + b*1 + c = d
    //b = d - c - a

    //x = 2
    //a*2^2 + b*2 + c = D
    //4*a + 2*(d - c - a) + c = D
    //2*a + 2*d - c = D
    //a = (D + c)/2 - d
    a = (p(2) + c)/2 - p(1);
    b = p(1) - c - a;

    return Trio(a, b, c);
}
