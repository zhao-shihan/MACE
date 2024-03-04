#include "MACE/Detector/Definition/Target.h++"
#include "MACE/Detector/Description/AcceleratorField.h++"
#include "MACE/Detector/Description/Target.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

namespace MACE::Detector::Definition {

using namespace MACE::LiteralUnit::Density;

auto Target::Construct(G4bool checkOverlaps) -> void {
    const auto& target{Description::Target::Instance()};
    const auto& acceleratorField{Description::AcceleratorField::Instance()};

    const auto nist{G4NistManager::Instance()}; // clang-format off
    const auto silicaAerogel{new G4Material{"Aerogel", target.SilicaAerogelDensity(), 3, kStateSolid, target.EffectiveTemperature()}}; // clang-format on
    silicaAerogel->AddMaterial(nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE"), 0.625);
    silicaAerogel->AddMaterial(nist->FindOrBuildMaterial("G4_WATER"), 0.374);
    silicaAerogel->AddElement(nist->FindOrBuildElement("C"), 0.001);

    switch (const auto z0{acceleratorField.Length() / 2 - acceleratorField.DownStreamLength()};
            target.ShapeType()) {
    case Description::Target::TargetShapeType::Cuboid: {
        const auto& cuboid{target.Cuboid()};
        const auto solid{Make<G4Box>(
            target.Name(),
            cuboid.Width() / 2,
            cuboid.Width() / 2,
            cuboid.Thickness() / 2)};
        const auto logic{Make<G4LogicalVolume>(
            solid,
            silicaAerogel,
            target.Name())};
        Make<G4PVPlacement>( // clang-format off
            G4Transform3D{{}, {0, 0, z0 - cuboid.Thickness() / 2}}, // clang-format on
            logic,
            target.Name(),
            Mother().LogicalVolume().get(),
            false,
            0,
            checkOverlaps);
        return;
    }
    case Description::Target::TargetShapeType::MultiLayer: {
        const auto& multiLayer{target.MultiLayer()};
        const auto solid{Make<G4Box>(
            target.Name(),
            multiLayer.Thickness() / 2,
            multiLayer.Height() / 2,
            multiLayer.Width() / 2)};
        const auto logic{Make<G4LogicalVolume>(
            solid,
            silicaAerogel,
            target.Name())};
        const auto r{multiLayer.Spacing() + multiLayer.Thickness()};
        for (int k{}; k < multiLayer.Count(); ++k) {
            Make<G4PVPlacement>( // clang-format off
                G4Transform3D{{}, {k * r - r * (multiLayer.Count() - 1) / 2, 0, z0}}, // clang-format on
                logic,
                target.Name(),
                Mother().LogicalVolume().get(),
                false,
                k,
                checkOverlaps);
        }
    }
    }
}

} // namespace MACE::Detector::Definition
