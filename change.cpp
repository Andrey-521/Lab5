#include <iostream>
#include <string>
using namespace std;

template<typename T>
bool contains(T value, T* array, int size) {
    for (int i = 0; i < size; ++i) {
        if (array[i] == value)
            return true;
    }
    return false;
}

template<typename T>
bool change(T first, T second, T* array, int size){
    if (!contains(first, array, size) || !contains(second, array, size)){
        cout << "404: Not found" << endl;
        return false;
    }

    int firstIdx = -1, secondIdx = -1;
    for (int i = 0; i < size; ++i) {
        if (array[i] == first) firstIdx = i;
        if (array[i] == second) secondIdx = i;
    }

    T tmp = array[firstIdx];
    array[firstIdx] = array[secondIdx];
    array[secondIdx] = tmp;

    cout << "200: Swapped" << endl;
    return true;
}

template<typename T>
void printArray(T* array, int size) {
    for (int i = 0; i < size; ++i) {
        cout << array[i] << (i + 1 < size ? " " : "");
    }
    cout << endl;
}

int main() {
     int arr[] = { 10, 20, 30, 40 };
    for (int i = 0; i < 4; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    change<int>(10, 40, arr, 4);
    for (int i = 0; i < 4; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << endl;

    double arr1[] = { 0.8, -20.53, 97.48, 7.65 };
    for (int i = 0; i < 4; i++) {
        cout << arr1[i] << " ";
    }
    cout << endl;
    change<double>(-20.53, 97.48, arr1, 4);
    for (int i = 0; i < 4; i++) {
        cout << arr1[i] << " ";
    }
    cout << endl;
    cout << endl;

    string arr2[] = {"House", "Monday", "Thing", "Sleep"};
    for (int i = 0; i < 4; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;
    change<string>("Monday", "Sleep", arr2, 4);
    for (int i = 0; i < 4; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;
    return 0;
}
