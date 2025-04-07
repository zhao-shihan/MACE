#pragma once

#include "MACE/Data/SimVertex.h++"
#include "MACE/SimVeto/Messenger/AnalysisMessenger.h++"
#include "MACE/SimVeto/Messenger/PrimaryGeneratorActionMessenger.h++"

#include "Mustard/Data/Tuple.h++"
#include "Mustard/Env/Memory/PassiveSingleton.h++"
#include "Mustard/Extension/Geant4X/Generator/EcoMugCosmicRayMuon.h++"
#include "Mustard/Extension/Geant4X/Generator/GeneralParticleSourceX.h++"

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

#include <memory>
#include <vector>

namespace MACE::SimVeto::inline Action {

class PrimaryGeneratorAction final : public Mustard::Env::Memory::PassiveSingleton<PrimaryGeneratorAction>,
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
        Mustard::Geant4X::GeneralParticleSourceX gpsx;
        Mustard::Geant4X::EcoMugCosmicRayMuon ecoMug{Mustard::Geant4X::EcoMugCosmicRayMuon::Coordinate::Beam};
    } fAvailableGenerator;
    G4VPrimaryGenerator* fGenerator;

    bool fSavePrimaryVertexData;
    std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimPrimaryVertex>>> fPrimaryVertexData;

    AnalysisMessenger::Register<PrimaryGeneratorAction> fAnalysisMessengerRegister;
    PrimaryGeneratorActionMessenger::Register<PrimaryGeneratorAction> fPrimaryGeneratorActionMessengerRegister;
};

} // namespace MACE::SimVeto::inline Action
