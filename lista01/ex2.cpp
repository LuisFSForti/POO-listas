//Luis Filipe Silva Forti - 14592348

#include <iostream>

int main() {
    int nroBala, nroChoco;
    float precBala, precChoco;

    std::cin >> nroBala;
    std::cin >> precBala;
    std::cin >> nroChoco;
    std::cin >> precChoco;

    float total = nroBala * precBala + nroChoco * precChoco;

    //Define a quantidade de casas deciamais a serem imprimidas SEMPRE
    std::cout.precision(1);
    std::cout << std::fixed;

    std::cout << total << std::endl;
    return 0;
}
