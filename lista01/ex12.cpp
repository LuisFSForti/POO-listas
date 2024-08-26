//Luis Filipe Silva Forti - 14592348

#include <iostream>

int pow(int b, int e, int m)
{
    int aux = 1;

    for (int i = 0; i < e; i++)
        aux *= b;

    return aux % m;
}

int main() {
    int b, e, m;

    std::cin >> b;
    std::cin >> e;
    std::cin >> m;

    std::cout << pow(b, e, m) << std::endl;
    return 0;
}
