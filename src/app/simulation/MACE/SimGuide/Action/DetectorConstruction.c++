#include "MACE/Detector/Description/AcceleratorField.h++"
#include "MACE/Detector/Description/Collimator.h++"
#include "MACE/Detector/Description/DescriptionIO.h++"
#include "MACE/Detector/Description/EMCField.h++"
#include "MACE/Detector/Description/EMCShield.h++"
#include "MACE/Detector/Description/MCP.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Description/SpectrometerField.h++"
#include "MACE/Detector/Description/SpectrometerMagnet.h++"
#include "MACE/Detector/Description/SpectrometerShield.h++"
#include "MACE/Detector/Description/World.h++"
#include "MACE/SimGuide/Action/DetectorConstruction.h++"

namespace MACE::SimTarget::inline Action {

DetectorConstruction::DetectorConstruction() :
    fCollimator{},
    fEMCField{},
    fEMCShield{},
    fSolenoidB1Field{},
    fSolenoidB1{},
    fSolenoidS1Field{},
    fSolenoidS1{},
    fAcceleratorField{},
    fMCP{},
    fSolenoidB2Field{},
    fSolenoidB2{},
    fSolenoidS2Field{},
    fSolenoidS2{},
    fSpectrometerField{},
    fSpectrometerMagnet{},
    fSpectrometerShield{},
    fSolenoidS3Field{},
    fSolenoidS3{},
    fWorld{} {
    Detector::DescriptionIO::Import<UsedDescriptions>(
#include "MACE/SimGuide/DefaultGeometry.inlyaml"
    );
}

auto DetectorConstruction::Construct() -> G4VPhysicalVolume* {
}

} // namespace MACE::SimTarget::inline Action
