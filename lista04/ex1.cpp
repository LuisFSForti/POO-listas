//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <stack>

int elementok(std::stack<int>& pilha, int k)
{
    int qtd = 0;

    std::stack<int> atual = pilha;

    while(atual.size() > 0)
    {
        if(atual.top() % 2 == 0)
            qtd++;

        if(qtd == k)
            return atual.top();

        atual.pop();
    }

    return -1;
}
