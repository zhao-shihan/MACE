#pragma once

#include "MACE/Detector/Description/EMC.h++"
#include "MACE/Detector/Description/World.h++"
#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Region.h++"
#include "MACE/PhaseI/SimMACEPhaseI/SD/EMCPMTSD.h++"
#include "MACE/PhaseI/SimMACEPhaseI/SD/EMCSD.h++"

#include "G4VUserDetectorConstruction.hh"

#include <memory>
#include <tuple>

namespace MACE {

namespace Detector::Definition {
class DefinitionBase;
} // namespace Detector::Definition

namespace PhaseI::SimMACEPhaseI::inline Action {

class DetectorConstruction final : public Env::Memory::PassiveSingleton<DetectorConstruction>,
                                   public G4VUserDetectorConstruction {
public:
    DetectorConstruction();

    auto Construct() -> G4VPhysicalVolume* override;

    auto SetCheckOverlaps(G4bool checkOverlaps) -> void { fCheckOverlap = checkOverlaps; }

    auto DefaultGaseousRegion() const -> const auto& { return fDefaultGaseousRegion; }
    auto DefaultSolidRegion() const -> const auto& { return fDefaultSolidRegion; }
    auto EMCSensitiveRegion() const -> const auto& { return fEMCSensitiveRegion; }
    auto ShieldRegion() const -> const auto& { return fShieldRegion; }
    auto TargetRegion() const -> const auto& { return fTargetRegion; }
    auto VacuumRegion() const -> const auto& { return fVacuumRegion; }

    auto EMCSD() const -> auto& { return *fEMCSD; }
    auto EMCPMTSD() const -> auto& { return *fEMCPMTSD; }

public:
    using DescriptionInUse = std::tuple<Detector::Description::EMC,
                                        Detector::Description::World>;

private:
    G4bool fCheckOverlap;

    std::unique_ptr<Detector::Definition::DefinitionBase> fWorld;

    Region* fDefaultGaseousRegion;
    Region* fDefaultSolidRegion;
    Region* fEMCSensitiveRegion;
    Region* fShieldRegion;
    Region* fTargetRegion;
    Region* fVacuumRegion;

    SD::EMCSD* fEMCSD;
    SD::EMCPMTSD* fEMCPMTSD;
};

} // namespace SimMACEPhaseI::inline Action

} // namespace MACE
