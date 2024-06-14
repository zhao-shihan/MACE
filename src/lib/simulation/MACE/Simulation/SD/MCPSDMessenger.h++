#pragma once

#include "MACE/Extension/Geant4X/Interface/SingletonMessenger.h++"

#include <memory>

class G4UIcmdWithADoubleAndUnit;
class G4UIdirectory;

namespace MACE::inline Simulation::inline SD {

class MCPSD;

class MCPSDMessenger final : public Geant4X::SingletonMessenger<MCPSDMessenger,
                                                                MCPSD> {
    friend Env::Memory::SingletonInstantiator;

private:
    MCPSDMessenger();
    ~MCPSDMessenger();

public:
    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fIonizingEnergyDepositionThreshold;
};

} // namespace MACE::inline Simulation::inline SD
