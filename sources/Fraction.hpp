#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>

namespace ariel
{
    class Fraction
    {
        int numerator;
        int denominator;

    public:
        Fraction(int num1, int num2);
        Fraction(float num1);
        Fraction();

        int getNumerator();
        int getDenominator();
        void set(int numerator, int denominator);

        Fraction operator+(const Fraction &other) const;
        Fraction operator-(const Fraction &other) const;
        Fraction operator*(const Fraction &other) const;
        Fraction operator/(const Fraction &other) const;

        bool operator==(const Fraction &other) const;
        bool operator!=(const Fraction &other) const;
        bool operator<(const Fraction &other) const;
        bool operator<=(const Fraction &other) const;
        bool operator>(const Fraction &other) const;
        bool operator>=(const Fraction &other) const;

        Fraction &operator++();   // ++C
        Fraction operator++(int); // c++
        Fraction &operator--();   // --c
        Fraction operator--(int); // c--

        friend std::ostream &operator<<(std::ostream &oos, const Fraction &fract);
        friend std::istream &operator>>(std::istream &iis, Fraction &fract);

        friend bool operator==(const float &fract, const Fraction &other);
        friend bool operator!=(const float &fract, const Fraction &other);
        friend bool operator<(const float &fract, const Fraction &other);
        friend bool operator<=(const float &fract, const Fraction &other);
        friend bool operator>(const float &fract, const Fraction &other);
        friend bool operator>=(const float &fract, const Fraction &other);

        friend Fraction operator+(const float &fract, const Fraction &other);
        friend Fraction operator-(const float &fract, const Fraction &other);
        friend Fraction operator*(const float &fract, const Fraction &other);
        friend Fraction operator/(const float &fract, const Fraction &other);

    private:
        int gcd(int numerator, int denominator);
        void reduction();


    };
};

#endif