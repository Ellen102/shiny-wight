#include "Definitie.h";
#include "Sudoku.h"

int controleer_grenzen(int r, int k, int n){
	return (( (r-1)>=0 && (k-1)>=0 && (r-1)<NEGEN && (k-1)<NEGEN && n>0 && n<10))?OK:FOUT;

}