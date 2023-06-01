#include "MACE/Math/RALog.h++"
#include "MACE/Math/Random/Distribution/Uniform.h++"
#include "MACE/Math/Random/Generator/Xoshiro256Plus.h++"
#include "MACE/Utility/CPUTimeStopwatch.h++"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include <type_traits>
#include <vector>

using namespace MACE;

#define MACE_RALOG_BENCHMARK(xFPType, TheLog)          \
    rng.Seed(20030202);                                \
    for (auto k = 0ull; k < n; ++k) {                  \
        xFPType = TheLog(u##xFPType(rng));             \
    }                                                  \
    sw.Reset();                                        \
    for (auto k = 0ull; k < n; ++k) {                  \
        xFPType = TheLog(u##xFPType(rng));             \
    }                                                  \
    tTotal = sw.MicrosecondsUsed();                    \
    std::cout << #TheLog "(" #xFPType "):\n"           \
              << "  last result = " << xFPType << '\n' \
              << "  performance = " << n / tTotal << " per us" << std::endl;

int main(int /* argc */, char* argv[]) {
    const auto n = std::stoull(argv[1]);

    volatile float xFloat;
    volatile double xDouble;

    CPUTimeStopwatch sw;
    double tTotal;

    Math::Random::Xoshiro256Plus rng;
    Math::Random::Uniform<double> uxFloat;
    Math::Random::Uniform<double> uxDouble;

    std::cout.precision(std::numeric_limits<double>::max_digits10);
    std::cout << "\n"
                 "================================================================\n"
                 "      log\n"
                 "================================================================\n"
              << std::endl;

    MACE_RALOG_BENCHMARK(xFloat, std::log)
    MACE_RALOG_BENCHMARK(xFloat, Math::RA2Log)
    MACE_RALOG_BENCHMARK(xFloat, Math::RA3Log)

    MACE_RALOG_BENCHMARK(xDouble, std::log)
    MACE_RALOG_BENCHMARK(xDouble, Math::RA2Log)
    MACE_RALOG_BENCHMARK(xDouble, Math::RA3Log)
    MACE_RALOG_BENCHMARK(xDouble, Math::RA4Log)
    MACE_RALOG_BENCHMARK(xDouble, Math::RA5Log)
    MACE_RALOG_BENCHMARK(xDouble, Math::RA6Log)

    std::cout << "\n"
                 "================================================================\n"
                 "      log2\n"
                 "================================================================\n"
              << std::endl;

    MACE_RALOG_BENCHMARK(xFloat, std::log2)
    MACE_RALOG_BENCHMARK(xFloat, Math::RA2Log2)
    MACE_RALOG_BENCHMARK(xFloat, Math::RA3Log2)

    MACE_RALOG_BENCHMARK(xDouble, std::log2)
    MACE_RALOG_BENCHMARK(xDouble, Math::RA2Log2)
    MACE_RALOG_BENCHMARK(xDouble, Math::RA3Log2)
    MACE_RALOG_BENCHMARK(xDouble, Math::RA4Log2)
    MACE_RALOG_BENCHMARK(xDouble, Math::RA5Log2)
    MACE_RALOG_BENCHMARK(xDouble, Math::RA6Log2)

    std::cout << "\n"
                 "================================================================\n"
                 "      log10\n"
                 "================================================================\n"
              << std::endl;

    MACE_RALOG_BENCHMARK(xFloat, std::log10)
    MACE_RALOG_BENCHMARK(xFloat, Math::RA2Log10)
    MACE_RALOG_BENCHMARK(xFloat, Math::RA3Log10)

    MACE_RALOG_BENCHMARK(xDouble, std::log10)
    MACE_RALOG_BENCHMARK(xDouble, Math::RA2Log10)
    MACE_RALOG_BENCHMARK(xDouble, Math::RA3Log10)
    MACE_RALOG_BENCHMARK(xDouble, Math::RA4Log10)
    MACE_RALOG_BENCHMARK(xDouble, Math::RA5Log10)
    MACE_RALOG_BENCHMARK(xDouble, Math::RA6Log10)

    return EXIT_SUCCESS;
}
