#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>


// Uses Coleman-Liau index to determine complexity of a provided passage.
int main(void)
{
    string text = get_string("Text: ");

    int letterCount = 0;
    int sentenceCount = 0;
    // assumes at least one word is passed in
    int wordCount = 1;

    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentenceCount++;
        }
        else if (text[i] == ' ')
        {
            wordCount++;
        }
        else if (text[i] != ',' && text[i] != '\'')
        {
            letterCount++;
        }
    }

    // Now, use formula to determine score
    float lettersPer100Words = ((float)letterCount / (float)wordCount) * 100;
    float sentencesPer100Words = ((float)sentenceCount / (float)wordCount) * 100;
    float score = 0.0588 * lettersPer100Words - 0.296 * sentencesPer100Words - 15.8;

    // Print the grade level to terminal
    int convertedScore = (int)roundf(score);
    if (convertedScore <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (convertedScore >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", convertedScore);
    }
}