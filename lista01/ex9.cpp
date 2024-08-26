//Luis Filipe Silva Forti - 14592348

#include <iostream>
#include <math.h>

int main() {
    double x1, x2, y1, y2;
    std::cin >> x1;
    std::cin >> y1;
    std::cin >> x2;
    std::cin >> y2;

    double d = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));

    //Define a quantidade de casas deciamais a serem imprimidas SEMPRE
    std::cout.precision(4);
    std::cout << std::fixed;

    std::cout << d << std::endl;

    return 0;
}
