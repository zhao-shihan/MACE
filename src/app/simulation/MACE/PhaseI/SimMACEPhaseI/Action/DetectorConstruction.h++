#pragma once

#include "MACE/Detector/Description/ECal.h++"
#include "MACE/PhaseI/Detector/Description/CentralBeamPipe.h++"
#include "MACE/PhaseI/Detector/Description/World.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Region.h++"
#include "MACE/PhaseI/SimMACEPhaseI/SD/ECalPMTSD.h++"
#include "MACE/PhaseI/SimMACEPhaseI/SD/ECalSD.h++"

#include "Mustard/Env/Memory/PassiveSingleton.h++"

#include "G4VUserDetectorConstruction.hh"

#include <memory>
#include <tuple>

namespace Mustard::Detector::Definition {
class DefinitionBase;
} // namespace Mustard::Detector::Definition

namespace MACE {

namespace PhaseI::SimMACEPhaseI::inline Action {

class DetectorConstruction final : public Mustard::Env::Memory::PassiveSingleton<DetectorConstruction>,
                                   public G4VUserDetectorConstruction {
public:
    DetectorConstruction();

    auto Construct() -> G4VPhysicalVolume* override;

    auto SetCheckOverlaps(G4bool checkOverlaps) -> void { fCheckOverlap = checkOverlaps; }

    auto DefaultGaseousRegion() const -> const auto& { return fDefaultGaseousRegion; }
    auto DefaultSolidRegion() const -> const auto& { return fDefaultSolidRegion; }
    auto ECalSensitiveRegion() const -> const auto& { return fECalSensitiveRegion; }
    auto ShieldRegion() const -> const auto& { return fShieldRegion; }
    auto TargetRegion() const -> const auto& { return fTargetRegion; }
    auto VacuumRegion() const -> const auto& { return fVacuumRegion; }

    auto ECalSD() const -> auto& { return *fECalSD; }
    auto ECalPMTSD() const -> auto& { return *fECalPMTSD; }

public:
    using DescriptionInUse = std::tuple<MACE::Detector::Description::ECal,
                                        PhaseI::Detector::Description::CentralBeamPipe,
                                        PhaseI::Detector::Description::World>;

private:
    G4bool fCheckOverlap;

    std::unique_ptr<Mustard::Detector::Definition::DefinitionBase> fWorld;

    Region* fDefaultGaseousRegion;
    Region* fDefaultSolidRegion;
    Region* fECalSensitiveRegion;
    Region* fShieldRegion;
    Region* fTargetRegion;
    Region* fVacuumRegion;

    SD::ECalSD* fECalSD;
    SD::ECalPMTSD* fECalPMTSD;
};

} // namespace PhaseI::SimMACEPhaseI::inline Action

} // namespace MACE
