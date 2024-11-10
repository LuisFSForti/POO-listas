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
        //Se estava no canal 100 antes de somar, ele diminui em 100, caindo para 1
        this->_canal -= (this->_canal == 101) * 100;
    }

    void canal_baixo()
    {
        this->_canal -= this->_ligada;
        //Se estava no canal 1 antes de somar, ele aumenta em 100, subindo para 100
        this->_canal += (this->_canal == 0) * 100;
    }

    friend std::ostream& operator<<(std::ostream& out, const Televisao& tv)
    {
        out << "(";

        //Para selecionar a saída baseada no tv._ligada, pois false == 0 e true == 1
        std::string res[] = {"desligada", "ligada"};

        out << res[tv._ligada] << ", " << tv._canal << ")\r";
        return out;
    }
};
