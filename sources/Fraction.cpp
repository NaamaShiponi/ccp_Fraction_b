#include <iostream>
#include <string.h>
#include <math.h>
#include <algorithm> // For __gcd; taken from the internet

#include "Fraction.hpp"

using namespace std;
using namespace ariel;

Fraction::Fraction():numerator(1),denominator(0){};


Fraction::Fraction(int num1,int num2):numerator(num1),denominator(num2){
    if (denominator == 0) {
        throw invalid_argument("0");
    }
    if (num1 == 0) num2=1;

    if((num2<0 && num1<0) || (num2<0 && num1>0)){
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
        numerator = abs(num1) * 1000 * sign;
        denominator = 1000;   
    }
    reduction();


}

int Fraction::getNumerator(){
    return numerator;
}

int Fraction::getDenominator(){
    return denominator;
}

void Fraction::reduction(){
    int positivNumer=numerator,positivDenom=denominator;
    if(numerator<0){
        positivNumer=positivNumer*(-1);
    }
    if(denominator<0 ){
        positivDenom=positivDenom*(-1);
    }
    int gcdNum = gcd(positivNumer,positivDenom);

    numerator=numerator/gcdNum;
    denominator=denominator/gcdNum;

}

int Fraction::gcd(int numerator, int denominator) {
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
    if(num>max_int || num<min_int || den>max_int || den<min_int){
        throw std::overflow_error("long");
    }
    return Fraction(num, den);
    
}
Fraction Fraction::operator-(const Fraction& other) const{
    int max_int = std::numeric_limits<int>::max();
    int min_int = std::numeric_limits<int>::min();
    
    long num = (long)numerator * other.denominator - other.numerator * denominator;
    long den = (long)denominator * other.denominator;
    if(num>max_int || num<min_int || den>max_int || den<min_int){
        throw std::overflow_error("long");
    }
    return Fraction(num, den);
}
Fraction Fraction::operator*(const Fraction& other) const{
    int max_int = std::numeric_limits<int>::max();
    int min_int = std::numeric_limits<int>::min();
    long num = (long)numerator * other.numerator;
    long den = (long)denominator * other.denominator;
    if(num>max_int || num<min_int || den>max_int || den<min_int){
        throw std::overflow_error("long");
    }
    return Fraction(num, den);
    
}

Fraction Fraction::operator/(const Fraction& other) const{
    int max_int = std::numeric_limits<int>::max();
    int min_int = std::numeric_limits<int>::min();
    if(other.numerator==0){
        throw std::runtime_error("division by zero");    
    }

    long num = (long)numerator * other.denominator;
    long den = (long)denominator * other.numerator;
    if(num>max_int || num<min_int || den>max_int || den<min_int){
        throw std::overflow_error("long");
    }
    return Fraction(num, den);
}


bool Fraction::operator==(const Fraction& other) const {
    float number1 = (float)this->numerator/this->denominator;
    float number2 = (float)other.numerator/other.denominator;
    return std::abs(number1 - number2)<0.001;
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
        iis >> numer;
        if (iis.peek() == '.')
            throw std::runtime_error("Invalid input.");

        iis.ignore(1); 

        iis >> denom;
        if (denom == 0)
            throw std::runtime_error("divideing by 0!");

        if((denom<0 && numer<0) || (denom<0 && numer>0)){
            denom=denom*(-1);
            numer=numer*(-1);
        }
        fraction.numerator=numer;
        fraction.denominator = denom;
        fraction.reduction();

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








