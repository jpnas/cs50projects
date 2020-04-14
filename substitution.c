#import <stdio.h>
#import <cs50.h>
#import <ctype.h>

int repeated(string s);
char encrypt(char c, string s);

int main(int arcg, string arcv[])
{
    string key = arcv[1];
    //Testing if the user gave more than 1 argument
    if (arcg != 2)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }
    int i;
    //Testing if the user gave non-alphebetic characters
    for (i = 0; key[i] ; i++)
    {
        if (isalpha(key[i]) == 0)
        {
            printf("Key must only contain alphabetic charcacters.\n");
            return 1;
        }
    }
    
    //Testing if there are repeated characters using the funcion created
    if (repeated(key) == 1)
    {
        printf("Key must not cointain repeated characters.\n");
        return 1;
    }
    
    //Testing if the key has 26 characters
    if (i != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    
    string text = get_string("plaintext: ");
    printf("ciphertext: ");
    
    //Substituting characters that are alphabetic for their key correspondence
    for (i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]) != 0)
        {
            printf("%c", encrypt(text[i], key));
        }
        else
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
}


//Funcition that checks if there are repeated characters in the string
int repeated(string s)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        for (int j = i + 1; s[j] != '\0'; j++)
        {
            if (s[i] == s[j])
            {
                return 1;
            }
        }
    }
    return 0;
}

//Function that converts the charcther into the key correspondence
char encrypt(char c, string s)
{
    //For uppercase letters
    for (int u = 65; u < 91; u++)
    {
        if ((int) c == u)
        {
            c = toupper(s[u - 65]);
            return c;
        }
    }
    //For lowercase letters
    for (int l = 97; l < 123; l++)
    {
        if ((int) c == l)
        {
            c = tolower(s[l - 97]);
            return c;
        }
    }
    return c;
}