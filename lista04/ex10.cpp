//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <vector>
#include <iostream>
#include <regex>

void ordena_versoes(std::vector<std::string>& versoes)
{
    std::vector<std::vector<std::string>> valores;

    for(const auto& versao : versoes)
    {
        std::regex reg(R"(\d+)");
        std::sregex_iterator currentMatch(versao.begin(), versao.end(), reg);
        std::sregex_iterator endMatch;

        std::vector<std::string> dadosVersao;
        for(; currentMatch != endMatch; ++currentMatch)
            dadosVersao.push_back(currentMatch->str());

        valores.push_back(dadosVersao);
    }

    for(int i = 0; i < versoes.size() - 1; i++)
    {
        int menor = i;

        for(int j = i+1; j < versoes.size(); j++)
        {
            //std::cout << versoes.at(menor) << " > " << versoes.at(j) << " = " << (valores.at(menor) > valores.at(j)) << std::endl;
            if(valores.at(menor) > valores.at(j))
            {
                menor = j;
            }
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
