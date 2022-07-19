#pragma once

#include "MACE/Environment/Resource/Singleton.hxx"
#include "MACE/SimulationG4/Generator/SurfaceMuon.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"
#include "G4UImessenger.hh"

namespace MACE::SimulationG4::Generator {

using Utility::ObserverPtr;

class SurfaceMuonMessenger final : public Environment::Resource::Singleton<SurfaceMuonMessenger>,
                                   public G4UImessenger {
    friend Environment::Resource::SingletonFactory;

private:
    SurfaceMuonMessenger();
    ~SurfaceMuonMessenger() noexcept = default;
    SurfaceMuonMessenger(const SurfaceMuonMessenger&) = delete;
    SurfaceMuonMessenger& operator=(const SurfaceMuonMessenger&) = delete;

public:
    void SetTo(ObserverPtr<SurfaceMuon> gen) { fSurfaceMuonGenerator = gen; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    ObserverPtr<SurfaceMuon> fSurfaceMuonGenerator;

    G4UIdirectory fDirectory;
    G4UIcmdWithADoubleAndUnit fSetMomentum;
    G4UIcmdWithADoubleAndUnit fSetMomentumSpreadRMS;
    G4UIcmdWithADoubleAndUnit fSetBeamProfileRMS;
    G4UIcmdWithADoubleAndUnit fSetVertexZ;
};

} // namespace MACE::SimulationG4::Generator
