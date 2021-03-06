#include <stdio.h>

void PrintResult(int res)
{
printf("Result: %d\n", res);
}


int main()
{
int a = 5;
int b = 4;
int c;
if(a > b)
c = a - b;
else
c = b - a;
PrintResult( c);
return 0;
}
