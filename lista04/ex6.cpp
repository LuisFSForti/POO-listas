//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <vector>
#include <set>

std::vector<int> retira(std::vector<int> v, int n)
{
    //Cria um set com os valores de v
    //Set já ordena os dados e remove duplicatas
    std::set<int> ret(v.begin(), v.end());
    //Remove do set o valor pedido
    ret.erase(n);

    //Retorna um vetor com os dados do set
    return std::vector<int>(ret.begin(), ret.end());
}
