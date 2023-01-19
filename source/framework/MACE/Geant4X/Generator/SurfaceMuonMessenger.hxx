#pragma once

#include "MACE/Env/Memory/Singleton.hxx"
#include "MACE/Geant4X/Generator/SurfaceMuon.hxx"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"
#include "G4UImessenger.hh"

#include "gsl/gsl"

namespace MACE::Geant4X::Generator {

class SurfaceMuonMessenger final : public Env::Memory::Singleton<SurfaceMuonMessenger>,
                                   public G4UImessenger {
    friend Env::Memory::SingletonFactory;

private:
    SurfaceMuonMessenger();
    ~SurfaceMuonMessenger() noexcept = default;
    SurfaceMuonMessenger(const SurfaceMuonMessenger&) = delete;
    SurfaceMuonMessenger& operator=(const SurfaceMuonMessenger&) = delete;

public:
    void AssignTo(gsl::not_null<SurfaceMuon*> gen) { fSurfaceMuonGenerator = gen; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    SurfaceMuon* fSurfaceMuonGenerator;

    G4UIdirectory fDirectory;
    G4UIcmdWithADoubleAndUnit fSetMomentum;
    G4UIcmdWithADoubleAndUnit fSetMomentumSpreadRMS;
    G4UIcmdWithADoubleAndUnit fSetBeamProfileRMS;
    G4UIcmdWithADoubleAndUnit fSetVertexZ;
};

} // namespace MACE::Geant4X::Generator
