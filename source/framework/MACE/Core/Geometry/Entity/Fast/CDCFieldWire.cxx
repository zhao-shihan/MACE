#include "MACE/Core/Geometry/Description/CDC.hxx"
#include "MACE/Core/Geometry/Entity/Fast/CDCFieldWire.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

#include "gsl/gsl"

namespace MACE::Core::Geometry::Entity::Fast {

using namespace MACE::Utility::PhysicalConstant;

void CDCFieldWire::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::CDC::Instance();
    const auto name = "CDCFieldWire";
    const auto rFieldWire = description.FieldWireDiameter() / 2;
    const auto detail = description.FieldWireGeometryDetail();
    const auto layerCount = detail.size();

    for (gsl::index layerID = 0; layerID < layerCount; ++layerID) {
        auto&& [halfLength, positionList] = detail[layerID];
        auto solid = Make<G4Tubs>(
            name,
            0,
            rFieldWire,
            halfLength,
            0,
            twopi);
        auto logic = Make<G4LogicalVolume>(
            solid,
            nullptr,
            name);
        for (gsl::index wireID = 0; wireID < positionList.size(); ++wireID) {
            Make<G4PVPlacement>(
                G4Transform3D(
                    G4RotationMatrix(),
                    positionList[wireID]),
                logic,
                name,
                Mother()->LogicalVolume(layerID),
                false,
                wireID,
                checkOverlaps);
        }
    }
}

} // namespace MACE::Core::Geometry::Entity::Fast
