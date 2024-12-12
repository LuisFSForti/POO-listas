//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <vector>
#include <iostream>
#include <regex>

void ordena_versoes(std::vector<std::string>& versoes)
{
    std::vector<std::vector<int>> valores;

    for(const auto& versao : versoes)
    {
        std::regex reg(R"(\d+)");
        std::sregex_iterator currentMatch(versao.begin(), versao.end(), reg);
        std::sregex_iterator endMatch;

        std::vector<int> dadosVersao;
        for(; currentMatch != endMatch; ++currentMatch)
            dadosVersao.push_back(stoi(currentMatch->str()));

        valores.push_back(dadosVersao);
    }

    for(int i = 0; i < versoes.size() - 1; i++)
    {
        int menor = i;

        for(int j = i+1; j < versoes.size(); j++)
        {
            int menorTamanho = valores.at(j).size();
            if(valores.at(menor).size() < valores.at(j).size())
                menorTamanho = valores.at(menor).size();

            bool iguais = true;
            for(int k = 0; k < menorTamanho; k++)
            {
                if(valores.at(menor).at(k) > valores.at(j).at(k))
                {
                    menor = j;
                    iguais = false;
                    break;
                }
                if(valores.at(menor).at(k) < valores.at(j).at(k))
                {
                    iguais = false;
                    break;
                }
            }
            if(iguais && valores.at(menor).size() > valores.at(j).size())
                menor = j;
        }

        if(menor == i)
            continue;

        versoes.push_back(versoes.at(i));
        versoes.erase(versoes.begin() + i);
        versoes.insert(versoes.begin() + i, versoes.at(menor - 1));
        versoes.erase(versoes.begin() + menor);

        valores.push_back(valores.at(i));
        valores.erase(valores.begin() + i);
        valores.insert(valores.begin() + i, valores.at(menor - 1));
        valores.erase(valores.begin() + menor);
    }
}
