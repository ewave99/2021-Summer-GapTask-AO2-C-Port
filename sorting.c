#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generic.h"
#include "species.h"

static int compareNamesAsc ( const void * a, const void * b );
static int compareNamesDesc ( const void * a, const void * b );
static int compareCountsAsc ( const void * a, const void * b );
static int compareCountsDesc ( const void * a, const void * b );
void sortRecords ( SpeciesData * species_data );

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
sortRecords ( SpeciesData * species_data )
{
    Species * record_ptr;
    int record_index;
    int field_choice;
    int reverse;

    puts ( "SORT RECORDS:" );

    /* walk through all species data until we get to the first blank record */
    record_ptr = species_data -> records;
    record_index = 0;

    while ( strcmp ( record_ptr -> name, "" ) != 0 && record_index < species_data -> length )
    {
        record_ptr ++;
        record_index ++;
    }

    if ( record_index == 0 )
    {
        puts ( "No records to sort." );
        puts ( "" );

        return;
    }
    if ( record_index == 1 )
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
            qsort ( species_data -> records, record_index, sizeof ( Species ), compareNamesAsc );
        }
        else
        {
            qsort ( species_data -> records, record_index, sizeof ( Species ), compareNamesDesc );
        }
    }
    else
    {
        if ( reverse == 1 ) {
            qsort ( species_data -> records, record_index, sizeof ( Species ), compareCountsAsc );
        }
        else
        {
            qsort ( species_data -> records, record_index, sizeof ( Species ), compareCountsDesc );
        }
    }

    puts ( "" );

    puts ( "RECORDS SORTED." );
    puts ( "" );
}
