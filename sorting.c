#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generic.h"
#include "species.h"

static int compareNamesAsc ( const void * a, const void * b );
static int compareNamesDesc ( const void * a, const void * b );
static int compareCountsAsc ( const void * a, const void * b );
static int compareCountsDesc ( const void * a, const void * b );
void sortRecords ( Species * species_data );

static int
compareNamesAsc ( const void * a, const void * b )
{
    return strcmp ( ( ( Species * ) a ) -> name, ( ( Species * ) b ) -> name );
}

static int
compareNamesDesc ( const void * a, const void * b )
{
    return strcmp ( ( ( Species * ) b ) -> name, ( ( Species * ) a ) -> name );
}

static int
compareCountsAsc ( const void * a, const void * b )
{
    return ( ( Species * ) a ) -> count - ( ( Species * ) b ) -> count;
}

static int
compareCountsDesc ( const void * a, const void * b )
{
    return ( ( Species * ) b ) -> count - ( ( Species * ) a ) -> count;
}

void
sortRecords ( Species * species_data )
{
    Species * ptr;
    int i;
    int field_choice;
    int reverse;

    puts ( "SORT RECORDS:" );

    /* walk through all species data until we get to the first blank record */
    ptr = species_data;
    i = 0;

    while ( strcmp ( ptr -> name, "" ) != 0 && i < 16 )
    {
        ptr ++;
        i ++;
    }

    if ( i == 0 )
    {
        puts ( "No records to sort." );
        puts ( "" );

        return;
    }
    if ( i == 1 )
    {
        puts ( "Only one record in data." );
        puts ( "" );
        
        return;
    }

    puts ( "" );

    puts ( "Sort by:" );
    puts ( "(1) Name (alphabetical)" );
    puts ( "(2) Count (numeric)" );
    puts ( "" );

    field_choice = getNumericChoice ( 2, "Enter number of chosen option: ", "Invalid option." );

    puts ( "" );
    
    puts ( "Sort in reverse?" );
    puts ( "(1) No" );
    puts ( "(2) Yes" );
    puts ( "" );

    reverse = getNumericChoice ( 2, "Enter number of chosen option: ", "Invalid option." );

    if ( field_choice == 1 )
    {
        if ( reverse == 1 ) {
            qsort ( species_data, i, sizeof ( Species ), compareNamesAsc );
        }
        else
        {
            qsort ( species_data, i, sizeof ( Species ), compareNamesDesc );
        }
    }
    else
    {
        if ( reverse == 1 ) {
            qsort ( species_data, i, sizeof ( Species ), compareCountsAsc );
        }
        else
        {
            qsort ( species_data, i, sizeof ( Species ), compareCountsDesc );
        }
    }

    puts ( "" );

    puts ( "RECORDS SORTED." );
    puts ( "" );
}
