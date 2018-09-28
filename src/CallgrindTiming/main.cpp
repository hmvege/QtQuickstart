#include <iostream>
#include <random>
#include <cmath>
#include <thread>


void randomNumberOperations(const unsigned int N);
void fillArraysWithRandomNumbers(double *A, double *B, const unsigned int N, unsigned long long rseed=1234);
void fillArray(double *A, double a, const unsigned int N);
void addArrays(const double *A, const double *B, double *C, const unsigned int N);
void cubeArray(double *A, const unsigned int N);
double cuber(const double a);
double addNumber(const double a, const double b);

int main()
{
    randomNumberOperations((unsigned int) pow(10,4));
    return 0;
}

void randomNumberOperations(const unsigned int N) {
    /*
     * This function is a slow function.
     */

    double *VecRand1 = new double[N];
    double *VecRand2 = new double[N];
    double *VecSum = new double[N];

    printf("Filling arrays...\n");
//    fillArraysWithRandomNumbers(VecRand1, VecRand2, N);
    fillArray(VecRand1, 21, N);
    fillArray(VecRand2, 21, N);

    printf("Adding arrays...\n");
    addArrays(VecRand1, VecRand2, VecSum, N);

    printf("Taking the cube of an array...\n");
    cubeArray(VecSum, N);

    delete [] VecRand1;
    delete [] VecRand2;
//    delete [] VecSum;

    printf("Memory deallocated...?\n");
}


void fillArray(double *A, double a, const unsigned int N) {
    for (unsigned int i = 0; i < N; i++) {
        double * x = new double[10];
        A[i] = a;
    }
}

void fillArraysWithRandomNumbers(double *A, double *B, const unsigned int N, unsigned long long rseed) {
    /*
     * Function for filling two arrays with ranadom numbers
     */

    // The Mersenne-Twister random generator
    std::mt19937_64 randomGenerator(rseed);
    std::uniform_real_distribution<double> uniformDistribution(0,1);

    // Generate bunch of random numbers in two arrays
    for (unsigned int i = 0; i < N; i++) {
        A[i] = uniformDistribution(randomGenerator);
        B[i] = uniformDistribution(randomGenerator);
    }
}

void addArrays(const double *A, const double *B, double *C, const unsigned int N) {
    /* Silly function for adding two numbers. */
    for (unsigned int i = 0; i < N; i++) {
        C[i] = addNumber(A[i], B[i]);

        // This goes too fast...
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000));
    }
}

void cubeArray(double *A, const unsigned int N) {
    /* Silly function for adding two arrays. */
    for (unsigned int i = 0; i < N; i++) {
        A[i] = cuber(A[i]);
    }
}

double addNumber(const double a, const double b) {
    /*. Silly function for adding two numbers. */
    return a + b;
}

double cuber(const double a) {
    /* Really silly function for cubing a number. */
    return pow(a, 3);
}
