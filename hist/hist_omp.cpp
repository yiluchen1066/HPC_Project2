#include "walltime.h"
#include <iostream>
#include <random>
#include <omp.h>

#define VEC_SIZE 1000000000
#define BINS 16

using namespace std;

int main() {
  double time_start, time_end;

  // Initialize random number generator
  unsigned int seed = 123;
  float mean = BINS / 2.0;
  float sigma = BINS / 12.0;
  std::default_random_engine generator(seed);
  std::normal_distribution<float> distribution(mean, sigma);

  // Generate random sequence
  // Note: normal distribution is on interval [-inf; inf]
  //       we want [0; BINS-1]
  int *vec = new int[VEC_SIZE];
  for (long i = 0; i < VEC_SIZE; ++i) {
    vec[i] = int(distribution(generator));
    if (vec[i] < 0)
      vec[i] = 0;
    if (vec[i] > BINS - 1)
      vec[i] = BINS - 1;
  }

  // Initialize histogram
  // Set all bins to zero
  long dist[BINS];
  for (int i = 0; i < BINS; ++i) {
    dist[i] = 0;
  }
  long dist_private[BINS];
  for (int i = 0; i < BINS; ++i)
  {
    dist_private[i] = 0; 
  }
  

  time_start = wall_time();

  // TODO Parallelize the histogram computation
  /*
  long i; 
  #pragma omp parallel for default(shared) private(i) reduction (+:dist) 
  for (i = 0; i < VEC_SIZE; ++i) {
    dist[vec[i]]++;
  }
  time_end = wall_time();
  */ 

  long i; 
  int j; 
  #pragma omp parallel default(none) firstprivate(dist_private,vec) shared(dist)
  {
    #pragma omp for schedule(static) 
    for (i = 0; i < VEC_SIZE; ++i)
    {
      dist_private[vec[i]]++;
    }
    
    //merge
    for (j = 0; j < BINS; j++)
      {
        #pragma omp atomic
        dist[j] += dist_private[j]; 
      }  
    
  }
  time_end = wall_time(); 

  // Write results
  for (int i = 0; i < BINS; ++i) {
    cout << "dist[" << i << "]=" << dist[i] << endl;
  }
  cout << "Time: " << time_end - time_start << " sec" << endl;

  delete[] vec;

  return 0;
}
