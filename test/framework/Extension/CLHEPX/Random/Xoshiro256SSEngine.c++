#include "MACE/Extension/CLHEPX/Random/Xoshiro256SSEngine.h++"
#include "MACE/Math/Random/Distribution/Uniform.h++"
#include "MACE/Math/Random/Generator/Xoshiro256SS.h++"
#include "MACE/Utility/WallTimeStopwatch.h++"

#include "Eigen/Core"

#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>

using namespace MACE;

int main() {
    Math::Random::Xoshiro256SS xoshiro256SS(114514);
    CLHEPX::Random::Xoshiro256SSEngine xoshiro256SSX(114514);

    std::cout << "Simply generate 10 million integers:" << std::endl;

    unsigned int r;
    for (int i = 0; i < 1000; ++i) { r = xoshiro256SS(); }
    WallTimeStopwatch<> stopWatch;
    for (int i = 0; i < 10'000'000; ++i) { r = xoshiro256SS(); }
    auto time = stopWatch.MillisecondsElapsed();
    std::cout << "    CLHEPX::...::Xoshiro256SSEngine : " << time << " ms (last integer: " << r << ')' << std::endl;

    for (int i = 0; i < 1000; ++i) { r = (unsigned int)(xoshiro256SSX); }
    stopWatch.Reset();
    for (int i = 0; i < 10'000'000; ++i) { r = (unsigned int)(xoshiro256SSX); }
    time = stopWatch.MillisecondsElapsed();
    std::cout << "     Math::...::Xoshiro256SS : " << time << " ms (last integer: " << r << ')' << std::endl;

    std::cout << "2D random walk, 10 million steps:" << std::endl;
    Eigen::RowVector2d v2d = {0, 0};
    Eigen::RowVector2d delta2d;

    for (int i = 0; i < 1'000'000; ++i) {
        delta2d = {Math::Random::Uniform<double>()(xoshiro256SS),
                   Math::Random::Uniform<double>()(xoshiro256SS)};
        v2d += delta2d;
    }
    stopWatch.Reset();
    for (int i = 0; i < 10'000'000; ++i) {
        delta2d = {Math::Random::Uniform<double>()(xoshiro256SS),
                   Math::Random::Uniform<double>()(xoshiro256SS)};
        v2d += delta2d;
    }
    time = stopWatch.MillisecondsElapsed();
    std::cout << "    CLHEPX::...::Xoshiro256SSEngine : " << time << " ms (last displacement: " << std::setprecision(18) << v2d << std::setprecision(6) << ')' << std::endl;

    v2d = {0, 0};
    for (int i = 0; i < 1'000'000; ++i) {
        delta2d = {xoshiro256SSX.flat(),
                   xoshiro256SSX.flat()};
        v2d += delta2d;
    }
    stopWatch.Reset();
    for (int i = 0; i < 10'000'000; ++i) {
        delta2d = {xoshiro256SSX.flat(),
                   xoshiro256SSX.flat()};
        v2d += delta2d;
    }
    time = stopWatch.MillisecondsElapsed();
    std::cout << "     Math::...::Xoshiro256SS : " << time << " ms (last displacement: " << std::setprecision(18) << v2d << std::setprecision(6) << ')' << std::endl;

    std::cout << "3D random walk, 10 million steps:" << std::endl;
    Eigen::RowVector3d v3d = {0, 0, 0};
    Eigen::RowVector3d delta3d;

    for (int i = 0; i < 1'000'000; ++i) {
        delta3d = {Math::Random::Uniform<double>()(xoshiro256SS),
                   Math::Random::Uniform<double>()(xoshiro256SS),
                   Math::Random::Uniform<double>()(xoshiro256SS)};
        v3d += delta3d;
    }
    stopWatch.Reset();
    for (int i = 0; i < 10'000'000; ++i) {
        delta3d = {Math::Random::Uniform<double>()(xoshiro256SS),
                   Math::Random::Uniform<double>()(xoshiro256SS),
                   Math::Random::Uniform<double>()(xoshiro256SS)};
        v3d += delta3d;
    }
    time = stopWatch.MillisecondsElapsed();
    std::cout << "    CLHEPX::...::Xoshiro256SSEngine : " << time << " ms (last displacement: " << std::setprecision(18) << v3d << std::setprecision(6) << ')' << std::endl;

    v3d = {0, 0, 0};
    for (int i = 0; i < 1'000'000; ++i) {
        delta3d = {xoshiro256SSX.flat(),
                   xoshiro256SSX.flat(),
                   xoshiro256SSX.flat()};
        v3d += delta3d;
    }
    stopWatch.Reset();
    for (int i = 0; i < 10'000'000; ++i) {
        delta3d = {xoshiro256SSX.flat(),
                   xoshiro256SSX.flat(),
                   xoshiro256SSX.flat()};
        v3d += delta3d;
    }
    time = stopWatch.MillisecondsElapsed();
    std::cout << "     Math::...::Xoshiro256SS : " << time << " ms (last displacement: " << std::setprecision(18) << v3d << std::setprecision(6) << ')' << std::endl;

    std::cout << "4D random walk, 10 million steps:" << std::endl;
    Eigen::RowVector4d v4d = {0, 0, 0, 0};
    Eigen::RowVector4d delta4d;

    for (int i = 0; i < 1'000'000; ++i) {
        delta4d = {Math::Random::Uniform<double>()(xoshiro256SS),
                   Math::Random::Uniform<double>()(xoshiro256SS),
                   Math::Random::Uniform<double>()(xoshiro256SS),
                   Math::Random::Uniform<double>()(xoshiro256SS)};
        v4d += delta4d;
    }
    stopWatch.Reset();
    for (int i = 0; i < 10'000'000; ++i) {
        delta4d = {Math::Random::Uniform<double>()(xoshiro256SS),
                   Math::Random::Uniform<double>()(xoshiro256SS),
                   Math::Random::Uniform<double>()(xoshiro256SS),
                   Math::Random::Uniform<double>()(xoshiro256SS)};
        v4d += delta4d;
    }
    time = stopWatch.MillisecondsElapsed();
    std::cout << "    CLHEPX::...::Xoshiro256SSEngine : " << time << " ms (last displacement: " << std::setprecision(18) << v4d << std::setprecision(6) << ')' << std::endl;

    v4d = {0, 0, 0, 0};
    for (int i = 0; i < 1'000'000; ++i) {
        delta4d = {xoshiro256SSX.flat(),
                   xoshiro256SSX.flat(),
                   xoshiro256SSX.flat(),
                   xoshiro256SSX.flat()};
        v4d += delta4d;
    }
    stopWatch.Reset();
    for (int i = 0; i < 10'000'000; ++i) {
        delta4d = {xoshiro256SSX.flat(),
                   xoshiro256SSX.flat(),
                   xoshiro256SSX.flat(),
                   xoshiro256SSX.flat()};
        v4d += delta4d;
    }
    time = stopWatch.MillisecondsElapsed();
    std::cout << "     Math::...::Xoshiro256SS : " << time << " ms (last displacement: " << std::setprecision(18) << v4d << std::setprecision(6) << ')' << std::endl;

    return 0;
}
