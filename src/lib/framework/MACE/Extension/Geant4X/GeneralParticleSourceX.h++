#pragma once

#include "MACE/Extension/Geant4X/GeneralParticleSourceXMessenger.h++"

#include "G4GeneralParticleSource.hh"

namespace MACE::inline Extension::Geant4X {

class GeneralParticleSourceX : public G4GeneralParticleSource {
public:
    GeneralParticleSourceX();

    auto PulseWidth() const -> auto { return fPulseWidth; }
    auto PulseWidth(double val) -> void { fPulseWidth = val; }

    auto GeneratePrimaryVertex(G4Event*) -> void override;

private:
    double fPulseWidth;

    GeneralParticleSourceXMessenger::Register<GeneralParticleSourceX> fMessengerRegister;
};

} // namespace MACE::inline Extension::Geant4X
