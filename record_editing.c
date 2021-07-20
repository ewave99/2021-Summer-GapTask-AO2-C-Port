#include "generic.h"
#include "species.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void pickAndEditRecord ( Species * species_data );
void inputSpeciesName ( Species * species_data, char * input_buffer );
void inputSpeciesCount ( char * input_buffer );

void pickAndEditRecord ( Species * species_data )
{
    Species * record_ptr;
    
    int i;
    int chosen_record;

    int chosen_field;

    char input_buffer [ INPUT_LENGTH_LIMIT ];

    puts ( "EDITING RECORDS:" );

    /* fast-forward through species data to find the index of the first empty
     * record, printing out the record fields along the way */
    record_ptr = species_data;
    i = 1;

    if ( strcmp ( record_ptr -> name, "" ) != 0 )
        puts ( "" );

    while ( strcmp ( record_ptr -> name, "" ) != 0 )
    {
        printf ( "(%d) %s, %d\n", i, record_ptr -> name, record_ptr -> count );
        record_ptr ++;
        i ++;
    }

    /* if i hasn't changed then there are no records to edit */
    if ( i == 1 )
    {
        puts ( "No records to edit." );
        puts ( "" );

        return;
    }
    /* if i has changed by one then there is 1 record to edit. */
    else if ( i == 2 )
    {
        chosen_record = 0;

        puts ( "Only one record to edit." );
    }
    else
    {
        puts ( "" );
        chosen_record = getNumericChoice ( i - 1, "Enter number of chosen record: ", "Invalid option." );
    }

    puts ( "" );

    record_ptr = species_data;
    /* index is offset by 1, but this still gets us to the right record */
    i = 1;

    /* fast forward to the chosen record */
    while ( i < chosen_record && strcmp ( record_ptr -> name, "" ) != 0 )
    {
        record_ptr ++;
        i ++;
    }

    /* user chooses field they want to change */
    puts ( "(1) Name" );
    puts ( "(2) Count" );
    puts ( "" );

    chosen_field = getNumericChoice ( 2, "Enter number of chosen field: ", "Invalid option" );
    puts ( "" );

    if ( chosen_field == 1 )
    {
        printf ( "Current name: %s\n", record_ptr -> name );

        inputSpeciesName ( species_data, input_buffer );

        strcpy ( record_ptr -> name, input_buffer );
    }
    else if ( chosen_field == 2 )
    {
        printf ( "Current count: %d\n", record_ptr -> count );

        inputSpeciesCount ( input_buffer );

        record_ptr -> count = atoi ( input_buffer );
    }

    puts ( "" );
}
