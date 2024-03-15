#pragma once

#include "G4VPrimaryGenerator.hh"

#include <any>

namespace MACE::inline Simulation::Generator {

/// @brief brief description A generator generates surface muon beam.
class EcoMugCosmicRayMuon final : public G4VPrimaryGenerator {
public:
    EcoMugCosmicRayMuon();
    ~EcoMugCosmicRayMuon();

    auto GeneratePrimaryVertex(G4Event* event) -> void override;

private:
    std::any fEcoMug;
};

} // namespace MACE::inline Simulation::Generator
