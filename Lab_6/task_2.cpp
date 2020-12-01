#include <stdlib.h>
#include <iostream>

using namespace std;

int main()
{
	double x, y, res, j;
	const volatile double a = -3.0, b = 13.0;
	cout << "Enter x: ";
	cin >> x;
	cout << endl;

	asm(
		"fldl %[x]\n"
		"fldl %[B]\n"//13, x
		"fcom\n" // 13 ? x
		"fstsw %%ax\n"
		"sahf\n"
		//???? сравнить x с st(0) и извдечь из стека st(0)
		"jnb func2\n" //13 > x
		"jb func1\n" // 13 <= x




		"func1:\n"// 13, x
		"fstp %[j]\n" // x
		"fld1\n" // 1, x
		"faddp %%st(0), %%st(1)\n"// x+1
		"fstpl %[res]\n"
		"jmp end\n"

		"func2:\n"// 13, x
		"fstp %[j]\n" // x
		"fldl %[A]\n" //-3, x
		"fxch\n" // x, -3
		"fdiv %%st(1)\n" //x/-3, x

		"fxch\n" // x, x/3
		"fstp %[j]\n" // x/3

		"fld1\n" // 1, x/3
		"faddp %%st(0), %%st(1)\n" //x/3+1 
		"fstpl %[res]\n"
		"jmp end\n"

		"end:\n"
		: [res] "=m"(res), [j]"=m"(j)
		: [A] "m"(a), [B]"m"(b), [x]"m"(x)
		: "cc"
	);
	cout << res << endl;
	return 0;
}




