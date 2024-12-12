//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>

void ordena_strings(std::vector<std::string>& vetor)
{
    //Uma struct que define como comparar dois valores da pilha
    //Usa-se ela para o std::sort, o qual precisa de uma forma de definir a ordem que deve organizar
    struct comparar
    {
        //https://stackoverflow.com/questions/18831470/sorting-a-string-vector-based-on-the-string-size
        inline bool operator()(const std::string& first, const std::string& second) const
        {
            //Se o primeiro for menor que o segundo
            if(first.size() < second.size())
                //Retorna que o primeiro tem prioridade na estrutura
                return true;

            //Se tiverem o mesmo tamanho
            if(first.size() == second.size())
            {
                //Se o segundo tiver prioridade alfabeticamente
                if(first.compare(second) > 0)
                    //Retorna que o primeiro tem prioridade na estrutura
                    return true;
            }

            //Retorna falso se o segundo tem prioridade na estrutura sobre o primeiro
            return false;
        }
    };

    //Ordena o vetor
    comparar c;
    std::sort(vetor.begin(), vetor.end(), c);
}
