#include "MACE/Core/Geometry/Description/Collimator.hxx"
#include "MACE/Core/Geometry/Description/EMCalField.hxx"
#include "MACE/Core/Geometry/Description/EMCalShield.hxx"
#include "MACE/Core/Geometry/Description/LinacField.hxx"
#include "MACE/Core/Geometry/Description/MCP.hxx"
#include "MACE/Core/Geometry/Description/SelectorField.hxx"
#include "MACE/Core/Geometry/Description/SpectrometerField.hxx"
#include "MACE/Core/Geometry/Description/SpectrometerMagnet.hxx"
#include "MACE/Core/Geometry/Description/SpectrometerShield.hxx"
#include "MACE/Core/Geometry/Description/TransportLine.hxx"
#include "MACE/Core/Geometry/Description/World.hxx"
#include "MACE/Core/Geometry/DescriptionIO.hxx"
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
    Core::Geometry::DescriptionIO::Import<UsedDescriptions>(std::array{
#include "MACE/SimGuide/DefaultGeometry.inlyaml"
    });
}

G4VPhysicalVolume* DetectorConstruction::Construct() {
}

} // namespace MACE::SimTarget::Action
