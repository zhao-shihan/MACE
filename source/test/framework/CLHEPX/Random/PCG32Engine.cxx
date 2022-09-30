#include "MACE/CLHEPX/Random/PCG32Engine.hxx"
#include "MACE/Math/Random/Distribution/Uniform.hxx"
#include "MACE/Math/Random/Generator/PCGXSHRR6432.hxx"
#include "MACE/Utility/WallTimer.hxx"

#include "Eigen/Core"

#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>

int main() {
    using namespace MACE::Math::Random;
    using MACE::Utility::WallTimer;

    Generator::PCGXSHRR6432 pcg32(114514);
    MACE::CLHEPX::Random::PCG32Engine pcg32x(114514);

    std::cout << "Simply generate 10 million integers:" << std::endl;

    unsigned int r;
    for (int i = 0; i < 1000; ++i) { r = pcg32(); }
    WallTimer<double> timer;
    for (int i = 0; i < 10'000'000; ++i) { r = pcg32(); }
    auto time = timer.MillisecondsElapsed();
    std::cout << "    CLHEPX::...::PCG32Engine : " << time << " ms (last integer: " << r << ')' << std::endl;

    for (int i = 0; i < 1000; ++i) { r = (unsigned int)(pcg32x); }
    timer.Reset();
    for (int i = 0; i < 10'000'000; ++i) { r = (unsigned int)(pcg32x); }
    time = timer.MillisecondsElapsed();
    std::cout << "     Math::...::PCGXSHRR6432 : " << time << " ms (last integer: " << r << ')' << std::endl;

    std::cout << "2D random walk, 10 million steps:" << std::endl;
    Eigen::RowVector2d v2d = {0, 0};
    Eigen::RowVector2d delta2d;

    for (int i = 0; i < 1'000'000; ++i) {
        delta2d = {Distribution::Uniform<double>()(pcg32),
                   Distribution::Uniform<double>()(pcg32)};
        v2d += delta2d;
    }
    timer.Reset();
    for (int i = 0; i < 10'000'000; ++i) {
        delta2d = {Distribution::Uniform<double>()(pcg32),
                   Distribution::Uniform<double>()(pcg32)};
        v2d += delta2d;
    }
    time = timer.MillisecondsElapsed();
    std::cout << "    CLHEPX::...::PCG32Engine : " << time << " ms (last displacement: " << std::setprecision(18) << v2d << std::setprecision(6) << ')' << std::endl;

    v2d = {0, 0};
    for (int i = 0; i < 1'000'000; ++i) {
        delta2d = {pcg32x.flat(),
                   pcg32x.flat()};
        v2d += delta2d;
    }
    timer.Reset();
    for (int i = 0; i < 10'000'000; ++i) {
        delta2d = {pcg32x.flat(),
                   pcg32x.flat()};
        v2d += delta2d;
    }
    time = timer.MillisecondsElapsed();
    std::cout << "     Math::...::PCGXSHRR6432 : " << time << " ms (last displacement: " << std::setprecision(18) << v2d << std::setprecision(6) << ')' << std::endl;

    std::cout << "3D random walk, 10 million steps:" << std::endl;
    Eigen::RowVector3d v3d = {0, 0, 0};
    Eigen::RowVector3d delta3d;

    for (int i = 0; i < 1'000'000; ++i) {
        delta3d = {Distribution::Uniform<double>()(pcg32),
                   Distribution::Uniform<double>()(pcg32),
                   Distribution::Uniform<double>()(pcg32)};
        v3d += delta3d;
    }
    timer.Reset();
    for (int i = 0; i < 10'000'000; ++i) {
        delta3d = {Distribution::Uniform<double>()(pcg32),
                   Distribution::Uniform<double>()(pcg32),
                   Distribution::Uniform<double>()(pcg32)};
        v3d += delta3d;
    }
    time = timer.MillisecondsElapsed();
    std::cout << "    CLHEPX::...::PCG32Engine : " << time << " ms (last displacement: " << std::setprecision(18) << v3d << std::setprecision(6) << ')' << std::endl;

    v3d = {0, 0, 0};
    for (int i = 0; i < 1'000'000; ++i) {
        delta3d = {pcg32x.flat(),
                   pcg32x.flat(),
                   pcg32x.flat()};
        v3d += delta3d;
    }
    timer.Reset();
    for (int i = 0; i < 10'000'000; ++i) {
        delta3d = {pcg32x.flat(),
                   pcg32x.flat(),
                   pcg32x.flat()};
        v3d += delta3d;
    }
    time = timer.MillisecondsElapsed();
    std::cout << "     Math::...::PCGXSHRR6432 : " << time << " ms (last displacement: " << std::setprecision(18) << v3d << std::setprecision(6) << ')' << std::endl;

    std::cout << "4D random walk, 10 million steps:" << std::endl;
    Eigen::RowVector4d v4d = {0, 0, 0, 0};
    Eigen::RowVector4d delta4d;

    for (int i = 0; i < 1'000'000; ++i) {
        delta4d = {Distribution::Uniform<double>()(pcg32),
                   Distribution::Uniform<double>()(pcg32),
                   Distribution::Uniform<double>()(pcg32),
                   Distribution::Uniform<double>()(pcg32)};
        v4d += delta4d;
    }
    timer.Reset();
    for (int i = 0; i < 10'000'000; ++i) {
        delta4d = {Distribution::Uniform<double>()(pcg32),
                   Distribution::Uniform<double>()(pcg32),
                   Distribution::Uniform<double>()(pcg32),
                   Distribution::Uniform<double>()(pcg32)};
        v4d += delta4d;
    }
    time = timer.MillisecondsElapsed();
    std::cout << "    CLHEPX::...::PCG32Engine : " << time << " ms (last displacement: " << std::setprecision(18) << v4d << std::setprecision(6) << ')' << std::endl;

    v4d = {0, 0, 0, 0};
    for (int i = 0; i < 1'000'000; ++i) {
        delta4d = {pcg32x.flat(),
                   pcg32x.flat(),
                   pcg32x.flat(),
                   pcg32x.flat()};
        v4d += delta4d;
    }
    timer.Reset();
    for (int i = 0; i < 10'000'000; ++i) {
        delta4d = {pcg32x.flat(),
                   pcg32x.flat(),
                   pcg32x.flat(),
                   pcg32x.flat()};
        v4d += delta4d;
    }
    time = timer.MillisecondsElapsed();
    std::cout << "     Math::...::PCGXSHRR6432 : " << time << " ms (last displacement: " << std::setprecision(18) << v4d << std::setprecision(6) << ')' << std::endl;

    return 0;
}
