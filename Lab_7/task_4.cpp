#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Arrstr
{
    int key;
    double value;
};

int main()
{
    srand(time(NULL));
    int N = 10, key;
    double min = 0;

    Arrstr B[N] = {};
    Arrstr *ptr = B;
    for (int i = 0; i < N; i++)
    {
        B[i].key = i%2;
        B[i].value = (rand()%100)*1.3+1;
        cout << "Key: " << B[i].key << "    Value:  "<< B[i].value << endl;
    }


    cout << "\nEnter key: " << endl; 
    cin >> key; 
    
asm ( 
		"push %%eax\n" 
		"push %%ebx\n" 
		"push %%ecx\n" 
		"movl $0, %%eax\n" 
		"Loop:\n" 
		"cmpl %[N], %%eax\n" 
		"je End\n" 
		"movl %[ptr], %%ecx\n" 
		"leal (%%ecx, %%eax, 8), %%ecx\n" 
		"leal (%%ecx, %%eax, 8), %%ecx\n" 
		"movl (%%ecx),%%ecx\n" 
		"cmpl %[KEY], %%ecx\n" 
		"je Point\n" 
		"incl %%eax\n" 
		"jmp Loop\n" 
		"Point:\n" 
		"movl %[ptr], %%ecx\n" 
		"leal (%%ecx, %%eax, 8), %%ecx\n" 
		"leal 8(%%ecx, %%eax, 8), %%ecx\n" 
		"fldl (%%ecx)\n" 
		"incl %%eax\n" 
		"Minimum:\n" 
		"cmpl %[N], %%eax\n" 
		"je Reset\n" 
		"movl %[ptr], %%ecx\n" 
		"leal (%%ecx, %%eax, 8), %%ecx\n" 
		"leal (%%ecx, %%eax, 8), %%ecx\n" 
		"movl (%%ecx),%%ecx\n" 
		"cmpl %[KEY], %%ecx\n" 
		"jne Reset1\n" 
		"movl %[ptr], %%ecx\n" 
		"leal (%%ecx, %%eax, 8), %%ecx\n" 
		"leal 8(%%ecx, %%eax, 8), %%ecx\n" 
		"fldl (%%ecx)\n" 
		"push %%ax\n" 
		"fcom\n" 
		"fnstsw\n" 
		"sahf\n" 
		"pop %%ax\n" 
		"jc Newminimum\n" 
		"fstpl %[min]\n" 
		"jmp Reset1\n" 
		"Newminimum:\n" 
		"fxch\n" 
		"fstpl %[min]\n" 
		"Reset1:\n" 
		"incl %%eax\n" 
		"jmp Minimum\n" 
		"Reset:\n" 
		"fstpl %[min]\n" 
		"End:\n" 
		"pop %%ecx\n" 
		"pop %%ebx\n" 
		"pop %%eax\n" 
		: [min]"+m" (min) 
		: [ptr]"m"(ptr), [N]"m"(N), [KEY]"m"(key) 
		: "cc" 
		); 

		if ( min != 0) 
			cout << "Minimum:  " << min << endl;
		else
			cout << "Wrong key" << endl;
		
		
		delete [] ptr; 
		return 0; 
		}		