#include<stdio.h>
#include<string.h>
void func()
{
        int *p = NULL;
        memcpy(p, "test", 4);
}

int main()
{
        func();
        return 0;
}
