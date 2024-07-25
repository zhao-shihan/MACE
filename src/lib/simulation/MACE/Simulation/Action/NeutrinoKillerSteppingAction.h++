#pragma once

#include "MACE/Simulation/Action/NeutrinoKillerMessenger.h++"

#include "Mustard/Env/Memory/PassiveSingleton.h++"

#include "G4ParticleDefinition.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4TrackStatus.hh"
#include "G4UserSteppingAction.hh"

#include "muc/math"

namespace MACE::inline Simulation::inline Action {

template<typename ADerived = void>
class NeutrinoKillerSteppingAction : public Mustard::Env::Memory::PassiveSingleton<ADerived>,
                                     public G4UserSteppingAction {
public:
    NeutrinoKillerSteppingAction();

    auto EnableNeutrinoKiller(bool val) { fEnableNeutrinoKiller = val; }

    auto UserSteppingAction(const G4Step* step) -> void override final;

private:
    virtual auto SteppingActionForNeutrino(const G4Step& step) -> void {}
    virtual auto SteppingActionWithoutNeutrino(const G4Step& step) -> void = 0;

private:
    bool fEnableNeutrinoKiller;

    NeutrinoKillerMessenger<ADerived>::template Register<ADerived> fMessengerRegister;
};

template<>
class NeutrinoKillerSteppingAction<void> final : public NeutrinoKillerSteppingAction<NeutrinoKillerSteppingAction<void>> {
private:
    auto SteppingActionWithoutNeutrino(const G4Step&) -> void override {}
};

} // namespace MACE::inline Simulation::inline Action

#include "MACE/Simulation/Action/NeutrinoKillerSteppingAction.inl"
