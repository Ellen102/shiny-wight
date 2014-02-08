#include "Filereader.h"
//#include <conio.h>  /* for clrscr */

int read_sudoku_from_file(char* file, Sudoku* s){
	FILE *fp; /* create a pointer to the file */
	int i,j,v;
	char c,w;

	if(s == NULL)return SUDOKUPOINTERFOUT;

	if((fp = fopen(file, "r")) == NULL)
	{
		return FILENIETOPEN;
	} 

	for(i=1; i <= NEGEN; i++){
		for(j=1; j <= NEGEN; j++){
			c = fgetc(fp);//int
			if(c == EOF ) return FOUTKARAKTER;
			if( c == '.'){
			}else{
				v=c-'0';
				if(v<=0 || v>9  ) return FOUTKARAKTER;
				insert_sudoku(s,i,j,v);
			}
			w = fgetc(fp);//spatie of newline
		}
	}

	printf("file readed \n");

	fclose(fp);
	return GELUKT;
}

int write_sudoku_to_file(char* file, Sudoku* s){
	int i,j;
	FILE *fp;
	fp = fopen(file, "w");
	if (fp == NULL)
	{
		return FILENIETOPEN;
	}


	for(i=0;i<NEGEN;i++){
		for(j=0;j<NEGEN;j++){
			if(s->gegevens[i][j].gevonden == F){
				fprintf(fp,".");
			}else{
				fprintf(fp,"%i",s->gegevens[i][j].inhoud);
			}
			if(j != NEGEN-1)fprintf(fp," ");else fprintf(fp,"\n");

		}

	}


	printf(" writed to file ");
	fclose(fp);
	return GELUKT;

}