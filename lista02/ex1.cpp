#include <stdio.h>
#include <iostream>

class Televisao
{
private:
    int _ligada = false;
    int _canal;

public:
    Televisao(bool ligada, int canal)
    {
        this->_canal = canal;
        this->_ligada = ligada;
    }

    Televisao(int canal)
    {
        this->_canal = canal;
        this->_ligada = false;
    }

    Televisao()
    {
        this->_canal = 1;
        this->_ligada = false;
    }

    void liga()
    {
        this->_ligada = true;
    }

    void desliga()
    {
        this->_ligada = false;
    }

    void canal_cima()
    {
        this->_canal++;
    }

    void canal_baixo()
    {
        this->_canal--;
    }

    friend std::ostream& operator<<(std::ostream& out, const Televisao& tv)
    {
        out << "(";

        if(tv._ligada)
            out << "ligada";
        else
            out << "desligada";

        out << ", " << tv._canal << ")" << std::endl;
        return out;
    }
};
