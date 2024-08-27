//Luis Filipe Silva Forti - 14592348

#include <iostream>

int main() {
    int nro;
    std::cin >> nro;

    int rep = nro/19635;

    for (int i = 1; i <= rep; i++)
    {
        std::cout << 19635*i << std::endl;
    }
    return 0;
}
