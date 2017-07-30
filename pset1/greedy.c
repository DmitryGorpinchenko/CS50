#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    
    float change;
    
    printf("O hai! ");
    
    do 
    {
        printf("How much change is owed?\n");
        change = GetFloat();
    } 
    while(change < 0);
    
    int cents = (int) round(change * 100), coins = 0;
    
    while(cents > 0) 
    {
        if (cents - 25 >= 0) 
        {
            cents -= 25;
        } 
        else if(cents - 10 >= 0)
        {
            cents -= 10;
        }
        else if(cents - 5 >= 0)
        {
            cents -= 5;
        }
        else if(cents - 1 >= 0)
        {
            cents -= 1;
        }
        coins++;
    }
    printf("%d\n", coins);
}
