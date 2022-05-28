#include "MACE/Utility/IntegerPower.hxx"

#include <cmath>

using namespace MACE::Utility;

double DoConstPowIntImAlmostEmpty() {
    return PowInt<4>(42);
}

double DoConstMultiplyImAlmostEmpty() {
    return 42 * 42 * 42 * 42;
}

double DoConstPowImProbablySlow() {
    return std::pow(42, 4);
}

double DoPowIntSquareImEquivlentToMultiply(double a) {
    return PowInt<2>(a);
}

double DoMultiplySquare(double a) {
    return a * a;
}

double DoPowSquareImSlow(double a) {
    return std::pow(a, 2);
}

double DoPowIntCubicImEquivlentToMultiply(double a) {
    return PowInt<3>(a);
}

double DoMultiplyCubic(double a) {
    return a * a * a;
}

double DoPowCubicImSlow(double a) {
    return std::pow(a, 3);
}

double DoPowInt5ImEquivlentToMultiply(double a) {
    return PowInt<5>(a);
}

double DoMultiply5th(double a) {
    return a * a * a * a * a;
}

double DoPow5thImSlow(double a) {
    return std::pow(a, 5);
}

double DoPowIntNeg4ImEquivlentToDivideMultiply(double a) {
    return PowInt<-4>(a);
}

double DoDivideMultiply4th(double a) {
    return 1 / (a * a * a * a);
}

double DoPowNeg4thImSlow(double a) {
    return std::pow(a, -4);
}
