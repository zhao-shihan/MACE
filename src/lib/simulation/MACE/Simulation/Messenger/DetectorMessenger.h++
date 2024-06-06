#pragma once

#include "MACE/Detector/Description/DescriptionIO.h++"
#include "MACE/Extension/Geant4X/SingletonMessenger.h++"

#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"
#include "G4VUserDetectorConstruction.hh"

#include "muc/ceta_string"

#include "fmt/format.h"

#include <concepts>
#include <memory>
#include <string_view>

namespace MACE::inline Simulation::inline Messenger {

template<typename ADerived, std::derived_from<G4VUserDetectorConstruction> ADetectorConstruction, muc::ceta_string AAppName = nullptr>
class DetectorMessenger : public Geant4X::SingletonMessenger<ADerived> {
protected:
    DetectorMessenger();

public:
    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithAString> fImportDescription;
    std::unique_ptr<G4UIcmdWithAString> fExportDescription;
    std::unique_ptr<G4UIcmdWithAString> fIxportDescription;
};

} // namespace MACE::inline Simulation::inline Messenger

#include "MACE/Simulation/Messenger/DetectorMessenger.inl"
