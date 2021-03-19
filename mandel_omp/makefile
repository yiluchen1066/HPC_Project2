all: mandel_omp

mandel_omp: mandel_omp.c pngwriter_omp.c
	gcc -o $@ -I. -O3 $^ -lpng -fopenmp

clean:
	rm -rf mandel_omp

