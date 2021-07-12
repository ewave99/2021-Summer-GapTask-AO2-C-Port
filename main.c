#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generic.h"
#include "menu.h"

int
main ()
{
    /* We need to create an array for storing all the Species records.
     * Unfortunately, the size of this array will change over time as the user
     * adds more records.
     * We therefore need to allocate a starting amount of memory for the array, say,
     * 16. If the user wants to exceed this number of records, we must
     * (re?)allocate more memory for the array. So therefore, whenever the user
     * reaches the limit of the array, add 16 more spaces of memory each time.
     * c -> current length of array
     * To reallocate more memory, we need to pass the new length of the array we
     * want, i.e. c + 16.
     * We also need a temporary pointer variable to catch errors should the
     * reallocation function fail and return a NULL pointer.
     * For more information:
     * https://stackoverflow.com/questions/4065229/how-do-i-allocate-more-space-for-my-array-of-c-structs
     * We will do this in the main.c file, and pass a pointer to the array to all
     * relevant functions.
     */

    // Species data array
    Species * species_data;

    // return value for mainMenu function
    int main_menu_return_value;
    
    // Allocate memory for 16 species records
    species_data = ( Species * ) malloc ( sizeof ( Species ) * 16 );

    // Check for any weird errors with memory allocation
    if ( species_data == NULL )
    {
        puts ( "Error in function malloc ()." );
        // abrupt exit from the program
        exit ( 1 );
    }


    main_menu_return_value = mainMenu ( species_data );
    
    if ( main_menu_return_value == 1 )
    {
        return 1;
    }

    return 0;
}
