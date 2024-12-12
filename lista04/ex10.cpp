//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <vector>
#include <iostream>
#include <regex>

void ordena_versoes(std::vector<std::string>& versoes)
{
    //Lista de listas de inteiro para armazenar as partes de cada versão
    std::vector<std::vector<int>> valores;

    //Loop para separar as versões
    for(const auto& versao : versoes)
    {
        //Configura o regex
        std::regex reg(R"(\d+)");
        std::sregex_iterator currentMatch(versao.begin(), versao.end(), reg);
        std::sregex_iterator endMatch;

        //Para salvar os dados da versão atual
        std::vector<int> dadosVersao;
        //Para cada pedaço da versão
        for(; currentMatch != endMatch; ++currentMatch)
            //Adiciona ela ao final do vetor
            dadosVersao.push_back(stoi(currentMatch->str()));

        //Adiciona o vetor
        valores.push_back(dadosVersao);
    }

    //Para cada versão
    for(int i = 0; i < versoes.size() - 1; i++)
    {
        //Para inicializar, fala que o menor é i
        int menor = i;

        //Para cada versão depois de i, para não analisar quem já foi arranjado e o valor de i
        for(int j = i+1; j < versoes.size(); j++)
        {
            //Verifica qual das versões tem menos partes
            int menorTamanho = valores.at(j).size();
            if(valores.at(menor).size() < valores.at(j).size())
                menorTamanho = valores.at(menor).size();

            //Se eles são iguais nos trechos analizados
            bool iguais = true;
            for(int k = 0; k < menorTamanho; k++)
            {
                //Se j tiver prioridade sobre o menor
                if(valores.at(menor).at(k) > valores.at(j).at(k))
                {
                    //Atualiza quem é o menor
                    menor = j;
                    //Define que eles não são iguais
                    iguais = false;
                    //Encerra o loop de análise
                    break;
                }
                //Se o menor tiver prioridade sobre o j
                if(valores.at(menor).at(k) < valores.at(j).at(k))
                {
                    //Define que não são iguais
                    iguais = false;
                    //Encerra o loop de análise
                    break;
                }
            }
            //Se, após o loop de análise, ele não encontrou diferença entre eles
            //Então o menor é quem tiver menos números
            if(iguais && valores.at(menor).size() > valores.at(j).size())
                menor = j;
        }

        //Se menor for i, então não necessita nenhuma alteração nos vetores
        if(menor == i)
            continue;

        //Se deve trocar o valor em i
        //Empurra o i para o final do vetor
        versoes.push_back(versoes.at(i));
        //Apaga ele na posição i
        versoes.erase(versoes.begin() + i);
        //Insere em i o menor valor encontrado
        versoes.insert(versoes.begin() + i, versoes.at(menor - 1));
        //Apaga o menor na sua antiga posição
        versoes.erase(versoes.begin() + menor);

        //Repete o processo para os valores das versões
        valores.push_back(valores.at(i));
        valores.erase(valores.begin() + i);
        valores.insert(valores.begin() + i, valores.at(menor - 1));
        valores.erase(valores.begin() + menor);
    }
}
