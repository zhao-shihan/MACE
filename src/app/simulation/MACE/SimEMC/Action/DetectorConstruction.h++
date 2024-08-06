#pragma once

#include "MACE/Detector/Description/EMC.h++"
#include "MACE/Detector/Description/Vacuum.h++"
#include "MACE/Detector/Description/World.h++"
#include "MACE/SimEMC/SD/EMCPMTSD.h++"
#include "MACE/SimEMC/SD/EMCSD.h++"
#include "MACE/SimEMC/SD/MCPSD.h++"

#include "Mustard/Env/Memory/PassiveSingleton.h++"

#include "G4VUserDetectorConstruction.hh"

#include <memory>
#include <tuple>

namespace Mustard::Detector::Definition {
class DefinitionBase;
} // namespace Mustard::Detector::Definition

namespace MACE {

namespace SimEMC::inline Action {

class DetectorConstruction final : public Mustard::Env::Memory::PassiveSingleton<DetectorConstruction>,
                                   public G4VUserDetectorConstruction {
public:
    DetectorConstruction();

    auto Construct() -> G4VPhysicalVolume* override;

    auto SetCheckOverlaps(G4bool checkOverlaps) -> void { fCheckOverlap = checkOverlaps; }

public:
    using DescriptionInUse = std::tuple<MACE::Detector::Description::EMC,
                                        MACE::Detector::Description::Vacuum,
                                        MACE::Detector::Description::World>;

private:
    G4bool fCheckOverlap;

    std::unique_ptr<Mustard::Detector::Definition::DefinitionBase> fWorld;
};

} // namespace SimEMC::inline Action

} // namespace MACE
