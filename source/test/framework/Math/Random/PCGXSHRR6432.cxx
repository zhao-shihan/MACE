#include "MACE/Math/Random/Generator/PCGXSHRR6432.hxx"
#include "MACE/Utility/Timer.hxx"

#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <random>

using MACE::Utility::Timer;
using namespace MACE::Math::Random;

int main() {
    std::mt19937 stdMT19937;
    Generator::PCGXSHRR6432 pcg32;

    std::cout << "Simply generate 10k integers:" << std::endl;

    auto r = stdMT19937();
    for (int i = 0; i < 100; ++i) { r = stdMT19937(); }
    Timer timer;
    for (int i = 0; i < 10'000; ++i) { r = stdMT19937(); }
    auto time = timer.MicrosecondsElapsed();
    std::cout << "        std::mt19937 : " << time << " us (last integer: " << r << ')' << std::endl;

    for (int i = 0; i < 100; ++i) { r = pcg32(); }
    timer.Reset();
    for (int i = 0; i < 10'000; ++i) { r = pcg32(); }
    time = timer.MicrosecondsElapsed();
    std::cout << "    PCG-XSH-RR-64/32 : " << time << " us (last integer: " << r << ')' << std::endl;

    std::cout << "Shuffle a std::array<double, 16> 1k times:" << std::endl;
    std::array<double, 16> arr16;
    std::iota(arr16.begin(), arr16.end(), 0);

    for (int i = 0; i < 10; ++i) { std::ranges::shuffle(arr16, stdMT19937); }
    timer.Reset();
    for (int i = 0; i < 1'000; ++i) { std::ranges::shuffle(arr16, stdMT19937); }
    time = timer.MicrosecondsElapsed();
    std::cout << "        std::mt19937 : " << time << " us (first element: " << arr16.front() << ')' << std::endl;

    for (int i = 0; i < 10; ++i) { std::ranges::shuffle(arr16, pcg32); }
    timer.Reset();
    for (int i = 0; i < 1'000; ++i) { std::ranges::shuffle(arr16, pcg32); }
    time = timer.MicrosecondsElapsed();
    std::cout << "    PCG-XSH-RR-64/32 : " << time << " us (first element: " << arr16.front() << ')' << std::endl;

    std::cout << "Shuffle a std::array<double, 4096> 10 times:" << std::endl;
    std::array<double, 4096> arr4096;
    std::iota(arr4096.begin(), arr4096.end(), 0);

    for (int i = 0; i < 10; ++i) { std::ranges::shuffle(arr4096, stdMT19937); }
    timer.Reset();
    for (int i = 0; i < 10; ++i) { std::ranges::shuffle(arr4096, stdMT19937); }
    time = timer.MicrosecondsElapsed();
    std::cout << "        std::mt19937 : " << time << " us (first element: " << arr4096.front() << ')' << std::endl;

    for (int i = 0; i < 10; ++i) { std::ranges::shuffle(arr4096, pcg32); }
    timer.Reset();
    for (int i = 0; i < 10; ++i) { std::ranges::shuffle(arr4096, pcg32); }
    time = timer.MicrosecondsElapsed();
    std::cout << "    PCG-XSH-RR-64/32 : " << time << " us (first element: " << arr4096.front() << ')' << std::endl;

    return 0;
}
