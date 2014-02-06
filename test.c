#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <crtdbg.h>
#include "Sudoku.h"
#include "Printer.h"

#define PRINTNEWLINE printf("\n")
#define PRINTBIN(n) print_bin(n);printf("  %i  ",n);printf("\n")

int maintwee(void)
{
	//In case of memory leaks the number of the datablock can be used here
	//_CrtSetBreakAlloc({NR}); 

	unsigned int test = 1, a,b,c;
	unsigned int counter = 0;
	Sudoku* s = initlizeSudoku();

	
	print_bin_Header(); printf("\n");

	for(counter=0; counter < 9; counter++){
	
		print_bin(test);
		printf("  %i  ", test);
		printf("\n");
		test = test << 1; 

	}
	
	
	a = 70;
	PRINTBIN(a);
	
	PRINTBIN(1<<(6-1));
	b = a | (1<<(6-1));
	PRINTBIN(b);
	c = b & (1<<(7-1));
	PRINTBIN(c);

	PRINTNEWLINE;

	print_sudoku_rijkolom(s);
	PRINTNEWLINE;PRINTNEWLINE;PRINTNEWLINE;PRINTNEWLINE;
	print_sudoku_inhoud(s);




	free_sudoku(s);
	//Memory leaks test
	_CrtDumpMemoryLeaks();
	return 0;

}