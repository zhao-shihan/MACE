#include "MACE/Detector/Description/AcceleratorField.h++"
#include "MACE/Detector/Description/Collimator.h++"
#include "MACE/Detector/Description/DescriptionIO.h++"
#include "MACE/Detector/Description/EMCField.h++"
#include "MACE/Detector/Description/EMCShield.h++"
#include "MACE/Detector/Description/MCP.h++"
#include "MACE/Detector/Description/SelectorField.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Description/SpectrometerField.h++"
#include "MACE/Detector/Description/SpectrometerMagnet.h++"
#include "MACE/Detector/Description/SpectrometerShield.h++"
#include "MACE/Detector/Description/World.h++"
#include "MACE/SimGuide/Action/DetectorConstruction.h++"

namespace MACE::SimTarget::inline Action {

DetectorConstruction::DetectorConstruction() :
    fCollimator(nullptr),
    fEMCField(nullptr),
    fEMCShield(nullptr),
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
    Detector::DescriptionIO::Import<UsedDescriptions>(
#include "MACE/SimGuide/DefaultGeometry.inlyaml"
    );
}

auto DetectorConstruction::Construct() -> G4VPhysicalVolume* {
}

} // namespace MACE::SimTarget::inline Action
