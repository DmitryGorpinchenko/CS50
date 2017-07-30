#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char encrypt(char c, int key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("You entered no or more that one key!\n");
        return 1;
    }
    string keyword = argv[1];
    for(int i = 0, n = strlen(keyword); i < n; i++)
    {
        if (!isalpha(keyword[i]))
        {
            printf("You entered wrong key!\n");
            return 1;
        }
    }
    int len = strlen(keyword);
    int k[len];
    for(int i = 0; i < len; i++)
    {
        if (isupper(keyword[i]))
        {
            k[i] = keyword[i] - 'A';
        }
        else
        {
            k[i] = keyword[i] - 'a';
        } 
    } 
    string plaintext = GetString();
    for (int i = 0, n = strlen(plaintext), m = len, j = 0; i < n; i++)
    {
        if (isalpha(plaintext[i]))
        {
            printf("%c", encrypt(plaintext[i], k[j]));
            j = (j + 1) % m;
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}

char encrypt(char c, int k)
{
    if (isupper(c))
    {
        return 'A' + ((c - 'A') + k) % 26;
    } 
    return 'a' + ((c - 'a') + k) % 26;
}
