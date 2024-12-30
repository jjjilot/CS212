#include <stdio.h>
#include <string.h>

int main()
{
    int i, max;
    printf("Enter Number to Fizz and Buzz: ");
    scanf("%d", &max);
    for (i=1; i<=max; i++)
    {
        if (i%3!=0 && i%5!=0)
            printf("%d", i);
        else if (i%3==0)
            printf("Fizz");
        if (i%5==0)
            printf("Buzz");
        printf("\n");
    }
}