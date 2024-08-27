//Luis Filipe Silva Forti - 14592348

#include <iostream>
#include <math.h>

int main() {
    int n1, n2, n3;
    std::cin >> n1;
    std::cin >> n2;
    std::cin >> n3;

    float medias[4];

    medias[0] = (n1 + n2 + n3)/3.0f; //aritmetica
    medias[1] = 3.0f/(1.0f/n1 + 1.0f/n2 + 1.0f/n3); //harmonica
    medias[2] = pow(n1 * n2 * n3, 1.0f/3.0f); //geometrica
    medias[3] = pow((pow(n1, 2) + pow(n2, 2) + pow(n3, 2))/3.0f, 0.5f); //quadratica

    std::cout << "Menor: " << medias[1] << std::endl;
    std::cout << "Maior: " << medias[3] << std::endl;

    return 0;
}
