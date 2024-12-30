#include <stdio.h>

int main()
{
    char userInput[14] = { 'a','a','b','b','b','b','b','a', 'c', 'x', 'y', 'b', 'z', 'z'};
    char toCount[6] = { 'a', 'b', 'c', 'x', 'y', 'z' };
    
    /*
    Count the number of times each character from toCount
    occurs in userInput and print it
    */
   int i;
   int j;
   for (i=0; i<6; i++)
   {
        int num = 0;
        for (j=0; j<14; j++)
            if (toCount[i] == userInput[j])
                num++;
        printf("%c occurs %d times\n", toCount[i], num);
   }
}