#include <stdio.h>
#include <cs50.h>

int main(void)
{
    
    int h;
    
    do 
    {
        printf("Height: ");
        h = GetInt();
    } 
    while(h < 0 || h > 23);
    
    for(int i = h; i > 0; i--) 
    {
        for(int j = i - 1; j > 0; j--) 
        {
            printf(" ");
        }
        for(int j = h - i + 2; j > 0; j--) 
        {
            printf("#");
        }
        printf("\n");
    }
}
