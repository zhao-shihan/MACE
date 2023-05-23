#include "MACE/Detector/Description/Solenoid.hxx"
#include "MACE/Detector/Geometry/Fast/SolenoidS3.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Geometry::Fast {

using namespace MACE::PhysicalConstant;

void SolenoidS3::Construct(G4bool checkOverlaps) {
    const auto& description = Description::Solenoid::Instance();
    const auto name = "SolenoidS3";
    const auto innerRadius = description.InnerRadius();
    const auto outerRadius = description.OuterRadius();
    const auto length = description.S3Length();

    auto solid = Make<G4Tubs>(
        name,
        innerRadius,
        outerRadius,
        length / 2,
        0,
        twopi);
    auto logic = Make<G4LogicalVolume>(
        solid,
        nullptr,
        name);
    Make<G4PVPlacement>(
        G4Transform3D(),
        logic,
        name,
        Mother().LogicalVolume().get(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Geometry::Fast
