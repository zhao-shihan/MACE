#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"

#include "G4VUserDetectorConstruction.hh"

#include <memory>
#include <tuple>

namespace MACE {

namespace Detector {

namespace Description {

class Collimator;
class EMCField;
class EMCShield;
class AcceleratorField;
class MCP;
class MMSField;
class MMSMagnet;
class MMSShield;
class Solenoid;
class World;

} // namespace Description

class DefinitionBase;

} // namespace Detector

namespace SimTarget::inline Action {

class DetectorConstruction final : public Env::Memory::PassiveSingleton<DetectorConstruction>,
                                   public G4VUserDetectorConstruction {
public:
    DetectorConstruction();

    G4VPhysicalVolume* Construct() override;

    void SetCheckOverlaps(G4bool checkOverlaps) { fCheckOverlap = checkOverlaps; }

public:
    using UsedDescriptions = std::tuple<Detector::Description::Collimator,
                                        Detector::Description::EMCField,
                                        Detector::Description::EMCShield,
                                        Detector::Description::AcceleratorField,
                                        Detector::Description::MCP,
                                        Detector::Description::MMSField,
                                        Detector::Description::MMSMagnet,
                                        Detector::Description::MMSShield,
                                        Detector::Description::Solenoid,
                                        Detector::Description::World>;

private:
    G4bool fCheckOverlap;

    std::shared_ptr<Detector::DefinitionBase> fCollimator;
    std::shared_ptr<Detector::DefinitionBase> fEMCField;
    std::shared_ptr<Detector::DefinitionBase> fEMCShield;
    std::shared_ptr<Detector::DefinitionBase> fSolenoidB1Field;
    std::shared_ptr<Detector::DefinitionBase> fSolenoidB1;
    std::shared_ptr<Detector::DefinitionBase> fSolenoidS1Field;
    std::shared_ptr<Detector::DefinitionBase> fSolenoidS1;
    std::shared_ptr<Detector::DefinitionBase> fAcceleratorField;
    std::shared_ptr<Detector::DefinitionBase> fMCP;
    std::shared_ptr<Detector::DefinitionBase> fMMSField;
    std::shared_ptr<Detector::DefinitionBase> fMMSMagnet;
    std::shared_ptr<Detector::DefinitionBase> fMMSShield;
    std::shared_ptr<Detector::DefinitionBase> fSolenoidB2Field;
    std::shared_ptr<Detector::DefinitionBase> fSolenoidB2;
    std::shared_ptr<Detector::DefinitionBase> fSolenoidS2Field;
    std::shared_ptr<Detector::DefinitionBase> fSolenoidS2;
    std::shared_ptr<Detector::DefinitionBase> fSolenoidS3Field;
    std::shared_ptr<Detector::DefinitionBase> fSolenoidS3;
    std::shared_ptr<Detector::DefinitionBase> fWorld;
};

} // namespace SimTarget::inline Action

} // namespace MACE
