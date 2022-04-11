#pragma once

#include "MACE/Simulation/Generator/SurfaceMuon/PrimaryGeneratorAction.hxx"

namespace MACE::Simulation::SimTarget::Action {

using namespace Generator;

class PrimaryGeneratorAction final : public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction() noexcept = default;
    PrimaryGeneratorAction(const PrimaryGeneratorAction&) = delete;
    PrimaryGeneratorAction& operator=(const PrimaryGeneratorAction&) = delete;

    void GeneratePrimaries(G4Event* event) override;

    const auto& GetSurfaceMuonPGA() const { return fSurfaceMuonPGA; }

private:
    SurfaceMuon::PrimaryGeneratorAction fSurfaceMuonPGA;
};

} // namespace MACE::Simulation::SimTarget
