// g++ -std=c++17 -fopenmp test_quick_sort.cpp -o test
// Multithreaded quicksort using openMP

#include <omp.h>

// Swaps two pointer values
template<typename T>
void swap(T* a, T* b)
{
	T tmp = *a;
	*a = *b;
	*b = tmp;
}

// Partitions the array such that:
//  - The entry args[j] is in its final place in the array, for some j.
//  - No entry in args[lo] through args[j-1] is greater than args[j].
//  - No entry in args[j+1] through a[hi] is less than args[j].
template <typename T>
int partition(T* args, int lo, int hi)
{
	T pivot = args[hi];
	int i, j;
	i = lo-1;
	for (j = lo; j <= hi-1; ++j)
	{
		if(args[j] <= pivot)
		{
			++i;
			swap(&args[i], &args[j]);
		}
	}
	swap(&args[i+1], &args[hi]);
	return (i + 1);
}

// Sorts an array in ascending order from index 'lo' to 'hi'
template<typename T>
void quick_sort(T* args, int lo, int hi)
{
	int pivot;
	if(lo < hi)
	{
		pivot = partition(args, lo, hi);
		
		#pragma omp task shared(args) firstprivate(lo, pivot)
		quick_sort(args, lo, pivot-1);
		
		#pragma omp task shared(args) firstprivate(pivot, hi)
		quick_sort(args, pivot+1, hi);
		
		#pragma omp taskwait
	}
	return;
}

