//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

//https://stackoverflow.com/questions/62716242/implement-iterator-over-file
class End_iterator {};

class Iterator {
private:
    void proximaLinha() {
        std::getline(_arquivo, _linha);
    }

    std::fstream& _arquivo;
    std::string _linha;

public:
    Iterator(std::fstream& arquivo) : _arquivo{arquivo} {
        proximaLinha();
    }

    const std::string& operator*() const {
        return _linha;
    }

    Iterator& operator++() {
        proximaLinha();
        return *this;
    }

    bool operator!=(End_iterator) const {
        return !!_arquivo;
    }
};

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

    auto begin() {
        return Iterator(_conteudo);
    }

    auto end() {
        return End_iterator();
    }
};
