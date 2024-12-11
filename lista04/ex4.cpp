//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>

void ordena_strings(std::vector<std::string>& vetor)
{
    struct comparar
    {
        //https://stackoverflow.com/questions/18831470/sorting-a-string-vector-based-on-the-string-size
        inline bool operator()(const std::string& first, const std::string& second) const
        {
            if(first.size() < second.size())
                return true;

            if(first.size() == second.size())
            {
                if(first.compare(second) > 0)
                    return true;
            }

            return false;
        }
    };

    comparar c;
    std::sort(vetor.begin(), vetor.end(), c);
}
