export OMP_NUM_THREADS=1
./hist_omp

export OMP_NUM_THREADS=2
./hist_omp

export OMP_NUM_THREADS=4
./hist_omp

export OMP_NUM_THREADS=8
./hist_omp

export OMP_NUM_THREADS=16
./hist_omp

export OMP_NUM_THREADS=24
./hist_omp

export OMP_NUM_THREADS=1
./hist_seq
