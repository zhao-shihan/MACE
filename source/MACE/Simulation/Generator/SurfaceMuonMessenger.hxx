#pragma once

#include "MACE/Simulation/Generator/SurfaceMuon.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"
#include "G4UImessenger.hh"

namespace MACE::Simulation::Generator {

using Utility::ObserverPtr;

class SurfaceMuonMessenger final : public G4UImessenger {
public:
    static SurfaceMuonMessenger& Instance();

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

} // namespace MACE::Simulation::Generator
