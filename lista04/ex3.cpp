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

    //Enquanto n�o for EOF
    while(std::cin >> comando)
    {
        //Pega o valor do comando
        std::cin >> val;
        int numero = stoi(val);

        //Comandos "add" e "pop"
        //Se come�ar com 'a' � "add", sen�o � "pop"
        if(comando[0] == 'a')
        {
            //Adicionar o valor �s estruturas
            pilha.push(numero);
            fila.push(numero);
            filaP.push(numero);
        }
        //Se for "pop"
        else
        {
            //Se o valor das estruturas for diferente do valor passado na entrada
            //Marca que n�o pode ser a estrutura
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

        //Se todos j� deram falso
        if(!ehStack && !ehQueue && !ehPriority)
        {
            //Avisa que n�o pode ser nenhum deles
            std::cout << "none";
            //Encerra o c�digo
            return 0;
        }
    }

    //Verifica quantos terminaram como true
    int quantos = ehStack + ehQueue + ehPriority;
    //Se mais de 1 deles for true
    if(quantos > 1)
    {
        //Alerta que n�o d� para saber
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

    //Encerra o c�digo
    return 0;
}
