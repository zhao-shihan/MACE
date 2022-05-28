#include "MACE/Utility/IntegerPower.hxx"

#include <cmath>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>

using namespace MACE::Utility;

template<uintmax_t N>
void TestPowInt(auto xI, auto xL, auto xLL, auto xUL, auto xULL, auto xF, auto xD, auto xLD) {
    auto TestEqual = [](auto a, auto b) {
        const long double aLD = a;
        const long double bLD = b;
        const auto diff = std::abs(aLD - bLD) / std::midpoint(aLD, bLD);
        std::string result("Passed.");
        if (diff != 0) {
            result = "Failed, relative error = ";
            std::string diffStr;
            std::stringstream ss;
            ss << diff << '.';
            ss >> diffStr;
            result.append(diffStr);
        }
        return result;
    };
    std::cout << "(int)                 PowInt<" << N << ">(x) = " << PowInt<N>(xI) << ", pow(x, " << N << ") = " << pow(xI, N) << " --> " << TestEqual(PowInt<N>(xI), std::pow(xI, N)) << '\n'
              << "(long)                PowInt<" << N << ">(x) = " << PowInt<N>(xL) << ", pow(x, " << N << ") = " << pow(xL, N) << " --> " << TestEqual(PowInt<N>(xL), std::pow(xL, N)) << '\n'
              << "(long long)           PowInt<" << N << ">(x) = " << PowInt<N>(xLL) << ", pow(x, " << N << ") = " << pow(xLL, N) << " --> " << TestEqual(PowInt<N>(xLL), std::pow(xLL, N)) << '\n'
              << "(unsigned long)       PowInt<" << N << ">(x) = " << PowInt<N>(xUL) << ", pow(x, " << N << ") = " << pow(xUL, N) << " --> " << TestEqual(PowInt<N>(xUL), std::pow(xUL, N)) << '\n'
              << "(unsigned long long)  PowInt<" << N << ">(x) = " << PowInt<N>(xULL) << ", pow(x, " << N << ") = " << pow(xULL, N) << " --> " << TestEqual(PowInt<N>(xULL), std::pow(xULL, N)) << '\n'
              << "(float)               PowInt<" << N << ">(x) = " << PowInt<N>(xF) << ", pow(x, " << N << ") = " << pow(xF, N) << " --> " << TestEqual(PowInt<N>(xF), std::pow(xF, N)) << '\n'
              << "(double)              PowInt<" << N << ">(x) = " << PowInt<N>(xD) << ", pow(x, " << N << ") = " << pow(xD, N) << " --> " << TestEqual(PowInt<N>(xD), std::pow(xD, N)) << '\n'
              << "(long double)         PowInt<" << N << ">(x) = " << PowInt<N>(xLD) << ", pow(x, " << N << ") = " << pow(xLD, N) << " --> " << TestEqual(PowInt<N>(xLD), std::pow(xLD, N)) << '\n'
              << std::endl;
}

template<intmax_t N>
void TestPowInt(auto xF, auto xD, auto xLD) {
    auto TestEqual = [](auto a, auto b) {
        const long double aLD = a;
        const long double bLD = b;
        const auto diff = std::abs(aLD - bLD) / std::midpoint(aLD, bLD);
        std::string result("Passed.");
        if (diff != 0) {
            result = "Failed, relative error = ";
            std::string diffStr;
            std::stringstream ss;
            ss << diff << '.';
            ss >> diffStr;
            result.append(diffStr);
        }
        return result;
    };
    std::cout << "(float)               PowInt<" << N << ">(x) = " << PowInt<N>(xF) << ", pow(x, " << N << ") = " << pow(xF, N) << " --> " << TestEqual(PowInt<N>(xF), std::pow(xF, N)) << '\n'
              << "(double)              PowInt<" << N << ">(x) = " << PowInt<N>(xD) << ", pow(x, " << N << ") = " << pow(xD, N) << " --> " << TestEqual(PowInt<N>(xD), std::pow(xD, N)) << '\n'
              << "(long double)         PowInt<" << N << ">(x) = " << PowInt<N>(xLD) << ", pow(x, " << N << ") = " << pow(xLD, N) << " --> " << TestEqual(PowInt<N>(xLD), std::pow(xLD, N)) << '\n'
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

    TestPowInt<0>(xI, xL, xLL, xUL, xULL, xF, xD, xLD);
    TestPowInt<1>(xI, xL, xLL, xUL, xULL, xF, xD, xLD);
    TestPowInt<2>(xI, xL, xLL, xUL, xULL, xF, xD, xLD);
    TestPowInt<7>(xI, xL, xLL, xUL, xULL, xF, xD, xLD);
    // TestPowInt<42>(xI, xL, xLL, xUL, xULL, xF, xD, xLD);
    TestPowInt<-1>(xF, xD, xLD);
    TestPowInt<-2>(xF, xD, xLD);
    TestPowInt<-7>(xF, xD, xLD);
    // TestPowInt<-42>(xF, xD, xLD);

    return EXIT_SUCCESS;
}
