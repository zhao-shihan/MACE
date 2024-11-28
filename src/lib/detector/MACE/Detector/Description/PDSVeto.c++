#include "MACE/Detector/Description/ECALField.h++"
#include "MACE/Detector/Description/PDSVeto.h++"

#include "Mustard/Utility/LiteralUnit.h++"
#include "Mustard/Utility/MathConstant.h++"
#include "Mustard/Utility/VectorCast.h++"

#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"

namespace MACE::Detector::Description {

using namespace Mustard::LiteralUnit::Length;
using namespace Mustard::MathConstant;

PDSVeto::PDSVeto() :
    DescriptionWithCacheBase{"PDSVeto"},
    // Geometry
    fNModuleOfaType{this, 1, 2, 4, 4},
    fNLayerPerModuleOfaType{this, 3, 2, 2, 2},
    fNStripPerLayerOfaType{this, 12, 16, 5, 8},
    fStripLengthOfaType{this, 145_cm, 140_cm, 180_cm, 35_cm},
    fPSWidth{this, 10_cm},
    fPSThickness{this, 2_cm},
    fPSFiberRadius{this, 0.7_mm},
    fPSHoleRadius{this, 0.75_mm},
    fPSFiberCurvatureRadius{this, 13_cm},
    fInterPSGap{this, 1_mm},
    fInterModuleGap{this, 0.5_cm},
    fCap12Gap{this, 1_cm},
    fModuleOffset{this, 1_cm},
    fAlAbsorberThickness{this, 0.6_cm},
    fReflectiveFilmThickness{this, 0.4_mm},
    fSiPMThickness{this, 0.2_mm},
    fSiPMCathodeThickness{this, 0.1_mm},
    fSiPMCouplerThickness{this, 0.1_mm},
    fSiPMSize{this, 3_mm},
    fSolenoidWindowRadius{this, 14_cm},
    fFiberNum{this, 4},
    fSelectedType{this, -1},
    fTypeConfiguration{this, [this] { return CalculateTypeConfiguration(); }},
    fStripInformation{this, [this] { return CalculateStripInformation(); }} {}

auto PDSVeto::CalculateTypeConfiguration() const -> std::vector<TypeConfiguration> {
    std::vector<double> moduleLengths;
    std::vector<double> moduleThicknesses;
    std::vector<double> moduleWidths;
    for (int typeID{}; typeID < (*fNModuleOfaType).size(); ++typeID) {
        moduleLengths.emplace_back((*fStripLengthOfaType)[typeID] + (*fSiPMThickness + *fSiPMCouplerThickness) * 2);
        moduleWidths.emplace_back(((*fPSWidth + *fReflectiveFilmThickness * 2) + *fInterPSGap) * (*fNStripPerLayerOfaType)[typeID] - *fInterPSGap + *fModuleOffset * ((*fNLayerPerModuleOfaType)[typeID] - 1));
        moduleThicknesses.emplace_back(((*fPSThickness + *fReflectiveFilmThickness * 2) + *fAlAbsorberThickness) * (*fNLayerPerModuleOfaType)[typeID] - *fAlAbsorberThickness);
    }
    const auto sideModuleXShift{fSolenoidWindowRadius + moduleWidths[2] + moduleThicknesses[1] / 2 + *fInterModuleGap};
    const G4ThreeVector side0ModuleCenter{sideModuleXShift, 0, 0};
    const G4ThreeVector side1ModuleCenter{-sideModuleXShift, 0, 0};

    const auto cap2ModuleYShift{fSolenoidWindowRadius + moduleWidths[3] / 2};
    const auto cap2ModuleZShift{moduleWidths[0] / 2 + *fInterModuleGap + moduleThicknesses[2] + *fCap12Gap + moduleThicknesses[3] / 2};
    const G4ThreeVector cap2Module0Center{0, cap2ModuleYShift, cap2ModuleZShift};
    const G4ThreeVector cap2Module1Center{0, -cap2ModuleYShift, cap2ModuleZShift};
    const auto cap2Module2Center{-cap2Module0Center};
    const auto cap2Module3Center{-cap2Module1Center};

    const auto cap1ModuleXShift{fSolenoidWindowRadius + moduleWidths[2] / 2};
    const auto cap1ModuleZShift(moduleWidths[0] / 2 + *fInterModuleGap + moduleThicknesses[2] / 2);
    const G4ThreeVector cap1Module0Center{cap1ModuleXShift, 0, cap1ModuleZShift};
    const G4ThreeVector cap1Module1Center{-cap1ModuleXShift, 0, cap1ModuleZShift};
    const auto cap1Module2Center{-cap1Module0Center};
    const auto cap1Module3Center{-cap1Module1Center};

    const auto topModuleYShift{moduleWidths[1] / 2 + *fInterModuleGap + moduleThicknesses[0] / 2};
    const G4ThreeVector topModuleCenter{0, topModuleYShift, 0};

    const auto topModuleRotation{G4RotateY3D{pi / 2}.getRotation()};

    const auto side0ModuleRotation{G4RotateZ3D{pi / 2}.getRotation()};
    const auto side1ModuleRotation{G4RotateZ3D{-pi / 2}.getRotation()};

    const auto cap1ModuleRotation{G4RotateX3D{pi / 2}.getRotation()};
    const auto cap2ModuleRotation{(G4RotateZ3D{pi / 2} * G4RotateX3D{pi / 2}).getRotation()};
    const auto& ecalField{Description::ECALField::Instance()};
    const auto x0{Mustard::VectorCast<G4ThreeVector>(ecalField.Center())};

    const G4Transform3D topModuleTransform{topModuleRotation, topModuleCenter + x0};

    const G4Transform3D side0ModuleTransform{side0ModuleRotation, side0ModuleCenter + x0};
    const G4Transform3D side1ModuleTransform{side1ModuleRotation, side1ModuleCenter + x0};

    const G4Transform3D cap1Module0Transform{cap1ModuleRotation, cap1Module0Center + x0};
    const G4Transform3D cap1Module1Transform{cap1ModuleRotation, cap1Module1Center + x0};
    const G4Transform3D cap1Module2Transform{cap1ModuleRotation, cap1Module2Center + x0};
    const G4Transform3D cap1Module3Transform{cap1ModuleRotation, cap1Module3Center + x0};

    const G4Transform3D cap2Module0Transform{cap2ModuleRotation, cap2Module0Center + x0};
    const G4Transform3D cap2Module1Transform{cap2ModuleRotation, cap2Module1Center + x0};
    const G4Transform3D cap2Module2Transform{cap2ModuleRotation, cap2Module2Center + x0};
    const G4Transform3D cap2Module3Transform{cap2ModuleRotation, cap2Module3Center + x0};

    std::vector<TypeConfiguration> typeConfigurationS;
    const std::vector<G4Transform3D> moduleTransformS{topModuleTransform, side0ModuleTransform, side1ModuleTransform, cap1Module0Transform, cap1Module1Transform, cap1Module2Transform, cap1Module3Transform, cap2Module0Transform, cap2Module1Transform, cap2Module2Transform, cap2Module3Transform};
    int typeID{};
    int moduleID{};
    int layerID{};
    int stripID{};
    for (auto nModule : *fNModuleOfaType) {
        TypeConfiguration aTypeConfig;
        TypeConfiguration::ModuleConfiguration aModuleConfig;
        TypeConfiguration::ModuleConfiguration::LayerConfiguration aLayerConfig;
        TypeConfiguration::ModuleConfiguration::LayerConfiguration::StripConfiguration aStripConfig;
        aTypeConfig.typeID = typeID;
        aTypeConfig.moduleLength = moduleLengths[typeID];
        aTypeConfig.moduleWidth = moduleWidths[typeID];
        aTypeConfig.moduleThickness = moduleThicknesses[typeID];
        for (int moduleLocalID{}; moduleLocalID < nModule; ++moduleLocalID) {
            aModuleConfig.moduleID = moduleID;
            aModuleConfig.moduleLocalID = moduleLocalID;
            aModuleConfig.moduleTransform = moduleTransformS[moduleID];
            for (int layerLocalID{}; layerLocalID < (*fNLayerPerModuleOfaType)[typeID]; ++layerLocalID) {
                // clang-format off
                auto layerYShift{
                                -(moduleThicknesses[typeID]/2-(*fPSThickness+2*(*fReflectiveFilmThickness))/2)
                                +layerLocalID*((*fPSThickness+2*(*fReflectiveFilmThickness))+*fAlAbsorberThickness)
                                    };
                auto alAbsorberYShift{
                                layerYShift - (fPSThickness + 2 * fReflectiveFilmThickness) / 2 - fAlAbsorberThickness / 2};
                // clang-format on
                auto layerLocalTransform{
                    G4Transform3D{G4RotationMatrix::IDENTITY, G4ThreeVector{0, layerYShift, 0}}
                };
                auto alAbsorberLocalTransform{
                    G4Transform3D{G4RotationMatrix::IDENTITY, G4ThreeVector{0, alAbsorberYShift, 0}}
                }; // relative to modulebox

                aLayerConfig.layerID = layerID;
                aLayerConfig.layerLocalID = layerLocalID;
                aLayerConfig.layerLocalTransform = layerLocalTransform;
                aLayerConfig.alAbsorberLocalTransform = alAbsorberLocalTransform;//first Transform not used, only absorber between layers

                for (int stripLocalID{}; stripLocalID < (*fNStripPerLayerOfaType)[typeID]; ++stripLocalID) {
                    // clang-format off
                    auto stripXShift{
                                    -(moduleWidths[typeID]/2-(*fPSWidth+2*(*fReflectiveFilmThickness))/2)
                                    +stripLocalID*(*fPSWidth+2*(*fReflectiveFilmThickness)+*fInterPSGap)
                                    +layerLocalID*(*fModuleOffset)
                    };
                    // clang-format on
                    auto stripLocalTransform{
                        G4Transform3D{G4RotationMatrix::IDENTITY, G4ThreeVector{stripXShift, 0, 0}}
                    }; // relative to layerbox

                    aStripConfig.stripID = stripID;
                    aStripConfig.stripLocalID = stripLocalID;
                    aStripConfig.stripLocalTranform = stripLocalTransform;
                    aLayerConfig.strips.emplace_back(aStripConfig);
                    ++stripID;
                }
                aModuleConfig.layers.emplace_back(aLayerConfig);
                ++layerID;
            };
            aTypeConfig.modules.emplace_back(aModuleConfig);
            ++moduleID;
        }
        typeConfigurationS.emplace_back(aTypeConfig);
        ++typeID;
    }
    return typeConfigurationS;
}

auto PDSVeto::CalculateStripInformation() const -> std::vector<StripInformation> {
    std::vector<StripInformation> stripInformationS;
    int moduleID{};
    int layerID{};
    int stripID{};
    for (auto nModule : *fNModuleOfaType) {
        int typeID{};
        for (int moduleLocalID{}; moduleLocalID < nModule; ++moduleLocalID) {
            for (int layerLocalID{}; layerLocalID < (*fNLayerPerModuleOfaType)[typeID]; ++layerLocalID) {
                for (int stripLocalID; stripLocalID < (*fNStripPerLayerOfaType)[typeID]; ++stripLocalID) {
                    double x{((typeID == 1) && (typeID == 4)) ? 1. : 0.},
                        y{(typeID == 3) ? 1. : 0.},
                        z{(typeID == 2) ? 1. : 0.};
                    muc::array3d readDirection{x, y, z};
                    stripInformationS.emplace_back(StripInformation{stripID, stripLocalID, layerID, layerLocalID, moduleID, moduleLocalID, typeID, (*fStripLengthOfaType)[typeID], readDirection});
                    ++stripLocalID;
                }
                ++layerID;
            }
            ++moduleID;
        }
        ++typeID;
    }
    return stripInformationS;
}
auto PDSVeto::ImportAllValue(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fNModuleOfaType, "NModuleOfaType");
    ImportValue(node, fNLayerPerModuleOfaType, "NLayerPerModuleOfaType");
    ImportValue(node, fNStripPerLayerOfaType, "NStripPerLayerOfaType");
    ImportValue(node, fStripLengthOfaType, "StripLengthOfaType");
    ImportValue(node, fPSWidth, "PSWidth");
    ImportValue(node, fPSThickness, "PSThickness");
    ImportValue(node, fPSFiberRadius, "PSFiberRadius");
    ImportValue(node, fPSHoleRadius, "PSHoleRadius");
    ImportValue(node, fPSFiberCurvatureRadius, "PSFiberCurvatureRadius");
    ImportValue(node, fInterPSGap, "InterPSGap");
    ImportValue(node, fInterModuleGap, "InterModuleGap");
    ImportValue(node, fModuleOffset, "ModuleOffset");
    ImportValue(node, fCap12Gap, "Cap12Gap");
    ImportValue(node, fAlAbsorberThickness, "AlAbsorberThickness");
    ImportValue(node, fReflectiveFilmThickness, "ReflectiveFilmThickness");
    ImportValue(node, fSiPMThickness, "SiPMThickness");
    ImportValue(node, fSiPMCathodeThickness, "SiPMCathodeThickness");
    ImportValue(node, fSiPMCouplerThickness, "SiPMCouplerThickness");
    ImportValue(node, fSiPMSize, "SiPMSize");
    ImportValue(node, fSolenoidWindowRadius, "SolenoidWindowRadius");
    ImportValue(node, fFiberNum, "FiberNum");
    ImportValue(node, fSelectedType, "SelectedType");
}
auto PDSVeto::ExportAllValue(YAML::Node& node) const -> void {
    // Geometry

    ExportValue(node, fNModuleOfaType, "NModuleOfaType");
    ExportValue(node, fNLayerPerModuleOfaType, "NLayerPerModuleOfaType");
    ExportValue(node, fNStripPerLayerOfaType, "NStripPerLayerOfaType");
    ExportValue(node, fStripLengthOfaType, "StripLengthOfaType");
    ExportValue(node, fPSWidth, "PSWidth");
    ExportValue(node, fPSThickness, "PSThickness");
    ExportValue(node, fPSFiberRadius, "PSFiberRadius");
    ExportValue(node, fPSHoleRadius, "PSHoleRadius");
    ExportValue(node, fPSFiberCurvatureRadius, "PSFiberCurvatureRadius");
    ExportValue(node, fInterPSGap, "InterPSGap");
    ExportValue(node, fInterModuleGap, "InterModuleGap");
    ExportValue(node, fReflectiveFilmThickness, "ReflectiveFilmThickness");
    ExportValue(node, fModuleOffset, "ModuleOffset");
    ExportValue(node, fAlAbsorberThickness, "AlAbsorberThickness");
    ExportValue(node, fSiPMThickness, "SiPMThickness");
    ExportValue(node, fSiPMCathodeThickness, "SiPMCathodeThickness");
    ExportValue(node, fSiPMCouplerThickness, "SiPMCouplerThickness");
    ExportValue(node, fSiPMSize, "SiPMSize");
    ExportValue(node, fSolenoidWindowRadius, "SolenoidWindowRadius");
    ExportValue(node, fFiberNum, "FiberNum");
    ExportValue(node, fSelectedType, "SelectedType");
}
} // namespace MACE::Detector::Description
