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

    //Construtor de copia para o for
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

    //Quando comecar o loop, essa funcao � chamada
    //Deve retornar a instancia "inicial"
    auto begin() {
        //Retorna a instancia atual
        return *this;
    }

    //Quando comecar o loop, essa funcao � chamada
    //Deve retornar a instancia "final"
    //Como o loop nao pode ser definido por um objeto final, esta funcao eh irrelevante
    auto end() {
        return Arquivo("");
    }

    //Para pegar o valor de cada iteracao do loop, essa funcao eh chamada
    const std::string& operator*() const {
        return this->_linha;
    }

    //Para o loop, isto representa ++i
    Arquivo& operator++() {
        //Avan�a pra proxima linha
        proxima_linha();
        //Retorna a instancia atual, a qual possui a nova linha
        return *this;
    }

    /*//Para o loop, isto repr
    Arquivo& operator++(int) {
        proxima_linha();
        return *this;
    }

    bool operator==(Arquivo) const {
        return !!this->_conteudo;
    }*/

    //Para terminar o loop, o for verifica se instancia atual != instancia retornada na funcao end()
    //Como nao tem uma instancia final, ela eh desconsiderada
    bool operator!=(Arquivo) const {
        //Retorna se foi tentada ler uma linha apos o fim do arquivo
        //Se usasse o EOF, nao imprimiria a ultima linha
        return !!this->_conteudo;
    }
};
