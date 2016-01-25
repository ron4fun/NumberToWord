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

#include "numToWord.h"
#include <stdexcept>
using namespace std;

string num[28][2] = { { "","" },
				{ "1", "one" },
				{ "2", "two" },
				{ "3", "three" },
				{ "4", "four" },
				{ "5", "five" },
				{ "6", "six" },
				{ "7", "seven" },
				{ "8", "eight" },
				{ "9", "nine" },
				{ "10", "ten" },
				{ "11", "eleven" },
				{ "12", "twelve" },
				{ "13", "thirteen" },
				{ "14", "fourteen" },
				{ "15", "fifteen" },
				{ "16", "sixteen"},
				{ "17", "seventeen" },
				{ "18", "eighteen" },
				{ "19", "nineteen" },
				{ "20", "twenty" },
				{ "30", "thirty" },
				{ "40", "forty" },
				{ "50", "fifty" },
				{ "60", "sixty" },
				{ "70", "seventy" },
				{ "80", "eighty" },
				{ "90", "ninety" } };

string units[] = { "", "thousand", "million", "billion", "trillion", "quadrillion" };

numWord::numWord(long long Amount)
{
    if(Amount < 0)
        throw invalid_argument("Argument must be a positive integer.");

    this->amount = Amount;
} // end constructor

numWord::numWord(string &Amount)
:amount(Amount)
{

} // end constructor

// remove unwanted spaces
string numWord::removeDoubleSpace(const string &value)
{
	string word, tempValue;

	for (string::size_type i = 0; i < value.size(); ++i)
	{
		if (value[i] != ' ') // if current letter is not a space
			word += value[i]; // add the letters of the words until a space is found
		else
		{
			if (word.size() > 0)
				tempValue += (word + " ");

			word = ""; // reset word
		} // end else
	} // end for

	// add last word inserted in string word object
	tempValue += word;

	// check if last letter is a space
	if (tempValue[tempValue.size() - 1] == ' ')
		tempValue.pop_back();

	return tempValue;
} // end func removeDoubleSpace

template < typename T>
vector<T> numWord::reverseList( const vector<T> list)
{
	int length = list.size();
	vector<T> tempList;

	for (int i = length - 1; i >= 0; --i)
	{
		tempList.push_back(list[i]);
	} // end for

	return tempList;
} // end func reverseList

// function converts 3 digit numbers to place value string
string numWord::placeValue(string &value)
{
	string first, second, third; // hold individual digits

	// if len of value is not 3, add zero in front to make it 3 digits
	if (value.length() != 3)
	{
		for (size_t i = 0; i < (3 - value.length()); ++i)
			value = "0" + value;
	} // end if

	// split value into hundred, tens and unit
	first = value[0]; // first digit

	if (value[1] == '1' && value[1] != '0')
	{
		second = "";
		third = value.substr(1); // value[1:]; // number 10 - 19
	} // end if
	else
	{
		second = value[1];
		second += "0"; // number 20, 30, 40, ..., 90
		third = value[2]; // last digit
	} // end else


	if (first != "0") // if not 0
	{
		for (int i = 0; i < 28; ++i)
		{
			if (num[i][0] == first) // if dictionary key is == digit string
			{
				first = num[i][1] + " hundred"; // store the word in first
				break;
			} // end if
		} // end func for
	} // end func if
	else
		first = "";

	if (second != "0" && second != "00") // if not 0
	{
		for (int i = 0; i < 28; ++i)
		{
			if (num[i][0] == second) // if dictionary key is == digit string
			{
				if (first != "")
					second = " and " + num[i][1]; // store the word in first
				else
					second = num[i][1];
				break;
			} // end if
		} // end func for
	} // end if
	else
		second = "";

	if (third != "0") // if not 0
	{
		for (int i = 0; i < 28; ++i)
		{
			if (num[i][0] == third) // if dictionary key is == digit string
			{
				if (first != "" && second == "")
					third = " and " + num[i][1]; // store the word in first
				else
					third = " " + num[i][1];
				break;
			} // end if
		} // end func for
	} // end if
	else
		third = "";

	string temp = first + second + third; // temp data to hold string

	return removeDoubleSpace(temp);
} // end func placeValue

string numWord::reverseString(const string &value)
{
	string::const_iterator iterator = value.end();
	string temp;

	while (iterator > value.begin())
	{
		--iterator;
		temp += *iterator;
	} // end while

	return temp;
} // end func reverseString

string numWord::joinElements(const vector<string> list)
{
	int length = list.size();
	string temp;

	for (int i = 0; i < length; ++i)
		temp += list[i];

	return temp;
} // end func joinElements

string numWord::getStr()
{
	string oldStr = amount.stringForm(); // convert hugeInt amount to string
	int length = oldStr.size(); // get the length of amount

	vector<string> holder; // holds at most 3 digits as elements
	string threesome; // holds the 3 digit string for manipulation

	for (int i = length - 1, counter = 0; i >= 0; --i, ++counter)
	{
		if (counter % 3 == 0 && counter != 0)
		{
			threesome = reverseString(threesome); // reverse string

			holder.push_back(threesome); // append threesome

			threesome = ""; // empty
		} // end if

		threesome += oldStr[i]; // hold at most 3 digit in reverse order, space is to enable split function in str
	} // end for

	// incase there are some digits been held by threesome
	threesome = reverseString(threesome); // reverse string
	holder.push_back(threesome); // append threesome

	vector<string> tempList; // hold new words list;
	for (unsigned int i = 0; i < holder.size(); ++i)
	{
		if (placeValue(holder[i]) != "")
			tempList.push_back(placeValue(holder[i]) + " " + units[i] + " ");
	} // end for

	//reverse the tempList list
	tempList = reverseList(tempList);

	return removeDoubleSpace(joinElements(tempList)); // remove spaces after joining elements in templist
} // end func getAmountStr

string numWord::splitFigure(const string &value, bool trailing_zero)
{
	string integer_side;
	string decimal_side;

	// Make sure value is all number
	for (size_t i = 0; i < value.length(); ++i)
	{
		if ((value[i] >= '0' && value[i] <= '9') || value[i] == ',' || value[i] == '.')
			continue;
		throw invalid_argument("Value contains wrong input.");
	} // end for

	// Making sure no comma in string
	if (value.find(',') != -1)
		integer_side = removeComma(value);
	else
		integer_side = value;

	// Organising the decimal part of the number
	decimal_side = ".00";
	int index = value.find('.');
	if (index != -1) // if there is a decimal place
	{
		if (value.find('.', index+1) != -1)
			throw invalid_argument("Value contains multiple decimal points.");

		string s;
		if (size_t(index + 1) < value.length())
			s = value.substr(index + 1);
		else
			s = "";

		if (s.length() > 2)
			throw invalid_argument("Value contains too many digits after decimal point.");

		index = integer_side.rfind('.');
		int len = integer_side.length();
		integer_side = integer_side.substr(0, len - (len - index));

		if (s.length() == 2)
		{
			decimal_side[1] = s[0];
			decimal_side[2] = s[1];
		} // end if
		else  if (s.length() == 1)
		{
			decimal_side[2] = s[0];
		} // end if
	} // end if

	size_t strLength = integer_side.length();
	if (strLength == 0)
		integer_side = "0";
	if (strLength < 4)
	{
		if (trailing_zero)
			return integer_side + decimal_side;
		return integer_side;
	} // end if

	vector<string> dump;
	integer_side = revString(integer_side);
	strLength = integer_side.length();

	for (size_t i = 0; i < strLength; i += 3)
	{
		if (i + 3 > strLength)
		{
			dump.push_back(integer_side.substr(i, strLength - i));
			break;
		} // end if
		string out = integer_side.substr(i, 3);
		dump.push_back(out);
	} // end for

	integer_side.clear();
	for (size_t i = 0; i < dump.size(); ++i)
	{
		integer_side += (dump[i] + ",");
	} // end for
	integer_side.pop_back();
	integer_side = revString(integer_side);
	if (trailing_zero)
		return integer_side + decimal_side;
	return integer_side;
} // end func splitFigure

string numWord::removeComma(const string &value)
{
	string temp;
	size_t len = value.size();

	for (size_t i = 0; i < len; ++i)
	{
		if (value[i] == ',')
			continue;
		temp += value[i];
	} // end for

	return temp;
} // end func removeComma

// reverse string
string numWord::revString(const string &value)
{
	string::const_iterator iterator = value.end();
	string temp;

	while (iterator > value.begin())
	{
		--iterator;
		temp += *iterator;
	} // end while

	return temp;
} // end func reverseString

// overloaded output operator
ostream& operator<<(ostream &output, numWord &num)
{
	output << num.getStr();

	return output;
} // endfunction operator<<
