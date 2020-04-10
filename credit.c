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
    //Extracting the numbers for the pararell sums
    while (credit1 > 1)
    {
        //Getting the last number
        sum1 = sum1 + credit1 % 10;
        //Deleting the last number
        credit1 = (credit1 - credit1 % 10) / 10;
        //Getting the second-to-last number and multiplying by 2
        other = (credit1 % 10) * 2;
        //Adding the numbers if after multiplying by 2, it becomes double digit
        while (other >= 1)
        {
            sum2 = sum2 + other % 10;
            other = (other - other % 10) / 10;
        }
        //Deleting the last number again
        credit1 = (credit1 - credit1 % 10) / 10;
    }
    //Testing if the last digit of the sum is different from zero
    if ((sum1 + sum2) % 10 != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        //Now the last digit will be removed until we got the first two numbers
        while (credit2 > 100)
        {
            credit2 = (credit2 - credit2 % 10) / 10;
        }
        //Testing if the card number has 15 digits
        if (credit < pow(10, 15) && credit >= pow(10, 14))
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
        //Testing if the card number has 16 digits
        else if (credit < pow(10, 16) && credit >= pow(10, 15))
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
        //Testing if the card number has 13 digits
        else if (credit < pow(10, 13) && credit >= pow(10, 12))
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
