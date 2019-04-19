/*
 * Move semantics example.
 *
 * See also:
 * - https://www.internalpointers.com/post/c-rvalue-references-and-move-semantics-beginners
 * - https://www.srcmake.com/home/move-semantics
 */

#include <iostream>
#include "dynovec.h"

using namespace std;

template <class T>
void printVec(DynoVec<T> &A, const unsigned long N) {
    for (unsigned long i = 0; i < N; ++i) {
        cout << A[i] << " ";
    }
    cout << endl;
}


int main()
{
    unsigned long N = 10;

    DynoVec<double>A(N);
    DynoVec<double>B(N);
    DynoVec<double>C(N);

    for (unsigned long i = 0; i < N; ++i) {
        A[i] = 1;
        B[i] = 2;
        C[i] = 0;
    }

    // Prints values before we are initiating operations.
    cout << "A: ";
    printVec<double>(A, N);

    cout << "B: ";
    printVec<double>(B, N);

    cout << "C: ";
    printVec<double>(C, N);

    cout << "Beginning move-sem. operations" << endl;

    // Perform a simple addition to self.
    // This should trigger a move assignement operation
    A = A + B;

    // This should trigger a copy assignement operation
//    C = A;

    cout << "Finalizing move-sem. operations" << endl;

    cout << "A: ";
    printVec<double>(A, N);

    cout << "B: ";
    printVec<double>(B, N);

    cout << "C: ";
    printVec<double>(C, N);


    return 0;
}
