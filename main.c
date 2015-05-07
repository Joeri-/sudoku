#include <stdio.h>
#define DIM 4

void print_matrix(int *matrix, int row, int col, int exclude);
void check_row(int *matrix, int *poss, int index);

int main(int argc, char *argv[]){
	int i,j;
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
	
	print_matrix(&P[0],DIM*DIM,DIM,-1);
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
		
	print_matrix(&S[0],DIM,DIM, index);
	check_row(&S[0], &P[0], index);
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

	col = index%DIM;
	row = (index-col)/DIM;	
	
//	printf("\nFor index: %d", index);
//	printf("\nThe row number is: %d", row);
//	printf("\nThe column number is: %d", col);
//	printf("\n");

	for(i=0; i<DIM; i++){
		el_row = *(matrix + (row*DIM + i));
		el_col = *(matrix + (i*DIM + col));
		if (el_row == row && el_col == col);
		else{
			if (el_row != 0)
				*(poss+index*DIM+el_row-1)=0;
			if (el_col != 0)
				*(poss+index*DIM+el_col-1)=0;
		}
//		printf("%d \n", el_col);
//		el_block = 0;
	}

	for (i=0; i<DIM; i++)
		printf("%d\n", *(poss+index+i));
	
}
