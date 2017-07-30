#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string name = GetString();
    bool new_word = true;
    for(int i = 0, n = strlen(name); i < n; i++)
    {
        if(name[i] == ' ')
        {
            new_word = true;
        }
        else if(new_word)
        {
            printf("%c", toupper(name[i]));
            new_word = false;
        } 
    }
    printf("\n");
}
