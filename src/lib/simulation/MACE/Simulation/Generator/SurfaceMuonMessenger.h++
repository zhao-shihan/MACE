#pragma once

#include "MACE/Extension/Geant4X/SingletonMessenger.h++"

#include <memory>

class G4UIcmdWithADoubleAndUnit;
class G4UIdirectory;

namespace MACE::inline Simulation::Generator {

class SurfaceMuon;

class SurfaceMuonMessenger final : public Geant4X::SingletonMessenger<SurfaceMuonMessenger,
                                                                      SurfaceMuon> {
    friend Env::Memory::SingletonInstantiator;

private:
    SurfaceMuonMessenger();
    ~SurfaceMuonMessenger();

public:
    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fMomentum;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fMomentumRMS;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fPositionRMS;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fPositionZ;
};

} // namespace MACE::inline Simulation::Generator
