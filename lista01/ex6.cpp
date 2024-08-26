//Luis Filipe Silva Forti - 14592348

#include <iostream>

int soma(double a, double b)
{
    return a + b;
}

int main() {
    double a, b;
    std::cin >> a;
    std::cin >> b;

    std::cout << soma(a,b) << std::endl;
    return 0;
}
