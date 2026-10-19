
#pragma once

#include <ostream>
#include <cmath>

#include <iomanip>

struct scalar_t {
    double value{0.0};

    constexpr scalar_t() = default;
    constexpr scalar_t(double v) : value(v) {}

    friend constexpr std::ostream& operator<<(std::ostream& os, const scalar_t& u) {
        os << std::fixed << std::setprecision(6) << u.value;
        return os;
    }

    constexpr scalar_t operator+(const scalar_t& other) const {
        return scalar_t(value + other.value);
    }

    constexpr scalar_t operator+=(const scalar_t& other) {
        value += other.value;
        return *this;
    }

    friend constexpr scalar_t operator+(double left, const scalar_t& right) {
        return scalar_t(left + right.value);
    }

    constexpr scalar_t operator-(const scalar_t& other) const {
        return scalar_t(value - other.value);
    }

    constexpr scalar_t operator-=(const scalar_t& other) {
        value -= other.value;
        return *this;
    }

    friend constexpr scalar_t operator-(double left, const scalar_t& right) {
        return scalar_t(left - right.value);
    }

    constexpr scalar_t operator*(const scalar_t& other) const {
        return scalar_t(value * other.value);
    }

    constexpr scalar_t operator*=(const scalar_t& other) {
        value *= other.value;
        return *this;
    }

    friend constexpr scalar_t operator*(double left, const scalar_t& right) {
        return scalar_t(left * right.value);
    }

    constexpr scalar_t operator/(const scalar_t& other) const {
        return scalar_t(value / other.value);
    }

    constexpr scalar_t operator/=(const scalar_t& other) {
        value /= other.value;
        return *this;
    }

    friend constexpr scalar_t operator/(double left, const scalar_t& right) {
        return scalar_t(left / right.value);
    }

    constexpr scalar_t operator-() const {
        return scalar_t(-value);
    }

    constexpr bool operator<(const scalar_t& other) const {
        return value < other.value;
    }

    constexpr bool operator<=(const scalar_t& other) const {
        return value <= other.value;
    }

    constexpr bool operator>(const scalar_t& other) const {
        return value > other.value;
    }

    constexpr bool operator>=(const scalar_t& other) const {
        return value >= other.value;
    }

    constexpr bool operator==(const scalar_t& other) const {
        const double difference = std::abs(value - other.value);
        const double scale = std::max(
            std::abs(value),
            std::abs(other.value)
        );

        return difference <= 1e-9
            || difference <= 1e-9 * scale;
    }

    constexpr bool operator!=(const scalar_t& other) const {
        return !(*this == other);
    }
};

template<typename T>
struct units_t {
    scalar_t scalar{0.0};
    
    constexpr double value() const {
        return scalar.value;
    }
    
    constexpr units_t() = default;
    constexpr units_t(double v) : scalar(v) {}
    constexpr units_t(scalar_t v) : scalar(v) {}

    constexpr operator scalar_t() const {
        return scalar;
    }

    friend constexpr std::ostream& operator<<(std::ostream& os, const units_t& u) {
        os << u.scalar.value << " u";
        return os;
    }

    constexpr T operator+(const units_t& other) const {
        return T{scalar + other.scalar};
    }

    constexpr T& operator+=(const units_t& other) {
        scalar += other.scalar;
        return static_cast<T&>(*this);
    }

    constexpr T operator-(const units_t& other) const {
        return T{scalar - other.scalar};
    }

    constexpr T& operator-=(const units_t& other) {
        scalar -= other.scalar;
        return static_cast<T&>(*this);
    }

    constexpr T operator*(const scalar_t& other) const {
        return T{scalar * other};
    }

    constexpr T& operator*=(const scalar_t& other) {
        scalar *= other;
        return static_cast<T&>(*this);
    }

    friend constexpr T operator*(const scalar_t& left, const units_t& right) {
        return T{left * right.scalar};
    }

    constexpr T operator/(const scalar_t& other) const {
        return T{scalar / other};
    }

    constexpr T& operator/=(const scalar_t& other) {
        scalar /= other;
        return static_cast<T&>(*this);
    }

    constexpr T operator-() const {
        return T{-scalar};
    }

    constexpr bool operator<(const units_t& other) const {
        return scalar < other.scalar;
    }

    constexpr bool operator<=(const units_t& other) const {
        return scalar <= other.scalar;
    }

    constexpr bool operator>(const units_t& other) const {
        return scalar > other.scalar;
    }

    constexpr bool operator>=(const units_t& other) const {
        return scalar >= other.scalar;
    }

    constexpr bool operator==(const units_t& other) const {
        return scalar == other.scalar;
    }

    constexpr bool operator!=(const units_t& other) const {
        return scalar != other.scalar;
    }
};

struct seconds_t : public units_t<seconds_t> {
    using units_t<seconds_t>::units_t;

    friend constexpr std::ostream& operator<<(std::ostream& os, const seconds_t& s) {
        os << s.scalar << " s";
        return os;
    }
};

struct meters_t : public units_t<meters_t> {
    using units_t<meters_t>::units_t;

    friend constexpr std::ostream& operator<<(std::ostream& os, const meters_t& m) {
        os << m.scalar << " m";
        return os;
    }
};

struct meters_per_second_t : public units_t<meters_per_second_t> {
    using units_t<meters_per_second_t>::units_t;

    friend constexpr std::ostream& operator<<(std::ostream& os, const meters_per_second_t& mps) {
        os << mps.scalar << " m/s";
        return os;
    }
};

struct meters_per_second_squared_t : public units_t<meters_per_second_squared_t> {
    using units_t<meters_per_second_squared_t>::units_t;

    friend constexpr std::ostream& operator<<(std::ostream& os, const meters_per_second_squared_t& mps2) {
        os << mps2.scalar << " m/s^2";
        return os;
    }
};

struct radians_t : public units_t<radians_t> {
    using units_t<radians_t>::units_t;

    friend constexpr std::ostream& operator<<(std::ostream &os, const radians_t &r) {
        os << r.scalar << " rad";
        return os;
    }
};

struct degrees_t : public units_t<degrees_t> {
    using units_t<degrees_t>::units_t;

    friend constexpr std::ostream& operator<<(std::ostream& os, const degrees_t& d) {
        os << d.scalar << " deg";
        return os;
    }
};

struct kilograms_t : public units_t<kilograms_t> {
    using units_t<kilograms_t>::units_t;

    friend constexpr std::ostream& operator<<(std::ostream& os, const kilograms_t& kg) {
        os << kg.scalar << " kg";
        return os;
    }
};

struct newtons_t : public units_t<newtons_t> {
    using units_t<newtons_t>::units_t;

    friend constexpr std::ostream& operator<<(std::ostream& os, const newtons_t& n) {
        os << n.scalar << " N";
        return os;
    }
};

struct kilograms_meter_squared_t : public units_t<kilograms_meter_squared_t> {
    using units_t<kilograms_meter_squared_t>::units_t;

    friend constexpr std::ostream& operator<<(std::ostream& os, const kilograms_meter_squared_t& kgm2) {
        os << kgm2.scalar << " kg·m^2";
        return os;
    }
};

struct pascals_t : public units_t<pascals_t> {
    using units_t<pascals_t>::units_t;

    friend constexpr std::ostream& operator<<(std::ostream& os, const pascals_t& pa) {
        os << pa.scalar << " Pa";
        return os;
    }
};

struct kelvin_t : public units_t<kelvin_t> {
    using units_t<kelvin_t>::units_t;

    friend constexpr std::ostream& operator<<(std::ostream& os, const kelvin_t& k) {
        os << k.scalar << " K";
        return os;
    }
};

struct kilograms_per_meter_squared_t : public units_t<kilograms_per_meter_squared_t> {
    using units_t<kilograms_per_meter_squared_t>::units_t;

    friend constexpr std::ostream& operator<<(std::ostream& os, const kilograms_per_meter_squared_t& kgm2) {
        os << kgm2.scalar << " kg/m^2";
        return os;
    }
};

struct kilograms_per_cubic_meter_t : public units_t<kilograms_per_cubic_meter_t> {
    using units_t<kilograms_per_cubic_meter_t>::units_t;

    friend constexpr std::ostream& operator<<(std::ostream& os, const kilograms_per_cubic_meter_t& kgm3) {
        os << kgm3.scalar << " kg/m^3";
        return os;
    }
};

struct kilograms_meter_per_second_t : public units_t<kilograms_meter_per_second_t> {
    using units_t<kilograms_meter_per_second_t>::units_t;

    friend constexpr std::ostream& operator<<(std::ostream& os, const kilograms_meter_per_second_t& kgms) {
        os << kgms.scalar << " kg·m/s";
        return os;
    }
};
