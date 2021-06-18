#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

//work method
void work() {
    for (int i = 0; i < INT16_MAX; i++) {
        // simulate workload
    }
}

int main(int argc, char *argv[]) {

   int myrank, numprocs;
   /*variables used for gathering timing statistics*/
   double mytime, maxtime, mintime, avgtime;

   MPI_Init(&argc,&argv); // Initialize

   MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
   MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
   MPI_Barrier(MPI_COMM_WORLD); /*synchronize all processes*/

   mytime = MPI_Wtime(); /*get time just before work section */ 
   
   work(); 
   mytime = MPI_Wtime() - mytime; /*get time just after work section*/
   
   /*compute max, min, and average timing statistics*/ 
   MPI_Reduce(&mytime, &maxtime, 1, MPI_DOUBLE, MPI_MAX, 0,MPI_COMM_WORLD);
   MPI_Reduce(&mytime, &mintime, 1, MPI_DOUBLE, MPI_MIN, 0,MPI_COMM_WORLD); 
   MPI_Reduce(&mytime, &avgtime, 1, MPI_DOUBLE, MPI_SUM, 0,MPI_COMM_WORLD); 
   
   if (myrank == 0) { 
      avgtime /= numprocs;
      printf("Min: %lf Max: %lf Avg: %lf\n", mintime, maxtime,avgtime);
}

    // Finalize the MPI environment.
    MPI_Finalize();
}
