//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <iostream>

class Televisao
{
private:
    int _ligada = false;
    int _canal;

public:
    Televisao(bool ligada = false, int canal = true)
    {
        this->_canal = canal;
        this->_ligada = ligada;
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
        this->_canal -= (this->_canal == 99) * 99 * this->_ligada;
        this->_canal += this->_ligada;
    }

    void canal_baixo()
    {
        this->_canal += (this->_canal == 1) * 99 * this->_ligada;
        this->_canal -= this->_ligada;
    }

    friend std::ostream& operator<<(std::ostream& out, const Televisao& tv)
    {
        out << "(";

        if(tv._ligada)
            out << "ligada";
        else
            out << "desligada";

        out << ", " << tv._canal << ")\r";
        return out;
    }
};
