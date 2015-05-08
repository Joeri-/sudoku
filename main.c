#include <stdio.h>
#define DIM 4

void print_matrix(int *matrix, int row, int col, int exclude);
void check_row(int *matrix, int *poss, int index);

int main(int argc, char *argv[]){
	int i,j,k,l,m;
	int index = 10;
	
	/* Creating and initializing the Sudoku S as an MxN matrix */
	int S[DIM*DIM];
	for (i=0; i<DIM*DIM; i++){
		S[i]= 0;
	}

	//print_matrix(&S[0],DIM,DIM);
	
	/* start the iteration cyclus */

	int P[DIM*DIM*DIM];

	for (i=0; i<DIM*DIM*DIM; i++){
		P[i] = 1;
	}
	
//	print_matrix(&P[0],DIM*DIM,DIM,-1);
	int Q[DIM*DIM];
	
	for (i=0; i<DIM*DIM; i++){
		Q[i] = 0;
	}
	

	/* Entering the intial condition of the Sudoku */

	S[1]=1;
	S[2]=2;
	S[3]=3;
	S[8]=1;
	S[9]=2;
	S[10]=3;
	S[11]=4;
		

	for (l=0; l<DIM*DIM; l++){
		if(S[l]!= 0){
			for(m=0; m<DIM; m++){
				P[DIM*l+m]=-1;
				printf("%d\n", DIM*l+m);
			}
		}
	}

	print_matrix(&S[0],DIM,DIM, index);

	for (k=0; k<DIM*DIM; k++){
		check_row(&S[0], &P[0],k);
	}
	print_matrix(&P[0],DIM*DIM,DIM, -1);
	return 0;
}


void print_matrix(int *matrix, int row, int col, int exclude){
	int i,j;
	int row_ex, col_ex;
	
	if(exclude == -1){
		row_ex = -1;
		col_ex = -1;
	}
	else{
		row_ex = (exclude - exclude%DIM)/DIM;
		col_ex = exclude%DIM;
	}
	printf("\n");
	
	for(i=0; i<row; i++){
		printf("\n |");
		for(j=0; j<col; j++){
			if (i==row_ex && j == col_ex)	
				printf("\t X \t|");
			else
				printf("\t %d \t|", *(matrix+i*DIM+j));
		}
	}
	printf("\n");
}

void check_row(int *matrix, int *poss, int index){
	int i;	
	int row, col;
	int el_row, el_col, el_block;

	col = index%DIM;			//determine the column of the selected square
	row = (index-col)/DIM;			//determine the row the selected square
	
//	printf("\nFor index: %d", index);
//	printf("\nThe row number is: %d", row);
//	printf("\nThe column number is: %d", col);
//	printf("\n");

	for(i=0; i<DIM; i++){
		el_row = *(matrix + (row*DIM + i));
		el_col = *(matrix + (i*DIM + col));
		
		if (row*DIM + i == i*DIM + col){}
		else{
			
				poss_row = poss+index*DIM+el_row-1;
				poss_col = poss+index*DIM+el_col-1;
			if (el_row != 0)
				*(poss+index*DIM+el_row-1)=0;
				//printf("row_el %d removed\n", el_row);
			if (el_col != 0)
				*(poss+index*DIM+el_col-1)=0;
				//printf("col_el %d removed\n", el_col);
		}
//		printf("%d \n", el_col);
//		el_block = 0;
	}
}
