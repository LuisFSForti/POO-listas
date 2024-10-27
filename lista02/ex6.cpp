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

    BigInt(int num = 0, bool eh_num = true)
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

        if(a._npartes != b._npartes)
            return false;

        if(a._partes == b._partes)
            return true;

        if(a._partes == nullptr || b._partes == nullptr)
            return false;

        for(int i = 0; i < a._npartes; i++)
        {
            if(a._partes[i] != b._partes[i])
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

        bool saoNegativos = (!a._positivo && !b._positivo);

        int diff1 = 0, diff2 = 0, menorTam = a._npartes;

        if(a._npartes < b._npartes)
        {
            diff2 = b._npartes - a._npartes;
            for(int i = 0; i < diff2; i++)
            {
                if(b._partes[i] > 0)
                    return saoNegativos;
            }
        }
        else
        {
            diff1 = a._npartes - b._npartes;
            for(int i = 0; i < diff1; i++)
            {
                if(a._partes[i] > 0)
                    return !saoNegativos;
            }
        }

        for(int i = 0; i < menorTam; i++)
        {
            if(a._partes[i + diff1] < b._partes[i + diff2])
                return saoNegativos;
            if(a._partes[i + diff1] > b._partes[i + diff2])
                return !saoNegativos;
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

        int maior, menor, diff1 = 0, diff2 = 0, neg1 = 1, neg2 = 1;
        BigInt aux;

        if(!a._positivo)
            neg1 = -1;
        if(!b._positivo)
            neg2 = -1;

        if(a._npartes > b._npartes)
        {
            maior = a._npartes;
            menor = b._npartes;
            diff1 = maior - menor;

            aux = BigInt(maior + 1, false);

            for(int i = 0; i < diff1; i++)
            {
                aux._partes[i + 1] = neg1 * a._partes[i];
            }
        }
        else
        {
            maior = b._npartes;
            menor = a._npartes;
            diff2 = maior - menor;

            aux = BigInt(maior + 1, false);

            for(int i = 0; i < diff2; i++)
            {
                aux._partes[i + 1] = neg2 * b._partes[i];
            }
        }

        for(int i = 0; i < menor; i++)
        {
            aux._partes[i + diff1 + diff2 + 1] = neg1 * a._partes[i + diff1] + neg2 * b._partes[i + diff2];
        }

        if(a.abs() == b.abs())
            //Sabe-se que os sinais sao diferentes, senao teria saído no começo do codigo
            aux._positivo = a._positivo;
        if(a.abs() > b.abs())
            aux._positivo = a._positivo;
        else
            aux._positivo = b._positivo;

        //========================= Organizar vetor =========================//
        int negAux = 1;
        if(!aux._positivo)
            negAux = -1;

        for(int i = aux._npartes - 1; i > 0; i--)
        {
            aux._partes[i] *= negAux;
            while(aux._partes[i] < 0)
            {
                aux._partes[i] += 10;
                aux._partes[i - 1] -= negAux;
            }
            while(aux._partes[i] > 9)
            {
                aux._partes[i] -= 10;
                aux._partes[i - 1] += negAux;
            }
        }
        aux._partes[0] *= negAux;

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

    friend BigInt operator-(const BigInt& a, const BigInt& b)
    {
        return a + (-b);
    }

    BigInt operator-() const
    {
        BigInt aux;
        aux = *this;
        aux._positivo = !aux._positivo;
        return aux;
    }

    friend BigInt operator*(const BigInt& a, const BigInt& b)
    {
        if(a == BigInt() || b == BigInt())
            return BigInt();

        int neg1 = 1, neg2 = 1;
        BigInt aux;

        if(!a._positivo)
            neg1 = -1;
        if(!b._positivo)
            neg2 = -1;

        aux = BigInt(a._npartes + b._npartes, false);

        for(int i = b._npartes-1; i >= 0; i--)
        {
            if(b._partes[i] == 0)
                continue;

            for(int j = a._npartes-1; j >= 0; j--)
                aux._partes[i + j + 1] += neg1 * a._partes[j] * neg2 * b._partes[i];
        }

        aux._positivo = a._positivo == b._positivo;

        //========================= Organizar vetor =========================//
        int negAux = 1;
        if(!aux._positivo)
            negAux = -1;

        for(int i = aux._npartes - 1; i > 0; i--)
        {
            aux._partes[i] *= negAux;
            while(aux._partes[i] < 0)
            {
                aux._partes[i] += 10;
                aux._partes[i - 1] -= negAux;
            }
            while(aux._partes[i] > 9)
            {
                aux._partes[i] -= 10;
                aux._partes[i - 1] += negAux;
            }
        }
        aux._partes[0] *= negAux;

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

    BigInt operator/(int b)
    {
        if(BigInt(b).abs() > (*this).abs())
            return BigInt("0");

        BigInt dividendo, aux(0), divisor(b);
        dividendo = *this;

        std::string mult;
        mult.insert(0, dividendo._npartes, '0');
        mult.insert(0, 1, '1');
        if(divisor._positivo != dividendo._positivo)
            mult.insert(0, 1, '-');

        BigInt aumento, decremento;
        while(dividendo.abs() > divisor.abs())
        {
            int pos = mult.find("1");
            mult[pos] = '0';
            mult[pos+1] = '1';
            aumento = BigInt(mult);
            decremento = divisor * BigInt(mult);
            while(dividendo.abs() > decremento.abs())
            {
                aux = aux + aumento;
                dividendo = dividendo - decremento;
            }
        }

        aux._positivo = divisor._positivo == dividendo._positivo;

        return aux;
    }

    friend BigInt operator^(const BigInt& a, const BigInt& b)
    {
        BigInt aux("1");

        int multi = 1;
        for(int i = b._npartes-1; i >=0; i--)
        {
            if(b._partes[i] != 0)
            {
                for(int j = 0; j < b._partes[i] * multi; j++)
                {
                    aux = aux * a;
                }
            }
            multi *= 10;
        }

        return aux;
    }

    friend std::ostream& operator<<(std::ostream &out, const BigInt &a)
    {
        if(a._partes == nullptr)
            return out;

        if(!a._positivo)
            out << "-";

        int i;
        while(a._partes[i] == 0 && i < a._npartes-1)
            i++;
        for(; i < a._npartes; i++)
        {
            out << a._partes[i];
        }

        return out;
    }
};
