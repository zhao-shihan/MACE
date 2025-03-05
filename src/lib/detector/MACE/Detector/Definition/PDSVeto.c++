#include "MACE/Detector/Definition/PDSVeto.h++"
#include "MACE/Detector/Description/ECALField.h++"
#include "MACE/Detector/Description/PDSVeto.h++"

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
    const auto MPTFiber{new G4MaterialPropertiesTable};
    MPTFiber->AddProperty("RINDEX", veto.WlsRIndexEnergy(), veto.WlsRIndex());
    MPTFiber->AddProperty("ABSLENGTH",veto.WlsVAbsEnergy(),veto.WlsVAbsLength());
    MPTFiber->AddProperty("WLSABSLENGTH", veto.WlsAbsEnergy(), veto.WlsAbsLength());
    MPTFiber->AddProperty("WLSCOMPONENT", veto.WlsEmissionEnergy(), veto.WlsEmissionAmplitude());
    MPTFiber->AddConstProperty("WLSTIMECONSTANT", 0.5_ns);
    fWls->SetMaterialPropertiesTable(MPTFiber);
}

auto PDSVeto::ConstructLV() -> void {
    const auto& veto{Description::PDSVeto::Instance()};
    const auto [minPhotonEnergy, maxPhotonEnergy]{std::ranges::minmax(veto.PSScintillationEnergyBin())};

    const auto rfSurfacePropertiesTable{new G4MaterialPropertiesTable};
    rfSurfacePropertiesTable->AddProperty("REFLECTIVITY", {minPhotonEnergy, maxPhotonEnergy}, {0.985, 0.985});
    const auto cathodeSurfacePropertiesTable{new G4MaterialPropertiesTable};
    cathodeSurfacePropertiesTable->AddProperty("REFLECTIVITY", {minPhotonEnergy, maxPhotonEnergy}, {0., 0.});
    cathodeSurfacePropertiesTable->AddProperty("EFFICIENCY", veto.SiPMEnergyBin(), veto.SiPMEfficiency());

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
        const auto logicStrip{Make<G4LogicalVolume>(solidStrip, fPlasticScintillaor, fmt::format("VetoStrip_{}", typeID))};
        // skin surface PS strip
        const auto rfSurface{new G4OpticalSurface("reflector", unified, polished, dielectric_metal)};
        new G4LogicalSkinSurface{"reflectorSurface", logicStrip, rfSurface};
        rfSurface->SetMaterialPropertiesTable(rfSurfacePropertiesTable);

        const auto solidAlAbsorber{Make<G4Box>("temp",
                                               dynamic_cast<const G4Box*>(logicModule->GetSolid())->GetXHalfLength(),
                                               veto.AlAbsorberThickness() / 2,
                                               psStripLength / 2)};
        Make<G4LogicalVolume>(solidAlAbsorber, fAl, fmt::format("VetoAlAbsorber_{}", typeID));

        const auto fiberLength{psStripLength};
        const auto solidFiberHole{Make<G4Tubs>("temp", 0, veto.PSHoleRadius(), fiberLength / 2, 0, 2 * pi)};
        Make<G4LogicalVolume>(solidFiberHole, fSiliconeGrease, fmt::format("VetoFiberHole_{}", typeID));
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
            auto phyStripBox{Make<G4PVPlacement>(aStripConfig.stripLocalTranform,
                                                 LogicalVolume(fmt::format("VetoStripBox_{}", typeID)),
                                                 fmt::format("VetoStripBox_{}_all_all_{}", typeID, aStripConfig.stripLocalID),
                                                 LogicalVolume(fmt::format("VetoLayerBox_{}", typeID)),
                                                 false,
                                                 aStripConfig.stripID,
                                                 checkOverlaps)};
            if (veto.SelectedType() != -1) { 
                // fmt::println("@info\nSingle strip configuration info: ");
                // fmt::println("x0: {}", phyStripBox->GetObjectTranslation().getX());
                // fmt::println("y0: {}", phyStripBox->GetObjectTranslation().getY());
                // fmt::println("z0: {}", phyStripBox->GetObjectTranslation().getZ());
                // const auto frameRot{phyStripBox->GetFrameRotation()};
                // fmt::print("frame rotation: {}",frameRot);
                break; }
        }
        // strips
        const auto physicalStrip{Make<G4PVPlacement>(G4Transform3D::Identity,
                                                        LogicalVolume(fmt::format("VetoStrip_{}", typeID)),
                                                        fmt::format("VetoStrip_{}", typeID),
                                                        LogicalVolume(fmt::format("VetoStripBox_{}", typeID)),
                                                        false,
                                                        0,
                                                        checkOverlaps)};
        if (veto.SelectedType() != -1) { 
            fPhySingleStrip = physicalStrip;
            fLogSingleStrip = fPhySingleStrip->GetLogicalVolume();
        //     fmt::println("@info\nSingle strip configuration info: ");
        //     G4Box solidStrip {(G4Box)physicalStrip->GetLogicalVolume()->GetSolid()};
        //     fmt::println("strip scaleX: {}", solidStrip.GetXHalfLength()*2.);
        //     fmt::println("strip scaleY: {}", solidStrip.GetYHalfLength()*2.);
        //     fmt::println("strip scaleZ: {}", solidStrip.GetZHalfLength()*2.);
            }


        // fibers
        const auto fiberNum{veto.FiberNum()};
        const auto fiberSpacing{veto.PSWidth() / (fiberNum)};
        for (int fiberCount{}; fiberCount < fiberNum; ++fiberCount) {
            const auto fiberCenterX{-veto.PSWidth() / 2 + fiberSpacing * (2 * fiberCount + 1) / 2};
            const G4Transform3D fiberTransform{
                G4RotationMatrix::IDENTITY, G4ThreeVector{fiberCenterX, 0, 0}
            };
            const auto physicalFiberHole{Make<G4PVPlacement>(fiberTransform,
                                                             LogicalVolume(fmt::format("VetoFiberHole_{}", typeID)),
                                                             fmt::format("VetoFiberHole_{}", typeID),
                                                             LogicalVolume(fmt::format("VetoStrip_{}", typeID)),
                                                             false,
                                                             fiberCount,
                                                             checkOverlaps)};
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

        // border surface air -> strips
        const auto airPaintSurface{new G4OpticalSurface("AirPaint", unified, polished, dielectric_metal)};
        new G4LogicalBorderSurface{"airPaintSurface", Mother().PhysicalVolume(), physicalStrip, airPaintSurface};
        airPaintSurface->SetMaterialPropertiesTable(airPaintSurfacePropertiesTable);
        // border surface strip(fiberholes(fibers)) -> coupler
        for (auto physicalCoupler : PhysicalVolumes("VetoSiPMCoupler")) {
            if (physicalStrip && physicalCoupler) {
                const auto couplerSurface{new G4OpticalSurface("coupler", unified, polished, dielectric_dielectric)};
                new G4LogicalBorderSurface{"couplerSurface",
                                           physicalStrip,
                                           physicalCoupler,
                                           couplerSurface};
                couplerSurface->SetMaterialPropertiesTable(couplerSurfacePropertiesTable);
            }
        }
        // border surface fiberholes -> fibers
        for (auto physicalFiberHole : PhysicalVolumes(fmt::format("VetoFiberHole_{}", typeID))) {
            for (auto physicalFiber : PhysicalVolumes(fmt::format("VetoFiber_{}", typeID))) {
                if (physicalFiberHole && physicalFiber) {
                    const auto couplerSurface{new G4OpticalSurface("coupler", unified, polished, dielectric_dielectric)};
                    new G4LogicalBorderSurface{"couplerSurface",
                                               physicalFiberHole,
                                               physicalFiber,
                                               couplerSurface};
                    couplerSurface->SetMaterialPropertiesTable(couplerSurfacePropertiesTable);
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
