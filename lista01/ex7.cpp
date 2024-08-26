//Luis Filipe Silva Forti - 14592348

#include <iostream>
#include <cmath>

int seq(int n, int k, int *ini)
{
    if (n < k)
        return *(ini + n);

    int an = 0;

    for (int i = n - k; i <= n-1; i++)
    {
        an += std::pow(seq(i, k, ini), 2);
    }

    return an;
}

int main() {
    int n, k;
    std::cin >> n;
    std::cin >> k;
    int *ini = (int*) calloc(k, sizeof(*ini));

    for (int i = 0; i < k; i++)
    {
        std::cin >> *(ini + i);
    }

    std::cout << seq(n, k, ini) << std::endl;
    return 0;
}
