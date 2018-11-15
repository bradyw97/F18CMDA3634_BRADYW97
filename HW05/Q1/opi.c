#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>



int main(int argc, char **argv){


  // takes command line arg for how many threads akah wants
  int Nthreads = atoi(argv[1]);

  // does some akah
  struct drand48_data buff;
   


  long long int Ninside; // number of random points inside 1/4 circle
 
  long long int Ntests = 1000;
  long long n;
  double x, y, t_start, t_end, estpi;

    // declares no. of threads
  omp_set_num_threads(Nthreads);
  
  t_start = omp_get_wtime();
  Ninside = 0;

  srand48_r(omp_get_thread_num(), &buff);

#pragma omp for reduction(+:Ninside)
  
  for(n=0;n<Ntests;++n){
    drand48_r(&buff, &x);
    drand48_r(&buff, &y);
    
    if(x*x+y*y<1){
      ++Ninside;
    }
  }

  
  estpi = 4.*(Ninside/(double)Ntests);

  t_end = omp_get_wtime();

  printf("estPi = %lf\n", estpi);
  printf("time elapsed = %f\n", t_end-t_start);
  
  return 0;
}
