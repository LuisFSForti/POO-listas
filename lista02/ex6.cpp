//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <iostream>

class BigInt
{
private:
    int* _partes;
    int _npartes;
    bool _positivo;

public:
    //Construtor dado uma string
    BigInt(std::string numero)
    {
        //Pega o tamanho da string
        int tam = numero.length();

        //Define que o numero eh positivo
        this->_positivo = true;

        //Se o primeiro caractere da string for um '-'
        if(numero[0] == '-')
        {
            //Define que o numero eh negativo
            this->_positivo = false;
            //Define que o tamanho eh 1 menor
            tam--;
        }

        this->_npartes = tam / 9;
        int deslc = tam % 9;
        bool aux = deslc > 0;
        if(!aux)
        {
            this->_partes = (int*)calloc(this->_npartes, sizeof(int));
        }
        else
        {
            this->_npartes++;
            this->_partes = (int*)calloc(this->_npartes, sizeof(int));

            this->_partes[0] = std::stoi(numero.substr(1 - this->_positivo, deslc));
        }

        for(int i = aux; i < this->_npartes; i++)
            this->_partes[i] = std::stoi(numero.substr(1 - this->_positivo + deslc + (i - aux) * 9, 9));


        for(int i = 0; i < this->_npartes; i++)
        {
            if(this->_partes[i] != 0)
                return;
        }
        this->_positivo = true;
    }

    BigInt(int num = 0, bool eh_num = true)
    {
        if(eh_num)
        {
            new (this) BigInt(std::to_string(num));
        }
        else
        {
            this->_positivo = true;
            this->_npartes = num;
            this->_partes = (int*)calloc(this->_npartes, sizeof(int));
        }
    }

    BigInt(BigInt&& b)
    {
        this->_positivo = std::move(b._positivo);
        this->_npartes = std::move(b._npartes);

        if(b._partes != nullptr)
            this->_partes = b._partes;

            b._partes = nullptr;
    }

    ~BigInt()
    {
        delete this->_partes;
    }

    bool positivo() const
    {
        return this->_positivo;
    }

    BigInt& operator=(const BigInt& b)
    {
        this->_positivo = b._positivo;
        this->_npartes = b._npartes;

        if(this->_partes != nullptr)
            delete this->_partes;

        this->_partes = (int*)malloc(this->_npartes * sizeof(int));
        std::copy(b._partes, b._partes + this->_npartes, this->_partes);

        return *this;
    }

    BigInt abs() const
    {
        BigInt aux;
        aux = *this;
        aux._positivo = true;
        return aux;
    }

    friend bool operator==(const BigInt& a, const BigInt& b)
    {
        if(&a == &b)
            return true;

        if(a._positivo != b._positivo)
            return false;

        if(a._partes == b._partes)
            return true;

        if(a._partes == nullptr || b._partes == nullptr)
            return false;

        int menor = 0, diff1 = 0, diff2 = 0;
        if(a._npartes > b._npartes)
        {
            menor = b._npartes;
            diff1 = a._npartes - b._npartes;
            for(int i = 0; i < diff1; i++)
            {
                if(a._partes[i] != 0)
                    return false;
            }
        }
        else
        {
            menor = a._npartes;
            diff2 = b._npartes - a._npartes;
            for(int i = 0; i < diff2; i++)
            {
                if(b._partes[i] != 0)
                    return false;
            }
        }

        for(int i = 0; i < menor; i++)
        {
            if(a._partes[i + diff1] != b._partes[i + diff2])
                return false;
        }

        return true;
    }

    friend bool operator>(const BigInt& a, const BigInt& b)
    {
        if(a._positivo && !b._positivo)
            return true;

        if(!a._positivo && b._positivo)
            return false;

        bool saoPositivos = (a._positivo && b._positivo);

        int diff1 = 0, diff2 = 0, menorTam = 0;

        if(a._npartes < b._npartes)
        {
            menorTam = a._npartes;
            diff2 = b._npartes - a._npartes;

            for(int i = 0; i < diff2; i++)
            {
                if(b._partes[i] > 0)
                    return !saoPositivos;
            }
        }
        else
        {
            menorTam = b._npartes;
            diff1 = a._npartes - b._npartes;
            for(int i = 0; i < diff1; i++)
            {
                if(a._partes[i] > 0)
                    return saoPositivos;
            }
        }

        for(int i = 0; i < menorTam; i++)
        {
            if(a._partes[i + diff1] < b._partes[i + diff2])
                return !saoPositivos;
            if(a._partes[i + diff1] > b._partes[i + diff2])
                return saoPositivos;
        }
        return false;
    }

    friend BigInt operator+(const BigInt& a, const BigInt& b)
    {
        if(a.abs() == b.abs())
        {
            if(a._positivo != b._positivo)
                return BigInt();
        }

        int neg1 = 1, neg2 = 1, menor = 0, diff1 = 0, diff2 = 0;
        BigInt aux;

        if(!a._positivo)
            neg1 = -1;
        if(!b._positivo)
            neg2 = -1;

        if(a._npartes > b._npartes)
        {
            aux = BigInt(a._npartes + 1, false);

            menor = b._npartes;
            diff1 = a._npartes - b._npartes;

            for(int i = 0; i < diff1; i++)
                aux._partes[i + 1] = neg1 * a._partes[i];
        }
        else
        {
            aux = BigInt(b._npartes + 1, false);

            menor = a._npartes;
            diff2 = b._npartes - a._npartes;

            for(int i = 0; i < diff2; i++)
                aux._partes[i + 1] = neg2 * b._partes[i];
        }

        for(int i = 0; i < menor; i++)
        {
            aux._partes[i + diff1 + diff2 + 1] = neg1 * a._partes[i + diff1] + neg2 * b._partes[i + diff2];
        }

        //===================================Organizar=============================
        if(a.abs() > b.abs())
            aux._positivo = a._positivo;
        else
            aux._positivo = b._positivo;

        int negAux = 1;
        if(!aux._positivo)
            negAux = -1;

        for(int i = aux._npartes - 1; i > 0; i--)
        {
            aux._partes[i] *= negAux;
            if(aux._partes[i] < 0)
            {
                aux._partes[i] += 1000000000;
                aux._partes[i-1] -= negAux;
            }
            if(aux._partes[i] >= 1000000000)
            {
                aux._partes[i] -= 1000000000;
                aux._partes[i-1] += negAux;
            }
        }
        aux._partes[0] *= negAux;

        int diff = 0;
        for(int i = 0; i < aux._npartes-1 && aux._partes[i] == 0; i++)
            diff++;

        BigInt ret(aux._npartes - diff, false);
        ret._positivo = aux._positivo;

        for(int i = 0; i < ret._npartes; i++)
            ret._partes[i] = aux._partes[i + diff];

        return ret;
    }

    friend BigInt operator-(const BigInt& a, const BigInt& b)
    {
        return a + (-b);
    }

    BigInt operator-() const
    {
        BigInt ret;
        ret = *this;
        ret._positivo = !ret._positivo;
        return ret;
    }

    friend BigInt operator*(const BigInt& a, const BigInt& b)
    {
        if(a == BigInt() || b == BigInt())
            return BigInt();

        int neg1 = 1, neg2 = 1, negAux = 1;
        BigInt aux;

        if(!a._positivo)
            neg1 = -1;
        if(!b._positivo)
            neg2 = -1;

        aux = BigInt(a._npartes + b._npartes, false);
        aux._positivo = a._positivo == b._positivo;
        if(!aux._positivo)
            negAux = -1;

        for(int i = b._npartes-1; i >= 0; i--)
        {
            if(b._partes[i] == 0)
                continue;

            for(int j = a._npartes-1; j >= 0; j--)
            {
                long long int soma = (long long int)(aux._partes[i + j + 1]) + (long long int)(neg1 * a._partes[j]) * (long long int)(neg2 * b._partes[i]);
                soma *= negAux;
                if(soma < 0)
                {
                    aux._partes[i + j] -= negAux * (soma / -1000000000 + 1);
                    soma %= 1000000000;
                    soma += 1000000000;
                }
                if(soma >= 1000000000)
                {
                    aux._partes[i + j] += negAux * soma / 1000000000;
                    soma %= 1000000000;
                }
                aux._partes[i + j + 1] = negAux * soma;
            }
        }

        //========================= Organizar vetor =========================//
        for(int i = aux._npartes - 1; i >= 0; i--)
            aux._partes[i] *= negAux;

        int i = 0;
        int tam = aux._npartes;
        while(aux._partes[i] == 0 && i < aux._npartes-1)
        {
            i++;
            tam--;
        }

        BigInt res(tam, false);
        res._positivo = aux._positivo;
        for(int j = 0; j < tam; j++)
            res._partes[j] = aux._partes[j + i];

        return res;
    }

    BigInt operator/(int b) const
    {
        if(b == 0)
            return BigInt();
        if(BigInt(b).abs() > this->abs())
            return BigInt();
        if(*this == BigInt())
            return BigInt();

        long long int resto = this->_partes[0];
        BigInt aux(this->_npartes, false);

        if(!this->_positivo)
            b *= -1;
        if(b < 0)
        {
            aux._positivo = false;
            b *= -1;
        }

        for(int i = 0; i < this->_npartes - 1; i++)
        {
            aux._partes[i] = resto / b;
            resto = (resto % b) * 1000000000 + this->_partes[i+1];
        }
        aux._partes[aux._npartes-1] = resto / b;

        //========================= Organizar vetor =========================//

        int i = 0;
        int tam = aux._npartes;
        while(aux._partes[i] == 0 && i < aux._npartes-1)
        {
            i++;
            tam--;
        }

        BigInt res(tam, false);
        res._positivo = aux._positivo;
        for(int j = 0; j < tam; j++)
            res._partes[j] = aux._partes[j + i];

        return res;
    }

    friend BigInt operator^(const BigInt& a, const BigInt& b)
    {
        //https://www.geeksforgeeks.org/write-a-c-program-to-calculate-powxn/

        if(a == BigInt())
            return BigInt();

        if(b == BigInt())
            return BigInt(1);

        BigInt temp;
        temp = a ^ (b/2);

        if(b._partes[b._npartes - 1] % 2 == 0)
            return temp * temp;
        else
            return a * temp * temp;
    }


    friend std::ostream& operator<<(std::ostream &out, const BigInt &a)
    {
        if(a._partes == nullptr)
            return out;

        if(!a._positivo)
            out << "-";

        int i = 0;
        while(a._partes[i] == 0 && i < a._npartes - 1)
            i++;

        std::string aux;
        bool primeiro = true;
        for(; i < a._npartes; i++)
        {
            aux = std::to_string(a._partes[i]);

            if(!primeiro)
                aux.insert(0, 9 - aux.length(), '0');
            else
                primeiro = false;

            out << aux;
        }

        return out;
    }
};
