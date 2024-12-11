//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <vector>
#include <iostream>

void ordena_strings(std::vector<std::string>& vetor)
{
    for(int i = 0; i < vetor.size() - 1; i++)
    {
        int menor = i;
        for(int j = i + 1; j < vetor.size(); j++)
        {
            if(vetor.at(j).length() < vetor.at(menor).length())
            {
                menor = j;
            }
            else if(vetor.at(j).length() == vetor.at(menor).length())
            {
                if(vetor.at(j).compare(vetor.at(menor)) > 0)
                {
                    menor = j;
                }
            }
        }

        if(i == menor)
            continue;

        vetor.insert(vetor.end(), vetor.at(i)); //Insere no fim pois não importa
        vetor.erase(vetor.begin() + i);
        vetor.insert(vetor.begin() + i, vetor.at(menor - 1));
        vetor.erase(vetor.begin() + menor);
    }
}
