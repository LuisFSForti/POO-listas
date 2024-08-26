//Luis Filipe Silva Forti - 14592348

#include <iostream>
#include <math.h>

std::string raizes(double a, double b, double c)
{
    if (a == 0)
        return "Infinitas";

    if (pow(b , 2) < 4*a*c)
        return "Nenhuma";

    double x1 = (-b + sqrt(pow(b,2) - 4 * a * c))/(2*a);
    double x2 = (-b - sqrt(pow(b,2) - 4 * a * c))/(2*a);

    if (x1 == x2)
        return std::to_string(x1);

    if (x1 < x2)
        return std::to_string(x1) + " e " + std::to_string(x2);
    else
        return std::to_string(x2) + " e " + std::to_string(x1);
}

int main() {
    double a, b, c;

    std::cin >> a;
    std::cin >> b;
    std::cin >> c;

    std::cout << raizes(a, b, c) << std::endl;
    return 0;
}
