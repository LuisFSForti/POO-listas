//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <vector>
#include <iostream>
#include <regex>

void ordena_versoes(std::vector<std::string>& versoes)
{
    //Lista de listas de inteiro para armazenar as partes de cada vers�o
    std::vector<std::vector<int>> valores;

    //Loop para separar as vers�es
    for(const auto& versao : versoes)
    {
        //Configura o regex
        std::regex reg(R"(\d+)");
        std::sregex_iterator currentMatch(versao.begin(), versao.end(), reg);
        std::sregex_iterator endMatch;

        //Para salvar os dados da vers�o atual
        std::vector<int> dadosVersao;
        //Para cada peda�o da vers�o
        for(; currentMatch != endMatch; ++currentMatch)
            //Adiciona ela ao final do vetor
            dadosVersao.push_back(stoi(currentMatch->str()));

        //Adiciona o vetor
        valores.push_back(dadosVersao);
    }

    //Para cada vers�o
    for(int i = 0; i < versoes.size() - 1; i++)
    {
        //Para inicializar, fala que o menor � i
        int menor = i;

        //Para cada vers�o depois de i, para n�o analisar quem j� foi arranjado e o valor de i
        for(int j = i+1; j < versoes.size(); j++)
        {
            //Verifica qual das vers�es tem menos partes
            int menorTamanho = valores.at(j).size();
            if(valores.at(menor).size() < valores.at(j).size())
                menorTamanho = valores.at(menor).size();

            //Se eles s�o iguais nos trechos analizados
            bool iguais = true;
            for(int k = 0; k < menorTamanho; k++)
            {
                //Se j tiver prioridade sobre o menor
                if(valores.at(menor).at(k) > valores.at(j).at(k))
                {
                    //Atualiza quem � o menor
                    menor = j;
                    //Define que eles n�o s�o iguais
                    iguais = false;
                    //Encerra o loop de an�lise
                    break;
                }
                //Se o menor tiver prioridade sobre o j
                if(valores.at(menor).at(k) < valores.at(j).at(k))
                {
                    //Define que n�o s�o iguais
                    iguais = false;
                    //Encerra o loop de an�lise
                    break;
                }
            }
            //Se, ap�s o loop de an�lise, ele n�o encontrou diferen�a entre eles
            //Ent�o o menor � quem tiver menos n�meros
            if(iguais && valores.at(menor).size() > valores.at(j).size())
                menor = j;
        }

        //Se menor for i, ent�o n�o necessita nenhuma altera��o nos vetores
        if(menor == i)
            continue;

        //Se deve trocar o valor em i
        //Empurra o i para o final do vetor
        versoes.push_back(versoes.at(i));
        //Apaga ele na posi��o i
        versoes.erase(versoes.begin() + i);
        //Insere em i o menor valor encontrado
        versoes.insert(versoes.begin() + i, versoes.at(menor - 1));
        //Apaga o menor na sua antiga posi��o
        versoes.erase(versoes.begin() + menor);

        //Repete o processo para os valores das vers�es
        valores.push_back(valores.at(i));
        valores.erase(valores.begin() + i);
        valores.insert(valores.begin() + i, valores.at(menor - 1));
        valores.erase(valores.begin() + menor);
    }
}
