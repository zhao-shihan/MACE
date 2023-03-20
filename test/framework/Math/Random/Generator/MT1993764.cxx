#include "MACE/Math/Random/Generator/MT1993764.hxx"
#include "MACE/Utility/WallTimer.hxx"

#include "Eigen/Core"

#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>

using namespace MACE;

int main() {
    std::mt19937_64 stdMT1993764;
    Math::Random::MT1993764 mt1993764;

    std::cout << "Simply generate 10 million integers:" << std::endl;

    uintmax_t r;
    for (int i = 0; i < 1'000'000; ++i) { r = stdMT1993764(); }
    WallTimer<> timer;
    for (int i = 0; i < 10'000'000; ++i) { r = stdMT1993764(); }
    auto time = timer.MillisecondsElapsed();
    std::cout << "    std::mt19937_64 : " << time << " ms (last integer: " << r << ')' << std::endl;

    for (int i = 0; i < 1'000'000; ++i) { r = mt1993764(); }
    timer.Reset();
    for (int i = 0; i < 10'000'000; ++i) { r = mt1993764(); }
    time = timer.MillisecondsElapsed();
    std::cout << "    MACE MT19937-64 : " << time << " ms (last integer: " << r << ')' << std::endl;

    std::cout << "Shuffle a std::array<double, 16> 1 million times:" << std::endl;
    std::array<double, 16> arr16;

    std::iota(arr16.begin(), arr16.end(), 0);
    for (int i = 0; i < 100'000; ++i) { std::ranges::shuffle(arr16, stdMT1993764); }
    timer.Reset();
    for (int i = 0; i < 1'000'000; ++i) { std::ranges::shuffle(arr16, stdMT1993764); }
    time = timer.MillisecondsElapsed();
    std::cout << "    std::mt19937_64 : " << time << " ms (first element: " << arr16.front() << ')' << std::endl;

    std::iota(arr16.begin(), arr16.end(), 0);
    for (int i = 0; i < 100'000; ++i) { std::ranges::shuffle(arr16, mt1993764); }
    timer.Reset();
    for (int i = 0; i < 1'000'000; ++i) { std::ranges::shuffle(arr16, mt1993764); }
    time = timer.MillisecondsElapsed();
    std::cout << "    MACE MT19937-64 : " << time << " ms (first element: " << arr16.front() << ')' << std::endl;

    std::cout << "Shuffle a std::array<double, 4096> 10k times:" << std::endl;
    std::array<double, 4096> arr4096;

    std::iota(arr4096.begin(), arr4096.end(), 0);
    for (int i = 0; i < 1'000; ++i) { std::ranges::shuffle(arr4096, stdMT1993764); }
    timer.Reset();
    for (int i = 0; i < 10'000; ++i) { std::ranges::shuffle(arr4096, stdMT1993764); }
    time = timer.MillisecondsElapsed();
    std::cout << "    std::mt19937_64 : " << time << " ms (first element: " << arr4096.front() << ')' << std::endl;

    std::iota(arr4096.begin(), arr4096.end(), 0);
    for (int i = 0; i < 1'000; ++i) { std::ranges::shuffle(arr4096, mt1993764); }
    timer.Reset();
    for (int i = 0; i < 10'000; ++i) { std::ranges::shuffle(arr4096, mt1993764); }
    time = timer.MillisecondsElapsed();
    std::cout << "    MACE MT19937-64 : " << time << " ms (first element: " << arr4096.front() << ')' << std::endl;

    std::cout << "2D random walk, 10 million steps:" << std::endl;
    Eigen::RowVector2d v2d = {0, 0};
    Eigen::RowVector2d delta2d;

    for (int i = 0; i < 1'000'000; ++i) {
        delta2d = {std::uniform_real_distribution()(stdMT1993764),
                   std::uniform_real_distribution()(stdMT1993764)};
        v2d += delta2d;
    }
    timer.Reset();
    for (int i = 0; i < 10'000'000; ++i) {
        delta2d = {std::uniform_real_distribution()(stdMT1993764),
                   std::uniform_real_distribution()(stdMT1993764)};
        v2d += delta2d;
    }
    time = timer.MillisecondsElapsed();
    std::cout << "    std::mt19937_64 : " << time << " ms (last displacement: " << std::setprecision(18) << v2d << std::setprecision(6) << ')' << std::endl;

    v2d = {0, 0};
    for (int i = 0; i < 1'000'000; ++i) {
        delta2d = {std::uniform_real_distribution()(mt1993764),
                   std::uniform_real_distribution()(mt1993764)};
        v2d += delta2d;
    }
    timer.Reset();
    for (int i = 0; i < 10'000'000; ++i) {
        delta2d = {std::uniform_real_distribution()(mt1993764),
                   std::uniform_real_distribution()(mt1993764)};
        v2d += delta2d;
    }
    time = timer.MillisecondsElapsed();
    std::cout << "    MACE MT19937-64 : " << time << " ms (last displacement: " << std::setprecision(18) << v2d << std::setprecision(6) << ')' << std::endl;

    std::cout << "3D random walk, 10 million steps:" << std::endl;
    Eigen::RowVector3d v3d = {0, 0, 0};
    Eigen::RowVector3d delta3d;

    for (int i = 0; i < 1'000'000; ++i) {
        delta3d = {std::uniform_real_distribution()(stdMT1993764),
                   std::uniform_real_distribution()(stdMT1993764),
                   std::uniform_real_distribution()(stdMT1993764)};
        v3d += delta3d;
    }
    timer.Reset();
    for (int i = 0; i < 10'000'000; ++i) {
        delta3d = {std::uniform_real_distribution()(stdMT1993764),
                   std::uniform_real_distribution()(stdMT1993764),
                   std::uniform_real_distribution()(stdMT1993764)};
        v3d += delta3d;
    }
    time = timer.MillisecondsElapsed();
    std::cout << "    std::mt19937_64 : " << time << " ms (last displacement: " << std::setprecision(18) << v3d << std::setprecision(6) << ')' << std::endl;

    v3d = {0, 0, 0};
    for (int i = 0; i < 1'000'000; ++i) {
        delta3d = {std::uniform_real_distribution()(mt1993764),
                   std::uniform_real_distribution()(mt1993764),
                   std::uniform_real_distribution()(mt1993764)};
        v3d += delta3d;
    }
    timer.Reset();
    for (int i = 0; i < 10'000'000; ++i) {
        delta3d = {std::uniform_real_distribution()(mt1993764),
                   std::uniform_real_distribution()(mt1993764),
                   std::uniform_real_distribution()(mt1993764)};
        v3d += delta3d;
    }
    time = timer.MillisecondsElapsed();
    std::cout << "    MACE MT19937-64 : " << time << " ms (last displacement: " << std::setprecision(18) << v3d << std::setprecision(6) << ')' << std::endl;

    std::cout << "4D random walk, 10 million steps:" << std::endl;
    Eigen::RowVector4d v4d = {0, 0, 0, 0};
    Eigen::RowVector4d delta4d;

    for (int i = 0; i < 1'000'000; ++i) {
        delta4d = {std::uniform_real_distribution()(stdMT1993764),
                   std::uniform_real_distribution()(stdMT1993764),
                   std::uniform_real_distribution()(stdMT1993764),
                   std::uniform_real_distribution()(stdMT1993764)};
        v4d += delta4d;
    }
    timer.Reset();
    for (int i = 0; i < 10'000'000; ++i) {
        delta4d = {std::uniform_real_distribution()(stdMT1993764),
                   std::uniform_real_distribution()(stdMT1993764),
                   std::uniform_real_distribution()(stdMT1993764),
                   std::uniform_real_distribution()(stdMT1993764)};
        v4d += delta4d;
    }
    time = timer.MillisecondsElapsed();
    std::cout << "    std::mt19937_64 : " << time << " ms (last displacement: " << std::setprecision(18) << v4d << std::setprecision(6) << ')' << std::endl;

    v4d = {0, 0, 0, 0};
    for (int i = 0; i < 1'000'000; ++i) {
        delta4d = {std::uniform_real_distribution()(mt1993764),
                   std::uniform_real_distribution()(mt1993764),
                   std::uniform_real_distribution()(mt1993764),
                   std::uniform_real_distribution()(mt1993764)};
        v4d += delta4d;
    }
    timer.Reset();
    for (int i = 0; i < 10'000'000; ++i) {
        delta4d = {std::uniform_real_distribution()(mt1993764),
                   std::uniform_real_distribution()(mt1993764),
                   std::uniform_real_distribution()(mt1993764),
                   std::uniform_real_distribution()(mt1993764)};
        v4d += delta4d;
    }
    time = timer.MillisecondsElapsed();
    std::cout << "    MACE MT19937-64 : " << time << " ms (last displacement: " << std::setprecision(18) << v4d << std::setprecision(6) << ')' << std::endl;

    return 0;
}
