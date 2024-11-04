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
        this->_canal += this->_ligada;
        this->_canal -= (this->_canal == 101) * 100;
    }

    void canal_baixo()
    {
        this->_canal -= this->_ligada;
        this->_canal += (this->_canal == 0) * 100;
    }

    friend std::ostream& operator<<(std::ostream& out, const Televisao& tv)
    {
        out << "(";

        std::string res[] = {"desligada", "ligada"};

        out << res[tv._ligada] << ", " << tv._canal << ")\r";
        return out;
    }
};
