#include "MACE/Math/IntegerPower.hxx"

#include <chrono>
#include <complex>
#include <iostream>
#include <random>
#include <type_traits>

using namespace MACE::Math;
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
        dummy = T(common + 1e-5 * i); // "+i": prevent optimization
    }
    end = steady_clock::now();
    // benchmark
    begin = steady_clock::now();
    for (int i = 0; i < benchmarkCycle; ++i) {
        dummy = T(common + 1e-5 * i);
    }
    end = steady_clock::now();

    std::cout << "Background: " << duration<double, std::milli>(end - begin).count() << " ms\t\t";

    // benchmark PowZ
    // warm up
    begin = steady_clock::now();
    for (int i = 0; i < warmUpCycle; ++i) {
        dummy = PowZ<N>(T(common + 1e-5 * i));
    }
    end = steady_clock::now();
    // benchmark
    begin = steady_clock::now();
    for (int i = 0; i < benchmarkCycle; ++i) {
        dummy = PowZ<N>(T(common + 1e-5 * i));
    }
    end = steady_clock::now();

    const duration<double, std::milli> powIntTime = end - begin;
    std::cout << "PowZ<" << N << ">(x):\t" << powIntTime.count() << " ms\t";

    // benchmark std::pow
    // warm up
    begin = steady_clock::now();
    for (int i = 0; i < warmUpCycle; ++i) {
        dummy = std::pow(T(common + 1e-5 * i), N);
    }
    end = steady_clock::now();
    // benchmark
    begin = steady_clock::now();
    for (int i = 0; i < benchmarkCycle; ++i) {
        dummy = std::pow(T(common + 1e-5 * i), N);
    }
    end = steady_clock::now();

    const duration<double, std::milli> powTime = end - begin;
    std::cout << "pow(x, " << N << "):\t" << powTime.count() << " ms\tspeedup = " << powTime.count() / powIntTime.count() << std::endl;

    return dummy; // surpress "unused-but-set"
}

int main(int argc, char* argv[]) {
    const auto common = (argc == 1) ? 1 : std::stoi(argv[1]);

#define MACE_BENCHMARK_POWZ(Type)                       \
    std::cout << #Type << ", power zero:" << std::endl; \
    BenchmarkPowZ<Type, 0>(common);                     \
    std::cout << #Type << ", power 4^n:" << std::endl;  \
    BenchmarkPowZ<Type, PowI<4, 0>()>(common);          \
    BenchmarkPowZ<Type, PowI<4, 1>()>(common);          \
    BenchmarkPowZ<Type, PowI<4, 2>()>(common);          \
    BenchmarkPowZ<Type, PowI<4, 3>()>(common);          \
    BenchmarkPowZ<Type, PowI<4, 4>()>(common);          \
    BenchmarkPowZ<Type, PowI<4, 5>()>(common);          \
    BenchmarkPowZ<Type, PowI<4, 6>()>(common);          \
    BenchmarkPowZ<Type, PowI<4, 7>()>(common);          \
    BenchmarkPowZ<Type, PowI<4, 8>()>(common);          \
    BenchmarkPowZ<Type, PowI<4, 9>()>(common);          \
    BenchmarkPowZ<Type, PowI<4, 10>()>(common);         \
    BenchmarkPowZ<Type, PowI<4, 11>()>(common);         \
    BenchmarkPowZ<Type, PowI<4, 12>()>(common);         \
    BenchmarkPowZ<Type, PowI<4, 13>()>(common);         \
    BenchmarkPowZ<Type, PowI<4, 14>()>(common);         \
    BenchmarkPowZ<Type, PowI<4, 15>()>(common);         \
    std::cout << #Type << ", power -4^n:" << std::endl; \
    BenchmarkPowZ<Type, -PowI<4, 0>()>(common);         \
    BenchmarkPowZ<Type, -PowI<4, 1>()>(common);         \
    BenchmarkPowZ<Type, -PowI<4, 2>()>(common);         \
    BenchmarkPowZ<Type, -PowI<4, 3>()>(common);         \
    BenchmarkPowZ<Type, -PowI<4, 4>()>(common);         \
    BenchmarkPowZ<Type, -PowI<4, 5>()>(common);         \
    BenchmarkPowZ<Type, -PowI<4, 6>()>(common);         \
    BenchmarkPowZ<Type, -PowI<4, 7>()>(common);         \
    BenchmarkPowZ<Type, -PowI<4, 8>()>(common);         \
    BenchmarkPowZ<Type, -PowI<4, 9>()>(common);         \
    BenchmarkPowZ<Type, -PowI<4, 10>()>(common);        \
    BenchmarkPowZ<Type, -PowI<4, 11>()>(common);        \
    BenchmarkPowZ<Type, -PowI<4, 12>()>(common);        \
    BenchmarkPowZ<Type, -PowI<4, 13>()>(common);        \
    BenchmarkPowZ<Type, -PowI<4, 14>()>(common);        \
    BenchmarkPowZ<Type, -PowI<4, 15>()>(common);        \
    std::cout << #Type << ", power 7^n:" << std::endl;  \
    BenchmarkPowZ<Type, PowI<7, 0>()>(common);          \
    BenchmarkPowZ<Type, PowI<7, 1>()>(common);          \
    BenchmarkPowZ<Type, PowI<7, 2>()>(common);          \
    BenchmarkPowZ<Type, PowI<7, 3>()>(common);          \
    BenchmarkPowZ<Type, PowI<7, 4>()>(common);          \
    BenchmarkPowZ<Type, PowI<7, 5>()>(common);          \
    BenchmarkPowZ<Type, PowI<7, 6>()>(common);          \
    BenchmarkPowZ<Type, PowI<7, 7>()>(common);          \
    BenchmarkPowZ<Type, PowI<7, 8>()>(common);          \
    BenchmarkPowZ<Type, PowI<7, 9>()>(common);          \
    BenchmarkPowZ<Type, PowI<7, 10>()>(common);         \
    BenchmarkPowZ<Type, PowI<7, 11>()>(common);         \
    std::cout << #Type << ", power -7^n:" << std::endl; \
    BenchmarkPowZ<Type, -PowI<7, 0>()>(common);         \
    BenchmarkPowZ<Type, -PowI<7, 1>()>(common);         \
    BenchmarkPowZ<Type, -PowI<7, 2>()>(common);         \
    BenchmarkPowZ<Type, -PowI<7, 3>()>(common);         \
    BenchmarkPowZ<Type, -PowI<7, 4>()>(common);         \
    BenchmarkPowZ<Type, -PowI<7, 5>()>(common);         \
    BenchmarkPowZ<Type, -PowI<7, 6>()>(common);         \
    BenchmarkPowZ<Type, -PowI<7, 7>()>(common);         \
    BenchmarkPowZ<Type, -PowI<7, 8>()>(common);         \
    BenchmarkPowZ<Type, -PowI<7, 9>()>(common);         \
    BenchmarkPowZ<Type, -PowI<7, 10>()>(common);        \
    BenchmarkPowZ<Type, -PowI<7, 11>()>(common);

    // MACE_BENCHMARK_POWZ(char);
    // MACE_BENCHMARK_POWZ(signed char);
    // MACE_BENCHMARK_POWZ(unsigned char);
    // MACE_BENCHMARK_POWZ(char8_t);
    // MACE_BENCHMARK_POWZ(char16_t);
    // MACE_BENCHMARK_POWZ(char32_t);
    // MACE_BENCHMARK_POWZ(wchar_t);
    // MACE_BENCHMARK_POWZ(short);
    // MACE_BENCHMARK_POWZ(unsigned short);
    // MACE_BENCHMARK_POWZ(int);
    // MACE_BENCHMARK_POWZ(unsigned int);
    // MACE_BENCHMARK_POWZ(long);
    // MACE_BENCHMARK_POWZ(unsigned long);
    // MACE_BENCHMARK_POWZ(long long);
    // MACE_BENCHMARK_POWZ(unsigned long long);
    MACE_BENCHMARK_POWZ(float);
    MACE_BENCHMARK_POWZ(double);
    MACE_BENCHMARK_POWZ(long double);

#undef MACE_BENCHMARK_POWZ

    return EXIT_SUCCESS;
}
