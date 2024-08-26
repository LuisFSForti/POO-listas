//Luis Filipe Silva Forti - 14592348

#include <iostream>

int main() {
    int nro;
    std::cin >> nro;

    for (int i = 1; i <= nro; i++)
    {
        if (i % 3 == 0 && i % 5 == 0 && i % 7 == 0 && i % 11 == 0 && i % 17 == 0)
            std::cout << i << std::endl;
    }
    return 0;
}
