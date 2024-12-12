//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <iostream>
#include <queue>
#include <stack>

int main()
{
    //Inicialmente, pode ser qualquer tipo
    bool ehStack = true, ehQueue = true, ehPriority = true;

    //Para fazer os testes
    std::stack<int> pilha;
    std::queue<int> fila;
    std::priority_queue<int> filaP;

    //Auxiliares
    std::string comando, val;

    //Enquanto não for EOF
    while(std::cin >> comando)
    {
        //Pega o valor do comando
        std::cin >> val;
        int numero = stoi(val);

        //Comandos "add" e "pop"
        //Se começar com 'a' é "add", senão é "pop"
        if(comando[0] == 'a')
        {
            //Adicionar o valor às estruturas
            pilha.push(numero);
            fila.push(numero);
            filaP.push(numero);
        }
        //Se for "pop"
        else
        {
            //Se o valor das estruturas for diferente do valor passado na entrada
            //Marca que não pode ser a estrutura
            if(pilha.top() != numero)
                ehStack = false;
            if(fila.front() != numero)
                ehQueue = false;
            if(filaP.top() != numero)
                ehPriority = false;

            //Remove os valores das estruturas
            pilha.pop();
            fila.pop();
            filaP.pop();
        }

        //Se todos já deram falso
        if(!ehStack && !ehQueue && !ehPriority)
        {
            //Avisa que não pode ser nenhum deles
            std::cout << "none";
            //Encerra o código
            return 0;
        }
    }

    //Verifica quantos terminaram como true
    int quantos = ehStack + ehQueue + ehPriority;
    //Se mais de 1 deles for true
    if(quantos > 1)
    {
        //Alerta que não dá para saber
        std::cout << "both";
    }
    //Se apenas 1 for true
    //Alerta qual
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

    //Encerra o código
    return 0;
}
