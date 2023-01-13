#include "MACE/Core/Geometry/Description/CDC.hxx"
#include "MACE/Core/Geometry/Entity/Fast/CDCSenseWire.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

#include "gsl/gsl"

namespace MACE::Core::Geometry::Entity::Fast {

using namespace MACE::Utility::PhysicalConstant;

void CDCSenseWire::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::CDC::Instance();
    const auto name = "CDCSenseWire";
    const auto rSenseWire = description.SenseWireDiameter() / 2;
    const auto detail = description.SenseWireGeometryDetail();
    const auto layerCount = std::ssize(detail);

    for (gsl::index layerID = 0; layerID < layerCount; ++layerID) {
        const auto& [localPositon, halfLength] = detail[layerID];
        auto solid = Make<G4Tubs>(
            name,
            0,
            rSenseWire,
            halfLength,
            0,
            twopi);
        auto logic = Make<G4LogicalVolume>(
            solid,
            nullptr,
            name);
        Make<G4PVPlacement>(
            G4Transform3D(
                G4RotationMatrix(),
                localPositon),
            logic,
            name,
            Mother()->LogicalVolume(layerID),
            false,
            0,
            checkOverlaps);
    }
}

} // namespace MACE::Core::Geometry::Entity::Fast
