#include <iostream>
#include <iomanip>
using namespace std;
#include "fraction.h"

int main()
{
   fraction f5(2.875);
   fraction::outputFormat(fraction::improper);
   cout << f5 << endl;

   fraction f1(1,2);

   cout << f1 + f5 << endl;
  // cout << f5.getWholeNumber() << endl;

   return 0;
}
