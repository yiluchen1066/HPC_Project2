#include "walltime.h"
#include <math.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int N = 2000000000;
  double up = 1.00000001;
  double Sn = 1.00000001;
  double originSn; 
  int n, lastn;
  /* allocate memory for the recursion */
  double *opt = (double *)malloc((N + 1) * sizeof(double));

  if (opt == NULL)
    die("failed to allocate problem size");

  originSn = 1.0; 
  lastn = -2; 

  double time_start = wall_time();
  // TODO: YOU NEED TO PARALLELIZE THIS LOOP
  #pragma omp parallel for firstprivate(lastn) lastprivate(Sn)
  for (n = 0; n<= N; n++)
  {
    if (lastn == n-1)
    {
      Sn *= up; 
    } else
    {
      Sn = originSn * pow(up, n); 
    }

    opt[n] = Sn; 
    lastn = n; 
  }
  Sn = Sn*up; 
  
  /*
  for (n = 0; n <= N; ++n) {
    opt[n] = Sn;
    Sn *= up;
  }
  */ 

  printf("Parallel RunTime   :  %f seconds\n", wall_time() - time_start);
  printf("Final Result Sn    :  %.17g \n", Sn);

  double temp = 0.0;
  for (n = 0; n <= N; ++n) {
    temp += opt[n] * opt[n];
  }
  printf("Result ||opt||^2_2 :  %f\n", temp / (double)N);
  printf("\n");

  return 0;
}
