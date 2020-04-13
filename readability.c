#include <stdio.h>
#include <cs50.h>
//The use of isaplha() from ctype.h made my day a whole lot easier!
#include <ctype.h>

//Calling the functions that were written outside the main
int letter_count(string s);
int word_count(string s);
int sentence_count(string s);

int main(void)
{
    string text = get_string("Text: ");
    float w = word_count(text);
    //Using the rule of three to determine the number of letter per 100 words and sentences per 100 words
    float L = (letter_count(text) * 100) / w;
    float S = (sentence_count(text) * 100) / w;
    float index = 0.0588 * L - 0.296 * S - 15.8;

    //I've used 0.5 as the comparisor to make sure that floats between 0.5 and 0.999... returns Before Grade 1
    if (index < 0.5)
    {
        printf("Before Grade 1\n");
    }
    //I've used 15.5 as the comparisor to make sure that floats between 15.5 and 15.999... returns Grade 16+
    else if (index >= 15.5)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", index);
    }
}

//I've created functions apart from the main part for aesthetic purposes

int letter_count(string s)
{
    int letters = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        //If the carachter is aplhabetical, count 1 more letter!
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
        //If the carachter is a space, count 1 more word!
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
        //If the carachter is a period, a exclamation mark or a question mark, count 1 more word!
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}