#include <stdlib.h>
#include <stdio.h>
void func()
{
 //只申请内存而不释放
    void *p=malloc(sizeof(int));
}
int main()
{
    func();
    getchar();
    return 0;
}