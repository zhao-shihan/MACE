#include "G4Tubs.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfCalorimeterField/Calorimeter.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfCalorimeterField/Calorimeter.hxx"

using namespace MACE::Geometry::Entity::Fast;

void Calorimeter::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::Calorimeter::Instance();
    const auto name = description.GetName();
    const auto innerRadius = description.GetInnerRadius();
    const auto outerRadius = description.GetOuterRadius();
    const auto length = description.GetLength();

    auto material = G4NistManager::Instance()->FindOrBuildMaterial("G4_CESIUM_IODIDE");

    auto solid = Make<G4Tubs>(
        name,
        innerRadius,
        outerRadius,
        length / 2,
        0,
        2 * M_PI);
    auto logic = Make<G4LogicalVolume>(
        solid,
        material,
        name);
    auto physics = Make<G4PVPlacement>(
        G4Transform3D(),
        name,
        logic,
        Mother()->GetPhysicalVolume(),
        false,
        0,
        checkOverlaps);
}
