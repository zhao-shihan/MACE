#include "MACE/Math/IntegerPower.h++"

#include <chrono>
#include <complex>
#include <iostream>
#include <random>
#include <type_traits>

using namespace MACE::Math;
using namespace std::chrono;
using std::complex;

template<typename T, int N>
T BenchmarkPowRZ(T common) {
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

    // benchmark Pow
    // warm up
    begin = steady_clock::now();
    for (int i = 0; i < warmUpCycle; ++i) {
        dummy = Pow<N>(T(common + 1e-5 * i));
    }
    end = steady_clock::now();
    // benchmark
    begin = steady_clock::now();
    for (int i = 0; i < benchmarkCycle; ++i) {
        dummy = Pow<N>(T(common + 1e-5 * i));
    }
    end = steady_clock::now();

    const duration<double, std::milli> powIntTime = end - begin;
    std::cout << "Pow<" << N << ">(x):\t" << powIntTime.count() << " ms\t";

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

#define MACE_BENCHMARK_POWRZ(Type)                      \
    std::cout << #Type << ", power zero:" << std::endl; \
    BenchmarkPowRZ<Type, 0>(common);                    \
    std::cout << #Type << ", power 4^n:" << std::endl;  \
    BenchmarkPowRZ<Type, IPow<4>(0)>(common);          \
    BenchmarkPowRZ<Type, IPow<4>(1)>(common);          \
    BenchmarkPowRZ<Type, IPow<4>(2)>(common);          \
    BenchmarkPowRZ<Type, IPow<4>(3)>(common);          \
    BenchmarkPowRZ<Type, IPow<4>(4)>(common);          \
    BenchmarkPowRZ<Type, IPow<4>(5)>(common);          \
    BenchmarkPowRZ<Type, IPow<4>(6)>(common);          \
    BenchmarkPowRZ<Type, IPow<4>(7)>(common);          \
    BenchmarkPowRZ<Type, IPow<4>(8)>(common);          \
    BenchmarkPowRZ<Type, IPow<4>(9)>(common);          \
    BenchmarkPowRZ<Type, IPow<4>(10)>(common);         \
    BenchmarkPowRZ<Type, IPow<4>(11)>(common);         \
    BenchmarkPowRZ<Type, IPow<4>(12)>(common);         \
    BenchmarkPowRZ<Type, IPow<4>(13)>(common);         \
    BenchmarkPowRZ<Type, IPow<4>(14)>(common);         \
    BenchmarkPowRZ<Type, IPow<4>(15)>(common);         \
    std::cout << #Type << ", power -4^n:" << std::endl; \
    BenchmarkPowRZ<Type, -IPow<4>(0)>(common);         \
    BenchmarkPowRZ<Type, -IPow<4>(1)>(common);         \
    BenchmarkPowRZ<Type, -IPow<4>(2)>(common);         \
    BenchmarkPowRZ<Type, -IPow<4>(3)>(common);         \
    BenchmarkPowRZ<Type, -IPow<4>(4)>(common);         \
    BenchmarkPowRZ<Type, -IPow<4>(5)>(common);         \
    BenchmarkPowRZ<Type, -IPow<4>(6)>(common);         \
    BenchmarkPowRZ<Type, -IPow<4>(7)>(common);         \
    BenchmarkPowRZ<Type, -IPow<4>(8)>(common);         \
    BenchmarkPowRZ<Type, -IPow<4>(9)>(common);         \
    BenchmarkPowRZ<Type, -IPow<4>(10)>(common);        \
    BenchmarkPowRZ<Type, -IPow<4>(11)>(common);        \
    BenchmarkPowRZ<Type, -IPow<4>(12)>(common);        \
    BenchmarkPowRZ<Type, -IPow<4>(13)>(common);        \
    BenchmarkPowRZ<Type, -IPow<4>(14)>(common);        \
    BenchmarkPowRZ<Type, -IPow<4>(15)>(common);        \
    std::cout << #Type << ", power 7^n:" << std::endl;  \
    BenchmarkPowRZ<Type, IPow<7>(0)>(common);          \
    BenchmarkPowRZ<Type, IPow<7>(1)>(common);          \
    BenchmarkPowRZ<Type, IPow<7>(2)>(common);          \
    BenchmarkPowRZ<Type, IPow<7>(3)>(common);          \
    BenchmarkPowRZ<Type, IPow<7>(4)>(common);          \
    BenchmarkPowRZ<Type, IPow<7>(5)>(common);          \
    BenchmarkPowRZ<Type, IPow<7>(6)>(common);          \
    BenchmarkPowRZ<Type, IPow<7>(7)>(common);          \
    BenchmarkPowRZ<Type, IPow<7>(8)>(common);          \
    BenchmarkPowRZ<Type, IPow<7>(9)>(common);          \
    BenchmarkPowRZ<Type, IPow<7>(10)>(common);         \
    BenchmarkPowRZ<Type, IPow<7>(11)>(common);         \
    std::cout << #Type << ", power -7^n:" << std::endl; \
    BenchmarkPowRZ<Type, -IPow<7>(0)>(common);         \
    BenchmarkPowRZ<Type, -IPow<7>(1)>(common);         \
    BenchmarkPowRZ<Type, -IPow<7>(2)>(common);         \
    BenchmarkPowRZ<Type, -IPow<7>(3)>(common);         \
    BenchmarkPowRZ<Type, -IPow<7>(4)>(common);         \
    BenchmarkPowRZ<Type, -IPow<7>(5)>(common);         \
    BenchmarkPowRZ<Type, -IPow<7>(6)>(common);         \
    BenchmarkPowRZ<Type, -IPow<7>(7)>(common);         \
    BenchmarkPowRZ<Type, -IPow<7>(8)>(common);         \
    BenchmarkPowRZ<Type, -IPow<7>(9)>(common);         \
    BenchmarkPowRZ<Type, -IPow<7>(10)>(common);        \
    BenchmarkPowRZ<Type, -IPow<7>(11)>(common);

    // MACE_BENCHMARK_POWRZ(char);
    // MACE_BENCHMARK_POWRZ(signed char);
    // MACE_BENCHMARK_POWRZ(unsigned char);
    // MACE_BENCHMARK_POWRZ(char8_t);
    // MACE_BENCHMARK_POWRZ(char16_t);
    // MACE_BENCHMARK_POWRZ(char32_t);
    // MACE_BENCHMARK_POWRZ(wchar_t);
    // MACE_BENCHMARK_POWRZ(short);
    // MACE_BENCHMARK_POWRZ(unsigned short);
    // MACE_BENCHMARK_POWRZ(int);
    // MACE_BENCHMARK_POWRZ(unsigned int);
    // MACE_BENCHMARK_POWRZ(long);
    // MACE_BENCHMARK_POWRZ(unsigned long);
    // MACE_BENCHMARK_POWRZ(long long);
    // MACE_BENCHMARK_POWRZ(unsigned long long);
    MACE_BENCHMARK_POWRZ(float);
    MACE_BENCHMARK_POWRZ(double);
    MACE_BENCHMARK_POWRZ(long double);

#undef MACE_BENCHMARK_POWRZ

    return EXIT_SUCCESS;
}
