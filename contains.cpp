#include <iostream>
#include <string>
using namespace std;

template<typename T>
bool contains(T element, T* array, int size) {
    for (int i = 0; i < size; ++i) {
        if (array [i] == element) {
            return true;
    }
    return false;
}

int main() {
    int intArray[] = {1, 2, 3, 4, 5};
    int intSize = 5;
    cout << "Contains 3? " << contains(3, intArray, intSize) << endl;
    cout << "Contains 7? " << contains(7, intArray, intSize) << endl;
    
    cout << endl;
    
    double doubleArray[] = {1.5, 2.5, 3.0, 4.2. 5.3};
    int doubleSize = 3;
    cout << "Contains 2.5? " << contains(2.5, doubleArray, doubleSize) << endl;
    cout << "Contains 5.0? " << contains(5.0, doubleArray, doubleSize) << endl;
    
    cout << endl;

    string strArray[] = {"hello", "world", "banana"};
    int strSize = 4;
    cout << "Contains banana?" in string array: " << contains<string>(world, strArray, strSize) << endl;
    cout << "Contains java?" in string array: " << contains<string>(java, strArray, strSize) << endl;

    return 0;
}
