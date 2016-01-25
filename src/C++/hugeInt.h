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

#ifndef HUGEINT_H
#define HUGEINT_H

#include <iostream>
#include <string>
using namespace std;

class hugeInt
{
    friend ostream &operator<<(ostream &, const hugeInt &);
public:
	static const unsigned int digits = 18; // max digits in hugeInt
	hugeInt(unsigned long = 0); // conversion/default constructor
	hugeInt(const string &); // conversion constructor

	~hugeInt(); // destructor
	string stringForm() const; // return hugeInt as string
	const hugeInt pow(long) const; // find the power
	unsigned int len() const
	{
		return size;
	} // end func length

	const hugeInt &operator=(const hugeInt &);//assignment operator
	const hugeInt &operator*=(const hugeInt &); // s1*=s2
	const hugeInt &operator*=(int); // s1*=2
	const hugeInt &operator+=(const hugeInt &); // s1+=s2
	const hugeInt &operator+=(int); // s1+=2

	//equality operator
	bool operator==(const hugeInt &) const;
	// inquality operator !=
	bool operator!=(const hugeInt &right) const
	{
		return !(*this == right); // invokes operator==
	} // end func operator!=
	// less than operator <
	bool operator<(const hugeInt &) const;
	// less than and equal to operator <=
	bool operator<=(const hugeInt &right) const
	{
		return !(right < *this);
	} // end func operator<=
	// greater than operator >
	bool operator>(const hugeInt &right) const
	{
		return right < *this;
	} // end func operator>
	// greater than and equal to operator >=
	bool operator>=(const hugeInt &right) const
	{
		return !(*this < right);
	} // end func operator >=

	// prefix increament operator++
	hugeInt &operator++();
	// prefix decreament operator++
	hugeInt &operator--();
	// addition operator; hugeInt + hugeInt
	hugeInt operator+(const hugeInt &) ;
	// addition operator; hugeInt + int
	hugeInt operator+(int);
	// addition operator; hugeInt + string that repr. large integer value
	hugeInt operator+(const string &);
	// subtraction operator; hugeInt - hugeInt
	hugeInt operator-(const hugeInt &); // only positive subtractions
	// subtraction operator; hugeInt - int
	hugeInt operator-(int); // only positive subtractions
	// multiplication operator; hugeInt * hugeInt
	hugeInt operator*(const hugeInt &);
	// multiplication operator; hugeInt * int
	hugeInt operator*(int);
	// multiplication operator; hugeInt * string that repr. large integer value
	hugeInt operator*(const string &);
	// division operator; hugeInt / hugeInt
	hugeInt operator/(const hugeInt &);

private:
	void subDivision(hugeInt &, unsigned int); // do unit division, hugeInt/int(unit or tens must end with 0)
	void rightShift(hugeInt &, unsigned int = 1); // shifts the array elements to the right
	void setArrayElement(short[], int); // utility func, for division to organise element in array
	hugeInt produceNine(hugeInt &); // produces values of 9's
	void power(hugeInt &, long); // exponential
	void setSize( hugeInt &); // set size
	short integer[digits];
	unsigned int size; // size of number
	unsigned int pos; // position of first element
}; // end class hugeInt

#endif
