#include <cs50.h>
#include <stdio.h>

#define TEN_12 1000000000000
#define TEN_13 10000000000000
#define TEN_14 100000000000000
#define TEN_15 1000000000000000

bool is_amex(long long num);

bool is_mc(long long num);

bool is_visa(long long num);

bool check(long long num);

int main(void)
{
    long long num;
    
    printf("Number: ");
    num = GetLongLong();
    
    if (is_amex(num)) 
    {
        printf("AMEX\n");  
    } 
    else if (is_mc(num)) 
    {
        printf("MASTERCARD\n");  
    } 
    else if (is_visa(num)) 
    {
        printf("VISA\n");  
    }
    else 
    {
        printf("INVALID\n");
    }
    
    return 0;    
}

bool check(long long num)
{
    int sum = 0;
    long long temp = num / 10;
    while(temp > 0) 
    {
        int prod = 2 * (temp % 10);
        sum = sum + (prod % 10) + (prod / 10) % 10;
        temp /= 100;
    }
    temp = num;
    while(temp > 0) 
    {
        sum += (temp % 10);
        temp /= 100;
    }
    if (sum % 10 == 0) 
    {
        return true;
    }
    
    return false;
}

bool is_amex(long long num)
{
    if (num / TEN_13 == 34 || num / TEN_13 == 37) 
    {
        return check(num);
    }
    
    return false;
}


bool is_mc(long long num)
{
    if (num / TEN_14 >= 51 && num / TEN_14 <= 55) 
    {
        return check(num);
    }
    
    return false;
}

bool is_visa(long long num)
{
    if (num / TEN_12 == 4 || num / TEN_15 == 4) 
    {
        return check(num);
    }
    
    return false;
}
