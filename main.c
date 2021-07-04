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

        printf ( "%d\n", main_menu_choice );

        if ( main_menu_choice == 10 ) {
            quit = confirmQuit ();
        }
    }
    while ( quit != 1 );

    puts ( "QUITTING." );

    return 0;
}

