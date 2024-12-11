//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <vector>
#include <iostream>

std::vector<double> notas(std::string s)
{
    std::string aux = s;
    std::vector<double> ret;

    while(aux.find(",") != -1)
    {
        aux = aux.substr(aux.find(",") + 1);
        ret.push_back(stod(aux.substr(0, aux.find(","))));
        aux = aux.substr(aux.find(",") + 1);
    }

    return ret;
}
