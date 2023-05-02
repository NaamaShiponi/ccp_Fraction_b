#include <iostream>
#include <string.h>
#include <math.h>
#include <algorithm> // For __gcd; taken from the internet

#include "Fraction.hpp"

using namespace std;
using namespace ariel;

Fraction::Fraction():numerator(1),denominator(0){};


Fraction::Fraction(int num1,int num2):numerator(num1),denominator(num2){
    if (denominator == 0) {// denominator cannot be zero, throw an error if it is
        throw invalid_argument("0");
    }
    if (num1 == 0) num2=1; // if numerator is zero, denominator should be set to one

    if((num2<0 && num1<0) || (num2<0 && num1>0)){// if numerator and denominator have different signs, flip signs of both
        num2=num2*(-1);
        num1=num1*(-1);
    }
    numerator=num1;        
    denominator=num2;
    reduction();
}

Fraction::Fraction(float num1){
    if(num1==0){
        numerator=0;        
        denominator=1;
    }else{
        int sign=1;
        if(num1 < 0) sign= -1;
        numerator = abs(num1) * 1000 * sign;// calculate numerator by taking absolute value of input, multiplying by 1000, and multiplying by sign
        denominator = 1000;   // denominator is set to 1000
    }
    reduction();


}

int Fraction::getNumerator(){
    return numerator;
}

int Fraction::getDenominator(){
    return denominator;
}

void Fraction::reduction(){// function to reduce fraction to simplest form
    int positivNumer=numerator,positivDenom=denominator;
    if(numerator<0){// if numerator is negative, make it positive
        positivNumer=positivNumer*(-1);
    }
    if(denominator<0 ){// if numerator is negative, make it positive
        positivDenom=positivDenom*(-1);
    }
    int gcdNum = gcd(positivNumer,positivDenom);// get greatest common divisor of numerator and denominator

    numerator=numerator/gcdNum;
    denominator=denominator/gcdNum;

}

int Fraction::gcd(int numerator, int denominator) {// function to get greatest common divisor of two integers using recursion
    if (numerator == 0) {
        return denominator;
    }
    return gcd(denominator % numerator, numerator);
}



void Fraction::set(int numerator, int denominator){
    this->numerator=numerator;
    this->denominator=denominator;
}


Fraction Fraction::operator+(const Fraction& other) const{
    int max_int = std::numeric_limits<int>::max();
    int min_int = std::numeric_limits<int>::min();
    
    long num = (long)numerator * other.denominator + other.numerator * denominator;
    long den = (long)denominator * other.denominator;

    if(num>max_int || num<min_int || den>max_int || den<min_int){// Check for integer overflow
        throw std::overflow_error("long");
    }

    return Fraction(num, den);
    
}
Fraction Fraction::operator-(const Fraction& other) const{
    int max_int = std::numeric_limits<int>::max();
    int min_int = std::numeric_limits<int>::min();
    
    long num = (long)numerator * other.denominator - other.numerator * denominator;
    long den = (long)denominator * other.denominator;

    if(num>max_int || num<min_int || den>max_int || den<min_int){// Check for integer overflow
        throw std::overflow_error("long");
    }

    return Fraction(num, den);
}
Fraction Fraction::operator*(const Fraction& other) const{
    int max_int = std::numeric_limits<int>::max();
    int min_int = std::numeric_limits<int>::min();
    long num = (long)numerator * other.numerator;
    long den = (long)denominator * other.denominator;

    if(num>max_int || num<min_int || den>max_int || den<min_int){// Check for integer overflow

        throw std::overflow_error("long");
    }

    return Fraction(num, den);
    
}

Fraction Fraction::operator/(const Fraction& other) const{
    int max_int = std::numeric_limits<int>::max();
    int min_int = std::numeric_limits<int>::min();
    if(other.numerator==0){ // Check for division by zero
        throw std::runtime_error("division by zero");    
    }

    long num = (long)numerator * other.denominator;
    long den = (long)denominator * other.numerator;

    if(num>max_int || num<min_int || den>max_int || den<min_int){// Check for integer overflow

        throw std::overflow_error("long");
    }

    return Fraction(num, den);
}

// Implementation of the equality comparison operator
bool Fraction::operator==(const Fraction& other) const {
    float number1 = (float)this->numerator/this->denominator;
    float number2 = (float)other.numerator/other.denominator;
    return abs(number1 - number2)<0.001;
}

bool Fraction::operator!=(const Fraction& other) const {
    return !(*this == other);
}
bool Fraction::operator<(const Fraction& other) const {
    return !(*this > other) && !(*this == other);
}
bool Fraction::operator<=(const Fraction& other) const {
    return (*this < other) || (*this == other);
}

bool Fraction::operator>(const Fraction& other) const {
    if ((numerator > 0) && (other.numerator < 0)) return true;
    if((numerator < 0) && (other.numerator > 0)) return false;
    if((numerator < 0) && (other.numerator < 0)) return (numerator * other.denominator > other.numerator * denominator);
    return numerator * other.denominator > other.numerator * denominator;
}

bool Fraction::operator>=(const Fraction& other) const {
    return (*this > other) || (*this == other);
}



Fraction& Fraction::operator++(){
    numerator += denominator;
    reduction();
    return *this;
}
Fraction Fraction::operator++(int){
    Fraction temp = *this;
    numerator += denominator;
    reduction();
    return temp;
}
Fraction& Fraction::operator--(){
    numerator -= denominator;
    reduction();
    return *this;
}
Fraction Fraction::operator--(int){
    Fraction temp = *this;
    numerator -= denominator;
    reduction();
    return temp;
}


std::ostream& ariel::operator<<(std::ostream& oos, const Fraction& fract) {
    oos << fract.numerator << "/" << fract.denominator;
    return oos;
}


std::istream& ariel::operator>>(std::istream& iis, Fraction& fraction){
        int numer, denom;
        iis >> numer; // Read the numerator from the input stream

        // Check if there is a decimal point after the numerator
        if (iis.peek() == '.')
            throw std::runtime_error("Invalid input.");

        // Ignore the decimal point
        iis.ignore(1); 

        iis >> denom;  // Read the denominator from the input stream

        if (denom == 0)     // Check if the denominator is zero
            throw std::runtime_error("divideing by 0!");

        if((denom<0 && numer<0) || (denom<0 && numer>0)){   // If the fraction is negative, make the denominator positive and the numerator negative
            denom=denom*(-1);
            numer=numer*(-1);
        }
        fraction.numerator=numer;
        fraction.denominator = denom;
        fraction.reduction();

        // Check if there was an error reading the input
        if (iis.fail())
            throw std::runtime_error("Invalid input.");

        return iis;
}



bool ariel::operator==(const float& fract, const Fraction& other) {
    Fraction newFract(fract);
    return newFract==other;

}
bool ariel::operator!=(const float& fract, const Fraction& other) {
    Fraction newFract(fract);
    return newFract!=other;
}
bool ariel::operator<(const float& fract, const Fraction& other) {
    Fraction newFract(fract);
    return newFract<other;
}
bool ariel::operator<=(const float& fract, const Fraction& other) {
    Fraction newFract(fract);
    return newFract<=other;
}
bool ariel::operator>(const float& fract, const Fraction& other) {
    Fraction newFract(fract);
    return newFract>other;
}
bool ariel::operator>=(const float& fract, const Fraction& other) {
    Fraction newFract(fract);
    return newFract>=other;
}



Fraction ariel::operator+(const float& fract, const Fraction& other)  { 
    Fraction newFract(fract);
    newFract=newFract+other;
    return newFract;
}
Fraction ariel::operator-(const float& fract, const Fraction& other)  { 
    Fraction newFract(fract);
    newFract=newFract-other;
    return newFract;
}
Fraction ariel::operator*(const float& fract, const Fraction& other)  {
    Fraction newFract(fract);
    newFract=newFract*other;
    return newFract;
}
Fraction ariel::operator/(const float& fract, const Fraction& other)  {
    Fraction newFract(fract);
    newFract=newFract/other;
    return newFract;

}








