#include <stdio.h>

int add(int a, int b);

int main(void)
{
    int x;
    int y;

    printf("Type a number for x: ");
    scanf("%i", &x);

    printf("Type a number for y: ");
    scanf("%i", &y);

    printf("%i\n", add(x, y));
}

int add(int a, int b)
{
    return a + b;
}