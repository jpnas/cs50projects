#include <stdio.h>
#include <cs50.h>
#include <ctype.h>

int letter_count(string s);
int word_count(string s);
int sentence_count(string s);

int main(void)
{
    string text = get_string("Text: ");
    float w = word_count(text);
    float L = (letter_count(text) * 100) / w;
    float S = (sentence_count(text) * 100) / w;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 15.5)
    {
        printf("Grade 16+");
    }
    else
    {
    printf("Grade %.0f\n", index);
    }
}

int letter_count(string s)
{
    int letters = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (isalpha(s[i]) != 0)
        {
            letters++;
        }
    }
    return letters;
}


int word_count(string s)
{
    int words = 1;
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == ' ')
        {
            words++;
        }
    }
    return words;
}


int sentence_count(string s)
{
    int sentences = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}