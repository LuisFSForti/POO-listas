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

        //Calcula quantas partes sao necessarias
        this->_npartes = tam / 9;
        //Calcula quantos numeros nao couberam na divisao por 9
        int deslc = tam % 9;
        //Verifica se houveram numeros que nao couberam, necessario para operacoes futuras
        bool aux = deslc > 0;

        //Se todos os numeros couberam
        if(!aux)
        {
            //Aloca o espaco necessario
            this->_partes = (int*)calloc(this->_npartes, sizeof(int));
        }
        //Se tiveram numeros que nao couberam
        else
        {
            //Define que precisa de mais uma parte
            this->_npartes++;
            //Aloca o espaco necessario
            this->_partes = (int*)calloc(this->_npartes, sizeof(int));

            //Salva os numeros que nao couberam no primeiro espaco
            this->_partes[0] = std::stoi(numero.substr(1 - this->_positivo, deslc));
        }

        //Para cada parte
        //int i = aux ->
            //se nao tiveram numeros que nao couberam, i = 0
            //se tiveram numeros que nao couberam, i = 1
        for(int i = aux; i < this->_npartes; i++)
            //1 - this->_positivo
                //Se for positivo, 1 - this->_positivo = 0
                //Se for negativo, 1 - this->_positivo = 1
                    //Assim ele sempre fica uma casa para frente, para ignorar o sinal de '-' da string
            // + delc -> para ignorar os numeros que nao couberam e ja foram salvos
            // + (i - aux) * 9 ->
                //se aux = true (ou seja, houveram numeros que nao couberam)
                    //i - aux = i - 1, pois ele vai estar salvando sempre um espaco a frente do referencial na string
                        //ex: 1234567891234567891234567891234567891
                        //_partes[0] = 1, salvo anteriormente
                        //_partes[1] = 234567891, que comeca na posicao (1 - 1 + 1 + (1 - 1) * 9) = 1
                        //_partes[2] = 234567891, que comeca na posicao (1 - 1 + 1 + (2 - 1) * 9) = 10
                        //e assim em diante
            this->_partes[i] = std::stoi(numero.substr(1 - this->_positivo + deslc + (i - aux) * 9, 9));


        //Para conferir se o numero eh 0
        for(int i = 0; i < this->_npartes; i++)
        {
            //Se alguma parte nao for 0, sai do construtor
            if(this->_partes[i] != 0)
                return;
        }
        //Se todas as partes forem 0, entao o numero eh positivo
        this->_positivo = true;
    }

    //Construtor com um inteiro e um booleano
    BigInt(int num = 0, bool eh_num = true)
    {
        //Se for um numero
        if(eh_num)
        {
            //Chama o construtor da string, usando o numero passado como string
            new (this) BigInt(std::to_string(num));
        }
        //Se nao for um numero
        else
        {
            //Define que eh positivo
            this->_positivo = true;
            //Define que a quantidade de partes eh o numero passado
            this->_npartes = num;
            //Aloca o espaco necessario apenas com numeros 0
            this->_partes = (int*)calloc(this->_npartes, sizeof(int));
        }
    }

    BigInt(BigInt&& b)
    {
        //Move os dados
        this->_positivo = std::move(b._positivo);
        this->_npartes = std::move(b._npartes);

        //Se tiver um endereco para _partes
        if(b._partes != nullptr)
        {
            //Passa o endereco
            this->_partes = b._partes;
            //Remove a conexao com o endereco
            b._partes = nullptr;
        }
    }

    ~BigInt()
    {
        delete this->_partes;
    }

    //Para checar se eh positivo
    //foi necessario definir como const para poder ser usado nas operacoes
    bool positivo() const
    {
        return this->_positivo;
    }

    BigInt& operator=(const BigInt& b)
    {
        this->_positivo = b._positivo;
        this->_npartes = b._npartes;

        //Se a instancia atual ja tiver um ponteiro para _partes
        if(this->_partes != nullptr)
            //Libera o ponteiro
            delete this->_partes;

        //Aloca o espaco novo
        this->_partes = (int*)malloc(this->_npartes * sizeof(int));
        //Copia os dados
        std::copy(b._partes, b._partes + this->_npartes, this->_partes);

        return *this;
    }

    //Para pegar o modulo do numero
    //foi necessario definir como const para poder ser usado nas operacoes
    BigInt abs() const
    {
        BigInt aux;
        aux = *this;
        aux._positivo = true;
        return aux;
    }

    friend bool operator==(const BigInt& a, const BigInt& b)
    {
        //Se forem o mesmo endereco, portanto a mesma isntancia
        if(&a == &b)
            return true;

        //Se os sinais forem diferentes
        if(a._positivo != b._positivo)
            return false;

        //Se algum deles nao tiver o ponteiro para _partes
        if(a._partes == nullptr || b._partes == nullptr)
            return false;

        //Para comparar todo o numero de ambos
        int menor = 0, diff1 = 0, diff2 = 0;
        //Se a for mais comprido que b
        if(a._npartes > b._npartes)
        {
            //Define o tamanho do menor e a diferenca entre os dois
            menor = b._npartes;
            diff1 = a._npartes - b._npartes;

            //Compara as partes extras de a
            for(int i = 0; i < diff1; i++)
            {
                //Se alguma for diferente de 0, retorna falso
                if(a._partes[i] != 0)
                    return false;
            }
        }
        //Se b for mais comprido que a
        else
        {
            //Define o tamanho do menor e a difrence entre os dois
            menor = a._npartes;
            diff2 = b._npartes - a._npartes;
            //Compara as partes extras de b
            for(int i = 0; i < diff2; i++)
            {
                //Se alguma for diferente de 0, retorna falso
                if(b._partes[i] != 0)
                    return false;
            }
        }

        //Compara as partes de ambos
        for(int i = 0; i < menor; i++)
        {
            //Se alguma for diferente, retorna falso
            if(a._partes[i + diff1] != b._partes[i + diff2])
                return false;
        }

        //Se nenhuma comparacao invalidou, entao retorna verdadeiro
        return true;
    }

    friend bool operator>(const BigInt& a, const BigInt& b)
    {
        //Se a for positivo e b negativo
        if(a._positivo && !b._positivo)
            //a > b
            return true;

        //Se a for negativo e b positivo
        if(!a._positivo && b._positivo)
            //a < b
            return false;

        //Se ambos sao positivos
            //a e b positivos -> true
            //a e b negativos -> false
            //a e b diferentes -> codigo nao chega aqui
        bool saoPositivos = (a._positivo && b._positivo);

        //Para comparar todo o numero de ambos
        int diff1 = 0, diff2 = 0, menorTam = 0;
        //Se b for mais comprido que a
        if(a._npartes < b._npartes)
        {
            //Define o tamanho do menor e a diferenca de ambos
            menorTam = a._npartes;
            diff2 = b._npartes - a._npartes;
            //Para cada parte extra de b
            for(int i = 0; i < diff2; i++)
            {
                //Se for diferente de 0
                if(b._partes[i] > 0)
                    //Se a e b negativos (saoPositivos == false), a > b
                    //Se a e b positivos (saoPositivos == true), a < b
                    return !saoPositivos;
            }
        }
        //Se a for mais comprido que b
        else
        {
            //Define o tamanho do menor e a diferenca de ambos
            menorTam = b._npartes;
            diff1 = a._npartes - b._npartes;
            //Para cada aprte extra de a
            for(int i = 0; i < diff1; i++)
            {
                //Se for diferente de 0
                if(a._partes[i] > 0)
                    //Se a e b negativos (saoPositivos == false), a < b
                    //Se a e b positivos (saoPositivos == true), a > b
                    return saoPositivos;
            }
        }

        //Compara as partes de ambos
        for(int i = 0; i < menorTam; i++)
        {
            //Se a[i] < b[i]
            if(a._partes[i + diff1] < b._partes[i + diff2])
                //Se a e b negativos (saoPositivos == false), a > b
                //Se a e b positivos (saoPositivos == true), a < b
                return !saoPositivos;

            //Se a[i] > b[i]
            if(a._partes[i + diff1] > b._partes[i + diff2])
                //Se a e b negativos (saoPositivos == false), a < b
                //Se a e b positivos (saoPositivos == true), a > b
                return saoPositivos;
        }

        //Se nenhuma comparacao foi dada, entao a == b
        return false;
    }

    friend BigInt operator+(const BigInt& a, const BigInt& b)
    {
        //Se tiverem o mesmo modulo
        if(a.abs() == b.abs())
        {
            //Se tiiverem sinais opostos
            if(a._positivo != b._positivo)
                //a + b = 0
                return BigInt();
        }

        //Para realizar as operacoes
        int neg1 = 1, neg2 = 1, menor = 0, diff1 = 0, diff2 = 0;
        BigInt aux;


        if(!a._positivo)
            neg1 = -1;
        if(!b._positivo)
            neg2 = -1;

        //Se a for mais comprido que b
        if(a._npartes > b._npartes)
        {
            //Instancia aux com partes o suficiente para somar, todas sendo 0
            aux = BigInt(a._npartes + 1, false);

            //Define o menor e a diferenca entre eles
            menor = b._npartes;
            diff1 = a._npartes - b._npartes;

            //Para cada parte extra
            for(int i = 0; i < diff1; i++)
                //Salva o valor dela, levando em conta o sinal de a
                aux._partes[i + 1] = neg1 * a._partes[i];
        }
        //Se b for mais comprido que a
        else
        {
            //Instancia aux com partes o suficiente para somar, todas sendo 0
            aux = BigInt(b._npartes + 1, false);

            //Define o menor e a diferenca entre eles
            menor = a._npartes;
            diff2 = b._npartes - a._npartes;

            //Para cada parte extra
            for(int i = 0; i < diff2; i++)
                //Salva o valor dela, levando em conta o sinal de b
                aux._partes[i + 1] = neg2 * b._partes[i];
        }

        //Para o restante das partes
        for(int i = 0; i < menor; i++)
        {
            //Como a._partes[i] <= 999999999 e b._partes[i] tambem, entao nao eh necessario lidar com overflow ateh o fim do loop
            //Soma os valores, levando em conta os sinais
            aux._partes[i + diff1 + diff2 + 1] = neg1 * a._partes[i + diff1] + neg2 * b._partes[i + diff2];
        }

        //===================================Organizar=============================
        //Se o modulo de a for maior que o de b
        if(a.abs() > b.abs())
            //O sinal sera o mesmo que o de a
            aux._positivo = a._positivo;
        //Se o modulo de b for maior que o de a
        else
            //O sinal sera o mesmo que o de b
            aux._positivo = b._positivo;

        //Para fazer as operacoes
        int negAux = 1;
        if(!aux._positivo)
            negAux = -1;

        //Para cada casa, indo da direita pra esquerda
        for(int i = aux._npartes - 1; i > 0; i--)
        {
            //Multiplica pelo sinal de aux
            aux._partes[i] *= negAux;

            //Se a parte for menor que 0
            if(aux._partes[i] < 0)
            {
                //Aumenta em 1000000000
                aux._partes[i] += 1000000000;
                //Remove um valor da proxima parte, levando em conta o sinal
                aux._partes[i-1] -= negAux;
            }
            //Se a parte for maior que 1000000000
            if(aux._partes[i] >= 1000000000)
            {
                //Diminui em 1000000000
                aux._partes[i] -= 1000000000;
                //Aumenta um valor da proxima parte, levando em conta o sinal
                aux._partes[i-1] += negAux;
            }
        }
        //Corrige o valor da primeira casa, que nao eh avaliada no loop
        aux._partes[0] *= negAux;

        //Calcula quantas partes na esquerda sao 0
        int diff = 0;
        for(int i = 0; aux._partes[i] == 0; i++)
            diff++;

        //Cria um novo BigInt com a quantidade de espacos realmente necessaria
        BigInt ret(aux._npartes - diff, false);

        //Define o sinal
        ret._positivo = aux._positivo;
        //Copia todas as casas diferente de 0, reduzindo o tamanho do BigInt
        for(int i = 0; i < ret._npartes; i++)
            ret._partes[i] = aux._partes[i + diff];

        //Retorna o resultado reduzido
        return ret;
    }

    friend BigInt operator-(const BigInt& a, const BigInt& b)
    {
        //Para fazer a subtracao, basta somar com o oposto de b
        return a + (-b);
    }

    BigInt operator-() const
    {
        //Basta copiar o BigInt e retornar a copia com o _positivo oposto
        BigInt ret;
        ret = *this;
        ret._positivo = !ret._positivo;
        return ret;
    }

    friend BigInt operator*(const BigInt& a, const BigInt& b)
    {
        //Se a ou b == 0, retorna 0
        if(a == BigInt() || b == BigInt())
            return BigInt();

        //Para realizar as operacoes
        int neg1 = 1, neg2 = 1, negAux = 1;
        BigInt aux;

        if(!a._positivo)
            neg1 = -1;
        if(!b._positivo)
            neg2 = -1;

        //Cria um BigInt com espaco o suficiente para multiplicar
        aux = BigInt(a._npartes + b._npartes, false);

        //Se os sinais forem diferentes, aux eh negativo, senao eh positivo
        aux._positivo = a._positivo == b._positivo;
        if(!aux._positivo)
            negAux = -1;

        //Para cada valor de b
        for(int i = b._npartes-1; i >= 0; i--)
        {
            //Se for 0, pula
            if(b._partes[i] == 0)
                continue;

            //Para cada valor de a
            for(int j = a._npartes-1; j >= 0; j--)
            {
                //Soma o valor salvo em aux e o produto de a._partes[j] e b._partes[i], levando em contaa os sinais de a e b
                long long int soma = (long long int)(aux._partes[i + j + 1]) + (long long int)(neg1 * a._partes[j]) * (long long int)(neg2 * b._partes[i]);

                //Arruma o sinal, de acordo com o sinal de aux
                soma *= negAux;
                //Se soma for menor que 0
                if(soma < 0)
                {
                    //Remove valores o suficiente da proxima parte para corrigir, levando em conta o sinal
                    aux._partes[i + j] -= negAux * (soma / -1000000000 + 1);
                    //Corrige o valor de soma
                    soma %= 1000000000;
                    soma += 1000000000;
                }
                //Se soma for maior que 1000000000
                if(soma >= 1000000000)
                {
                    //Adiciona valores o suficiente da proximia parte para corrigir, levando em conta o sinal
                    aux._partes[i + j] += negAux * soma / 1000000000;
                    //Corrige o valor de soma
                    soma %= 1000000000;
                }
                //Salva o valor em aux, levando em conta o sinal
                aux._partes[i + j + 1] = negAux * soma;
            }
        }

        //========================= Organizar vetor =========================//
        //Como os valores foram corrigidos durante a multiplicacao, basta corrigir os seus sinais
        for(int i = aux._npartes - 1; i >= 0; i--)
            aux._partes[i] *= negAux;

        //Calcula quantas partes na esquerda sao 0
        int diff = 0;
        for(int i = 0; aux._partes[i] == 0; i++)
            diff++;

        //Cria um novo BigInt com a quantidade de espacos realmente necessaria
        BigInt ret(aux._npartes - diff, false);

        //Define o sinal
        ret._positivo = aux._positivo;
        //Copia todas as casas diferente de 0, reduzindo o tamanho do BigInt
        for(int i = 0; i < ret._npartes; i++)
            ret._partes[i] = aux._partes[i + diff];

        //Retorna o resultado reduzido
        return ret;
    }

    BigInt operator/(int b) const
    {
        //Se b == 0, divisao impossivel, retorna 0 por padrao
        if(b == 0)
            return BigInt();
        //Se b > *this, retorna 0
        if(BigInt(b).abs() > this->abs())
            return BigInt();
        //Se *this == 0, retorna 0
        if(*this == BigInt())
            return BigInt();

        //Cria um BigInt para salvar o resultado
        BigInt aux(this->_npartes, false);

        //Se o dividendo for negativo
        if(!this->_positivo)
            //Multiplica o divisor por -1
            b *= -1;
        //Se o diviisor for negativo
        if(b < 0)
        {
            //O quociente sera negativo
            aux._positivo = false;
            //Deixa o divisor positivo para nao afetar as operacoes
            b *= -1;
        }

        //Pega o valor da primeira parte
        long long int resto = this->_partes[0];
        //Para cada parte
        for(int i = 0; i < this->_npartes - 1; i++)
        {
            //Salva o quociente do resto sobre o divisor
            aux._partes[i] = resto / b;
            //Recalcula o resto, levando em conta que o antigo resto eh 1000000000 vezes maior que o novo
            resto = (resto % b) * 1000000000 + this->_partes[i+1];
        }
        //Calcula o quociente da ultima parte, pois nao coube no loop
        aux._partes[aux._npartes-1] = resto / b;

        //========================= Organizar vetor =========================//
        //Calcula quantas partes na esquerda sao 0
        int diff = 0;
        for(int i = 0; aux._partes[i] == 0; i++)
            diff++;

        //Cria um novo BigInt com a quantidade de espacos realmente necessaria
        BigInt ret(aux._npartes - diff, false);

        //Define o sinal
        ret._positivo = aux._positivo;
        //Copia todas as casas diferente de 0, reduzindo o tamanho do BigInt
        for(int i = 0; i < ret._npartes; i++)
            ret._partes[i] = aux._partes[i + diff];

        //Retorna o resultado reduzido
        return ret;
    }

    friend BigInt operator^(const BigInt& a, const BigInt& b)
    {
        //https://www.geeksforgeeks.org/write-a-c-program-to-calculate-powxn/

        //Verifica se a base eh 0
        if(a == BigInt())
            //Se sim, retorna 0
            return BigInt();

        //Verifica se o expoente eh 0
        if(b == BigInt())
            //Se sim, retorna 1
            return BigInt(1);

        //Temporario que salva o valor da base elevado ao expoente/2
            //Assim inicia-se uma recursao, diminuindo a complexidade para O(log(x)), x sendo o comprimento de a._partes
        BigInt temp;
        temp = a ^ (b/2);

        //Se o expoente for par
        if(b._partes[b._npartes - 1] % 2 == 0)
            //Retorna o quadrado de temp
            return temp * temp;
        //Se o expoente for impar
        else
            //Retorna o quadrado de temp * a, pois a divisao de um inteiro impar por 2 perde 1 em c++
            return a * temp * temp;
    }

    friend std::ostream& operator<<(std::ostream &out, const BigInt &a)
    {
        //Se nao tiver ponteiro, retorna
        if(a._partes == nullptr)
            return out;

        //Se for negativo, adiciona o sinal de '-'
        if(!a._positivo)
            out << "-";

        //Para pular todas as partes na esquerda igual a 0, exceto a ultima
        int i = 0;
        while(a._partes[i] == 0 && i < a._npartes - 1)
            i++;

        //Para manipular os numeros
        std::string aux;
        bool primeiro = true;
        //Para cada aprte
        for(; i < a._npartes; i++)
        {
            //Salva o valor da parte
            aux = std::to_string(a._partes[i]);

            //Se nao for o primeiro numero escrito
            if(!primeiro)
                //Adiciona zeros o suficiente para terem 9 caracteres
                aux.insert(0, 9 - aux.length(), '0');
            //Se for o primeiro numero escrito
            else
                //Salva que ele ja foi escrito
                primeiro = false;

            //Adiciona o numero manipulado
            out << aux;
        }

        //Retorna a saida
        return out;
    }
};
