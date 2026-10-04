#include <iostream>
#include <omp.h>
using namespace std;

int main()
{
    int N = 1000000;
    int* A = new int[N];
    int* B = new int[N];
    int* C_single = new int[N];
    int* C_parallel = new int[N];

    for (int i = 0; i < N; i++) {
        A[i] = i;
        B[i] = i + 1;
    }

    double start_single = omp_get_wtime();

    for (int i = 0; i < N; i++) {
        C_single[i] = A[i] + B[i];
    }

    double end_single = omp_get_wtime();
    double single_time = end_single - start_single;

    double start_parallel = omp_get_wtime();

#pragma omp parallel for
    for (int i = 0; i < N; i++) {
        C_parallel[i] = A[i] + B[i];
    }

    double end_parallel = omp_get_wtime();
    double parallel_time = end_parallel - start_parallel;

    cout << "First 5 elements of C_single: ";
    for (int i = 0; i < 5; i++) {
        cout << C_single[i] << " ";
    }
    cout << endl;

    cout << "First 5 elements of C_parallel: ";
    for (int i = 0; i < 5; i++) {
        cout << C_parallel[i] << " ";
    }
    cout << endl;

    cout << "Last 5 elements of C_single: ";
    for (int i = N - 5; i < N; i++) {
        cout << C_single[i] << " ";
    }
    cout << endl;

    cout << "Last 5 elements of C_parallel: ";
    for (int i = N - 5; i < N; i++) {
        cout << C_parallel[i] << " ";
    }
    cout << endl;

    cout << "Single time: " << single_time << " seconds" << endl;
    cout << "Parallel time: " << parallel_time << " seconds" << endl;

    delete[] A;
    delete[] B;
    delete[] C_single;
    delete[] C_parallel;

    return 0;
}