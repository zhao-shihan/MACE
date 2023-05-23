#include "MACE/Detector/Description/Collimator.hxx"
#include "MACE/Detector/Description/EMCalField.hxx"
#include "MACE/Detector/Description/EMCalShield.hxx"
#include "MACE/Detector/Description/AcceleratorField.hxx"
#include "MACE/Detector/Description/MCP.hxx"
#include "MACE/Detector/Description/SelectorField.hxx"
#include "MACE/Detector/Description/SpectrometerField.hxx"
#include "MACE/Detector/Description/SpectrometerMagnet.hxx"
#include "MACE/Detector/Description/SpectrometerShield.hxx"
#include "MACE/Detector/Description/Solenoid.hxx"
#include "MACE/Detector/Description/World.hxx"
#include "MACE/Detector/Description/DescriptionIO.hxx"
#include "MACE/SimGuide/Action/DetectorConstruction.hxx"

namespace MACE::SimTarget::inline Action {

DetectorConstruction::DetectorConstruction() :
    fCollimator(nullptr),
    fEMCalField(nullptr),
    fEMCalShield(nullptr),
    fSolenoidB1Field(nullptr),
    fSolenoidB1(nullptr),
    fSolenoidS1Field(nullptr),
    fSolenoidS1(nullptr),
    fAcceleratorField(nullptr),
    fMCP(nullptr),
    fSolenoidB2Field(nullptr),
    fSolenoidB2(nullptr),
    fSolenoidS2Field(nullptr),
    fSolenoidS2(nullptr),
    fSelectorField(nullptr),
    fSpectrometerField(nullptr),
    fSpectrometerMagnet(nullptr),
    fSpectrometerShield(nullptr),
    fSolenoidS3Field(nullptr),
    fSolenoidS3(nullptr),
    fWorld(nullptr) {
    Detector::DescriptionIO::Import<UsedDescriptions>(std::array{
#include "MACE/SimGuide/DefaultGeometry.inlyaml"
    });
}

G4VPhysicalVolume* DetectorConstruction::Construct() {
}

} // namespace MACE::SimTarget::inline Action
