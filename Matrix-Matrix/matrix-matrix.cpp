#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define NCOLS 6
int main(int argc, char **argv) {
	int i,j,k,l;
	int ierr, rank, size, root;
	float A[NCOLS][NCOLS], Apart[NCOLS];
	float B[NCOLS][NCOLS], Bpart[NCOLS];
	float C[NCOLS][NCOLS];
	float A_exact[NCOLS][NCOLS];
	

	root = 0;
	/* Initiate MPI. */
	ierr=MPI_Init(&argc, &argv);
	ierr=MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	ierr=MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	/* Initialize B and C. */
	srand(time(NULL)); 
    	for (int row = 0; row < NCOLS; row++) {
        	for (int col = 0; col < NCOLS; col++) {
            		B[row][col] = rand() % 4;
            		C[row][col] = rand() % 8;
        	}
    	}

	/* Put up a barrier until I/O is complete */
	ierr=MPI_Barrier(MPI_COMM_WORLD);
	/* Scatter matrix B by rows. */
	ierr=MPI_Scatter(B,NCOLS,MPI_FLOAT,Bpart,NCOLS,MPI_FLOAT,root, MPI_COMM_WORLD);
	
	float sum = 0.0;
    	for (int i = 0; i < NCOLS; i++) {
        	for (int j = 0; j < NCOLS; j++) {
            		sum += Bpart[j] * C[j][i];
        	}
        	Apart[i] = sum;
        	sum = 0.0;
    	}
	
    	MPI_Gather(Apart, NCOLS, MPI_FLOAT, A, NCOLS, MPI_FLOAT, root, MPI_COMM_WORLD);

    	// sync all processes
    	MPI_Barrier(MPI_COMM_WORLD);


    	// print the resulting matrix A from root process
    	if (rank == root) {
        	printf("Original matrices: \n");
		printf("B: \n");
		for (int i = 0; i < NCOLS; i++) {
			for (int j = 0; j < NCOLS; j++) {
				printf(" %g", B[i][j]);
			}
		printf("\n");
		}
		printf("\n");
	
		printf("C: \n");
		for (int i = 0; i < NCOLS; i++) {
			for (int j = 0; j < NCOLS; j++) {
				printf(" %g", C[i][j]);
			}
		printf("\n");
		}
		printf("\n");

        	printf("This is the result of the parallel computation: \n");
        	printf("A: \n");
		for (int i = 0; i < NCOLS; i++) {
			for (int j = 0; j < NCOLS; j++) {
				printf(" %g", A[i][j]);
			}
		printf("\n");
		}
		printf("\n");

        	printf("\nThis is the result of the serial computation: \n");
        	// compute sequintially
        	for (int i = 0; i < NCOLS; i++) {
            		for (int j = 0; j < NCOLS; j++) {
                		A_exact[i][j] = 0.0;
                		for (int k = 0; k < NCOLS; k++) {
                    			A_exact[i][j] += B[i][k] * C[k][j];
                		}
            		}
        	}

        	printf("A_exact: \n");
		for (int i = 0; i < NCOLS; i++) {
			for (int j = 0; j < NCOLS; j++) {
				printf(" %g", A_exact[i][j]);
			}
		printf("\n");
		}
		printf("\n");
    	}
	
	MPI_Finalize();
}
