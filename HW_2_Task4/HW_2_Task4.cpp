#include <iostream>
#include <omp.h>
#include <random>
using namespace std;

int main()
{
	long long N = 100000000;
	long long inside = 0;
#pragma omp parallel 
	{
		long long local_inside = 0;
		mt19937 generator(omp_get_thread_num());
		uniform_real_distribution<double> distribution(0.0, 1.0);

#pragma omp for
		for (long long i = 0; i < N; i++)
		{
			double x = distribution(generator);
			double y = distribution(generator);
			if (x * x + y * y <= 1.0)
			{
				local_inside++;
			}
		}
#pragma omp atomic
		inside += local_inside;
#pragma omp barrier
#pragma omp single
		{
			double pi = 4.0 * inside / N;
			cout << "Estimated value of pi: " << pi << endl;
			cout << "Number of points inside the circle: " << inside << endl;
		}

	}

}