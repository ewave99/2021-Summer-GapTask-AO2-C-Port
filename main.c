#include <stdio.h>

#include "main.h"
#include "menu.h"
#include "generic.h"

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

        if ( main_menu_choice != 10 )
        {
            doChosenAction ( main_menu_choice );
        }
        else
        {
            quit = confirmQuit ();
        }

        puts ( "" );
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

void displaySpeciesDataAsTable ()
{
    return;
}

void displaySpeciesDataAsBarChart ()
{
    return;
}

void inputSpeciesData ()
{
    return;
}

void pickAndEditRecord ()
{
    return;
}

void pickAndDeleteRecord ()
{
    return;
}

void sortRecords ()
{
    return;
}

void clearCurrentRecords ()
{
    return;
}

void saveAsCSV ()
{
    return;
}

void loadDataFromCSV ()
{
    return;
}
