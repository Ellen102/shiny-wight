#include "Sudoku.h"
#include "Printer.h"

int del_vakje_sudoku(Sudoku* s , SudokuVakje* vakje){
	int i,j,oorspronkelijk,k,r;
	SudokuVakje* omliggend,ander;
	oorspronkelijk = vakje->inhoud;
	vakje->inhoud = 0;
	vakje->gevonden = F;

	//bepaal nieuwe inhoud 
	// bekijk de andere vakjes
	omliggend=vakje->rechts;
	for(i=vakje->rijnr; i<NEGEN; i++){
		if(omliggend->gevonden == F){
			//kijken of er geen ander vakje op dit vakje dezelfde waarde heeft of de oorspronkelijke waarde anders kan het toch nog neit
			for(k=0;k<NEGEN;k++){
				//.... de kolom en vierkant afgaan 
				//if(ander.inhoud er al in zit continue;
			}

			//toevoegen aan het andere
			omliggend->inhoud = vakje->inhoud & (1<<(oorspronkelijk-1) ^ FULL);

		}else{
			vakje->inhoud = vakje->inhoud | (1<<(omliggend->inhoud-1)); //de inhoud kan geen mogelijkheid zijn meer voor vakje
		}
	
	}
	for(i=vakje->rijnr; i>=0; i--){
	
	
	}

	return -1;
}




void clear_sudoku(Sudoku* s){
	SudokuKolom *k1=NULL;
	SudokuRij *r1=NULL;
	int i,j;
	 
	k1 = s->eerstekolom;
	r1 = s->eersterij;

	for(i=0; i < NEGEN ; i++){
		for(j=0; j<NEGEN; j++){
			s->gegevens[i][j].inhoud = 0;
			s->gegevens[i][j].gevonden = F;
		}
		k1->inhoud = 0;
		r1->inhoud =0;
		k1 = k1->rechts;
		r1 = r1->onder;
	}

	for(i=0; i < NEGEN ; i=i+3){
		for(j=0; j < NEGEN ; j=j+3){
			s->gegevens[i][j].vierkant->inhoud = 0;
		}
	}
	

}


int simple_insert(Sudoku* s, SudokuVakje* vakje, int n){
	int r;
	r=insert_vakje(s,vakje,n);
	vind_uniek(s,vakje->rijnr,vakje->kolomnr);
	return r;

}

int insert_vakje(Sudoku* s, SudokuVakje* vakje, int n){
	int r,k;
	SudokuVakje *volgende=NULL, *next=NULL;
	int i,j;
	r= vakje->rijnr -1;
	k= vakje->kolomnr -1;


	if(vakje->gevonden==T)return BEZET;
	if(vakje->inhoud & (1<<(n-1)) )return ONMOGELIJK;

	vakje->inhoud=n;
	vakje->gevonden=T;

	volgende=vakje->rij->eerste;
	vakje->rij->inhoud= vakje->rij->inhoud | (1<<(n-1));
	while(volgende != NULL){
		if(volgende->gevonden == F){
			volgende->inhoud = volgende->inhoud | (1<<(n-1));
		}
		volgende=volgende->rechts;
	}

	volgende=vakje->kolom->eerste;
	vakje->kolom->inhoud= vakje->kolom->inhoud | (1<<(n-1));
	while(volgende != NULL){
		if(volgende->gevonden == F){
			volgende->inhoud = volgende->inhoud | (1<<(n-1));
		}
		volgende=volgende->onder;
	}

	vakje->vierkant->inhoud = vakje->vierkant->inhoud | (1<<(n-1));
	volgende=vakje->vierkant->linksboven;
	next=volgende;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(volgende->gevonden == F && (i != r) && (j!=k)) {
				volgende->inhoud = volgende->inhoud | (1<<(n-1));
			}
			volgende=volgende->rechts;
		}
		next=next->onder;
		volgende=next;
	}

	return MOGELIJK;

}

int eenmogelijkheid(int n){
	int xor,i;
	xor = n ^ FULL;
	for(i=0;i<=9;i++){
		if(xor == (1<<i)){
			return i+1;

		}
	}
	return 0;
}

void vind_uniek(Sudoku* s, int r, int k){
	SudokuVakje * vakje=NULL, *volgende=NULL, *next=NULL;
	int i,j,v;

	r=r-1;
	k=k-1;
	vakje = &(s->gegevens[r][k]);
	volgende=vakje->rij->eerste;
	while(volgende != NULL){
		if(volgende->gevonden == F){
			v=eenmogelijkheid(volgende->inhoud);
			if(v != 0){
				simple_insert(s,volgende,v);
			}
		}
		volgende=volgende->rechts;
	}

	volgende=vakje->kolom->eerste;
	while(volgende != NULL){
		if(volgende->gevonden == F){
			v=eenmogelijkheid(volgende->inhoud);
			if(v != 0){
			simple_insert(s,volgende,v);
			}
		}
		volgende=volgende->onder;
	}

	volgende=vakje->vierkant->linksboven;
	next=volgende;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(volgende->gevonden == F && (i != r) && (j!=k)) {
				 v=eenmogelijkheid(volgende->inhoud);
				if(v != 0){
					simple_insert(s,volgende,v);
				}
			}
			volgende=volgende->rechts;
		}
		next=next->onder;
		volgende=next;
	}
	 


}


//vul de waarde in en schrap het als mogelijkheid bij de andere
int insert_sudoku(Sudoku* s,int r,int k,int n){
	SudokuVakje * vakje=NULL, *volgende=NULL, *next=NULL;

	r=r-1;
	k=k-1;
	vakje = &(s->gegevens[r][k]);

	return simple_insert(s,vakje,n);

}



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
				s->gegevens[i][j].inhoud = 0;
				s->gegevens[i][j].gevonden = F;
			}

	}

	//kolommen
	k1 = (SudokuKolom*) malloc(sizeof(SudokuKolom));
	k1->links = NULL;
	k1->kolomnr = 1;
	k1->inhoud =0;
	k1->eerste = &(s->gegevens[0][0]);
	vorigekolom=k1;
	for(i=1; i < NEGEN ; i++){
		volgendekolom = (SudokuKolom*) malloc(sizeof(SudokuKolom));
		volgendekolom->kolomnr=i+1;
		volgendekolom->inhoud =0;
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
	r1->inhoud =0;
	r1->eerste = &(s->gegevens[0][0]);
	vorigerij=r1;
	for(i=1; i < NEGEN ; i++){
		volgenderij = (SudokuRij*) malloc(sizeof(SudokuRij));
		volgenderij->rijnr = i+1;
		volgenderij->eerste = &(s->gegevens[i][0]);
		volgenderij->inhoud =0;
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
					v1->vierkantnr = c;c++;
					v1->inhoud =0;
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
	printf("    ");
	for(j=0; j < NEGEN ; j++){
		if(j % 3 == 0  && j != 0) printf(" ");	
		printf("  %i ", j+1);
	}
	printf(" ");	
	printf("\n");
	printf("    ");
	for(j=0; j < NEGEN ; j++){
		if(j % 3 == 0  && j != 0) printf("_");	
		printf("____");
	}
	printf("\n");
	//de tablegedeelte
	for(i=0; i < NEGEN ; i++){
		//scheiding vierkant
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
			if(s->gegevens[i][j].gevonden == T){
				printf("  %i ",  s->gegevens[i][j].inhoud);
			}else{
				printf("  . ");
			}
			
		}
		printf("|");	
		printf("\n");
		
	}
	//lijntje eronder
	printf("    ");
	for(j=0; j < NEGEN ; j++){
		if(j % 3 == 0  && j != 0) printf("_");	
		printf("____");
	}
	printf("\n");


}