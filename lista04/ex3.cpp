//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <iostream>
#include <queue>
#include <stack>

int main()
{
    bool ehStack = true, ehQueue = true, ehPriority = true;

    std::stack<int> pilha;
    std::queue<int> fila;
    std::priority_queue<int> filaP;

    std::string comando, val;
    while(std::cin >> comando)
    {
        std::cin >> val;
        int numero = stoi(val);
        if(comando[0] == 'a') //comando add
        {
            pilha.push(numero);
            fila.push(numero);
            filaP.push(numero);
        }
        else
        {
            if(pilha.top() != numero)
                ehStack = false;
            if(fila.front() != numero)
                ehQueue = false;
            if(filaP.top() != numero)
                ehPriority = false;

            pilha.pop();
            fila.pop();
            filaP.pop();
        }

        if(!ehStack && !ehQueue && !ehPriority)
        {
            std::cout << "none";
            return 0;
        }
    }

    int quantos = ehStack + ehQueue + ehPriority;
    if(quantos > 1)
    {
        std::cout << "both";
    }
    else if(ehStack)
    {
        std::cout << "stack";
    }
    else if(ehQueue)
    {
        std::cout << "queue";
    }
    else if(ehPriority)
    {
        std::cout << "priority";
    }

    return 0;
}
