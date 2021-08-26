#ifndef Vector3_hh
#define Vector3_hh 1

#include <cmath>

namespace MACE {
    namespace SimMTransport {
        struct Vector3 {
            double_t x, y, z;

            inline Vector3() {}
            inline Vector3(double_t px, double_t py, double_t pz);

            inline const double_t* CArr() const { return &x; }
            inline double_t RSq() const { return x * x + y * y + z * z; }
            inline double_t R() const { return sqrt(x * x + y * y + z * z); }
            inline double_t NormSq() const { return x * x + y * y + z * z; }
            inline double_t Norm() const { return sqrt(x * x + y * y + z * z); }
            inline double_t RhoSq() const { return x * x + y * y; }
            inline double_t Rho() const { return sqrt(x * x + y * y); }
            inline double_t Theta() const { return atan2(sqrt(x * x + y * y), z); }
            inline double_t Phi() const { return atan2(y, x); }

            inline Vector3& operator+=(const Vector3& rhs);
            inline Vector3& operator-=(const Vector3& rhs);
            inline Vector3& operator*=(double_t rhs);
            inline Vector3& operator/=(double_t rhs);
        };

        inline Vector3::Vector3(double_t px, double_t py, double_t pz) :
            x(px), y(py), z(pz) {}

        inline Vector3& Vector3::operator+=(const Vector3& rhs) {
            this->x += rhs.x;
            this->y += rhs.y;
            this->z += rhs.z;
            return *this;
        }

        inline Vector3& Vector3::operator-=(const Vector3& rhs) {
            this->x -= rhs.x;
            this->y -= rhs.y;
            this->z -= rhs.z;
            return *this;
        }

        inline Vector3& Vector3::operator*=(double_t rhs) {
            this->x *= rhs;
            this->y *= rhs;
            this->z *= rhs;
            return *this;
        }

        inline Vector3& Vector3::operator/=(double_t rhs) {
            this->x /= rhs;
            this->y /= rhs;
            this->z /= rhs;
            return *this;
        }

        inline Vector3 operator+(const Vector3& lhs, const Vector3& rhs) {
            return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
        }

        inline Vector3 operator-(const Vector3& lhs, const Vector3& rhs) {
            return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
        }

        inline Vector3 operator*(double_t lhs, const Vector3& rhs) {
            return Vector3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
        }

        inline Vector3 operator*(const Vector3& lhs, double_t rhs) {
            return Vector3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
        }

        inline Vector3 operator/(const Vector3& lhs, double_t rhs) {
            return Vector3(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
        }
    }
}

#endif

