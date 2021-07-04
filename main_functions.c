#define INPUT_LENGTH_LIMIT 100

#include <stdio.h>

#include "data_input.h"

struct Species {
    char name [ INPUT_LENGTH_LIMIT ];
    int count;
};

/* We need to create an array for storing all the Species records.
 * Unfortunately, the size of this array will change over time as the user
 * adds more records.
 * We therefore need to allocate a starting amount of memory for the array, say,
 * 32. If the user wants to exceed this number of records, we must
 * (re?)allocate more memory for the array. So therefore, whenever the user
 * reaches the limit of the array, add 32 more spaces of memory each time.
 * c -> current length of array
 * To reallocate more memory, we need to pass the new length of the array we
 * want, i.e. c + 32.
 * We also need a temporary pointer variable to catch errors should the
 * reallocation function fail and return a NULL pointer.
 * For more information:
 * https://stackoverflow.com/questions/4065229/how-do-i-allocate-more-space-for-my-array-of-c-structs
 */

void displaySpeciesDataAsTable ()
{
    return;
}

void displaySpeciesDataAsBarChart ()
{
    return;
}

void inputSpeciesData ()
{
    puts ( "INPUT SPECIES DATA:" );

    puts ( "Inputting species data. Leave either field blank to stop." );
    puts ( "" );
}

void pickAndEditRecord ()
{
    return;
}

void pickAndDeleteRecord ()
{
    return;
}

void sortRecords ()
{
    return;
}

void clearCurrentRecords ()
{
    return;
}

void saveAsCSV ()
{
    return;
}

void loadDataFromCSV ()
{
    return;
}
