#pragma once

#include "MACE/SimulationG4/Generator/SurfaceMuon.hxx"

#include "G4VUserPrimaryGeneratorAction.hh"

namespace MACE::SimTarget::Action {

class PrimaryGeneratorAction final : public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction() noexcept = default;
    PrimaryGeneratorAction(const PrimaryGeneratorAction&) = delete;
    PrimaryGeneratorAction& operator=(const PrimaryGeneratorAction&) = delete;

    void SetMuonsForEachG4Event(G4int n) { fMuonsForEachG4Event = n; }
    const auto& GetMuonsForEachG4Event() const { return fMuonsForEachG4Event; }

    void GeneratePrimaries(G4Event* event) override;

private:
    SimulationG4::Generator::SurfaceMuon fSurfaceMuonGenerator;

    G4int fMuonsForEachG4Event;
};

} // namespace MACE::SimTarget::Action
