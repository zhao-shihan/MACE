#include "MACE/Detector/Definition/MMSField.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "Mustard/Utility/MathConstant.h++"

#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Definition {

using namespace Mustard::MathConstant;

auto MMSField::Construct(G4bool checkOverlaps) -> void {
    const auto& description = Description::MMSField::Instance();
    auto name = description.Name();
    auto length = description.Length();
    auto radius = description.Radius();

    auto solid = Make<G4Tubs>(
        name,
        0,
        radius,
        length / 2,
        0,
        2 * pi);
    auto logic = Make<G4LogicalVolume>(
        solid,
        nullptr,
        name);
    Make<G4PVPlacement>(
        G4Transform3D(),
        logic,
        name,
        Mother().LogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Definition
