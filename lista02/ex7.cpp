//Luis Filipe Silva Forti - 14592348

#include "ex6.cpp"

class Fracao
{
private:
    BigInt _numerador, _denominador;

public:
    Fracao(BigInt numerador = BigInt("0"), BigInt denominador = BigInt("1"))
    {
        _numerador = numerador;
        _denominador = denominador;
    }

    friend Fracao operator+(const Fracao&a, const Fracao& b)
    {
        return Fracao(a._numerador * b._denominador + b._numerador * a._denominador, a._denominador * b._denominador);
    }

    friend Fracao operator-(const Fracao&a, const Fracao& b)
    {
        return Fracao(a._numerador * b._denominador - b._numerador * a._denominador, a._denominador * b._denominador);
    }

    friend Fracao operator*(const Fracao&a, const Fracao& b)
    {
        return Fracao(a._numerador * b._numerador, a._denominador * b._denominador);
    }

    friend Fracao operator/(const Fracao&a, const Fracao& b)
    {
        return Fracao(a._numerador * b._denominador, a._denominador * b._numerador);
    }

    friend std::ostream& operator<<(std::ostream &out, const Fracao &a)
    {
        out << a._numerador << "/" << a._denominador;

        return out;
    }
};
