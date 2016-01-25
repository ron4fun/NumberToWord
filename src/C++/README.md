#NumToWord Class#


A C++ class implementation that converts numbers to words and can also split figures to a more readable value (display). This class (library) is built for monetary handling.


Example
---------



    
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
		cout << n1.splitFigure("53274287.67") << endl;
		cout << n1.splitFigure("339020.3", true) << endl;
		
		return 0;
	} // end main

Note
------

	NumToWord class can convert numbers ranging into quadrillion to word and 
	returns the string format quickly, with the aid of a hugeInt class I wrote
	myself, it is able to theoritically convert any number to word.
	The hugeInt class is still lacking in some areas feel free to test, modify and
	improve the class, thanks alot.
	

License
----------
    Copyright (c) 2015 Mbadiwe Nnaemeka Ronald ron2tele@gmail.com

    This software is provided 'as-is', without any express or implied
    warranty. In no event will the author be held liable for any damages
    arising from the use of this software.
    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:
    
    1. The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software
    in a product, an acknowledgment in the product documentation must be
    specified.
    
    2. Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.
    
    3. This notice must not be removed or altered from any source distribution.
        
        