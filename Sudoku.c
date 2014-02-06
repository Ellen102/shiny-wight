#include "Sudoku.h"

Sudoku* initlizeSudoku (){
	int i,j,c,a,b;
	SudokuKolom *k1=NULL, *volgendekolom=NULL, *vorigekolom=NULL ;
	SudokuRij *r1=NULL, *volgenderij=NULL, *vorigerij=NULL ;
	SudokuVierkant *v1=NULL,*volgendevierkant=NULL, *vorigevierkant=NULL ;

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
	k1->eerste = &(s->gegevens[0][0]);
	vorigekolom=k1;
	for(i=1; i < NEGEN ; i++){
		volgendekolom = (SudokuKolom*) malloc(sizeof(SudokuKolom));
		volgendekolom->kolomnr=i+1;
		volgendekolom->eerste = &(s->gegevens[0][i]);
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
	r1->eerste = &(s->gegevens[0][0]);
	vorigerij=r1;
	for(i=1; i < NEGEN ; i++){
		volgenderij = (SudokuRij*) malloc(sizeof(SudokuRij));
		volgenderij->rijnr = i+1;
		volgenderij->eerste = &(s->gegevens[i][0]);
		vorigerij->onder = volgenderij;
		volgenderij->boven = vorigerij;
		vorigerij = volgenderij;
	}
	vorigerij->onder=NULL;
	s->eersterij=r1;
	
	//linken tussen vakje -> kolom
	//linken tussen vakjes
	r1=s->eersterij;
	k1=s->eerstekolom;
	for(i=0; i < NEGEN ; i++){
		k1=s->eerstekolom;
		for(j=0; j < NEGEN ; j++){
			s->gegevens[i][j].kolom = k1;
			s->gegevens[i][j].rij = r1;

			//printf("%s %i  ", ( ((i-1) >= 0)? ("ja") : ("nee")),i);
			s->gegevens[i][j].boven = ((i-1) >= 0)? (&(s->gegevens[i-1][j])) : NULL;
			s->gegevens[i][j].onder = ((i+1) < NEGEN)? (&(s->gegevens[i+1][j])) : NULL;
			s->gegevens[i][j].links = ((j-1) >= 0)? (&(s->gegevens[i][j-1])) : NULL;
			s->gegevens[i][j].rechts = ((j+1) < NEGEN)? (&(s->gegevens[i][j+1])) : NULL;

			k1=k1->rechts;
		}
		r1=r1->onder;
	}

		//vierkant
	c=1;
	for(i=0; i < NEGEN ; i=i+3){
		
			for(j=0; j < NEGEN ; j=j+3){
					v1 = (SudokuVierkant*) malloc(sizeof(SudokuVierkant));
					v1->vierkantnr = c;
					c++;
					v1->linksboven = (&(s->gegevens[i][j]));
					for(a=0; a <DRIE ; a++){
						for(b=0; b <3 ; b++){
							s->gegevens[i+a][j+b].vierkant = v1;
						}
					}
					for(a=0; a <DRIE ; a++){
						v1->rijen[a] = s->gegevens[i+a][j].rij;
					}
					for(a=0; a <DRIE ; a++){
						v1->kolommen[a] = s->gegevens[i][j+a].kolom;
					}

	
		}
	}

	return s;
}


void free_sudoku ( Sudoku * s){
	unsigned int i,j;
	SudokuKolom *volgendekolom=NULL, *vorigekolom=NULL ;
	SudokuRij *volgenderij=NULL, *vorigerij=NULL ;


	//vierkant
	for(i=0; i < NEGEN ; i=i+3){
		for(j=0; j < NEGEN ; j=j+3){
			free(s->gegevens[i][j].vierkant);
		}
	}

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
	SudokuVakje *boven=NULL,*onder=NULL,*links=NULL,*rechts=NULL,*vakje=NULL;

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


	//test poitners van vierkantjes
	vakje=&(s->gegevens[5][4]);

	while(vakje != NULL){
		
		printf(" %i%i \n", vakje->rijnr, vakje->kolomnr);
		vakje=vakje->links;

	}

	vakje=&(s->gegevens[5][4]);
	printf("r: %i  k: %i", vakje->rij->rijnr, vakje->kolom->kolomnr);
	printf("vkn: %i  ", vakje->vierkant->vierkantnr);
	for(i=0; i < DRIE; i++){
		printf("r: %i ", vakje->vierkant->rijen[i]->rijnr);
		printf("k: %i ", vakje->vierkant->kolommen[i]->kolomnr);
	}


}



void print_sudoku_inhoud(Sudoku* s){
	unsigned int i,j;

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
		printf("____");
	}
	printf("\n");

	for(i=0; i < NEGEN ; i++){
		if(i % 3 == 0  && i!= 0){
			printf("   |");
			for(j=0; j < NEGEN ; j++){
				printf("----");
			}
			printf("\n");
		}
		
		//header ervoor
		printf("%i  |",i+1);
		
		for(j=0; j < NEGEN ; j++){
			if(j % 3 == 0  && j != 0) printf("|");	
			printf(" %i%i ", s->gegevens[i][j].rijnr,s->gegevens[i][j].kolomnr);
			
		}
		printf("|");	
		printf("\n");
		
	}

}