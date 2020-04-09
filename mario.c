#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    for (int i = 0; i < n; i++)
    {
        //To print the inicial blank spaces
        for (int j = 0; j < n - i - 1; j++)
        {
            printf(" ");
        }
        //To print the left hash marks
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        //To print spacing between collumns
        printf("  ");
        //To print the right hash marks
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
