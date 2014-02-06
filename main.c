#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <crtdbg.h>
#include "Sudoku.h"
#include "Printer.h"
#include "Definitie.h";

int main(void)
{
	char* a = "";
	int r,k,n,c;
	Sudoku* s = initlizeSudoku();
	//In case of memory leaks the number of the datablock can be used here
	//_CrtSetBreakAlloc({NR}); 

	while(1){
		
		printf("-insert ( Rij ,	Kolom ) =nr \n-delete ( Rij ,	Kolom )	\n-exit \n-new	\n");
		print_sudoku_inhoud(s);
		printf("\n\n\n");
		printf("you: ");
		scanf("%s", a);

		if(strncmp(a, "insert", 10) == 0){
			c=scanf(" ( %i , %i ) = %i", &r,&k,&n);
			
			if(controleer_grenzen(r,k,n) == OK && c==3){
				c=insert_sudoku(s,r,k,n);
				if(c==MOGELIJK){
					printf("invoegen: rij=%i kolom=%i nummer=%i \n",  r,k,n);
					vind_uniek(s,r,k);
				}else if(c==ONMOGELIJK){
					printf("onmogelijk");
				}else if(c==BEZET){
					printf("al bezet");
				}else if(c==UITGESLOTEN){
					printf("vormt een probleem");
				}

			}else{
				if(c < 3){
				scanf("%s", a);
				}
				printf("ERROR: foute waarde");
			}

		}else if(strncmp(a, "delete", 10) == 0){
			c=scanf(" ( %i , %i )", &r,&k);
			
			if(controleer_grenzen(r,k,5) == OK && c==2){
				printf("delete:  rij=%i kolom=%i \n",  r,k);
			}else{
				if(c < 2){
				scanf("%s", a);
				}
				printf("ERROR: foute waarde");
			}
		}else if(strncmp(a, "exit", 10) == 0){
			printf("exit: \n");
			break;

		}else if(strncmp(a, "new", 10) == 0){
			printf("new:  \n");

		}else{
			printf("ERROR: not a command: %s\n",a);
		}
		printf("\n\n");
	}
		


	free_sudoku(s);
	//Memory leaks test
	_CrtDumpMemoryLeaks();
	return 0;

}

