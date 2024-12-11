//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <algorithm>
#include <iostream>

std::string retira(std::string texto, char c)
{
    std::string ret = texto;
    ret.erase(std::remove(ret.begin(), ret.end(), c), ret.end());

    return ret;
}
