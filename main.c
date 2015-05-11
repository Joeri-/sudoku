#include <stdio.h>
#include <math.h>

#define DIM 4
#define ITER 5
#define test_index 10
#define DEBUG 0

void print_matrix(int *matrix, int row, int col, int exclude);
void check_box(int *matrix, int *poss, int index);
void check_row(int *matrix, int *poss, int index);
void fill_in(int *matrix, int *poss, int index);

int main(int argc, char *argv[]){
	int i,j,k,l,m;
	
	/* Creating and initializing the Sudoku S as an MxN matrix */
	int S[DIM*DIM];
	for (i=0; i<DIM*DIM; i++){
		S[i]= 0;
	}

	if (DEBUG){
		printf("Sudoko dimension: %d x %d \n", DIM, DIM);
		printf("The initialised matrix S is: \n");
		print_matrix(&S[0],DIM,DIM, -1); 
	}	

	/* start the iteration cyclus */

	int P[DIM*DIM*DIM];

	for (i=0; i<DIM*DIM*DIM; i++){
		P[i] = 1;
	}
	
	if (DEBUG){
		printf("The initialised possibility matrix P is: \n");
		print_matrix(&P[0],DIM,DIM, -1);
	}	

	int Q[DIM*DIM];
	
	for (i=0; i<DIM*DIM; i++){
		Q[i] = 0;
	}
	

	/* Entering the intial condition of the Sudoku */
//-----------------------------------------------------------------------

	S[1]=1;
	S[2]=2;
	S[3]=3;
	S[8]=1;
	S[9]=2;
	S[11]=4;

/*--------------------------------------------------------------------*/
	for (l=0; l<DIM*DIM; l++){
		if(S[l]!= 0){
			for(m=0; m<DIM; m++){
				P[DIM*l+m]=-1;
				//printf("%d\n", DIM*l+m);
			}
		}
	}


	if (DEBUG){
		printf("The initial matrix is: \n");
		print_matrix(&S[0],DIM,DIM, test_index);
		check_row(&S[0], &P[0],test_index);
		check_box(&S[0], &P[0],test_index); 
	}
	else{
		for(l=0; l<ITER; l++){
			for (k=0; k<DIM*DIM; k++){
				if(*(P+DIM*k)!=-1){
					check_row(&S[0], &P[0],k);
					check_box(&S[0], &P[0],k); 
					fill_in(&S[0], &P[0],k); 
				}

				print_matrix(&S[0],DIM,DIM, -1);
			}
		}
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
	printf("\n\n");
}

void check_row(int *matrix, int *poss, int index){
	int i;	
	int row, col;
	int el_row, el_col, el_block;

	col = index%DIM;			//determine the column of the selected square
	row = (index-col)/DIM;			//determine the row the selected square
	
	for(i=0; i<DIM; i++){
		el_row = *(matrix + (row*DIM + i));
		el_col = *(matrix + (i*DIM + col));
		
		if (row*DIM + i == i*DIM + col){}
		else{			

			if (el_row != 0)
				*(poss+index*DIM+el_row-1)=0;
				if(DEBUG)
				//printf("row_el %d removed\n", el_row);
			if (el_col != 0)
				*(poss+index*DIM+el_col-1)=0;
				//printf("col_el %d removed\n", el_col);
		}
	}
}

void check_box(int *matrix, int *poss, int index){
	int i, j;
	int col, row, value;
	int box_dim, box_row, box_col, box_el;
	
	col = index%DIM;
	row = (index-col)/DIM;
	box_dim = pow(DIM, 0.5);
		
	box_col = col-col%box_dim;	// column of Top Left item of box
	box_row = row-row%box_dim;	// row of Top Left item of box
	
	if(box_dim%1!=0){
		printf("Dimension does not allow for partitioning of the sudoku into boxes.");
	}
	else{
		for(i=0; i<box_dim; i++){					//progress through elements in the box where the index is located
			for(j=0; j<box_dim; j++){
				box_el = (DIM*box_row + i*box_row) + (box_col + j);	//box_element being checked
				if (box_el != index){					//ignore the box_element which needs to be filled in
					value = *(matrix + box_el);			//read value of cell in box
					if (value != 0)
						*(poss+index*DIM + value-1) = 0;	//set possibility of found value for this element in the sudoku to 'O'
				}
			}
		}
	}
}

void fill_in(int *matrix, int *poss, int index){
	int i,j,k,sum;

	for(i=0; i<DIM; i++){
		sum+= *(poss + index*DIM + i);
	}	
	if(sum == 1){
		for(j=0; j<DIM; j++){
			if(*(poss + index*DIM + j)==1){
				*(matrix+index)=j+1;
			}	
		}	
		for(k=0; k<DIM; k++){
			*(poss + index*DIM + k)=-1;
		}	
	}
}
