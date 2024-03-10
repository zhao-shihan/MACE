#pragma once

#include "MACE/Env/CLI/BasicCLI.h++"

#include <optional>
#include <string>

namespace CLHEP {
class HepRandomEngine;
} // namespace CLHEP

namespace MACE::Env::CLI {

class Geant4CLI : public BasicCLI {
public:
    Geant4CLI();

    auto Macro() const -> std::optional<std::string>;
    auto IsInteractive() const -> auto { return not Macro().has_value() or ArgParser().is_used("-i"); }

    auto Seed(CLHEP::HepRandomEngine& rng) const -> bool;
};

} // namespace MACE::Env::CLI
