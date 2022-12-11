//
// Created by Illea on 10.12.2022.
//

#ifndef CURSEWORK_1_FRACTION_H
#define CURSEWORK_1_FRACTION_H

#include <iostream>

class Fraction {
    int numerator;
    int denominator;
public:
    explicit Fraction(int numer=0,int denom=1);
    Fraction(const Fraction& source);
    friend std::ostream& operator<<(std::ostream&, Fraction&);
    friend std::istream& operator>>(std::istream&, Fraction&);
    friend bool operator==(const Fraction&,Fraction&);
    friend bool operator!=(const Fraction&,Fraction&);
    friend bool operator>(const Fraction&,Fraction&);
    friend bool operator>=(const Fraction& f1,Fraction& f2);
    friend bool operator<(const Fraction& f1,Fraction& f2);
    friend bool operator<=(const Fraction& f1,Fraction& f2);

};


#endif //CURSEWORK_1_FRACTION_H
