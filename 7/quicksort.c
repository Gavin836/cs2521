#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

typedef enum mode {
	NAIVE,
	MEDIAN,
	RANDOM,
	NONE,
} mode;

void set_pivot (int *data_set, size_t lo, size_t hi, mode m);
void quicksort (int *data_set, size_t lo, size_t hi, mode m);
size_t quicksort_partition(int *data_set, size_t lo, size_t hi, mode m);
void swap_index(int *data_set, size_t  one, size_t  two);

int main (int argc, char *argv[]){
	mode m = NONE;
	if (argc > 1) {
		if (strcmp(argv[1], "-pn") == 0) m = NAIVE;
		if (strcmp(argv[1], "-pm") == 0) m = MEDIAN;
		if (strcmp(argv[1], "-pr") == 0) m = RANDOM;
		
		if (m == NONE) {
			perror("unknown modifier");
			return 1;
		}
	} else {
		perror("usage ./quicksort [-pn | -pm | -pr]");
		return 1;
	}
	
	int data_size = 0;
	int *data_set = NULL;

	printf("Enter data size: ");
	scanf("%d", &data_size);

	data_set = calloc(data_size, sizeof(int));
	int insert_no = 0;

	for (int i = 0; i < data_size; i++) {
		scanf("%d", &insert_no);
		data_set[i] = insert_no;
	}

	quicksort(data_set, 0, data_size - 1, m);
	
	if (m == NAIVE) puts("Sorted by naive pivot");
	if (m == MEDIAN) puts("Sorted by median of three pivots");
	if (m == RANDOM) puts("Sorted by random pivot");
	
	for(int i = 0; i < data_size; i++) {
		printf("%d\n", data_set[i]);
	}
	return 0;
}

void quicksort (int *data_set, size_t lo, size_t hi, mode m) {
	if (hi <= lo) return;
	 
	size_t p;
	
	p = quicksort_partition(data_set, lo, hi, m);
	
	quicksort(data_set, lo, p - 1, m);
	quicksort(data_set, p + 1, hi, m);
	
}

size_t quicksort_partition(int *data_set, size_t lo, size_t hi, mode m) {
	set_pivot(data_set, lo, hi, m);	
	int pivot = data_set[hi];
	
	int  left_most = lo - 1;
	int  right_most = lo;

	while (right_most != hi) {
		if (data_set[right_most] < pivot) {
			left_most++;
			swap_index(data_set, left_most, right_most);
		}

		right_most++;
	}
	
	swap_index(data_set, left_most + 1, hi);

	return (size_t)left_most;
}


void set_pivot (int *data_set, size_t lo, size_t hi, mode m) {
	size_t pivot = 0;
	if (m == NAIVE) {
		return ;	

	} else if (m == MEDIAN) {
		size_t median = (lo + hi) / 2;
		int one_i = data_set[lo];
		int two_i = data_set[median];
		int three_i = data_set[hi];

		if (three_i > two_i && three_i > one_i)
			pivot = (two_i >= one_i) ? median: lo;
		
		if (two_i > three_i && two_i > one_i)
			pivot = (three_i >= one_i) ? hi: lo;
		
		if (one_i > two_i && one_i > three_i)
			pivot = (three_i >= two_i) ? hi: median;

	} else if (m == RANDOM) {
		srand(time(NULL));
		pivot = rand() % (hi + 1 - lo) + lo;
	}

	assert(pivot >= lo);
	assert(pivot <= hi);

	int temp = data_set[hi];
	data_set[hi] = data_set[pivot];
	data_set[pivot] = temp;
}

void swap_index(int *data_set, size_t  one, size_t  two) {
	int temp = data_set[one];

	data_set[one] = data_set[two];
	data_set[two] = temp;
}
