#include "Sudoku.h"

Sudoku* initlizeSudoku (){
	unsigned int i,j;
	SudokuKolom *k1=NULL, *volgendekolom=NULL, *vorigekolom=NULL ;
	SudokuRij *r1=NULL, *volgenderij=NULL, *vorigerij=NULL ;

	Sudoku* s =  (Sudoku*) malloc(sizeof(Sudoku));

	//basis:tweedimensionale array met sudokuvakjes
	(s->gegevens) = ((SudokuVakje**) malloc(sizeof(SudokuVakje*)*(NEGEN)));
	for(i=0; i< NEGEN ; i++){
		s->gegevens[i] = ((SudokuVakje*) malloc(sizeof(SudokuVakje)*(NEGEN)));
	}

	//nummering
	for(i=0; i < NEGEN ; i++){
		
			for(j=0; j < NEGEN ; j++){
				s->gegevens[i][j].kolomnr = j+1;
				s->gegevens[i][j].rijnr = i+1;

			}

	}

	//kolommen
	k1 = (SudokuKolom*) malloc(sizeof(SudokuKolom));
	k1->links = NULL;
	k1->kolomnr = 1;
	vorigekolom=k1;
	for(i=1; i < NEGEN ; i++){
		volgendekolom = (SudokuKolom*) malloc(sizeof(SudokuKolom));
		volgendekolom->kolomnr=i+1;
		vorigekolom->rechts = volgendekolom;
		volgendekolom->links = vorigekolom;
		vorigekolom=volgendekolom;
	}
	vorigekolom->rechts=NULL;
	s->eerstekolom=k1;

	//rijen
	r1 = (SudokuRij*) malloc(sizeof(SudokuRij));
	r1->boven=NULL;
	r1->rijnr=1;
	vorigerij=r1;
	for(i=1; i < NEGEN ; i++){
		volgenderij = (SudokuRij*) malloc(sizeof(SudokuRij));
		volgenderij->rijnr = i+1;
		vorigerij->onder = volgenderij;
		volgenderij->boven = vorigerij;
		vorigerij = volgenderij;
	}
	vorigerij->onder=NULL;
	s->eersterij=r1;

	//vierkant


	return s;
}


void free_sudoku ( Sudoku * s){
	unsigned int i;
	SudokuKolom *volgendekolom=NULL, *vorigekolom=NULL ;
	SudokuRij *volgenderij=NULL, *vorigerij=NULL ;

	//kolom
	vorigekolom=s->eerstekolom;
	while(vorigekolom != NULL){
		volgendekolom = vorigekolom->rechts;
		free(vorigekolom);
		vorigekolom = volgendekolom;

	}

	//rij
	vorigerij=s->eersterij;
	while(vorigerij != NULL){
		volgenderij = vorigerij->onder;
		free(vorigerij);
		vorigerij=volgenderij;
	}

	//gegevens
	for(i=0; i< NEGEN ; i++){
		free(s->gegevens[i]) ;
	}
	free(s->gegevens);

	free(s);
}

void print_sudoku_rijkolom(Sudoku* s){
	unsigned int i,j;
	SudokuKolom *volgendekolom=NULL, *vorigekolom=NULL, *laatstekolom=NULL ;
	SudokuRij *volgenderij=NULL, *vorigerij=NULL, *laatsterij=NULL ;

	printf("Sudoku: \n");

	//header
	printf("   |");
	for(j=0; j < NEGEN ; j++){
		printf("  %i ", j+1);
	}
	printf("\n");
	printf("   |");
	for(j=0; j < NEGEN ; j++){
		printf(" RK ");
	}
	printf("\n");
	printf("   |");
	for(j=0; j < NEGEN ; j++){
		printf("____", j+1);
	}
	printf("\n");

	for(i=0; i < NEGEN ; i++){
		//header ervoor
		printf("%i  |",i+1);
		for(j=0; j < NEGEN ; j++){
			printf(" %i%i ", s->gegevens[i][j].rijnr,s->gegevens[i][j].kolomnr);
				
		}
		printf("\n");
	}


	//printkolommen
	printf("kolommen: ");
	vorigekolom=s->eerstekolom;
	while(vorigekolom != NULL){
		laatstekolom = vorigekolom;
		volgendekolom = vorigekolom->rechts;
		printf("%i ", vorigekolom->kolomnr);
		vorigekolom = volgendekolom;
	}
	printf("\n");
	vorigekolom=laatstekolom;
	while(vorigekolom != NULL){
		volgendekolom = vorigekolom->links;
		printf("%i ", vorigekolom->kolomnr);
		vorigekolom = volgendekolom;
	}
	printf("\n");


	//print rijen
	printf("rijen: ");
	vorigerij=s->eersterij;
	while(vorigerij != NULL){
		laatsterij=vorigerij;
		volgenderij = vorigerij->onder;
		printf("%i ", vorigerij->rijnr);
		vorigerij=volgenderij;
	}
	printf("\n");
	vorigerij=laatsterij;
	while(vorigerij != NULL){
		volgenderij = vorigerij->boven;
		printf("%i ", vorigerij->rijnr);
		vorigerij=volgenderij;
	}

	printf("\n");
}