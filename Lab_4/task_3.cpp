#include <stdlib.h>
#include <iostream>

using namespace std;

int main()
{

	int x, buffer, y;
	cout << "Enter parameter: ";
	cin >> x;
	cout << endl;

	asm("movl %[x], %[buff]\n"
		"andl $3, %[buff]\n"
		"movl %[buff], %[y]\n"
		"subl %[x], %[y]\n"
		: [y]"+g"(y), [buff]"+g"(buffer)
		: [x]"g"(x)
		: "cc"
	);
	cout << "x%4 - x = " << y << endl;
	return 0;
}
