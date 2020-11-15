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