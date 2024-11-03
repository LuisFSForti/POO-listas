//Luis Filipe Silva Forti - 14592348

#include <stdio.h>
#include <iostream>

class C
{
private:
    double _real, _imag;

public:
    C(double real = 0, double imag = 0)
    {
        this->_real = real;
        this->_imag = imag;
    }

    C& operator=(const C& b)
    {
        this->_real = b._real;
        this->_imag = b._imag;

        return *this;
    }

    //Para pegar o valor do atributo real, necessario para o restante da hierarquia
    double real() const
    {
        return this->_real;
    }

    //Para pegar o valor do atributo imaginario
    double imag() const
    {
        return this->_imag;
    }

    //Para comparar dois valores
    friend bool operator==(const C& a, const C& b)
    {
        //Se tiverem o mesmo endereco, entao sao a mesma instancia
        if(&a == &b)
            return true;

        if(a._real != b._real)
            return false;

        if(a._imag != b._imag)
            return false;

        //Se nao achou nenhuma diferenca, retorna verdadeiro
        return true;
    }

    //z = a + bi
    //-z = -a - bi
    C operator-() const
    {
        C ret;
        ret._real = -(*this)._real;
        ret._imag = -(*this)._imag;
        return ret;
    }

    //z1 = a + bi
    //z2 = c + di
    //z1 + z2 = a + c + (b + d) i
    friend C operator+(const C& a, const C& b)
    {
        C ret;

        //a + c
        ret._real = a._real + b._real;
        //b + d
        ret._imag = a._imag + b._imag;

        return ret;
    }

    //z1 = a + bi
    //z2 = c + di
    //z1 - z2 = a - c + i(b - d) = z1 + (-z2)
    friend C operator-(const C& a, const C& b)
    {
        return a + (-b);
    }

    //z1 = a + bi
    //z2 = c + di
    //z1 * z2 = a*c + a*di + bi*c + bi*di = a*c - b*d + (a*d + b*c)*i
    friend C operator*(const C& a, const C& b)
    {
        C ret;

        //a*c - b*d
        ret._real = a._real * b._real - a._imag * b._imag;
        //a*d + b*c
        ret._imag = a._real * b._imag + a._imag * b._real;

        return ret;
    }

    //z1 = a + bi
    //z2 = c + di
    //z1 / z2 = z1 / z2 * conjugado(z2)/conjugado(z2) = (a + bi) * (c - di) / (c^2 + d^2)
    //z1 / z2 = (a * c + b * d)/(c^2 + d^2) + (-a * d + b * c)/(c^2 + d^2) i
    friend C operator/(const C& a, const C& b)
    {
        C ret;

        //(a * c + b * d)/(c^2 + d^2)
        ret._real = (a._real * b._real + a._imag * b._imag) / (b._real * b._real + b._imag * b._imag);
        //(-a * d + b * c)/(c^2 + d^2) = (b * c - a * d)/(c^2 + d^2)
        ret._imag = (a._imag * b._real - a._real * b._imag) / (b._real * b._real + b._imag * b._imag);

        return ret;
    }

    //Para imprimir conforme as especificacoes da hierarquia, chama-se a funcao Print()
    friend std::ostream& operator<<(std::ostream &out, const C &a)
    {
        out << a.Print();
        return out;
    }

    //Escreve "_real + _imagi"
    virtual std::string Print() const
    {
        return std::to_string(this->_real) + " + " + std::to_string(this->_imag) + "i";
    }
};

class R : public C
{
public:
    //Construtor de R dado um double
    R(double real = 0) : C(real, 0) {};

    //Construtor de R dado um C, para converter o retorno das operacoes
    R(const C& val) : C(val.real(), 0) {};

    //Escreve "_real"
    virtual std::string Print() const
    {
        return std::to_string(this->real());
    }
};

class Q : public R
{
private:
    //Para salvar o numerador e o denominador
    long long int _numerador, _denominador;

    //Para calcular o maior divisor comum entre dois numeros
    static long long int mdc(long long int a, long long int b)
    {
        //https://www.geeksforgeeks.org/gcd-in-cpp/

        //Se a = 0, entao o maior divisor comum eh o valor de b
        if (a == 0)
            return b;
        //Se b = 0, entao o maior divisor comum eh o valor de a
        if (b == 0)
            return a;

        //Se a eh menor do que b
        if (a < b)
            //Calcula novamente utilizando o valor de a e o resto de b/a
            return mdc(a, b % a);
        //Se b é menor do que a
        else
            //Calcula novamente utilizando o valor de b e o resto de a/b
            return mdc(b, a % b);
    }

    void reduz()
    {
        //Se o numerador é 0, o denominador deve ser 1
        if(this->_numerador == 0)
        {
            this->_numerador = 0;
            this->_denominador = 1;
            return;
        }

        //Se o denominador estiver negtaivo
        if(this->_denominador < 0)
        {
            //Multiplica em cima e em baixo por -1
            this->_denominador *= -1;
            this->_numerador *= -1;
        }

        //Calcula o maior divisor comum entre o numerador e o denominador
        long long int aux;

        //Para o algoritmo funcionar, ambos os valores devem ser positivos
        if(this->_numerador < 0)
            aux = mdc(-this->_numerador, this->_denominador);
        else
            aux = mdc(this->_numerador, this->_denominador);

        //Reduz a fracao
        this->_denominador = this->_denominador / aux;
        this->_numerador = this->_numerador / aux;
    }

public:
    //Construtor de Q usando um numerador e um denominador
    Q(int numerador = 0, int denominador = 1) : R((double)(numerador) / (double)(denominador))
    {
        //Define o numerador e o denominador, sem reduzi-los
        this->_numerador = numerador;
        this->_denominador = denominador;
    }

    //Construtor de Q dado um C, para o retorno das operacoes
    Q(const C& val) : R(val.real())
    {
        //Multiplica o numerador por 1e10 para lvar em conta multiplas casas decimais
        this->_numerador = val.real() * 1e10;
        this->_denominador = 1e10;

        //Reduz a fracao
        this->reduz();
    };

    //Escreve "numerador/denominador"
    virtual std::string Print() const
    {
        return std::to_string(this->_numerador) + "/" + std::to_string(this->_denominador);
    }
};

class Z : public Q
{
public:
    //Construtor de Z usando um inteiro
    Z(int real = 0) : Q(real, 1) {};

    //Construtor de Z dado um C, para o retorno das operacoes
    Z(const C& val) : Q((int)val.real(), 1) {};

    //Escreve "{sinal do inteiro}_real"
    virtual std::string Print() const
    {
        if(this->real() < 0)
            return std::to_string((int)this->real());
        else
            return "+" + std::to_string((int)this->real());
    }
};

class N : public Z
{
public:
    //Construtor de N usando um inteiro
    N(int real = 0) : Z(real)
    {
        //Se for negativo
        if(this->real() < 0)
            //Chama o construtor novamente, agora comm o valor 0
            new (this) N(0);
    }

    //Construtor de N dado um C, para o retorno das operacoes
    N(const C& val) : Z((int)val.real())
    {
        //Se _real for negativo
        if(this->real() < 0)
            //Chama o construtor, agora com o valor 0
            new (this) N(0);
    }

    //Escreve "_real"
    std::string Print() const
    {
        return std::to_string((int)this->real());
    }
};
