#include "MACE/Utility/IntegerPower.hxx"

#include <cmath>
#include <complex>

using namespace MACE::Utility;

#define MACE_TEST_GENERATE_FP_POWINT_FUNC(FPType, Prefix)                \
    FPType Prefix##__DoConstPowIntImAlmostEmpty() {                      \
        return PowInt<4>(3);                                             \
    }                                                                    \
    FPType Prefix##__DoConstMultiplyImAlmostEmpty() {                    \
        return 3 * 3 * 3 * 3;                                            \
    }                                                                    \
    FPType Prefix##__DoConstPowImProbablySlow() {                        \
        return std::pow(3, 4);                                           \
    }                                                                    \
    FPType Prefix##__DoPowIntSquareImEquivlentToMultiply(FPType a) {     \
        return PowInt<2>(a);                                             \
    }                                                                    \
    FPType Prefix##__DoMultiplySquare(FPType a) {                        \
        return a * a;                                                    \
    }                                                                    \
    FPType Prefix##__DoPowSquareImSlow(FPType a) {                       \
        return std::pow(a, 2);                                           \
    }                                                                    \
    FPType Prefix##__DoPowIntCubicImEquivlentToMultiply(FPType a) {      \
        return PowInt<3>(a);                                             \
    }                                                                    \
    FPType Prefix##__DoMultiplyCubic(FPType a) {                         \
        return a * a * a;                                                \
    }                                                                    \
    FPType Prefix##__DoPowCubicImSlow(FPType a) {                        \
        return std::pow(a, 3);                                           \
    }                                                                    \
    FPType Prefix##__DoPowInt5ImEquivlentToMultiply(FPType a) {          \
        return PowInt<5>(a);                                             \
    }                                                                    \
    FPType Prefix##__DoMultiply5th(FPType a) {                           \
        return a * a * a * a * a;                                        \
    }                                                                    \
    FPType Prefix##__DoPow5thImSlow(FPType a) {                          \
        return std::pow(a, 5);                                           \
    }                                                                    \
    FPType Prefix##__DoPowIntNeg4ImEquivlentToDivideMultiply(FPType a) { \
        return PowInt<-4>(a);                                            \
    }                                                                    \
    FPType Prefix##__DoDivideMultiply4th(FPType a) {                     \
        return (FPType)(1) / (a * a * a * a);                            \
    }                                                                    \
    FPType Prefix##__DoPowNeg4thImSlow(FPType a) {                       \
        return std::pow(a, -4);                                          \
    }

MACE_TEST_GENERATE_FP_POWINT_FUNC(float, F)
MACE_TEST_GENERATE_FP_POWINT_FUNC(double, D)
MACE_TEST_GENERATE_FP_POWINT_FUNC(long double, LD)
MACE_TEST_GENERATE_FP_POWINT_FUNC(std::complex<float>, CF)
MACE_TEST_GENERATE_FP_POWINT_FUNC(std::complex<double>, CD)
MACE_TEST_GENERATE_FP_POWINT_FUNC(std::complex<long double>, CLD)

#undef MACE_TEST_GENERATE_FP_POWINT_FUNC

#define MACE_TEST_GENERATE_INTEGRAL_POWINT_FUNC(IntType, Prefix)       \
    IntType Prefix##__DoConstPowIntImAlmostEmpty() {                   \
        return PowInt<4>(3);                                           \
    }                                                                  \
    IntType Prefix##__DoConstMultiplyImAlmostEmpty() {                 \
        return 3 * 3 * 3 * 3;                                          \
    }                                                                  \
    IntType Prefix##__DoConstPowImProbablySlow() {                     \
        return std::pow(3, 4);                                         \
    }                                                                  \
    IntType Prefix##__DoPowIntSquareImEquivlentToMultiply(IntType a) { \
        return PowInt<2>(a);                                           \
    }                                                                  \
    IntType Prefix##__DoMultiplySquare(IntType a) {                    \
        return a * a;                                                  \
    }                                                                  \
    IntType Prefix##__DoPowSquareImSlow(IntType a) {                   \
        return std::pow(a, 2);                                         \
    }                                                                  \
    IntType Prefix##__DoPowIntCubicImEquivlentToMultiply(IntType a) {  \
        return PowInt<3>(a);                                           \
    }                                                                  \
    IntType Prefix##__DoMultiplyCubic(IntType a) {                     \
        return a * a * a;                                              \
    }                                                                  \
    IntType Prefix##__DoPowCubicImSlow(IntType a) {                    \
        return std::pow(a, 3);                                         \
    }                                                                  \
    IntType Prefix##__DoPowInt5ImEquivlentToMultiply(IntType a) {      \
        return PowInt<5>(a);                                           \
    }                                                                  \
    IntType Prefix##__DoMultiply5th(IntType a) {                       \
        return a * a * a * a * a;                                      \
    }                                                                  \
    IntType Prefix##__DoPow5thImSlow(IntType a) {                      \
        return std::pow(a, 5);                                         \
    }

MACE_TEST_GENERATE_INTEGRAL_POWINT_FUNC(char, C)
MACE_TEST_GENERATE_INTEGRAL_POWINT_FUNC(unsigned char, UC)
MACE_TEST_GENERATE_INTEGRAL_POWINT_FUNC(short, S)
MACE_TEST_GENERATE_INTEGRAL_POWINT_FUNC(unsigned short, US)
MACE_TEST_GENERATE_INTEGRAL_POWINT_FUNC(int, I)
MACE_TEST_GENERATE_INTEGRAL_POWINT_FUNC(unsigned int, UI)
MACE_TEST_GENERATE_INTEGRAL_POWINT_FUNC(long, L)
MACE_TEST_GENERATE_INTEGRAL_POWINT_FUNC(unsigned long, UL)
MACE_TEST_GENERATE_INTEGRAL_POWINT_FUNC(long long, LL)
MACE_TEST_GENERATE_INTEGRAL_POWINT_FUNC(unsigned long long, ULL)

#undef MACE_TEST_GENERATE_INTEGRAL_POWINT_FUNC
