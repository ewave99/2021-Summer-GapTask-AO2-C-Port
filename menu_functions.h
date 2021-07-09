#ifndef MENU_FUNCTIONS_H_
#define MENU_FUNCTIONS_H_

#include "common.h"

void displaySpeciesDataAsTable ();
void displaySpeciesDataAsBarChart ();
void inputSpeciesData ( struct Species* species_data );
void pickAndEditRecord ();
void pickAndDeleteRecord ();
void sortRecords ();
void clearCurrentRecords ();
void saveAsCSV ();
void loadDataFromCSV ();

#endif
