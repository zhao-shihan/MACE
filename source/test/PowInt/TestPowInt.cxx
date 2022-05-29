#include "MACE/Utility/IntegerPower.hxx"

#include <cmath>
#include <complex>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>

using namespace MACE::Utility;

template<int N>
void TestPowInt(auto xI, auto xL, auto xLL, auto xUL, auto xULL, auto xF, auto xD, auto xLD, auto xCF, auto xCD, auto xCLD) {
    auto TestEqual = [](auto a, auto b, auto tolerance) {
        const auto relErr = 2 * std::abs(a - b) / std::abs(a + b);
        if (std::abs(relErr) > 1) {
            return "OVERFLOW";
        } else if (std::abs(relErr) > tolerance) {
            std::string result = "***FAIL***, relErr = ";
            std::string diffStr;
            std::stringstream ss;
            ss << relErr;
            ss >> diffStr;
            result.append(diffStr);
        }
        return "PASS";
    };
    std::cout << std::setprecision(18)
              << "(int)                 " << TestEqual(PowInt<N>(xI), std::pow(xI, N), 0) << " --> PowInt<" << N << ">(x) = " << PowInt<N>(xI) << ", pow(x, " << N << ") = " << std::pow(xI, N) << '\n'
              << "(long)                " << TestEqual(PowInt<N>(xL), std::pow(xL, N), 0) << " --> PowInt<" << N << ">(x) = " << PowInt<N>(xL) << ", pow(x, " << N << ") = " << std::pow(xL, N) << '\n'
              << "(long long)           " << TestEqual(PowInt<N>(xLL), std::pow(xLL, N), 0) << " --> PowInt<" << N << ">(x) = " << PowInt<N>(xLL) << ", pow(x, " << N << ") = " << std::pow(xLL, N) << '\n'
              << "(unsigned long)       " << TestEqual(PowInt<N>(xUL), std::pow(xUL, N), 0) << " --> PowInt<" << N << ">(x) = " << PowInt<N>(xUL) << ", pow(x, " << N << ") = " << std::pow(xUL, N) << '\n'
              << "(unsigned long long)  " << TestEqual(PowInt<N>(xULL), std::pow(xULL, N), 0) << " --> PowInt<" << N << ">(x) = " << PowInt<N>(xULL) << ", pow(x, " << N << ") = " << std::pow(xULL, N) << '\n'
              << "(float)               " << TestEqual(PowInt<N>(xF), std::pow(xF, N), 2 * std::numeric_limits<float>::epsilon()) << " --> PowInt<" << N << ">(x) = " << PowInt<N>(xF) << ", pow(x, " << N << ") = " << std::pow(xF, N) << '\n'
              << "(double)              " << TestEqual(PowInt<N>(xD), std::pow(xD, N), 2 * std::numeric_limits<double>::epsilon()) << " --> PowInt<" << N << ">(x) = " << PowInt<N>(xD) << ", pow(x, " << N << ") = " << std::pow(xD, N) << '\n'
              << "(long double)         " << TestEqual(PowInt<N>(xLD), std::pow(xLD, N), 2 * std::numeric_limits<long double>::epsilon()) << " --> PowInt<" << N << ">(x) = " << PowInt<N>(xLD) << ", pow(x, " << N << ") = " << std::pow(xLD, N) << '\n'
              << "(complex float)       " << TestEqual(PowInt<N>(xCF), std::pow(xCF, N), 2 * std::numeric_limits<float>::epsilon()) << " --> PowInt<" << N << ">(x) = " << PowInt<N>(xCF) << ", pow(x, " << N << ") = " << std::pow(xCF, N) << '\n'
              << "(complex double)      " << TestEqual(PowInt<N>(xCD), std::pow(xCD, N), 2 * std::numeric_limits<double>::epsilon()) << " --> PowInt<" << N << ">(x) = " << PowInt<N>(xCD) << ", pow(x, " << N << ") = " << std::pow(xCD, N) << '\n'
              << "(complex long double) " << TestEqual(PowInt<N>(xCLD), std::pow(xCLD, N), 2 * std::numeric_limits<long double>::epsilon()) << " --> PowInt<" << N << ">(x) = " << PowInt<N>(xCLD) << ", pow(x, " << N << ") = " << std::pow(xCLD, N) << '\n'
              << std::endl;
}

template<int N>
void TestPowInt(auto xF, auto xD, auto xLD, auto xCF, auto xCD, auto xCLD) {
    auto TestEqual = [](auto a, auto b, auto tolerance) {
        const auto relErr = 2 * std::abs(a - b) / std::abs(a + b);
        if (std::abs(relErr) > 1) {
            return "OVERFLOW";
        } else if (std::abs(relErr) > tolerance) {
            std::string result = "***FAIL***, relErr = ";
            std::string diffStr;
            std::stringstream ss;
            ss << relErr;
            ss >> diffStr;
            result.append(diffStr);
        }
        return "PASS";
    };
    std::cout << std::setprecision(18)
              << "(float)               " << TestEqual(PowInt<N>(xF), std::pow(xF, N), 2 * std::numeric_limits<float>::epsilon()) << " --> PowInt<" << N << ">(x) = " << PowInt<N>(xF) << ", pow(x, " << N << ") = " << std::pow(xF, N) << '\n'
              << "(double)              " << TestEqual(PowInt<N>(xD), std::pow(xD, N), 2 * std::numeric_limits<double>::epsilon()) << " --> PowInt<" << N << ">(x) = " << PowInt<N>(xD) << ", pow(x, " << N << ") = " << std::pow(xD, N) << '\n'
              << "(long double)         " << TestEqual(PowInt<N>(xLD), std::pow(xLD, N), 2 * std::numeric_limits<long double>::epsilon()) << " --> PowInt<" << N << ">(x) = " << PowInt<N>(xLD) << ", pow(x, " << N << ") = " << std::pow(xLD, N) << '\n'
              << "(complex float)       " << TestEqual(PowInt<N>(xCF), std::pow(xCF, N), 2 * std::numeric_limits<float>::epsilon()) << " --> PowInt<" << N << ">(x) = " << PowInt<N>(xCF) << ", pow(x, " << N << ") = " << std::pow(xCF, N) << '\n'
              << "(complex double)      " << TestEqual(PowInt<N>(xCD), std::pow(xCD, N), 2 * std::numeric_limits<double>::epsilon()) << " --> PowInt<" << N << ">(x) = " << PowInt<N>(xCD) << ", pow(x, " << N << ") = " << std::pow(xCD, N) << '\n'
              << "(complex long double) " << TestEqual(PowInt<N>(xCLD), std::pow(xCLD, N), 2 * std::numeric_limits<long double>::epsilon()) << " --> PowInt<" << N << ">(x) = " << PowInt<N>(xCLD) << ", pow(x, " << N << ") = " << std::pow(xCLD, N) << '\n'
              << std::endl;
}

int main(int argc, char* argv[]) {
    const auto xI = std::stoi(argv[1]);
    const auto xL = std::stol(argv[1]);
    const auto xLL = std::stoll(argv[1]);
    const auto xUL = std::stoul(argv[1]);
    const auto xULL = std::stoull(argv[1]);
    const auto xF = std::stof(argv[1]);
    const auto xD = std::stod(argv[1]);
    const auto xLD = std::stold(argv[1]);
    const auto xCF = std::complex<float>(xF, (argc == 2) ? xF : std::stof(argv[2]));
    const auto xCD = std::complex<double>(xD, (argc == 2) ? xD : std::stod(argv[2]));
    const auto xCLD = std::complex<long double>(xLD, (argc == 2) ? xLD : std::stold(argv[2]));

    TestPowInt<0>(xI, xL, xLL, xUL, xULL, xF, xD, xLD, xCF, xCD, xCLD);
    TestPowInt<1>(xI, xL, xLL, xUL, xULL, xF, xD, xLD, xCF, xCD, xCLD);
    TestPowInt<2>(xI, xL, xLL, xUL, xULL, xF, xD, xLD, xCF, xCD, xCLD);
    TestPowInt<3>(xI, xL, xLL, xUL, xULL, xF, xD, xLD, xCF, xCD, xCLD);
    TestPowInt<7>(xI, xL, xLL, xUL, xULL, xF, xD, xLD, xCF, xCD, xCLD);
    TestPowInt<-1>(xF, xD, xLD, xCF, xCD, xCLD);
    TestPowInt<-2>(xF, xD, xLD, xCF, xCD, xCLD);
    TestPowInt<-3>(xF, xD, xLD, xCF, xCD, xCLD);
    TestPowInt<-7>(xF, xD, xLD, xCF, xCD, xCLD);

    return EXIT_SUCCESS;
}
