#include <stdio.h>

int main(void)
{
   int n;
   
   do
   {
    printf("Enter Height: ");
    scanf("%i", &n);
   } while (n < 1);

   for(int i = 0; i < n; i++)
   {
    for(int j = i + 1; j < n; j++)
    {
        printf("#");
    }
    printf("\n");
   } 
}