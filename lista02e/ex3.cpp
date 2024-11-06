//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

//https://stackoverflow.com/questions/62716242/implement-iterator-over-file

class Arquivo
{
private:
    //Guarda o conteudo do arquivo
    std::ifstream _conteudo;
    std::string _linha, _endereco;

public:
    //Abre o arquivo, salvando seu conteudo em _conteudo
    Arquivo(std::string arquivo)
    {
        this->_endereco = arquivo;
        this->_conteudo.open(arquivo, std::ifstream::in);
    }

    Arquivo(const Arquivo& b)
    {
        this->_endereco = b._endereco;
        this->_linha = b._linha;
        this->_conteudo.open(this->_endereco, std::ifstream::in);
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
        return *this;
    }

    auto end() {
        return Arquivo("");
    }

    const std::string& operator*() const {
        return this->_linha;
    }

    Arquivo& operator++() {
        proxima_linha();
        return *this;
    }

    Arquivo& operator++(int) {
        proxima_linha();
        return *this;
    }

    bool operator==(Arquivo) const {
        return !!this->_conteudo;
    }

    bool operator!=(Arquivo) const {
        return !!this->_conteudo;
    }

    friend std::ostream& operator<<(std::ostream &out, const Arquivo &a)
    {
        out << a._linha;

        return out;
    }
};
