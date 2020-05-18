#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double average = round(((double)image[i][j].rgbtRed + (double)image[i][j].rgbtGreen + (double)image[i][j].rgbtBlue) / (double)3);

            image[i][j].rgbtRed = (int)average;
            image[i][j].rgbtGreen = (int)average;
            image[i][j].rgbtBlue = (int)average;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap bytes horizontally
            BYTE tempRedByte = image[i][j].rgbtRed;
            BYTE tempGreenByte = image[i][j].rgbtGreen;
            BYTE tempBlueByte = image[i][j].rgbtBlue;

            int oppositeIndex = width - j - 1;
            image[i][j].rgbtRed = image[i][oppositeIndex].rgbtRed;
            image[i][j].rgbtGreen = image[i][oppositeIndex].rgbtGreen;
            image[i][j].rgbtBlue = image[i][oppositeIndex].rgbtBlue;

            image[i][oppositeIndex].rgbtRed = tempRedByte;
            image[i][oppositeIndex].rgbtGreen = tempGreenByte;
            image[i][oppositeIndex].rgbtBlue = tempBlueByte;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurredImage[height][width];

    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            // Get average of all neighboring values
            int pixelCount = 0;
            int redSum = 0;
            int greenSum = 0;
            int blueSum = 0;
            for (int ro = -1; ro <= 1; ro++)
            {
                for (int co = -1; co <= 1; co++)
                {
                    int rOffset = r + ro;
                    int cOffset = c + co;

                    // Points to a space that exists?
                    if (rOffset >= 0 && rOffset < height && cOffset >= 0 && cOffset < width)
                    {
                        int red = image[rOffset][cOffset].rgbtRed;
                        int green = image[rOffset][cOffset].rgbtGreen;
                        int blue = image[rOffset][cOffset].rgbtBlue;
                        redSum += red;
                        greenSum += green;
                        blueSum += blue;
                        pixelCount++;
                    }
                }
            }

            // Record blurred image
            int redAvg = round((double)redSum / (double)pixelCount);
            int greenAvg = round((double)greenSum / (double)pixelCount);
            int blueAvg = round((double)blueSum / (double)pixelCount);

            blurredImage[r][c].rgbtRed = redAvg;
            blurredImage[r][c].rgbtGreen = greenAvg;
            blurredImage[r][c].rgbtBlue = blueAvg;
        }
    }

    // Now convert to the blurred image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = blurredImage[i][j].rgbtRed;
            image[i][j].rgbtGreen = blurredImage[i][j].rgbtGreen;
            image[i][j].rgbtBlue = blurredImage[i][j].rgbtBlue;
        }
    }

    return;
}

// Computes an edge result
int edge_result(int sumX, int sumY)
{
    int result = (double)round(sqrt(pow(sumX, 2) + pow(sumY, 2)));
    if (result > 255)
    {
        result = 255;
    }

    return result;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{ -1, 0, 1 },
        { -2, 0, 2 },
        { -1, 0, 1 }
    };
    int Gy[3][3] = {{ -1, -2, -1 },
        { 0, 0, 0 },
        { 1, 2, 1 }
    };
    RGBTRIPLE moddedImage[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Get average of all neighboring values
            int redSumX = 0;
            int greenSumX = 0;
            int blueSumX = 0;
            int redSumY = 0;
            int greenSumY = 0;
            int blueSumY = 0;
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    // Points to a space that exists?
                    if (i + k >= 0 && i + k < height && j + l >= 0 && j + l < width)
                    {
                        redSumX += image[i + k][j + l].rgbtRed * Gx[k + 1][l + 1];
                        redSumY += image[i + k][j + l].rgbtRed * Gy[k + 1][l + 1];
                        greenSumX += image[i + k][j + l].rgbtGreen * Gx[k + 1][l + 1];
                        greenSumY += image[i + k][j + l].rgbtGreen * Gy[k + 1][l + 1];
                        blueSumX += image[i + k][j + l].rgbtBlue * Gx[k + 1][l + 1];
                        blueSumY += image[i + k][j + l].rgbtBlue * Gy[k + 1][l + 1];
                    }
                }
            }

            moddedImage[i][j].rgbtRed = edge_result(redSumX, redSumY);
            moddedImage[i][j].rgbtGreen = edge_result(greenSumX, greenSumY);
            moddedImage[i][j].rgbtBlue = edge_result(blueSumX, blueSumY);
        }
    }

    // Now convert to the blurred image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = moddedImage[i][j].rgbtBlue;
            image[i][j].rgbtGreen = moddedImage[i][j].rgbtGreen;
            image[i][j].rgbtRed = moddedImage[i][j].rgbtRed;
        }
    }

    return;
}
