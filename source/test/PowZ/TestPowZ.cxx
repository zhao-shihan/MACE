#include "MACE/Utility/IntegerPower.hxx"

#include <cmath>
#include <complex>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>

using namespace MACE::Utility;

std::string TestEqual(auto a, auto b, auto tolerance) {
    const auto relErr = 2 * std::abs(a - b) / std::abs(a + b);
    if (std::abs(relErr) > 1) {
        return "OVERFLOW";
    }
    if (std::abs(relErr) > tolerance) {
        return std::string("***FAIL***, relErr = ").append(std::to_string(relErr));
    }
    return "PASS";
};

template<int N>
void TestPowZ(auto xI, auto xL, auto xLL, auto xUL, auto xULL, auto xF, auto xD, auto xLD) {
    std::cout << std::setprecision(18)
              << "(int)                 " << TestEqual(PowZ<N>(xI), std::pow(xI, N), 0) << " --> PowZ<" << N << ">(x) = " << PowZ<N>(xI) << ", pow(x, " << N << ") = " << std::pow(xI, N) << '\n'
              << "(long)                " << TestEqual(PowZ<N>(xL), std::pow(xL, N), 0) << " --> PowZ<" << N << ">(x) = " << PowZ<N>(xL) << ", pow(x, " << N << ") = " << std::pow(xL, N) << '\n'
              << "(long long)           " << TestEqual(PowZ<N>(xLL), std::pow(xLL, N), 0) << " --> PowZ<" << N << ">(x) = " << PowZ<N>(xLL) << ", pow(x, " << N << ") = " << std::pow(xLL, N) << '\n'
              << "(unsigned long)       " << TestEqual(PowZ<N>(xUL), std::pow(xUL, N), 0) << " --> PowZ<" << N << ">(x) = " << PowZ<N>(xUL) << ", pow(x, " << N << ") = " << std::pow(xUL, N) << '\n'
              << "(unsigned long long)  " << TestEqual(PowZ<N>(xULL), std::pow(xULL, N), 0) << " --> PowZ<" << N << ">(x) = " << PowZ<N>(xULL) << ", pow(x, " << N << ") = " << std::pow(xULL, N) << '\n'
              << "(float)               " << TestEqual(PowZ<N>(xF), std::pow(xF, N), 2 * std::numeric_limits<float>::epsilon()) << " --> PowZ<" << N << ">(x) = " << PowZ<N>(xF) << ", pow(x, " << N << ") = " << std::pow(xF, N) << '\n'
              << "(double)              " << TestEqual(PowZ<N>(xD), std::pow(xD, N), 2 * std::numeric_limits<double>::epsilon()) << " --> PowZ<" << N << ">(x) = " << PowZ<N>(xD) << ", pow(x, " << N << ") = " << std::pow(xD, N) << '\n'
              << "(long double)         " << TestEqual(PowZ<N>(xLD), std::pow(xLD, N), 2 * std::numeric_limits<long double>::epsilon()) << " --> PowZ<" << N << ">(x) = " << PowZ<N>(xLD) << ", pow(x, " << N << ") = " << std::pow(xLD, N) << '\n'
              << std::endl;
}

template<int N>
void TestPowZ(auto xF, auto xD, auto xLD) {
    std::cout << std::setprecision(18)
              << "(float)               " << TestEqual(PowZ<N>(xF), std::pow(xF, N), 2 * std::numeric_limits<float>::epsilon()) << " --> PowZ<" << N << ">(x) = " << PowZ<N>(xF) << ", pow(x, " << N << ") = " << std::pow(xF, N) << '\n'
              << "(double)              " << TestEqual(PowZ<N>(xD), std::pow(xD, N), 2 * std::numeric_limits<double>::epsilon()) << " --> PowZ<" << N << ">(x) = " << PowZ<N>(xD) << ", pow(x, " << N << ") = " << std::pow(xD, N) << '\n'
              << "(long double)         " << TestEqual(PowZ<N>(xLD), std::pow(xLD, N), 2 * std::numeric_limits<long double>::epsilon()) << " --> PowZ<" << N << ">(x) = " << PowZ<N>(xLD) << ", pow(x, " << N << ") = " << std::pow(xLD, N) << '\n'
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
    TestPowZ<-1>(xF, xD, xLD);
    TestPowZ<-2>(xF, xD, xLD);
    TestPowZ<-3>(xF, xD, xLD);
    TestPowZ<-7>(xF, xD, xLD);

    return EXIT_SUCCESS;
}
