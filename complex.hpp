// Tsadik88@gmail.com
#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>

/**
 * @class Complex
 * @brief A class representing a complex number with real and imaginary parts.
 */
class Complex {
public:
    /**
     * @brief Constructs a Complex number.
     * @param real The real part of the complex number. Defaults to 0.
     * @param imag The imaginary part of the complex number. Defaults to 0.
     */
    Complex(double real = 0, double imag = 0) : real(real), imag(imag) {}

    /**
     * @brief Gets the real part of the complex number.
     * @return The real part.
     */
    double get_real() const { return real; }

    /**
     * @brief Gets the imaginary part of the complex number.
     * @return The imaginary part.
     */
    double get_imag() const { return imag; }

    /**
     * @brief Overloads the insertion (<<) operator to print the complex number in the form "real+imagi".
     * @param os The output stream.
     * @param c The complex number to be printed.
     * @return The output stream.
     */
    friend std::ostream &operator<<(std::ostream &os, const Complex &c) {
        os << c.real << "+" << c.imag << "i";
        return os;
    }

    /**
     * @brief Overloads the greater than (>) operator to compare two complex numbers.
     *        Comparison is based on the real part first, then the imaginary part if the real parts are equal.
     * @param other The other complex number to compare with.
     * @return True if this complex number is greater than the other, false otherwise.
     */
    bool operator>(const Complex &other) const {
        return real > other.real || (real == other.real && imag > other.imag);
    }

    /**
     * @brief Overloads the less than (<) operator to compare two complex numbers.
     *        Comparison is based on the real part first, then the imaginary part if the real parts are equal.
     * @param other The other complex number to compare with.
     * @return True if this complex number is less than the other, false otherwise.
     */
    bool operator<(const Complex &other) const {
        return real < other.real || (real == other.real && imag < other.imag);
    }

    /**
     * @brief Overloads the equality (==) operator to check if two complex numbers are equal.
     *        Two complex numbers are equal if both their real and imaginary parts are equal.
     * @param other The other complex number to compare with.
     * @return True if the complex numbers are equal, false otherwise.
     */
    bool operator==(const Complex &other) const {
        return real == other.real && imag == other.imag;
    }

    /**
     * @brief Overloads the inequality (!=) operator to check if two complex numbers are not equal.
     * @param other The other complex number to compare with.
     * @return True if the complex numbers are not equal, false otherwise.
     */
    bool operator!=(const Complex &other) const {
        return !(*this == other);
    }

private:
    double real; ///< The real part of the complex number.
    double imag; ///< The imaginary part of the complex number.
};

#endif // COMPLEX_HPP
