#include "MACE/Detector/Definition/PDSVeto.h++"
#include "MACE/Detector/Description/ECALField.h++"
#include "MACE/Detector/Description/PDSVeto.h++"

#include "Mustard/Utility/LiteralUnit.h++"
#include "Mustard/Utility/MathConstant.h++"
#include "Mustard/Utility/PrettyLog.h++"
#include "Mustard/Utility/VectorCast.h++"

#include "unordered_set"

#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Definition {

using namespace Mustard::LiteralUnit;
using namespace Mustard::MathConstant;

auto PDSVeto::DefineMaterial() -> void {
    const auto nistManager{G4NistManager::Instance()};
    const auto hydrogenElement{nistManager->FindOrBuildElement("H")};
    const auto carbonElement{nistManager->FindOrBuildElement("C")};
    const auto oxygenElement{nistManager->FindOrBuildElement("O")};
    const auto siliconElement{nistManager->FindOrBuildElement("Si")};

    fSilicon = nistManager->FindOrBuildMaterial("G4_Si");

    fSiliconeGrease = new G4Material("siliconeGrease", 1.06_g_cm3, 4, kStateLiquid);
    fSiliconeGrease->AddElement(carbonElement, 2);
    fSiliconeGrease->AddElement(hydrogenElement, 6);
    fSiliconeGrease->AddElement(oxygenElement, 1);
    fSiliconeGrease->AddElement(siliconElement, 1);

    fPlasticScinllator = nistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    fAir = nistManager->FindOrBuildMaterial("G4_AIR");

    fEpoxy = new G4Material("epoxy", 1.18_g_cm3, 3, kStateSolid);
    fEpoxy->AddElement(carbonElement, 0.7362);
    fEpoxy->AddElement(hydrogenElement, 0.0675);
    fEpoxy->AddElement(oxygenElement, 0.1963);

    // const auto windowPropertiesTable{new G4MaterialPropertiesTable};
    // windowPropertiesTable->AddProperty("RINDEX", {minPhotonEnergy, maxPhotonEnergy}, {1.57, 1.57});
    // epoxy->SetMaterialPropertiesTable(windowPropertiesTable);
    fWls = nistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    fAl = nistManager->FindOrBuildMaterial("G4_Al");
}

auto PDSVeto::ConstructLV() -> void {
    const auto& veto{Description::PDSVeto::Instance()};
    const auto& typeConfiguration{veto.FTypeConfiguration()};
    for (int typeID{}; typeID < 4; ++typeID) {
        // fmt::println("typename: {}",thisTypeName);
        const auto moduleLength{typeConfiguration[typeID].moduleLength};
        const auto moduleWidth{typeConfiguration[typeID].moduleWidth};
        const auto moduleThickness{typeConfiguration[typeID].moduleThickness};
        // fmt::println("moudle size:{},{},{}",moduleLength,moduleThickness,moduleWidth);
        // define solids and logical volumes
        const auto solidModule{Make<G4Box>("temp",
                                           moduleWidth / 2,
                                           moduleThickness / 2,
                                           moduleLength / 2)};
        const auto logicModule{Make<G4LogicalVolume>(solidModule, fAir, fmt::format("VetoModuleBox_{}", typeID))};
        // fLVStoreOfTypes[typeID].fModule = logicModule;
        const auto solidLayerBox{Make<G4Box>("temp",
                                             moduleWidth / 2,
                                             veto.PSThickness() / 2 + veto.ReflectiveFilmThickness(),
                                             moduleLength / 2)};
        Make<G4LogicalVolume>(solidLayerBox, fAir, fmt::format("VetoLayerBox_{}", typeID));
        const auto solidStripBox{Make<G4Box>("temp",
                                             veto.PSWidth() / 2 + veto.ReflectiveFilmThickness(),
                                             veto.PSThickness() / 2 + veto.ReflectiveFilmThickness(),
                                             moduleLength / 2)};
        const auto logicStripBox{Make<G4LogicalVolume>(solidStripBox, fAir, fmt::format("VetoStripBox_{}", typeID))};
        // fLVStoreOfTypes[typeID].fStripBox = logicStripBox;
        const auto stripBoxHalfLength{dynamic_cast<const G4Box*>(logicStripBox->GetSolid())->GetZHalfLength()};
        const auto psStripLength{(stripBoxHalfLength - (veto.SiPMThickness() + veto.SiPMCouplerThickness())) * 2};
        const auto solidStrip{Make<G4Box>("temp",
                                          veto.PSWidth() / 2,
                                          veto.PSThickness() / 2,
                                          psStripLength / 2)};
        Make<G4LogicalVolume>(solidStrip, fPlasticScinllator, fmt::format("VetoStrip_{}", typeID));
        const auto solidAlAbsorber{Make<G4Box>("temp",
                                               dynamic_cast<const G4Box*>(logicModule->GetSolid())->GetXHalfLength(),
                                               veto.AlAbsorberThickness() / 2,
                                               psStripLength / 2)};
        Make<G4LogicalVolume>(solidAlAbsorber, fAl, fmt::format("VetoAlAbsorber_{}", typeID));
        const auto fiberLength{psStripLength};
        const auto solidFiberHole{Make<G4Tubs>("temp", 0, veto.PSHoleRadius(), fiberLength / 2, 0, 2 * pi)};
        Make<G4LogicalVolume>(solidFiberHole, fAir, fmt::format("VetoFiberHole_{}", typeID));
        const auto solidFiber{Make<G4Tubs>("temp", 0, veto.PSFiberRadius(), fiberLength / 2, 0, 2 * pi)};
        Make<G4LogicalVolume>(solidFiber, fWls, fmt::format("VetoFiber_{}", typeID));
    }
    const auto solidSiPMCoupuler{Make<G4Box>("temp",
                                             veto.SiPMSize() / 2,
                                             veto.SiPMCouplerThickness() / 2,
                                             veto.SiPMSize() / 2)};
    const auto solidSiPM{Make<G4Box>("temp",
                                     veto.SiPMSize() / 2,
                                     veto.SiPMThickness() / 2,
                                     veto.SiPMSize() / 2)};
    const auto solidSiPMCathode{Make<G4Box>("temp",
                                            veto.SiPMSize() / 2,
                                            veto.SiPMCathodeThickness() / 2,
                                            veto.SiPMSize() / 2)};
    Make<G4LogicalVolume>(solidSiPMCoupuler, fSiliconeGrease, "VetoSiPMCoupler");
    Make<G4LogicalVolume>(solidSiPM, fEpoxy, "VetoSiPM");
    Make<G4LogicalVolume>(solidSiPMCathode, fSilicon, "VetoCathode");
}

auto PDSVeto::Construct(bool checkOverlaps) -> void {
    const auto& veto{Description::PDSVeto::Instance()};
    DefineMaterial();
    ConstructLV();
    if (veto.SelectedType() < -1 or veto.SelectedType() > 3) {
        Mustard::Utility::PrintWarning(fmt::format("\n no such type: type_{}\n"
                                        "available type selection:\n"
                                        "type_3 (Cap2)\n"
                                        "type_2 (Cap1)\n"
                                        "type_1 (Side)\n"
                                        "type_0 (Top)\n"
                                        "type_-1 (All)\n",
                                        veto.SelectedType()));
    }
    for (auto aTypeConfig : veto.FTypeConfiguration()) {
        auto typeID{aTypeConfig.typeID};
        if ((veto.SelectedType() != -1) and (typeID != veto.SelectedType())) continue;
        for (auto aModuleConfig : aTypeConfig.modules) {
            Make<G4PVPlacement>(aModuleConfig.moduleTransform,
                                LogicalVolume(fmt::format("VetoModuleBox_{}", typeID)),
                                fmt::format("VetoModuleBox_{}_{}", typeID, aModuleConfig.moduleLocalID),
                                Mother().LogicalVolume(),
                                false,
                                aModuleConfig.moduleID,
                                checkOverlaps);
            if (veto.SelectedType() != -1) { break; }
        }
        for (auto aLayerConfig : aTypeConfig.modules[0].layers) {

            Make<G4PVPlacement>(aLayerConfig.layerLocalTransform,
                                LogicalVolume(fmt::format("VetoLayerBox_{}", typeID)),
                                fmt::format("VetoLayerBox_{}_all_{}", typeID, aLayerConfig.layerLocalID),
                                LogicalVolume(fmt::format("VetoModuleBox_{}", typeID)),
                                false,
                                aLayerConfig.layerLocalID,
                                checkOverlaps);
            if (veto.SelectedType() == -1 and aLayerConfig.layerLocalID > 0) {
                Make<G4PVPlacement>(aLayerConfig.alAbsorberLocalTransform,
                                    LogicalVolume(fmt::format("VetoAlAbsorber_{}", typeID)),
                                    fmt::format("VetoAlAbsorber_{}_all_{}", typeID, aLayerConfig.layerLocalID),
                                    LogicalVolume(fmt::format("VetoModuleBox_{}", typeID)),
                                    false,
                                    aLayerConfig.layerLocalID,
                                    checkOverlaps);
            }
            if (veto.SelectedType() != -1) { break; }
        }
        for (auto aStripConfig : aTypeConfig.modules[0].layers[0].strips) {
            Make<G4PVPlacement>(aStripConfig.stripLocalTranform,
                                LogicalVolume(fmt::format("VetoStripBox_{}", typeID)),
                                fmt::format("VetoStripBox_{}_all_all_{}", typeID, aStripConfig.stripLocalID),
                                LogicalVolume(fmt::format("VetoLayerBox_{}", typeID)),
                                false,
                                aStripConfig.stripID,
                                checkOverlaps);
            if (veto.SelectedType() != -1) { break; }
        }
        // strips
        Make<G4PVPlacement>(G4Transform3D::Identity,
                            LogicalVolume(fmt::format("VetoStrip_{}", typeID)),
                            fmt::format("VetoStrip_{}", typeID),
                            LogicalVolume(fmt::format("VetoStripBox_{}", typeID)),
                            false,
                            0,
                            checkOverlaps);
        // fibers
        auto fiberNum{veto.FiberNum()};
        const auto fiberSpacing{veto.PSWidth() / (fiberNum)};
        for (int fiberCount{}; fiberCount < fiberNum; ++fiberCount) {
            const auto fiberCenterX{-veto.PSWidth() / 2 + fiberSpacing * (2 * fiberCount + 1) / 2};
            const G4Transform3D fiberTransform{
                G4RotationMatrix::IDENTITY, G4ThreeVector{fiberCenterX, 0, 0}
            };
            Make<G4PVPlacement>(fiberTransform,
                                LogicalVolume(fmt::format("VetoFiberHole_{}", typeID)),
                                fmt::format("VetoFiberHole_{}", typeID),
                                LogicalVolume(fmt::format("VetoStrip_{}", typeID)),
                                false,
                                fiberCount,
                                checkOverlaps);
            for (int sideCount{}; sideCount < 2; ++sideCount) {                              // loop by one pairs' 2 sides
                const auto readBoxRotation{G4RotateX3D{std::pow(-1., sideCount) * pi / 2.}}; // SiPM&coupler
                const auto stripBoxHalfLength{dynamic_cast<const G4Box*>(LogicalVolume(fmt::format("VetoStripBox_{}", typeID))->GetSolid())->GetZHalfLength()};
                const auto SiPMPosZ{(stripBoxHalfLength - veto.SiPMThickness() / 2)};
                const auto couplerPosZ{stripBoxHalfLength - veto.SiPMThickness() - veto.SiPMCouplerThickness() / 2};
                G4Transform3D couplerTransform{
                    readBoxRotation.getRotation(), G4ThreeVector{fiberCenterX, 0, couplerPosZ * std::pow(-1., sideCount)}
                };
                G4Transform3D SiPMTransform{
                    readBoxRotation.getRotation(), G4ThreeVector{fiberCenterX, 0, SiPMPosZ * std::pow(-1., sideCount)}
                };
                Make<G4PVPlacement>(couplerTransform,
                                    LogicalVolume("VetoSiPMCoupler"),
                                    "VetoSiPMCoupler",
                                    LogicalVolume(fmt::format("VetoStripBox_{}", typeID)),
                                    false,
                                    sideCount,
                                    checkOverlaps);
                Make<G4PVPlacement>(SiPMTransform,
                                    LogicalVolume("VetoSiPM"),
                                    "VetoSiPM",
                                    LogicalVolume(fmt::format("VetoStripBox_{}", typeID)),
                                    false,
                                    sideCount,
                                    checkOverlaps);
            }
        }
        Make<G4PVPlacement>(G4Transform3D::Identity,
                            LogicalVolume(fmt::format("VetoFiber_{}", typeID)),
                            fmt::format("VetoFiber_{}", typeID),
                            LogicalVolume(fmt::format("VetoFiberHole_{}", typeID)),
                            false,
                            0,
                            checkOverlaps);
    }
    const auto cathodeRelativePosY{veto.SiPMThickness() / 2 - veto.SiPMCathodeThickness() / 2};
    G4Transform3D cathodeRelativeTransform{
        G4RotationMatrix::IDENTITY, G4ThreeVector{0, cathodeRelativePosY, 0}
    };
    Make<G4PVPlacement>(cathodeRelativeTransform,
                        LogicalVolume("VetoCathode"),
                        "VetoCathode",
                        LogicalVolume("VetoSiPM"),
                        false,
                        0,
                        checkOverlaps);
    fmt::println("finish construct!");
}
} // namespace MACE::Detector::Definition
