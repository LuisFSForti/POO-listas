//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <stack>

int elementok(std::stack<int>& pilha, int k)
{
    //Para contar quantos pares já foram
    int qtd = 0;

    //Para não alterar a pilha passada
    std::stack<int> atual = pilha;

    //Enquanto a pilha não acabou
    while(atual.size() > 0)
    {
        //Se atual for par
        if(atual.top() % 2 == 0)
            //Aumenta a contagem
            qtd++;

        //Se leu a quantidade de pares desejada
        if(qtd == k)
            //Retorna o valor atual
            return atual.top();

        //Se ainda não acabou a pesquisa, remove o valor de cima da pilha
        atual.pop();
    }

    //Se não achou retorna -1
    return -1;
}
