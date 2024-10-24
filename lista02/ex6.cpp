//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <iostream>
#include <string>
#include <iomanip>

class BigInt
{
private:
    int* _partes;
    int _npartes;
    bool _positivo;

public:
    BigInt(std::string numero)
    {
        _npartes = numero.size();

        if(numero[0] == '-')
        {
            this->_positivo = false;
            this->_npartes--;
        }
        else
            this->_positivo = true;

        this->_partes = (int*) (calloc(this->_npartes, sizeof(int)));

        if(this->_positivo)
        {
            for(int i = 0; i < this->_npartes; i++)
                this->_partes[i] = numero[i] - '0';
        }
        else
        {
            for(int i = 0; i < this->_npartes; i++)
                this->_partes[i] = numero[i + 1] - '0';
        }
    }

    BigInt(int num, bool eh_num)
    {
        std::string numero;
        if(eh_num)
        {
            numero = std::to_string(num);
        }
        else
        {
            this->_npartes = num;
            numero.insert(0, _npartes, '0');
        }
        new (this) BigInt(numero);
    }

    BigInt() : BigInt(9, false) {};

    BigInt(BigInt&& b)
    {
        this->_npartes = std::move(b._npartes);
        this->_positivo = std::move(b._positivo);
        this->_partes = b._partes;
        b._partes = nullptr;
    }

    ~BigInt()
    {
        delete this->_partes;
    }

    bool positivo()
    {
        return this->_positivo;
    }

    BigInt& operator=(const BigInt& b)
    {
        if(this == &b)
            return *this;

        this->_positivo = b._positivo;
        this->_npartes = b._npartes;

        if(this->_partes != nullptr)
            delete this->_partes;

        this->_partes = (int*)malloc(this->_npartes * sizeof(int));
        std::copy(b._partes, b._partes + this->_npartes, this->_partes);

        return *this;
    }

    BigInt abs()
    {
        BigInt aux;
        aux = *this;
        aux._positivo = true;
        return aux;
    }

    friend std::ostream& operator<<(std::ostream &out, const BigInt &a)
    {
        if(a._partes == nullptr)
            return out;

        if(!a._positivo)
            out << "-";

        for(int i = 0; i < a._npartes; i++)
        {
            out << a._partes[i];
        }

        return out;
    }
};

int main()
{
    BigInt teste1("-234586");
    BigInt teste2(333, true);
    BigInt teste3(3, false);
    BigInt teste4;
    BigInt teste5(std::move(teste1));
    std::cout << teste1 << " " << teste2 << " " << teste3 << " " << teste4 << " " << teste5 << std::endl;
    teste1 = teste5.abs();
    std::cout << teste1 << " " << teste2 << " " << teste3 << " " << teste4 << " " << teste5 << std::endl;
    return 0;
}
