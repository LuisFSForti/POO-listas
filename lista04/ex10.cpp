//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>

void ordena_versoes(std::vector<std::string>& versoes)
{
    struct comparar
    {
        //https://stackoverflow.com/questions/18831470/sorting-a-string-vector-based-on-the-string-size
        inline bool operator()(const std::string& first, const std::string& second) const
        {
            return first.compare(second) < 0;
        }
    };

    comparar c;
    std::sort(versoes.begin(), versoes.end(), c);
}
