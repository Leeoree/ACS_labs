#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

extern "C" int task_1_func(int x);

int main()
{
    int obj;
    srand(time(NULL));
    for (int i = 0; i < 10; i++)
    {
        if (i % 2 == 0)
            obj = rand() % 20;
        else
            obj = (-1) * rand() % 20;
        printf("%d mod4 - %d = %d\n", obj, obj, task_1_func(obj));
    }

    return 0;
}