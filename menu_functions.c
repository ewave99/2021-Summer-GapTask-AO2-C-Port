#define INPUT_LENGTH_LIMIT 100

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "species.h"

void inputSpeciesName ( struct Species* species_data, char* input_buffer );
int checkIfNameExists ( char* name, struct Species* species_data );

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
    char input_buffer [ INPUT_LENGTH_LIMIT ];

    puts ( "INPUT SPECIES DATA:" );

    puts ( "Inputting species data. Leave either field blank to stop." );
    puts ( "" );

    inputSpeciesName ( species_data, input_buffer );

    // input until user leaves the input blank
    while ( strcmp ( input_buffer, "" ) != 0 )
    {
        // input species count

        // this if statement is needed since we are checking *both* fields
        // for a blank input.
        if ( strcmp ( input_buffer, "" ) != 0 )
        {
            // convert count to int

            // build a record and add it to the array

            puts ( "" );

            inputSpeciesName ( species_data, input_buffer );
        }
    }

    puts ( "" );
    puts ( "Finished inputting species data." );

    puts ( "" );
}

void inputSpeciesName ( struct Species* species_data, char* input_buffer )
{
    int name_exists;

    printf ( "Enter species name: " );

    fgets ( input_buffer, INPUT_LENGTH_LIMIT, stdin );

    input_buffer [ strcspn ( input_buffer, "\n" ) ] = 0;

    name_exists = checkIfNameExists ( input_buffer, species_data );

    // we need to check if the value is "" to be able to determine whether
    // to terminate the data-inputting process in the function
    // inputSpeciesData ().
    while ( name_exists == 1 && strcmp ( input_buffer, "" ) != 0 )
    {
        printf ( "Error: Name '%s' already exists in records!\n", input_buffer );

        printf ( "Enter species name: " );

        fgets ( input_buffer, INPUT_LENGTH_LIMIT, stdin );

        input_buffer [ strcspn ( input_buffer, "\n" ) ] = 0;

        checkIfNameExists ( input_buffer, species_data );
    }
}

// 0 for does not exist; 1 for does exist
int checkIfNameExists ( char* name, struct Species* species_data )
{
    int name_exists = 0;

    struct Species* species_data_ptr;

    // we can guarantee that names will not be longer than INPUT_LENGTH_LIMIT
    char record_name [ INPUT_LENGTH_LIMIT ];

    char* record_name_ptr;

    // create pointer to initial element of species_data
    species_data_ptr = species_data;

    while ( name_exists == 0 && strcmp ( species_data_ptr -> name, "" ) != 0 )
    {
        // make a copy of the record name so we can compare the lowercase version
        strcpy ( record_name, species_data_ptr -> name );

        // convert record name to lowercase (not in-place of course)
        record_name_ptr = record_name;

        while ( *record_name_ptr )
        {
            *record_name_ptr = tolower ( *record_name_ptr );

            record_name_ptr ++;
        } // record name is now lowercase

        // if the names are equal
        if ( strcmp ( name, record_name ) == 0 )
        {
            name_exists = 1;
        }

        species_data_ptr ++;
    }
    
    if ( name_exists == 1 )
    {
        return 1;
    }

    return 0;
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
