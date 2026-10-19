
#pragma once

#include <ostream>
#include <cmath>

#include <iomanip>
#include <limits>

#include "units.hpp"
#include "frames.hpp"

template<frame_t Frame>
struct direction_t;

namespace math {

    template <typename Derived, typename RowType, std::size_t numRows, std::size_t numColumns, frame_t Frame>
    struct matrix_t;

    template<typename Derived, typename T, std::size_t N, frame_t Frame>
    struct vector_t {
        using value_type = T;
        std::array<T, N> data{0.0};

        constexpr vector_t() = default;
        constexpr vector_t(T value) : data{value} {}
        constexpr vector_t(const std::array<T, N>& values) : data{values} {}
        constexpr vector_t(const vector_t<Derived, T, N, Frame>& other) = default;

        template<typename... Args>
        requires(sizeof...(Args) == N)
        constexpr vector_t(const Args&... args) : data{args...} {}

        constexpr Derived& operator=(const std::array<T, N>& values) {
            data = values;
            return *static_cast<Derived*>(this);
        }

        constexpr Derived& operator=(const vector_t<Derived, T, N, Frame>& other) {
            data = other.data;
            return *static_cast<Derived*>(this);
        }

        constexpr Derived& operator=(const Derived& other) {
            data = other.data;
            return *static_cast<Derived*>(this);
        }

        constexpr T& operator[](std::size_t index) {
            return data[index];
        }

        constexpr const T& operator[](std::size_t index) const {
            return data[index];
        }

        constexpr Derived operator+(const Derived& other) const {
            Derived result{0.0};
            for (std::size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] + other.data[i];
            }
            return result;
        }

        constexpr Derived& operator+=(const Derived& other) {
            for (std::size_t i = 0; i < N; ++i) {
                data[i] += other.data[i];
            }
            return *static_cast<Derived*>(this);
        }

        constexpr Derived operator-(const Derived& other) const {
            Derived result{0.0};
            for (std::size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] - other.data[i];
            }
            return result;
        }

        constexpr Derived& operator-=(const Derived& other) {
            for (std::size_t i = 0; i < N; ++i) {
                data[i] -= other.data[i];
            }
            return *static_cast<Derived*>(this);
        }
        
        constexpr Derived operator*(T scalar) const {
            Derived result{0.0};
            for (std::size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] * scalar;
            }
            return result;
        }

        template<typename Any>
        constexpr Derived operator*(const vector_t<Any, scalar_t, N, Frame>& other) const {
            Derived result{0.0};
            for (std::size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] * other.data[i];
            }
            return result;
        }

        constexpr Derived& operator*=(T scalar) {
            for (std::size_t i = 0; i < N; ++i) {
                data[i] *= scalar;
            }
            return *static_cast<Derived*>(this);
        }

        template<typename Any>
        constexpr Derived& operator*=(const vector_t<Any, scalar_t, N, Frame>& other) {
            for (std::size_t i = 0; i < N; ++i) {
                data[i] *= other.data[i];
            }
            return *static_cast<Derived*>(this);
        }

        constexpr Derived operator/(T scalar) const {
            Derived result{0.0};
            for (std::size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] / scalar;
            }
            return result;
        }

        template<typename Any>
        constexpr Derived operator/(const vector_t<Any, scalar_t, N, Frame>& other) const {
            Derived result{0.0};
            for (std::size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] / other.data[i];
            }
            return result;
        }

        constexpr Derived& operator/=(T scalar) {
            for (std::size_t i = 0; i < N; ++i) {
                data[i] /= scalar;
            }
            return *static_cast<Derived*>(this);
        }

        template<typename Any>
        constexpr Derived& operator/=(const vector_t<Any, scalar_t, N, Frame>& other) {
            for (std::size_t i = 0; i < N; ++i) {
                data[i] /= other.data[i];
            }
            return *static_cast<Derived*>(this);
        }

        constexpr Derived operator-() const {
            Derived result{0.0};
            for (std::size_t i = 0; i < N; ++i) {
                result.data[i] = -data[i];
            }
            return result;
        }

        constexpr bool operator==(const Derived& other) const {
            for (std::size_t i = 0; i < N; ++i) {
                if (data[i] != other.data[i]) {
                    return false;
                }
            }

            return true;
        }

        constexpr bool operator!=(const Derived& other) const {
            return !(*this == other);
        }

        constexpr bool operator>(const Derived& other) const {
            return this->magnitude() > other.magnitude();
        }

        constexpr bool operator<(const Derived& other) const {
            return this->magnitude() < other.magnitude();
        }

        constexpr bool operator<=(const Derived& other) const {
            return this->magnitude() <= other.magnitude();
        }

        constexpr bool operator>=(const Derived& other) const {
            return this->magnitude() >= other.magnitude();
        }

        constexpr T dot(const Derived& other) const {
            T result{0.0};
            for (std::size_t i = 0; i < N; ++i) {
                result += data[i] * other.data[i];
            }
            return result;
        }
        
        constexpr T magnitude() const {
            T sum_of_squares{0.0};
            for (std::size_t i = 0; i < N; ++i) {
                sum_of_squares += data[i] * data[i];
            }
            return T{std::sqrt(sum_of_squares.value)};
        }

        friend std::ostream& operator<<(std::ostream& os, const Derived& v) {
            for (std::size_t i = 0; i < N; ++i) {
                os << v.data[i];
                if (i != N - 1) {
                    os << " ";
                }
            }
            return os;
        }
    };

};

template<typename Derived, typename T, frame_t Frame>
struct cartesian_t : public math::vector_t<Derived, T, 3, Frame> {
    using math::vector_t<Derived, T, 3, Frame>::vector_t;

    constexpr T x() const {
        return (*this)[0];
    }

    constexpr T y() const {
        return (*this)[1];
    }

    constexpr T z() const {
        return (*this)[2];
    }
    
    constexpr Derived cross(const Derived& v) const {
        return Derived{
            y() * v.z() - z() * v.y(),
            z() * v.x() - x() * v.z(),
            x() * v.y() - y() * v.x()
        };
    }
};

template<frame_t Frame>
struct direction_t : public cartesian_t<direction_t<Frame>, scalar_t, Frame> {
    using cartesian_t<direction_t<Frame>, scalar_t, Frame>::cartesian_t;
};

namespace math {

    template<typename Derived, frame_t Frame>
    struct quaternion_t {
        scalar_t w{1.0};
        scalar_t x{0.0};
        scalar_t y{0.0};
        scalar_t z{0.0};

        constexpr quaternion_t(scalar_t w_val, scalar_t x_val, scalar_t y_val, scalar_t z_val) : w(w_val), x(x_val), y(y_val), z(z_val) {}
        constexpr quaternion_t(const quaternion_t<Derived, Frame>& other) : w(other.w), x(other.x), y(other.y), z(other.z) {}

        constexpr Derived& operator=(const quaternion_t<Derived, Frame>& other) {
            if (this != &other) {
                w = other.w;
                x = other.x;
                y = other.y;
                z = other.z;
            }
            return static_cast<Derived&>(*this);
        }

        friend std::ostream& operator<<(std::ostream& os, const Derived& q) {
            os << q.w << " " << q.x << " " << q.y << " " << q.z;
            return os;
        }

        constexpr direction_t<Frame> forward() const {
            return direction_t<Frame>{
                1.0 - 2.0 * (y * y + z * z),
                2.0 * (x * y + w * z),
                2.0 * (x * z - w * y)
            };
        }

        constexpr direction_t<Frame> aft() const {
            return -forward();
        }

        constexpr direction_t<Frame> zenith() const {
            return direction_t<Frame>{
                2.0 * (x * z + w * y),
                2.0 * (y * z - w * x),
                1.0 - 2.0 * (x * x + y * y)
            };
        }

        constexpr direction_t<Frame> nadir() const {
            return -zenith();
        }

        constexpr direction_t<Frame> port() const {
            return direction_t<Frame>{
                2.0 * (x * y - w * z),
                1.0 - 2.0 * (x * x + z * z),
                2.0 * (y * z + w * x)
            };
        }

        constexpr direction_t<Frame> starboard() const {
            return -port();
        }
    };

    template <typename Derived, typename RowType, std::size_t numRows, std::size_t numColumns, frame_t Frame>
    struct matrix_t {
        std::array<RowType, numRows> data{0.0};
 
        constexpr matrix_t() = default;
        constexpr matrix_t(RowType::value_type value) : data{value} {}
        constexpr matrix_t(const std::array<std::array<typename RowType::value_type, numColumns>, numRows>& data) : data(data) {}
        constexpr matrix_t(const matrix_t<Derived, RowType, numRows, numColumns, Frame>& other) : data(other.data) {}

        template<typename... Args>
        requires(sizeof...(Args) == numRows)
        constexpr matrix_t(const Args&... args) : data{args...} {}

        constexpr RowType& operator[](std::size_t index) {
            return data[index];
        }

        constexpr const RowType& operator[](std::size_t index) const {
            return data[index];
        }

        constexpr Derived operator*(const Derived& other) const {
            Derived result{0.0};

            for (std::size_t row = 0; row < numRows; ++row) {
                for (std::size_t col = 0; col < numColumns; ++col) {
                    for (std::size_t k = 0; k < numColumns; ++k) {
                        result[row][col] +=
                            (*this)[row][k] * other[k][col];
                    }
                }
            }

            return result;
        }

        template<std::size_t OthernumRows, std::size_t OthernumColumns>
        constexpr Derived operator*(const matrix_t<Derived, RowType, OthernumRows, OthernumColumns, Frame>& other) const {
            static_assert(numColumns == OthernumRows, "Incompatible matrix dimensions for multiplication");

            Derived result{0.0};

            for (std::size_t row = 0; row < numRows; ++row) {
                for (std::size_t col = 0; col < OthernumColumns; ++col) {
                    for (std::size_t k = 0; k < numColumns; ++k) {
                        result[row][col] += (*this)[row][k] * other[k][col];
                    }
                }
            }

            return result;
        }

        template<typename Any>
        constexpr RowType operator*(const vector_t<Any, scalar_t, numColumns, Frame>& v) const {
            RowType result{0.0};

            for (std::size_t row = 0; row < numRows; ++row) {
                for (std::size_t col = 0; col < numColumns; ++col) {
                    result[row] += (*this)[row][col] * v[col];
                }
            }

            return result;
        }

        template<typename Any>
        constexpr RowType operator/(const vector_t<Any, scalar_t, numRows, Frame>& v) const {
            RowType result{0.0};

            for (std::size_t row = 0; row < numRows; ++row) {
                for (std::size_t col = 0; col < numColumns; ++col) {
                    result[row] += (*this)[row][col] / v[col];
                }
            }

            return result;
        }

        friend constexpr std::ostream& operator<<(std::ostream& os, const Derived& m) {
            os << "{";
            for (std::size_t row = 0; row < numRows; ++row) {
                for (std::size_t col = 0; col < numColumns; ++col) {
                    os << m[row][col];
                    if (col < numColumns - 1) {
                        os << " ";
                    }
                }
                if (row < numRows - 1) {
                    os << "; ";
                }
            }
            os << "}";
            return os;
        }
    };

    template<typename Derived, typename ElementType, frame_t Frame>
    struct matrix3x3_t : public matrix_t<matrix3x3_t<Derived, ElementType, Frame>, std::array<ElementType, 3>, 3, 3, Frame> {
        using matrix_t<matrix3x3_t<Derived, ElementType, Frame>, std::array<ElementType, 3>, 3, 3, Frame>::matrix_t;

        matrix3x3_t(
            std::array<ElementType, 3> x,
            std::array<ElementType, 3> y,
            std::array<ElementType, 3> z
        ) {
            this->data[0] = x;
            this->data[1] = y;
            this->data[2] = z;
        }
    };
}

template<frame_t FromFrame, frame_t ToFrame>
struct rotation_matrix_t : public math::matrix_t<rotation_matrix_t<FromFrame, ToFrame>, direction_t<FromFrame>, 3, 3, FromFrame> {
    
    using math::matrix_t<rotation_matrix_t<FromFrame, ToFrame>, direction_t<FromFrame>, 3, 3, FromFrame>::matrix_t;

    constexpr scalar_t xx() const {
        return (*this)[0][0];
    }

    constexpr scalar_t xy() const {
        return (*this)[0][1];
    }

    constexpr scalar_t xz() const {
        return (*this)[0][2];
    }

    constexpr scalar_t yx() const {
        return (*this)[1][0];
    }

    constexpr scalar_t yy() const {
        return (*this)[1][1];
    }

    constexpr scalar_t yz() const {
        return (*this)[1][2];
    }

    constexpr scalar_t zx() const {
        return (*this)[2][0];
    }

    constexpr scalar_t zy() const {
        return (*this)[2][1];
    }

    constexpr scalar_t zz() const {
        return (*this)[2][2];
    }

    template<typename Any, typename T>
    constexpr Any operator*(const cartesian_t<Any, T, FromFrame>& v) const {
        Any result{0.0};

        for (std::size_t row = 0; row < 3; ++row) {
            for (std::size_t col = 0; col < 3; ++col) {
                result[row] += (*this)[row][col] * v[col];
            }
        }

        return result;
    }
    
    template<frame_t OtherFromFrame, frame_t OtherToFrame>
    constexpr rotation_matrix_t<OtherFromFrame, ToFrame> operator*(const rotation_matrix_t<OtherFromFrame, OtherToFrame>& v) const {
        static_assert(OtherToFrame == FromFrame, "Incompatible frame types for rotation matrix multiplication");

        rotation_matrix_t<OtherFromFrame, ToFrame> result{0.0};

        for (std::size_t row = 0; row < 3; ++row) {
            for (std::size_t col = 0; col < 3; ++col) {
                for (std::size_t k = 0; k < 3; ++k) {
                    result[row][col] += (*this)[row][k] * v[k][col];
                }
            }
        }

        return result;
    }

    constexpr direction_t<FromFrame> forward_from() const {
        return this[0];
    }
    
    constexpr direction_t<FromFrame> port_from() const {
        return this[1];
    }

    constexpr direction_t<FromFrame> zenith_from() const {
        return this[2];
    }

    constexpr direction_t<FromFrame> forward_to() const {
        return this * forward_from();
    }

    constexpr direction_t<FromFrame> port_to() const {
        return this * port_from();
    }

    constexpr direction_t<FromFrame> zenith_to() const {
        return this * zenith_from();
    }
};

template<frame_t Frame>
struct frame_axes_t {
    direction_t<Frame> forward;
    direction_t<Frame> port;
    direction_t<Frame> zenith;
};

template<frame_t Frame>
struct position_t : public cartesian_t<position_t<Frame>, meters_t, Frame> {
    using cartesian_t<position_t<Frame>, meters_t, Frame>::cartesian_t;
};

template<frame_t Frame>
struct velocity_t : public cartesian_t<velocity_t<Frame>, meters_per_second_t, Frame> {
    using cartesian_t<velocity_t<Frame>, meters_per_second_t, Frame>::cartesian_t;
};

template<frame_t Frame>
struct acceleration_t : public cartesian_t<acceleration_t<Frame>, meters_per_second_squared_t, Frame> {
    using cartesian_t<acceleration_t<Frame>, meters_per_second_squared_t, Frame>::cartesian_t;
};

template<frame_t Frame>
struct orientation_t : public math::quaternion_t<orientation_t<Frame>, Frame> {
    using math::quaternion_t<orientation_t<Frame>, Frame>::quaternion_t;
};

template<frame_t Frame>
struct inertial_tensor_t : public math::matrix3x3_t<inertial_tensor_t<Frame>, kilograms_meter_squared_t, Frame> {
    using math::matrix3x3_t<inertial_tensor_t<Frame>, kilograms_meter_squared_t, Frame>::matrix3x3_t;
};
