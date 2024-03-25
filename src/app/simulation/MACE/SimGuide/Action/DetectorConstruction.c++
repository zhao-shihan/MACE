#include "MACE/Detector/Description/AcceleratorField.h++"
#include "MACE/Detector/Description/Collimator.h++"
#include "MACE/Detector/Description/DescriptionIO.h++"
#include "MACE/Detector/Description/EMCField.h++"
#include "MACE/Detector/Description/EMCShield.h++"
#include "MACE/Detector/Description/MCP.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Detector/Description/MMSMagnet.h++"
#include "MACE/Detector/Description/MMSShield.h++"
#include "MACE/Detector/Description/Solenoid.h++"
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
    fMMSField{},
    fMMSMagnet{},
    fMMSShield{},
    fSolenoidB2Field{},
    fSolenoidB2{},
    fSolenoidS2Field{},
    fSolenoidS2{},
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
