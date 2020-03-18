#include <stdio.h>
#include <stdlib.h>

int main()
{
int n,a;
scanf("%d",&n);
do
 {
 a=n%10;
 n=n/10;
 }
 while (a!=3 && n!=0);
 if (a == 3);
printf("yes");
return 0;
}
