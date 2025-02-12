#pragma once

#include "MACE/Detector/Description/PDSVeto.h++"
// #include "MACE/SimECAL/SD/ECALPMSD.h++"
// #include "MACE/SimECAL/SD/ECALSD.h++"
// #include "MACE/SimECAL/SD/MCPSD.h++"

#include "Mustard/Env/Memory/PassiveSingleton.h++"

#include "G4VUserDetectorConstruction.hh"

#include <memory>
#include <tuple>

namespace Mustard::Detector::Definition {
class DefinitionBase;
} // namespace Mustard::Detector::Definition

namespace MACE {

namespace SimVeto::inline Action {

class DetectorConstruction final : public Mustard::Env::Memory::PassiveSingleton<DetectorConstruction>,
                                   public G4VUserDetectorConstruction {
public:
    DetectorConstruction();

    auto Construct() -> G4VPhysicalVolume* override;

    auto SetCheckOverlaps(G4bool checkOverlaps) -> void { fCheckOverlap = checkOverlaps; }

public:
    using DescriptionInUse = std::tuple<MACE::Detector::Description::PDSVeto>;

private:
    G4bool fCheckOverlap;

    std::unique_ptr<Mustard::Detector::Definition::DefinitionBase> fWorld;
};

} // namespace SimVeto::inline Action

} // namespace MACE
