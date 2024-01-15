#pragma once

#include "MACE/Math/Parity.h++"
#include "MACE/Math/Random/Distribution/Uniform.h++"
#include "MACE/Math/Random/UniformPseudoRandomBitGenerator.h++"

#include "CLHEP/Random/RandomEngine.h"

#include "gsl/gsl"

#include "fmt/format.h"

#include <cstdio>
#include <fstream>
#include <limits>
#include <string>
#include <string_view>
#include <typeinfo>

namespace MACE::inline Extension::CLHEPX::Random {

template<Math::Random::UniformPseudoRandomBitGenerator PRBG>
class Wrap : public CLHEP::HepRandomEngine {
public:
    Wrap();
    explicit Wrap(long seed);

    ~Wrap() = default;

    auto flat() -> double override final { return Math::Random::Uniform<double>{}(fPRBG); }
    virtual auto flatArray(const int size, double* vect) -> void override;

    auto setSeed(long seed, int = 0) -> void override final;
    auto setSeeds(const long* seeds, int = 0) -> void override final;

    auto saveStatus(gsl::czstring filename) const -> void override final;
    auto restoreStatus(gsl::czstring filename) -> void override final;
    auto showStatus() const -> void override final;

    virtual auto name() const -> std::string override { return typeid(Wrap).name(); }

    auto put(std::ostream& os) const -> decltype(os) override final;
    auto get(std::istream& is) -> decltype(is) override final;

    operator double() override final { return Math::Random::Uniform<double>()(fPRBG); }
    operator float() override final { return Math::Random::Uniform<float>()(fPRBG); }
    operator unsigned int() override final { return fPRBG(); }

private:
    /// @brief Do not use.
    auto getState(std::istream& is) -> decltype(is) override final;

private:
    PRBG fPRBG;
};

} // namespace MACE::inline Extension::CLHEPX::Random

#include "MACE/Extension/CLHEPX/Random/Wrap.inl"
