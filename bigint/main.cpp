#include"bigint.h"

int BigInt::objectnum = 0;

void testBigInt()
{
	BigInt x, y("1234"), z("00000987654321");
	cout << "x y z values: " << x << ' ' << y << ' ' << z << endl << endl;

	BigInt i(44, 2); // Array ¤j¤p 2
	BigInt j(i);
	BigInt k(10);
	cout << "i j k values: " << i << ' ' << j << ' ' << k << endl << endl;
	cout << "Total BigInt Object Count: " << BigInt::getCount() << endl << endl;

	x = y = "987654321098765432109876543210987654321098765432109876543210";
	cout << "x values: " << x << endl;
	cout << "y values: " << y << endl;
	cout << "z values: " << z << endl << endl;

	y = 10;
	y *= -88;
	cout << "y values: " << y << endl;
	y = 10;
	y *= i;
	cout << "y values: " << y << endl << endl;

	y = x / 8;
	cout << "y values: " << y << endl;
	x /= -8;
	cout << "x values: " << x << endl;
	x /= i;
	cout << "x values: " << x << endl << endl;

	y = 10;
	y += -88;
	cout << "y values: " << y << endl;
	y = 10;
	y += i;
	cout << "y values: " << y << endl;
	y = 10;
	y -= -88;
	cout << "y values: " << y << endl;
	y = 10;
	y -= i;
	cout << "y values: " << y << endl << endl;

	x = i + 3 + j * 2 * k;
	cout << "x values: " << x << endl;
	x = i - 3 - j * 2 * k;
	cout << "x values: " << x << endl;
	cout << "k values: " << k++ << ' ' << k << endl << endl;

	k = 10;
	x = ++k++;
	cout << "x k values: " << x << ' ' << k << endl;
	k = 10;
	x = --k--;
	cout << "x k values: " << x << ' ' << k << endl << endl;

	x = y = "987654321098765432109876543210";
	cout << "x values: " << x << endl;
	cout << "y values: " << y << endl;
	cout << "z values: " << z << endl << endl;
}

void testBigComplexNumber()
{
	BigComplexNumber x, y("10", "20"), z(2, 4);

	cout << "x y z values: " << x << ' ' << y << ' ' << z << endl;

	x = y + z;
	cout << "x y z values: " << x << ' ' << y << ' ' << z << endl;
	x += y;
	cout << "x y z values: " << x << ' ' << y << ' ' << z << endl;
	y += z;
	cout << "x y z values: " << x << ' ' << y << ' ' << z << endl;

	y.setValue(10, 20);
	z.setValue(4, 2);
	cout << "x y z values: " << x << ' ' << y << ' ' << z << endl;
	x = y - z;
	cout << "x y z values: " << x << ' ' << y << ' ' << z << endl;
	x -= y;
	cout << "x y z values: " << x << ' ' << y << ' ' << z << endl;
	z -= y;
	cout << "x y z values: " << x << ' ' << y << ' ' << z << endl;

	y.setValue(2, 4);
	z.setValue(10, 20);
	cout << "x y z values: " << x << ' ' << y << ' ' << z << endl;
	x = y * z;
	cout << "x y z values: " << x << ' ' << y << ' ' << z << endl;
	x *= y;
	cout << "x y z values: " << x << ' ' << y << ' ' << z << endl;
	z *= y;
	cout << "x y z values: " << x << ' ' << y << ' ' << z << endl;
}

void main()
{
	cout << "testBigInt:\n";
	testBigInt();
	cout << "testBigComplexNumber:\n";
	testBigComplexNumber();
	system("pause");
}
