#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
	int N = 10, min = 0;
	int arr[N] = {};
	int *ptr = arr;
	
	srand(time(NULL));
	for (int i = 0; i < N; i++)
	{
		arr[i] = rand();
		cout << arr[i] << " ";
	}
	cout << endl;


asm (
		"push %%eax\n"
		"push %%ebx\n"
		"push %%ecx\n"
		"movl $1, %%eax\n"
		"movl %[ptr], %%ebx\n"
		"movl (%%ebx), %%ebx\n"
		"Loop:\n"
		"cmpl %[N], %%eax\n"
		"je End\n"
		"movl %[ptr], %%ecx\n"
		"leal (%%ecx, %%eax, 4), %%ecx\n"
		"movl (%%ecx),%%ecx\n"
		"cmpl %%ebx, %%ecx\n"
		"jnbe Func1\n"
		"movl %%ecx, %%ebx\n"
		"Func1:\n"
		"incl %%eax\n"
		"jmp Loop\n"
		"End:\n"
		"movl %%ebx, %[min]\n"
		"pop %%ecx\n"
		"pop %%ebx\n"
		"pop %%eax\n"
		: [min]"+m" (min)
		: [ptr]"m" (ptr), [N]"m"(N)
		: "cc"
		);

cout << "Minimum: " << min;
delete[] ptr;

return 0;
}
