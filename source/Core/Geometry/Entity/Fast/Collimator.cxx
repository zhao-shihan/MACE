#include "Core/Geometry/Description/Collimator.hxx"
#include "Core/Geometry/Entity/Fast/Collimator.hxx"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

using MACE::Core::Geometry::Entity::Fast::Collimator;

void Collimator::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::Collimator::Instance();
    const auto name = description.GetName();
    const auto innerRadius = description.GetInnerRadius();
    const auto outerRadius = description.GetOuterRadius();
    const auto length = description.GetLength();
    const auto thickness = description.GetThickness();
    const auto zPosition = description.GetZPosition();
    const auto count = description.GetCount();

    auto material = G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu");

    for (int i = 0; i < count; ++i) {
        auto radii = innerRadius + i * (outerRadius - innerRadius) / (count - 1);
        auto solid = Make<G4Tubs>(
            name,
            radii,
            radii + thickness,
            length / 2,
            0,
            2 * M_PI);
        auto logic = Make<G4LogicalVolume>(
            solid,
            material,
            name);
        Make<G4PVPlacement>(
            G4Transform3D(
                G4RotationMatrix(),
                G4ThreeVector(0.0, 0.0, zPosition)),
            name,
            logic,
            Mother()->GetPhysicalVolume(),
            false,
            0,
            checkOverlaps);
    }
}
