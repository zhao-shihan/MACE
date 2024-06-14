#pragma once

#include "MACE/Env/Print.h++"
#include "MACE/Extension/Geant4X/Particle/Antimuonium.h++"
#include "MACE/Extension/Geant4X/Particle/Muonium.h++"
#include "MACE/Extension/Geant4X/Physics/MuoniumPhysicsMessenger.h++"
#include "MACE/Extension/Geant4X/Physics/TargetForMuoniumPhysics.h++"
#include "MACE/Math/QinAlgorithm.h++"
#include "MACE/Utility/LiteralUnit.h++"
#include "MACE/Utility/NonMoveableBase.h++"
#include "MACE/Utility/PhysicalConstant.h++"

#include "G4MuonPlus.hh"
#include "G4ParticleChange.hh"
#include "G4VRestProcess.hh"
#include "Randomize.hh"

#include "muc/math"
#include "muc/numeric"

#include "gsl/gsl"

#include <limits>

namespace MACE::inline Extension::Geant4X::inline Process {

template<TargetForMuoniumPhysics ATarget>
class MuoniumFormation final : public NonMoveableBase,
                               public G4VRestProcess {
public:
    MuoniumFormation();

    auto ConversionProbability(G4double p) -> void { fConversionProbability = muc::clamp<"[]">(p, 0., 1.); }

    auto IsApplicable(const G4ParticleDefinition&) -> G4bool override;
    auto AtRestDoIt(const G4Track& track, const G4Step&) -> G4VParticleChange* override;

private:
    auto GetMeanLifeTime(const G4Track& track, G4ForceCondition*) -> G4double override;

private:
    G4double fConversionProbability;

    G4ParticleChange fParticleChange;

    typename MuoniumPhysicsMessenger<ATarget>::template Register<MuoniumFormation<ATarget>> fMessengerRegister;
};

} // namespace MACE::inline Extension::Geant4X::inline Process

#include "MACE/Extension/Geant4X/Process/MuoniumFormation.inl"
