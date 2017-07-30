#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char encrypt(char c, int k);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("You entered no key\n");
        return 1;
    }
    int k = atoi(argv[1]) % 26;
    string plaintext = GetString();
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        printf("%c", encrypt(plaintext[i], k));
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
    if (islower(c))
    {
        return 'a' + ((c - 'a') + k) % 26;
    }
    return c;
}
