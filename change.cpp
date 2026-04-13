#include <iostream>
#include <string>
using namespace std;

template<typename T>
int contains(const T* arr, size_t n, const T value) {
    for (size_t i = 0; i < n; ++i) {
        if (arr[i] == value) return static_cast<int>(i);
    }
    return -1;
}

template<typename T>
bool change(const T a, const T b, T* arr, size_t n) {
    int ia = contains(arr, n, a);
    int ib = contains(arr, n, b);

    if (ia == -1 || ib == -1) {
        cout << "Error: ";
        if (ia == -1) cout << a;
        if (ia == -1 & ib == -1) cout << " и ";
        if (ib == -1) cout << b;
        cout << " not found";
        cout << " in an array\n";
        return false;
    }

    T temp = arr[ia];
    arr[ia] = arr[ib];
    arr[ib] = temp;

    cout << "The exchange of elements was successfully completed. (" << a << " <-> " << b << ")\n";
    return true;
}

template<typename T>
void printArray(const T* arr, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        cout << arr[i];
        if (i + 1 < n) cout << " ";
    }
    cout << "\n";
}

int main() {
    size_t n1 = 5;
    int* iarr = new int[n1];
    for (size_t i = 0; i < n1; ++i) iarr[i] = static_cast<int>(i + 1);
    cout << "int array before: "; printArray(iarr, n1);
    change(2, 5, iarr, n1);
    cout << "int array after: "; printArray(iarr, n1);
    change(7, 3, iarr, n1);
    delete[] iarr;

    size_t n2 = 4;
    double* darr = new double[n2];
    darr[0] = 1.1; darr[1] = 2.2; darr[2] = 3.3; darr[3] = 4.4;
    cout << "\n double array before: "; printArray(darr, n2);
    change(1.1, 4.4, darr, n2);
    cout << "double array after: "; printArray(darr, n2);
    delete[] darr;

    size_t n3 = 4;
    string* sarr = new string[n3];
    sarr[0] = "apple"; sarr[1] = "banana"; sarr[2] = "cherry"; sarr[3] = "date";
    cout << "\n string array before: "; printArray(sarr, n3);
    change(string("banana"), string("date"), sarr, n3);
    cout << "string array after: "; printArray(sarr, n3);
    change(string("pear"), string("apple"), sarr, n3);
    delete[] sarr;

    return 0;
}