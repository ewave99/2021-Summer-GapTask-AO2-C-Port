#include "generic.h"
#include "species.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void pickAndEditRecord ( SpeciesData * species_data );
void inputSpeciesName ( SpeciesData * species_data, char * input_buffer, char * ignore_exists );
void inputSpeciesCount ( char * input_buffer );
void pickAndDeleteRecord ( SpeciesData * species_data );
void clearCurrentRecords ( SpeciesData * species_data );

void
pickAndEditRecord ( SpeciesData * species_data )
{
    Species * record_ptr;
    
    int record_index;
    int chosen_record;

    int chosen_field;

    char input_buffer [ INPUT_LENGTH_LIMIT ];

    puts ( "EDITING RECORDS:" );

    /* fast-forward through species data to find the index of the first empty
     * record, printing out the record fields along the way */
    record_ptr = species_data -> records;
    record_index = 1;

    if ( strcmp ( record_ptr -> name, "" ) != 0 )
        puts ( "" );

    while ( strcmp ( record_ptr -> name, "" ) != 0 && record_index < species_data -> length )
    {
        printf ( "(%d) %s, %d\n", record_index, record_ptr -> name, record_ptr -> count );
        record_ptr ++;
        record_index ++;
    }

    /* if record_index hasn't changed then there are no records to edit */
    if ( record_index == 1 )
    {
        puts ( "No records to edit." );
        puts ( "" );

        return;
    }
    /* if record_index has changed by one then there is 1 record to edit. */
    else if ( record_index == 2 )
    {
        chosen_record = 1;

        puts ( "Only one record to edit." );
    }
    else
    {
        puts ( "" );
        chosen_record = getNumericChoice ( record_index - 1, "Enter number of chosen record: ", "Invalid option." );
    }

    if ( chosen_record == 1 )
    {
        printf ( "Do you want to edit this record [y/n]: " );
    }
    else
    {
        printf ( "Are you sure you want to edit this record [y/n]: " );
    }
    
    fgets ( input_buffer, INPUT_LENGTH_LIMIT, stdin );
    input_buffer [ strcspn ( input_buffer, "\n" ) ] = 0;

    /* abort if the user does not enter "y" or "Y" */
    if ( strcmp ( input_buffer, "y" ) != 0 &&
         strcmp ( input_buffer, "Y" ) != 0 )
    {
        puts ( "Aborted." );
        puts ( "" );

        return;
    }

    puts ( "" );

    record_ptr = species_data -> records;
    /* index is offset by 1, but this still gets us to the right record */
    record_index = 1;

    /* fast forward to the chosen record */
    while ( record_index < chosen_record && strcmp ( record_ptr -> name, "" ) != 0 )
    {
        record_ptr ++;
        record_index ++;
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

        inputSpeciesName ( species_data, input_buffer, record_ptr -> name );

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

void
pickAndDeleteRecord ( SpeciesData * species_data )
{
    Species * record_ptr;
    
    int record_index;
    int chosen_record;

    char input_buffer [ INPUT_LENGTH_LIMIT ];

    puts ( "DELETE RECORD:" );

    /* fast-forward through species data to find the index of the first empty
     * record, printing out the record fields along the way */
    record_ptr = species_data -> records;
    record_index = 1;

    if ( strcmp ( record_ptr -> name, "" ) != 0 )
        puts ( "" );

    while ( strcmp ( record_ptr -> name, "" ) != 0 && record_index < species_data -> length )
    {
        printf ( "(%d) %s, %d\n", record_index, record_ptr -> name, record_ptr -> count );
        record_ptr ++;
        record_index ++;
    }

    /* if record_index hasn't changed then there are no records to delete */
    if ( record_index == 1 )
    {
        puts ( "No records to delete." );
        puts ( "" );

        return;
    }
    /* if record_index has changed by one then there is 1 record to delete. */
    else if ( record_index == 2 )
    {
        chosen_record = 1;

        puts ( "Only one record to delete." );
    }
    else
    {
        puts ( "" );
        chosen_record = getNumericChoice ( record_index - 1, "Enter number of chosen record: ", "Invalid option." );
    }

    if ( chosen_record == 1 )
    {
        printf ( "Do you want to delete this record [y/n]: " );
    }
    else
    {
        printf ( "Are you sure you want to delete this record [y/n]: " );
    }
    
    fgets ( input_buffer, INPUT_LENGTH_LIMIT, stdin );
    input_buffer [ strcspn ( input_buffer, "\n" ) ] = 0;

    /* abort if the user does not enter "y" or "Y" */
    if ( strcmp ( input_buffer, "y" ) != 0 &&
         strcmp ( input_buffer, "Y" ) != 0 )
    {
        puts ( "Aborted." );
        puts ( "" );

        return;
    }

    puts ( "" );

    record_ptr = species_data -> records;
    /* index is offset by 1, but this still gets us to the right record */
    record_index = 1;

    /* fast forward to the chosen record */
    while ( record_index < chosen_record && strcmp ( record_ptr -> name, "" ) != 0 )
    {
        record_ptr ++;
        record_index ++;
    }

    Species * record_ptr_last;

    /* for each record that comes after the chosen record, copy its contents
     * into the record to the left of it. */
    while ( record_index < 15 )
    {
        record_ptr_last = record_ptr;

        record_ptr ++;
        record_index ++;

        strcpy ( record_ptr_last -> name, record_ptr -> name );
        record_ptr_last -> count = record_ptr -> count;
    }

    /* nullify the last record */
    strcpy ( record_ptr -> name, "" );
}

void
clearCurrentRecords ( SpeciesData * species_data )
{
    Species * record_ptr;
    int record_index;

    char input_buffer [ INPUT_LENGTH_LIMIT ];

    puts ( "CLEARING ALL RECORDS:" );

    record_ptr = species_data -> records;
    record_index = 0;

    while ( strcmp ( record_ptr -> name, "" ) != 0 && record_index < species_data -> length )
    {
        record_ptr ++;
        record_index ++;
    }

    /* if record_index hasn't changed then there are no records to delete */
    if ( record_index == 0 )
    {
        puts ( "No records to delete." );
        puts ( "" );

        return;
    }
    
    printf ( "Are you sure [y/n]: " );
    
    fgets ( input_buffer, INPUT_LENGTH_LIMIT, stdin );
    input_buffer [ strcspn ( input_buffer, "\n" ) ] = 0;

    /* abort if the user does not enter "y" or "Y" */
    if ( strcmp ( input_buffer, "y" ) != 0 &&
         strcmp ( input_buffer, "Y" ) != 0 )
    {
        puts ( "Aborted." );
        puts ( "" );

        return;
    }

    /* take advantage of the fact that the program doesn't 'see' all the records
     * that come after a record whose name is null, */
    record_ptr = species_data -> records;

    strcpy ( record_ptr -> name, "" );
    
    puts ( "Cleared all current records." );

    puts ( "" );
}
