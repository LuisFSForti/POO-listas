//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <vector>
#include <set>

std::vector<int> retira(std::vector<int> v, int n)
{
    std::set<int> ret(v.begin(), v.end());
    ret.erase(n);

    return std::vector<int>(ret.begin(), ret.end());
}
