#include <string.h>
#include <stdio.h>
#include "Sudoku.h"

#ifndef PRINTER
#define PRINTER

//print de eerste 9 bit van een getal met spaties tussen
void print_bin(unsigned int);

//print de getallen 9 -> 1 met een spatie tussen
void print_bin_Header(void);

//print de inhoud van een vakje als gekend het getal anders de verzameling
void print_value_vakje(Sudoku* s, int r, int k);

#endif