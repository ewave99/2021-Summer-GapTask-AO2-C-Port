#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generic.h"
#include "species.h"

/* function declarations */
void inputSpeciesData ( Species * species_data );
void inputSpeciesName ( Species * species_data, char * input_buffer, char * ignore_exists );
static int checkIfNameExists ( Species * species_data, char * name, char * ignore );
void inputSpeciesCount ( char * input_buffer );

void
inputSpeciesData ( Species * species_data )
{
    char input_buffer [ INPUT_LENGTH_LIMIT ];
    
    char name [ INPUT_LENGTH_LIMIT ];
    int count;

    Species * ptr;

    int index = 0;
    
    ptr = species_data;

    // fast forward till we get to the first empty struct
    while ( index < 16 && strcmp ( ptr -> name, "" ) != 0 )
    {
        ptr ++;
        index ++;
    }

    puts ( "INPUT SPECIES DATA:" );

    puts ( "Inputting species data. Leave either field blank to stop." );
    puts ( "" );

    // input species name (pass pointer to species array so we can check if
    // a name already exists).
    // 2021-06-08: for some reason this functionality isn't working
    inputSpeciesName ( species_data, input_buffer, "" );

    // input until user leaves the input blank
    while ( strcmp ( input_buffer, "" ) != 0 && index < 16 )
    {
        strcpy ( name, input_buffer );

        // input species count
        inputSpeciesCount ( input_buffer );

        // this if statement is needed since we are checking *both* fields
        // for a blank input.
        if ( strcmp ( input_buffer, "" ) != 0 )
        {
            // convert count to int
            count = atoi ( input_buffer );

            // add the information to the current record
            strcpy ( ptr -> name, name );
            ptr -> count = count;

            index ++;
            ptr ++;

            if ( index < 16 )
            {
                puts ( "" );

                inputSpeciesName ( species_data, input_buffer, "" );
            }
            else
            {
                // from testing we see that pointer is not NULL. Don't know
                // why though.
                if ( ptr == NULL )
                {
                    puts ( "pointer is NULL." );
                }
                // future: reallocate memory for a larger array.
                puts ( "Limit of 16 records reached." );
            }
        }
    }

    puts ( "" );
    puts ( "Finished inputting species data." );

    puts ( "" );
}

void
inputSpeciesName ( Species * species_data, char * input_buffer, char * ignore_exists )
{
    int name_exists;

    printf ( "Enter species name: " );

    fgets ( input_buffer, INPUT_LENGTH_LIMIT, stdin );

    input_buffer [ strcspn ( input_buffer, "\n" ) ] = 0;

    name_exists = checkIfNameExists ( species_data, input_buffer, ignore_exists );

    // we need to check if the value is "" to be able to determine whether
    // to terminate the data-inputting process in the function
    // inputSpeciesData ().
    while ( name_exists == 1 && strcmp ( input_buffer, "" ) != 0 )
    {
        printf ( "Error: Name '%s' already exists in records!\n", input_buffer );

        printf ( "Enter species name: " );

        fgets ( input_buffer, INPUT_LENGTH_LIMIT, stdin );

        input_buffer [ strcspn ( input_buffer, "\n" ) ] = 0;

        name_exists = checkIfNameExists ( species_data, input_buffer, ignore_exists );
    }
}

// 0 for does not exist; 1 for does exist
static int
checkIfNameExists ( Species * species_data, char * name, char * ignore )
{
    int name_exists;

    Species * species_data_ptr;

    // default existence of name is 0
    name_exists = 0;

    // create pointer to initial element of species_data
    species_data_ptr = species_data;

    // while the name does not exist and the 'name' value of the current species
    // struct = 
    while ( name_exists == 0 && strcmp ( species_data_ptr -> name, "" ) != 0 )
    {
        // if the names are equal
        if ( strcmp ( name, species_data_ptr -> name ) == 0 && strcmp ( species_data_ptr -> name, ignore ) != 0 )
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

void
inputSpeciesCount ( char * input_buffer )
{
    printf ( "Enter specimen count: " );

    fgets ( input_buffer, INPUT_LENGTH_LIMIT, stdin );

    input_buffer [ strcspn ( input_buffer, "\n" ) ] = 0;

    while (
        (
            stringIsInteger ( input_buffer ) == 0 ||
            // by limiting the user input to 9 or fewer characters, we ensure that
            // we are always below the integer limit (2 147 483 547), meaning there
            // will never be an integer overflow.
            strlen ( input_buffer ) > COUNT_STR_LENGTH_LIMIT
        ) &&
        strcmp ( input_buffer, "" ) != 0
    )
    {
        puts ( "Invalid count." );

        printf ( "Enter specimen count: " );

        fgets ( input_buffer, INPUT_LENGTH_LIMIT, stdin );

        input_buffer [ strcspn ( input_buffer, "\n" ) ] = 0;
    }
}
