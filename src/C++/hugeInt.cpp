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

#include "hugeInt.h"
#include <stdexcept>
#include <cctype> // for isdigit func prototype

using namespace std;

hugeInt::hugeInt( unsigned long value)
{
	// initialize array to zero
	for (size_t i = 0; i < digits; ++i)
		integer[i] = 0;

	//place digits of argument into array
	for (int j = digits - 1; value != 0 && j >= 0; j--)
	{
		if (j >= 0)
		{
			integer[j] = value % 10;
			value /= 10;
		} // end if
		else if (j < 0 && value != 0)
			throw out_of_range("Maximum digits for hugeInt is passed.");
	} // end for

	setSize(*this);
} // end conversion/ default constructor

// conversion constructor that converts a character string
// representing a large integer into a hugeInt object
hugeInt::hugeInt(const string &number)
{
	// initialize array to zero
	for (size_t i = 0; i < digits; ++i)
		integer[i] = 0;

	// place digits of argument into array
	unsigned int length = number.size();

	if (length <= hugeInt::digits) // max length
	{
		for (size_t j = digits - length, k = 0; j < digits; ++j, ++k)
		{
			if (isdigit(number[k]))// ensure that character is a digit
				integer[j] = number[k] - '0';
			else
				throw invalid_argument("String must contain only numbers.");
		} // end for
	} // end if
	else
		throw out_of_range("Maximum digits for hugeInt passed."); // if after the max digit, there remains a value to carry over

	setSize(*this);
} // end hugeInt conversion constructor

hugeInt::~hugeInt()
{
} // end destructor

void hugeInt::setSize( hugeInt &num)
{
	size_t i;

	for (i = 0; (num.integer[i] == 0) && (i <= hugeInt::digits); ++i)
		; // skip leading zeros

	num.pos = i; // set position of first digit
	num.size = digits - i; // set size data member
} // end func setSize

void hugeInt::rightShift(hugeInt &num, unsigned int how_many)
{
	hugeInt fakeNum = num;
	unsigned int j = num.pos, counter = 0;
	for (; counter < how_many; ++counter)
	{
		j = num.pos;
		fakeNum.integer[j] = 0; // make the first entry 0
		for (; j < digits - 1; ++j)
		{
			fakeNum.integer[j + 1] = num.integer[j]; // right shift digits
		} // end for
		//setSize(fakeNum); // resets the size and pos of fakeNum
		num = fakeNum; // copy elements into object
		setSize(num); // set size
	} // end for

} // end func rightShift

void hugeInt::subDivision(hugeInt &num, unsigned int val)//hugeInt &divider)
{
	unsigned int hold, rem; //val = value;//divider.integer[divider.pos]; // hold the digit
	hugeInt temp = num, fakeNum = num; // temporary hugeInt object for calculations
	unsigned int i = num.pos;

	if (val%10 == 0 && val >= 0)
	{
		rightShift(fakeNum); // shifts fakeNum array elements to the right all others at the front is zero
		++i; // shift right
		temp = fakeNum; // copy new value
	} // end if

	for (; i < digits - 1; ++i) // stop at 28
	{
		hold = fakeNum.integer[i] / val; // hold integer division
		rem = (fakeNum.integer[i] % val) * 10; // hold and multiply by 10 carryover forward value
		temp.integer[i] = hold;  // copy integer division into current position in temp object array
		temp.integer[i + 1] += rem; // copy remainder into forward position in temp object array
		fakeNum.integer[i + 1] = temp.integer[i + 1]; // put fakeNum foward position array element = new temp object forward position value for calculation
	} // end for
	hold = fakeNum.integer[i] / val; // do integer division for last digit
	temp.integer[i] = hold; // copy to temp object

	//setSize(temp); // set size
	num = temp; // copy temp into object
	//return temp;
}// end func subDivision

// utility func, for division to organise element in array
void hugeInt::setArrayElement(short * array, int start)
{
	for (register int i = start; i >= 0; --i)
	{
		array[i - 1] += (array[i] / 10); // carry over integer division of current position in array and add to element behind
		array[i] %= 10; //  save remainder in current pos

		if (i - 1 < 0) // if gone beyond array length
			throw out_of_range("Out of range, max lenght is 30.");
		else if (array[i - 1] <= 9)
			break; // it's a unit value(single value) and require no futher deduction
	} // end for
} // end func setArrayElement

hugeInt hugeInt::produceNine(hugeInt &num)
{
	string hold_nines; // hold 9's

	for (hugeInt i = 0; i < num; ++i)
		hold_nines += "9"; // join 9's

	hugeInt temp(hold_nines); // create a hugeInt object of nines

	return temp;
} // end func produceNine

void hugeInt::power(hugeInt &num, long val)
{
	hugeInt temp = 1;

	for (long i = 0; i < val; ++i)
		temp *= num; // multiply number by itself

	num = temp; // copy value
} // end func produceNine

const hugeInt &hugeInt::operator=(const hugeInt &right)
{
	for (unsigned int i = 0; i < digits; ++i)
	{
		integer[i] = right.integer[i]; // copy into object
	} // end for

	//setSize(*this); // set new size for object
	pos = right.pos;
	size = right.size;
	return *this; // enables  x = y = z
} // end func operator=

// multiplication operator*=, hugeint*=hugeint
const hugeInt &hugeInt::operator*=(const hugeInt &right)
{
	*this = *this * right; // invokes operator*
	return *this; // enables cascading
} // end func operator*=

// multiplication operator*=, hugeint*=int
const hugeInt &hugeInt::operator*=(int num)
{
	hugeInt temp = num;
	*this = *this * temp; // invokes operator*
	return *this; // enables cascading
} // end func operator*=

// addition operator+=, hugeint+=hugeint
const hugeInt &hugeInt::operator+=(const hugeInt &right)
{
	*this = *this + right; // invokes operator+
	return *this; // enables cascading
} // end func operator+=

// addition operator+=, hugeint+=int
const hugeInt &hugeInt::operator+=(int num)
{
	*this = *this + num; // invokes operator*
	return *this; // enables cascading
} // end func operator+=

//equality operator
bool hugeInt::operator == (const hugeInt &num) const
{
	if (size != num.size)
		return false; // not thesame size

	for (unsigned int i = 0; i < digits; ++i)
	{
		if (integer[i] != num.integer[i])
			return false; // digits are not equal
	} // end for

	return true; // digits are equal
} // end func operator==

// less than operator <
bool hugeInt::operator<(const hugeInt &num) const
{
	if (size < num.size)
		return true; // object is smaller
	else if (size > num.size)
		return false; // object is bigger
	// if they are of thesame size
	for (unsigned int i = pos; i < digits; ++i)
	{
		if (integer[i] < num.integer[i])
			return true; // first digit of object is smaller
		else if (integer[i] > num.integer[i])
			return false; // first digit of object is bigger
	} // end for
	// if they are all equal return false
	return false; // object not smaller
} // end func operator <

// increament operator++, prefix increament
hugeInt &hugeInt::operator++()
{
	*this = *this + 1; // invokes the addition operator
	return *this; // enables cascading
} // end func operator++

// increament operator--, prefix decreament
hugeInt &hugeInt::operator--()
{
	hugeInt one = 1;
	*this = *this - one; // invokes operator-
	return *this; // enables cascading
} // end func operator--

// addition operator; hugeInt + hugeInt
 hugeInt hugeInt::operator+(const hugeInt &op2)
{
	hugeInt temp; // temporary result
	int carry = 0;

	for (int i = digits - 1; i >= 0; i--)
	{
		temp.integer[i] = integer[i] + op2.integer[i] + carry;

		// determine whether to carry a1
		if (temp.integer[i] > 9)
		{
			temp.integer[i] %= 10; // reduce to 0-9
			carry = 1;
		} // end if
		else // no carry
			carry = 0;
   } // end for

	setSize(temp); // set size

	return temp; // return copy of temporary object
} // end function operator+

// addition operator; HugeInt +int
 hugeInt hugeInt::operator+(int op2)
{
	// convert op2 to a HugeInt, then invoke
	// operator+ for two hugeInt objects
	return *this + hugeInt(op2);
} // endfunction operator+

// hugeInt + string that represents large integer value
hugeInt hugeInt::operator+(const string &op2)
{
	// convert op2 to a hugeInt, then invoke
	// operator+ for two hugeInt objects
	return *this + hugeInt(op2);
} // endoperator+

// subtraction operator; hugeInt - hugeInt
hugeInt hugeInt::operator-(const hugeInt &op2)
{
	hugeInt temp, fakeTemp = *this, negSign("999999999999999999999999999999"); // temporary result

	if (*this >= op2) // the left value must be larger
	{
		for (int i = digits - 1; i >= 0; i--)
		{
			if (fakeTemp.integer[i] < op2.integer[i])
			{
				for (int j = i; j >= 0; j--)
				{
					if (fakeTemp.integer[j - 1] > 0) // if left element is a number you can borrow from
					{
						fakeTemp.integer[i] += 10;  // carry over 10 from digit in front and add to current digit
						fakeTemp.integer[j - 1] -= 1; // subtract one from the element you borrowed ten from
						break;
					} // end if
					// if code reaches here it means the element to the left is zero
					fakeTemp.integer[j - 1] = 9; // put nine bcos at the end it will still be nine after borrowing from it

				} // end for

			} // end if

			temp.integer[i] = fakeTemp.integer[i] - op2.integer[i];

		} // end for
	} // end if
	else
		return negSign; // show that a negative ans is gotten

	setSize(temp); // set size

	return temp; // return copy of temporary object
} // end func operator-

// subtraction operator; hugeInt - int
hugeInt hugeInt::operator-(int op2)
{
	// convert op2 to a HugeInt, then invoke
	// operator- for two hugeInt objects
	return *this + hugeInt(op2);
} // end func operator-

// multiplication operator; hugeInt * hugeInt
hugeInt hugeInt::operator*(const hugeInt &op2)
{
	hugeInt temp; // temporary result
	hugeInt thisHold = *this;
	int start = digits;
	int y; // helps temp object to decrease sequentially, from high to low
	int val; // hold single digit multiplicant

	for (register unsigned int i = digits - 1; i >= op2.pos; --i) // for our right hand number in the multiplication
	{
		val = op2.integer[i];
		--start; // keep temp object array indexing in correct position
		y = 0; // to push temp object array indrx from high to low
		for (register int j = digits - 1; j >= pos; --j, ++y) // for our left hand operand, remember increamenting y
		{
			temp.integer[start - y] = (val * integer[j]) + temp.integer[start - y];
			// determine whether to carry over values to maintain single value in each index
			if (temp.integer[start - y] > 9)
			{
				setArrayElement(temp.integer, start - y);
			} // end if
		} // end for
	} // end for

	setSize(temp); // set size

	return temp; // return temporary object
} // end function operator*

// multiplication operator; HugeInt * int
hugeInt hugeInt::operator*(int op2)
{
	hugeInt temp = op2;
	// convert op2 to a HugeInt, then invoke
	// operator* for two hugeInt objects
	return *this * temp;
} // end function operator*

// hugeInt * string that represents large integer value
hugeInt hugeInt::operator*(const string &op2)
{
	// convert op2 to a hugeInt, then invoke
	// operator* for two hugeInt objects
	return *this * hugeInt(op2);
} // end operator*

// division operator; hugeInt / hugeInt
hugeInt hugeInt::operator/(const hugeInt &op2)
{
	 if (*this == 0) // check if numerator is zero
		throw invalid_argument("Zero must not be the numerator.");
	 else if (op2 == 0 || size < op2.size)
			return 0; // return zero, if denominator is zero

	 hugeInt subOne = op2, one = 1, c = op2;
	 --c; // remove one from c
	 register hugeInt  min = 10, max, ten = 10, ans, hold, average; // hold result
	 hugeInt opFake = 10;

	 //bool size8 = false;
	 power(opFake, size);
	 int sizeDiff = opFake.size - op2.size; // hold the difference in size btw numerator and denominator

	 if (sizeDiff > 0)
	 {
		 power(min, (sizeDiff - 1)); // 10^(sizeDiff-1); lowest value quotient can be
		 hugeInt no_of_nines(sizeDiff + 1); // holds the nos of nines to be produced
		 max = produceNine(no_of_nines); // the highest value the quotient can be
	 } // end if
	 else // sizeDiff == 0
	 {
		 min = 0;
		 max = opFake;
	 } // end else


	while (true)
	{
		average = max + min;
		subDivision(average, 2); // find the  average
		hold = average * c;

		//cout << average * c << " c: " << c << " average: " << average << " max: " << max << " min: " << min << endl;

		if (hold <= opFake) // a positve or zero value
			ans = opFake - hold;
		else // a negative value
			ans = -1;
		//cout << "ans: " << ans << " hold: " << hold << endl;
		if ( ans > average)
		{
			hold = max - min;
			min = average;
		} // end if
		else if ( ans < average)
		{
			hold = max - min;
			max = average;
		} // end else if
		else if( ans == -1) // ans is negative
		{
			hold = max - min;
			max = average;
		} // end else if
		else // ans == average
			break; // average is the answer

		if (hold == one)
		{
			ans = min; // the min value is the answer
			break;
		} // end if

	} // end while
	/////////////////////////////////////////////
	//approx
	////////////////////////////////////////////
	//cout << "ANS: " << ans << endl;
	ans *= *this;
	//cout << "ANS: " << ans << endl;

	//unsigned int x = digits - size, value = ans.integer[x]; // index of number after the decimal, so as to approx properly

	rightShift(ans, size); // division by ten^size takes place

	// final check , to ensure that ans is the correct value
	hold = ans * op2; // jst hold the check value

	if (hold > *this) // if ans is bigger than the correct integer division
	{
		for (;;)
		{
			--ans; // decrease ans and test for correctness
			if ((ans*op2) <= *this) // if their product is less than *this then that is the correct integer ans
				break;
		} // end for
	} // end if
	else if ((hold+op2) < *this)
	// if ans is less than the correct integer division, +op2 bcos if ans*op2 is suppose to be equal or less than to ans
	// so if ans*op2 + op2 is less than *this it means  the ans is still up the scale
	{
		for (;;)
		{
			++ans; // increase ans and test for correctness
			if ((ans*op2) > *this) // if their product is greater than *this then the correct integer ans is the former ans value
			{
				--ans; // reduce ans to former value
				break;
			} // end if
		} // end for
	} // end else if
	//cout << "ANS: " << (ans*(op2)) << endl;
	return ans; // return object */
} // end func operator /

string hugeInt::stringForm() const
{
	string output;
	size_t i;

	for (i = 0; (integer[i] == 0) && (i <= hugeInt::digits); ++i)
		; // skip leading zeros

	if (i == hugeInt::digits)
		output = "0";
	else if (size == 0)
		output = "0";
	else
		for (; i < hugeInt::digits; ++i)
			output += integer[i] + '0'; // convert to string

	return output;
} // end func toString

// overloaded output operator
ostream& operator<<(ostream &output, const hugeInt &num)
{
	size_t i;

	for (i = 0; (num.integer[i] == 0) && (i <= hugeInt::digits); ++i)
	; // skip leading zeros

	if (i == hugeInt::digits)
		output << 0;
	else if (num.size == 0)
		output << 0;
	else
		for (; i < hugeInt::digits; ++i)
			output << num.integer[i];

	return output;
} // endfunction operator<<
