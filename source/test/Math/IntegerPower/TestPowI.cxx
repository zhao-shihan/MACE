#include "MACE/Utility/Math/IntegerPower.hxx"

#include <cmath>
#include <complex>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>

using namespace MACE::Utility::Math;

std::string TestEqual(auto a, auto real) {
    const auto relErr = a / real - 1;
    if (std::abs(relErr) > 2 * std::numeric_limits<double>::epsilon()) {
        return std::string("***FAIL/OVERFLOW***, relErr = ").append(std::to_string(relErr * 1e16)).append("e-16");
    }
    return "PASS";
};

template<int N>
void TestPowI(auto xI, auto xL, auto xLL, auto xUL, auto xULL) {
    std::cout << std::setprecision(18)
              << "(int)                 " << TestEqual(PowI<N>(xI), std::pow(xI, N)) << " --> PowI<" << N << ">(x) = " << PowI<N>(xI) << ", pow(x, " << N << ") = " << std::pow(xI, N) << '\n'
              << "(long)                " << TestEqual(PowI<N>(xL), std::pow(xL, N)) << " --> PowI<" << N << ">(x) = " << PowI<N>(xL) << ", pow(x, " << N << ") = " << std::pow(xL, N) << '\n'
              << "(long long)           " << TestEqual(PowI<N>(xLL), std::pow(xLL, N)) << " --> PowI<" << N << ">(x) = " << PowI<N>(xLL) << ", pow(x, " << N << ") = " << std::pow(xLL, N) << '\n'
              << "(unsigned long)       " << TestEqual(PowI<N>(xUL), std::pow(xUL, N)) << " --> PowI<" << N << ">(x) = " << PowI<N>(xUL) << ", pow(x, " << N << ") = " << std::pow(xUL, N) << '\n'
              << "(unsigned long long)  " << TestEqual(PowI<N>(xULL), std::pow(xULL, N)) << " --> PowI<" << N << ">(x) = " << PowI<N>(xULL) << ", pow(x, " << N << ") = " << std::pow(xULL, N) << '\n'
              << std::endl;
}

int main(int, char* argv[]) {
    const auto xI = std::stoi(argv[1]);
    const auto xL = std::stol(argv[1]);
    const auto xLL = std::stoll(argv[1]);
    const auto xUL = std::stoul(argv[1]);
    const auto xULL = std::stoull(argv[1]);

    TestPowI<0>(xI, xL, xLL, xUL, xULL);
    TestPowI<1>(xI, xL, xLL, xUL, xULL);
    TestPowI<2>(xI, xL, xLL, xUL, xULL);
    TestPowI<3>(xI, xL, xLL, xUL, xULL);
    TestPowI<7>(xI, xL, xLL, xUL, xULL);
    TestPowI<11>(xI, xL, xLL, xUL, xULL);

    return EXIT_SUCCESS;
}
