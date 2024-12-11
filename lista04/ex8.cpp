//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <vector>

typedef std::vector<std::vector<int>> Matriz;

void ordena_par(Matriz& M)
{
    Matriz ret;
    std::vector<int> valores;

    for(int i = 0; i < M.size(); i++)
    {
        int qtdPares = 0;
        for(int j = 0; j < M.at(i).size(); j++)
        {
            if(M.at(i).at(j) % 2 == 0)
                qtdPares++;
        }

        int k = 0;
        for(; k < valores.size(); k++)
        {
            if(valores.at(k) > qtdPares)
            {
                break;
            }
            if(valores.at(k) == qtdPares)
            {
                bool achou = false;
                for(int l = 0; l < M.at(i).size(); l++)
                {
                    if(M.at(i).at(l) > ret.at(k).at(l))
                        break;
                    else if(M.at(i).at(l) < ret.at(k).at(l))
                    {
                        achou = true;
                        break;
                    }
                }
                if(achou)
                    break;
            }
        }
        valores.insert(valores.begin() + k, qtdPares);
        ret.insert(ret.begin() + k, M.at(i));
    }

    M = ret;
}
