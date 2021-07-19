#include <stdio.h>
#include <string.h>

#include "species.h"

void displaySpeciesDataAsTable ( Species * species_data );

void displaySpeciesDataAsTable ( Species * species_data )
{
    Species * record_ptr;
    
    int current_name_field_width;
    int current_count_field_width;

    int max_name_field_width;
    int max_count_field_width;

    /* we need a location to pass to sprintf in order to convert the integer
     * 'count' to a string */
    char current_count_field [ COUNT_STR_LENGTH_LIMIT ];

    /* find max string length for each field */
    record_ptr = species_data;

    /* length of string "name" is the minimum */
    max_name_field_width = 4;

    /* length of string "count" is the minimum */
    max_count_field_width = 5;

    /* while the name field is not empty */
    while ( strcmp ( record_ptr -> name, "" ) != 0 )
    {
        current_name_field_width = strlen ( record_ptr -> name );

        /* convert count to string and store it */
        sprintf ( current_count_field, "%d", record_ptr -> count );

        current_count_field_width = strlen ( current_count_field );

        if ( current_name_field_width > max_name_field_width )
            max_name_field_width = current_name_field_width;

        if ( current_count_field_width > max_count_field_width )
            max_count_field_width = current_count_field_width;

        record_ptr ++;
    }

    /* print headers */
    printf ( "%*s %*s\n", max_name_field_width, "name", max_count_field_width, "count" );

    for ( int i = 0; i < max_name_field_width + 1 + max_count_field_width; i ++ )
    {
        printf ( "-" );
    }
    printf ( "\n" );

    /* print values */

    /* reset record pointer */
    record_ptr = species_data;

    while ( strcmp ( record_ptr -> name, "" ) != 0 )
    {
        printf ( "%*s %*d\n", max_name_field_width, record_ptr -> name, max_count_field_width, record_ptr -> count );

        record_ptr ++;
    }

    /* trailing blank line */
    printf ( "\n" );
}
