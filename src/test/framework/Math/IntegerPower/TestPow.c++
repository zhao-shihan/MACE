#include "MACE/Math/IntegerPower.h++"

#include <cmath>
#include <complex>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>

using namespace MACE::Math;

std::string TestEqual(auto a, auto real, auto tolerance) {
    if (std::abs(real) <= std::numeric_limits<decltype(real)>::min() or std::isinf(real)) {
        return "OVERFLOW";
    }
    const auto relErr = a / real - 1;
    if (std::abs(relErr) > tolerance) {
        return std::string("***FAIL***, relErr = ").append(std::to_string(relErr * 1e16)).append("e-16");
    }
    return "PASS";
}

template<int N>
void TestPowZ(auto xI, auto xL, auto xLL, auto xUL, auto xULL, auto xF, auto xD, auto xLD) {
    std::cout << std::setprecision(18)
              << "(int)                 " << TestEqual(Pow<N>(xI), std::pow(xI, N), std::abs(N) * std::numeric_limits<double>::epsilon()) << " --> Pow<" << N << ">(x) = " << Pow<N>(xI) << ", pow(x, " << N << ") = " << std::pow(xI, N) << '\n'
              << "(long)                " << TestEqual(Pow<N>(xL), std::pow(xL, N), std::abs(N) * std::numeric_limits<double>::epsilon()) << " --> Pow<" << N << ">(x) = " << Pow<N>(xL) << ", pow(x, " << N << ") = " << std::pow(xL, N) << '\n'
              << "(long long)           " << TestEqual(Pow<N>(xLL), std::pow(xLL, N), std::abs(N) * std::numeric_limits<double>::epsilon()) << " --> Pow<" << N << ">(x) = " << Pow<N>(xLL) << ", pow(x, " << N << ") = " << std::pow(xLL, N) << '\n'
              << "(unsigned long)       " << TestEqual(Pow<N>(xUL), std::pow(xUL, N), std::abs(N) * std::numeric_limits<double>::epsilon()) << " --> Pow<" << N << ">(x) = " << Pow<N>(xUL) << ", pow(x, " << N << ") = " << std::pow(xUL, N) << '\n'
              << "(unsigned long long)  " << TestEqual(Pow<N>(xULL), std::pow(xULL, N), std::abs(N) * std::numeric_limits<double>::epsilon()) << " --> Pow<" << N << ">(x) = " << Pow<N>(xULL) << ", pow(x, " << N << ") = " << std::pow(xULL, N) << '\n'
              << "(float)               " << TestEqual(Pow<N>(xF), std::pow(xF, (float)N), std::abs(N) * std::numeric_limits<float>::epsilon()) << " --> Pow<" << N << ">(x) = " << Pow<N>(xF) << ", pow(x, " << N << ") = " << std::pow(xF, (float)N) << '\n'
              << "(double)              " << TestEqual(Pow<N>(xD), std::pow(xD, N), std::abs(N) * std::numeric_limits<double>::epsilon()) << " --> Pow<" << N << ">(x) = " << Pow<N>(xD) << ", pow(x, " << N << ") = " << std::pow(xD, N) << '\n'
              << "(long double)         " << TestEqual(Pow<N>(xLD), std::pow(xLD, (long double)N), std::abs(N) * std::numeric_limits<long double>::epsilon()) << " --> Pow<" << N << ">(x) = " << Pow<N>(xLD) << ", pow(x, " << N << ") = " << std::pow(xLD, (long double)N) << '\n'
              << std::endl;
}

int main(int, char* argv[]) {
    const auto xI = std::stoi(argv[1]);
    const auto xL = std::stol(argv[1]);
    const auto xLL = std::stoll(argv[1]);
    const auto xUL = std::stoul(argv[1]);
    const auto xULL = std::stoull(argv[1]);
    const auto xF = std::stof(argv[1]);
    const auto xD = std::stod(argv[1]);
    const auto xLD = std::stold(argv[1]);

    TestPowZ<0>(xI, xL, xLL, xUL, xULL, xF, xD, xLD);
    TestPowZ<1>(xI, xL, xLL, xUL, xULL, xF, xD, xLD);
    TestPowZ<2>(xI, xL, xLL, xUL, xULL, xF, xD, xLD);
    TestPowZ<3>(xI, xL, xLL, xUL, xULL, xF, xD, xLD);
    TestPowZ<7>(xI, xL, xLL, xUL, xULL, xF, xD, xLD);
    TestPowZ<11>(xI, xL, xLL, xUL, xULL, xF, xD, xLD);
    TestPowZ<120>(xI, xL, xLL, xUL, xULL, xF, xD, xLD);
    TestPowZ<177>(xI, xL, xLL, xUL, xULL, xF, xD, xLD);
    TestPowZ<-1>(xI, xL, xLL, xUL, xULL, xF, xD, xLD);
    TestPowZ<-2>(xI, xL, xLL, xUL, xULL, xF, xD, xLD);
    TestPowZ<-3>(xI, xL, xLL, xUL, xULL, xF, xD, xLD);
    TestPowZ<-7>(xI, xL, xLL, xUL, xULL, xF, xD, xLD);
    TestPowZ<-11>(xI, xL, xLL, xUL, xULL, xF, xD, xLD);
    TestPowZ<-120>(xI, xL, xLL, xUL, xULL, xF, xD, xLD);
    TestPowZ<-177>(xI, xL, xLL, xUL, xULL, xF, xD, xLD);

    return EXIT_SUCCESS;
}
