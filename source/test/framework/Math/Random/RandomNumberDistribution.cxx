#include "MACE/Utility/Math/Random/RandomNumberDistribution.hxx"
#include "MACE/Utility/Math/Random/Generator/MT1993732.hxx"
#include "MACE/Utility/Math/Random/Generator/PCGXSHRR6432.hxx"
#include "MACE/Utility/Math/Random/RandomNumberDistributionBase.hxx"
#include "MACE/Utility/Math/Random/Distribution/Uniform.hxx"
#include "MACE/CLHEPX/Random/OptimizedMTEngine.hxx"
#include "MACE/CLHEPX/Random/PCGEngine.hxx"

#include <iostream>
#include <random>

// namespace stdts = MACE::Compatibility::stdts;
using namespace MACE::Utility::Math::Random;

int main(int, char* argv[]) {
    Generator::PCGXSHRR6432 rng;
    // Generator::MT1993732 rng;

    using RNG = decltype(rng);

    auto x1 = 0.0/* std::stod(argv[1]) */;
    auto x2 = 1.0/* std::stod(argv[2]) */;
    auto a = x1;
    for (auto i = 0ULL; i < 2000000000ULL; ++i) {
        // do {
        //     const auto u = static_cast<decltype(a)>(1 / static_cast<long double>(RNG::Max() - RNG::Min())) *
        //                    (rng() - RNG::Min());
        //     a = x1 * (1 - u) + x2 * u;
        // } while (a <= x1 || a >= x2);
        // if (a <= x1 || a >= x2) {
        //     std::cout << a << std::endl;
        //     throw "Failed";
        // }
        a = Distribution::Uniform<double>()(rng);
    }
    Distribution::Uniform<double>().Reset();
    std::cout << a << std::endl;

    return 0;
}

static_assert(STDRandomNumberDistribution<std::uniform_int_distribution<int>>);
static_assert(STDRandomNumberDistribution<std::uniform_real_distribution<double>>);
static_assert(STDRandomNumberDistribution<std::bernoulli_distribution>);
static_assert(STDRandomNumberDistribution<std::binomial_distribution<int>>);
static_assert(STDRandomNumberDistribution<std::negative_binomial_distribution<int>>);
static_assert(STDRandomNumberDistribution<std::geometric_distribution<int>>);
static_assert(STDRandomNumberDistribution<std::poisson_distribution<int>>);
static_assert(STDRandomNumberDistribution<std::exponential_distribution<double>>);
static_assert(STDRandomNumberDistribution<std::gamma_distribution<double>>);
static_assert(STDRandomNumberDistribution<std::weibull_distribution<double>>);
static_assert(STDRandomNumberDistribution<std::extreme_value_distribution<double>>);
static_assert(STDRandomNumberDistribution<std::normal_distribution<double>>);
static_assert(STDRandomNumberDistribution<std::lognormal_distribution<double>>);
static_assert(STDRandomNumberDistribution<std::chi_squared_distribution<double>>);
static_assert(STDRandomNumberDistribution<std::cauchy_distribution<double>>);
static_assert(STDRandomNumberDistribution<std::fisher_f_distribution<double>>);
static_assert(STDRandomNumberDistribution<std::student_t_distribution<double>>);
static_assert(STDRandomNumberDistribution<std::discrete_distribution<int>>);
static_assert(STDRandomNumberDistribution<std::piecewise_constant_distribution<double>>);
static_assert(STDRandomNumberDistribution<std::piecewise_linear_distribution<double>>);
