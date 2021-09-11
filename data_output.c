#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>

#include "species.h"

void displaySpeciesDataAsTable ( SpeciesData * species_data );
void displaySpeciesDataAsBarChart ( SpeciesData * species_data );

void displaySpeciesDataAsTable ( SpeciesData * species_data )
{
    Species * record_ptr;
    int record_index;
    
    int current_name_field_width;
    int current_count_field_width;

    int max_name_field_width;
    int max_count_field_width;

    /* we need a location to pass to sprintf in order to convert the integer
     * 'count' to a string */
    char current_count_field [ COUNT_STR_LENGTH_LIMIT ];

    /* find max string length for each field */
    record_ptr = species_data -> records;
    record_index = 0;

    /* length of string "name" is the minimum */
    max_name_field_width = 4;

    /* length of string "count" is the minimum */
    max_count_field_width = 5;

    /* while the name field is not empty */
    while ( strcmp ( record_ptr -> name, "" ) != 0 && record_index < species_data -> length )
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
        record_index ++;
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
    record_ptr = species_data -> records;

    while ( strcmp ( record_ptr -> name, "" ) != 0 )
    {
        printf ( "%*s %*d\n", max_name_field_width, record_ptr -> name, max_count_field_width, record_ptr -> count );

        record_ptr ++;
    }

    /* trailing blank line */
    printf ( "\n" );
}

void
displaySpeciesDataAsBarChart ( SpeciesData * species_data )
{
    Species * record_ptr;
    int record_index;

    int max_name_field_width;
    int current_name_field_width;

    int max_count;

    struct winsize dimensions;

    int max_bar_length;
    int current_bar_length;

    int i;

    puts ( "SPECIES_DATA:" );

    /* find the maximum width amongst all the species names */
    /* and find the maximum count */

    record_ptr = species_data -> records;
    record_index = 0;

    max_name_field_width = 0;
    max_count = 0;

    /* while the name field is not empty */
    while ( strcmp ( record_ptr -> name, "" ) != 0 && record_index < species_data -> length )
    {
        current_name_field_width = strlen ( record_ptr -> name );

        if ( current_name_field_width > max_name_field_width )
            max_name_field_width = current_name_field_width;

        if ( record_ptr -> count > max_count )
            max_count = record_ptr -> count;

        record_ptr ++;
        record_index ++;
    }

    if ( record_index == 0 )
    {
        puts ( "No records to display." );
        puts ( "" );
        
        return;
    }

    if ( max_count == 0 )
    {
        /* go through the records and print the name + ' |' */
        record_ptr = species_data -> records;
        record_index = 0;

        /* repeat until we get to an empty record */
        while ( strcmp ( record_ptr -> name, "" ) != 0 && record_index < species_data -> length )
        {
            /* print the species name, padded to fit the maximum width */
            printf ( "%*s |\n", max_name_field_width, record_ptr -> name );

            record_ptr ++;
            record_index ++;
        }

        puts ( "" );

        return;
    }

    /* we shall make the limit for the bar chart the next multiple of 5 */
    //if ( max_count % 5 != 0 )
    //{
    //    max_count += 5 - max_count % 5;
    //}

    /* get the dimensions of the terminal and store it in 'dimensions' */
    ioctl ( 0, TIOCGWINSZ, & dimensions );

    /* limit the width of the bar chart to 80 */
    //dimensions.ws_col = ( dimensions.ws_col > 80 ) ? 80 : dimensions.ws_col;

    /* account for the ' |' after the species name and the '|' right at the end */
    max_bar_length = dimensions.ws_col - max_name_field_width - 3;

    /* find/decide the numeric interval (not the physical number of chars)
     * between the numbers on the scale */
    int numeric_interval = 1;
    int chars_between_intervals = numeric_interval * max_bar_length / max_count;

    while ( numeric_interval <= max_count &&
            chars_between_intervals < 10 )
    {
        switch ( numeric_interval )
        {
            case 1:
                numeric_interval = 2;
                break;
            case 2:
                numeric_interval = 4;
                break;
            default:
                if ( numeric_interval % 5 == 0 )
                {
                    numeric_interval += 4 - numeric_interval % 4;
                }
                else if ( numeric_interval % 4 == 0 )
                {
                    numeric_interval += 5 - numeric_interval % 5;
                }
                break;
        }
        if ( max_count % numeric_interval != 0 )
        {
            max_count += numeric_interval - max_count % numeric_interval;
        }
        chars_between_intervals = numeric_interval * max_bar_length / max_count;
    }
    
    int number_of_intervals = max_count / numeric_interval;
     
    /* draw header */
    int old_imaginary_bar_length;

    int current_interval_number = 0;
    int current_imaginary_bar_length = 0;
    int next_amount_of_chars_to_draw = 0;

    printf ( "%*s0|", max_name_field_width, "" );

    old_imaginary_bar_length = current_imaginary_bar_length;

    for ( i = 0; i < number_of_intervals; i ++ )
    {
        current_interval_number += numeric_interval;
        current_imaginary_bar_length = current_interval_number * max_bar_length / max_count;
        next_amount_of_chars_to_draw = current_imaginary_bar_length - old_imaginary_bar_length;

        printf ( "%*d|", next_amount_of_chars_to_draw - 1, current_interval_number );

        old_imaginary_bar_length = current_imaginary_bar_length;
    }

    printf ( "\n" );

    /* go through the records and print the name + ' |' + a suitably sized bar. */
    record_ptr = species_data -> records;
    record_index = 0;

    /* repeat until we get to an empty record */
    while ( strcmp ( record_ptr -> name, "" ) != 0 && record_index < species_data -> length )
    {
        /* print the species name, padded to fit the maximum width */
        printf ( "%*s |", max_name_field_width, record_ptr -> name );

        /* calculate the length of the bar needed */
        current_bar_length = record_ptr -> count * max_bar_length / max_count;

        /* print the bar */
        i = 0;

        while ( i < current_bar_length - 1 )
        {
            printf ( "-" );

            i ++;
        }

        printf ( "*\n" );

        record_ptr ++;
        record_index ++;
    }

    puts ( "" );
}
