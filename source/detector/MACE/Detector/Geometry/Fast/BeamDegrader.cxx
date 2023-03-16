#include "MACE/Detector/Description/BeamDegrader.hxx"
#include "MACE/Detector/Geometry/Fast/BeamDegrader.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

namespace MACE::Detector::Geometry::Fast {

using namespace MACE::LiteralUnit::Density;

bool BeamDegrader::Enabled() const {
    return Description::BeamDegrader::Instance().Enabled();
}

void BeamDegrader::Construct(G4bool checkOverlaps) {
    const auto& description = Description::BeamDegrader::Instance();
    const auto name = description.GetName();
    const auto width = description.Width();
    const auto thickness = description.Thickness();
    const auto transform = description.CalcTransform();

    auto solid = Make<G4Box>(
        name,
        width / 2,
        width / 2,
        thickness / 2);
    auto logic = Make<G4LogicalVolume>(
        solid,
        nullptr,
        name);
    Make<G4PVPlacement>(
        transform,
        logic,
        name,
        Mother().LogicalVolume().get(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Geometry::Fast
