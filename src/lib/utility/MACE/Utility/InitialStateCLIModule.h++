#pragma once

#include "Mustard/CLI/CLI.h++"
#include "Mustard/CLI/Module/ModuleBase.h++"

#include "CLHEP/Vector/ThreeVector.h"

#include "muc/ceta_string"

#include "fmt/core.h"

#include <array>
#include <type_traits>
#include <vector>

namespace MACE::inline Utility {

template<muc::ceta_string P, muc::ceta_string... Ms>
    requires((P == "polarized" or P == "unpolarized") and sizeof...(Ms) >= 1)
class InitialStateCLIModule : public Mustard::CLI::ModuleBase {
public:
    explicit InitialStateCLIModule(gsl::not_null<Mustard::CLI::CLI<>*> cli);

    auto Momentum() const -> CLHEP::Hep3Vector
        requires(sizeof...(Ms) == 1);
    auto Momentum() const -> std::array<CLHEP::Hep3Vector, sizeof...(Ms)>
        requires(sizeof...(Ms) >= 2);
    auto Polarization() const -> CLHEP::Hep3Vector
        requires(P == "polarized" and sizeof...(Ms) == 1);
    auto Polarization() const -> std::array<CLHEP::Hep3Vector, sizeof...(Ms)>
        requires(P == "polarized" and sizeof...(Ms) >= 2);

public:
    auto To3Vector(std::string_view option) const -> CLHEP::Hep3Vector;
};

} // namespace MACE::inline Utility

#include "MACE/Utility/InitialStateCLIModule.inl"
