//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <map>
#include <iostream>

typedef std::map<std::pair<int, int>, int> Matriz;

Matriz soma(const Matriz& A, const Matriz& B)
{
    //Matriz que vai retornar
    Matriz C;

    //Para cada valor de A
    for(const auto& [k, v] : A)
        //Insere ele em C
        C.insert({k, v});

    //Para cada valor de B
    for(const auto& [k, v] : B)
    {
        //Para pular a posição [-1, -1]
        if(k.first == -1)
            continue;

        //A soma só funciona se já havia um valor na posição
        C.find(k)->second += B.find(k)->second;

        //Insert só funciona se a posição estava vazia
        C.insert({k, v});

        //Desta forma ele adiciona onde já haviam valores de A, ou insere o valor de B no caso contrário
    }

    return C;
}
