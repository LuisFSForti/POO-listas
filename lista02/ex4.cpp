//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <iostream>
#include <random>
#include <math.h>

class Polinomio2
{
private:
    int _a, _b, _c;

public:
    Polinomio2(int a, int b, int c)
    {
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

    Polinomio2(int a, int b) : Polinomio2(a, b, 9) {};

    Polinomio2(int a) : Polinomio2(a, 0, 0) {};

    Polinomio2() : Polinomio2(0, 0, 0) {};

    double *raizes()
    {
        double* res = (double*)calloc(3, sizeof(double));

        int delta = _b * _b - 4 * _a * _c;

        if(delta < 0)
        {
            res[0] = 0;
        }
        else if(delta == 0)
        {
            res[0] = 1;
            res[1] = -_b / (2 * _a);
        }
        else
        {
            res[0] = 2;
            res[1] = (-_b - sqrt(delta)) / (2 * _a);
            res[2] = (-_b + sqrt(delta)) / (2 * _a);
        }
        return res;
    }

    double operator()(double x)
    {
        return _a * x * x + _b * x + _c;
    }
};
