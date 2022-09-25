#include "MACE/Math/Random/Distribution/Uniform.hxx"
#include "MACE/Math/Random/Generator/MT1993732.hxx"
#include "MACE/Math/Random/Generator/PCGXSHRR6432.hxx"
#include "MACE/Utility/WallTimer.hxx"

#include "Eigen/Core"

#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <random>

using MACE::Utility::WallTimer;
using namespace MACE::Math::Random;

int main() {
    Generator::MT1993732 mt1993732;
    Generator::PCGXSHRR6432 pcg32;

    std::cout << "Simply generate 10 million integers:" << std::endl;

    auto r = mt1993732();
    for (int i = 0; i < 1000; ++i) { r = mt1993732(); }
    WallTimer<double> timer;
    for (int i = 0; i < 10'000'000; ++i) { r = mt1993732(); }
    auto time = timer.MillisecondsElapsed();
    std::cout << "          MT19937-32 : " << time << " ms (last integer: " << r << ')' << std::endl;

    for (int i = 0; i < 1000; ++i) { r = pcg32(); }
    timer.Reset();
    for (int i = 0; i < 10'000'000; ++i) { r = pcg32(); }
    time = timer.MillisecondsElapsed();
    std::cout << "    PCG-XSH-RR-64/32 : " << time << " ms (last integer: " << r << ')' << std::endl;

    std::cout << "Shuffle a std::array<double, 16> 1 million times:" << std::endl;
    std::array<double, 16> arr16;
    std::iota(arr16.begin(), arr16.end(), 0);

    for (int i = 0; i < 1000; ++i) { std::ranges::shuffle(arr16, mt1993732); }
    timer.Reset();
    for (int i = 0; i < 1'000'000; ++i) { std::ranges::shuffle(arr16, mt1993732); }
    time = timer.MillisecondsElapsed();
    std::cout << "          MT19937-32 : " << time << " ms (first element: " << arr16.front() << ')' << std::endl;

    for (int i = 0; i < 1000; ++i) { std::ranges::shuffle(arr16, pcg32); }
    timer.Reset();
    for (int i = 0; i < 1'000'000; ++i) { std::ranges::shuffle(arr16, pcg32); }
    time = timer.MillisecondsElapsed();
    std::cout << "    PCG-XSH-RR-64/32 : " << time << " ms (first element: " << arr16.front() << ')' << std::endl;

    std::cout << "Shuffle a std::array<double, 4096> 10k times:" << std::endl;
    std::array<double, 4096> arr4096;
    std::iota(arr4096.begin(), arr4096.end(), 0);

    for (int i = 0; i < 100; ++i) { std::ranges::shuffle(arr4096, mt1993732); }
    timer.Reset();
    for (int i = 0; i < 10'000; ++i) { std::ranges::shuffle(arr4096, mt1993732); }
    time = timer.MillisecondsElapsed();
    std::cout << "          MT19937-32 : " << time << " ms (first element: " << arr4096.front() << ')' << std::endl;

    for (int i = 0; i < 100; ++i) { std::ranges::shuffle(arr4096, pcg32); }
    timer.Reset();
    for (int i = 0; i < 10'000; ++i) { std::ranges::shuffle(arr4096, pcg32); }
    time = timer.MillisecondsElapsed();
    std::cout << "    PCG-XSH-RR-64/32 : " << time << " ms (first element: " << arr4096.front() << ')' << std::endl;

    std::cout << "2D random walk, 10 million steps:" << std::endl;
    Eigen::RowVector2d v2d = {0, 0};
    Eigen::RowVector2d delta2d;

    for (int i = 0; i < 1'000'000; ++i) {
        delta2d = {Distribution::Uniform<double>()(mt1993732),
                   Distribution::Uniform<double>()(mt1993732)};
        v2d += delta2d;
    }
    timer.Reset();
    for (int i = 0; i < 10'000'000; ++i) {
        delta2d = {Distribution::Uniform<double>()(mt1993732),
                   Distribution::Uniform<double>()(mt1993732)};
        v2d += delta2d;
    }
    time = timer.MillisecondsElapsed();
    std::cout << "          MT19937-32 : " << time << " ms (last displacement: " << v2d << ')' << std::endl;

    v2d = {0, 0};
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
    std::cout << "    PCG-XSH-RR-64/32 : " << time << " ms (last displacement: " << v2d << ')' << std::endl;

    std::cout << "3D random walk, 10 million steps:" << std::endl;
    Eigen::RowVector3d v3d = {0, 0, 0};
    Eigen::RowVector3d delta3d;

    for (int i = 0; i < 1'000'000; ++i) {
        delta3d = {Distribution::Uniform<double>()(mt1993732),
                   Distribution::Uniform<double>()(mt1993732),
                   Distribution::Uniform<double>()(mt1993732)};
        v3d += delta3d;
    }
    timer.Reset();
    for (int i = 0; i < 10'000'000; ++i) {
        delta3d = {Distribution::Uniform<double>()(mt1993732),
                   Distribution::Uniform<double>()(mt1993732),
                   Distribution::Uniform<double>()(mt1993732)};
        v3d += delta3d;
    }
    time = timer.MillisecondsElapsed();
    std::cout << "          MT19937-32 : " << time << " ms (last displacement: " << v3d << ')' << std::endl;

    v3d = {0, 0, 0};
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
    std::cout << "    PCG-XSH-RR-64/32 : " << time << " ms (last displacement: " << v3d << ')' << std::endl;

    std::cout << "4D random walk, 10 million steps:" << std::endl;
    Eigen::RowVector4d v4d = {0, 0, 0, 0};
    Eigen::RowVector4d delta4d;

    for (int i = 0; i < 1'000'000; ++i) {
        delta4d = {Distribution::Uniform<double>()(mt1993732),
                   Distribution::Uniform<double>()(mt1993732),
                   Distribution::Uniform<double>()(mt1993732),
                   Distribution::Uniform<double>()(mt1993732)};
        v4d += delta4d;
    }
    timer.Reset();
    for (int i = 0; i < 10'000'000; ++i) {
        delta4d = {Distribution::Uniform<double>()(mt1993732),
                   Distribution::Uniform<double>()(mt1993732),
                   Distribution::Uniform<double>()(mt1993732),
                   Distribution::Uniform<double>()(mt1993732)};
        v4d += delta4d;
    }
    time = timer.MillisecondsElapsed();
    std::cout << "          MT19937-32 : " << time << " ms (last displacement: " << v4d << ')' << std::endl;

    v4d = {0, 0, 0, 0};
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
    std::cout << "    PCG-XSH-RR-64/32 : " << time << " ms (last displacement: " << v4d << ')' << std::endl;

    return 0;
}
