#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "generic.h"
#include "menu_functions.h"
// species.h is already included in menu_functions.h

int mainMenu ( struct Species* species_data );
void displayMainMenu ();
void doChosenAction ( int main_menu_choice, struct Species* species_data );
int confirmQuit ();

int main ()
{
    /* We need to create an array for storing all the Species records.
     * Unfortunately, the size of this array will change over time as the user
     * adds more records.
     * We therefore need to allocate a starting amount of memory for the array, say,
     * 16. If the user wants to exceed this number of records, we must
     * (re?)allocate more memory for the array. So therefore, whenever the user
     * reaches the limit of the array, add 16 more spaces of memory each time.
     * c -> current length of array
     * To reallocate more memory, we need to pass the new length of the array we
     * want, i.e. c + 16.
     * We also need a temporary pointer variable to catch errors should the
     * reallocation function fail and return a NULL pointer.
     * For more information:
     * https://stackoverflow.com/questions/4065229/how-do-i-allocate-more-space-for-my-array-of-c-structs
     * We will do this in the main.c file, and pass a pointer to the array to all
     * relevant functions.
     */

    // Species data array
    struct Species *species_data;

    // return value for mainMenu function
    int main_menu_return_value;
    
    // Allocate memory for 16 species records
    species_data = ( struct Species * ) malloc ( sizeof ( struct Species ) * 16 );

    // Check for any weird errors with memory allocation
    if ( species_data == NULL )
    {
        puts ( "Error in function malloc ()." );
        // abrupt exit from the program
        exit ( 1 );
    }


    main_menu_return_value = mainMenu ( species_data );
    
    if ( main_menu_return_value == 1 )
    {
        return 1;
    }

    return 0;
}

int mainMenu ( struct Species* species_data )
{
    int main_menu_choice;
    int quit = 0;

    do
    {
        displayMainMenu ();

        main_menu_choice = getNumericChoice (
            10,
            "Enter number of main menu option: ",
            "Invalid option."
        );

        puts ( "" );

        if ( main_menu_choice != 10 )
        {
            doChosenAction ( main_menu_choice, species_data );
        }
        else
        {
            quit = confirmQuit ();
        }
    }
    while ( quit != 1 );

    puts ( "QUITTING." );

    return 0;
}

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

void doChosenAction ( int main_menu_choice, struct Species* species_data )
{
    switch ( main_menu_choice )
    {
        case 1:
            displaySpeciesDataAsTable ();
            break;
        case 2:
            displaySpeciesDataAsBarChart ();
            break;
        case 3:
            inputSpeciesData ( species_data );
            break;
        case 4:
            pickAndEditRecord ();
            break;
        case 5:
            pickAndDeleteRecord ();
            break;
        case 6:
            sortRecords ();
            break;
        case 7:
            clearCurrentRecords ();
            break;
        case 8:
            saveAsCSV ();
            break;
        case 9:
            loadDataFromCSV ();
            break;
        default:
            break;
    }
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
