#ifndef MENU_H_
#define MENU_H_

#include "species.h"

int mainMenu ( Species * species_data );

void displaySpeciesDataAsTable ();
/*
void displaySpeciesDataAsBarChart ();
*/
void inputSpeciesData ( Species * species_data );
void pickAndEditRecord ();
/*
void pickAndDeleteRecord ();
void sortRecords ();
void clearCurrentRecords ();
void saveAsCSV ();
void loadDataFromCSV ();
*/

#endif
