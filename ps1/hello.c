#include <stdio.h>
#include <cs50.h>

// Asks for user's name and displays "hello, {name}"
int main(void)
{
    string name = get_string("What is your name?\n");

    printf("hello, %s\n", name);
}