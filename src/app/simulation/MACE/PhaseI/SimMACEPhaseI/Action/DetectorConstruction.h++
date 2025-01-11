#pragma once

#include "MACE/Detector/Description/ECAL.h++"
#include "MACE/Detector/Description/Target.h++"
#include "MACE/PhaseI/Detector/Description/CentralBeamPipe.h++"
#include "MACE/PhaseI/Detector/Description/MRPC.h++"
#include "MACE/PhaseI/Detector/Description/World.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Region.h++"
#include "MACE/PhaseI/SimMACEPhaseI/SD/ECALPMSD.h++"
#include "MACE/PhaseI/SimMACEPhaseI/SD/ECALSD.h++"

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
    auto ECALSensitiveRegion() const -> const auto& { return fECALSensitiveRegion; }
    auto ShieldRegion() const -> const auto& { return fShieldRegion; }
    auto TargetRegion() const -> const auto& { return fTargetRegion; }
    auto VacuumRegion() const -> const auto& { return fVacuumRegion; }

    auto ECALSD() const -> auto& { return *fECALSD; }
    auto ECALPMSD() const -> auto& { return *fECALPMSD; }

public:
    using DescriptionInUse = std::tuple<MACE::Detector::Description::ECAL,
                                        PhaseI::Detector::Description::MRPC,
                                        PhaseI::Detector::Description::CentralBeamPipe,
                                        MACE::Detector::Description::Target,
                                        PhaseI::Detector::Description::World>;

private:
    G4bool fCheckOverlap;

    std::unique_ptr<Mustard::Detector::Definition::DefinitionBase> fWorld;

    Region* fDefaultGaseousRegion;
    Region* fDefaultSolidRegion;
    Region* fECALSensitiveRegion;
    Region* fShieldRegion;
    Region* fTargetRegion;
    Region* fVacuumRegion;

    SD::ECALSD* fECALSD;
    SD::ECALPMSD* fECALPMSD;
};

} // namespace PhaseI::SimMACEPhaseI::inline Action

} // namespace MACE
