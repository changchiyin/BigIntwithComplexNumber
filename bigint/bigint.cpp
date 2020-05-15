#include "bigint.h"

void BigInt::PrintValue()
{
	if (count == 1 && num[0] == 0)
		printf("0");
	else
	{
		if (sign == 1)
			cout << "+";
		else
			cout << "-";
		for (int i = count - 1; i >= 0; i--)
			cout << static_cast<int>(num[i]);
	}
}

void BigInt::PrintValueABS()
{
	for (int i = count - 1; i >= 0; i--)
		cout << static_cast<int>(num[i]);
}

void BigInt::Zero()
{
	for (int i = 0; i < space; i++)
		num[i] = 0;
}

BigInt::BigInt()
{
	// default constructor, value = 0, capacity = 100, numDigits = 0
	objectnum++;
	space = 10;
	num = new char[space];
	Zero();
	count = 1, sign = 1;
}

BigInt::~BigInt()
{
	// destructor
	objectnum--;
	if (space > 0)
	{
		if (space == 1)
			delete num;
		else
			delete[] num;
	}
}

//////////////////////////////////////////////////////////////////////////////
// BUG
//////////////////////////////////////////////////////////////////////////////

BigInt::BigInt(const char* const s, const int size)
{
	// assign a string 
	objectnum++;
	int strSize = strlen(s);
	if (s[0] == '+' || s[0] == '-')
		strSize--;
	space = (strSize > size) ? strSize : size;
	if (space == 1)
		num = new char;
	else
		num = new char[space];
	Zero();
	if (s[0] == '-')
		sign = -1;
	else
		sign = 1;
	for (int i = 0; i < strSize; i++)
	{
		if (s[strSize - i - 1] < '0' || s[strSize - i - 1] > '9')
			break;
		num[i] = s[strSize - i - 1] - 48;
	}
	count = strSize;
	while ((num[count - 1] == 0) && (count > 1))
		count--;
}

BigInt::BigInt(int value, const int size)
{
	objectnum++;
	if (value < 0)
		sign = -1, value *= -1;
	else
		sign = 1;
	int valueSize = 1, temp = value / 10;
	while (temp > 0)
		temp /= 10, valueSize++;
	count = valueSize;
	space = (valueSize > size) ? valueSize : size;
	if (space == 1)
		num = new char;
	else
		num = new char[space];
	Zero();
	valueSize = 0, temp = value;
	while (temp > 0)
		num[valueSize] = temp % 10, temp /= 10, valueSize++;
}

BigInt::BigInt(const BigInt& copy)
{
	objectnum++;
	sign = copy.sign;
	count = copy.count;
	space = copy.space;
	if (space == 1)
		num = new char;
	else
		num = new char[space];
	for (int i = 0; i < space; i++)
		num[i] = copy.num[i];
}

void BigInt::Add(const char* const s)
{
	BigInt save(s, space);
	Add(save);
}

void BigInt::Add(const int value)
{
	BigInt save(value, space);
	Add(save);
}

void BigInt::Add(const BigInt& copy)
{
	int carry = 0, max = (count > copy.count) ? count + 1 : copy.count + 1;
	BigInt temp(copy);
	if (space < max)
		Expansion(max);
	if (temp.space < max)
		temp.Expansion(max);
	if (sign != temp.sign)
	{
		if (sign == -1)
			Convert(max);
		else
			temp.Convert(max);
	}
	for (int i = 0; i < max; i++)
	{
		num[i] = (num[i] + temp.num[i] + carry);
		carry = num[i] / 10;
		num[i] %= 10;
	}
	if (sign != temp.sign)
	{
		if (num[max - 1] == 9)
		{
			Convert(max);
			sign = -1;
		}
		else
			sign = 1;
	}
	count = max;
	while ((num[count - 1] == 0) && (count > 1))
		count--;
}

void BigInt::Expansion(const int max)
{
	char* save;
	save = new char[max];
	for (int i = 0; i < count; i++)
		save[i] = num[i];
	for (int i = count; i < max; i++)
		save[i] = 0;
	if (space == 1)
		delete num;
	else
		delete[] num;
	num = save;
	space = max;
}

void BigInt::Convert(int max)
{
	int carry = 1;
	for (int i = 0; i < max; i++)
		num[i] = 9 - num[i];
	for (int i = 0; i < max; i++)
	{
		num[i] = num[i] + carry;
		carry = num[i] / 10;
		num[i] %= 10;
	}
}

BigInt BigInt::operator+(BigInt input)
{
	BigInt ans(*this);
	ans.Add(input);
	return ans;
}

BigInt BigInt::operator-(BigInt input)
{
	input.sign *= -1;
	BigInt ans(*this);
	ans.Add(input);
	return ans;
}

BigInt BigInt::operator*(BigInt input)
{
	BigInt ans;
	for (int i = 0; i < input.num[0]; i++)
		ans.Add(*this);
	int temp = 10;
	for (int i = 1; i < input.count; i++)
	{
		for (int j = 0; j < input.num[i] * temp; j++)
			ans.Add(*this);
		temp *= 10;
	}
	ans.sign *= input.sign;
	return ans;
}

BigInt BigInt::operator/(BigInt input)
{
	int sign_save = input.sign;
	if (input.sign < 0)
		input.sign *= -1;
	BigInt ans, div;
	int temp;
	for (int i = count - 1; i >= 0; i--)
	{
		temp = 0;
		div = div * 10 + num[i];
		while (div.sign == 1)
			div -= input, temp++;
		div += input, temp--;
		ans = ans * 10 + temp;
	}
	ans.sign *= sign_save;
	return ans;
}

BigInt BigInt::operator=(const BigInt& input)
{
	sign = input.sign;
	count = input.count;
	space = input.space;
	if (space == 1)
	{
		delete num;
		num = new char;
	}
	else
	{
		delete[] num;
		num = new char[space];
	}
	for (int i = 0; i < space; i++)
		num[i] = input.num[i];
	return *this;
}

BigInt BigInt::operator=(const int& input)
{
	BigInt temp(input);
	*this = temp;
	return temp;
}

BigInt BigInt::operator+=(BigInt input)
{
	Add(input);
	return *this;
}

BigInt BigInt::operator-=(BigInt input)
{
	input.sign *= -1;
	Add(input);
	return *this;
}

BigInt BigInt::operator*=(BigInt input)
{
	*this = *this * input;
	return *this;
}

BigInt BigInt::operator/=(BigInt input)
{
	*this = *this / input;
	return *this;
}

BigInt BigInt::operator++(int)
{
	BigInt temp(*this);
	Add(1);
	return temp;
}

BigInt BigInt::operator++()
{
	Add(1);
	return *this;
}

BigInt BigInt::operator--(int)
{
	BigInt temp(*this);
	Add(-1);
	return temp;
}

BigInt BigInt::operator--()
{
	Add(-1);
	return *this;
}

BigComplexNumber::BigComplexNumber(BigInt r, BigInt i)
{
	real = r;
	imaginary = i;
}

void BigComplexNumber::setValue(BigInt r, BigInt i)
{
	real = r;
	imaginary = i;
}

BigComplexNumber BigComplexNumber::operator+(const BigComplexNumber& input)
{
	BigComplexNumber temp;
	temp.real = real + input.real;
	temp.imaginary = imaginary + input.imaginary;
	return temp;
}

BigComplexNumber BigComplexNumber::operator-(BigComplexNumber input)
{
	BigComplexNumber temp;
	temp.real = real - input.real;
	temp.imaginary = imaginary - input.imaginary;
	return temp;
}

BigComplexNumber BigComplexNumber::operator*(const BigComplexNumber& input)
{
	BigComplexNumber temp;
	temp.real = real * input.real - imaginary * input.imaginary;
	temp.imaginary = imaginary * input.real + real * input.imaginary;
	return temp;
}

BigComplexNumber BigComplexNumber::operator=(const BigComplexNumber& input)
{
	real = input.real;
	imaginary = input.imaginary;
	return *this;
}

BigComplexNumber BigComplexNumber::operator+=(const BigComplexNumber& input)
{
	real += input.real;
	imaginary += input.imaginary;
	return *this;
}

BigComplexNumber BigComplexNumber::operator-=(BigComplexNumber input)
{
	real -= input.real;
	imaginary -= input.imaginary;
	return *this;
}

BigComplexNumber BigComplexNumber::operator*=(const BigComplexNumber& input)
{
	*this = *this * input;
	return *this;
}
