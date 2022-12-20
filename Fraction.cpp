//
// Created by Illea on 10.12.2022.
//

#include "Fraction.h"

Fraction::Fraction(int numer,int denom)
{
    if (denom == 0) throw "division by zero!";
    numerator=numer;
    denominator=denom;
}

Fraction::Fraction(const Fraction& source)
{
    this->numerator=source.numerator;
    this->denominator=source.denominator;
}
std::ostream& operator<<(std::ostream& os, Fraction& fraction)
{
    os<<fraction.numerator<<" / "<<fraction.denominator;
    return os;
}
std::istream& operator>>(std::istream& is, Fraction& fraction)
{
    std::cout<<"numerator---> "<<std::ends; is>>fraction.numerator;
    std::cout<<"denominator---> "<<std::ends; is>>fraction.denominator;
    if (fraction.denominator==0)
    {
        fraction.denominator=1;
        std::cout<<" denominator = 1"<<std::endl;
    }
    return is;
}
bool operator==(const Fraction& f1,Fraction& f2)
{
    return f1.numerator==f2.numerator && f1.denominator==f2.denominator;
}
bool operator!=(const Fraction& f1,Fraction& f2)
{
    return f1.numerator!=f2.numerator && f1.denominator!=f2.denominator;
}

bool operator>(const Fraction& f1,Fraction& f2)
{
    if (f1.denominator == f2.denominator) return f1.numerator>f2.numerator;
    if (f1.numerator == f2.numerator) return f1.denominator<f2.denominator;
    int num1 = f1.numerator*f2.denominator;
    int num2 = f2.numerator*f1.denominator;
    return num1>num2;
}
bool operator>=(const Fraction& f1,Fraction& f2)
{
    if (f1.denominator == f2.denominator) return f1.numerator>=f2.numerator;
    if (f1.numerator == f2.numerator) return f1.denominator<=f2.denominator;

    int num1 = f1.numerator*f2.denominator;
    int num2 = f2.numerator*f1.denominator;
    return num1>=num2;
}

bool operator<=(const Fraction& f1,Fraction& f2)
{
    if (f1.denominator == f2.denominator) return f1.numerator<=f2.numerator;
    if (f1.numerator == f2.numerator) return f1.denominator>=f2.denominator;

    int num1 = f1.numerator*f2.denominator;
    int num2 = f2.numerator*f1.denominator;
    return num1<=num2;
}
bool operator<(const Fraction& f1,Fraction& f2)
{
    if (f1.denominator == f2.denominator) return f1.numerator<f2.numerator;
    if (f1.numerator == f2.numerator) return f1.denominator>f2.denominator;

    int num1 = f1.numerator*f2.denominator;
    int num2 = f2.numerator*f1.denominator;
    return num1<num2;
}