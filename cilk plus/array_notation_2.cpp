#include 
#include 

const int array_size=10;

int main(int argc, char **argv)
{
    int a[array_size];
    const char *loop_results[array_size];
    const char *an_results[array_size];

    // Initialize array using for loop
    for (int i = 0; i < array_size; i++)
        a[i] = i;

    // Check for 5 using a for loop
    printf ("Checking using for loop:\n");
    for (int i = 0; i < array_size; i++)
    {
        if (5 == a[i])
            loop_results[i] = "Matched";
        else
            loop_results[i] = "Not Matched";
    }

    // Check for 5 using Array Notation
    printf ("\nChecking using Array Notation:\n");
    if (5 == a[:])
        an_results[:] = "Matched";
    else
        an_results[:] = "Not Matched";

    // Verify the results
    bool success = true;
    for (int i = 0; i < array_size; i++)
    {
        if (strcmp(loop_results[i], an_results[i]))
            success = false;
    }

    if (success)
        printf("match\n");
    else
        printf("differ!\n");

    return 0;
}