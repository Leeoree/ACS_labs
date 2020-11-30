#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
	const volatile double multiplier = 0.5;
	double E, summ = 0, ai = 1;
	unsigned int i = 0;
	cout << "Enter E: ";
	cin >> E;
	cout << endl;

	if (E < pow(10, -14))
	{
		cout << "Unattainable accuracy: E = 10^(-14) will be used" << endl;
		E = pow(10, -14);
	}

	asm("fldz\n"						//0
		"fldl %[E]\n"					//E, 0
		"fld1\n"						//1, E, 0

		"begin_loop:"
		"fcom\n"						//a(i) , E , 0.5 , summ(i-1)
		"fstsw %%ax\n"
		"sahf\n"
		"jb end_loop\n"
		"fadd %%st(0), %%st(2)\n"		//a(i)   , E	  , 0.5	    , summ(i-1) + a(i)
		"fldl %[M]\n"					//M	     , a(i)   , E       , 0.5				, summ(i)
		"fmulp\n"						//M*a(i) , E      , 0.5		, summ(i)
		"addl $1, %[I]\n"

		"fcom\n"						//a(i+1) , E	  , 0.5		, summ(i)
		"fstsw %%ax\n"
		"sahf\n"
		"jb end_loop\n"
		"fsubr %%st(0), %%st(2)\n"		//a(i+1)  , E	   , 0.5	 , summ(i) + a(i+1)
		"fldl %[M]\n"					//M	      , a(i+1) , E       , 0.5				 , summ(i+1)
		"fmulp\n"						//M*a(i+1), E      , 0.5	 , summ(i+1)
		"addl $1, %[I]\n"
		"jmp begin_loop\n"

		"end_loop:\n"
		"fstpl %[Ai]\n"
		"fcomp\n"
		"fstpl %[S]\n"
		: [S] "=rm"(summ), [I]"+m"(i), [Ai]"=rm"(ai)
		: [E] "m" (E), [M]"m"(multiplier)
		: "cc"
	);

	cout << "Assembler result: " << endl;
	cout << setprecision(15) << "Summ = " << summ << " for " << "i = " << i << " and " << "|a_i| = " << ai << endl;

	i = 0, ai = 1, summ = 0;

	while (true)
	{
		if (ai < E)
			break;
		summ = summ + ai;
		ai = ai * multiplier;
		i += 1;
		if (ai < E)
			break;
		summ = summ - ai;
		ai = ai * multiplier;
		i += 1;
	}

	cout << "C++ result (check): " << endl;
	cout << setprecision(15) << "Summ = " << summ << " for " << "i = " << i << " and " << "|a_i| = " << ai << endl;

	return 0;
}