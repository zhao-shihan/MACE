#include "MACE/Compatibility/std23/unreachable.h++"
#include "MACE/Detector/Description/AcceleratorField.h++"
#include "MACE/Detector/Description/Target.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "CLHEP/Vector/Rotation.h"

#include "G4Material.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4NistManager.hh"

#include "fmt/format.h"

#include <cstdio>
#include <string>

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;
using namespace LiteralUnit::Density;
using namespace LiteralUnit::Temperature;

Target::Target() :
    DescriptionSingletonBase{"Target"},
    fShapeType{TargetShapeType::MultiLayer},
    fCuboid{},
    fMultiLayer{},
    fSilicaAerogelDensity{27_mg_cm3},
    fEffectiveTemperature{400_K},
    fFormationProbability{0.655},
    fMeanFreePath{200_nm} {}

auto Target::Material() const -> G4Material* {
    constexpr auto materialName{"SilicaAerogel"};
    const auto nist{G4NistManager::Instance()};

    auto silicaAerogel{nist->FindMaterial(materialName)};
    if (silicaAerogel) { return silicaAerogel; }

    silicaAerogel = new G4Material{materialName, fSilicaAerogelDensity, 3, kStateSolid, fEffectiveTemperature};
    silicaAerogel->AddMaterial(nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE"), 0.625);
    silicaAerogel->AddMaterial(nist->FindOrBuildMaterial("G4_WATER"), 0.374);
    silicaAerogel->AddElement(nist->FindOrBuildElement("C"), 0.001);

    const auto mpt{new G4MaterialPropertiesTable};
    mpt->AddConstProperty("MUONIUM_MFP", fMeanFreePath, true);
    mpt->AddConstProperty("MUONIUM_FORM_PROB", fFormationProbability, true);
    silicaAerogel->SetMaterialPropertiesTable(mpt);

    return silicaAerogel;
}

auto Target::ImportValues(const YAML::Node& node) -> void {
    ImportValue<std::string>(
        node, [this](auto&& shape) {
            if (shape == "Cuboid") {
                fShapeType = TargetShapeType::Cuboid;
            } else if (shape == "MultiLayer") {
                fShapeType = TargetShapeType::MultiLayer;
            } else {
                fmt::print(stderr, "MACE::Detector::Description::Target::ImportValues: Unknown target shape \"{}\", skipping", shape);
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
                } else if (detail == "Perforated") {
                    fCuboid.DetailType(CuboidTarget::ShapeDetailType::Perforated);
                } else {
                    fmt::print(stderr, "MACE::Detector::Description::Target::ImportValues: Unknown cuboid target detail \"{}\", skipping", detail);
                }
            },
            "Cuboid", "DetailType");
        {
            ImportValue<double>(
                node, [this](auto value) { fCuboid.Perforated().Extent(value); },
                "Cuboid", "Perforated", "Extent");
            ImportValue<double>(
                node, [this](auto value) { fCuboid.Perforated().Spacing(value); },
                "Cuboid", "Perforated", "Spacing");
            ImportValue<double>(
                node, [this](auto value) { fCuboid.Perforated().Diameter(value); },
                "Cuboid", "Perforated", "Diameter");
            ImportValue<double>(
                node, [this](auto value) { fCuboid.Perforated().Depth(value); },
                "Cuboid", "Perforated", "Depth");
        }
    }
    {
        ImportValue<double>(
            node, [this](auto value) { fMultiLayer.Width(value); },
            "MultiLayer", "Width");
        ImportValue<double>(
            node, [this](auto value) { fMultiLayer.Height(value); },
            "MultiLayer", "Height");
        ImportValue<double>(
            node, [this](auto value) { fMultiLayer.Thickness(value); },
            "MultiLayer", "Thickness");
        ImportValue<double>(
            node, [this](auto value) { fMultiLayer.Spacing(value); },
            "MultiLayer", "Spacing");
        ImportValue<int>(
            node, [this](auto value) { fMultiLayer.Count(value); },
            "MultiLayer", "Count");
        ImportValue<std::string>(
            node, [this](auto&& detail) {
                if (detail == "Flat") {
                    fMultiLayer.DetailType(MultiLayerTarget::ShapeDetailType::Flat);
                } else if (detail == "Perforated") {
                    fMultiLayer.DetailType(MultiLayerTarget::ShapeDetailType::Perforated);
                } else {
                    fmt::print(stderr, "MACE::Detector::Description::Target::ImportValues: Unknown MultiLayer target detail \"{}\", skipping", detail);
                }
            },
            "MultiLayer", "DetailType");
        {
            ImportValue<double>(
                node, [this](auto value) { fMultiLayer.Perforated().ExtentZ(value); },
                "MultiLayer", "Perforated", "ExtentZ");
            ImportValue<double>(
                node, [this](auto value) { fMultiLayer.Perforated().ExtentY(value); },
                "MultiLayer", "Perforated", "ExtentY");
            ImportValue<double>(
                node, [this](auto value) { fMultiLayer.Perforated().Spacing(value); },
                "MultiLayer", "Perforated", "Spacing");
            ImportValue<double>(
                node, [this](auto value) { fMultiLayer.Perforated().Diameter(value); },
                "MultiLayer", "Perforated", "Diameter");
        }
    }
    ImportValue(node, fSilicaAerogelDensity, "SilicaAerogelDensity");
    ImportValue(node, fEffectiveTemperature, "EffectiveTemperature");
    ImportValue(node, fFormationProbability, "FormationProbability");
    ImportValue(node, fMeanFreePath, "MeanFreePath");
}

auto Target::ExportValues(YAML::Node& node) const -> void {
    using namespace std::string_literals;
    ExportValue(
        node, [this] {
            switch (fShapeType) {
            case TargetShapeType::Cuboid:
                return "Cuboid"s;
            case TargetShapeType::MultiLayer:
                return "MultiLayer"s;
            }
            std23::unreachable();
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
                case CuboidTarget::ShapeDetailType::Perforated:
                    return "Perforated"s;
                }
                std23::unreachable();
            }(),
            "Cuboid", "DetailType");
        {
            ExportValue(node, fCuboid.Perforated().Extent(), "Cuboid", "Perforated", "Extent");
            ExportValue(node, fCuboid.Perforated().Spacing(), "Cuboid", "Perforated", "Spacing");
            ExportValue(node, fCuboid.Perforated().Diameter(), "Cuboid", "Perforated", "Diameter");
            ExportValue(node, fCuboid.Perforated().Depth(), "Cuboid", "Perforated", "Depth");
        }
    }
    {
        ExportValue(node, fMultiLayer.Width(), "MultiLayer", "Width");
        ExportValue(node, fMultiLayer.Height(), "MultiLayer", "Height");
        ExportValue(node, fMultiLayer.Thickness(), "MultiLayer", "Thickness");
        ExportValue(node, fMultiLayer.Spacing(), "MultiLayer", "Spacing");
        ExportValue(node, fMultiLayer.Count(), "MultiLayer", "Count");
        ExportValue(
            node, [this] {
                switch (fMultiLayer.DetailType()) {
                case MultiLayerTarget::ShapeDetailType::Flat:
                    return "Flat"s;
                case MultiLayerTarget::ShapeDetailType::Perforated:
                    return "Perforated"s;
                }
                std23::unreachable();
            }(),
            "MultiLayer", "DetailType");
        {
            ExportValue(node, fMultiLayer.Perforated().ExtentZ(), "MultiLayer", "Perforated", "ExtentZ");
            ExportValue(node, fMultiLayer.Perforated().ExtentY(), "MultiLayer", "Perforated", "ExtentY");
            ExportValue(node, fMultiLayer.Perforated().Spacing(), "MultiLayer", "Perforated", "Spacing");
            ExportValue(node, fMultiLayer.Perforated().Diameter(), "MultiLayer", "Perforated", "Diameter");
        }
    }
    ExportValue(node, fSilicaAerogelDensity, "SilicaAerogelDensity");
    ExportValue(node, fEffectiveTemperature, "EffectiveTemperature");
    ExportValue(node, fFormationProbability, "FormationProbability");
    ExportValue(node, fMeanFreePath, "MeanFreePath");
}

Target::CuboidTarget::CuboidTarget() :
    ShapeBase{},
    fWidth{6_cm},
    fThickness{1_cm},
    fDetailType{ShapeDetailType::Perforated},
    fPerforated{} {}

Target::CuboidTarget::PerforatedCuboid::PerforatedCuboid() :
    DetailBase{},
    fHalfExtent{4_cm / 2},
    fSpacing{55_um},
    fRadius{184_um / 2},
    fDepth{2_mm} {}

Target::MultiLayerTarget::MultiLayerTarget() :
    ShapeBase{},
    fWidth{6_cm},
    fHeight{5_cm},
    fThickness{3_mm},
    fSpacing{2_mm},
    fCount{11},
    fDetailType{ShapeDetailType::Perforated},
    fPerforated{} {}

Target::MultiLayerTarget::PerforatedMultiLayer::PerforatedMultiLayer() :
    DetailBase{},
    fHalfExtentZ{5_cm / 2},
    fHalfExtentY{4_cm / 2},
    fSpacing{55_um},
    fRadius{184_um / 2} {}

} // namespace MACE::Detector::Description
