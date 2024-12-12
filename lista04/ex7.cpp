//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <algorithm>
#include <iostream>

std::string retira(std::string texto, char c)
{
    //Copia o texto para n�o alterar o dado passado
    std::string ret = texto;

    //std::remove move todos os valores C para o fim da string e retorna um iterador
    //Assim, o erase() remove todos os valores no final, come�ando pelo retorno do std::remove
    ret.erase(std::remove(ret.begin(), ret.end(), c), ret.end());

    //Retorna a string modificada
    return ret;
}
