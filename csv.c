#include <stdio.h>
#include <string.h>

#include "generic.h"
#include "species.h"

void loadDataFromCSV ( Species * species_data );
static void parseCSVIntoStructs ( Species * species_data, int starting_record, int mode, FILE * file );

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
        puts ( "WARNING: all records currently in memory will be deleted." );
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

    fclose ( file );
}

static void
parseCSVIntoStructs ( Species * species_data, int starting_record, int mode, FILE * file )
{
    /*  Algorithm structure
     *  
     *  read in line
     *  strip newline character
     *  point to first char in line
     *  while record index < 16 and we are not at the end of the file 
     *      [read in name field]
     *      reset current field content to blank
     *      reset current field length to 0
     *      while char is not ',' and char is not '\0' and current_field_length < INPUT_LENGTH_LIMIT
     *          append char to current field content
     *          increment pointer to point at next char in line
     *          increment current field length
     *      [when we reach a ',' or '\0']
     *      append a '\0' to the current field content
     *      record -> name = current field content
     *
     *      [read in count field]
     *      reset current field content to blank
     *      reset current field length to 0
     *      while char is not ',' and char is not '\0' and current field length < INPUT_LENGTH_LIMIT
     *          if char is not numeric
     *              there is an error: count field '<count field>' is an invalid number
     *              return from function 
     *          if current field length >= 9
     *              error: number '<count field>' is too long to store
     *              return from function
     *          append char to current field content
     *          increment pointer to point at next char in line
     *          increment current field length
     *      [when we reach a ',' or '\0']
     *      append a '\0' to the current field content
     *      record -> count = atoi ( current field content )
     *
     *      read in line
     *      strip newline character
     *      point to first char in line
     *
     *  print 'All records filled.'
     *      */

    Species * record_ptr;

    int record_index;

    char buffer [ INPUT_LENGTH_LIMIT ];

    char * buffer_ptr;
    int buffer_index;

    int buffer_length;

    char * field_ptr;
    int field_index;

    record_ptr = species_data;
    record_index = 0;

    /* fast forward to the chosen starting point */
    while ( record_index < starting_record && record_index < 16 )
    {
        record_ptr ++;
        record_index ++;
    }

    /* set up initial values for the boolean expression at the top of the
     * while loop */
    if ( record_index < 16 )
    {
        fgets ( buffer, INPUT_LENGTH_LIMIT, stdin );
        buffer [ strcspn ( buffer, "\n" ) ] = 0;
    }

    /* loop until end of file is reached */
    while ( record_index < 16 && strlen ( buffer ) != 0 )
    {
        /* read in name field */
        field_ptr = record_ptr -> name;
        field_index = 0;

        /* point to the start of the current line */
        buffer_ptr = buffer;
        buffer_index = 0;

        /* store the length of the line for convenience */
        buffer_length = strlen ( buffer );

        /* read in characters until we reach a comma */
        while ( * buffer_ptr != '\0' &&
                buffer_index < INPUT_LENGTH_LIMIT &&
                * buffer_ptr != ',' &&
                field_index < INPUT_LENGTH_LIMIT )
        {
            buffer_ptr ++;
            buffer_index ++;

            field_ptr ++;
            field_index ++;
        }

        /* point to the start of the current line */
        buffer_ptr = buffer;
        buffer_index = 0;

        /* store the length of the line for convenience */
        buffer_length = strlen ( buffer );

        /* loop through all the characters in the line */
        while ( * buffer_ptr != '\0' && buffer_index < INPUT_LENGTH_LIMIT )
        {
            buffer_ptr ++;
            buffer_index ++;
        }

        /* point to the next record */
        record_ptr ++;
        record_index ++;

        if ( record_index < 16 )
        {
            fgets ( buffer, INPUT_LENGTH_LIMIT, stdin );
            buffer [ strcspn ( buffer, "\n" ) ] = 0;
        }
    }
}
