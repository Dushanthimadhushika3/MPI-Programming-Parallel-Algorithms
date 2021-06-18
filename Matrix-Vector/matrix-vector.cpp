#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define NCOLS 6
int main(int argc, char **argv) {
	int i,j,k,l;
	int ierr, rank, size, root;
	float A[NCOLS],Apart[NCOLS];
	float B[NCOLS][NCOLS],Bpart[NCOLS];
	float C[NCOLS],Cpart[1];
	float A_exact[NCOLS];
	
	root = 0;
	/* Initiate MPI. */
	ierr=MPI_Init(&argc, &argv);
	ierr=MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	ierr=MPI_Comm_size(MPI_COMM_WORLD, &size);

	/* Initialize B and C. */
	srand(time(NULL));
    	for (int row = 0; row < NCOLS; row++) {
        	for (int col = 0; col < NCOLS; col++) {
            		B[row][col] = rand() % 10;
        	}
		C[row] = rand() % 5;
    	}

	/* Put up a barrier until I/O is complete */
	ierr=MPI_Barrier(MPI_COMM_WORLD);
	/* Scatter matrix B by rows. */
	ierr=MPI_Scatter(B,NCOLS,MPI_FLOAT,Bpart,NCOLS,MPI_FLOAT,root, MPI_COMM_WORLD);
	/* Scatter matrix C by columns */
	ierr=MPI_Scatter(C, 1, MPI_FLOAT, Cpart, 1, MPI_FLOAT,root,MPI_COMM_WORLD);

	/* Do the vector-scalar multiplication. */
	for(j=0;j<NCOLS;j++){
		Apart[j] = Cpart[0]*Bpart[j];
	}

	/* Reduce to matrix A. */
	ierr=MPI_Reduce(Apart,A,NCOLS,MPI_FLOAT,MPI_SUM, root, MPI_COMM_WORLD);

	//print results
	if (rank == 0) {
		printf("\nThis is the result of the parallel computation:\n\n");
		for (int row = 0; row < NCOLS; row++) {
            		printf("A[%d] = %g\n", row, A[row]);
        	}

		for(k=0;k<NCOLS;k++) {
			A_exact[k] = 0.0;
			for(l=0;l<NCOLS;l++) {
				A_exact[k] += C[l]*B[l][k];
			}
		}
		printf("\nThis is the result of the serial computation:\n\n");
		for (int row = 0; row < NCOLS; row++) {
            		printf("A_exact[%d] = %g\n", row, A_exact[row]);
        	}
	}
	MPI_Finalize();
}
