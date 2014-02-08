#include "Printer.h"

void print_value_vakje(Sudoku* s, int r, int k){
	SudokuVakje *vakje=NULL;
	vakje = &(s->gegevens[r-1][k-1]);
	if(vakje->gevonden == T){
	
		printf("gevonden: (%i,%i)=%i\n", r,k, vakje->inhoud);

	}else{
	
		printf("nog niet gevoden\n");
		print_bin_Header(); printf("\n");
		print_bin(vakje->inhoud);printf("\n");
	}

	

}



void print_bin(unsigned int getal){

	unsigned i;
    for (i = 1 << 8; i > 0; i = i / 2){
        (getal & i)? printf("1"): printf("0");
		printf(" ");
	}

}

void print_bin_Header(void){
	unsigned int i=0;
	for(i=9; i >= 1 ; i--){
		printf("%i ", i);
	}
}