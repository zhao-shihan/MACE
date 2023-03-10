#pragma once

#include "G4VPrimaryGenerator.hh"

class G4MuonPlus;

namespace MACE::Geant4X::Generator {

/// @brief brief description A generator generates surface muon beam.
class SurfaceMuon final : public G4VPrimaryGenerator {
public:
    SurfaceMuon();
    ~SurfaceMuon() noexcept = default;
    SurfaceMuon(const SurfaceMuon&) = delete;
    SurfaceMuon& operator=(const SurfaceMuon&) = delete;

    void GeneratePrimaryVertex(G4Event* event) override;

    void Momentum(G4double val) { fMomentum = val; }
    void MomentumSpreadRMS(G4double val) { fMomentumSpreadRMS = val; }
    void BeamProfileRMS(G4double val) { fBeamProfileRMS = val; }
    void VertexTime(G4double val) { fVertexTime = val; }
    void VertexZ(G4double val) { fVertexZ = val; }

    const auto& Momentum() const { return fMomentum; }
    const auto& MomentumSpreadRMS() const { return fMomentumSpreadRMS; }
    const auto& BeamProfileRMS() const { return fBeamProfileRMS; }
    const auto& VertexZ() const { return fVertexZ; }
    const auto& VertexTime() const { return fVertexTime; }

private:
    const G4MuonPlus* const fMuonPlus;

    G4double fMomentum;
    G4double fMomentumSpreadRMS;
    G4double fBeamProfileRMS;
    G4double fVertexTime;
    G4double fVertexZ;
};

} // namespace MACE::Geant4X::Generator
