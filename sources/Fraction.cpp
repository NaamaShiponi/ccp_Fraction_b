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
        throw invalid_argument("Denominator cannot be 0.");
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
    // cout << endl << "numerator " << numerator << "denominator" << denominator << endl ; 
    // cout <<  "gcd(positivNumer,positivDenom) (" <<positivNumer << positivDenom << ")" << " gcdNum "<< gcdNum << endl;

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
    int num = numerator * other.denominator + other.numerator * denominator;
    int den = denominator * other.denominator;
    return Fraction(num, den);
    
}
Fraction Fraction::operator-(const Fraction& other) const{
    int num = numerator * other.denominator - other.numerator * denominator;
    int den = denominator * other.denominator;
    return Fraction(num, den);
}
Fraction Fraction::operator*(const Fraction& other) const{
    int num = numerator * other.numerator;
    int den = denominator * other.denominator;
    return Fraction(num, den);
    
}
Fraction Fraction::operator/(const Fraction& other) const{
    if(numerator==0){
        throw invalid_argument("It is impossible to divide by 0.");
    }
    int num = numerator * other.denominator;
    int den = denominator * other.numerator;
    return Fraction(num, den);
}


bool Fraction::operator==(const Fraction& other) const {
    if(numerator==other.numerator && denominator==other.denominator){
        return true;
    }
    return false;
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



std::istream& ariel::operator>>(std::istream& iis, Fraction& fract) {
    int numerator, denominator;
    iis >> numerator >> denominator;
    fract = Fraction(numerator, denominator);
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








