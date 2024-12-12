//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <vector>

typedef std::vector<std::vector<int>> Matriz;

void ordena_par(Matriz& M)
{
    //Para facilitar, cria-se uma nova matriz com os valores de saída
    Matriz ret;
    //Cria-se um vetor para armazenar a quantidade de pares em cada linha
    std::vector<int> valores;

    //Para cada linha
    for(int i = 0; i < M.size(); i++)
    {
        //Conta a quantidade de pares na linha
        int qtdPares = 0;
        for(int j = 0; j < M.at(i).size(); j++)
        {
            if(M.at(i).at(j) % 2 == 0)
                qtdPares++;
        }

        //k é onde deve ser salva a linha na matriz de saída
        int k = 0;
        for(; k < valores.size(); k++)
        {
            //Se a linha k tem mais pares que a linha atual
            if(valores.at(k) > qtdPares)
            {
                //Encerra o loop, pois achou onde deve inserir
                break;
            }
            //Se tiverem a mesma quantidade de pares
            if(valores.at(k) == qtdPares)
            {
                //Para saber se a linha atual tem prioridade sobre a linha k
                bool achou = false;

                //Para cada elemento da linha
                for(int l = 0; l < M.at(i).size(); l++)
                {
                    //Se a o elemento de k tem prioridade sobre o elemento da atual
                    if(M.at(i).at(l) > ret.at(k).at(l))
                        //Encerra a busca na linha, pois não deve ser aqui a inserção
                        break;
                    //Se o elemento da atual tem prioridade sobre o elemento de k
                    else if(M.at(i).at(l) < ret.at(k).at(l))
                    {
                        //Salva que deve ser aqui a inserção
                        achou = true;
                        //Encerra a busca na linha
                        break;
                    }
                }
                //Se deve inserir no k atual
                if(achou)
                    //Encerra o loop, pois achou onde deve inserir
                    break;
            }
        }
        //Salva a quantidade de pares e a linha na posição, ambos na posição k
        valores.insert(valores.begin() + k, qtdPares);
        ret.insert(ret.begin() + k, M.at(i));
    }

    //Atualiza a matriz M passada
    M = ret;
}
