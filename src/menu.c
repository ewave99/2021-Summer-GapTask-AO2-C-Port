#include <stdio.h>
#define INPUT_LENGTH_LIMIT 100

void displayMainMenu ( void ) {
    printf ( "MAIN MENU:\n"                    );
    printf ( "(1) Display data as table\n"     );
    printf ( "(2) Display data as bar chart\n" );
    printf ( "(3) Input new data\n"            );
    printf ( "(4) Edit record\n"               );
    printf ( "(5) Delete record\n"             );
    printf ( "(6) Sort records\n"              );
    printf ( "(7) Clear all current records\n" );
    printf ( "(8) Save as CSV\n"               );
    printf ( "(9) Load data from CSV\n"        );
    printf ( "(10) Quit\n"                     );
}

void *inputMainMenuChoice ( char* string_pointer ) {
    char user_input [ INPUT_LENGTH_LIMIT ];

    printf ( "Enter number of main menu option: " );

    fgets ( user_input, INPUT_LENGTH_LIMIT, stdin );
    
    *string_pointer = *user_input;
}

int main ( void ) {
    char main_menu_choice [ INPUT_LENGTH_LIMIT ];

    displayMainMenu ();

    inputMainMenuChoice ( main_menu_choice );

    printf ( "%s\n", main_menu_choice );

    return 0;
}
