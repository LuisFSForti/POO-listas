//Luis Filipe Silva Forti - 14592348

#include <iostream>
#include <fstream>

std::string conteudo(std::string nome)
{
    std::ifstream arquivo(nome);

    std::string cont, aux;

    while (getline (arquivo, aux))
    {
        cont += aux + '\n';
    }

    arquivo.close();
    return cont;
}

int main() {
    std::string nome;

    std::cin >> nome;

    std::cout << conteudo(nome) << std::endl;
    return 0;
}
