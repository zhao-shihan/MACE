#pragma once

#include "MACE/Detector/Assembly/MMS.h++"
#include "MACE/Detector/Description/World.h++"
#include "MACE/SimMMS/Region.h++"
#include "MACE/Simulation/Messenger/NumericMessenger.h++"

#include "Mustard/Env/Memory/PassiveSingleton.h++"

#include "G4VUserDetectorConstruction.hh"

#include "muc/tuple"

#include <memory>

namespace Mustard::Detector::Definition {
class DefinitionBase;
} // namespace Mustard::Detector::Definition

namespace MACE::SimMMS {

inline namespace SD {
class CDCSD;
class TTCSD;
} // namespace SD

inline namespace Action {

class DetectorConstruction final : public Mustard::Env::Memory::PassiveSingleton<DetectorConstruction>,
                                   public G4VUserDetectorConstruction {
public:
    DetectorConstruction();

    auto SetCheckOverlaps(G4bool checkOverlaps) -> void { fCheckOverlap = checkOverlaps; }

    auto MinDriverStep(double val) -> void { fMinDriverStep = val; }
    auto DeltaChord(double val) -> void { fDeltaChord = val; }

    auto Construct() -> G4VPhysicalVolume* override;

    auto CDCSensitiveRegion() const -> const auto& { return *fCDCSensitiveRegion; }
    auto DefaultGaseousRegion() const -> const auto& { return *fDefaultGaseousRegion; }
    auto DefaultSolidRegion() const -> const auto& { return *fDefaultSolidRegion; }
    auto ShieldRegion() const -> const auto& { return *fShieldRegion; }
    auto SolenoidOrMagnetRegion() const -> const auto& { return *fSolenoidOrMagnetRegion; }
    auto TargetRegion() const -> const auto& { return *fTargetRegion; }
    auto TTCSensitiveRegion() const -> const auto& { return *fTTCSensitiveRegion; }
    auto VacuumRegion() const -> const auto& { return *fVacuumRegion; }

    auto CDCSD() const -> auto& { return *fCDCSD; }
    auto TTCSD() const -> auto& { return *fTTCSD; }

public:
    using DescriptionInUse = muc::tuple_concat_t<
        Detector::Assembly::MMS::DescriptionInUse,
        std::tuple<Detector::Description::World>>;

private:
    G4bool fCheckOverlap;

    double fMinDriverStep;
    double fDeltaChord;

    std::unique_ptr<Mustard::Detector::Definition::DefinitionBase> fWorld;

    Region* fCDCFieldWireRegion;
    Region* fCDCSenseWireRegion;
    Region* fCDCSensitiveRegion;
    Region* fDefaultGaseousRegion;
    Region* fDefaultSolidRegion;
    Region* fShieldRegion;
    Region* fSolenoidOrMagnetRegion;
    Region* fTTCSensitiveRegion;
    Region* fTargetRegion;
    Region* fVacuumRegion;

    SD::CDCSD* fCDCSD;
    SD::TTCSD* fTTCSD;

    NumericMessenger<DetectorConstruction>::Register<DetectorConstruction> fNumericMessengerRegister;
};

} // namespace Action

} // namespace MACE::SimMMS
