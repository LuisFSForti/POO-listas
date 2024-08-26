//Luis Filipe Silva Forti - 14592348

#include <iostream>

int main() {
    int nro;
    std::cin >> nro;

    std::cout << "0";

    for (int i = 1; i <= 2*nro; i++)
    {
        std::cout << ", " << i;
    }

    return 0;
}
