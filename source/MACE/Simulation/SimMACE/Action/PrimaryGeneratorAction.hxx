// -*- C++ -*-
/// @author Shihan Zhao

#pragma once

#include "MACE/Simulation/Generator/SurfaceMuon/PrimaryGeneratorAction.hxx"

namespace MACE::Simulation::SimMACE::Action {

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
    // CosmicRayMuon::PrimaryGeneratorAction fCosmicRayMuonPGA;
};

} // namespace MACE::Simulation::SimMACE::Action
