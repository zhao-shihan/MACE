#pragma once

#include "MACE/Data/SimVertex.h++"
#include "Mustard/Data/Tuple.h++"
#include "Mustard/Env/Memory/PassiveSingleton.h++"
#include "Mustard/Extension/Geant4X/Generator/GeneralParticleSourceX.h++"
#include "MACE/SimMACE/Messenger/AnalysisMessenger.h++"

#include "G4VUserPrimaryGeneratorAction.hh"

#include <memory>
#include <vector>

namespace MACE::SimMACE::inline Action {

class PrimaryGeneratorAction final : public Mustard::Env::Memory::PassiveSingleton<PrimaryGeneratorAction>,
                                     public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGeneratorAction();

    auto SavePrimaryVertexData() const -> auto { return fSavePrimaryVertexData; }
    auto SavePrimaryVertexData(bool val) -> void { fSavePrimaryVertexData = val; }

    auto GeneratePrimaries(G4Event* event) -> void override;

private:
    auto UpdatePrimaryVertexData(const G4Event& event) -> void;

private:
    Mustard::Geant4X::GeneralParticleSourceX fGPSX;

    bool fSavePrimaryVertexData;
    std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimPrimaryVertex>>> fPrimaryVertexData;

    AnalysisMessenger::Register<PrimaryGeneratorAction> fMessengerRegister;
};

} // namespace MACE::SimMACE::inline Action
