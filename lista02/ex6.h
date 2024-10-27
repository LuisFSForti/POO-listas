#ifndef EX6_H_INCLUDED
#define EX6_H_INCLUDED

#include <stdio.h>
#include <iostream>

class BigInt
{
private:
    int* _partes;
    int _npartes;
    bool _positivo;
public:
    BigInt(std::string numero);
    BigInt(int num = 0, bool eh_num = true);
    BigInt(BigInt&& b);
    ~BigInt();
    bool positivo();
    BigInt& operator=(const BigInt& b);
    BigInt abs() const;
    friend bool operator==(const BigInt& a, const BigInt& b);
    friend bool operator>(const BigInt& a, const BigInt& b);
    friend BigInt operator+(const BigInt& a, const BigInt& b);
    friend BigInt operator-(const BigInt& a, const BigInt& b);
    BigInt operator-() const;
    friend BigInt operator*(const BigInt& a, const BigInt& b);
    BigInt operator/(int b);
    friend BigInt operator^(const BigInt& a, const BigInt& b);
    friend std::ostream& operator<<(std::ostream &out, const BigInt &a);
};


#endif // EX6_H_INCLUDED
