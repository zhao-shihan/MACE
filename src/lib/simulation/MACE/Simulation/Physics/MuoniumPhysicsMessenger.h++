#pragma once

#include "MACE/Extension/Geant4X/SingletonMessenger.h++"
#include "MACE/Simulation/Physics/TargetForMuoniumPhysics.h++"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"
#include "G4UImessenger.hh"

#include <memory>

namespace MACE::inline Simulation::inline Physics {

inline namespace Process {

template<TargetForMuoniumPhysics ATarget>
class MuoniumFormation;

template<TargetForMuoniumPhysics ATarget>
class MuoniumTransport;

} // namespace Process

template<TargetForMuoniumPhysics ATarget>
class MuoniumPhysicsMessenger final : public Geant4X::SingletonMessenger<MuoniumPhysicsMessenger<ATarget>,
                                                                         MuoniumFormation<ATarget>,
                                                                         MuoniumTransport<ATarget>> {
    friend Env::Memory::SingletonInstantiator;

private:
    MuoniumPhysicsMessenger();

public:
    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    std::unique_ptr<G4UIdirectory> fMuoniumPhysicsDirectory;

    std::unique_ptr<G4UIdirectory> fFormationProcessDirectory;
    std::unique_ptr<G4UIcmdWithADouble> fConversionProbability;

    std::unique_ptr<G4UIdirectory> fTransportProcessDirectory;
    std::unique_ptr<G4UIcmdWithABool> fManipulateAllSteps;
};

} // namespace MACE::inline Simulation::inline Physics

#include "MACE/Simulation/Physics/MuoniumPhysicsMessenger.inl"
