#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

/* function declarations */
int stringIsInteger ( const char * string_to_test );
int inputAndValidateNumericChoice ( const int number_of_options, int * input_int_value );
int getNumericChoice ( const int number_of_options, const char * main_prompt, const char * invalid_input_message );

// 0 -> FALSE, 1 -> TRUE
int
stringIsInteger ( const char * string_to_test )
{
    int is_number = 1;

    int i = 0;

    int string_length = strlen ( string_to_test );

    while ( i < string_length && is_number == 1 )
    {
        if ( ! isdigit ( string_to_test [ i ] ) )
        {
            is_number = 0;
        }

        i++;
    }

    return is_number;
}

int
inputAndValidateNumericChoice ( const int number_of_options, int *input_int_value )
{
    char input_buffer [ INPUT_LENGTH_LIMIT ];

    int input_is_number = 0;
    int input_is_in_specified_range = 0;

    int input_is_valid = 0;

    // fgets () resets the input buffer every time
    fgets ( input_buffer, INPUT_LENGTH_LIMIT, stdin );

    // strip trailing newline character
    input_buffer [ strcspn ( input_buffer, "\n" ) ] = 0;

    // check if a valid integer has been entered
    input_is_number = stringIsInteger ( input_buffer );

    // if the input is an integer
    if ( input_is_number == 1 )
    {
        // convert the input to an integer
        * input_int_value = atoi ( input_buffer );

        // check if the input is in the range of the option numbers
        input_is_in_specified_range = ( * input_int_value > 0 && * input_int_value <= number_of_options ) ? 1 : 0;
        
        // input is valid only if it is an integer in the specified range
        input_is_valid = ( input_is_number && input_is_in_specified_range ) ? 1 : 0;
    }
    // if the input is not a valid integer
    else
    {
        // the overall validity of the input is false (0)
        input_is_valid = 0;
    }

    return input_is_valid;
}

int
getNumericChoice ( const int number_of_options, const char * main_prompt, const char * invalid_input_message )
{
    int input_int_value = 0;
    int input_is_valid = 0;

    // print the main prompt, e.g. "Enter your option: "
    printf ( "%s", main_prompt );

    input_is_valid = inputAndValidateNumericChoice (
        number_of_options,
        &input_int_value
    );

    // repeat this routine until the user enters a valid input
    while ( input_is_valid == 0 ) {
        printf ( "%s\n", invalid_input_message );
        printf ( "%s", main_prompt );

        input_is_valid = inputAndValidateNumericChoice (
            number_of_options,
            &input_int_value
        );
    }

    // we should be guaranteed we won't get an error since we have checked the
    // input is numeric.

    return input_int_value;
}
