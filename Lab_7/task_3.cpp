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
    int N = 3;

    Arrstr B[N] = {};
    for (int i = 0; i < N; i++)
    {
        B[i].key = i;
        B[i].value = (rand()%100)*1.3;
        cout << "Key: " << B[i].key << "    Value:  "<< B[i].value << endl;
    }

    cout << "\nStructure size: " << sizeof(B[0]) << endl;
    cout << "Key size: " << sizeof(B[0].key) << endl;
    cout << "Value size: " << sizeof(B[0].value) << endl;
    cout << "Addresses difference between two keys: " << &B[1].key << " - " << &B[0].key << " = 16"<< endl;
    cout << "Addresses difference between two values: " << &B[1].value << " - " << &B[0].value << " = 16"<< endl;
    cout << "Array size: " << N << " * 16 = "<< sizeof(B) << endl;
    cout << "B[2].key adress: " << &(B[0+2]).key << ",  B[2].key:  " << (B[0+2]).key << endl;

    return 0;

}