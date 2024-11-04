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

    Trio& operator=(const Trio& t)
    {
        this->a = t.a;
        this->b = t.b;
        this->c = t.c;

        return *this;
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
    int a = 0, b = 0, c = 0;
    double *raizes = p.raizes();

    c = p(0);
    if(raizes[0] == 2)
    {
        a = c/(raizes[1] * raizes[2]);
        b = -(raizes[1] + raizes[2]) * a;
    }


    return Trio(a, b, c);
}

int main()
{
    Polinomio2 p1(1, 1, 1);
    Trio t = coeficientes(p1);
    std::cout << t.a << " " << t.b << " " << t.c << '\n' ;
    Polinomio2 p2(1, 2, 1);
    t = coeficientes(p2);
    std::cout << t.a << " " << t.b << " " << t.c << '\n' ;
    Polinomio2 p3(1, -3, 2);
    t = coeficientes(p3);
    std::cout << t.a << " " << t.b << " " << t.c << '\n' ;

    return 0;
}
