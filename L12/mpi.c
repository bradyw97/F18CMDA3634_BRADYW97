#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv){



  int rank, size;

  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  
  long long int Ninside = 0; // number of random points inside 1/4 circle
  long long int Ntests = 100;
  long long n;
  
 

  if (rank == 0) {
    
    MPI_Status status;

    long long int TNinside = 0;

    

    for (int i = 1; i < size; ++i) {

      long long int insideCount;

      MPI_Recv(&insideCount, 1, MPI_LONG_LONG, i, 99, MPI_COMM_WORLD, &status);
      TNinside = TNinside + insideCount;
    }



    
    double estpi = 4.*(TNinside/((double)Ntests*(double)(size-1)));
      printf("estPi = %lf\n", estpi);
	      
  }

  else {

    double estpi = 0;
    
    srand48(rank);
  
    for(n=0;n<Ntests;++n){
      double x = drand48();
      double y = drand48();
    
      if(x*x+y*y<1){
	++Ninside;
      }
    }

  
    
    MPI_Send(&Ninside, 1, MPI_LONG_LONG, 0, 99, MPI_COMM_WORLD);

   
  }

   

  MPI_Finalize();
  return 0;
}
