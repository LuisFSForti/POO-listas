//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

//https://stackoverflow.com/questions/62716242/implement-iterator-over-file

class Arquivo
{
private:
    struct FimIterador {};

    //Guarda o conteudo do arquivo
    std::fstream _conteudo;
    std::string _linha;

public:
    //Abre o arquivo, salvando seu conteudo em _conteudo
    Arquivo(std::string arquivo)
    {
        this->_conteudo.open(arquivo, std::fstream::in);
    }

    //Para pegar a proxima linha
    std::string proxima_linha()
    {
        std::getline(this->_conteudo, this->_linha);
        return this->_linha;
    }

    //Ao deletar a instancia
    ~Arquivo()
    {
        //Fecha o arquivo
        this->_conteudo.close();
    }

    auto begin() {
        return ;
    }

    auto end() {
        return FimIterador();
    }

    const std::string& operator*() const {
        return this->_linha;
    }

    Arquivo& operator++() {
        proxima_linha();
        return *this;
    }

    bool operator!=(FimIterador) const {
        return !!_conteudo;
    }
};
