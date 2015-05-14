#include <stdio.h>
#include <math.h>
#include <time.h>
#define DIM 4
#define ITER 10
#define test_index 10
#define DEBUG 0

void init_S(int *matrix);
void init_P(int *matrix, int *poss);
void print_matrix(int *matrix, int row, int col, int exclude, int indent);
void check_box(int *matrix, int *poss, int index);
void check_row(int *matrix, int *poss, int index);
void fill_in(int *matrix, int *poss, int *seq, int index);

int main(int argc, char *argv[]){
	int i,j,k,l,m;
	int iter_check=0;	
	/* Creating and initializing the Sudoku S as an MxN matrix */
	int S[DIM*DIM];		//S, the sudoku array, all elements are put in row
	int P[DIM*DIM*DIM];	//P, the array which lists the possible values for each sudoku element. Value -1 for filled in values; value 0 or 1 for (non)possible values
	int Q[DIM*DIM+1];		//Q, the array that holds the sequence of the solved values

	for (i=0; i<DIM*DIM; i++){
		S[i]= 0;
	}

	for (i=0; i<DIM*DIM*DIM; i++){
		P[i] = 1;
	}
	
	for (i=0; i<DIM*DIM+1; i++){
		Q[i] = 0;
	}
	Q[0]=1;	

	for (l=0; l<DIM*DIM; l++){
		if(S[l]!= 0){
			for(m=0; m<DIM; m++){
				P[DIM*l+m]=-1;
			}
		}
	}
	printf("-------------------------------------------------------\n");
	printf("----------Joeri's-Super-Awesome-Sudoku-Solver----------\n");
	printf("-------------------------------------------------------\n\n");

	printf("Sudoku dimension: %d x %d \n", DIM, DIM);

	init_S(&S[0]);
	init_P(&S[0],&P[0]);

	printf("The unsolved Sudoku is: \n");
	print_matrix(&S[0],DIM,DIM, -1, 1);

	if (DEBUG){
		print_matrix(&P[0],DIM*DIM,DIM, -1, 0);
	}

	iter_check = Q[0];

	clock_t start=clock();

	for(l=0; l<ITER; l++){
		iter_check = Q[0];
		for (k=0; k<DIM*DIM; k++){
			if(*(P+DIM*k)!=-1){
				check_row(&S[0], &P[0],k);
				check_box(&S[0], &P[0],k); 
				fill_in(&S[0], &P[0],&Q[0],k); 
				if(DEBUG){
					printf("Checked cell %d\n",k);
					print_matrix(&S[0],DIM,DIM, -1, 1);
					print_matrix(&P[0],DIM*DIM,DIM, -1, 0);
				}
			}
		}
		if(DEBUG){
			printf("After iteration %d the matrix is:\n",l);
			print_matrix(&S[0],DIM,DIM, -1, 1);
		}
		if(Q[0]==iter_check) break;	
	}
	
	clock_t stop = clock();	

	printf("The solved Sudoku is:\n");
	print_matrix(&S[0],DIM,DIM, -1, 1);
	printf("The computer needed %d iterations and %.6f seconds.\n What was your time, you puny human?\n\n", l, (double) (stop-start)/CLOCKS_PER_SEC);
	return 0;
}


	/* Entering the intial condition of the Sudoku */

void init_S(int *matrix){
	*(matrix+1)=1;
	*(matrix+2)=2;
	*(matrix+3)=3;
	*(matrix+8)=1;
	*(matrix+11)=4;
}

void init_P(int *matrix, int *poss){
	int i, j;
	for(i=0; i<DIM*DIM; i++){
		if(*(matrix+i)!=0){
			for(j=0; j<DIM; j++){
				*(poss+DIM*i + j) = -1;	
			}
		}			
	}	
}

void print_matrix(int *matrix, int row, int col, int exclude, int indent){
	int i,j,s;
	int row_ex, col_ex;
	int dim_int;
	double dim;	
	
	dim = pow(DIM, 0.5);
	dim_int = (int) dim;

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
		printf("\n");
		for(j=0; j<col; j++){
			if (i==row_ex && j == col_ex)	
				printf("\t *");
			else
				printf("\t %d", *(matrix+i*DIM+j));
			
			if(indent && j!=0 && j!=(row-1) && j%dim_int==(dim_int-1)){
				printf("\t");
			}
		}
		printf("\n");
		if(indent && i!=0 && i!=(row-1) && i%dim_int==(dim_int-1)){
			printf("\n");
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
				printf("row_el %d removed\n", el_row);
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
	double box_dim_double;
	
	col = index%DIM;
	row = (index-col)/DIM;
	box_dim_double = pow(DIM, 0.5);
	box_dim = (int) box_dim_double;
		
	box_col = (col-col%box_dim)/box_dim;	// column of Top Left item of box
	box_row = (row-row%box_dim)/box_dim;	// row of Top Left item of box
	//printf("element with index %d is located in box_row %d and box_col %d\n",index, box_row, box_col);	
	if(box_dim%1!=0){
		printf("Dimension does not allow for partitioning of the sudoku into boxes.");
	}
	else{
		for(i=0; i<box_dim; i++){					//progress through elements in the box where the index is located
			for(j=0; j<box_dim; j++){
				box_el = DIM*(box_row*box_dim + i) + box_col*box_dim + j;	//box_element being checked
			//	printf("index %d is part of the box for element %d\n", box_el, index);  
				if (box_el != index){					//ignore the box_element which needs to be filled in
					value = *(matrix + box_el);			//read value of cell in box
					if (value != 0)
						*(poss + index*DIM + value - 1) = 0;	//set possibility of found value for this element in the sudoku to 'O'
				}
			}
		}
	}
}

void fill_in(int *matrix, int *poss, int *seq, int index){
	int i,j,k,l,m,sum;
	int next = *(seq);

	sum = 0;
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
		*(seq+next)=index;
		*(seq)=next+1;
	}
}
