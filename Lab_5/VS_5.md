# <div align="center"> Лабораторная работа №5 <br> Программирование FPU
    
<div align="right"> ПМ-31 <br> Нанкевич Иван <br> Рысина Серафима <br> Вариант 7

### Задание 1. 
Разработайте программу на языке C++, выполняющую вычисления
над вещественными числами одинарной точности (тип float).
Проверьте, что программа действительно работает с операндами одинарной
точности, а не приводит к типу float окончательный результат.

1. Найти разность 𝑎 − 𝑏 для различных значений 𝑎, 𝑏:<br>
𝑎 = 123456789; 𝑏 = 123456788,<br>
𝑎 = 123456788; 𝑏 = 123456787<br> <br> 

Сравните полученный результат с теоретическим. Объясните результат.<br>
Измените тип операндов на double. Объясните результат.<br> 


```C++
#include <stdlib.h>
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	float af1 = 123456789, bf1 = 123456788, af2 = 123456788, bf2 = 123456787, rf1, rf2;
	double ad1 = 123456789, bd1 = 123456788, ad2 = 123456788, bd2 = 123456787, rd1, rd2;

	rf1 = af1 + bf1;
	rf2 = af2 + bf2;
	rd1 = ad1 + bd1;
	rd2 = ad2 + bd2;

	cout << setprecision(9);

	
	cout << "Type float:\n" << af1 << " + " << bf1 << " = " << rf1 << endl 
		<< af2 << " + " << bf2 << " = " << rf2 << endl << endl;  
	
	cout << "Type double:\n" << ad1 << " + " << bd1 << " = " << rd1 << endl 
		<< ad2 << " + " << bd2 << " = " << rd2 << endl << endl;
}

```

**Output**<br> <br>
$ task_1.exe/ <br>
Type float:<br>
123456792 + 123456784 = 246913568<br>
123456784 + 123456784 = 246913568<br>
<br>
Type double:<br>
123456789 + 123456788 = 246913577<br>
123456788 + 123456787 = 246913575<br>


### Задание 2.
Составьте программу calc для вычисления выражения с использованием сопроцессора в соответствии со своим вариантом. <br>
<div align="center"> $\cos(𝑥 + 0.9𝑥^2)$

```C++
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

	asm(								
		"fldl  %[A]\n"					
		"fldl  %[x]\n"					
		"fldl  %[x]\n"					
		"fmul  %%st(1), %%st(0)\n"		
		"fmulp %%st(0), %%st(2)\n"		
		"faddp %%st(0), %%st(1)\n"		
		"fcos\n"						
		"fstpl %[z]\n"					

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


```

**Output** <br><br>
$ task_2.exe/<br>
Entex x: 7<br>
cos(7 + 0.9 * 7*7) =            0.671535248547449<br>
Calcutated by C++ result:       0.671535248547448<br>

$ task_2.exe/<br>
Entex x: -7<br>
cos(-7 + 0.9 * -7*-7) =                 0.8258367804435<br>
Calcutated by C++ result:       0.8258367804435<br>


### Задание 3.
Оформите вычисления из задания 2 как функцию на ассемблере (вещественную от вещественного аргумента 𝑥).

task_3_func.s

```C++
.globl _task_3_func
_task_3_func:
    fldl  4(%esp)
	fldl  12(%esp)
	fldz					
	fadd  %st(1), %st(0)						
	fmul  %st(1), %st(0)
	fmulp %st(0), %st(2)		
	faddp %st(0), %st(1)		
	fcos
	ret
```

task_3_main.cpp

```C++
#include <cstdio>
#include <cstdlib>

using namespace std;

extern "C" double task_3_func(double a, double x);

int main()
{
    double a = 0.9, x = 1;
    printf("cos(%lf + %lf * %lf * %lf) = %.15lf\n", x, x, x, a, task_3_func(a,x));
    return 0;
}
```

**Output**

$ a.exe/ <br>
cos(1.000000 + 1.000000 * 1.000000 * 0.900000) = -0.323289566863503
