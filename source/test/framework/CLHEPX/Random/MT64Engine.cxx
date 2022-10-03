#include "MACE/CLHEPX/Random/MT64Engine.hxx"
#include "MACE/Math/Random/Distribution/Uniform.hxx"
#include "MACE/Math/Random/Generator/MT1993764.hxx"
#include "MACE/Utility/WallTimer.hxx"

#include "Eigen/Core"

#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>

int main() {
    using namespace MACE::Math::Random;
    using MACE::Utility::WallTimer;

    Generator::MT1993764 mt64(114514);
    MACE::CLHEPX::Random::MT64Engine mt64x(114514);

    std::cout << "Simply generate 10 million integers:" << std::endl;

    unsigned int r;
    for (int i = 0; i < 1000; ++i) { r = mt64(); }
    WallTimer<> timer;
    for (int i = 0; i < 10'000'000; ++i) { r = mt64(); }
    auto time = timer.MillisecondsElapsed();
    std::cout << "    CLHEPX::...::MT64Engine : " << time << " ms (last integer: " << r << ')' << std::endl;

    for (int i = 0; i < 1000; ++i) { r = (unsigned int)(mt64x); }
    timer.Reset();
    for (int i = 0; i < 10'000'000; ++i) { r = (unsigned int)(mt64x); }
    time = timer.MillisecondsElapsed();
    std::cout << "       Math::...::MT1993764 : " << time << " ms (last integer: " << r << ')' << std::endl;

    std::cout << "2D random walk, 10 million steps:" << std::endl;
    Eigen::RowVector2d v2d = {0, 0};
    Eigen::RowVector2d delta2d;

    for (int i = 0; i < 1'000'000; ++i) {
        delta2d = {Distribution::Uniform<double>()(mt64),
                   Distribution::Uniform<double>()(mt64)};
        v2d += delta2d;
    }
    timer.Reset();
    for (int i = 0; i < 10'000'000; ++i) {
        delta2d = {Distribution::Uniform<double>()(mt64),
                   Distribution::Uniform<double>()(mt64)};
        v2d += delta2d;
    }
    time = timer.MillisecondsElapsed();
    std::cout << "    CLHEPX::...::MT64Engine : " << time << " ms (last displacement: " << std::setprecision(18) << v2d << std::setprecision(6) << ')' << std::endl;

    v2d = {0, 0};
    for (int i = 0; i < 1'000'000; ++i) {
        delta2d = {mt64x.flat(),
                   mt64x.flat()};
        v2d += delta2d;
    }
    timer.Reset();
    for (int i = 0; i < 10'000'000; ++i) {
        delta2d = {mt64x.flat(),
                   mt64x.flat()};
        v2d += delta2d;
    }
    time = timer.MillisecondsElapsed();
    std::cout << "       Math::...::MT1993764 : " << time << " ms (last displacement: " << std::setprecision(18) << v2d << std::setprecision(6) << ')' << std::endl;

    std::cout << "3D random walk, 10 million steps:" << std::endl;
    Eigen::RowVector3d v3d = {0, 0, 0};
    Eigen::RowVector3d delta3d;

    for (int i = 0; i < 1'000'000; ++i) {
        delta3d = {Distribution::Uniform<double>()(mt64),
                   Distribution::Uniform<double>()(mt64),
                   Distribution::Uniform<double>()(mt64)};
        v3d += delta3d;
    }
    timer.Reset();
    for (int i = 0; i < 10'000'000; ++i) {
        delta3d = {Distribution::Uniform<double>()(mt64),
                   Distribution::Uniform<double>()(mt64),
                   Distribution::Uniform<double>()(mt64)};
        v3d += delta3d;
    }
    time = timer.MillisecondsElapsed();
    std::cout << "    CLHEPX::...::MT64Engine : " << time << " ms (last displacement: " << std::setprecision(18) << v3d << std::setprecision(6) << ')' << std::endl;

    v3d = {0, 0, 0};
    for (int i = 0; i < 1'000'000; ++i) {
        delta3d = {mt64x.flat(),
                   mt64x.flat(),
                   mt64x.flat()};
        v3d += delta3d;
    }
    timer.Reset();
    for (int i = 0; i < 10'000'000; ++i) {
        delta3d = {mt64x.flat(),
                   mt64x.flat(),
                   mt64x.flat()};
        v3d += delta3d;
    }
    time = timer.MillisecondsElapsed();
    std::cout << "       Math::...::MT1993764 : " << time << " ms (last displacement: " << std::setprecision(18) << v3d << std::setprecision(6) << ')' << std::endl;

    std::cout << "4D random walk, 10 million steps:" << std::endl;
    Eigen::RowVector4d v4d = {0, 0, 0, 0};
    Eigen::RowVector4d delta4d;

    for (int i = 0; i < 1'000'000; ++i) {
        delta4d = {Distribution::Uniform<double>()(mt64),
                   Distribution::Uniform<double>()(mt64),
                   Distribution::Uniform<double>()(mt64),
                   Distribution::Uniform<double>()(mt64)};
        v4d += delta4d;
    }
    timer.Reset();
    for (int i = 0; i < 10'000'000; ++i) {
        delta4d = {Distribution::Uniform<double>()(mt64),
                   Distribution::Uniform<double>()(mt64),
                   Distribution::Uniform<double>()(mt64),
                   Distribution::Uniform<double>()(mt64)};
        v4d += delta4d;
    }
    time = timer.MillisecondsElapsed();
    std::cout << "    CLHEPX::...::MT64Engine : " << time << " ms (last displacement: " << std::setprecision(18) << v4d << std::setprecision(6) << ')' << std::endl;

    v4d = {0, 0, 0, 0};
    for (int i = 0; i < 1'000'000; ++i) {
        delta4d = {mt64x.flat(),
                   mt64x.flat(),
                   mt64x.flat(),
                   mt64x.flat()};
        v4d += delta4d;
    }
    timer.Reset();
    for (int i = 0; i < 10'000'000; ++i) {
        delta4d = {mt64x.flat(),
                   mt64x.flat(),
                   mt64x.flat(),
                   mt64x.flat()};
        v4d += delta4d;
    }
    time = timer.MillisecondsElapsed();
    std::cout << "       Math::...::MT1993764 : " << time << " ms (last displacement: " << std::setprecision(18) << v4d << std::setprecision(6) << ')' << std::endl;

    return 0;
}
