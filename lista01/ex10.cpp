//Luis Filipe Silva Forti - 14592348

#include <iostream>

int main() {
    double custo, valor;

    std::cin >> custo;
    std::cin >> valor;

    int notas[] = {20000, 10000, 5000, 2000, 1000, 500, 200, 100, 50, 25, 10, 5, 1}; //Valores *100 para calcular com inteiros
    int *qtdCedulas = (int*) calloc(sizeof(notas)/sizeof(float), sizeof(*qtdCedulas));

    int atual = 0;

    int aux = (valor * 100) - (custo * 100); //Transforma em inteiro para nao ocorrerem erros

    while (aux > 0)
    {
        if(aux >= notas[atual])
        {
            aux -= notas[atual];
            (*(qtdCedulas + atual))++;
        }
        else
            atual++;
    }

    //Define a quantidade de casas deciamais a serem imprimidas SEMPRE
    std::cout.precision(2);
    std::cout << std::fixed;

    std::cout << "Troco: R$ " << valor - custo << std::endl;

    for (int i = 0; i < sizeof(notas)/sizeof(float); i++)
        std::cout << *(qtdCedulas + i) << " de R$ " << (float)notas[i]/100 << std::endl;
    return 0;
}
