all: mandel_seq mandel_omp

mandel_seq: mandel_seq.c pngwriter.c
	gcc -o $@ -I. -O3 $^ -lpng 

mandel_omp: mandel_omp_3072.c pngwriter.c
	gcc -o $@ -I. -O3 $^ -lpng -fopenmp

clean:
	rm -rf mandel_seq mandel_omp

