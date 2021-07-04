#include "menu.h"
#include <stdio.h>

int main ()
{
    int main_menu_choice;

    displayMainMenu ();

    main_menu_choice = getNumericChoice (
        10,
        "Enter number of main menu option: ",
        "Invalid option."
    );

    printf ( "%d\n", main_menu_choice );

    return 0;
}

