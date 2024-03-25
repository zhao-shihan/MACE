#pragma once

#include "MACE/Detector/Description/CDC.h++"
#include "MACE/Detector/Description/MMSBeamPipe.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Detector/Description/MMSMagnet.h++"
#include "MACE/Detector/Description/MMSShield.h++"
#include "MACE/Detector/Description/STC.h++"
#include "MACE/Detector/Description/World.h++"
#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/SimMMS/Region.h++"

#include "G4VUserDetectorConstruction.hh"

#include <memory>

namespace MACE {

namespace Detector::Definition {
class DefinitionBase;
} // namespace Detector::Definition

namespace SimMMS {

inline namespace SD {
class CDCSD;
class STCSD;
} // namespace SD

inline namespace Action {

class DetectorConstruction final : public Env::Memory::PassiveSingleton<DetectorConstruction>,
                                   public G4VUserDetectorConstruction {
public:
    DetectorConstruction();

    auto Construct() -> G4VPhysicalVolume* override;

    auto SetCheckOverlaps(G4bool checkOverlaps) -> void { fCheckOverlap = checkOverlaps; }

    auto CDCSensitiveRegion() const -> const auto& { return *fCDCSensitiveRegion; }
    auto DefaultGaseousRegion() const -> const auto& { return *fDefaultGaseousRegion; }
    auto DefaultSolidRegion() const -> const auto& { return *fDefaultSolidRegion; }
    auto ShieldRegion() const -> const auto& { return *fShieldRegion; }
    auto SolenoidOrMagnetRegion() const -> const auto& { return *fSolenoidOrMagnetRegion; }
    auto TargetRegion() const -> const auto& { return *fTargetRegion; }
    auto STCSensitiveRegion() const -> const auto& { return *fSTCSensitiveRegion; }
    auto VacuumRegion() const -> const auto& { return *fVacuumRegion; }

    auto CDCSD() const -> auto& { return *fCDCSD; }
    auto STCSD() const -> auto& { return *fSTCSD; }

public:
    using DescriptionInUse = std::tuple<Detector::Description::CDC,
                                        Detector::Description::MMSBeamPipe,
                                        Detector::Description::MMSField,
                                        Detector::Description::MMSMagnet,
                                        Detector::Description::MMSShield,
                                        Detector::Description::STC,
                                        Detector::Description::World>;

private:
    G4bool fCheckOverlap;

    std::unique_ptr<Detector::Definition::DefinitionBase> fWorld;

    Region* fCDCFieldWireRegion;
    Region* fCDCSenseWireRegion;
    Region* fCDCSensitiveRegion;
    Region* fDefaultGaseousRegion;
    Region* fDefaultSolidRegion;
    Region* fShieldRegion;
    Region* fSolenoidOrMagnetRegion;
    Region* fSTCSensitiveRegion;
    Region* fTargetRegion;
    Region* fVacuumRegion;

    SD::CDCSD* fCDCSD;
    SD::STCSD* fSTCSD;
};

} // namespace Action

} // namespace SimMMS

} // namespace MACE
