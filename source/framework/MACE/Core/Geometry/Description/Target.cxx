#include "MACE/Core/Geometry/Description/LinacField.hxx"
#include "MACE/Core/Geometry/Description/Target.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "CLHEP/Vector/Rotation.h"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

Target::Target() :
    ISingletonDescription<Target>(__func__),
    fShapeType(ShapeType::Cuboid),
    fCuboid() {}

void Target::ImportValues(const YAML::Node& node) {
    ImportValue<std::string>(
        node, [this](auto&& shape) {
            if (shape == "Cuboid") {
                fShapeType = ShapeType::Cuboid;
            } else {
                MACE_ENVIRONMENT_CONTROLLED_OUT(Warning, std::cout)
                    << "MACE::Core::Geometry::Description::Target::ImportValues: Unknown target shape \"" << shape << "\", skipping" << std::endl;
            }
        },
        "ShapeType");
    {
        ImportValue<double>(
            node, [this](auto value) { fCuboid.SetWidth(value); },
            "Cuboid", "Width");
        ImportValue<double>(
            node, [this](auto value) { fCuboid.SetThickness(value); },
            "Cuboid", "Thickness");
        ImportValue<std::string>(
            node, [this](auto&& detail) {
                if (detail == "Flat") {
                    fCuboid.SetDetailType(Cuboid::DetailType::Flat);
                } else if (detail == "Hole") {
                    fCuboid.SetDetailType(Cuboid::DetailType::Hole);
                } else {
                    MACE_ENVIRONMENT_CONTROLLED_OUT(Warning, std::cout)
                        << "MACE::Core::Geometry::Description::Target::ImportValues: Unknown cuboid target detail \"" << detail << "\", skipping" << std::endl;
                }
            },
            "Cuboid", "DetailType");
        {
            ImportValue<double>(
                node, [this](auto value) { fCuboid.GetHole().SetExtent(value); },
                "Cuboid", "Hole", "AblationExtent");
            ImportValue<double>(
                node, [this](auto value) { fCuboid.GetHole().SetSpacing(value); },
                "Cuboid", "Hole", "Spacing");
            ImportValue<double>(
                node, [this](auto value) { fCuboid.GetHole().SetDiameter(value); },
                "Cuboid", "Hole", "Diameter");
            ImportValue<double>(
                node, [this](auto value) { fCuboid.GetHole().SetDepth(value); },
                "Cuboid", "Hole", "Depth");
        }
    }
}

void Target::ExportValues(YAML::Node& node) const {
    std::string shapeString;
    switch (fShapeType) {
    case ShapeType::Cuboid:
        shapeString = "Cuboid";
        break;
    }
    ExportValue(node, shapeString, "ShapeType");
    {
        ExportValue(node, fCuboid.GetWidth(), "Cuboid", "Width");
        ExportValue(node, fCuboid.GetThickness(), "Cuboid", "Thickness");
        std::string detailString;
        switch (fCuboid.GetDetailType()) {
        case Cuboid::DetailType::Flat:
            detailString = "Flat";
            break;
        case Cuboid::DetailType::Hole:
            detailString = "Hole";
            break;
        }
        ExportValue(node, detailString, "Cuboid", "DetailType");
        {
            ExportValue(node, fCuboid.GetHole().GetExtent(), "Cuboid", "Hole", "AblationExtent");
            ExportValue(node, fCuboid.GetHole().GetSpacing(), "Cuboid", "Hole", "Spacing");
            ExportValue(node, fCuboid.GetHole().GetDiameter(), "Cuboid", "Hole", "Diameter");
            ExportValue(node, fCuboid.GetHole().GetDepth(), "Cuboid", "Hole", "Depth");
        }
    }
}

Target::Cuboid::Cuboid() :
    fWidth(6_cm),
    fThickness(1_cm),
    fDetailType(DetailType::Hole),
    fHole() {}

HepGeom::Transform3D Target::Cuboid::CalcTransform() const {
    const auto& linacField = LinacField::Instance();
    const auto transZ = linacField.GetLength() / 2 - linacField.GetDownStreamLength() - fThickness / 2;
    return HepGeom::Transform3D(CLHEP::HepRotation(), CLHEP::Hep3Vector(0, 0, transZ));
}

Target::Cuboid::Hole::Hole() :
    DetailBase<Hole>(),
    fHalfExtent(4_cm / 2),
    fSpacing(175_um),
    fRadius(49.5_um / 2),
    fDepth(3_mm),
    fPitch(fSpacing + 2 * fRadius) {}

void Target::Cuboid::Hole::SetSpacing(double spacing) {
    fSpacing = spacing;
    fPitch = spacing + 2 * fRadius;
}

void Target::Cuboid::Hole::SetDiameter(double diameter) {
    fRadius = diameter / 2;
    fPitch = fSpacing + diameter;
}

} // namespace MACE::Core::Geometry::Description
