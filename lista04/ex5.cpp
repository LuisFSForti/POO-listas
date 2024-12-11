//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <map>
#include <iostream>

typedef std::map<std::pair<int, int>, int> Matriz;

Matriz soma(const Matriz& A, const Matriz& B)
{
    Matriz C;

    for(const auto& [k, v] : A)
        C.insert({k, v});

    for(const auto& [k, v] : B)
    {
        C.find(k)->second += B.find(k)->second; //A soma só funciona se já havia um valor na posição
        C.insert({k, v}); //Insert só funciona se a posição estava vazia
    }

    return C;
}
