#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <crtdbg.h>
#include "Sudoku.h"
#include "Printer.h"
#include "Definitie.h"
#include "Filereader.h"

int main(void)
{
	char* a = "";
	int r,k,n,c,i;
	Sudoku* s = initlizeSudoku();
	//In case of memory leaks the number of the datablock can be used here
	//_CrtSetBreakAlloc({NR}); 
	/*for( i=1; i< NEGEN-1; i++){
		insert_sudoku(s,1,i,i);
		insert_sudoku(s,i,1,i);
	
	}*/
	
	print_sudoku_inhoud(s);
	read_sudoku_from_file("S4.txt",s);

	//insert_sudoku(s,1,1,1);
	//insert_sudoku(s,1,2,2);
	//insert_sudoku(s,1,3,3);
	//insert_sudoku(s,1,1,4);
	//insert_sudoku(s,2,1,5);
	//insert_sudoku(s,3,1,6);
	//insert_sudoku(s,2,2,7);
	//insert_sudoku(s,3,3,8);

	while(1){
		
		printf("-insert ( Rij ,	Kolom ) =nr \n-delete ( Rij ,	Kolom )	\n-exit \n-clear	\n-save	\n-vakje (Rij , Kolom )	\n");
		print_sudoku_inhoud(s);
		printf("\n\n\n");
		LABEL:printf("you: ");
		scanf("%s", a);

		if(strncmp(a, "insert", 10) == 0){
			c=scanf(" ( %i , %i ) = %i", &r,&k,&n);
			
			if(controleer_grenzen(r,k,n) == OK && c==3){
				c=insert_sudoku(s,r,k,n);
				if(c==MOGELIJK){
					printf("invoegen: rij=%i kolom=%i nummer=%i \n",  r,k,n);
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

		}else if(strncmp(a, "save", 10) == 0){
			write_sudoku_to_file("S2.txt",s);

		}else if(strncmp(a, "vakje", 10) == 0){
			c=scanf(" ( %i , %i )", &r,&k);
			
			if(controleer_grenzen(r,k,5) == OK && c==2){
				print_value_vakje(s,r,k);
			}else{
				if(c < 2){
				scanf("%s", a);
				}
				printf("ERROR: foute waarde");
			}
			goto LABEL;
		} if(strncmp(a, "clear", 10) == 0){
			clear_sudoku(s);

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

