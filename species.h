#ifndef SPECIES_H_
#define SPECIES_H_

#include "common.h"

typedef struct
{
    char name [ INPUT_LENGTH_LIMIT ];
    int count;
}
Species;

typedef struct
{
    Species * records;
    int length;
} SpeciesData;

#endif
