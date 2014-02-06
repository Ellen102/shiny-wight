#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <crtdbg.h>

#ifndef SUDOKU
#define SUDOKU

#define word unsigned int
#define DRIE 3
#define NEGEN 9
#define MAX 9

typedef enum { F, T } Bool;

typedef struct Sudoku{
	struct SudokuVakje** gegevens;
	struct SudokuKolom* eerstekolom;
	struct SudokuRij* eersterij;
} Sudoku;

typedef struct SudokuVakje {
	Bool gevonden;
	word inhoud;
	unsigned int rijnr;
	unsigned int kolomnr;
	struct SudokuVierkant* vierkant;
	struct SudokuRij* rij;
	struct SudokuKolom* kolom;
	struct SudokuVakje* boven;
	struct SudokuVakje* onder;
	struct SudokuVakje* links;
	struct SudokuVakje* rechts;
} SudokuVakje;

typedef struct SudokuVierkant{
	word inhoud;
	unsigned int vierkantnr;
	struct SudokuRij* rijen[3];
	struct SudokuKolom*kolommen[3];
} SudokuVierkant;

typedef struct SudokuRij{
	word inhoud;
	unsigned int rijnr;
	struct SudokuRij* boven;
	struct SudokuRij* onder;
	struct SudokuVakje* eerste;
} SudokuRij;

typedef struct SudokuKolom{
	word inhoud;
	unsigned int kolomnr;
	struct SudokuKolom* links;
	struct SudokuKolom* rechts;
	struct SudokuVakje* eerste;
} SudokuKolom;


//initilaliseert een lege sudoku met op elke plaats alle mogelijkheden
Sudoku* initlizeSudoku ();
void free_sudoku (Sudoku *);
void print_sudoku_rijkolom(Sudoku*);



#endif