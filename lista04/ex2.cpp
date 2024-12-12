//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <stack>
#include <queue>
#include <iostream>

std::string jogo(std::stack<int>& cartas, std::queue<std::string> jogadores)
{
    //Para guardar a soma de cada jogador
    int* somas = (int*)calloc(jogadores.size(), sizeof(int));

    //Para n�o alterar a pilha passada
    std::stack<int> atual = cartas;

    //Enquanto a pilha n�o acabou
    while(atual.size() > 0)
    {
        //Para cada jogador
        for(int i = 0; i < jogadores.size() && atual.size() > 0; i++)
        {
            //Aumenta a soma do jogador atual
            somas[i] += atual.top();
            //Remove a carta do topo
            atual.pop();
        }
    }

    //Para n�o alterar a fila passada
    std::queue<std::string> atualJ = jogadores;

    //Para inicializar, define que a menor soma � do primeiro jogador
    int menor = somas[0];
    std::string menorS = atualJ.front();

    //Remove o primeiro jogador
    atualJ.pop();

    //Para cada jogador
    for(int i = 1; atualJ.size() > 0; i++, atualJ.pop())
    {
        //Se a soma dele for a menor at� o momento
        if(somas[i] < menor)
        {
            //Atualiza qual � o valor menor e de quem �
            menor = somas[i];
            menorS = atualJ.front();
        }

        //Se a soma for igual a menor
        if(somas[i] == menor)
        {
            //Se o jogador atual tiver prioridade alfab�tica ao menor atual
            if(menorS.compare(atualJ.front()) > 0)
            {
                //Atualiza quem � o jogador com menor soma
                menorS = atualJ.front();
            }
        }
    }

    //Retorna qual jogador teve a menor soma
    return menorS;
}
