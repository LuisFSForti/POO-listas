//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

//https://stackoverflow.com/questions/62716242/implement-iterator-over-file

class Arquivo
{
private:
    //Para marcar o fim da iteracao
    struct End_iterator {};

    //Guarda o conteudo do arquivo
    std::ifstream _conteudo;
    std::string linha;

public:
    //Abre o arquivo, salvando seu conteudo em _conteudo
    Arquivo(std::string arquivo)
    {
        this->_conteudo.open(arquivo, std::ifstream::in);
    }

    //Para pegar a proxima linha
    std::string proxima_linha()
    {
        std::getline(this->_conteudo, this->linha);
        return this->linha;
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
        return End_iterator();
    }

    const std::string& operator*() const {
        return this->linha;
    }

    Arquivo& operator++() {
        proxima_linha();
        return *this;
    }

    bool operator!=(End_iterator) const {
        return !!this->_conteudo;
    }
};
