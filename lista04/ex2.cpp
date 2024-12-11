//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <stack>
#include <queue>
#include <iostream>

std::string jogo(std::stack<int>& cartas, std::queue<std::string> jogadores)
{
    int* somas = (int*)calloc(jogadores.size(), sizeof(int));

    std::stack<int> atual = cartas;

    while(atual.size() > 0)
    {
        for(int i = 0; i < jogadores.size() && atual.size() > 0; i++)
        {
            somas[i] += atual.top();
            atual.pop();
        }
    }

    int menor = somas[0];
    std::string menorS = jogadores.front();
    std::queue<std::string> atualJ = jogadores;
    atualJ.pop();

    for(int i = 1; atualJ.size() > 0; i++, atualJ.pop())
    {
        if(somas[i] <= menor)
        {
            menor = somas[i];
            if(menorS.compare(atualJ.front()) < 0)
            {
                menorS = atualJ.front();
            }
        }
    }

    return menorS;
}
