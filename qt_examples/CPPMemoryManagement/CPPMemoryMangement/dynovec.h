#ifndef DYNOVEC_H
#define DYNOVEC_H

#include <algorithm>
#include <utility>
#include <iostream>

using std::cout;
using std::endl;

template<class T>
class DynoVec
{
private:
    T *m_arr;
    unsigned long m_N;

public:
    // Default constructor
    DynoVec()
    {
        cout << "Using default constructor." << endl;
    }

    // Parametrized constructor
    DynoVec(const unsigned long N) :
        m_N(N)
    {
        cout << "Using parametrized constructor." << endl;
        m_arr = new T[N];
    }

    // Destructor
    ~DynoVec()
    {
        cout << "Using destructor." << endl;
        delete [] m_arr;
    }

    // Copy constructor
    DynoVec(const DynoVec<T>& other) :
        m_N(other.m_N)
    {
        cout << "Using copy constructor" << endl;

        m_arr = new T[m_N];
        std::copy(other.m_arr, other.m_arr+m_N, &m_arr[0]);
    }

    // Move constructor
    DynoVec(DynoVec<T> && other)
//        m_arr(std::move(other.m_arr)),
//        m_N(other.m_N)
    {
        cout << "Using move constructor" << endl;
        m_arr = new T[other.m_N];
//        m_arr = std::move(other.m_arr);
        swap(*this, other);
//        delete [] other.m_arr;
//        other.m_arr = nullptr;
//        other.m_N = 0;

        // Destructor for 'other' object called at the end.
    }

    // Copy assignement constructor
    DynoVec &operator =(const DynoVec& other) {
        cout << "Using copy assignement constructor" << endl;
        m_N = other.m_N;
        delete[] m_arr;
        m_arr = new T[m_N];
        std::copy(other.m_arr, other.m_arr+m_N, m_arr);
        return *this;
    }

    // Move assignement constructor
    DynoVec &operator =(DynoVec<T>&& other) {
        cout << "Using move assignement constructor" << endl;
//        m_N = other.m_N;
        delete[] m_arr;
        m_arr = new T[other.m_N];
//        m_arr = std::move(other.m_arr);
        swap(*this, other);
//        delete [] other.m_arr;
//        other.m_arr = nullptr;
//        other.m_N = 0;

        // Destructor for 'other' object called at the end.

        return *this;
    }

    T &operator[](unsigned long i) {
        return m_arr[i];
    }

    T &operator()(unsigned long i) {
        if (i >= m_N) {
            printf("\nOU T OF BUNDS WITH INDEX %lu of %lu", i, m_N);
            exit(1);
        }
        return m_arr[i];
    }

    // Overloading DynoVec operations
    DynoVec<T> &operator+=(DynoVec<T>& B);
    DynoVec<T> &operator+=(DynoVec<T>&& B);
    DynoVec<T> &operator-=(DynoVec<T>& B);
    DynoVec<T> &operator-=(DynoVec<T>&& B);
    DynoVec<T> &operator*=(DynoVec<T>& B);
    DynoVec<T> &operator*=(DynoVec<T>&& B);

    friend void swap(DynoVec<T> &first, DynoVec<T> &second)
    {
        using std::swap;

        swap(first.m_N, second.m_N);
        swap(first.m_arr, second.m_arr);
    }
};

// External DynoVec operator overloading
template <class T>
inline DynoVec<T> operator+(DynoVec<T> A, DynoVec<T>& B) {
    A += B;
    return A;
}

template <class T>
inline DynoVec<T> operator+(DynoVec<T> A, DynoVec<T>&& B) {
    A += B;
    return A;
}

template <class T>
inline DynoVec<T> operator-(DynoVec<T> A, DynoVec<T>& B) {
    A -= B;
    return A;
}

template <class T>
inline DynoVec<T> operator-(DynoVec<T> A, DynoVec<T>&& B) {
    A -= B;
    return A;
}

template <class T>
inline DynoVec<T> operator*(DynoVec<T> A, DynoVec<T>& B) {
    A *= B;
    return A;
}

template <class T>
inline DynoVec<T> operator*(DynoVec<T> A, DynoVec<T>&& B) {
    A *= B;
    return A;
}


// DynoVec operator overloading
template <class T>
inline DynoVec<T> &DynoVec<T>::operator+=(DynoVec<T>& B) {
    for (unsigned long iSite = 0; iSite < m_N; iSite++) {
        m_arr[iSite] += B[iSite];
    }
    return *this;
}

template <class T>
inline DynoVec<T> &DynoVec<T>::operator+=(DynoVec<T>&& B) {
    for (unsigned long iSite = 0; iSite < m_N; iSite++) {
        m_arr[iSite] += B[iSite];
    }
    return *this;
}

template <class T>
inline DynoVec<T> &DynoVec<T>::operator-=(DynoVec<T>& B) {
    for (unsigned long iSite = 0; iSite < m_N; iSite++) {
        m_arr[iSite] -= B[iSite];
    }
    return *this;
}

template <class T>
inline DynoVec<T> &DynoVec<T>::operator-=(DynoVec<T>&& B) {
    for (unsigned long iSite = 0; iSite < m_N; iSite++) {
        m_arr[iSite] -= B[iSite];
    }
    return *this;
}

template <class T>
inline DynoVec<T> &DynoVec<T>::operator*=(DynoVec<T>& B) {
    for (unsigned long iSite = 0; iSite < m_N; iSite++) {
        m_arr[iSite] *= B[iSite];
    }
    return *this;
}

template <class T>
inline DynoVec<T> &DynoVec<T>::operator*=(DynoVec<T>&& B) {
    for (unsigned long iSite = 0; iSite < m_N; iSite++) {
        m_arr[iSite] *= B[iSite];
    }
    return *this;
}

#endif // DYNOVEC_H
