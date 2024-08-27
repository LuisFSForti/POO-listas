//Luis Filipe Silva Forti - 14592348

#include <iostream>

int main() {
    char dados[1000000];
    int qtd = 0;
    std::string aux;

    while (std::getline(std::cin, aux))
    {
        dados[qtd] = stoi(aux)+48;
        qtd++;
    }

    for(int i = 0; i < qtd; i++)
    {
        for(int j = i+1; j < qtd; j++)
        {
            if(!(dados[i] ^ dados[j]))
            {
                //std::cout << dados[i] << " " << i << "@@@@" << j << " " << dados[j] << std::endl; //duplicata
                for(int a = i; a < j-1; a++)
                {
                    //std::cout << dados[a] << " dupla 1 " << dados[a+1] << std::endl; //duplicata
                    dados[a] = dados[a+1];
                }
                for(int a = j-1; a < qtd-1; a++)
                {
                    //std::cout << dados[a] << " dupla 2 " << dados[a+2] << std::endl; //duplicata
                    dados[a] = dados[a+2];
                }
                qtd--;
                i--;
                break;
            }
        }
    }

    std::cout << dados[0] << std::endl;


    return 0;
}
