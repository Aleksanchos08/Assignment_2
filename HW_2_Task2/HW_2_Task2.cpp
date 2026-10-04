#include <iostream>
#include <omp.h>
#include <cmath>
using namespace std;

int main()
{
	const long long N = 100000000;
	double h = 1.0 / N;
	double sum = 0.0;

#pragma omp parallel for reduction(+:sum)
	for (long long i = 0; i < N; i++) {
		double x = (i + 0.5) * h;
		double fx = 4.0 / (1.0 + x * x);
		sum += fx * h;
	}

	double pi = sum;
	double error = abs(pi - 3.141592653589793);

	cout << "Approximation of pi: " << pi << endl;
	cout << "Error: " << error << endl;
}