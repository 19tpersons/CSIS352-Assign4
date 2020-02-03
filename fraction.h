#include <iostream>

using namespace std;

class fraction {
  friend ostream& operator<<(ostream&, const fraction&);
  friend istream& operator>>(istream&, fraction&);
public:
  enum fractionType {improper, decimal, mixed};
  static fractionType outputType;


  //sets the fraction
  void setFraction(int n, int d);
  void setFraction(double number);

  //sets the denominator
  void setDenominator(int number);

  //Returns numerator
  int getNumerator();

  //Returns denominator
  int getDenominator();

  //returns whole number
  int getWholeNumber();
  
  //Returns the decimal value of the fraction
  double decimalValue();

  static void outputFormat(fractionType newType);

  void reduce();

  //overload << + - / * == = >>
  const fraction& operator=(const fraction& rightObject);
  const fraction& operator=(double number);

  bool operator==(const fraction&) const;
  bool operator==(int);
  bool operator<(int);

  fraction operator+(const fraction& rightObject) const;
  fraction operator-(const fraction& rightObject) const;
  fraction operator*(const fraction& rightObject) const;
  fraction operator/(const fraction& rightObject) const;


  fraction();
  fraction(double);
  fraction(int numerator, int denominator);
private:
  int numerator = 0;
  int denominator = 1;
  int wholeNumber = 0;
};
