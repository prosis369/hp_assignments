#include <stdio.h>
#include <string.h>

const int array_size=10;

int main(int argc, char **argv)
{
    int i, j;
    int a[array_size][array_size];
    int b[array_size][array_size];

    // Initialize array using for loops
    for (i = 0; i < array_size; i++)
        for (j = 0; j < array_size; j++)
            a[i][j] = 5;

    // Set even rows using for loop
    for (i = 0; i < array_size; i += 2)
    {
        for (j = 0; j < array_size; j++)
            a[i][j] = 12;
    }

    b[:][:] = 5;

    // Set elements of even rows to 12
    b[0:5:2][:] = 12;

    // Verify the results - The arrays should be identical
    if (0 == memcmp(a, b, sizeof(a)))
        printf("Success\n");
    else
        printf("Failed\n");

    return 0;
}