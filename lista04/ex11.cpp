//Luis Filipe Silva Forti - 14592348

#include <iostream>

class Pessoa
{
private:
    //Dados da pessoa
    std::string _nome, _cidade, _UF, _pais;
    int _idade;

public:
    //Construtor com string com todos os dados
    Pessoa(std::string dados)
    {
        //Copia os dados para não alterar a string passada
        std::string aux = dados;

        //Pega o texto antes de " tem", que é o nome da pessoa
        this->_nome = aux.substr(0, aux.find(" tem"));
        aux = aux.substr(aux.find("tem ") + 4); //Remove tudo antes da idade

        //Pega o texto antes do primeiro espaço e converte para inteiro
        this->_idade = stoi(aux.substr(0, aux.find(" ")));
        aux = aux.substr(aux.find("em ") + 3); //Remove tudo antes da cidade

        //Pega tudo antes do "-", que é o nome da cidade
        this->_cidade = aux.substr(0, aux.find("-"));
        aux = aux.substr(aux.find("-") + 1); //Remove tudo antes da UF

        //Pega a UF, que é de 2 letras
        this->_UF = aux.substr(0, 2);
        aux = aux.substr(4); //Remove tudo antes do país

        //O restante da string é o nome do país
        this->_pais = aux;
    }

    //Para imprimir os dados
    friend std::ostream& operator<<(std::ostream& out, const Pessoa& pessoa)
    {
        //Adiciona a informação atual, dando um enter para cada
        out << pessoa._nome << std::endl;
        out << pessoa._idade << std::endl;
        out << pessoa._cidade << std::endl;
        out << pessoa._UF << std::endl;
        out << pessoa._pais << std::endl;

        //Retorna as informações
        return out;
    }
};
