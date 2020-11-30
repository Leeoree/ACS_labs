#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
	string format = "%d \t";
	int N, elem, increm, prev;
	cout << "Enter N: ";
	cin >> N;
	cout << endl;


	asm("movl $1, %[I]\n"
		"movl $0, %[P]\n"
		"movl $1, %[E]\n"
		"cmpl $0, %[N]\n"
		"jle end_loop\n"
		"jmp trivial_case\n"
		"begin_loop:\n"

		"push %[E]\n"
		"push %[F]\n"
		"call _printf\n"
		"add $8, %%esp\n"

		"subl $1, %[N]\n"
		"cmpl $0, %[N]\n"
		"jz end_loop\n"

		"movl %[E], %[P]\n"
		"addl %[I], %[E]\n"
		"movl %[P], %[I]\n"

		"jmp begin_loop\n"

		"trivial_case:\n"
		"push %[E]\n"
		"push %[F]\n"
		"call _printf\n"
		"add $8, %%esp\n"
		"cmpl $1, %[N]\n"
		"je end_loop\n"
		"jg begin_loop\n"

		"end_loop:\n"
		: [P]"=r"(prev), [E]"=rm"(elem), [I]"=rm"(increm)
		: [F]"m"(format), [N]"m"(N)
		: "cc", "%eax", "%ecx"
	);

	return 0;
}