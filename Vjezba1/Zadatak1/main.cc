#include <stdio.h>

int Calculation(int a, int b)
{
if(a > b)
return a - b;
else
return b - a;
}
 //stoe

void PrintResult(int res)
{
printf("Result: %d\n", res);
}



int main()
{
int a = 5;
int b = 4;
int c;

Calculation(a,  b);

PrintResult( c);

return 0;
}
