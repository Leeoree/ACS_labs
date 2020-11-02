#include <stdlib.h>
#include <iostream>

using namespace std;

int main()
{

	int x, buffer, y;
	cout << "Enter parameter: ";
	cin >> x;
	cout << endl;

	asm("movl %2, %1\n"
		"andl $3, %1\n"
		"movl %1, %0\n"
		"subl %2, %0\n"
		: "+g"(y), "+g"(buffer)
		: "g"(x)
		: "cc"
	);
	cout << "x%4 - x = " << y << endl;
	return 0;
}
