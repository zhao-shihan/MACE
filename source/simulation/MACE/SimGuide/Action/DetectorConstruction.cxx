#include "MACE/Detector/Description/Collimator.hxx"
#include "MACE/Detector/Description/EMCalField.hxx"
#include "MACE/Detector/Description/EMCalShield.hxx"
#include "MACE/Detector/Description/LinacField.hxx"
#include "MACE/Detector/Description/MCP.hxx"
#include "MACE/Detector/Description/SelectorField.hxx"
#include "MACE/Detector/Description/SpectrometerField.hxx"
#include "MACE/Detector/Description/SpectrometerMagnet.hxx"
#include "MACE/Detector/Description/SpectrometerShield.hxx"
#include "MACE/Detector/Description/TransportLine.hxx"
#include "MACE/Detector/Description/World.hxx"
#include "MACE/Detector/DescriptionIO.hxx"
#include "MACE/SimGuide/Action/DetectorConstruction.hxx"

namespace MACE::SimTarget::Action {

DetectorConstruction::DetectorConstruction() :
    fCollimator(nullptr),
    fEMCalField(nullptr),
    fEMCalShield(nullptr),
    fFirstBendField(nullptr),
    fFirstBendSolenoid(nullptr),
    fFirstTransportField(nullptr),
    fFirstTransportSolenoid(nullptr),
    fLinacField(nullptr),
    fMCP(nullptr),
    fSecondBendField(nullptr),
    fSecondBendSolenoid(nullptr),
    fSecondTransportField(nullptr),
    fSecondTransportSolenoid(nullptr),
    fSelectorField(nullptr),
    fSpectrometerField(nullptr),
    fSpectrometerMagnet(nullptr),
    fSpectrometerShield(nullptr),
    fThirdTransportField(nullptr),
    fThirdTransportSolenoid(nullptr),
    fWorld(nullptr) {
    Detector::DescriptionIO::Import<UsedDescriptions>(std::array{
#include "MACE/SimGuide/DefaultGeometry.inlyaml"
    });
}

G4VPhysicalVolume* DetectorConstruction::Construct() {
}

} // namespace MACE::SimTarget::Action
