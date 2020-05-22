#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t  BYTE;



bool has_jpg_header(BYTE block[512])
{
    // Check if block starts with 0xff, 0xd8, 0xff, and
    // 0xe(0-f)
    return block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (0xe0 <= block[3] && block[3] <= 0xef);
}

// Recovers JPG files from a .raw file provided.
int main(int argc, char *argv[])
{
    // Check if exactly one argument provided
    if (argc != 2)
    {
        printf("Usage: recover <filename>\n");
        return 1;
    }

    // Define block size of 512 bytes
    BYTE block[512];

    // Open the file, failing gracefully if error in file
    FILE *fp = fopen("card.raw", "r");
    if (fp == NULL)
    {
        printf("Error when opening file.\n");
        return 1;
    }

    // Loop through blocks and create JPG files
    int jpg_count = 0;
    FILE *fpw = NULL;
    while (fread(block, sizeof(block), 1, fp))
    {
        if (has_jpg_header(block))
        {
            // Close the existing file write stream
            if (fpw != NULL)
            {
                fclose(fpw);
            }

            // Create file to open
            char filename[0x100];
            snprintf(filename, sizeof(filename), "%03d.jpg", jpg_count);
            fpw = fopen(filename, "w");

            jpg_count++;
        }

        // If a file write stream is open, write to it
        if (fpw != NULL)
        {
            fwrite(block, sizeof(block), 1, fpw);
        }
    }

    // Finish out by closing both file streams
    fclose(fpw);
    fclose(fp);

    return 0;
}
