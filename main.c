#include <stdio.h>

#include "generic.h"
#include "menu.h"
#include "main_functions.h"

void doChosenAction ( int main_menu_choice );

int main ()
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
            doChosenAction ( main_menu_choice );
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

void doChosenAction ( int main_menu_choice )
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
            inputSpeciesData ();
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
