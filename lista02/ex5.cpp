//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

class Arquivo
{
private:
    std::fstream _conteudo;

public:
    Arquivo(std::string arquivo)
    {
        this->_conteudo.open(arquivo, std::fstream::in);
    }

    std::string proxima_linha()
    {
        std::string aux;
        std::getline(this->_conteudo, aux);
        return aux;
    }

    ~Arquivo()
    {
        this->_conteudo.close();
    }
};
