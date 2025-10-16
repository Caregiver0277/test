#include <stdio.h>
/* Unser erstes Programm */
int main(void)
{
int year = 2017;
printf("Hello World in %d!\n", year);
while (year <= 2019)
{
printf("Hello World in %d!\n", year);
year = year+1;
}
return 0;
}
