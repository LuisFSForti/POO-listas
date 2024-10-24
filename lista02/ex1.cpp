//Luis Filipe Silva Forti - 14592348

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

    Televisao(bool ligada) : Televisao(ligada, 1) {};

    Televisao(int canal) : Televisao(false, canal) {};

    Televisao() : Televisao(false, 1) {};

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
        if(this->_ligada)
            this->_canal++;
    }

    void canal_baixo()
    {
        if(this->_ligada)
            this->_canal--;
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
