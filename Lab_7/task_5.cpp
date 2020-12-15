#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;
int main()
{

    int N, prev = 1;
    while (true)
    {
        cout << "Enter N: ";
        cin >> N;
        if (N >= 2)
            break;
        else
            cout << "Ooopsie, try one more time." << endl;
    }
    int* ptrArr = new int[N];

    asm(
        "push %%eax\n\t"
        "push %%ebx\n\t"
        "push %%ecx\n\t"

        "movl %[ptrArr],%%ecx\n\t"
        "movl $0, %%eax\n\t"
        "movl $1, %%ebx\n\t"

        "jmp trivial_case\n"

        "begin_loop:\n\t"

        "cmpl %[N],%%eax\n\t"
        "je end_loop\n\t"
        "push %%eax\n"
        "movl %%ebx, %%eax\n\t"
        "addl %[P],%%ebx\n\t"
        "movl %%eax, %[P]\n\t"
        "pop %%eax\n"
        "movl %%ebx, (%%ecx,%%eax,4)\n\t"
        "incl %%eax\n\t"
        "jmp begin_loop\n\t"

        "trivial_case:\n"

        "movl %%ebx, (%%ecx,%%eax,4)\n\t"
        "incl %%eax\n\t"
        "movl %%ebx, (%%ecx,%%eax,4)\n\t"
        "incl %%eax\n\t"
        "jmp begin_loop\n\t"

        "end_loop:\n\t"

        "pop %%ecx\n\t"
        "pop %%ebx\n\t"
        "pop %%eax\n\t"
        : 
        : [P]"m"(prev), [N]"m"(N), [ptrArr]"m"(ptrArr)
        : "cc"
    );
    cout << setw(10);
    for (int i = 0; i < N; i++)
        cout << setw(10) << &ptrArr[i];
    cout << endl;
    for (int i = 0; i < N; i++)
        cout << setw(10) << ptrArr[i];
    cout << endl;
    delete[] ptrArr;
    return 0;
}