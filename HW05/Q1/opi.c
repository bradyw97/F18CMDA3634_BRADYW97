#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char **argv){

  int Nthreads = atoi(argv[1]);
  omp_set_num_threads(Nthreads);

  long long int Ninside = 0; // number of random points inside 1/4 circle
  long long int Ntests = 1000000000;
  long long n;

  int rank = omp_get_thread_num();

  double estpi = 0;

  //srand48(12345);

  double start = omp_get_wtime();

#pragma omp parallel reduction(+:Ninside)
  {
  struct drand48_data buffer;
  srand48_r(rank,&buffer);

  for(n=0;n<Ntests;++n){
    double x = drand48_r(&buffer,&x);
    double y = drand48_r(&buffer,&y);
    
    if(x*x+y*y<1){
      ++Ninside;
    }
  }
  }
  double end = omp_get_wtime();

  estpi = 4.*(Ninside/((double)Ntests*Nthreads));

  printf("estPi = %lf\n", estpi);
  printf("elapsed: %lf\n",end-start);
  printf("num ranks: %d\n",Nthreads);

  exit(0);
  return 0;
}
