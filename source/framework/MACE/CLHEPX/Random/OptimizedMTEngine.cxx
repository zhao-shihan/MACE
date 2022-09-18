#include "MACE/CLHEPX/Random/OptimizedMTEngine.hxx"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace MACE::CLHEPX::Random {

OptimizedMTEngine::OptimizedMTEngine() :
    HepRandomEngine(),
    fMT() {
    auto seed = reinterpret_cast<std::intptr_t>(this);
    constexpr std::intptr_t longMax = std::numeric_limits<long>::max();
    constexpr std::intptr_t longMin = std::numeric_limits<long>::min();
    while (seed > longMax) { seed -= (longMax - longMin + 1); }
    while (seed < longMin) { seed += (longMax - longMin + 1); }
    setSeed(seed);
}

OptimizedMTEngine::OptimizedMTEngine(long seed) :
    HepRandomEngine(),
    fMT(seed) {
    theSeed = seed;
    theSeeds = &theSeed;
}

void OptimizedMTEngine::flatArray(const int size, double* vect) {
    for (const auto end = vect + size; vect != end; ++vect) {
        *vect = flat();
    }
}

void OptimizedMTEngine::setSeed(long seed, int) {
    fMT.Seed(seed);
    theSeed = seed;
    theSeeds = &theSeed;
}

void OptimizedMTEngine::setSeeds(const long* seeds, int) {
    fMT.Seed(*seeds);
    theSeed = *seeds;
    theSeeds = seeds;
}

void OptimizedMTEngine::saveStatus(const char filename[]) const {
    // std::ofstream os(filename, std::ios::out);
    // if (os.is_open()) {
    //     put(os);
    //     os.close();
    // }
    throw std::logic_error(
        "OptimizedMTEngine::saveStatus(const char[]) has not been implemented.\n"
        "Please contact the developer if this function is necessary.");
}

void OptimizedMTEngine::restoreStatus(const char filename[]) {
    // std::ifstream is(filename, std::ios::in);
    // if (checkFile(is, filename, engineName(), "restoreStatus")) {
    //     get(is);
    // } else {
    //     std::cerr << "  -- Engine state remains unchanged" << std::endl;
    // }
    // is.close();
    throw std::logic_error(
        "OptimizedMTEngine::restoreStatus(const char[]) has not been implemented.\n"
        "Please contact the developer if this function is necessary.");
}

void OptimizedMTEngine::showStatus() const {
    throw std::logic_error(
        "OptimizedMTEngine::showStatus() has not been implemented.\n"
        "Please contact the developer if this function is necessary.");
}

std::ostream& OptimizedMTEngine::put(std::ostream& os) const {
    throw std::logic_error(
        "OptimizedMTEngine::put(std::ostream&) has not been implemented.\n"
        "Please contact the developer if this function is necessary.");
}

std::istream& OptimizedMTEngine::get(std::istream& is) {
    throw std::logic_error(
        "OptimizedMTEngine::get(std::istream&) has not been implemented.\n"
        "Please contact the developer if this function is necessary.");
}

std::istream& OptimizedMTEngine::getState(std::istream& is) {
    throw std::logic_error(
        "OptimizedMTEngine::getState(std::istream&) has not been implemented.\n"
        "Please contact the developer if this function is necessary.");
}

std::vector<unsigned long> OptimizedMTEngine::put() const {
    throw std::logic_error(
        "OptimizedMTEngine::put() has not been implemented.\n"
        "Please contact the developer if this function is necessary.");
}

bool OptimizedMTEngine::get(const std::vector<unsigned long>& v) {
    throw std::logic_error(
        "OptimizedMTEngine::get(const std::vector<unsigned long>&) has not been implemented.\n"
        "Please contact the developer if this function is necessary.");
}

bool OptimizedMTEngine::getState(const std::vector<unsigned long>& v) {
    throw std::logic_error(
        "OptimizedMTEngine::getState(const std::vector<unsigned long>&) has not been implemented.\n"
        "Please contact the developer if this function is necessary.");
}

} // namespace CLHEPX
