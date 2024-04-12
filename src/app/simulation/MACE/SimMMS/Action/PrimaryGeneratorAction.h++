#pragma once

#include "MACE/Data/SimVertex.h++"
#include "MACE/Data/Tuple.h++"
#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/Extension/Geant4X/GeneralParticleSourceX.h++"
#include "MACE/SimMMS/Messenger/AnalysisMessenger.h++"
#include "MACE/SimMMS/Messenger/PrimaryGeneratorActionMessenger.h++"
#include "MACE/Simulation/Generator/EcoMugCosmicRayMuon.h++"

#include "G4VUserPrimaryGeneratorAction.hh"

#include <memory>
#include <vector>

namespace MACE::SimMMS::inline Action {

class PrimaryGeneratorAction final : public Env::Memory::PassiveSingleton<PrimaryGeneratorAction>,
                                     public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGeneratorAction();

    auto SwitchToGPSX() -> void { fGenerator = &fAvailableGenerator.gpsx; }
    auto SwitchToEcoMug() -> void { fGenerator = &fAvailableGenerator.ecoMug; }

    auto SavePrimaryVertexData() const -> auto { return fSavePrimaryVertexData; }
    auto SavePrimaryVertexData(bool val) -> void { fSavePrimaryVertexData = val; }

    auto GeneratePrimaries(G4Event* event) -> void override;

private:
    auto UpdatePrimaryVertexData(const G4Event& event) -> void;

private:
    struct {
        Geant4X::GeneralParticleSourceX gpsx;
        Generator::EcoMugCosmicRayMuon ecoMug;
    } fAvailableGenerator;
    G4VPrimaryGenerator* fGenerator;

    bool fSavePrimaryVertexData;
    std::vector<std::unique_ptr<Data::Tuple<Data::SimPrimaryVertex>>> fPrimaryVertexData;

    PrimaryGeneratorActionMessenger::Register<PrimaryGeneratorAction> fMessengerRegister;
};

} // namespace MACE::SimMMS::inline Action
