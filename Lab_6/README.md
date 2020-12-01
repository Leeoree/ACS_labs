# <div align="center"> Лабораторная работа №6 <br> Программирование ветвящихся и циклических алгоритмов
    
<div align="right"> ПМ-31 <br> Нанкевич Иван <br> Рысина Серафима <br> Вариант 7

<div align="left">

### Задание 1. 
Вычислите для заданных целых x, y: <br>
<a href="https://www.codecogs.com/eqnedit.php?latex={&space;f(x)&space;=&space;\left\{\begin{matrix}&space;x/2,&space;x&space;\%&space;2=0&space;\\&space;3x&plus;1,&space;x&space;\%&space;2&space;\neq&space;0&space;\end{matrix}\right.&space;}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?{&space;f(x)&space;=&space;\left\{\begin{matrix}&space;x/2,&space;x&space;\%&space;2=0&space;\\&space;3x&plus;1,&space;x&space;\%&space;2&space;\neq&space;0&space;\end{matrix}\right.&space;}" title="{ f(x) = \left\{\begin{matrix} x/2, x \% 2=0 \\ 3x+1, x \% 2 \neq 0 \end{matrix}\right. }" /></a>

```
.data
x: .int 11
printf_format: .string "f(x) = %d\n"

.globl _main
_main:
    movl x, %eax
    and $1, %eax  
    cmpl $0, %eax  
    jg _func
    movl x, %eax
    sar $1, %eax 
    jmp _end  
_func:
    movl x, %eax
    imul $3, %eax
    addl $1, %eax
_end:
    pushl %eax
    pushl $printf_format
    call _printf
    addl $8, %esp
    xor %eax, %eax
    ret
```  

Вывод: <br> x = 11 <br>
$ ./task_1.exe <br>
f(x) = 34

x = 10 <br>
$ ./task_1.exe <br>
f(x) = 5


### Задание 2. 
Вычислите для заданного вещественного x: <br>
<a href="https://www.codecogs.com/eqnedit.php?latex={&space;\left\{\begin{matrix}&space;1-x/3,&space;x<13&space;\\1&plus;x,&space;x&space;\geq&space;13&space;\end{matrix}\right.&space;}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?{&space;\left\{\begin{matrix}&space;1-x/3,&space;x<13&space;\\1&plus;x,&space;x&space;\geq&space;13&space;\end{matrix}\right.&space;}" title="{ \left\{\begin{matrix} 1-x/3, x<13 \\1+x, x \geq 13 \end{matrix}\right. }" /></a>

```C++
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
	"fcom %%st(1)\n" // 13 ? x
	"fstsw %%ax\n"
    "sahf\n"
	"jnbe func2\n" //13 > x
	"jbe func1\n" // 13 <= x
	

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
		: [res]"=m"(res), [j]"=m"(j)
		: [A] "m"(a), [B]"m"(b), [x]"m"(x)
		: "cc"
	);
	cout << res << endl;
	return 0;
}
```
Вывод: <br>

Enter x: 5 <br>
-0.666667


Enter x: 15 <br>
16


### Задание 3.
Задайте с клавиатуры 𝑁 и напечатайте первые 𝑁 членов последовательности (целой).<br>
Числа Фибоначчи: <a href="https://www.codecogs.com/eqnedit.php?latex=\phi&space;_0&space;=&space;\phi&space;_1&space;=&space;1,&space;\phi&space;_{i&plus;1}&space;=&space;\phi&space;_i&space;&plus;&space;\phi&space;_{i-1}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\phi&space;_0&space;=&space;\phi&space;_1&space;=&space;1,&space;\phi&space;_{i&plus;1}&space;=&space;\phi&space;_i&space;&plus;&space;\phi&space;_{i-1}" title="\phi _0 = \phi _1 = 1, \phi _{i+1} = \phi _i + \phi _{i-1}" /></a>
```C++
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
```
Вывод: <br>
$ ./task_3.exe<br>
Enter N: 5<br>
1       1       2       3       5       8


### Задание 4. 
Найдите с заданной точностью 𝜀 сумму ряда (если это возможно).<br>
Если ряд расходится, выведите сообщение об этом.<br>
<a href="https://www.codecogs.com/eqnedit.php?latex=S&space;=&space;\sum_{i&space;=&space;0}^{&space;\infty&space;}&space;({-1})^i\frac{1}{2^i}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?S&space;=&space;\sum_{i&space;=&space;0}^{&space;\infty&space;}&space;({-1})^i\frac{1}{2^i}" title="S = \sum_{i = 0}^{ \infty } ({-1})^i\frac{1}{2^i}" /></a>

```C++
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
		"fadd %%st(0), %%st(2)\n"//a(i)   , E	  , 0.5	    , summ(i-1) + a(i)
		"fldl %[M]\n"					//M	     , a(i)   , E       , 0.5				, summ(i)
		"fmulp\n"						//M*a(i) , E      , 0.5		, summ(i)
		"addl $1, %[I]\n"

		"fcom\n"						//a(i+1) , E	  , 0.5		, summ(i)
		"fstsw %%ax\n"
		"sahf\n"
		"jb end_loop\n"
		"fsubr %%st(0), %%st(2)\n" //a(i+1)  , E	   , 0.5 , summ(i) + a(i+1)
		"fldl %[M]\n"					//M	      , a(i+1) , E       , 0.5				 , summ(i+1)
		"fmulp\n"				//M*a(i+1), E      , 0.5	 , summ(i+1)
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
```
Вывод: 
<br><br>
Enter E: 0.05<br>
Assembler result:<br>
Summ = 0.6875 for i = 5 and |a_i| = 0.03125<br>
C++ result (check):<br>
Summ = 0.6875 for i = 5 and |a_i| = 0.03125


### Задание 5.
Реализуйте умножение двух целых чисел без
знака (𝑥 · 𝑦) «в столбик» (то есть не как сумму 𝑥 + . . . + 𝑥 
y раз), не используя mul/imul и команды сопроцессора.
```C++
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
```
Вывод:

Enter x: 3 <br>
Enter y: 7 <br>
3 * 7 = 21

