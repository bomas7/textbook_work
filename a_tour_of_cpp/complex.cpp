#include <iostream>

class Complex {
public:
        Complex(double a, double b);
        Complex(double a);
        Complex();
        
        double real();
        void real(double d);
        double imaginary();
        void imaginary(double d);

        Complex& operator+=(const Complex& d);
        Complex& operator-=(const Complex& d);
        Complex& operator/=(const Complex& d);
        Complex& operator*=(const Complex& d);

private:
        double _real;
        double _imaginary;
};


Complex::Complex(double a, double b)
        :_real(a), _imaginary(b) {}

Complex::Complex(double a)
        :_real(a), _imaginary(0) {}

Complex::Complex()
        :_real(0), _imaginary(0) {}

double Complex::real() {
        return _real;
}

void Complex::real(double d) {
        _real = d;
}

double Complex::imaginary() {
        return _imaginary;
}

void Complex::imaginary(double d) {
        _imaginary = d;
}

Complex& Complex::operator+=(const Complex& c) {
        _real += c._real;
        _imaginary += c._imaginary;
        return *this;
}

Complex& Complex::operator-=(const Complex& c) {
        _real -= c._real;
        _imaginary -= c._imaginary;
        return *this;
}

Complex& Complex::operator*=(const Complex& c) {
        _real *= c._real;
        _imaginary *= c._imaginary;
        return *this;
}

Complex& Complex::operator/=(const Complex& c) {
        _real /= c._real;
        _imaginary /= c._imaginary;
        return *this;
}

std::ostream& operator<<(std::ostream& out, Complex d) {
        out << "(" << d.real() << "," << d.imaginary() << ")";
        return out;
}

int main() {
        Complex a = Complex(3, 4);
        Complex b = Complex(1, 2);
        Complex c = a += b;
        c.real(5);
        std::cout << a << std::endl;
        std::cout << b << std::endl;
        std::cout << c << std::endl;
        return 0;
}
