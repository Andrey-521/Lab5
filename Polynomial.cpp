#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>
using namespace std;

template<typename T>
class Polynomial {
    vector<T> coeffs_;

    void normalize() {
        while (coeffs_.size() > 1 & coeffs_.back() == T{}) coeffs_.pop_back();
    }

public:
    Polynomial() : coeffs_(1, T{}) {}
    Polynomial(const vector<T> v) : coeffs_(v) {
        if (coeffs_.empty()) coeffs_.push_back(T{});
        normalize();
    }

    Polynomial(const T c) : coeffs_(1, c) {
        normalize();
    }

    size_t Degree() const {
        for (size_t i = coeffs_.size(); i-- > 0; )
            if (coeffs_[i] != T{}) return i;
        return 0;
    }

    T operator const {
        if (k < coeffs_.size()) return coeffs_[k];
        return T{};
    }

    const vector<T> coeffs() const { return coeffs_; }

    Polynomial operator+=(const Polynomial other) {
        :size_t n = max(coeffs_.size(), other.coeffs_.size());
        coeffs_.resize(n, T{});
        for (size_t i = 0; i < other.coeffs_.size(); ++i)
            coeffs_[i] += other.coeffs_[i];
        normalize();
        return *this;
    }

    Polynomial operator+=(const T scalar) {
        if (coeffs_.empty()) coeffs_.push_back(scalar);
        else coeffs_[0] += scalar;
        normalize();
        return *this;
    }

    Polynomial operator-=(const Polynomial other) {
        size_t n = max(coeffs_.size(), other.coeffs_.size());
        coeffs_.resize(n, T{});
        for (size_t i = 0; i < other.coeffs_.size(); ++i)
            coeffs_[i] -= other.coeffs_[i];
        normalize();
        return *this;
    }

    Polynomial operator-=(const T scalar) {
        if (coeffs_.empty()) coeffs_.push_back(T{} - scalar);
        else coeffs_[0] -= scalar;
        normalize();
        return *this;
    }

    Polynomial operator*=(const T scalar) {
        if (scalar == T{}) {
            coeffs_.assign(1, T{});
        } else {
            for (auto c : coeffs_) c *= scalar;
        }
        normalize();
        return *this;
    }

    Polynomial operator*=(const Polynomial other) {
        f ((coeffs_.size() == 1 & coeffs_[0] == T{}) || (other.coeffs_.size() == 1 & other.coeffs_[0] == T{})) {
            coeffs_.assign(1, T{});
            return *this;
        }
        vector<T> res(coeffs_.size() + other.coeffs_.size() - 1, T{});
        for (size_t i = 0; i < coeffs_.size(); ++i)
            for (size_t j = 0; j < other.coeffs_.size(); ++j)
                res[i + j] += coeffs_[i] * other.coeffs_[j];
        coeffs_.swap(res);
        normalize();
        return *this;
    }

    T operator()(const T x) const {
        T result = T{};
        for (size_t i = coeffs_.size(); i-- > 0; )
            result = result * x + coeffs_[i];
        return result;
    }

    friend ostream operator<<(ostream os, const Polynomial p) {
        for (size_t i = p.coeffs_.size(); i-- > 0; ) {
            os << p.coeffs_[i];
            if (i != 0) os << ' ';
        }
        return os;
    }

    friend bool operator==(const Polynomial a, const Polynomial b) {
        return a.coeffs_ == b.coeffs_;
    }

    friend bool operator!=(const Polynomial a, const Polynomial b) {
        return !(a == b);
    }

    friend bool operator==(const Polynomial a, const T scalar) {
        if (a.coeffs_.size() == 1) return a.coeffs_[0] == scalar;
        for (size_t i = 1; i < a.coeffs_.size(); ++i) if (a.coeffs_[i] != T{}) return false;
        return a.coeffs_[0] == scalar;
    }
    friend bool operator==(const T scalar, const Polynomial a) { return a == scalar; }
    friend bool operator!=(const Polynomial a, const T scalar) { return !(a == scalar); }
    friend bool operator!=(const T scalar, const Polynomial a) { return !(a == scalar); }
};

template<typename T>
Polynomial<T> operator+(Polynomial<T> a, const Polynomial<T> b) { a += b; return a; }

template<typename T>
Polynomial<T> operator+(Polynomial<T> a, const T scalar) { a += scalar; return a; }

template<typename T>
Polynomial<T> operator+(const T scalar, Polynomial<T> a) { a += scalar; return a; }

template<typename T>
Polynomial<T> operator-(Polynomial<T> a, const Polynomial<T> b) { a -= b; return a; }

template<typename T>
Polynomial<T> operator-(Polynomial<T> a, const T scalar) { a -= scalar; return a; }

template<typename T>
Polynomial<T> operator-(const T scalar, const Polynomial<T> p) {
    Polynomial<T> res = Polynomial<T>(scalar);
    res -= p;
    return res;
}

template<typename T>
Polynomial<T> operator*(Polynomial<T> a, const T scalar) { a *= scalar; return a; }

template<typename T>
Polynomial<T> operator*(const T scalar, Polynomial<T> a) { a *= scalar; return a; }

template<typename T>
Polynomial<T> operator*(const Polynomial<T> a, const Polynomial<T> b) {
    Polynomial<T> res;
    res = a; res *= b;
    return res;
}

int main() {
    Polynomial<int> p({1,2,3});
    cout << "p coeffs (from highest to lowest): " << p << "\n";
    cout << "Degree(p) = " << p.Degree() << "\n";
    cout << "p(2) = " << p(2) << "\n";

    auto q = p + 5;
    cout << "q = p + 5 : " << q << "   q(2)=" << q(2) << "\n";

    Polynomial<int> r({0,1});
    auto s = p * r;
    cout << "s = p * x : " << s << "  Degree(s)=" << s.Degree() << "\n";

    Polynomial<int> zero(0);
    cout << "zero == 0 ? " << (zero == 0) << "\n";
    cout << "p == q ? " << (p == q) << "\n";

    using cd = complex<double>;
    Polynomial<cd> pc({ cd(1,0), cd(0,1), cd(2,-1) });
    cout << "pc coeffs: " << pc << "\n";
    cd val = pc(cd(1.0, 1.0));
    cout << "pc(1+i) = " << val << "\n";

    return 0;
}