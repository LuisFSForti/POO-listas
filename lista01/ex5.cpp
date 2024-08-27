//Luis Filipe Silva Forti - 14592348

#include <iostream>

int main() {
    int val = 0;
    int aux;

    while (std::cin >> aux)
    {
        val = val ^ aux;
    }

    std::cout << val << std::endl;

    return 0;
}
