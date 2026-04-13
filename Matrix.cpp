#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
using namespace std;

template<typename T>
class Matrix {
    size_t rows;
    size_t cols;
    vector<vector<T>> data;

public:
    Matrix(): rows(0), cols(0) {}
    Matrix(size_t r, size_t c, const T& init = T())
        : rows(r), cols(c), data(r, vector<T>(c, init)) {}
    Matrix(const Matrix& other)
        : rows(other.rows), cols(other.cols), data(other.data) {}
    ~Matrix() = default;

    size_t Rows() const { return rows; }
    size_t Cols() const { return cols; }

    void Set(size_t i, size_t j, const T& value) {
        if (i >= rows || j >= cols) throw out_of_range("Index out of range in Set");
        data[i][j] = value;
    }

    T Get(size_t i, size_t j) const {
        if (i >= rows || j >= cols) throw out_of_range("Index out of range in Get");
        return data[i][j];
    }

    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols)
            throw invalid_argument("Matrices must have same dimensions for addition");

        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                result.data[i][j] = data[i][j] + other.data[i][j];
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows)
            throw invalid_argument("Matrices dimensions incompatible for multiplication");

        Matrix result(rows, other.cols, T());
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.cols; ++j) {
                T sum = T();
                for (size_t k = 0; k < cols; ++k) {
                    sum = sum + (data[i][k] * other.data[k][j]);
                }
                result.data[i][j] = sum;
            }
        }
        return result;
    }

    template<typename U>
    friend ostream& operator<<(ostream& os, const Matrix<U>& m);

    template<typename U>
    friend istream& operator>>(istream& is, Matrix<U>& m);
};

template<typename U>
ostream& operator<<(ostream& os, const Matrix<U>& m) {
    os << m.rows << " " << m.cols << "\n";
    for (size_t i = 0; i < m.rows; ++i) {
        for (size_t j = 0; j < m.cols; ++j) {
            os << m.data[i][j];
            if (j + 1 < m.cols) os << " ";
        }
        os << "\n";
    }
    return os;
}

template<typename U>
istream& operator>>(istream& is, Matrix<U>& m) {
    size_t r, c;
    if (!(is >> r >> c)) return is;
    m.rows = r;
    m.cols = c;
    m.data.assign(r, vector<U>(c));
    for (size_t i = 0; i < r; ++i)
        for (size_t j = 0; j < c; ++j)
            is >> m.data[i][j];
    return is;
}

int main() {
    try {
        Matrix<int> A(2, 3);
        A.Set(0,0,1); A.Set(0,1,2); A.Set(0,2,3);
        A.Set(1,0,4); A.Set(1,1,5); A.Set(1,2,6);

        Matrix<int> B(2, 3);
        B.Set(0,0,10); B.Set(0,1,20); B.Set(0,2,30);
        B.Set(1,0,40); B.Set(1,1,50); B.Set(1,2,60);

        auto C = A + B;
        cout << "A + B:\n" << C << endl;

        Matrix<int> M1(2,3);
        Matrix<int> M2(3,2);

        M1.Set(0,0,1); M1.Set(0,1,2); M1.Set(0,2,3);
        M1.Set(1,0,4); M1.Set(1,1,5); M1.Set(1,2,6);

        M2.Set(0,0,7);  M2.Set(0,1,8);
        M2.Set(1,0,9);  M2.Set(1,1,10);
        M2.Set(2,0,11); M2.Set(2,1,12);

        auto P = M1 * M2;
        cout << "M1 * M2:\n" << P << endl;

        Matrix<string> S1(2,2);
        S1.Set(0,0,"a"); S1.Set(0,1,"b");
        S1.Set(1,0,"c"); S1.Set(1,1,"d");

        Matrix<string> S2(2,2);
        S2.Set(0,0,"X"); S2.Set(0,1,"Y");
        S2.Set(1,0,"Z"); S2.Set(1,1,"W");

        auto Ssum = S1 + S2;
        cout << "S1 + S2:\n" << Ssum << endl;

    }
    catch (const exception& ex) {
        cerr << "Error: " << ex.what() << endl;
    }
    return 0;
}