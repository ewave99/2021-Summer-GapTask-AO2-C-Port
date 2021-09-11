#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generic.h"
#include "species.h"

int mainMenu ( SpeciesData * species_data );

int
main ()
{
    // Species data frame
    SpeciesData * species_data;

    // return value for mainMenu function
    int main_menu_return_value;

    // Allocate memory for species data frame
    species_data = ( SpeciesData * ) malloc ( sizeof ( SpeciesData ) * 1 );
    
    // Allocate memory for 16 species records
    species_data -> records = ( Species * ) malloc ( sizeof ( Species ) * 16 );
    species_data -> length = 16;

    // Check for any weird errors with memory allocation
    if ( species_data -> records == NULL )
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
