#include "Printer.h"


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