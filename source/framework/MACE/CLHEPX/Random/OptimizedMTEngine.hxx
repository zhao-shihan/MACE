#pragma once

#include "MACE/Utility/Math/Random/MT1993732.hxx"

#include "CLHEP/Random/RandomEngine.h"

#include <cmath>

namespace MACE::CLHEPX::Random {

class OptimizedMTEngine final : public CLHEP::HepRandomEngine {
private:
    using MT = MACE::Utility::Math::Random::MT1993732;

public:
    OptimizedMTEngine();
    OptimizedMTEngine(long seed);

    double flat() override { return fgToDoubleFactor * NonZeroMTRandom(); }
    void flatArray(const int size, double* vect) override;

    void setSeed(long seed, int = 0) override;
    void setSeeds(const long* seeds, int = 0) override;

    void saveStatus(const char filename[] = "OptimizedMT.conf") const override;
    void restoreStatus(const char filename[] = "OptimizedMT.conf") override;
    void showStatus() const override;

    static std::string engineName() { return "OptimizedMTEngine"; }
    std::string name() const override { return engineName(); }

    std::ostream& put(std::ostream& os) const override;
    std::istream& get(std::istream& is) override;

    static std::string beginTag() { return "OptimizedMTEngine-begin"; }
    std::istream& getState(std::istream& is) override;

    std::vector<unsigned long> put() const override;
    bool get(const std::vector<unsigned long>& v) override;
    bool getState(const std::vector<unsigned long>& v) override;

    operator double() override { return flat(); }
    operator float() override { return fgToFloatFactor * NonZeroMTRandom(); }
    operator unsigned int() override { return fMT(); }

private:
    inline MT::ResultType NonZeroMTRandom();

private:
    MT fMT;

    static constexpr double fgToDoubleFactor = 1.0 / (MT::Max() + 1ULL);
    static inline const float fgToFloatFactor = std::nexttowardf(fgToDoubleFactor, 0); // Avoid end point
};

} // namespace CLHEPX

#include "MACE/CLHEPX/Random/OptimizedMTEngine.inl"
