#include <string.h>
#include <stdio.h>
#include "Sudoku.h"

#ifndef FILEREADER
#define FILEREADER

#define GELUKT 0
#define FILENIETOPEN -1
#define FOUTKARAKTER -2
#define SUDOKUPOINTERFOUT -3

//sudoku moet geinitalsieerd zijn!
int read_sudoku_from_file(char* file, Sudoku* s);
int write_sudoku_to_file(char* file, Sudoku* s);

#endif