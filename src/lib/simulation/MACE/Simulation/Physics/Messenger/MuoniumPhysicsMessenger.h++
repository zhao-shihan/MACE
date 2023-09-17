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

namespace MACE::inline Simulation::Physics {

inline namespace Process {

template<TargetForMuoniumPhysics ATarget>
class MuoniumFormation;

template<TargetForMuoniumPhysics ATarget>
class MuoniumTransport;

} // inline namespace Process

inline namespace Messenger {

template<TargetForMuoniumPhysics ATarget>
class MuoniumPhysicsMessenger final : public Env::Memory::Singleton<MuoniumPhysicsMessenger<ATarget>>,
                                      public G4UImessenger {
    friend Env::Memory::SingletonFactory;

private:
    MuoniumPhysicsMessenger();

public:
    void AssignTo(gsl::not_null<MuoniumFormation<ATarget>*> mf) { fMuoniumFormation = mf; }
    void AssignTo(gsl::not_null<MuoniumTransport<ATarget>*> mt) { fMuoniumTransport = mt; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

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

} // inline namespace Messenger

} // namespace MACE::inline Simulation::Physics

#include "MACE/Simulation/Physics/Messenger/MuoniumPhysicsMessenger.inl"
