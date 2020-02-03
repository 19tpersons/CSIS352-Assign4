#include "fraction.h"
#include <string>
#include <math.h>
#include <iostream>
#include <iomanip>

using namespace std;

fraction::fractionType fraction::outputType = fraction::mixed;

fraction::fraction() {
}

fraction::fraction(double number) {
  setFraction(number);
}

fraction::fraction(int numerator, int denominator) {
  setFraction(numerator, denominator);
}


void fraction::setFraction(int n, int d) {
  numerator = n;
  denominator = d;
  while (numerator > denominator) {
    wholeNumber += 1;
    numerator -= d;
  }

  reduce();
}

void fraction::setFraction(double number) {
  bool negative = false;
  if (number < 0) { //Needed because the calculations only work with positive numbers
    negative = true;
    number *= -1;
  }

  wholeNumber = floor(number);

  //Turns the decimal part of the entered number into a integer
  double decimal = fmod(number, 1);
  double numOfDecimals = 0;
  while (fmod(decimal, 1) > 0) {
    numOfDecimals++;
    decimal *= 10;
  }

  //sets numerator and denominator
  numerator = decimal;
  if (decimal == 0) {
    denominator = 1;
  } else {
    denominator = pow(10, numOfDecimals);
  }

  if (negative) {
    wholeNumber = wholeNumber * -1;
  }

  reduce();
}

void fraction::setDenominator(int number) {
  if (number == 0) {
    //TODO throw error
  } else {
    double divisor =  (double) number / denominator;
    if (numerator * divisor != (int)(numerator * divisor)) {
      cout << "The numerator has to be a whole number" << endl;
      return;
    }
    denominator *= divisor;
    numerator *= divisor;
  }
}

int fraction::getNumerator() {
  return numerator;
}

int fraction::getDenominator() {
  return denominator;
}

int fraction::getWholeNumber() {
  return wholeNumber;
}

double fraction::decimalValue() {
  double converted;
  if (wholeNumber < 0) {
    converted = wholeNumber +((numerator / (double) denominator) * -1);
  } else {
    converted =  wholeNumber + (numerator / (double) denominator);
  }

  return converted;
}


void fraction::outputFormat(fractionType newType) {
  fraction::outputType = newType;
}


//implementation of euclids algorithm
int fraction::gcd(int a, int b)
{
    if (a == 0)
        return b;
    return fraction::gcd(b % a, a);
}
void fraction::reduce() {
  int prevRemainder = gcd(numerator, denominator);

  numerator = numerator / prevRemainder;
  denominator = denominator / prevRemainder;
}

const fraction& fraction::operator=(const fraction& rightObject) {
  if (this != &rightObject) {
    //copies over the state
    numerator = rightObject.numerator;
    denominator = rightObject.denominator;
    wholeNumber = rightObject.wholeNumber;
  }

  return *this;
}

const fraction& fraction::operator=(double number) {
  setFraction(number);

  return *this;
}


ostream& operator<<(ostream& osObject, const fraction& fract) {
  //types
  if (fraction::outputType == fraction::improper) {
    if (fract.denominator == 1) { //TODO FIX!!!
      osObject << fract.wholeNumber + fract.numerator;
    } else {
      osObject << (fract.wholeNumber * fract.denominator + fract.numerator) << "/" << fract.denominator;
    }
  } else if (fraction::outputType == fraction::decimal) {
    osObject << fract.wholeNumber + ((double) fract.numerator / fract.denominator);
  } else {
    if (fract.wholeNumber == 0) {
      osObject << " " << fract.numerator << "/" << fract.denominator;
    } else if (fract.denominator == 1) { //TODO FIX!!!
      osObject << fract.wholeNumber + fract.numerator;
    } else {
      osObject << fract.wholeNumber << " " << fract.numerator << "/" << fract.denominator;
    }
  }

  return osObject;
}

istream& operator>>(istream& inStream, fraction& fract) {
  string n;
  string d;

  bool slash = false; //used to see if the string we are iterating over has reached the denominator
  string line;
  getline(inStream, line);
  for (int i = 0; i < line.length(); i++) {
    char tmp;
    tmp = line[i];

    if (!slash) {
      n = n + tmp;
    } else {
      d = d + tmp;
    }


    if (tmp == '/') {
      slash = true;
    }
  }
  fract.setFraction(stoi(n), stoi(d));

  return inStream;
}

bool fraction::operator==(const fraction& fract) const {
  return (wholeNumber == fract.wholeNumber && denominator == fract.denominator && numerator == fract.numerator);
}

bool fraction::operator==(int number) {
  return (number == wholeNumber);
}

bool fraction::operator<(int number) {
  return (number > decimalValue());
}


fraction fraction::operator+(const fraction& rightObject) const {
  fraction sum;

  sum.wholeNumber = rightObject.wholeNumber + wholeNumber;

  //calculates fraction part
  int tmpDenominator = denominator * rightObject.denominator;
  int tmpNumerator = numerator * rightObject.denominator + rightObject.numerator * denominator;

  sum.numerator = tmpNumerator;
  sum.denominator = tmpDenominator;
  fraction tmp(tmpNumerator, tmpDenominator);

  sum.numerator = tmp.getNumerator();
  sum.denominator = tmp.getDenominator();
  sum.wholeNumber += tmp.getWholeNumber();


  return sum;
}

fraction fraction::operator-(const fraction& rightObject) const {
    fraction difference;

    difference.wholeNumber = wholeNumber - rightObject.wholeNumber;
    int tmpDenominator = denominator * rightObject.denominator;
    difference.denominator = tmpDenominator;

    int tmpNumerator = numerator * rightObject.denominator - rightObject.numerator * denominator;
    difference.numerator = tmpNumerator;

    difference.reduce();

    return difference;
}

fraction fraction::operator*(const fraction& rightObject) const {
    fraction product;

    product.wholeNumber = wholeNumber * rightObject.wholeNumber;

    product.denominator = denominator * rightObject.denominator;

    product.numerator = numerator * rightObject.numerator;

    product.reduce();

    return product;
}

fraction fraction::operator/(const fraction& rightObject) const {
  fraction quotient;

  //divide fraction part
  quotient.numerator = numerator * rightObject.denominator;
  quotient.denominator = denominator * rightObject.numerator;

  //divide whole numbers and then add them back into the fraction
  double divOfWholes = wholeNumber / (double) rightObject.wholeNumber;
  fraction tmp;
  tmp.setFraction(divOfWholes);

   quotient = quotient + tmp;

  return quotient;
}
