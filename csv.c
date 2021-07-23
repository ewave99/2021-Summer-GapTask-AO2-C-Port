#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generic.h"
#include "species.h"

void loadDataFromCSV ( Species * species_data );
static void parseCSVIntoStructs ( Species * species_data, int mode, FILE * file );

void saveAsCSV ( Species * species_data );

void
loadDataFromCSV ( Species * species_data )
{
    int mode;
    char input_buffer [ INPUT_LENGTH_LIMIT ];
    FILE * file;

    puts ( "LOAD DATA FROM CSV FILE:" );
    puts ( "" );

    puts ( "CSV load mode:" );
    puts ( "(1) Append to existing data in memory" );
    puts ( "(2) Overwrite existing data in memory" );
    puts ( "" );

    mode = getNumericChoice ( 2, "Enter number of chosen option: ", "Invalid option." );

    puts ( "" );

    if ( mode == 2 )
    {
        puts ( "WARNING: some, if not all, records currently in memory will be deleted." );
        printf ( "Are you sure [y/n]: " );

        fgets ( input_buffer, INPUT_LENGTH_LIMIT, stdin );

        input_buffer [ strcspn ( input_buffer, "\n" ) ] = 0;

        puts ( "" );

        if ( strcmp ( input_buffer, "y" ) != 0 &&
             strcmp ( input_buffer, "Y" ) != 0 )
        {
            puts ( "Abort." );
            puts ( "" );

            return;
        }
    }

    printf ( "Enter filename to load from: " );

    fgets ( input_buffer, INPUT_LENGTH_LIMIT, stdin );

    input_buffer [ strcspn ( input_buffer, "\n" ) ] = 0;

    puts ( "" );

    /* attempt to open file */
    file = fopen ( input_buffer, "r" );
    
    if ( file == NULL )
    {
        printf ( "ERROR: file \"%s\" does not exist.\n", input_buffer );
        puts ( "Aborted." );
        puts ( "" );

        return;
    }

    parseCSVIntoStructs ( species_data, mode, file );

    fclose ( file );

    puts ( "LOADED DATA." );
    puts ( "" );
}

static void
parseCSVIntoStructs ( Species * species_data, int mode, FILE * file )
{
    Species * record_ptr;
    int record_index;
    
    int current_line_number;
    char line_buffer [ INPUT_LENGTH_LIMIT ];
    char * fgets_return_value;
    char * ptr_to_char_in_line;

    char current_field [ INPUT_LENGTH_LIMIT ];
    int current_field_length;

    char * ptr_to_char_in_current_field;

    record_ptr = species_data;
    record_index = 0;

    /* if the user has chosen to append to the data */
    if ( mode == 1 )
    {
        /* fast forward to first blank record */
        while ( strcmp ( record_ptr -> name, "" ) != 0 && record_index < 16 )
        {
            record_ptr ++;
            record_index ++;
        }
    }

    current_line_number = 0;

    /* read in line buffer */
    fgets_return_value = fgets ( line_buffer, INPUT_LENGTH_LIMIT, file );

    if ( fgets_return_value == NULL )
    {
        puts ( "Error: file is empty." );
        return;
    }

    /* while record index < 16 and we are not at the end of the file */
    while ( record_index < 16 && fgets_return_value != NULL )
    {
        /* strip newline character (take into account dos endings) */
        line_buffer [ strcspn ( line_buffer, "\r" ) ] = 0;
        line_buffer [ strcspn ( line_buffer, "\n" ) ] = 0;

        /* point to first char in line */
        ptr_to_char_in_line = line_buffer;

        /* read in name field: */

        /* reset current field content to blank */
        strcpy ( current_field, "" );
        current_field_length = 0;

        /* point to first char in current field */
        ptr_to_char_in_current_field = current_field;

        /* while char is not ',' and char is not '\0' and current_field_length < INPUT_LENGTH_LIMIT */
        while ( * ptr_to_char_in_line != ',' &&
                * ptr_to_char_in_line != '\0' &&
                current_field_length < INPUT_LENGTH_LIMIT )
        {
            /* add char to current field content */
            * ptr_to_char_in_current_field = * ptr_to_char_in_line;
            /* increment pointer to point at next char in line */
            ptr_to_char_in_line ++;
            /* point to next char in field */
            ptr_to_char_in_current_field ++;
            /* increment field length */
            current_field_length ++;
        }
        /* if a comma has not been reached */
        if ( * ptr_to_char_in_line != ',' )
        {
            printf ( "Error: field 'name' is too long on line %d!\n", current_line_number );

            return;
        }
        if ( * ptr_to_char_in_line == '\0' )
        {
            printf ( "Error: field 'count' is missing on line %d!\n", current_line_number );

            return;
        }
        /* add a null character to the end of the field */
        * ptr_to_char_in_current_field = '\0';
        /* copy current field content to the name of the record */
        strcpy ( record_ptr -> name, current_field );

        /* increment the pointer so it is not pointing at the comma */
        ptr_to_char_in_line ++;

        /* read in count field: */

        /* reset current field content to blank */
        strcpy ( current_field, "" );
        current_field_length = 0;

        /* point to first char in current field */
        ptr_to_char_in_current_field = current_field;

        /* while char is not ',' and char is not '\0' and current_field_length < 9 */
        while ( * ptr_to_char_in_line != ',' &&
                * ptr_to_char_in_line != '\0' &&
                current_field_length < 9 )
        {
            /* if char is not numeric */
            if ( ! isdigit ( * ptr_to_char_in_line ) )
            {
                printf ( "%c\n", * ptr_to_char_in_line );

                printf ( "Error: 'count' field on line %d is an invalid number.\n", current_line_number );

                return;
            }

            /* add char to current field content */
            * ptr_to_char_in_current_field = * ptr_to_char_in_line;
            /* increment pointer to point at next char in line */
            ptr_to_char_in_line ++;
            /* point to next char in field */
            ptr_to_char_in_current_field ++;
            /* increment field length */
            current_field_length ++;
        }
        if ( * ptr_to_char_in_line != ',' &&
             * ptr_to_char_in_line != '\0' )
        {
            printf ( "Error: field 'count' on line %d is too large to store!\n", current_line_number );

            return;
        }
        * ptr_to_char_in_current_field = '\0';
        record_ptr -> count = atoi ( current_field );

        record_ptr ++;
        record_index ++;

        current_line_number ++;
        fgets_return_value = fgets ( line_buffer, INPUT_LENGTH_LIMIT, file );
    }

    if ( record_index >= 16 && fgets_return_value != NULL )
    {
        puts ( "All records filled, no space for more data." );
        
        return;
    }

    /* if the user has chosen to overwrite the data */
    if ( mode == 2 )
    {
        /* blankify the remaining records */
        while ( record_index < 16 )
        {
            strcpy ( record_ptr -> name, "" );
            record_ptr -> count = 0;

            record_ptr ++;
            record_index ++;
        }
    }
}

void
saveAsCSV ( Species * species_data )
{
    Species * record_ptr;
    int record_index;

    char input_buffer [ INPUT_LENGTH_LIMIT ];

    FILE * file;

    puts ( "SAVE AS CSV:" );

    printf ( "Enter name to save to: " );
    fgets ( input_buffer, INPUT_LENGTH_LIMIT, stdin );
    input_buffer [ strcspn ( input_buffer, "\n" ) ] = 0;

    while ( strcmp ( input_buffer, "" ) == 0 )
    {
        puts ( "Error: filename cannot be blank." );

        printf ( "Enter name to save to: " );
        fgets ( input_buffer, INPUT_LENGTH_LIMIT, stdin );
        input_buffer [ strcspn ( input_buffer, "\n" ) ] = 0;
    }

    file = fopen ( input_buffer, "w" );

    record_ptr = species_data;
    record_index = 0;

    while ( strcmp ( record_ptr -> name, "" ) != 0 && record_index < 16 )
    {
        fprintf ( file, "%s,%d\n", record_ptr -> name, record_ptr -> count );

        record_ptr ++;
        record_index ++;
    }

    if ( record_index == 0 )
    {
        puts ( "No species data to save." );
        puts ( "" );
        
        return;
    }

    fclose ( file );

    puts ( "SAVED." );
    puts ( "" );
}
