#pragma once

#include "MACE/Env/Memory/Singleton.h++"
#include "MACE/Simulation/Physics/Process/MuoniumFormation.h++"
#include "MACE/Simulation/Physics/Process/MuoniumTransport.h++"
#include "MACE/Simulation/Physics/TargetForMuoniumPhysics.h++"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"
#include "G4UImessenger.hh"

#include "gsl/gsl"

#include <memory>

namespace MACE::inline Simulation::inline Physics {

inline namespace Process {

template<TargetForMuoniumPhysics ATarget>
class MuoniumFormation;

template<TargetForMuoniumPhysics ATarget>
class MuoniumTransport;

} // namespace Process

template<TargetForMuoniumPhysics ATarget>
class MuoniumPhysicsMessenger final : public Env::Memory::Singleton<MuoniumPhysicsMessenger<ATarget>>,
                                      public G4UImessenger {
    friend Env::Memory::SingletonInstantiator;

private:
    MuoniumPhysicsMessenger();

public:
    auto AssignTo(gsl::not_null<MuoniumFormation<ATarget>*> mf) -> void { fMuoniumFormation = mf; }
    auto AssignTo(gsl::not_null<MuoniumTransport<ATarget>*> mt) -> void { fMuoniumTransport = mt; }

    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    MuoniumFormation<ATarget>* fMuoniumFormation;
    MuoniumTransport<ATarget>* fMuoniumTransport;

    std::unique_ptr<G4UIdirectory> fMuoniumPhysicsDirectory;

    std::unique_ptr<G4UIdirectory> fFormationProcessDirectory;
    std::unique_ptr<G4UIcmdWithADouble> fFormationProbability;
    std::unique_ptr<G4UIcmdWithADouble> fConversionProbability;

    std::unique_ptr<G4UIdirectory> fTransportProcessDirectory;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fMeanFreePath;
    std::unique_ptr<G4UIcmdWithABool> fManipulateAllSteps;
};

} // namespace MACE::inline Simulation::inline Physics

#include "MACE/Simulation/Physics/MuoniumPhysicsMessenger.inl"
