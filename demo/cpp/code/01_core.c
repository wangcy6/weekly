#include<stdio.h>
void print(int* p)
{
    printf("%d\n", *p);
}
int main()
{
    int *p = NULL;
    //*p = 0;
    print(p);
    return 0;
}
