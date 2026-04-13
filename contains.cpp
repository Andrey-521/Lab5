#include <iostream>
#include <string>
using namespace std;

template<typename T>
bool contains(const T value, const T* arr, int size) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == value) return true;
    }
    return false;
}

int main() {
    int n1 = 5;
    int* iarr = new int[n1]{1, 2, 3, 4, 5};
    cout << boolalpha;
    cout << "3 in int array: " << contains(3, iarr, n1) << "\n";
    cout << "7 in int array: " << contains(7, iarr, n1) << "\n";
    delete[] iarr;

    int n2 = 4;
    double* darr = new double[n2]{1.5, 2.5, 3.0, 4.2};
    cout << "2.5 in double array: " << contains(2.5, darr, n2) << "\n";
    cout << "5.0 in double array: " << contains(5.0, darr, n2) << "\n";
    delete[] darr;

    int n3 = 3;
 string* sarr = new string[n3]{"hello", "world", "C++"};
    cout << "\"world\" in string array: " << contains(string("world"), sarr, n3) << "\n";
    cout << "\"java\" in string array: " << contains(string("java"), sarr, n3) << "\n";
    delete[] sarr;

    return 0;
}