#include "MACE/Utility/IntegerPower.hxx"

#include <chrono>
#include <complex>
#include <iostream>
#include <random>
#include <type_traits>

using namespace MACE::Utility;
using namespace std::chrono;
using std::complex;

template<typename T, int N>
T BenchmarkPowZ(T common) {
    constexpr int warmUpCycle = 100000;
    constexpr int benchmarkCycle = 100000;

    volatile T dummy; // "volatile": prevent optimization
    steady_clock::time_point begin;
    steady_clock::time_point end;

    // background
    // warm up
    begin = steady_clock::now();
    for (int i = 0; i < warmUpCycle; ++i) {
        dummy = common + i; // "+i": prevent optimization
    }
    end = steady_clock::now();
    // benchmark
    begin = steady_clock::now();
    for (int i = 0; i < benchmarkCycle; ++i) {
        dummy = common + i;
    }
    end = steady_clock::now();

    std::cout << "Background: " << duration<double, std::milli>(end - begin).count() << " ms\t\t";

    // benchmark PowZ
    // warm up
    begin = steady_clock::now();
    for (int i = 0; i < warmUpCycle; ++i) {
        dummy = PowZ<N>(common + i);
    }
    end = steady_clock::now();
    // benchmark
    begin = steady_clock::now();
    for (int i = 0; i < benchmarkCycle; ++i) {
        dummy = PowZ<N>(common + i);
    }
    end = steady_clock::now();

    const duration<double, std::milli> powIntTime = end - begin;
    std::cout << "PowZ<" << N << ">(x):\t" << powIntTime.count() << " ms\t";

    // benchmark std::pow
    // warm up
    begin = steady_clock::now();
    for (int i = 0; i < warmUpCycle; ++i) {
        dummy = std::pow(common + i, N);
    }
    end = steady_clock::now();
    // benchmark
    begin = steady_clock::now();
    for (int i = 0; i < benchmarkCycle; ++i) {
        dummy = std::pow(common + i, N);
    }
    end = steady_clock::now();

    const duration<double, std::milli> powTime = end - begin;
    std::cout << "pow(x, " << N << "):\t" << powTime.count() << " ms\tspeedup = " << powTime.count() / powIntTime.count() << std::endl;

    return dummy; // surpress "unused-but-set"
}

int main(int argc, char* argv[]) {
    const auto common = (argc == 1) ? 2 : std::stoi(argv[1]);

#define MACE_BENCHMARK_POWZ_INT(Type)                       \
    std::cout << #Type << ", power zero:" << std::endl;     \
    BenchmarkPowZ<Type, 0>(common);                         \
    std::cout << #Type << ", positive power:" << std::endl; \
    BenchmarkPowZ<Type, 1>(common);                         \
    BenchmarkPowZ<Type, 2>(common);                         \
    BenchmarkPowZ<Type, 3>(common);                         \
    BenchmarkPowZ<Type, 4>(common);                         \
    BenchmarkPowZ<Type, 5>(common);                         \
    BenchmarkPowZ<Type, 6>(common);                         \
    BenchmarkPowZ<Type, 7>(common);                         \
    BenchmarkPowZ<Type, 8>(common);                         \
    BenchmarkPowZ<Type, 9>(common);                         \
    BenchmarkPowZ<Type, 10>(common);                        \
    BenchmarkPowZ<Type, 20>(common);                        \
    BenchmarkPowZ<Type, 30>(common);                        \
    BenchmarkPowZ<Type, 40>(common);                        \
    BenchmarkPowZ<Type, 50>(common);                        \
    BenchmarkPowZ<Type, 60>(common);                        \
    BenchmarkPowZ<Type, 70>(common);                        \
    BenchmarkPowZ<Type, 80>(common);                        \
    BenchmarkPowZ<Type, 90>(common);                        \
    BenchmarkPowZ<Type, 100>(common);                       \
    BenchmarkPowZ<Type, 200>(common);                       \
    BenchmarkPowZ<Type, 300>(common);                       \
    BenchmarkPowZ<Type, 400>(common);                       \
    BenchmarkPowZ<Type, 500>(common)

#define MACE_BENCHMARK_POWZ_FP(Type)                        \
    MACE_BENCHMARK_POWZ_INT(Type);                          \
    std::cout << #Type << ", negative power:" << std::endl; \
    BenchmarkPowZ<Type, -1>(common);                        \
    BenchmarkPowZ<Type, -2>(common);                        \
    BenchmarkPowZ<Type, -3>(common);                        \
    BenchmarkPowZ<Type, -4>(common);                        \
    BenchmarkPowZ<Type, -5>(common);                        \
    BenchmarkPowZ<Type, -6>(common);                        \
    BenchmarkPowZ<Type, -7>(common);                        \
    BenchmarkPowZ<Type, -8>(common);                        \
    BenchmarkPowZ<Type, -9>(common);                        \
    BenchmarkPowZ<Type, -10>(common);                       \
    BenchmarkPowZ<Type, -20>(common);                       \
    BenchmarkPowZ<Type, -30>(common);                       \
    BenchmarkPowZ<Type, -40>(common);                       \
    BenchmarkPowZ<Type, -50>(common);                       \
    BenchmarkPowZ<Type, -60>(common);                       \
    BenchmarkPowZ<Type, -70>(common);                       \
    BenchmarkPowZ<Type, -80>(common);                       \
    BenchmarkPowZ<Type, -90>(common);                       \
    BenchmarkPowZ<Type, -100>(common);                      \
    BenchmarkPowZ<Type, -200>(common);                      \
    BenchmarkPowZ<Type, -300>(common);                      \
    BenchmarkPowZ<Type, -400>(common);                      \
    BenchmarkPowZ<Type, -500>(common)

    MACE_BENCHMARK_POWZ_INT(char);
    MACE_BENCHMARK_POWZ_INT(signed char);
    MACE_BENCHMARK_POWZ_INT(unsigned char);
    MACE_BENCHMARK_POWZ_INT(char8_t);
    MACE_BENCHMARK_POWZ_INT(char16_t);
    MACE_BENCHMARK_POWZ_INT(char32_t);
    MACE_BENCHMARK_POWZ_INT(wchar_t);
    MACE_BENCHMARK_POWZ_INT(short);
    MACE_BENCHMARK_POWZ_INT(unsigned short);
    MACE_BENCHMARK_POWZ_INT(int);
    MACE_BENCHMARK_POWZ_INT(unsigned int);
    MACE_BENCHMARK_POWZ_INT(long);
    MACE_BENCHMARK_POWZ_INT(unsigned long);
    MACE_BENCHMARK_POWZ_INT(long long);
    MACE_BENCHMARK_POWZ_INT(unsigned long long);
    MACE_BENCHMARK_POWZ_FP(float);
    MACE_BENCHMARK_POWZ_FP(double);
    MACE_BENCHMARK_POWZ_FP(long double);

#undef MACE_BENCHMARK_POWZ_INT
#undef MACE_BENCHMARK_POWZ_FP

    return EXIT_SUCCESS;
}
