#pragma once

#include "G4VPrimaryGenerator.hh"

#include <memory>

class G4MuonPlus;
class G4MuonMinus;
class EcoMug;

namespace Generator {

/// @brief brief description A generator generates surface muon beam.
class EcoMugCosmicRayMuon final : public G4VPrimaryGenerator {
public:
    EcoMugCosmicRayMuon();
    ~EcoMugCosmicRayMuon();

    auto GeneratePrimaryVertex(G4Event* event) -> void override;

private:
    const G4MuonPlus* const fMuonPlus;
    const G4MuonMinus* const fMuonMinus;

    std::unique_ptr<EcoMug> fEcoMug;
};

} // namespace Generator
