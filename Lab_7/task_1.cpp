#include <iostream>

using namespace std;

int main()
{
    int a[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };


    cout << "Array element size: " << sizeof(a[0]) << endl;
    cout << "Addresses difference: " << a+1 << " - " << a << " = 4 " << endl;
    cout << "Addresses difference between other elements: " << a+5 << " - " << a+4 << " =4\n";
    cout << "Array size: " << sizeof(a) << endl;
    cout << "a[7] adress: " << a+7 << ",  a[7] = " << *(a+7) << endl;


    return 0;
}