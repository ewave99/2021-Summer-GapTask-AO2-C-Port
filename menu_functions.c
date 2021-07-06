#define INPUT_LENGTH_LIMIT 100

#include <stdio.h>
#include <string.h>

#include "species.h"

void inputSpeciesName ( struct Species* species_data );

void displaySpeciesDataAsTable ()
{
    return;
}

void displaySpeciesDataAsBarChart ()
{
    return;
}

void inputSpeciesData ( struct Species* species_data )
{
    puts ( "INPUT SPECIES DATA:" );

    puts ( "Inputting species data. Leave either field blank to stop." );
    puts ( "" );

    inputSpeciesName ( species_data );

    puts ( "" );
}

void inputSpeciesName ( struct Species* species_data )
{
    char input_buffer [ INPUT_LENGTH_LIMIT ];

    // Pointer to access elements in the array
    struct Species *ptr;

    size_t index;

    // foo -> bar is the same as ( *foo ).bar

    // point pointer to first element of species data
    ptr = species_data;

    printf ( "Enter species name: " );

    fgets ( input_buffer, INPUT_LENGTH_LIMIT, stdin );

    input_buffer [ strcspn ( input_buffer, "\n" ) ] = 0;

    while ( strcmp ( input_buffer, "" ) != 0 )
    {
        printf ( "Enter species name: " );

        fgets ( input_buffer, INPUT_LENGTH_LIMIT, stdin );

        input_buffer [ strcspn ( input_buffer, "\n" ) ] = 0;
    }

    //strcpy ( ( ptr + 3 ) -> name, "banana" );

    //index = 0;
    //// get to the index of the first empty element (should be 0 in this case)
    //while ( strcmp ( ( ptr + index ) -> name, "banana" ) != 0 && index < 10 )
    //{
    //    index ++;
    //}

    //// conversion character %zu is for type size_t
    //printf ( "Index is %zu\n", index );
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
