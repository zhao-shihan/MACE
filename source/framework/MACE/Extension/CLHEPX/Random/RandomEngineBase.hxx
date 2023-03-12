#pragma once

#include "MACE/Math/Parity.hxx"
#include "MACE/Math/Random/Distribution/Uniform.hxx"
#include "MACE/Math/Random/UniformPseudoRandomBitGenerator.hxx"

#include "CLHEP/Random/RandomEngine.h"

#include "gsl/gsl"

#include <fstream>
#include <limits>
#include <string>
#include <string_view>
#include <typeinfo>

namespace MACE::inline Extension::CLHEPX::Random {

template<Math::Random::UniformPseudoRandomBitGenerator PRBG>
class RandomEngineBase : public CLHEP::HepRandomEngine {
public:
    RandomEngineBase();
    RandomEngineBase(long seed);

protected:
    ~RandomEngineBase() = default;

public:
    double flat() override final { return Math::Random::Distribution::Uniform<double>()(fPRBG); }
    virtual void flatArray(const int size, double* vect) override;

    void setSeed(long seed, int = 0) override final;
    void setSeeds(const long* seeds, int = 0) override final;

    void saveStatus(gsl::czstring filename) const override final;
    void restoreStatus(gsl::czstring filename) override final;
    void showStatus() const override final;

    std::ostream& put(std::ostream& os) const override final;
    std::istream& get(std::istream& is) override final;

    operator double() override final { return Math::Random::Distribution::Uniform<double>()(fPRBG); }
    operator float() override final { return Math::Random::Distribution::Uniform<float>()(fPRBG); }
    operator unsigned int() override final { return fPRBG(); }

private:
    /// @brief Do not use.
    std::istream& getState(std::istream& is) override final;

private:
    PRBG fPRBG;
};

} // namespace MACE::inline Extension::CLHEPX::Random

#include "MACE/Extension/CLHEPX/Random/RandomEngineBase.inl"
