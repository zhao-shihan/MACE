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
class SelectorField;
class SpectrometerField;
class SpectrometerMagnet;
class SpectrometerShield;
class Solenoid;
class World;

} // namespace Description

class GeometryBase;

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
                                        Detector::Description::SelectorField,
                                        Detector::Description::SpectrometerField,
                                        Detector::Description::SpectrometerMagnet,
                                        Detector::Description::SpectrometerShield,
                                        Detector::Description::Solenoid,
                                        Detector::Description::World>;

private:
    G4bool fCheckOverlap;

    std::shared_ptr<Detector::GeometryBase> fCollimator;
    std::shared_ptr<Detector::GeometryBase> fEMCField;
    std::shared_ptr<Detector::GeometryBase> fEMCShield;
    std::shared_ptr<Detector::GeometryBase> fSolenoidB1Field;
    std::shared_ptr<Detector::GeometryBase> fSolenoidB1;
    std::shared_ptr<Detector::GeometryBase> fSolenoidS1Field;
    std::shared_ptr<Detector::GeometryBase> fSolenoidS1;
    std::shared_ptr<Detector::GeometryBase> fAcceleratorField;
    std::shared_ptr<Detector::GeometryBase> fMCP;
    std::shared_ptr<Detector::GeometryBase> fSolenoidB2Field;
    std::shared_ptr<Detector::GeometryBase> fSolenoidB2;
    std::shared_ptr<Detector::GeometryBase> fSolenoidS2Field;
    std::shared_ptr<Detector::GeometryBase> fSolenoidS2;
    std::shared_ptr<Detector::GeometryBase> fSelectorField;
    std::shared_ptr<Detector::GeometryBase> fSpectrometerField;
    std::shared_ptr<Detector::GeometryBase> fSpectrometerMagnet;
    std::shared_ptr<Detector::GeometryBase> fSpectrometerShield;
    std::shared_ptr<Detector::GeometryBase> fSolenoidS3Field;
    std::shared_ptr<Detector::GeometryBase> fSolenoidS3;
    std::shared_ptr<Detector::GeometryBase> fWorld;
};

} // namespace SimTarget::inline Action

} // namespace MACE
