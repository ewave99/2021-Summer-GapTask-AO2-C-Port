#define INPUT_LENGTH_LIMIT 100

#include <stdio.h>
#include <ctype.h>
#include <string.h>

void displayMainMenu ()
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


// returns 1 for quit, 0 for don't quit
int confirmQuit ()
{
    char input_buffer [ INPUT_LENGTH_LIMIT ];
    
    printf ( "Are you sure you want to quit [y/n]: " );

    fgets ( input_buffer, INPUT_LENGTH_LIMIT, stdin );

    // strip trailing newline character
    input_buffer [ strcspn ( input_buffer, "\n" ) ] = 0;

    // convert string to lowercase
    for ( char *ptr = input_buffer; *ptr; ++ ptr )
    {
        *ptr = tolower ( *ptr );
    }

    //strcmp returns 0 if the strings are equal
    if ( strcmp ( input_buffer, "y" ) == 0 )
    {
        return 1;
    }

    return 0;
}
