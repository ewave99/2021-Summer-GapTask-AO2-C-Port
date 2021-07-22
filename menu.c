#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generic.h"
#include "species.h"

/* function declarations */
int mainMenu ( Species * species_data );
static void displayMainMenu ();
static void doChosenAction ( int main_menu_choice, Species * species_data );
static int confirmQuit ();

void inputSpeciesData ( Species * species_data );
void displaySpeciesDataAsTable ( Species * species_data );
void pickAndEditRecord ( Species * species_data );
void pickAndDeleteRecord ( Species * species_data );
void sortRecords ( Species * species_data );
void clearCurrentRecords ( Species * species_data );
void loadDataFromCSV ( Species * species_data );

int
mainMenu ( Species * species_data )
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

static void
displayMainMenu ()
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

static void
doChosenAction ( int main_menu_choice, Species * species_data )
{
    switch ( main_menu_choice )
    {
        case 1:
            displaySpeciesDataAsTable ( species_data );
            break;
        /*
        case 2:
            displaySpeciesDataAsBarChart ();
            break;
        */
        case 3:
            inputSpeciesData ( species_data );
            break;
        case 4:
            pickAndEditRecord ( species_data );
            break;
        case 5:
            pickAndDeleteRecord ( species_data );
            break;
        case 6:
            sortRecords ( species_data );
            break;
        case 7:
            clearCurrentRecords ( species_data );
            break;
        /*
        case 8:
            saveAsCSV ();
            break;
        */
        case 9:
            loadDataFromCSV ( species_data );
            break;
        default:
            break;
    }
}



// returns 1 for quit, 0 for don't quit
static int
confirmQuit ()
{
    char input_buffer [ INPUT_LENGTH_LIMIT ];
    
    printf ( "Are you sure you want to quit [y/n]: " );

    fgets ( input_buffer, INPUT_LENGTH_LIMIT, stdin );

    // strip trailing newline character
    input_buffer [ strcspn ( input_buffer, "\n" ) ] = 0;

    // convert string to lowercase
    for ( char * ptr = input_buffer; * ptr; ++ ptr )
    {
        * ptr = tolower ( * ptr );
    }

    //strcmp returns 0 if the strings are equal
    if ( strcmp ( input_buffer, "y" ) == 0 )
    {
        return 1;
    }

    return 0;
}
