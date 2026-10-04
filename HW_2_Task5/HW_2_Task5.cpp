#include <iostream>
#include <omp.h>
using namespace std;
long long fibonacci(int n, int cutoff);

int main()
{
	int N = 35;
	int cutoff = 10;
	long long result = 0;
	double start_time = omp_get_wtime();

#pragma omp parallel
	{
#pragma omp single
		{
			result = fibonacci(N, cutoff);
		}
	}
	double end_time = omp_get_wtime();
	cout << "Result: " << result << endl;
	cout << "Time taken: " << end_time - start_time << " seconds" << endl;
}

long long fibonacci(int n, int cutoff)
{
	if (n < cutoff) {
		if (n < 2)
			return n;
		return fibonacci(n - 1, cutoff) + fibonacci(n - 2, cutoff);
	}
	long long fib1 = 0;
	long long fib2 = 0;
#pragma omp task shared(fib1)
	{
		fib1 = fibonacci(n - 1, cutoff);
	}
#pragma omp task shared(fib2)
	{
		fib2 = fibonacci(n - 2, cutoff);
	}
#pragma omp taskwait
	return fib1 + fib2;
}