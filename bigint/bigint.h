#include <iostream>
using namespace std;

class BigComplexNumber;
//俱计
class BigInt
{
	// () default: ㏕﹚(100) 俱计
	// () ヴ種俱计
public:
	static int objectnum;
	BigInt(); // default constructor, value = 0, capacity = 100, numDigits = 0
	BigInt(int value, int size = 10); // assign an integer value and capacity = size
	BigInt(const char*, int size = 10); // assign a string 
	BigInt(const BigInt&); // copy constructor
	~BigInt(); // destructor

	static int getCount() { return objectnum; }

	void Zero();
	void Add(const BigInt&);
	void Add(int);
	void Add(const char*);
	void PrintValue();
	void PrintValueABS();
	void Expansion(int);
	void Convert(int);

	friend ostream& operator<<(ostream& os, BigInt input);
	friend ostream& operator<<(ostream& os, BigComplexNumber input);

	BigInt operator+(BigInt);
	BigInt operator-(BigInt);
	BigInt operator*(BigInt);
	BigInt operator/(BigInt);

	BigInt operator=(const BigInt&);
	BigInt operator=(const int&);

	BigInt operator+=(BigInt);
	BigInt operator-=(BigInt);
	BigInt operator*=(BigInt);
	BigInt operator/=(BigInt);

	BigInt operator++(int);
	BigInt operator++();

	BigInt operator--(int);
	BigInt operator--();

private:
	char* num = nullptr; // Array: array–俱计计 俱计筁ㄓ璸衡ゑ耕よ獽(array材计 array材计 ...)
	int space; // Array  癘拘砰甧秖
	int count; // 俱计Τ碭计
	int sign; // 耎Θす砛タ璽计ㄏノ
};

inline ostream& operator<<(ostream& os, BigInt input)
{
	input.PrintValue();
	return os;
}

class BigComplexNumber
{
public:
	BigComplexNumber(BigInt = 0, BigInt = 0);
	void setValue(BigInt, BigInt);

	friend ostream& operator<<(ostream& os, BigComplexNumber input);
	
	BigComplexNumber operator+(const BigComplexNumber&);
	BigComplexNumber operator-(BigComplexNumber);
	BigComplexNumber operator*(const BigComplexNumber&);
	BigComplexNumber operator=(const BigComplexNumber&);
	BigComplexNumber operator+=(const BigComplexNumber&);
	BigComplexNumber operator-=(BigComplexNumber);
	BigComplexNumber operator*=(const BigComplexNumber&);
	
private:
	BigInt real;
	BigInt imaginary;
};

inline ostream& operator<<(ostream& os, BigComplexNumber input)
{
	if (input.real.sign == -1)
		cout << "-";
	input.real.PrintValueABS();
	if (input.imaginary.sign == -1)
		cout << "-";
	else
		cout << "+";
	input.imaginary.PrintValueABS();
	cout << "i";
	return os;
}
