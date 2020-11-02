#include <stdlib.h>
#include <iostream>

using namespace std;

int main()
{

	unsigned short x, y;      //4 байта
	unsigned int test_summ;   //8 байт
	cout << "Enter the first addendum: ";
	cin >> x;
	cout << endl;
	cout << "Enter the second addendum: ";
	cin >> y;
	cout << endl;

	test_summ = x + y;

	asm("addw %[y], %[x]"
		: [x] "+r"(x)
		: [y] "rm"(y)
		: "cc"
	);

	cout << "Summ: " << x << endl;
	if (test_summ == x)
		cout << "Summ is correct" << endl;
	else
	{
		cout << "Summ is incorrect, overflow have happened" << endl;
		cout << "Actual summ is " << test_summ << endl;
	}
	return 0;
}

//65535 для переполнения суммы