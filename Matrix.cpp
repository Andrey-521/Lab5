#include <iostream>

using namespace std;

template <typename T>
class Matrix {

   T** data;
   size_t rows, columns;

public:
    Matrix(size_t r, size_t c) : rows(r), columns(c) {
        data = new T*[rows];
        for (size_t i = 0; i < rows; ++i) {
            data[i] = new T[columns]();
        }
    }

    Matrix(const Matrix& other) : rows(other.rows), columns(other.columns) {
        data = new T*[rows];
        for (size_t i = 0; i < rows; ++i) {
            data[i] = new T[columns];
            for (size_t j = 0; j < columns; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    Matrix& operator=(const Matrix& other) {
        if (this == &other) return *this;

        for (size_t i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;

        rows = other.rows;
        columns = other.columns;
        data = new T*[rows];
        for (size_t i = 0; i < rows; ++i) {
            data[i] = new T[columns];
            for (size_t j = 0; j < columns; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
        return *this;
    }

    ~Matrix() {
        for (size_t i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    void Set(size_t r, size_t c, const T& value) {
        if (r >= rows || c >= columns)
            throw out_of_range("Index out of range");
        data[r][c] = value;
    }

    T Get(size_t r, size_t c) const {
        if (r >= rows || c >= columns)
            throw out_of_range("Index out of range");
        return data[r][c];
    }

    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || columns != other.columns)
            throw invalid_argument("Matrices must have the same dimensions for addition");

        Matrix result(rows, columns);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < columns; ++j) {
                result.Set(i, j, this->Get(i, j) + other.Get(i, j));
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        if (columns != other.rows)
            throw invalid_argument("Matrices dimensions are not compatible for multiplication");

        Matrix result(rows, other.columns);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.columns; ++j) {
                T sum = T();
                for (size_t k = 0; k < columns; ++k) {
                    sum += this->Get(i, k) * other.Get(k, j);
                }
                result.Set(i, j, sum);
            }
        }
        return result;
    }

    friend ostream& operator<<(ostream& os, const Matrix& m) {
        for (size_t i = 0; i < m.rows; ++i) {
            for (size_t j = 0; j < m.columns; ++j) {
                os << m.Get(i, j);
                if (j + 1 < m.columns) os << " ";
            }
            os << endl;
        }
        return os;
    }

    friend istream& operator>>(istream& is, Matrix& m) {
        for (size_t i = 0; i < m.rows; ++i)
            for (size_t j = 0; j < m.columns; ++j)
                is >> m.data[i][j];
        return is;
    }
};

int main() {
    try {
        Matrix<int> A(2, 2);
        Matrix<int> B(2, 2);

        A.Set(0, 0, 1); A.Set(0, 1, 2);
        A.Set(1, 0, 3); A.Set(1, 1, 4);
        B.Set(0, 0, 5); B.Set(0, 1, 6);
        B.Set(1, 0, 7); B.Set(1, 1, 8);

        cout << "Matrix A:\n" << A << "\n";
        cout << "Matrix B:\n" << B << "\n";

        Matrix<int> C = A + B;
        cout << "A + B:\n" << C << "\n";

        Matrix<int> D = A * B;
        cout << "A * B:\n" << D << "\n";

    } catch (const exception& ex) {
        cerr << "Error: " << ex.what() << "\n";
    }

    return 0;
}
    return 0;
}
