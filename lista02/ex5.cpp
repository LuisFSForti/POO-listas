//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

class Arquivo
{
private:
    //Guarda o conteudo do arquivo
    std::fstream _conteudo;

public:
    //Abre o arquivo, salvando seu conteudo em _conteudo
    Arquivo(std::string arquivo)
    {
        this->_conteudo.open(arquivo, std::fstream::in);
    }

    //Para pegar a proxima linha
    std::string proxima_linha()
    {
        std::string aux;

        //Salva em aux a proxima linha em _conteudo
        std::getline(this->_conteudo, aux);
        return aux;
    }

    //Ao deletar a instancia
    ~Arquivo()
    {
        //Fecha o arquivo
        this->_conteudo.close();
    }
};
