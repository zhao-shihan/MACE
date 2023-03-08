#include "MACE/Math/IntegerPower.hxx"

#include <cmath>
#include <complex>

using namespace MACE::Math;

#define MACE_TEST_GENERATE_POWI_FUNC(FPType, Prefix)               \
    FPType Prefix##__DoConstPowIImAlmostEmpty() {                  \
        return PowZN<4>(3);                                        \
    }                                                              \
    FPType Prefix##__DoConstMultiplyImAlmostEmpty() {              \
        return 3 * 3 * 3 * 3;                                      \
    }                                                              \
    FPType Prefix##__DoConstPow() {                                \
        return std::pow(3, 4);                                     \
    }                                                              \
    FPType Prefix##__DoPowISquareImEquivlentToMultiply(FPType a) { \
        return PowZN<2>(a);                                        \
    }                                                              \
    FPType Prefix##__DoMultiplySquare(FPType a) {                  \
        return a * a;                                              \
    }                                                              \
    FPType Prefix##__DoPowSquareImProbablySlow(FPType a) {         \
        return std::pow(a, 2);                                     \
    }                                                              \
    FPType Prefix##__DoPowICubicImEquivlentToMultiply(FPType a) {  \
        return PowZN<3>(a);                                        \
    }                                                              \
    FPType Prefix##__DoMultiplyCubic(FPType a) {                   \
        return a * a * a;                                          \
    }                                                              \
    FPType Prefix##__DoPowCubicImSlow(FPType a) {                  \
        return std::pow(a, 3);                                     \
    }                                                              \
    FPType Prefix##__DoPowI5ImEquivlentToMultiply(FPType a) {      \
        return PowZN<5>(a);                                        \
    }                                                              \
    FPType Prefix##__DoMultiply5th(FPType a) {                     \
        return (a * a) * (a * a) * a;                              \
    }                                                              \
    FPType Prefix##__DoPow5thImSlow(FPType a) {                    \
        return std::pow(a, 5);                                     \
    }

MACE_TEST_GENERATE_POWI_FUNC(char, C)
MACE_TEST_GENERATE_POWI_FUNC(signed char, SC)
MACE_TEST_GENERATE_POWI_FUNC(unsigned char, UC)
MACE_TEST_GENERATE_POWI_FUNC(char8_t, C8)
MACE_TEST_GENERATE_POWI_FUNC(char16_t, C16)
MACE_TEST_GENERATE_POWI_FUNC(char32_t, C32)
MACE_TEST_GENERATE_POWI_FUNC(wchar_t, WC)
MACE_TEST_GENERATE_POWI_FUNC(short, S)
MACE_TEST_GENERATE_POWI_FUNC(unsigned short, US)
MACE_TEST_GENERATE_POWI_FUNC(int, I)
MACE_TEST_GENERATE_POWI_FUNC(unsigned int, UI)
MACE_TEST_GENERATE_POWI_FUNC(long, L)
MACE_TEST_GENERATE_POWI_FUNC(unsigned long, UL)
MACE_TEST_GENERATE_POWI_FUNC(long long, LL)
MACE_TEST_GENERATE_POWI_FUNC(unsigned long long, ULL)

#undef MACE_TEST_GENERATE_POWI_FUNC
