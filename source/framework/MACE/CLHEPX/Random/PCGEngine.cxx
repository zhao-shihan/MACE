#include "MACE/CLHEPX/Random/PCGEngine.hxx"

#include <bit>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace MACE::CLHEPX::Random {

PCGEngine::PCGEngine() :
    HepRandomEngine(),
    fPCG() {
    auto seed = reinterpret_cast<std::intptr_t>(this);
    constexpr std::intptr_t longMax = std::numeric_limits<long>::max();
    constexpr std::intptr_t longMin = std::numeric_limits<long>::min();
    while (seed > longMax) { seed -= (longMax - longMin + 1); }
    while (seed < longMin) { seed += (longMax - longMin + 1); }
    setSeed(seed);
}

PCGEngine::PCGEngine(long seed) :
    HepRandomEngine(),
    fPCG(seed) {
    theSeed = seed;
    theSeeds = &theSeed;
}

void PCGEngine::flatArray(const int size, double* vect) {
    for (const auto end = vect + size; vect != end; ++vect) {
        *vect = flat();
    }
}

void PCGEngine::setSeed(long seed, int) {
    fPCG.Seed(seed);
    theSeed = seed;
    theSeeds = &theSeed;
}

void PCGEngine::setSeeds(const long* seeds, int) {
    fPCG.Seed(*seeds);
    theSeed = *seeds;
    theSeeds = seeds;
}

void PCGEngine::saveStatus(const char filename[]) const {
    // std::ofstream os(filename, std::ios::out);
    // if (os.is_open()) {
    //     put(os);
    //     os.close();
    // }
    throw std::logic_error(
        "PCGEngine::saveStatus(const char[]) has not been implemented.\n"
        "Please contact the developer if this function is necessary.");
}

void PCGEngine::restoreStatus(const char filename[]) {
    // std::ifstream is(filename, std::ios::in);
    // if (checkFile(is, filename, engineName(), "restoreStatus")) {
    //     get(is);
    // } else {
    //     std::cerr << "  -- Engine state remains unchanged" << std::endl;
    // }
    // is.close();
    throw std::logic_error(
        "PCGEngine::restoreStatus(const char[]) has not been implemented.\n"
        "Please contact the developer if this function is necessary.");
}

void PCGEngine::showStatus() const {
    // std::cout << "----- PCGEngine (PCG XSH RR 64/32) status -----\n"
    //           << " Initial seed = " << theSeed << '\n'
    //           << " State = " << fPCG.GetState() << '\n'
    //           << "-----------------------------------------------" << std::endl;
    throw std::logic_error(
        "PCGEngine::showStatus() has not been implemented.\n"
        "Please contact the developer if this function is necessary.");
}

std::ostream& PCGEngine::put(std::ostream& os) const {
    // os << beginTag() << '\n';
    // const std::vector<unsigned long> state = put();
    // for (unsigned long v : state) {
    //     os << v << '\n';
    // }
    // return os;
    throw std::logic_error(
        "PCGEngine::put(std::ostream&) has not been implemented.\n"
        "Please contact the developer if this function is necessary.");
}

std::istream& PCGEngine::get(std::istream& is) {
    // std::string tag;
    // is >> std::ws >> tag;
    // if (tag != beginTag()) {
    //     is.clear(std::ios::badbit | is.rdstate());
    //     std::cerr << "No PCGEngine found at current position\n";
    //     return is;
    // }
    // return getState(is);
    throw std::logic_error(
        "PCGEngine::get(std::istream&) has not been implemented.\n"
        "Please contact the developer if this function is necessary.");
}

std::istream& PCGEngine::getState(std::istream& is) {
    throw std::logic_error(
        "PCGEngine::getState(std::istream&) has not been implemented.\n"
        "Please contact the developer if this function is necessary.");
}

std::vector<unsigned long> PCGEngine::put() const {
    throw std::logic_error(
        "PCGEngine::put() has not been implemented.\n"
        "Please contact the developer if this function is necessary.");
}

bool PCGEngine::get(const std::vector<unsigned long>& v) {
    throw std::logic_error(
        "PCGEngine::get(const std::vector<unsigned long>&) has not been implemented.\n"
        "Please contact the developer if this function is necessary.");
}

bool PCGEngine::getState(const std::vector<unsigned long>& v) {
    throw std::logic_error(
        "PCGEngine::getState(const std::vector<unsigned long>&) has not been implemented.\n"
        "Please contact the developer if this function is necessary.");
}

} // namespace CLHEPX
