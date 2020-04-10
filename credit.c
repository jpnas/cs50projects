#import <cs50.h>
#import <stdio.h>
#import <math.h>

int main(void)
{
    long credit = get_long("Number: ");
    long credit1 = credit;
    long credit2 = credit;
    int sum1 = 0;
    int sum2 = 0;
    int other;
    while (credit1>1)
    {
       sum1 = sum1 + credit1 % 10;
       credit1 = (credit1 - credit1 % 10)/10;
       
       other = (credit1 % 10) * 2;
       while (other>=1)
       {
           sum2 = sum2 + other % 10;
           other = (other - other % 10)/10;
       }
        credit1 = (credit1 - credit1 % 10)/10;
    }
    if ((sum1 + sum2) % 10 != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        while (credit2 > 100)
            {
                credit2 = (credit2 - credit2 % 10)/10;
            }
        if (credit < pow(10,15) && credit >= pow(10,14))
        {
            if (credit2 == 34 || credit2 == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (credit < pow(10,16) && credit >= pow(10,15))
        {
            if (credit2 >= 51 && credit2 <= 55)
            {
                printf("MASTERCARD\n");
            }
            else if (credit2 > 39 && credit2 < 50)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }   
        else if (credit < pow(10,13) && credit >= pow(10,12))
        {
            if (credit2 > 39 || credit2 < 50)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
}
