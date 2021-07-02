#define INPUT_LENGTH_LIMIT 100
#define PCRE2_CODE_UNIT_WIDTH 8

#include <stdlib.h>
#include <stdio.h>
#include <pcre2.h>
#include <string.h>

// 0 -> FALSE, 1 -> TRUE
int validateNumericInput ( char* string_to_test, int lower_bound, int upper_bound ) {
    // Store the regex to match in a variable of type PCRE2_SPTR
    PCRE2_SPTR regex_to_match = ( PCRE2_SPTR ) "^[0-9]+$";

    // Here we declare the variables whose pointers we pass to the
    // 'compile' function which creates the regex-pattern-matching object
    int error_number;

    PCRE2_SIZE error_offset;

    pcre2_code *re;

    // create the regex pattern-matching object
    re = pcre2_compile (
        regex_to_match, // the pattern to match
        PCRE2_ZERO_TERMINATED, // indicates pattern is zero-terminated
        0, // default options
        &error_number, // pointer to where to store the error number
        &error_offset, // pointer to where to store the error offset
        NULL // use default compile context
    );

    // check if compilation of regex pattern failed
    if ( re == NULL ) {
        PCRE2_UCHAR error_message_buffer [ 256 ];
        pcre2_get_error_message ( error_number, error_message_buffer, sizeof ( error_message_buffer ) );

        printf ( "PCRE2 regex pattern compilation failed at offset %d: %s\n", (int)error_offset, error_message_buffer );

        return 0;
    }

    puts ( "Regex compilation was successful." );
    
    // Still need to implement testing of whether the number is in the numeric
    // range.

    // Store the string we are trying to match the regex to (the 'subject')
    PCRE2_SPTR subject = ( PCRE2_SPTR ) string_to_test;

    // Store the length of the subject
    PCRE2_SIZE subject_length = ( PCRE2_SIZE ) strlen ( ( char* ) subject );

    // Create the match-data object
    pcre2_match_data *match_data = pcre2_match_data_create_from_pattern ( re, NULL );

    // Match the regex against the test-string
    int match_return_value = pcre2_match (
        re, // The compiled pattern
        subject, // The subject string
        subject_length, // The length of the subject
        0, // Start at offset 0 in the subject
        0, // Use default options
        match_data, // block for storing the result
        NULL // Use default match context
    );

    // Handle errors if matching failed
    if ( match_return_value < 0 ) {
        switch ( match_return_value ) {
            case PCRE2_ERROR_NOMATCH:
                puts ( "No match." );
                break;
            default:
                printf ( "Matching error %d\n", match_return_value );
                break;
        }

        // Free the memory-space that was used for the match data
        pcre2_match_data_free ( match_data );

        // Free the memory-space that was used for the compiled pattern
        pcre2_code_free ( re );

        return 0;
    }

    // If the match succeeded, get a pointer to the output vector, where
    // string offsets are stored.
    PCRE2_SIZE *ovector = pcre2_get_ovector_pointer ( match_data );

    printf ( "Match succeeded at offset %d\n", ( int ) ovector [ 0 ] );

    // if the output vector wasn't big enough
    if ( match_return_value == 0 ) {
        puts ( "ovector was not big enough for all the captured substrings." );
        
        return 1;
    }

    // guard against patterns that set the start of a match further on than
    // its end.
    
    if ( ovector [ 0 ] > ovector [ 1 ] ) {
        puts ( "\\K was used in an assertion to set the match start further on than its end." );
        printf (
            "From end to start the match was: %.*s\n",
            ( int ) ( ovector [ 0 ] - ovector [ 1 ] ),
            ( char* ) ( subject + ovector [ 1 ] )
        );
        puts ( "Run abandoned" );

        // Free the memory-space that was used for the match data
        pcre2_match_data_free ( match_data );

        // Free the memory-space that was used for the compiled pattern
        pcre2_code_free ( re );
        
        return 0;
    }

    // next, do things with the substrings stored in ovector ('output vector').
    
    PCRE2_SPTR substring_start;
    PCRE2_SIZE substring_length;

    for ( int i = 0; i < match_return_value; i++ ) {
        substring_start = subject + ovector [ 2 * i ];
        substring_length = ovector [ 2 * i + 1 ] - ovector [ 2 * i ];
        
        printf (
            "%2d: %.*s\n",
            i,
            ( int ) substring_length, 
            ( char* ) substring_start
        );
    }

    pcre2_match_data_free ( match_data );
    pcre2_code_free ( re );

    return 1;
}

void displayMainMenu ( void )
{
    puts ( "MAIN MENU:"                    );
    puts ( "(1) Display data as table"     );
    puts ( "(2) Display data as bar chart" );
    puts ( "(3) Input new data"            );
    puts ( "(4) Edit record"               );
    puts ( "(5) Delete record"             );
    puts ( "(6) Sort records"              );
    puts ( "(7) Clear all current records" );
    puts ( "(8) Save as CSV"               );
    puts ( "(9) Load data from CSV"        );
    puts ( "(10) Quit"                     );
    puts ( "" );
}

void inputMainMenuChoice ( char* string_pointer ) {
    char user_input [ INPUT_LENGTH_LIMIT ];

    printf ( "Enter number of main menu option: " );

    fgets ( user_input, INPUT_LENGTH_LIMIT, stdin );
    
    *string_pointer = *user_input;
}

int main ( void ) {
    char main_menu_choice_string [ INPUT_LENGTH_LIMIT ];
    //unsigned int main_menu_choice_int;

    displayMainMenu ();

    inputMainMenuChoice ( main_menu_choice_string );

    validateNumericInput ( main_menu_choice_string, 0, 10 );

    return 0;
}
