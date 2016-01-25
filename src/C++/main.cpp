#include <iostream>
#include <string>
#include "numToWord.h"
using namespace std;

int main()
{
    int digit1 = 90889;
    long digit2 = 111111;
    long long digit3 = 2453564564;
    string digit4("762845324532874238");

    numWord n1(digit1);
    numWord n2(digit2);
    numWord n3(digit3);
    numWord n4(digit4);

    cout << digit1 << endl << n1 << endl << endl;
    cout << digit2 << endl << n2 << endl << endl;
    cout << digit3 << endl << n3 << endl << endl;
    cout << digit4 << endl << n4 << endl << endl;
    cout << n1.splitFigure("12346675.2", true) << endl;

    return 0;
} // end main
