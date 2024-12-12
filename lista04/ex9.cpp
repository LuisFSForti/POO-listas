//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <vector>
#include <iostream>

std::vector<double> notas(std::string s)
{
    //Para não alterar a string passada
    std::string aux = s;
    //Para salvar as notas
    std::vector<double> ret;

    //Enquanto tiverem dados
    while(aux.find(",") != -1)
    {
        //Remove tudo até a primeira vírgula, ou seja, remove o nome do aluno atual
        aux = aux.substr(aux.find(",") + 1);

        //Transforma a string entre o começo e a próxima vírgula para double, pois é o trecho onde está a nota
        //Insere a nota no final
        ret.push_back(stod(aux.substr(0, aux.find(","))));

        //Remove tudo até a primeira vírgula, ou seja, remove a nota do aluno atual
        aux = aux.substr(aux.find(",") + 1);
    }

    //Retorna as notas encontradas
    return ret;
}
