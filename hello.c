#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Getting the name of the person
    string name = get_string("What's your name?\n");
    //Printing the person's name
    printf("hello, %s\n", name);
}
