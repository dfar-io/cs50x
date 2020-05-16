#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

// Converts a character based on a key provided, using correct casing
char convertCharacter(char character, char *key)
{
    const int UPPER_ASCII_DIFF = 65;
    const int LOWER_ASCII_DIFF = 97;
    int characterAsciiValue = (int)character;

    int asciiDifference = isupper(character) ? UPPER_ASCII_DIFF : LOWER_ASCII_DIFF;
    char newCharacter = key[characterAsciiValue - asciiDifference];

    if (isupper(character) && islower(newCharacter))
    {
        newCharacter = toupper(newCharacter);
    }
    else if (islower(character) && isupper(newCharacter))
    {
        newCharacter = tolower(newCharacter);
    }

    return newCharacter;
}

// Allows for providing a key to encrypt a provided plaintext
int main(int argc, string argv[])
{
    // Verify correct usage
    if (argc != 2)
    {
        printf("Usage: ./substitution key");
        return 1;
    }

    // Check that key is correct length
    string key = argv[1];
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.");
        return 1;
    }

    // Verify key
    for (int i = 0; i < strlen(key); i++)
    {
        char character = key[i];
        if (!isalpha(key[i]))
        {
            printf("Key contains invalid character %c.", character);
            return 1;
        }

        for (int j = i + 1; j < strlen(key); j++)
        {
            if (tolower(character) == tolower(key[j]))
            {
                printf("Key contains duplicate character %c.", character);
                return 1;
            }
        }
    }

    // Get plaintext from user
    string plaintext = get_string("plaintext: ");
    
    // Print out ciphertext
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        char character = plaintext[i];
        if (isalpha(character))
        {
            character = convertCharacter(character, key);
        }
        printf("%c", character);
    }

    printf("\n");
    return 0;
}