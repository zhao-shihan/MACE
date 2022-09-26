#include "MACE/Core/Geometry/Description/LinacField.hxx"
#include "MACE/Core/Geometry/Description/Target.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "CLHEP/Vector/Rotation.h"

#include <string>

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

Target::Target() :
    ISingletonDescription<Target>(__func__),
    fShapeType(TargetShapeType::Cuboid),
    fCuboid() {}

void Target::ImportValues(const YAML::Node& node) {
    ImportValue<std::string>(
        node, [this](auto&& shape) {
            if (shape == "Cuboid") {
                fShapeType = TargetShapeType::Cuboid;
            } else {
                MACE_ENVIRONMENT_CONTROLLED_OUT(Warning, std::cout)
                    << "MACE::Core::Geometry::Description::Target::ImportValues: Unknown target shape \"" << shape << "\", skipping" << std::endl;
            }
        },
        "ShapeType");
    {
        ImportValue<double>(
            node, [this](auto value) { fCuboid.Width(value); },
            "Cuboid", "Width");
        ImportValue<double>(
            node, [this](auto value) { fCuboid.Thickness(value); },
            "Cuboid", "Thickness");
        ImportValue<std::string>(
            node, [this](auto&& detail) {
                if (detail == "Flat") {
                    fCuboid.DetailType(CuboidTarget::ShapeDetailType::Flat);
                } else if (detail == "Hole") {
                    fCuboid.DetailType(CuboidTarget::ShapeDetailType::Hole);
                } else {
                    MACE_ENVIRONMENT_CONTROLLED_OUT(Warning, std::cout)
                        << "MACE::Core::Geometry::Description::Target::ImportValues: Unknown cuboid target detail \"" << detail << "\", skipping" << std::endl;
                }
            },
            "Cuboid", "DetailType");
        {
            ImportValue<double>(
                node, [this](auto value) { fCuboid.Hole().Extent(value); },
                "Cuboid", "Hole", "AblationExtent");
            ImportValue<double>(
                node, [this](auto value) { fCuboid.Hole().Spacing(value); },
                "Cuboid", "Hole", "Spacing");
            ImportValue<double>(
                node, [this](auto value) { fCuboid.Hole().Diameter(value); },
                "Cuboid", "Hole", "Diameter");
            ImportValue<double>(
                node, [this](auto value) { fCuboid.Hole().Depth(value); },
                "Cuboid", "Hole", "Depth");
        }
    }
}

void Target::ExportValues(YAML::Node& node) const {
    using namespace std::string_literals;
    ExportValue(
        node, [this] {
            switch (fShapeType) {
            case TargetShapeType::Cuboid:
                return "Cuboid"s;
            }
        }(),
        "ShapeType");
    {
        ExportValue(node, fCuboid.Width(), "Cuboid", "Width");
        ExportValue(node, fCuboid.Thickness(), "Cuboid", "Thickness");
        ExportValue(
            node, [this] {
                switch (fCuboid.DetailType()) {
                case CuboidTarget::ShapeDetailType::Flat:
                    return "Flat"s;
                case CuboidTarget::ShapeDetailType::Hole:
                    return "Hole"s;
                }
            }(),
            "Cuboid", "DetailType");
        {
            ExportValue(node, fCuboid.Hole().Extent(), "Cuboid", "Hole", "AblationExtent");
            ExportValue(node, fCuboid.Hole().Spacing(), "Cuboid", "Hole", "Spacing");
            ExportValue(node, fCuboid.Hole().Diameter(), "Cuboid", "Hole", "Diameter");
            ExportValue(node, fCuboid.Hole().Depth(), "Cuboid", "Hole", "Depth");
        }
    }
}

Target::CuboidTarget::CuboidTarget() :
    fWidth(6_cm),
    fThickness(1_cm),
    fDetailType(ShapeDetailType::Hole),
    fHole() {}

HepGeom::Transform3D Target::CuboidTarget::CalcTransform() const {
    const auto& linacField = LinacField::Instance();
    const auto transZ = linacField.Length() / 2 - linacField.DownStreamLength() - fThickness / 2;
    return HepGeom::Transform3D(CLHEP::HepRotation(), CLHEP::Hep3Vector(0, 0, transZ));
}

Target::CuboidTarget::HoledCuboid::HoledCuboid() :
    DetailBase<HoledCuboid>(),
    fHalfExtent(4_cm / 2),
    fSpacing(49.5_um),
    fRadius(175_um / 2),
    fDepth(3_mm),
    fPitch(fSpacing + 2 * fRadius) {}

void Target::CuboidTarget::HoledCuboid::Spacing(double spacing) {
    fSpacing = spacing;
    fPitch = spacing + 2 * fRadius;
}

void Target::CuboidTarget::HoledCuboid::Diameter(double diameter) {
    fRadius = diameter / 2;
    fPitch = fSpacing + diameter;
}

} // namespace MACE::Core::Geometry::Description
