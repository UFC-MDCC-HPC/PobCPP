#include "pob_bucketsort.h"

#include <cstdio>
#include <cstdlib> /* for random function */
#include <iostream>

void BucketSort::Worker::make_numbers(long int big_array[], int n, int n_bar, int p) {
	/* Puts numbers in "buckets" but we can treat it otherwise */
	int i, q;

	for (q = 0; q < p; q++) {
		for (i = 0; i < n_bar; i++) {
			big_array[q*n_bar+i] = random() % (2*n/p) + (q*2*n/p);
		}
	}
} 

void BucketSort::Worker::sequential_sort(long int array[], int size) {
	/* Use selection sort to sort a list from smallest to largest */
	int eff_size, minpos_;
	long int temp;

	for(eff_size = size; eff_size > 1; eff_size--) {
		minpos_ = minpos(array, eff_size);
		temp = array[minpos_];
		array[minpos] = array[eff_size-1];
		array[eff_size-1] = temp;
	}
}

int BucketSort::Worker::minpos(long int array[], int eff_size) {
	int i, minpos = 0;

	for (i=0; i<eff_size; i++)
		minpos = array[i] > array[minpos] ? i: minpos;
	return minpos;
}


void Bucketsort::Worker::sort() {
	long int * big_array;
	long int * local_array;
	int n=800; /* default is 80 elements to sort */
	int n_bar; /* = n/p */
	long int number;
	int p;
	int my_rank;
	int i;
	double start, stop; /* for timing */

	//MPI_Init(&argc, &argv);
	//MPI_Comm_size(MPI_COMM_WORLD, &p);
	//MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if (i == 0) {

		start = MPI_Wtime(); /* Timing */

		/* check if parameters are valid */
		if (n%p != 0) {
			std::cerr << "The number of processes must evenly divide total elements." << std::endl;
			exit(1);
		}

		/* make big array */
		big_array = (long int *)malloc(n*sizeof(long int));
		if (big_array==NULL) {
			std::cerr << "Big_array malloc failed!!" << std::endl;
			exit(1);
		}
		std::cout << "Total elements = " << n << "; Each process sorts " << n/p << " elements." << std::endl;
		make_numbers(big_array, n, n/p, p);
	}

	n_bar = n/p;

	local_array = (long int *)malloc(n_bar*sizeof(long int));
	if (local_array==NULL) {
		exit(0);
	}

	/* Can use scatter if numbers are grouped in the big_array */
/*	MPI_Scatter(big_array, n_bar, MPI_LONG,
	local_array, n_bar, MPI_LONG, 0, MPI_COMM_WORLD);*/
	comm->scatter<Worker>(0, big_array, n_bar, local_array);

	/* Put_numbers_in_bucket(big_array, local_array, n, n_bar, p,
	my_rank); */

	sequential_sort(local_array, n_bar);

/*	MPI_Gather(local_array, n_bar, MPI_LONG,
	big_array, n_bar, MPI_LONG, 0, MPI_COMM_WORLD);*/
	comm->gather<Worker>(0, local_array, big_array, n_bar);

	stop = MPI_Wtime();

	if (i == 0) {
		for(j=0; j<n; j++) printf("%7ld %c", big_array[j],
		i%8==7 ? '\n' : ' ');
		std::cout << "Time to sort: " << (stop-start)/0.001 << ", using " << p << " processes" << std::endl;
	}

	free(local_array);
	if (i==0) free(big_array);

}
