#include "typedefs.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

/* Tests:
9 6 5 3 7 8
7 3 6 8 5
*/

// Echo flag for debugging purposes, shows the sorting and searching steps on console.
// Set to on to show steps, off to hide them.
enum boolean
{
    off,
    on
} echo = off;

// This function prints the given array with special notation for specific elements
// If notation is not required, value can be set to -1.
void special_arr_print(uint32_t *arr, uint8_t size, int special_element_1, int special_element_2)
{
    for (int i = 0; i < size; i++)
    {
        if (i == special_element_1)
            printf("(");
        else if (i == special_element_2)
            printf("[");
        else
            printf(" ");

        printf("%d", arr[i]);

        if (i == special_element_1)
            printf(")");
        else if (i == special_element_2)
            printf("]");
        else
            printf(" ");

        printf(" ");
    }
    printf("\n");
}

void insertion_sort(uint32_t *arr, uint8_t size)
{
    if (echo)
        printf("\nSorting...\n");

    uint32_t temp; // variable to be used temporarily for insertion purposes.

    // For every element after the first one...
    for (int i = 1; i < size; i++)
    {

        if (echo)
        {
            printf("\n\nIteration #%d...\n", i);
            special_arr_print(arr, size, -1, i);
        }

        // First, we store the value to be inserted in the temporary variable.
        temp = arr[i];

        // Then, we check/push its predecessors as follows...
        // Starting with the predecessor before the one we're checking...
        for (int j = i - 1; j >= 0; j--)
        {

            // If a predecessor is larger than current value...
            if (temp < arr[j])
            {

                // Push it to the front
                arr[j + 1] = arr[j];

                // Then insert the value in its place
                arr[j] = temp;

                if (echo)
                    special_arr_print(arr, size, j + 1, j);
            }
        }
    }
}

int8_t binarySearch(uint32_t *arr, uint8_t size, uint32_t number)
{
    // It is required to check if the array is sorted or not initially...
    // However, if we sort an already sorted array, that would have the same...
    // ... time complexity of checking if it is sorted when it is indeed sorted.
    // Therefore, there is no need to check, we can directly pass the array to get sorted.

    // I think the most suitable sorting algorithm for this program would be Insertion Sort.
    insertion_sort(arr, size);

    uint8_t start = 0, end = size - 1, mid = (start + end) / 2;

    if (echo)
        printf("\n\nSearching...\n\n");

    while (1)
    {
        if (echo)
        {
            printf("\nStart = %d, Middle = %d, End = %d.\n", start, mid, end);
            printf("arr[middle] = %d... ", arr[mid]);
        }

        if (number == arr[mid])
        {
            if (echo)
                printf("this is the target, returning its index...\n");
            return mid;
        }
        else if (start == end)
        {
            if (echo)
                printf("\nAll possibilities have been exhausted, number has not been found.\n");
            return -1;
        }
        else if (number > arr[mid])
        {
            if (echo)
                printf("this is smaller than the target, modifying interval...\n");
            start = mid + 1;
            mid = (start + end) / 2;
        }
        else if (number < arr[mid])
        {
            if (echo)
                printf("this is larger than the target, modifying interval...\n");
            end = mid - 1;
            mid = (start + end) / 2;
        }
    }
}

uint8_t main()
{
    do
    {
        printf("Please enter the number of elements to enter (must be less than 255): ");
        uint8_t size;
        scanf("%d", &size);
        uint32_t *arr = calloc(size, sizeof(uint32_t));

        printf("Please enter %d elements separated by spaces: ", size);
        for (int i = 0; i < size; i++)
            scanf(" %d", &arr[i]);

        uint32_t number;

        printf("Please enter the value you'd like to search for: ");
        scanf(" %d", &number);

        int16_t result = binarySearch(arr, size, number);

        if (result == -1)
            printf("\nValue does not exist in provided list.\n");
        else
        {
            printf("\nSorted Array: ");
            special_arr_print(arr, size, -1, result);
            printf("\nValue has been found!\n\tValue = %d,\n\tIndex (in sorted array) = %d.\n", arr[result], result);
        }

        printf("\nPlease press 0 to exit, or any other key to restart application.\n");
    } while (getch() - '0');
    return 0;
}