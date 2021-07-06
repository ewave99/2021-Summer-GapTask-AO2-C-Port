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
    // Pointer to access elements in the array
    //struct Species *ptr;

    char input_buffer [ INPUT_LENGTH_LIMIT ];

    // point pointer to first element of species data
    //ptr = species_data;

    printf ( "Enter species name: " );

    fgets ( input_buffer, INPUT_LENGTH_LIMIT, stdin );

    input_buffer [ strcspn ( input_buffer, "\n" ) ] = 0;

    while ( strcmp ( input_buffer, "" ) != 0 )
    {
        printf ( "Enter species name: " );

        fgets ( input_buffer, INPUT_LENGTH_LIMIT, stdin );

        input_buffer [ strcspn ( input_buffer, "\n" ) ] = 0;
    }

    // foo -> bar is the same as ( *foo ).bar
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
