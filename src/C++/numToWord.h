/*
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
*/

#ifndef NUMTOWORD_H
#define NUMTOWORD_H

#include <string>
#include <stdexcept>
#include <vector>
#include "hugeInt.h"
using namespace std;

class numWord
{
    	friend ostream &operator<<(ostream &, numWord &);
public:
    	static string splitFigure(const string &value, bool trailing_zero = false);

	numWord(long long value = 0); // constructor
	numWord(string &); // constructor

	string getStr(); // returns a string in word form
private:
    	static string removeComma(const string &value);
    	static string revString(const string &); // reverse string

	string reverseString(const string &); // reverse string
	string removeDoubleSpace(const string &); // remove unwanted spaces
	string placeValue(string &); // add place value string
	string joinElements(const vector<string>); //join elements in a vector
	template < typename T>
	vector<T> reverseList(const vector<T>);

	hugeInt amount;

}; // end class numWord


#endif

