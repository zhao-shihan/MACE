#include "MACE/Detector/Definition/PDSVeto.h++"
#include "MACE/Detector/Description/ECALField.h++"
#include "MACE/Detector/Description/PDSVeto.h++"

#include "Mustard/Env/BasicEnv.h++"
#include "Mustard/Utility/LiteralUnit.h++"
#include "Mustard/Utility/MathConstant.h++"
#include "Mustard/Utility/PrettyLog.h++"
#include "Mustard/Utility/VectorCast.h++"

#include "unordered_set"

#include "G4Box.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4NistManager.hh"
#include "G4OpticalSurface.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Definition {

using namespace Mustard::LiteralUnit;
using namespace Mustard::MathConstant;

auto PDSVeto::DefineMaterial() -> void {
    const auto& veto{Description::PDSVeto::Instance()};
    const auto nistManager{G4NistManager::Instance()};
    const auto [minPhotonEnergy, maxPhotonEnergy]{std::ranges::minmax(veto.PSScintillationEnergyBin())};
    // SiPM material
    fSilicon = nistManager->FindOrBuildMaterial("G4_Si");
    // coupler material
    const auto hydrogenElement{nistManager->FindOrBuildElement("H")};
    const auto carbonElement{nistManager->FindOrBuildElement("C")};
    const auto oxygenElement{nistManager->FindOrBuildElement("O")};
    const auto siliconElement{nistManager->FindOrBuildElement("Si")};
    fSiliconeGrease = new G4Material("siliconeGrease", 1.06_g_cm3, 4, kStateLiquid);
    fSiliconeGrease->AddElement(carbonElement, 2);
    fSiliconeGrease->AddElement(hydrogenElement, 6);
    fSiliconeGrease->AddElement(oxygenElement, 1);
    fSiliconeGrease->AddElement(siliconElement, 1);
    const auto siliconeGreasePropertiesTable{new G4MaterialPropertiesTable};
    siliconeGreasePropertiesTable->AddProperty("RINDEX", {minPhotonEnergy, maxPhotonEnergy}, {1.46, 1.46}); // EJ-550
    siliconeGreasePropertiesTable->AddProperty("ABSLENGTH", {minPhotonEnergy, maxPhotonEnergy}, {100_cm, 100_cm});
    fSiliconeGrease->SetMaterialPropertiesTable(siliconeGreasePropertiesTable);
    // SiPM window material
    fEpoxy = new G4Material("epoxy", 1.18_g_cm3, 3, kStateSolid);
    fEpoxy->AddElement(carbonElement, 0.7362);
    fEpoxy->AddElement(hydrogenElement, 0.0675);
    fEpoxy->AddElement(oxygenElement, 0.1963);
    const auto epoxyPropertiesTable{new G4MaterialPropertiesTable};
    epoxyPropertiesTable->AddProperty("RINDEX", {minPhotonEnergy, maxPhotonEnergy}, {1.59, 1.59}); // microft-30032-smt
    fEpoxy->SetMaterialPropertiesTable(epoxyPropertiesTable);
    // plastic scintillator material
    fPlasticScintillaor = nistManager->FindOrBuildMaterial("G4_POLYSTYRENE");
    // air
    fAir = nistManager->FindOrBuildMaterial("G4_AIR");
    fAl = nistManager->FindOrBuildMaterial("G4_Al");
    // WLS fiber material
    fWls = nistManager->FindOrBuildMaterial("G4_POLYSTYRENE");
    fWls->SetFreeElectronDensity(1.19_g_cm3);
    const auto WLSFiberMaterial{new G4MaterialPropertiesTable};
    WLSFiberMaterial->AddProperty("RINDEX", veto.WLSRIndexEnergy(), veto.WLSRIndex());
    WLSFiberMaterial->AddProperty("ABSLENGTH", veto.WLSVAbsEnergy(), veto.WLSVAbsLength());
    WLSFiberMaterial->AddProperty("WLSABSLENGTH", veto.WLSAbsEnergy(), veto.WLSAbsLength());
    WLSFiberMaterial->AddProperty("WLSCOMPONENT", veto.WLSEmissionEnergy(), veto.WLSEmissionAmplitude());
    WLSFiberMaterial->AddConstProperty("WLSTIMECONSTANT", 0.5_ns);
    fWls->SetMaterialPropertiesTable(WLSFiberMaterial);
}

auto PDSVeto::ConstructLV() -> void {
    const auto& veto{Description::PDSVeto::Instance()};
    const auto [minPhotonEnergy, maxPhotonEnergy]{std::ranges::minmax(veto.PSScintillationEnergyBin())};

    const auto rfSurfacePropertiesTable{new G4MaterialPropertiesTable};
    rfSurfacePropertiesTable->AddProperty("REFLECTIVITY", {minPhotonEnergy, maxPhotonEnergy}, {0.985, 0.985});
    const auto cathodeSurfacePropertiesTable{new G4MaterialPropertiesTable};
    cathodeSurfacePropertiesTable->AddProperty("REFLECTIVITY", {minPhotonEnergy, maxPhotonEnergy}, {0., 0.});
    cathodeSurfacePropertiesTable->AddProperty("EFFICIENCY", veto.SiPMEnergyBin(), veto.SiPMEfficiency());

    const auto& categoryConfiguration{veto.CategoryConfiguration()};
    for (int categoryID{}; categoryID < 4; ++categoryID) {
        // fmt::println("categoryname: {}",thisCategoryName);
        const auto moduleLength{categoryConfiguration[categoryID].moduleLength};
        const auto moduleWidth{categoryConfiguration[categoryID].moduleWidth};
        const auto moduleThickness{categoryConfiguration[categoryID].moduleThickness};
        // fmt::println("moudle size:{},{},{}",moduleLength,moduleThickness,moduleWidth);
        // define solids and logical volumes
        const auto solidModule{Make<G4Box>("temp",
                                           moduleWidth / 2,
                                           moduleThickness / 2,
                                           moduleLength / 2)};
        const auto logicModule{Make<G4LogicalVolume>(solidModule, fAir, fmt::format("VetoModuleBox_{}", categoryID))};

        const auto solidStripBox{Make<G4Box>("temp",
                                             veto.PSWidth() / 2 + veto.ReflectiveFilmThickness(),
                                             veto.PSThickness() / 2 + veto.ReflectiveFilmThickness(),
                                             moduleLength / 2)};
        const auto logicStripBox{Make<G4LogicalVolume>(solidStripBox, fAir, fmt::format("VetoStripBox_{}", categoryID))};

        const auto stripBoxHalfLength{dynamic_cast<const G4Box*>(logicStripBox->GetSolid())->GetZHalfLength()};
        const auto psStripLength{(stripBoxHalfLength - (veto.SiPMThickness() + veto.SiPMCouplerThickness())) * 2};
        const auto solidStrip{Make<G4Box>("temp",
                                          veto.PSWidth() / 2,
                                          veto.PSThickness() / 2,
                                          psStripLength / 2)};
        const auto logicStrip{Make<G4LogicalVolume>(solidStrip, fPlasticScintillaor, fmt::format("VetoStrip_{}", categoryID))};
        // skin surface PS strip
        const auto rfSurface{new G4OpticalSurface("reflector", unified, polished, dielectric_metal)};
        new G4LogicalSkinSurface{"reflectorSurface", logicStrip, rfSurface};
        rfSurface->SetMaterialPropertiesTable(rfSurfacePropertiesTable);

        const auto solidAlAbsorber{Make<G4Box>("temp",
                                               dynamic_cast<const G4Box*>(logicModule->GetSolid())->GetXHalfLength(),
                                               veto.AlAbsorberThickness() / 2,
                                               psStripLength / 2)};
        Make<G4LogicalVolume>(solidAlAbsorber, fAl, fmt::format("VetoAlAbsorber_{}", categoryID));

        const auto fiberLength{psStripLength};
        const auto solidFiberHole{Make<G4Tubs>("temp", 0, veto.PSHoleRadius(), fiberLength / 2, 0, 2 * pi)};
        Make<G4LogicalVolume>(solidFiberHole, fSiliconeGrease, fmt::format("VetoFiberHole_{}", categoryID));
        const auto solidFiber{Make<G4Tubs>("temp", 0, veto.PSFiberRadius(), fiberLength / 2, 0, 2 * pi)};
        Make<G4LogicalVolume>(solidFiber, fWls, fmt::format("VetoFiber_{}", categoryID));
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
    const auto logicSiPM{Make<G4LogicalVolume>(solidSiPMCathode, fSilicon, "VetoCathode")};
    // surface cathode skin
    const auto cathodeSurface{new G4OpticalSurface("Cathode", unified, polished, dielectric_metal)};
    new G4LogicalSkinSurface{"cathodeSkinSurface", logicSiPM, cathodeSurface};
    cathodeSurface->SetMaterialPropertiesTable(cathodeSurfacePropertiesTable);
}

auto PDSVeto::Construct(bool checkOverlaps) -> void {
    const auto& veto{Description::PDSVeto::Instance()};
    const auto [minPhotonEnergy, maxPhotonEnergy]{std::ranges::minmax(veto.PSScintillationEnergyBin())};
    DefineMaterial();
    ConstructLV();
    // surface definition
    const auto airPaintSurfacePropertiesTable{new G4MaterialPropertiesTable};
    airPaintSurfacePropertiesTable->AddProperty("REFLECTIVITY", {minPhotonEnergy, maxPhotonEnergy}, {0, 0});
    const auto couplerSurfacePropertiesTable{new G4MaterialPropertiesTable};
    couplerSurfacePropertiesTable->AddProperty("TRANSMITTANCE", {minPhotonEnergy, maxPhotonEnergy}, {1, 1});

    if (veto.SelectedCategory() < -1 or veto.SelectedCategory() > 3) {
        Mustard::Utility::PrintWarning(fmt::format("\n no such category: category_{}\n"
                                                   "available category selection:\n"
                                                   "category_3 (Cap2)\n"
                                                   "category_2 (Cap1)\n"
                                                   "category_1 (Side)\n"
                                                   "category_0 (Top)\n"
                                                   "category_-1 (All)\n",
                                                   veto.SelectedCategory()));
    }
    for (auto aCategoryConfiguration : veto.CategoryConfiguration()) {
        auto categoryID{aCategoryConfiguration.categoryID};
        auto singleStripTranslation{new G4ThreeVector()};
        if ((veto.SelectedCategory() != -1)) {
            if (categoryID != veto.SelectedCategory()) {
                continue;
            }
        }

        for (auto aModuleConfig : aCategoryConfiguration.modules) {
            auto phyModuleBox{Make<G4PVPlacement>(aModuleConfig.moduleTransform,
                                                  LogicalVolume(fmt::format("VetoModuleBox_{}", categoryID)),
                                                  fmt::format("VetoModuleBox_{}_{}", categoryID, aModuleConfig.moduleLocalID),
                                                  Mother().LogicalVolume(),
                                                  false,
                                                  aModuleConfig.moduleID,
                                                  checkOverlaps)};
            if (veto.SelectedCategory() != -1) {
                (*singleStripTranslation) += phyModuleBox->GetTranslation();
                fmt::println("@info\nSingle strip configuration info: ");
                fmt::println("x_moduleBox: {},{},{}", phyModuleBox->GetTranslation().getX(), phyModuleBox->GetTranslation().getY(), phyModuleBox->GetTranslation().getZ());
                break;
            }
        }
        for (auto aLayerConfig : aCategoryConfiguration.modules[0].alLayers) {

            if (veto.SelectedCategory() == -1 and aLayerConfig.layerLocalID > 0) {
                Make<G4PVPlacement>(aLayerConfig.alAbsorberLocalTransform,
                                    LogicalVolume(fmt::format("VetoAlAbsorber_{}", categoryID)),
                                    fmt::format("VetoAlAbsorber_{}_allModules_{}", categoryID, aLayerConfig.layerLocalID),
                                    LogicalVolume(fmt::format("VetoModuleBox_{}", categoryID)),
                                    false,
                                    aLayerConfig.layerLocalID,
                                    checkOverlaps);
            }
        }
        for (auto aStripConfig : aCategoryConfiguration.modules[0].strips) {
            auto phyStripBox{Make<G4PVPlacement>(aStripConfig.stripLocalTransform,
                                                 LogicalVolume(fmt::format("VetoStripBox_{}", categoryID)),
                                                 fmt::format("VetoStripBox_{}_allModules_{}", categoryID, aStripConfig.stripLocalID),
                                                 LogicalVolume(fmt::format("VetoModuleBox_{}", categoryID)),
                                                 false,
                                                 aStripConfig.stripLocalID,
                                                 checkOverlaps)};
            if (veto.SelectedCategory() != -1) {
                (*singleStripTranslation) += phyStripBox->GetTranslation();
                fmt::println("x_stripBox: {},{},{}", phyStripBox->GetTranslation().getX(), phyStripBox->GetTranslation().getY(), phyStripBox->GetTranslation().getZ());
                fmt::println("Total actual X: {},{},{}", (*singleStripTranslation).getX(), (*singleStripTranslation).getY(), (*singleStripTranslation).getZ()); // fmt::print("frame rotation: {}",frameRot);
                break;
            }
        }
        // strips
        const auto physicalStrip{Make<G4PVPlacement>(G4Transform3D::Identity,
                                                     LogicalVolume(fmt::format("VetoStrip_{}", categoryID)),
                                                     fmt::format("VetoStrip_{}", categoryID),
                                                     LogicalVolume(fmt::format("VetoStripBox_{}", categoryID)),
                                                     false,
                                                     0,
                                                     checkOverlaps)};

        // fibers
        const auto fiberNum{veto.FiberNum()};
        const auto fiberSpacing{veto.PSWidth() / (fiberNum)};
        for (int fiberCount{}; fiberCount < fiberNum; ++fiberCount) {
            const auto fiberCenterX{-veto.PSWidth() / 2 + fiberSpacing * (2 * fiberCount + 1) / 2};
            const G4Transform3D fiberTransform{
                G4RotationMatrix::IDENTITY, G4ThreeVector{fiberCenterX, 0, 0}
            };
            const auto physicalFiberHole{Make<G4PVPlacement>(fiberTransform,
                                                             LogicalVolume(fmt::format("VetoFiberHole_{}", categoryID)),
                                                             fmt::format("VetoFiberHole_{}", categoryID),
                                                             LogicalVolume(fmt::format("VetoStrip_{}", categoryID)),
                                                             false,
                                                             fiberCount,
                                                             checkOverlaps)};
            for (int sideCount{}; sideCount < 2; ++sideCount) {                              // loop by one pairs' 2 sides
                const auto readBoxRotation{G4RotateX3D{std::pow(-1., sideCount) * pi / 2.}}; // SiPM&coupler
                const auto stripBoxHalfLength{dynamic_cast<const G4Box*>(LogicalVolume(fmt::format("VetoStripBox_{}", categoryID))->GetSolid())->GetZHalfLength()};
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
                                    LogicalVolume(fmt::format("VetoStripBox_{}", categoryID)),
                                    false,
                                    sideCount,
                                    checkOverlaps);
                Make<G4PVPlacement>(SiPMTransform,
                                    LogicalVolume("VetoSiPM"),
                                    "VetoSiPM",
                                    LogicalVolume(fmt::format("VetoStripBox_{}", categoryID)),
                                    false,
                                    fiberCount * 2 + sideCount,
                                    checkOverlaps);
            }
        }
        Make<G4PVPlacement>(G4Transform3D::Identity,
                            LogicalVolume(fmt::format("VetoFiber_{}", categoryID)),
                            fmt::format("VetoFiber_{}", categoryID),
                            LogicalVolume(fmt::format("VetoFiberHole_{}", categoryID)),
                            false,
                            0,
                            checkOverlaps);

        // border surface air -> strips
        const auto airPaintSurface{new G4OpticalSurface("AirPaint", unified, polished, dielectric_metal)};
        new G4LogicalBorderSurface{"airPaintSurface", Mother().PhysicalVolume(), physicalStrip, airPaintSurface};
        airPaintSurface->SetMaterialPropertiesTable(airPaintSurfacePropertiesTable);
        // border surface strip(fiberholes(fibers)) -> coupler
        for (auto physicalCoupler : PhysicalVolumes("VetoSiPMCoupler")) {
            if (physicalStrip && physicalCoupler) {
                const auto couplerSurfaceStripToCoupler{new G4OpticalSurface("coupler", unified, polished, dielectric_dielectric)};
                new G4LogicalBorderSurface{"couplerSurface",
                                           physicalStrip,
                                           physicalCoupler,
                                           couplerSurfaceStripToCoupler};
                couplerSurfaceStripToCoupler->SetMaterialPropertiesTable(couplerSurfacePropertiesTable);
            }
        }
        // border surface strips -> fiberholes
        for (auto physicalFiberHole : PhysicalVolumes(fmt::format("VetoFiberHole_{}", categoryID))) {
            if (physicalStrip && physicalFiberHole) {
                const auto couplerSurfaceStripToFiberHole{new G4OpticalSurface("coupler", unified, polished, dielectric_dielectric)};
                new G4LogicalBorderSurface{"couplerSurface",
                                           physicalStrip,
                                           physicalFiberHole,
                                           couplerSurfaceStripToFiberHole};
                couplerSurfaceStripToFiberHole->SetMaterialPropertiesTable(couplerSurfacePropertiesTable);
            }
        }
        // border surface fiberholes -> fibers
        for (auto physicalFiberHole : PhysicalVolumes(fmt::format("VetoFiberHole_{}", categoryID))) {
            for (auto physicalFiber : PhysicalVolumes(fmt::format("VetoFiber_{}", categoryID))) {
                if (physicalFiberHole && physicalFiber) {
                    const auto couplerSurfaceFiberHoleToFiber{new G4OpticalSurface("coupler", unified, polished, dielectric_dielectric)};
                    new G4LogicalBorderSurface{"couplerSurface",
                                               physicalFiberHole,
                                               physicalFiber,
                                               couplerSurfaceFiberHoleToFiber};
                    couplerSurfaceFiberHoleToFiber->SetMaterialPropertiesTable(couplerSurfacePropertiesTable);
                }
            }
        }
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
