//Luis Filipe Silva Forti - 14592348

#include <iostream>

class Pessoa
{
private:
    std::string _nome, _cidade, _UF, _pais;
    int _idade;

public:
    Pessoa(std::string dados)
    {
        std::string aux = dados;
        this->_nome = aux.substr(0, aux.find(" tem"));
        aux = aux.substr(aux.find("tem") + 4); //Remove tudo antes da idade

        this->_idade = stoi(aux.substr(0, aux.find(" ")));
        aux = aux.substr(aux.find("em ") + 3); //Remove tudo antes da cidade

        this->_cidade = aux.substr(0, aux.find("-"));
        aux = aux.substr(aux.find("-") + 1); //Remove tudo antes da UF

        this->_UF = aux.substr(0, 2);
        aux = aux.substr(4); //Remove tudo antes do país

        this->_pais = aux;
    }

    friend std::ostream& operator<<(std::ostream& out, const Pessoa& pessoa)
    {
        out << pessoa._nome << std::endl;
        out << pessoa._idade << std::endl;
        out << pessoa._cidade << std::endl;
        out << pessoa._UF << std::endl;
        out << pessoa._pais << std::endl;

        return out;
    }
};
