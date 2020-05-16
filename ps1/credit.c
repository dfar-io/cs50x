#include <stdio.h>
#include <cs50.h>
#include <math.h>

// Gets the digit sum of a passed in value
// eg. digitSum(12) = 1 + 2 = 3
int digitSum(int value)
{
    int sum = 0;
    int functionValue = value;

    while (functionValue > 0)
    {
        int result = functionValue % 10;
        sum += result;
        functionValue = functionValue / 10;
    }

    return sum;
}

// Gets a digit based on the position requested, starting from the left
int digitByPosition(long value, int position)
{
    int valueLength = log10(value);
    int result = value / pow(10, valueLength - position);

    while (result > 10)
    {
        result %= 10;
    }

    return result;
}

// Returns an integer representing the brand
// 1 - VISA
// 2 - AMEX
// 3 - MASTERCARD
// -1 - INVALID
int getBrand(long ccNumber)
{
    int ccNumberLength = log10(ccNumber) + 1;

    if ((ccNumberLength == 13 || ccNumberLength == 16) && digitByPosition(ccNumber, 0) == 4)
    {
        return 1;
    }

    if (ccNumberLength == 15 && digitByPosition(ccNumber, 0) == 3 && (digitByPosition(ccNumber, 1) == 4
            || digitByPosition(ccNumber, 1) == 7))
    {
        return 2;
    }

    if (ccNumberLength == 16 && digitByPosition(ccNumber, 0) == 5 && (digitByPosition(ccNumber, 1) == 1
            || digitByPosition(ccNumber, 1) == 2
            || digitByPosition(ccNumber, 1) == 3
            || digitByPosition(ccNumber, 1) == 4
            || digitByPosition(ccNumber, 1) == 5))
    {
        return 3;
    }

    return -1;
}

// Uses Luhn’s Algorithm to check if the checksum of a passed in CC number is valid
bool isCheckSumValid(long ccNumber)
{
    bool isOdd = true;
    int sum = 0;
    long functionCcNumber = ccNumber;

    while (functionCcNumber > 0)
    {
        long result = functionCcNumber % 10;
        if (isOdd)
        {
            sum += result;
        }
        else
        {
            sum += digitSum(result * 2);
        }

        isOdd = !isOdd;
        functionCcNumber = functionCcNumber / 10;
    }

    return sum % 10 == 0;
}

// Prints the brand associated to the brand ID provided.
void printBrand(int brand)
{
    if (brand == 1)
    {
        printf("VISA\n");
    }
    if (brand == 2)
    {
        printf("AMEX\n");
    }
    if (brand == 3)
    {
        printf("MASTERCARD\n");
    }
}

int main(void)
{
    long ccNumber = get_long("Number?: ");

    int brand = getBrand(ccNumber);

    if (brand == -1)
    {
        printf("INVALID\n");
        return 0;
    }

    if (!isCheckSumValid(ccNumber))
    {
        printf("INVALID\n");
        return 0;
    }

    printBrand(brand);
    return 0;
}