#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <cmath> 

using namespace std;

int main()
{
	const volatile double a = 0.9;
	double x, z, cres;
	cout << "Entex x: ";
	cin >> x;
	cout << endl;

	asm(								//      st(0),			 st(1),			 st(2)
		"fldl  %[A]\n"					//����: A
		"fldl  %[x]\n"					//����: x,				 A
		"fldl  %[x]\n"					//����: x,				 x,				 A
		"fmul  %%st(1), %%st(0)\n"		//����: x*x,			 x,				 x
		"fmulp %%st(0), %%st(2)\n"		//����: x,				 A*x*x
		"faddp %%st(0), %%st(1)\n"		//����: x + A*x*x
		"fcos\n"						//����: cos(x + A*x*x)
		"fstpl %[z]\n"					//����: ����

		:[z]"=m"(z)
		:[x]"m"(x), [A]"m"(a)
		:"cc"
	);

	cres = cos(x + 0.9 * x * x);

	cout << setprecision(15);
	cout << "cos(" << x << " + " << a << " * " << x << "*" << x << ") = \t\t" << z << endl;
	cout << "Calcutated by C++ result: \t" << cres << endl;
	return 0;
}