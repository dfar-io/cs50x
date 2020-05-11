#include <stdio.h>
#include <cs50.h>

// Creates "Mario-like" pyramid based on user-provided height.
int main(void)
{
    int height = 0;
    const int minHeight = 1;
    const int maxHeight = 8;

    bool hasValidHeight = false;

    // Get valid height from user
    while (!hasValidHeight)
    {
        height = get_int("Height?: ");

        // Check if height is within range
        if (minHeight <= height && height <= maxHeight)
        {
            hasValidHeight = true;
        }
    }

    // Construct pyramid
    for (int row = 1; row <= height; row++)
    {
        //Generate left side
        for (int col = 1; col <= height; col++)
        {
            if (height - row >= col)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }

        // Generate gap
        printf("  ");

        // Generate right side
        for (int col = 1; col <= height; col++)
        {
            if (row >= col)
            {
                printf("#");
            }
            else
            {
                // Exit out of loop to remove unneeded whitespace
                continue;
            }
        }

        // Next line
        printf("\n");
    }
}