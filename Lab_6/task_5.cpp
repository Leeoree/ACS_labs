#include <stdlib.h>
#include <iostream>

using namespace std;

int main()
{
	unsigned int x, y, myMul; 
	int count;
	cout << "Enter x: ";
	cin >> x;
	cout << endl;
	cout << "Enter y: ";
	cin >> y;
	cout << endl;

	asm("xorl %[S], %[S]\n"
		"xorl %[C], %[C]\n"
		"begin_loop:\n"
		"cmpl %[C], %[Y]\n"
		"je end_loop\n"
		"addl %[X], %[S]\n"
		"addl $1, %[C]\n"
		"jmp begin_loop\n"
		"end_loop:\n"
		: [S]"+rm"(myMul), [C]"+rm"(count)
		: [X] "rm"(x), [Y]"rm"(y)
		: "cc"
	);
	cout << x << " * " << y << " = " << myMul << endl;
	return 0;
}
