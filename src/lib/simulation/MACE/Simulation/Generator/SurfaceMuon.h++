#pragma once

#include "MACE/Simulation/Generator/SurfaceMuonMessenger.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "G4VPrimaryGenerator.hh"

class G4MuonPlus;

namespace MACE::inline Simulation::Generator {

/// @brief A generator generates surface muon beam.
class SurfaceMuon final : public NonMoveableBase,
                          public G4VPrimaryGenerator {
public:
    SurfaceMuon();

    void GeneratePrimaryVertex(G4Event* event) override;

    void Momentum(G4double val) { fMomentum = val; }
    void MomentumRMS(G4double val) { fMomentumRMS = val; }
    void PositionRMS(G4double val) { fPositionRMS = val; }
    void Time(G4double val) { fTime = val; }
    void PositionZ(G4double val) { fPositionZ = val; }

    const auto& Momentum() const { return fMomentum; }
    const auto& MomentumRMS() const { return fMomentumRMS; }
    const auto& PositionRMS() const { return fPositionRMS; }
    const auto& Time() const { return fTime; }
    const auto& PositionZ() const { return fPositionZ; }

private:
    const G4MuonPlus* const fMuonPlus;

    G4double fMomentum;
    G4double fMomentumRMS;
    G4double fPositionRMS;
    G4double fTime;
    G4double fPositionZ;

    SurfaceMuonMessenger::Register<SurfaceMuon> fMessengerRegister;
};

} // namespace MACE::inline Simulation::Generator
