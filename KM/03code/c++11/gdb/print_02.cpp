#include <stdio.h>

int func1(int a)
{
  int b = 1;
  return b * a;
}

int func2(int a)
{
  int b = 2;
  return b * func1(a);
}

int func3(int a)
{
  int b = 3;
  return b * func2(a);
}

int main(void)
{
  printf("%d\n", func3(10));
  return 0;
}