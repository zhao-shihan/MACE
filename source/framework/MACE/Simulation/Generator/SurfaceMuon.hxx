#pragma once

#include "MACE/Utility/ObserverPtr.hxx"

#include "G4VPrimaryGenerator.hh"

class G4MuonPlus;

namespace MACE::Simulation::Generator {

using Utility::ObserverPtr;

/// @brief brief description A generator generates surface muon beam.
class SurfaceMuon final : public G4VPrimaryGenerator {
public:
    SurfaceMuon();
    ~SurfaceMuon() noexcept = default;
    SurfaceMuon(const SurfaceMuon&) = delete;
    SurfaceMuon& operator=(const SurfaceMuon&) = delete;

    void GeneratePrimaryVertex(G4Event* event) override;

    void SetMomentum(G4double val) { fMomentum = val; }
    void SetMomentumSpreadRMS(G4double val) { fMomentumSpreadRMS = val; }
    void SetBeamProfileRMS(G4double val) { fBeamProfileRMS = val; }
    void SetVertexTime(G4double val) { fVertexTime = val; }
    void SetVertexZ(G4double val) { fVertexZ = val; }

    const auto& GetMomentum() const { return fMomentum; }
    const auto& GetMomentumSpreadRMS() const { return fMomentumSpreadRMS; }
    const auto& GetBeamProfileRMS() const { return fBeamProfileRMS; }
    const auto& GetVertexZ() const { return fVertexZ; }
    const auto& GetVertexTime() const { return fVertexTime; }

private:
    const ObserverPtr<const G4MuonPlus> fMuonPlus;

    G4double fMomentum;
    G4double fMomentumSpreadRMS;
    G4double fBeamProfileRMS;
    G4double fVertexTime;
    G4double fVertexZ;
};

} // namespace MACE::Simulation::Generator
