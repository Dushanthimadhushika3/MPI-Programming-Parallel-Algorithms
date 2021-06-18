#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int main(int argc, char** argv) {
    
    int gsize,*sendarray; 
    int root, myrank, *rbuf;

    root = 0;
    int count = 100;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    if ( myrank == root) {
        MPI_Comm_size( MPI_COMM_WORLD, &gsize);
        rbuf = (int *)malloc(gsize*count*sizeof(int));
    }

    // random generator
    srand(time(NULL));

    // assign random values to sendarray from (1-10)
    sendarray = (int*)malloc(sizeof(int) * count);
    for (int i = 0; i < count; i++) {
        sendarray[i] = (rand() % 10);
    }

    MPI_Gather( sendarray, count, MPI_INT, rbuf, count, MPI_INT, root, MPI_COMM_WORLD);

    // Print values from the rbuf
    if (myrank == 0) {
        // print some values from the root process
        for (int i = 0; i < 10; i++) {
            printf("rbud value: %d\n", rbuf[i]);
        }
    }

  
    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Finalize();

}
