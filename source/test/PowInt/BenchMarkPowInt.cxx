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
void BenchmarkPowInt(uint_fast32_t seed) {
    std::mt19937 randEng(seed);

    auto GetTrans = [] {
        if constexpr (std::is_floating_point_v<T>) {
            return std::uniform_real_distribution<T>(-2, 2);
        } else if constexpr (std::is_integral_v<T>) {
            return std::uniform_int_distribution<T>();
        }
    };
    auto Trans = GetTrans();

    constexpr int warmUpCycle = 10000;
    constexpr int benchmarkCycle = 100000;

    std::vector<T> dummy;
    dummy.reserve(benchmarkCycle);
    steady_clock::time_point begin, end;

    // background
    // warm up
    begin = steady_clock::now();
    for (int i = 0; i < warmUpCycle; ++i) {
        dummy.emplace_back(Trans(randEng));
    }
    end = steady_clock::now();
    dummy.clear();
    // benchmark
    begin = steady_clock::now();
    for (int i = 0; i < benchmarkCycle; ++i) {
        dummy.emplace_back(Trans(randEng));
    }
    end = steady_clock::now();
    dummy.clear();

    std::cout << "Background: " << duration<double, std::milli>(end - begin).count() << " ms\t";

    // benchmark PowInt
    // warm up
    begin = steady_clock::now();
    for (int i = 0; i < warmUpCycle; ++i) {
        dummy.emplace_back(PowInt<N>(Trans(randEng)));
    }
    end = steady_clock::now();
    dummy.clear();
    // benchmark
    begin = steady_clock::now();
    for (int i = 0; i < benchmarkCycle; ++i) {
        dummy.emplace_back(PowInt<N>(Trans(randEng)));
    }
    end = steady_clock::now();
    dummy.clear();

    const duration<double, std::milli> powIntTime = end - begin;
    std::cout << "PowInt<" << N << ">(x):   \t" << powIntTime.count() << " ms\t";

    // benchmark std::pow
    // warm up
    begin = steady_clock::now();
    for (int i = 0; i < warmUpCycle; ++i) {
        dummy.emplace_back(std::pow(Trans(randEng), N));
    }
    end = steady_clock::now();
    dummy.clear();
    // benchmark
    begin = steady_clock::now();
    for (int i = 0; i < benchmarkCycle; ++i) {
        dummy.emplace_back(std::pow(Trans(randEng), N));
    }
    end = steady_clock::now();
    dummy.clear();

    const duration<double, std::milli> powTime = end - begin;
    std::cout << "std::pow(x, " << N << "): \t" << powTime.count() << " ms\tspeedup = " << powTime.count() / powIntTime.count() << std::endl;
}

int main(int argc, char* argv[]) {
    uint_fast32_t seed = (argc == 1) ? 4357 : std::stoull(argv[1]);

#define MACE_BENCHMARK_POWINT_INT(Type)                     \
    std::cout << #Type << ", power zero:" << std::endl;     \
    BenchmarkPowInt<Type, 0>(seed);                         \
    std::cout << #Type << ", positive power:" << std::endl; \
    BenchmarkPowInt<Type, 1>(seed);                         \
    BenchmarkPowInt<Type, 2>(seed);                         \
    BenchmarkPowInt<Type, 3>(seed);                         \
    BenchmarkPowInt<Type, 4>(seed);                         \
    BenchmarkPowInt<Type, 5>(seed);                         \
    BenchmarkPowInt<Type, 6>(seed);                         \
    BenchmarkPowInt<Type, 7>(seed);                         \
    BenchmarkPowInt<Type, 8>(seed);                         \
    BenchmarkPowInt<Type, 9>(seed);                         \
    BenchmarkPowInt<Type, 10>(seed);                        \
    BenchmarkPowInt<Type, 20>(seed);                        \
    BenchmarkPowInt<Type, 30>(seed);                        \
    BenchmarkPowInt<Type, 40>(seed);                        \
    BenchmarkPowInt<Type, 50>(seed);                        \
    BenchmarkPowInt<Type, 60>(seed);                        \
    BenchmarkPowInt<Type, 70>(seed);                        \
    BenchmarkPowInt<Type, 80>(seed);                        \
    BenchmarkPowInt<Type, 90>(seed);                        \
    BenchmarkPowInt<Type, 100>(seed);                       \
    BenchmarkPowInt<Type, 200>(seed);                       \
    BenchmarkPowInt<Type, 300>(seed);                       \
    BenchmarkPowInt<Type, 400>(seed);                       \
    BenchmarkPowInt<Type, 500>(seed)

#define MACE_BENCHMARK_POWINT_FP(Type)                      \
    MACE_BENCHMARK_POWINT_INT(Type);                        \
    std::cout << #Type << ", negative power:" << std::endl; \
    BenchmarkPowInt<Type, -1>(seed);                        \
    BenchmarkPowInt<Type, -2>(seed);                        \
    BenchmarkPowInt<Type, -3>(seed);                        \
    BenchmarkPowInt<Type, -4>(seed);                        \
    BenchmarkPowInt<Type, -5>(seed);                        \
    BenchmarkPowInt<Type, -6>(seed);                        \
    BenchmarkPowInt<Type, -7>(seed);                        \
    BenchmarkPowInt<Type, -8>(seed);                        \
    BenchmarkPowInt<Type, -9>(seed);                        \
    BenchmarkPowInt<Type, -10>(seed);                       \
    BenchmarkPowInt<Type, -20>(seed);                       \
    BenchmarkPowInt<Type, -30>(seed);                       \
    BenchmarkPowInt<Type, -40>(seed);                       \
    BenchmarkPowInt<Type, -50>(seed);                       \
    BenchmarkPowInt<Type, -60>(seed);                       \
    BenchmarkPowInt<Type, -70>(seed);                       \
    BenchmarkPowInt<Type, -80>(seed);                       \
    BenchmarkPowInt<Type, -90>(seed);                       \
    BenchmarkPowInt<Type, -100>(seed);                      \
    BenchmarkPowInt<Type, -200>(seed);                      \
    BenchmarkPowInt<Type, -300>(seed);                      \
    BenchmarkPowInt<Type, -400>(seed);                      \
    BenchmarkPowInt<Type, -500>(seed)

    MACE_BENCHMARK_POWINT_INT(char);
    MACE_BENCHMARK_POWINT_INT(unsigned char);
    MACE_BENCHMARK_POWINT_INT(wchar_t);
    MACE_BENCHMARK_POWINT_INT(char16_t);
    MACE_BENCHMARK_POWINT_INT(char32_t);
    MACE_BENCHMARK_POWINT_INT(short);
    MACE_BENCHMARK_POWINT_INT(unsigned short);
    MACE_BENCHMARK_POWINT_INT(int);
    MACE_BENCHMARK_POWINT_INT(unsigned int);
    MACE_BENCHMARK_POWINT_INT(long);
    MACE_BENCHMARK_POWINT_INT(unsigned long);
    MACE_BENCHMARK_POWINT_INT(long long);
    MACE_BENCHMARK_POWINT_INT(unsigned long long);
    MACE_BENCHMARK_POWINT_FP(float);
    MACE_BENCHMARK_POWINT_FP(double);
    MACE_BENCHMARK_POWINT_FP(long double);

#undef MACE_BENCHMARK_POWINT_INT
#undef MACE_BENCHMARK_POWINT_FP

    return EXIT_SUCCESS;
}
