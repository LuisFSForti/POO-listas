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
            //Sabe-se que os sinais sao diferentes, senao teria saído no começo do código
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


class Fracao
{
private:
    BigInt _numerador, _denominador;

public:
    Fracao(BigInt numerador = BigInt("0"), BigInt denominador = BigInt("1"))
    {
        _numerador = numerador;
        _denominador = denominador;
    }

    friend Fracao operator+(const Fracao&a, const Fracao& b)
    {
        Fracao ret(a._numerador * b._denominador + b._numerador * a._denominador, a._denominador * b._denominador);

        if(!ret._denominador.positivo())
        {
            ret._numerador = -ret._numerador;
            ret._denominador = -ret._denominador;
        }

        if(ret._numerador == BigInt())
            return Fracao();

        return ret;
    }

    friend Fracao operator-(const Fracao&a, const Fracao& b)
    {
        Fracao ret(a._numerador * b._denominador - b._numerador * a._denominador, a._denominador * b._denominador);

        if(!ret._denominador.positivo())
        {
            ret._numerador = -ret._numerador;
            ret._denominador = -ret._denominador;
        }

        if(ret._numerador == BigInt())
            return Fracao();

        return ret;
    }

    friend Fracao operator*(const Fracao&a, const Fracao& b)
    {
        Fracao ret(a._numerador * b._numerador, a._denominador * b._denominador);

        if(!ret._denominador.positivo())
        {
            ret._numerador = -ret._numerador;
            ret._denominador = -ret._denominador;
        }

        if(ret._numerador == BigInt())
            return Fracao();

        return ret;
    }

    friend Fracao operator/(const Fracao&a, const Fracao& b)
    {
        Fracao ret(a._numerador * b._denominador, a._denominador * b._numerador);

        if(!ret._denominador.positivo())
        {
            ret._numerador = -ret._numerador;
            ret._denominador = -ret._denominador;
        }

        if(ret._numerador == BigInt())
            return Fracao();

        return ret;
    }

    friend std::ostream& operator<<(std::ostream &out, const Fracao &a)
    {
        out << a._numerador << "/" << a._denominador;

        return out;
    }
};

int main() {
    Fracao f(BigInt(734035207), BigInt(511864916));
    f = f - Fracao(BigInt(-832889994), BigInt(1664678207));
    std::cout << f << std::endl;
    f = f - Fracao(BigInt(-2065362421), BigInt(1465263685));
    std::cout << f << std::endl;
    f = f / Fracao(BigInt(-1579505132), BigInt(1031534419));
    std::cout << f << std::endl;
    f = f + Fracao(BigInt(-2087703387), BigInt(1458675701));
    std::cout << f << std::endl;
    f = f + Fracao(BigInt(1448063409), BigInt(265161020));
    f = f * Fracao(BigInt(-1067260534), BigInt(77665922));
    std::cout << f << std::endl;
    f = f * Fracao(BigInt(535477398), BigInt(1149576813));
    std::cout << f << std::endl;
    f = f * Fracao(BigInt(-1819355311), BigInt(1885855873));
    f = f - Fracao(BigInt(-1503143432), BigInt(1542581269));
    f = f / Fracao(BigInt(-214861489), BigInt(710880101));
    f = f * Fracao(BigInt(868649458), BigInt(831688637));
    f = f - Fracao(BigInt(-323305070), BigInt(125805741));
    std::cout << f << std::endl;
    f = f / Fracao(BigInt(-1659137372), BigInt(525625098));
    f = f * Fracao(BigInt(889780758), BigInt(1014960705));
    f = f - Fracao(BigInt(463245808), BigInt(1159366211));
    f = f + Fracao(BigInt(2000035477), BigInt(1998095752));
    std::cout << f << std::endl;
    f = f + Fracao(BigInt(-822061296), BigInt(633431096));
    std::cout << f << std::endl;
    f = f / Fracao(BigInt(90099074), BigInt(979243045));
    f = f - Fracao(BigInt(-2077266442), BigInt(364212872));
    f = f / Fracao(BigInt(176772741), BigInt(1989887008));
    f = f + Fracao(BigInt(-882674286), BigInt(2138806630));
    f = f / Fracao(BigInt(-1828002719), BigInt(31957551));
    f = f * Fracao(BigInt(277199174), BigInt(630444441));
    f = f + Fracao(BigInt(-1699658878), BigInt(220973317));
    f = f / Fracao(BigInt(1030294995), BigInt(1465089980));
    f = f * Fracao(BigInt(-2093379309), BigInt(440289461));
    f = f / Fracao(BigInt(284751535), BigInt(1882759700));
    f = f * Fracao(BigInt(-1415910765), BigInt(146399307));
    std::cout << f << std::endl;
    f = f + Fracao(BigInt(703498064), BigInt(1652391301));
    std::cout << f << std::endl;
    f = f - Fracao(BigInt(177528288), BigInt(1427053122));
    f = f * Fracao(BigInt(1281519613), BigInt(850820129));
    std::cout << f << std::endl;
    f = f / Fracao(BigInt(-1141030176), BigInt(1267358714));
    f = f + Fracao(BigInt(994379642), BigInt(1296913569));
    std::cout << f << std::endl;
    f = f / Fracao(BigInt(55604378), BigInt(1375242981));
    std::cout << f << std::endl;
    f = f - Fracao(BigInt(-1012499205), BigInt(97750314));
    f = f + Fracao(BigInt(1554214190), BigInt(1056101057));
    std::cout << f << std::endl;
    f = f + Fracao(BigInt(2134699649), BigInt(543379477));
    f = f - Fracao(BigInt(1471011707), BigInt(1007426153));
    f = f + Fracao(BigInt(319521006), BigInt(224412655));
    f = f / Fracao(BigInt(460353776), BigInt(939511164));
    f = f - Fracao(BigInt(-2068358448), BigInt(1963544818));
    std::cout << f << std::endl;
    f = f / Fracao(BigInt(-1163286621), BigInt(1124663496));
    f = f - Fracao(BigInt(-1788814729), BigInt(520153090));
    f = f * Fracao(BigInt(1495002710), BigInt(884993849));
    std::cout << f << std::endl;
    f = f - Fracao(BigInt(1598621538), BigInt(521662581));
    f = f / Fracao(BigInt(-1553320247), BigInt(467448920));
    f = f * Fracao(BigInt(1759919979), BigInt(942165013));
    f = f - Fracao(BigInt(-363108334), BigInt(1682208386));
    f = f + Fracao(BigInt(783892269), BigInt(1739553544));
    f = f * Fracao(BigInt(-1903057160), BigInt(546775176));
    f = f / Fracao(BigInt(642905460), BigInt(1457012917));
    f = f - Fracao(BigInt(1643204606), BigInt(588485109));
    f = f * Fracao(BigInt(1014830965), BigInt(2067335770));
    f = f / Fracao(BigInt(306268751), BigInt(924921327));
    f = f + Fracao(BigInt(-1171676835), BigInt(2108110786));
    f = f / Fracao(BigInt(892920551), BigInt(988023546));
    f = f - Fracao(BigInt(-73965338), BigInt(1974893394));
    f = f / Fracao(BigInt(-761348350), BigInt(1085950737));
    std::cout << f << std::endl;
    return 0;
}
