#include <iostream>
#include <omp.h>
using namespace std;
bool is_prime(int n);

int main()
{
	const int N = 1000000;
	int prime_counter = 0;

#pragma omp parallel for
	for (int i = 2; i <= N; i++) {
		if (is_prime(i)) {
#pragma omp atomic
			prime_counter++;
		}
	}

	cout << "Number of primes between 2 and " << N << ": " << prime_counter << endl;

}

bool is_prime(int n) {
	if (n <= 1) return false;
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) return false;
	}
	return true;
}