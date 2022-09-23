#pragma once

#include "MACE/Environment/Memory/Singleton.hxx"
#include "MACE/Geant4X/Generator/SurfaceMuon.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"
#include "G4UImessenger.hh"

namespace MACE::Geant4X::Generator {

using Utility::ObserverPtr;

class SurfaceMuonMessenger final : public Environment::Memory::Singleton<SurfaceMuonMessenger>,
                                   public G4UImessenger {
    friend Environment::Memory::SingletonFactory;

private:
    SurfaceMuonMessenger();
    ~SurfaceMuonMessenger() noexcept = default;
    SurfaceMuonMessenger(const SurfaceMuonMessenger&) = delete;
    SurfaceMuonMessenger& operator=(const SurfaceMuonMessenger&) = delete;

public:
    void AssignTo(ObserverPtr<SurfaceMuon> gen) { fSurfaceMuonGenerator = gen; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    ObserverPtr<SurfaceMuon> fSurfaceMuonGenerator;

    G4UIdirectory fDirectory;
    G4UIcmdWithADoubleAndUnit fSetMomentum;
    G4UIcmdWithADoubleAndUnit fSetMomentumSpreadRMS;
    G4UIcmdWithADoubleAndUnit fSetBeamProfileRMS;
    G4UIcmdWithADoubleAndUnit fSetVertexZ;
};

} // namespace MACE::Geant4X::Generator
