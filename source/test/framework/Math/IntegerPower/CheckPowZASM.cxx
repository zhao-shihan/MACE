#include "MACE/Math/IntegerPower.hxx"

#include <cmath>
#include <complex>

using namespace MACE::Math;

#define MACE_TEST_GENERATE_POWZ_FUNC(FPType, Prefix)                   \
    FPType Prefix##__DoConstPowZImAlmostEmpty() {                      \
        return Pow4(3);                                                \
    }                                                                  \
    FPType Prefix##__DoConstMultiplyImAlmostEmpty() {                  \
        return 3 * 3 * 3 * 3;                                          \
    }                                                                  \
    FPType Prefix##__DoConstPow() {                                    \
        return std::pow(3, 4);                                         \
    }                                                                  \
    FPType Prefix##__DoPowZSquareImEquivlentToMultiply(FPType a) {     \
        return Pow2(a);                                                \
    }                                                                  \
    FPType Prefix##__DoMultiplySquare(FPType a) {                      \
        return a * a;                                                  \
    }                                                                  \
    FPType Prefix##__DoPowSquareImProbablySlow(FPType a) {             \
        return std::pow(a, 2);                                         \
    }                                                                  \
    FPType Prefix##__DoPowZCubicImEquivlentToMultiply(FPType a) {      \
        return Pow3(a);                                                \
    }                                                                  \
    FPType Prefix##__DoMultiplyCubic(FPType a) {                       \
        return a * a * a;                                              \
    }                                                                  \
    FPType Prefix##__DoPowCubicImSlow(FPType a) {                      \
        return std::pow(a, 3);                                         \
    }                                                                  \
    FPType Prefix##__DoPowZ5ImEquivlentToMultiply(FPType a) {          \
        return Pow5(a);                                                \
    }                                                                  \
    FPType Prefix##__DoMultiply5th(FPType a) {                         \
        return (a * a) * (a * a) * a;                                  \
    }                                                                  \
    FPType Prefix##__DoPow5thImSlow(FPType a) {                        \
        return std::pow(a, 5);                                         \
    }                                                                  \
    FPType Prefix##__DoPowZNeg4ImEquivlentToDivideMultiply(FPType a) { \
        return PowZ<-4>(a);                                            \
    }                                                                  \
    FPType Prefix##__DoDivideMultiply4th(FPType a) {                   \
        return (FPType)(1) / ((a * a) * (a * a));                      \
    }                                                                  \
    FPType Prefix##__DoPowNeg4thImSlow(FPType a) {                     \
        return std::pow(a, -4);                                        \
    }

MACE_TEST_GENERATE_POWZ_FUNC(float, F)
MACE_TEST_GENERATE_POWZ_FUNC(double, D)
MACE_TEST_GENERATE_POWZ_FUNC(long double, LD)

#undef MACE_TEST_GENERATE_POWZ_FUNC
